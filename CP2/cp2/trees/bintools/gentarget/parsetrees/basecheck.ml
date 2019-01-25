(*
 * Copyright (c) 2017
 *	The President and Fellows of Harvard College.
 *
 * Written by David A. Holland.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *)

open Typetree
open Basetree

(*
 * Things we check:
 *    - every type reference refers to a type that exists
 *    - compound types are not recursive
 *
 * Also, currently genencoding expects us to expand alias typenames
 * that appear in compound type declarations. This should probably
 * be put somewhere else and made more systematic. XXX.
 *
 * This module is responsible for making sure that enums are fully
 * populated and properly sized, and also for expanding WRAPTYPEs into
 * ENUMTYPEs.
 *
 * XXX: shortnames live in a different namespace. this is confusing
 * and bogus.
 *)

(**************************************************************)
(* context *)

type context = {
   (* definition pos for each type *)
   definedat: Pos.pos Types.StringMap.t ref;

   (* whether each type takes a width argument *)
   takeswidth: bool Types.StringMap.t ref;

   (* whether each type is a compound type *)
   iscompound: bool Types.StringMap.t ref;

   (* whether each type can be used with the expression type *)
   expressionable: bool Types.StringMap.t ref;

   (* definition pos for each longname (operand tag) *)
   longnamepos: Pos.pos Types.StringMap.t ref;

   (* definition pos for each shortname *)
   shortnamepos: Pos.pos Types.StringMap.t ref;

   (* definition pos for each symbol *)
   sympos: Pos.pos Types.StringMap.t ref;
}

let ctx_getdefinedat' ctx name =
   Types.StringMap.find name !(ctx.definedat)

let ctx_gettakeswidth' ctx name =
   Types.StringMap.find name !(ctx.takeswidth)

let ctx_getiscompound' ctx name =
   Types.StringMap.find name !(ctx.iscompound)

let ctx_getexpressionable' ctx name =
   Types.StringMap.find name !(ctx.expressionable)

let ctx_getlongnamepos' ctx name =
   Types.StringMap.find name !(ctx.longnamepos)

let ctx_getshortnamepos' ctx name =
   Types.StringMap.find name !(ctx.shortnamepos)

let ctx_getsympos' ctx name =
   Types.StringMap.find name !(ctx.sympos)

