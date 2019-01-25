(*
 * Copyright (c) 2016, 2017
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

open Typerep
open Exprrep

(**************************************************************)
(* context *)

(* BEGIN MANDATORY CUTPASTE *)
type callbacks = {
   lookup_aliastype: string -> Typerep.typename option;
   lookup_type: string -> (Pos.pos * bool *
				(Pos.pos * Typerep.typename) list)
			  option;
                   (* (definedat, takeswidth, members) *)
   lookup_var: string -> (Pos.pos * Typerep.typename) option;
                   (* (definedat, type) *)
   lookup_modifier: string -> (Typerep.typename * Typerep.typename) option;
                   (* (argtype, resulttype) *)
}
(* END MANDATORY CUTPASTE *)

type context = {
   callbacks: callbacks ref;
}

let newctx () = {
   callbacks = ref {
      lookup_aliastype = (fun _ -> None);
      lookup_type = (fun _ -> None);
      lookup_var = (fun _ -> None);
      lookup_modifier = (fun _ -> None);
   }
}

let setcallbacks ctx callbacks =
   ctx.callbacks := callbacks

let lookup_aliastype ctx name =
   !(ctx.callbacks).lookup_aliastype name

let lookup_type ctx name =
   !(ctx.callbacks).lookup_type name

let lookup_var ctx name =
   !(ctx.callbacks).lookup_var name

let lookup_modifier ctx name =
   !(ctx.callbacks).lookup_modifier name

(**************************************************************)
(* tools *)

(* XXX: maybe this should just use PLAINTYPE "error"? *)
let failuretype = WIDTHTYPE ("uint", 8)

let typemismatch pos t'stored t'computed what =
   Pos.sayat pos ("Type mismatch in " ^ what ^ ": " ^ dump'typename t'stored ^
	 	  " stored but " ^ dump'typename t'computed ^ " computed");
   Util.fail ()

(**************************************************************)
(* types *)

(*
 * Check a bit width.
 *)
let checkwidth pos n =
   if n >= Types.maxintwidth then begin
      Pos.sayat pos ("Type width " ^ string_of_int n ^ " exceeds maximum " ^
                     string_of_int Types.maxintwidth);
      Util.fail ()
   end
   else if n <= 0 then begin
      Pos.sayat pos ("Field width " ^ string_of_int n ^
		     " must be at least 1");
      Util.fail ()
   end
   else ()

(*
 * Check a typename (use of a type)
 *
 * 1. The name must exist. Note that enum names have their own
 *    namespace, and we can just look them up in the spec, but
 *    PLAINTYPEs and WIDTHTYPEs share the namespace of other (normal)
 *    types. Since those have several sources, we need to collect
 *    them in the context.
 *
 * 2. The usage (PLAINTYPE vs. WIDTHTYPE vs. whatever) must match
 *    the prior declaration.
 *
 * 3. TMPTYPE is not allowed; typeinf is not supposed to leave those
 *    behind.
 *
 *)
let rec check'typename ctx pos ty =
   match ty with
        PLAINTYPE name -> begin
           begin
	   match lookup_aliastype ctx name with
                None -> ()
              | Some _ ->
                   Pos.sayat pos ("Unexpected alias type " ^ name);
                   Util.fail ()
           end;
	   match lookup_type ctx name with
                None ->
                   Pos.sayat pos ("Unknown type " ^ name);
                   Util.fail ()
               | Some (_defpos, takeswidth, _typeargs) ->
                   if takeswidth then begin
                      Pos.sayat pos ("Type " ^ name ^ " requires a width");
                      Util.fail ()
                   end
(* is any logic needed here?
           match stringmap_get name ctx.spec.enums with
                None -> ()
              | Some _e -> ()
*)
        end
      | WIDTHTYPE (name, width) -> begin
           checkwidth pos width;
	   match lookup_type ctx name with
                None ->
                   Pos.sayat pos ("Unknown type " ^ name);
                   Util.fail ()
               | Some (_defpos, takeswidth, _typeargs) ->
                   if not takeswidth then begin
                      Pos.sayat pos ("Type " ^ name ^ " does not take a " ^
				     "width argument");
                      Util.fail ()
                   end
        end
      | EXPRTYPE t ->
	   (*
            * XXX should check if t is an allowed value type... which is not
            * the same as whether t is an allowed field type (e.g.
            * fields can't be bool but we can presumably have
            * expressions producing bool (although maybe this should
            * be reviewed... maybe not?)
            *)
           check'typename ctx pos t
      | LISTTYPE t ->
           check'typename ctx pos t
      | TMPTYPE n ->
           Pos.crashat pos ("Unexpected temporary type " ^ string_of_int n)

let rec check'typename'aliasok ctx pos ty =
   match ty with
        PLAINTYPE name -> begin
           (* all alias types are PLAINTYPEs because they're just names *)
           match lookup_aliastype ctx name with
                Some ty' -> check'typename'aliasok ctx pos ty'
              | None -> check'typename ctx pos ty
        end
      | _ -> check'typename ctx pos ty

(**************************************************************)
(* operators *)

(*
 * operators
 *)

(* Because these operators are all syntax, wrong arity => bugs upstream *)
let require_nary n pos tys what =
   let n' = List.length tys in
   if n' <> n then
      Pos.crashat pos ("Wrong number of arguments for operator " ^ what ^
		       ": found " ^ string_of_int n' ^ " but should be " ^
		       string_of_int n)
let require_unary (* pos tys what *) = require_nary 1
let require_binary (* pos tys what *) = require_nary 2

let require_numbers pos tys what =
   let req (n, t) = match t with
        WIDTHTYPE ("int", _) -> ()
      | WIDTHTYPE ("uint", _) -> ()
      | _ ->
           Pos.sayat pos ("Bad argument " ^ string_of_int (n + 1) ^
			  " for operator " ^ what ^ ": found " ^
			  dump'typename t ^
			  "; expected a number");
           Util.fail ()
   in
   List.iter req (Util.number tys)

let require_strings pos tys what =
   let req (n, t) = match t with
        PLAINTYPE "string" -> ()
      | _ ->
           Pos.sayat pos ("Bad argument " ^ string_of_int (n + 1) ^
			  " for operator " ^ what ^ ": found " ^
			  dump'typename t ^
			  "; expected string");
           Util.fail ()
   in
   List.iter req (Util.number tys)

let require_bools pos tys what =
   let req (n, t) = match t with
        PLAINTYPE "bool" -> ()
      | _ ->
           Pos.sayat pos ("Bad argument " ^ string_of_int (n + 1) ^
			  " for operator " ^ what ^ ": found " ^
                          dump'typename t ^
			  "; expected bool");
           Util.fail ()
   in
   List.iter req (Util.number tys)

let require_enums ctx pos tys what =
   let req z (n, t) =
      let bad () =
         Pos.sayat pos ("Bad argument " ^ string_of_int (n + 1) ^
		        " for operator " ^ what ^ ": found " ^
                        dump'typename t ^
		        "; expected enumeration");
         Util.fail ()
      in
      match t with
           PLAINTYPE name -> begin
              match lookup_type ctx name with
                   None ->
                      Pos.sayat pos ("Unknown type " ^ name);
                      Util.fail ();
                      z
                  | Some (_defpos, true (*takeswidth*), _typeargs) -> bad (); z
                  | Some (_defpos, false (*takeswidth*), _ :: _) -> bad (); z
                  | Some (_defpos, false (*takeswidth*), []) ->
                      (*
                       * XXX we can't check if it's really an enumeration,
                       * or get the width; need to improve the interface.
                       *)
                      let w = 8 in
                      max z w
           end
         | WIDTHTYPE ("uint", w) ->
              (* must have this so it works after numerate *)
              max z w
         | _ -> bad (); z
   in
   List.fold_left req 0 (Util.number tys)

let require_exprs fsub pos tys what =
   let req (n, t) = match t with
        EXPRTYPE t' -> fsub pos [t'] what
      | _ ->
           Pos.sayat pos ("Bad argument " ^ string_of_int (n + 1) ^
			  " for operator " ^ what ^ ": found " ^
                          dump'typename t ^
			  "; expected expression");
           Util.fail ()
   in
   List.iter req (Util.number tys)

let rec is_expr ctx ty = match ty with
      PLAINTYPE name -> begin
         match lookup_aliastype ctx name with
              Some aty -> is_expr ctx aty
            | None -> false
      end
    | EXPRTYPE _ -> true
    | _ -> false

let is_exprs ctx tys =
   List.for_all (is_expr ctx) tys

let check'op'eq pos ty'stored ty'args =
   require_binary pos ty'args "==";
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype "result of =="
   ;
   match ty'args with
        WIDTHTYPE ("zeros", _) :: _ ->
           Pos.sayat pos ("Warning: fields of type zeros are always equal")
      | WIDTHTYPE ("ones", _) :: _ ->
           Pos.sayat pos ("Warning: fields of type ones are always equal")
      | _ -> ()

let check'op'in pos ty'stored ty'args =
   require_binary pos ty'args "in";
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype "result of =="

let check'op'lt pos ty'stored ty'args =
   let opstr = "<, >, <=, or <=" in
   require_binary pos ty'args opstr;
   require_numbers pos ty'args opstr;
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype ("result of " ^ opstr)
   ;
   match ty'args with
        WIDTHTYPE ("zeros", _) :: _ ->
           Pos.sayat pos ("Warning: fields of type zeros are always equal")
      | WIDTHTYPE ("ones", _) :: _ ->
           Pos.sayat pos ("Warning: fields of type ones are always equal")
      | _ -> ()

let check'op'string opstr pos ty'stored ty'args =
   require_binary pos ty'args opstr;
   begin
      require_strings pos ty'args opstr;
      match ty'args with
	   resulttype :: _ ->
	      if ty'stored <> resulttype then
		 typemismatch pos ty'stored resulttype ("result of " ^ opstr)
	 | _ -> ()
   end

let check'op'arith ctx opstr pos ty'stored ty'args =
   require_binary pos ty'args opstr;
   if is_exprs ctx ty'args then begin
      (* XXX should check that ty'args are expressions of the same type *)
      match ty'args with
	   resulttype :: _ ->
	      if ty'stored <> resulttype then
		 typemismatch pos ty'stored resulttype ("result of " ^ opstr)
	 | _ -> ()
   end
   else begin
      require_numbers pos ty'args opstr;
      match ty'args with
	   resulttype :: _ ->
	      if ty'stored <> resulttype then
		 typemismatch pos ty'stored resulttype ("result of " ^ opstr)
	 | _ -> ()
   end

let check'op'logic opstr pos ty'stored ty'args =
   require_binary pos ty'args opstr;
   require_bools pos ty'args opstr;
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype ("result of " ^ opstr)

let check'op'shift opstr pos ty'stored ty'args =
   require_binary pos ty'args opstr;
   match ty'args with
        [ty'val; ty'shift] -> begin
           require_numbers pos [ty'val] opstr;
           if ty'stored <> ty'val then
              typemismatch pos ty'stored ty'val ("result of " ^ opstr)
           ;
           match ty'shift with
                (* XXX...? *)
                WIDTHTYPE ("uint", _) -> ()
              | _ ->
                   Pos.sayat pos ("Type mismatch in argument 2 of " ^ opstr ^
				  ": should be shiftcount but " ^
				  dump'typename ty'shift ^ " computed");
                   Util.fail ()
        end
      | _ -> Util.crash "check'op'shift: not binary"

let check'op'neg pos ty'stored ty'args =
   let opstr = "unary -" in
   require_unary pos ty'args opstr;
   require_numbers pos ty'args opstr;
   match ty'args with
        resulttype :: _ ->
           if ty'stored <> resulttype then
              typemismatch pos ty'stored resulttype ("result of " ^ opstr)
      | _ -> ()

let check'op'bitnot pos ty'stored ty'args =
   require_unary pos ty'args "~";
   require_numbers pos ty'args "~";
   match ty'args with
        resulttype :: _ ->
           if ty'stored <> resulttype then
              typemismatch pos ty'stored resulttype ("result of ~")
      | _ -> ()

let check'op'lognot pos ty'stored ty'args =
   require_unary pos ty'args "!";
   require_bools pos ty'args "!";
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype "result of !"

let check'op'constp pos ty'stored ty'args =
   require_unary pos ty'args "constantp";
   require_exprs require_numbers pos ty'args "constantp";
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype "result of constantp"

let check'op'definedp pos ty'stored ty'args =
   require_unary pos ty'args "definedp";
   require_exprs require_numbers pos ty'args "definedp";
   if ty'stored <> booltype then
      typemismatch pos ty'stored booltype "result of definedp"

let check'op'ord ctx pos ty'stored ty'args =
   require_unary pos ty'args "ord";
   let wreq = require_enums ctx pos ty'args "ord" in
   let w = match ty'stored with
        WIDTHTYPE ("uint", w) -> w
      | _ -> wreq - 1
   in
   (* XXX should really require exact match *)
   if w < wreq then
      typemismatch pos ty'stored (WIDTHTYPE ("uint", wreq)) "result of ord"

let check'op ctx op (* pos ty'stored ty'args *) =
   match op with
        EQ -> check'op'eq
      | IN -> check'op'in
      | LT -> check'op'lt
      | STRCAT -> check'op'string "++"
      | ADD -> check'op'arith ctx "+"
      | SUB -> check'op'arith ctx "-"
      | MUL -> check'op'arith ctx "*"
      | DIV -> check'op'arith ctx "/"
      | MOD -> check'op'arith ctx "%"
      | NEG -> check'op'neg
      | SHL -> check'op'shift "<<"
      | SHR -> check'op'shift ">>"
      | BITAND -> check'op'arith ctx "&"
      | BITOR -> check'op'arith ctx "|"
      | BITXOR -> check'op'arith ctx "^"
      | BITNOT -> check'op'bitnot
      | LOGAND -> check'op'logic "&&"
      | LOGOR -> check'op'logic "||"
      | LOGXOR -> check'op'logic "^^"
      | LOGNOT -> check'op'lognot
      | CONSTP -> check'op'constp
      | DEFINEDP -> check'op'definedp
      | ORD -> check'op'ord ctx

(**************************************************************)
(* expressions *)

(*
 * expressions
 *)

let string_of_const k = match k with
     SMALL k' -> string_of_int k'
   | LARGE k' -> Types.Wide.to_string k'

let fitsint bits n =
   if bits > 30 then
      Util.crash ("typecheck: fitsint: too wide: " ^ string_of_int bits)
   else if n < 0 then
      Util.crash ("typecheck: fitsint: negative value " ^ string_of_int n)
   else
      n < Util.power 2 bits

let fitswide bits n =
   if Types.Wide.isneg n then
      Util.crash "typecheck: fitswide: negative"
   else
      Types.Wide.lt n (Types.Wide.twoN bits)

let rec check_cast pos nty oty =
   match nty, oty with
        WIDTHTYPE ("int", _), WIDTHTYPE ("int", _) -> ()
      | WIDTHTYPE ("uint", _), WIDTHTYPE ("uint", _) -> ()
      | WIDTHTYPE ("int", w2), WIDTHTYPE ("uint", w1) ->
           if w1 <> w2 then begin
              Pos.sayat pos ("Cast changes both width and signedness");
              Util.fail ()
           end
      | WIDTHTYPE ("uint", w2), WIDTHTYPE ("int", w1) ->
           if w1 <> w2 then begin
              Pos.sayat pos ("Cast changes both width and signedness");
              Util.fail ()
           end
      | WIDTHTYPE ("zeros", _), WIDTHTYPE ("zeros", _) -> ()
      | WIDTHTYPE ("ones", w1), WIDTHTYPE ("ones", w2) ->
           if w1 <> w2 then begin
              Pos.sayat pos ("Cast changes width of 'ones'");
              Util.fail ()
           end
        (* allow ones/zeros to uint but not back *)
      | WIDTHTYPE ("uint", _), WIDTHTYPE ("zeros", _) -> ()
      | WIDTHTYPE ("uint", w1), WIDTHTYPE ("ones", w2) ->
           if w1 <> w2 then begin
              Pos.sayat pos ("Cast changes width of 'ones'");
              Util.fail ()
           end
        (* XXX: do we want to allow this? *)
      | EXPRTYPE nty', EXPRTYPE oty' -> check_cast pos nty' oty'
      | _, _ ->
           Pos.sayat pos ("Illegal type conversion");
           Util.fail ()

let rec check'expr ctx e =
   match e with
      CONST (pos, ty, c) -> begin
         check'typename ctx pos ty;
         let ok = match ty, c with
              PLAINTYPE "bool", k -> begin
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
                          " has boolean type");
                 Util.fail ();
                 true (* already issued a message *)
              end
            | PLAINTYPE name, k -> begin
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
                          " has type " ^ name);
                 Util.fail ();
                 true (* already issued a message *)
              end
            | WIDTHTYPE ("int", bits), SMALL k ->
                 if k < 0 then fitsint (bits - 1) (-(k+1))
                 else fitsint (bits - 1) k
            | WIDTHTYPE ("int", bits), LARGE k ->
                 if Types.Wide.isneg k then
                    let k' = Types.Wide.neg (Types.Wide.inc k) in
                    fitswide (bits - 1) k'
                 else fitswide (bits - 1) k
            | WIDTHTYPE ("uint", bits), SMALL k ->
                 fitsint bits k
            | WIDTHTYPE ("uint", bits), LARGE k ->
                 fitswide bits k
            | WIDTHTYPE ("zeros", _bits), SMALL k ->
                 k = 0
            | WIDTHTYPE ("zeros", _bits), LARGE k ->
                 Types.Wide.eqint k 0
            | WIDTHTYPE ("ones", bits), SMALL k ->
                 k = Util.ones bits
            | WIDTHTYPE ("ones", bits), LARGE k ->
                 Types.Wide.eq k (Types.Wide.ones bits)
            | WIDTHTYPE (name, arg), k -> begin
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
                          " has type " ^ name ^ "(" ^ string_of_int arg ^ ")");
                 Util.fail ();
                 true (* already issued a message *)
              end
            | EXPRTYPE _, k -> begin
		 (* XXX should we allow this? *)
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
                          " has expression type");
                 Util.fail ();
                 true (* already issued a message *)
              end
            | LISTTYPE _, k -> begin
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
                          " has list type");
                 Util.fail ();
                 true (* already issued a message *)
              end
            | TMPTYPE _, k ->
                 Pos.sayat pos ("Integer constant " ^ string_of_const k ^
			  " has no type");
                 Util.fail ();
                 true (* already issued a message *)
         in
         if not ok then begin
            Pos.sayat pos ("Integer constant " ^ string_of_const c ^
                     " is too large for its type " ^ dump'typename ty);
            Util.fail ()
         end
         else ();
         ty
      end
    | STRCONST (pos, ty'stored, _s) -> begin
         let ty = PLAINTYPE "string" in
         check'typename ctx pos ty'stored;
         if ty'stored <> ty then
            typemismatch pos ty'stored ty "string literal"
         ;
         ty'stored
      end
    | USEVAR (pos, ty'stored, name) -> begin
         check'typename ctx pos ty'stored;
         match lookup_var ctx name with
              None ->
                 Pos.sayat pos ("Unbound variable " ^ name ^ " in expression");
                 Util.fail ();
                 ty'stored
            | Some (_defpos, ty) ->
                 if ty <> ty'stored then
                    typemismatch pos ty'stored ty ("use of " ^ name)
                 ;
                 ty'stored
      end
    | USEFIELD (pos, ty'stored, e1, name) ->
         check'typename ctx pos ty'stored;
         let ty'e1 = check'expr ctx e1 in
         (* XXX get the type of the field name in type ty'e1 *)
         (* (can't do this yet) *)
         let _ = (ty'e1, name) in
         let ty'name = PLAINTYPE "wrong" in
         if ty'stored <> ty'name then
            typemismatch pos ty'stored ty'name
               ("use of field " ^ name ^ " of type " ^ dump'typename ty'e1)
         ;
         ty'stored
    | OP (pos, ty'stored, op, es) -> begin
         check'typename ctx pos ty'stored;
         (*
          * XXX if op is a shift, and the shift count is a constant,
          * should check that it's in range. I wonder if shift ought
          * to be a separate branch of expression to make that easier.
          *)
         let ty'es = List.map (check'expr ctx) es in
         check'op ctx op pos ty'stored ty'es;
         ty'stored
      end
    | FITS (pos, ty'stored, e1, argty) -> begin
         check'typename ctx pos ty'stored;
         let ty'e1 = check'expr ctx e1 in
         check'typename ctx pos argty;
         if ty'stored <> booltype then
            typemismatch pos ty'stored booltype ("result of fits")
         ;
         let rec chkfits t1 t2 = match t1, t2 with
              WIDTHTYPE ("int", w1), WIDTHTYPE ("int", w2)
            | WIDTHTYPE ("uint", w1), WIDTHTYPE ("uint", w2)
            | WIDTHTYPE ("zeros", w1), WIDTHTYPE ("uint", w2)
            | WIDTHTYPE ("ones", w1), WIDTHTYPE ("uint", w2) ->
                 if w1 <= w2 then
                    Pos.sayat pos ("Warning: 'fits' a wider type is always true")
                 ;
                 if w2 <= 0 || t2 = WIDTHTYPE ("int", 1) then begin
                    Pos.sayat pos ("Invalid width to fit into");
                    Util.fail ()
                 end
            | WIDTHTYPE ("int", _), WIDTHTYPE ("uint", _)
            | WIDTHTYPE ("uint", _), WIDTHTYPE ("int", _) ->
                 Pos.sayat pos ("Signedness mismatch in 'fits'");
                 Util.fail ()
            | EXPRTYPE t1', EXPRTYPE t2' ->
                 chkfits t1' t2'
            | _, _ ->
                 Pos.sayat pos ("Invalid types for 'fits'");
                 Util.fail ()
          in
          chkfits ty'e1 argty;
          ty'stored
      end
    | MODE (_pos, _modename) -> begin
         (* XXX should check modename against the list of existing modes *)
         PLAINTYPE "bool"
      end
    | LIST (pos, ty'stored, elems) -> begin
         check'typename ctx pos ty'stored;
         let ty'stored'elem = match ty'stored with
              LISTTYPE t -> t
              (* wtf? *)
            | _ -> Pos.crashat pos "typecheck: list didn't have list type"
         in
         let ty'elems = List.map (check'expr ctx) elems in
         match ty'elems with
              [] -> ty'stored
            | ty'first :: more ->
                 let checkone (i, ty'm) =
                    if ty'first <> ty'm then begin
		       Pos.sayat pos ("List expression does not have " ^
				      "uniform type; first element has type " ^
				      dump'typename ty'first ^
                                      " but element " ^
				      string_of_int (i + 2) ^ " has type " ^
				      dump'typename ty'm);
		       Util.fail ()
		    end;
                 in
                 List.iter checkone (Util.number more);
                 if ty'stored'elem <> ty'first then
                    typemismatch pos ty'stored'elem ty'first "elements of list"
		 ;
                 ty'stored
      end
    | MODIFIER (pos, ty'stored, modname, elems) -> begin
         check'typename ctx pos ty'stored;
         let ty'elems = List.map (check'expr ctx) elems in

         (* XXX rearranging this logic will make it a lot tidier *)

         let (argty, ty) = match lookup_modifier ctx modname with
              Some q -> q
            | None ->
               Pos.sayat pos ("Unknown modifier " ^ modname);
               Util.fail ();
               (failuretype, failuretype)
         in
         begin
         match ty'elems with
              [ty'elem] ->
                 if ty'elem <> argty then
                    typemismatch pos argty ty'elem
                                 ("arguments for modifier " ^ modname)
            | _ ->
                 Pos.sayat pos ("Wrong arguments for modifier %hi");
                 Util.fail ()
         end;
         if ty'stored <> ty then begin
            typemismatch pos ty'stored ty "modifier invocation"
         end;
         ty'stored
      end
    | PACK (pos, ty'stored, ctor, args) -> begin
         check'typename ctx pos ty'stored;
         let ty'args = List.map (check'expr ctx) args in
         begin
         match lookup_type ctx ctor with
              None ->
                 Pos.sayat pos ("No such compound type " ^ ctor);
                 Util.fail ();
            | Some (_defpos, _takeswidth, []) ->
                 Pos.sayat pos ("Type " ^ ctor ^ " is not packable");
                 Util.fail ();
            | Some (defpos, _haswidth, argtypes) ->
                 let n'expected = List.length argtypes in
                 let n'found = List.length ty'args in
                 if n'expected <> n'found then begin
                    Pos.sayat pos ("Wrong number of elements packing type " ^
                                   ctor ^ ": found " ^ string_of_int n'found ^
                                   " but expected " ^
				   string_of_int n'expected);
                    Pos.sayat defpos ("Type declaration");
                    Util.fail ();
                 end;
                 let checkarg (n, ((_pos, t'exp), t'found)) =
                    if t'exp <> t'found then
                       typemismatch pos t'exp t'found ("argument " ^
						       string_of_int (n+1) ^
						       " packing " ^ ctor)
                 in
                 List.iter checkarg (Util.number (Util.zip' argtypes ty'args));
         end;
         let ty = PLAINTYPE ctor in
         if ty'stored <> ty then
            typemismatch pos ty'stored ty ("result of packing " ^ ctor)
         ;
         ty
      end
    | CAST (pos, nty, oty, e1) -> begin
         check'typename ctx pos oty;
         check'typename ctx pos nty;
         let ty'e1 = check'expr ctx e1 in
         if oty <> ty'e1 then begin
            Pos.sayat pos ("Type mismatch in argument of cast: type " ^
			   dump'typename oty ^ " expected but type " ^
			   dump'typename ty'e1 ^ " computed");
            Util.fail ()
         end;
         check_cast pos nty oty;
         nty
      end
    | EVAL (pos, nty, _relname, _reloffset, oty, e1) -> begin
         check'typename ctx pos oty;
         check'typename ctx pos nty;
         let ty'e1 = check'expr ctx e1 in
         if oty <> ty'e1 then begin
            Pos.sayat pos ("Type mismatch in argument of eval: type " ^
			   dump'typename oty ^ " expected but type " ^
			   dump'typename ty'e1 ^ " computed");
            Util.fail ()
         end;
         begin
         match (match oty with
              EXPRTYPE t -> Some t
            | _ -> None
         ) with
              None ->
                 Pos.sayat pos ("Invalid type " ^ dump'typename oty ^ " for eval");
                 Util.fail ()
            | Some ety ->
                 if ety <> nty then begin
                    Pos.sayat pos ("Type mismatch in result of eval: type " ^
			           dump'typename nty ^ " expected but type " ^
			           dump'typename ety ^ " computed");
                    Util.fail ()
                 end
         end;
         nty
      end
    | UNEVAL (pos, ty, e1) -> begin
         check'typename ctx pos ty;
         let ty'e1 = check'expr ctx e1 in

         (* XXX this is a mess *)

         begin
         match (match ty with
              EXPRTYPE t -> Some t
            | _ -> None
         ) with
              None ->
                 Pos.sayat pos ("Invalid type " ^ dump'typename ty ^ " for uneval");
                 Util.fail ()
            | Some ety ->
                 if ety <> ty'e1 then begin
                    Pos.sayat pos ("Type mismatch in argument of uneval: type " ^
			           dump'typename ety ^ " expected but type " ^
			           dump'typename ty'e1 ^ " computed");
                    Util.fail ()
                 end
         end;
         ty
      end   
    | ANNOTATE (pos, ty, e1) -> begin
         check'typename ctx pos ty;
         let ty'e1 = check'expr ctx e1 in
         if ty <> ty'e1 then begin
            Pos.sayat pos ("Type mismatch at explicit type annotation: type " ^
			   dump'typename ty ^ " was specified but type " ^
			   dump'typename ty'e1 ^ " computed");
            Util.fail ()
         end;
         ty
      end
    | COMMENTED (_text, e1) ->
         check'expr ctx e1