let ctx_getdefinedat ctx name =
   try Some (ctx_getdefinedat' ctx name)
   with Not_found -> None

let ctx_gettakeswidth ctx name =
   try Some (ctx_gettakeswidth' ctx name)
   with Not_found -> None

let ctx_getiscompound ctx name =
   try Some (ctx_getiscompound' ctx name)
   with Not_found -> None

let ctx_getexpressionable ctx name =
   try Some (ctx_getexpressionable' ctx name)
   with Not_found -> None

let ctx_getlongnamepos ctx name =
   try Some (ctx_getlongnamepos' ctx name)
   with Not_found -> None

let ctx_getshortnamepos ctx name =
   try Some (ctx_getshortnamepos' ctx name)
   with Not_found -> None

let ctx_getsympos ctx name =
   try Some (ctx_getsympos' ctx name)
   with Not_found -> None

let ctx_addtype ctx name pos takeswidth iscompound expressionable =
   ctx.definedat := Types.StringMap.add name pos !(ctx.definedat);
   ctx.takeswidth := Types.StringMap.add name takeswidth !(ctx.takeswidth);
   ctx.iscompound := Types.StringMap.add name iscompound !(ctx.iscompound);
   ctx.expressionable := Types.StringMap.add name expressionable
                                                          !(ctx.expressionable)

let ctx_addlongname ctx name pos =
   ctx.longnamepos := Types.StringMap.add name pos !(ctx.longnamepos)

let ctx_addshortname ctx name pos =
   ctx.shortnamepos := Types.StringMap.add name pos !(ctx.shortnamepos)

let ctx_addsym ctx name pos =
   ctx.sympos := Types.StringMap.add name pos !(ctx.sympos)

let newctx () =
   (*
    * XXX should not duplicate these lists here; there should be one
    * central place that holds them, but the current such (typerep)
    * is downstream of us...
    *)
   let plainbuiltins = ["bool"; "string"] in
   let ewidthbuiltins = ["int"; "uint"] in
   let widthbuiltins = ["ones"; "zeros"] in

   let ctx = {
      definedat = ref Types.StringMap.empty;
      takeswidth = ref Types.StringMap.empty;
      iscompound = ref Types.StringMap.empty;
      expressionable = ref Types.StringMap.empty;
      longnamepos = ref Types.StringMap.empty;
      shortnamepos = ref Types.StringMap.empty;
      sympos = ref Types.StringMap.empty;
   } in

   let addplain name = ctx_addtype ctx name Pos.builtin false false false in
   let addewidth name = ctx_addtype ctx name Pos.builtin true false true in
   let addwidth name = ctx_addtype ctx name Pos.builtin true false false in
   List.iter addplain plainbuiltins;
   List.iter addewidth ewidthbuiltins;
   List.iter addwidth widthbuiltins;
   ctx

(**************************************************************)
(* checks *)

let check'width pos width =
   if width = 0 || width > Types.maxintwidth then begin
      Pos.sayat pos ("Invalid type width " ^ string_of_int width);
      Util.fail ()
   end

(* check if ty can legally appear in an expression-of-T type *)
let check'okexpr ctx ty =
   let check'byname pos name =
      match ctx_getexpressionable ctx name with
           None -> () (* already complained that the type doesn't exist *)
         | Some true -> ()
         | Some false ->
              Pos.sayat pos "Cannot use 'expression' with this type";
              Util.fail ()
   in
   match ty with
	PLAINTYPE (pos, name) ->
	   check'byname pos name
      | WIDTHTYPE (pos, name, _arg) ->
	   check'byname pos name
      | EXPRTYPE (pos, _) ->
	   Pos.sayat pos ("Invalid use of expression type");
	   Util.fail ()

let check'typeref ctx pos name gavewidth =
   match ctx_gettakeswidth ctx name, gavewidth with
        None, _ ->
           Pos.sayat pos ("No such type " ^ name);
           Util.fail ()
      | Some false, true  ->
           Pos.sayat pos ("Type " ^ name ^ " does not take a width");
           Util.fail ()
      | Some true, false  ->
           Pos.sayat pos ("Type " ^ name ^ " needs a width");
           Util.fail ()
      | _, _ -> ()

let rec check'typename ctx ty = match ty with
     PLAINTYPE (pos, name) ->
        check'typeref ctx pos name false
   | WIDTHTYPE (pos, name, width) ->
        check'width pos width;
        check'typeref ctx pos name true
   | EXPRTYPE (_pos, ty') ->
        check'typename ctx ty';
        check'okexpr ctx ty'

let check'longname ctx pos longname =
   match ctx_getlongnamepos ctx longname with
        None ->
           Pos.sayat pos ("No operand tag " ^ longname);
           Util.fail ()
      | Some _ -> ()

(* note: must check'duptype before ctx_addtype to avoid circular types *)
let check'duptype ctx pos name =
   match ctx_getdefinedat ctx name with
        None -> ()
      | Some pos' ->
           Pos.sayat pos ("Duplicate type name " ^ name);
           Pos.sayat pos' ("Previous declaration");
           Util.fail ()

let check'duplongname ctx pos name =
   match ctx_getlongnamepos ctx name with
        None -> ()
      | Some pos' ->
           Pos.sayat pos ("Duplicate operand tag " ^ name);
           Pos.sayat pos' ("Previous declaration");
           Util.fail ()

let check'dupshortname ctx pos name =
   match ctx_getshortnamepos ctx name with
        None -> ()
      | Some pos' ->
           Pos.sayat pos ("Duplicate operand tag shortname " ^ name);
           Pos.sayat pos' ("Previous declaration");
           Util.fail ()

let check'enumerator ctx maxval (pos, name, optval) =
   if name = "_" then ()
   else
   match ctx_getsympos ctx name with
        Some pos' ->
           Pos.sayat pos ("Duplicate symbol name " ^ name);
           Pos.sayat pos' ("Previous declaration");
           Util.fail ()
      | None ->
           ctx_addsym ctx name pos;
           match optval with
                None -> ()
              | Some n -> if n >= maxval then begin
                   Pos.sayat pos ("Enumerator value out of range");
                   Util.fail ()
                end

let check'enumeration ctx pos width members =
   (* XXX should have a syntax for setting this *)
   let complete = false in

   (* XXX the max width should be defined in some config module *)
   let (toowide, width) = if width > 10 then begin
      Pos.sayat pos "Enumeration field too wide; limit is 10";
      Util.fail ();
      (true, 10)
   end
   else (false, width)
   in

   let expectednum = Util.power 2 width in
   let foundnum = List.length members in
   if foundnum > expectednum && not toowide then begin
      Pos.sayat pos ("Too many values for " ^ string_of_int width ^
		     "-bit enumeration: found " ^
			 string_of_int foundnum ^ ", expected at most " ^
			 string_of_int expectednum);
      Util.fail();
   end;

   if complete && foundnum < expectednum then begin
      Pos.sayat pos ("Too few values for complete " ^
		     string_of_int width ^
			  "-bit enumeration: found " ^
			  string_of_int foundnum ^ ", expected exactly " ^
			  string_of_int expectednum);
      Util.fail();
   end;

   (* now bind all the symbols *)
   List.iter (check'enumerator ctx expectednum) members


(*
 * Currently compound type aren't allowed to contain
 * other compound types. There is probably no real
 * need for this restriction and it should be lifted
 * when things have settled some and there's time to
 * think about it/test it. XXX.
 *)
let rec check'okcompound ctx (pos, ty) =
   let check'byname name =
      match ctx_getiscompound ctx name with
	   None -> ()  (* already complained about it not existing *)
	 | Some false -> ()
	 | Some true ->
	      Pos.sayat pos ("This type is not allowed in a compound type");
	      Util.fail ()
   in
   match ty with
        PLAINTYPE (_pos, name) -> check'byname name
      | WIDTHTYPE (_pos, name, _width) -> check'byname name
      | EXPRTYPE (pos, ty') -> check'okcompound ctx (pos, ty')

(*
 * The string for a wraptype must contain exactly one %u and
 * otherwise be an identifer. The %u can't be first, since then
 * the results won't be identifiers.
 *)

let isdigit c =
   (c >= '0' && c <= '9')

let isalpha c =
   (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')

let isalnum c = isalpha c || isdigit c

let check'wrapfmt pos s =
   let state = ref 0 in
   let visit c =
      match !state, c with
           0, _ -> state := if (isalpha c) then 1 else 4
         | 1, '%' -> state := 2
         | 1, _ -> state := if (c = '_' || isalnum c) then 1 else 5
         | 2, 'u' -> state := 3
         | 2, _ -> state := 6
         | 3, '%' -> state := 7
         | 3, _ -> state := if (c = '_' || isalnum c) then 3 else 5
         | _, _ -> ()
   in
   String.iter visit s;
   let msg = match !state with
        0 -> Some "Register names may not be empty"
      | 1 -> Some "Must have exactly one %u to generate register names"
      | 2 -> Some "Must have exactly one %u to generate register names"
      | 3 -> None (* ok *)
      | 4 -> Some "Register names must begin with a letter"
      | 5 -> Some "Register names must be alphanumeric"
      | 6 -> Some "Only %u is permitted for generating register names"
      | 7 -> Some "Must have exactly one %u to generate register names"
      | _ -> assert false
   in
   match msg with
        None -> ()
      | Some s -> Pos.sayat pos s; Util.fail ()

let check'decl ctx d = match d with
     ENUMTYPE (pos, name, width, members) ->
        check'duptype ctx pos name;
        check'width pos width;
        check'enumeration ctx pos width members;
        ctx_addtype ctx name pos false(*takeswidth*) false(*compound*) false
   | WRAPTYPE (pos, name, ty, fmt) ->
        check'duptype ctx pos name;
        check'typename ctx ty;
        check'wrapfmt pos fmt;
        begin
           match ty with
                WIDTHTYPE (_, "uint", _) -> ()
              | _ -> Pos.sayat pos ("Can only wrap sized unsigned integers");
                     Util.fail ()
        end;
        ctx_addtype ctx name pos false(*takeswidth*) false(*compound*) false
   | COMPOUNDTYPE (pos, name, members) ->
        check'duptype ctx pos name;
        List.iter (fun (_, ty) -> check'typename ctx ty) members;
        List.iter (check'okcompound ctx) members;
        ctx_addtype ctx name pos false(*takeswidth*) true(*compound*) false
   | OPERANDTAG (pos, longname, ty) ->
        check'duplongname ctx pos longname;
        check'typename ctx ty;
        ctx_addlongname ctx longname pos
   | SHORTNAME (pos, shortname, longname) ->
        check'dupshortname ctx pos shortname;
        check'longname ctx pos longname;
        ctx_addshortname ctx shortname pos

(**************************************************************)
(* populate enums *)

(*
 * Assign a value to every symbol, and insert _ where the values
 * skip. Don't allow smaller explicit values after larger ones,
 * because that's silly and error-prone.
 *
 * XXX cutpasted from encodingcheck, should be shared.
 *)
let fill_in_enum pos numvals vals =
   (* If we end up with leftovers, whine about the first identifiable one. *)
   let rec complain_leftovers thisval numskipped vals =
      match vals with
           [] ->
              if numskipped == 1 then
		 "Extra _ at end of enumeration"
              else
		 string_of_int numskipped ^ " extra _ at end of enumeration"
         | (_, "_", None) :: more ->
              complain_leftovers (thisval + 1) (numskipped + 1) more
         | (_, sym, None) :: _ ->
              "Symbol " ^ sym ^ " overflows size of enumeration"
         | (_, "_", Some n) :: _ ->
              if n < thisval then
                 "Explicit value " ^ string_of_int n ^ " out of order"
              else
                 "Explicit value " ^ string_of_int n ^
		 " too large for enumeration"
         | (_, sym, Some n) :: _ ->
              if n < thisval then
                 "Explicit value " ^ string_of_int n ^
		 " for symbol " ^ sym ^ " out of order"
              else
                 "Explicit value " ^ string_of_int n ^
		 " for symbol " ^ sym ^ " too large for enumeration"
   in

   let rec dofill thisval vals =
      if thisval = numvals then
         match vals with
              [] -> []
            | _ ->
                 Pos.sayat pos (complain_leftovers thisval 0 vals);
                 Util.fail ();
                 []
      else begin
         assert(thisval < numvals);
         match vals with
              [] ->
                 (pos, "_", Some thisval) :: (dofill (thisval + 1) [])
            | (pos2, sym, None) :: more ->
                 (pos2, sym, Some thisval) :: (dofill (thisval + 1) more)
            | (pos2, sym, Some n) :: more ->
                 if n <= thisval then begin
                    if n < thisval then begin
                       Pos.sayat pos2 ("Explicit value " ^ string_of_int n ^
				       " out of order");
                       Util.fail ();
                    end
                    else ();
                    (pos2, sym, Some thisval) :: (dofill (thisval + 1) more)
                 end
                 else
                    (pos2, "_", Some thisval) :: (dofill (thisval + 1) vals)
      end
   in
   dofill 0 vals

let wrapuint pos width fmt =
   let len = String.length fmt in
   let pct = String.index fmt '%' in
   let prefix = String.sub fmt 0 pct in
   let suffix = String.sub fmt (pct+2) (len - pct - 2) in

   let howmany = Util.power 2 width in
   let members = ref [] in
   for i = 0 to howmany - 1 do
      let s = prefix ^ string_of_int i ^ suffix in
      members := (pos, s, Some i) :: !members
   done;
   List.rev !members

let populate d = match d with
     ENUMTYPE (pos, name, width, members) ->
        let enumsize = Util.power 2 width in
        let members' = fill_in_enum pos enumsize members in
        ENUMTYPE (pos, name, width, members')
   | WRAPTYPE (pos, name, WIDTHTYPE (_pos, "uint", width), fmt) ->
        let members = wrapuint pos width fmt in
        ENUMTYPE (pos, name, width, members)
   | WRAPTYPE _ -> Util.crash "basecheck: populate: bad WRAPTYPE"
   | COMPOUNDTYPE _ -> d
   | OPERANDTAG _ -> d
   | SHORTNAME _ -> d

(**************************************************************)
(* interface *)

let check decls =
   let ctx = newctx () in
   List.iter (check'decl ctx) decls;
   (* don't try to process things that aren't valid *)
   Util.checkfail ();
   let decls = List.map populate decls in
   decls
