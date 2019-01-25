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

(*
 * Preliminary local checks/fixups on Encodingtree, the encoding.def
 * parse tree.
 *
 * Things this does:
 *    - enforces complete ENUMTYPEs
 *    - pads out non-complete ENUMTYPEs
 *    - rejects ENUMTYPEs with too many/out of range values
 *    - requires that FIELDREF refer to a declared field
 *    - rejects misplaced statements
 *    - rejects duplicate field names
 *    - [rejects duplicate encoding/macro names] [DOES NOT!]
 *    - requires that USE refer to a defined encoding or macro
 *      (modulo types that haven't been checked yet)
 *    - requires that SUBENUMs use defined constants from a single enum
 *    - rejects _ in SUBENUMs
 *    - requires that every encoding assign all fields of its form
 *    - warns about unused assignments
 *    - warns about assignments to fields not present in the current form
 *    - [rejects recursive USEs] [DOES NOT!]
 *
 *    - resolves the values of enumerated constants
 *    - resolves SUBENUMEXPRs
 *    - removes NEQ, NOTIN, and LTEQ by wrapping in NOT
 *    - removes unary plus
 *
 * Note that there are three namespaces:
 *    - types (field types)
 *    - variables/values, including enumeration constants, field
 *      names, subenum names, encoding/macro arguments, and operand
 *      names
 *    - encoding/macro names
 *
 * Type names aren't checked/enforced in this module. encoding.def
 * doesn't allow declaring new type names, and the existing ones are
 * partly from other files, so they aren't known at this point. They
 * all have global scope.
 *
 * Variable/value names come only from this file (and don't escape it)
 * and must be unique up to scoping. Each block is a scope. Assignment
 * can bind new variables, but assignment to an existing variable
 * updates it. Field names are bound as variables when a form is
 * declared.
 *
 * (Update on that: enumeration constants, field names, and subenum
 * names are now exported/exposed to hazmachine.)
 *
 * Encoding and macro names must be unique when combined with the
 * operand signature. They all have global scope regardless of where
 * they're defined. Since we haven't done type inference yet in this
 * module, we don't check this.
 *
 * Things we don't do yet (that'll want a solver):
 *    - make sure that for every use using something with a guard
 *      expression, conditions in the macro with the use imply the
 *      guard expression so the use is valid.
 *)

open Encodingtree

(**************************************************************)
(* scope *)

type 't scope = {
   parent: 't scope option;
   names: 't Types.StringMap.t ref;
}

let newscope () = {
   parent = None;
   names = ref Types.StringMap.empty;
}

let scope_bind name x scope =
   scope.names := Types.StringMap.add name x !(scope.names)

let rec scope_isbound name scope =
   match Types.StringMap.mem name !(scope.names), scope.parent with
        true, _ -> true
      | false, Some p -> scope_isbound name p
      | false, None -> false

let scope_get_bot name scope =
   try
      Some (Types.StringMap.find name !(scope.names))
   with Not_found ->
      None

let rec scope_get name scope =
   try
      Some (Types.StringMap.find name !(scope.names))
   with Not_found ->
      match scope.parent with
           None -> None
         | Some p -> scope_get name p

let scope_iter_bot f scope =
   Types.StringMap.iter f !(scope.names)

(*
 * Go through the scope calling f, but only call f for the visible
 * (innermost) binding of any given name. This requires remembering
 * what we've seen as we go up.
 *)
let scope_iter f scope =
   let seen = ref Types.StringSet.empty in
   let f' name x =
      if Types.StringSet.mem name !seen then ()
      else begin
         seen := Types.StringSet.add name !seen;
         f name x
      end
   in
   let rec scope_iter' scope =
      scope_iter_bot f' scope;
      match scope.parent with
           None -> ()
         | Some p -> scope_iter' p
   in
   scope_iter' scope

let scope_push scoperef =
   scoperef := { parent = Some !scoperef; names = ref Types.StringMap.empty; }

let scope_pop scoperef =
   scoperef := match (!scoperef).parent with
        Some s -> s
      | None -> Util.crash "encodingcheck: scope_pop: unbalanced pop"

(**************************************************************)
(* instruction signature *)

(* note this only goes by number of arguments/operands, not the types *)
type insnsig = INSNSIG of string * int * int

module Insnsig = struct
   type t = insnsig
   let compare = Pervasives.compare
end
module InsnsigMap = Map.Make(Insnsig)

(**************************************************************)
(* context *)

type ctx = {
   (* all variable/value names in scope; holds location where bound *)
   vars: Pos.pos scope ref;

   (* all field names in file; holds location where bound *)
   fields: Pos.pos scope;

   (* next key for ->enums *)
   nextenum: int ref;

   (* all enumerations in file; holds the symbol/value list *)
   enums: (Pos.pos * string * int option) list Types.IntMap.t ref;

   (* all enumerations in file; holds the serial number to index ->enums *)
   enumfieldnames: int Types.StringMap.t ref;

   (* all enumeration constants in file; holds enum serial number *)
   enumerators: int scope;

   (* all subenums in file; holds serial number of enum they're from *)
   subenums: int scope;

   (* all instruction signatures in file; holds location where defined *)
   insns: Pos.pos InsnsigMap.t ref;   

   (* all USE instances in file *)
   (*uses: (Pos.pos * string * int * int) list ref;*)

   (* all variables (only, includes fields in current form) in scope *)
   varsused: bool scope ref;

   (* fields in the current form *)
   fieldsassigned: bool scope ref;

   (* single flag *)
   formused: bool ref;

   (* signature of current macro being defined *)
   curmacro: insn option ref;
}

let newctx () = {
   vars = ref (newscope ());
   fields = newscope ();
   nextenum = ref 0;
   enums = ref Types.IntMap.empty;
   enumfieldnames = ref Types.StringMap.empty;
   enumerators = newscope ();
   subenums = newscope ();
   insns = ref InsnsigMap.empty;
   (*uses = ref [];*)
   varsused = ref (newscope ());
   fieldsassigned = ref (newscope ());
   formused = ref false;
   curmacro = ref None;
}

let ctx_addenum ctx fieldname vals =
   let whichenum = !(ctx.nextenum) in
   ctx.nextenum := whichenum + 1;
   ctx.enums := Types.IntMap.add whichenum vals !(ctx.enums);
   ctx.enumfieldnames := Types.StringMap.add fieldname whichenum
                                                         !(ctx.enumfieldnames);
   whichenum

let ctx_getenumbyfield ctx name =
   try
      Some (Types.StringMap.find name !(ctx.enumfieldnames))
   with Not_found -> None

let ctx_getenumbynum ctx num =
   try
      Some (Types.IntMap.find num !(ctx.enums))
   with Not_found -> None

let ctx_addinsn ctx (INSN (pos, name, args, ops)) =
   let numargs = List.length args in
   let numops = List.length ops in
   let isig = INSNSIG (name, numargs, numops) in
   (* do not check for duplicates yet as they might differ by type *)
   ctx.insns := InsnsigMap.add isig pos !(ctx.insns)

(*
let ctx_getinsn ctx name numargs numops =
   let isig = INSNSIG (name, numargs, numops) in
   try
      Some (InsnsigMap.find isig !(ctx.insns))
   with Not_found -> None

let ctx_adduse ctx pos name numargs numops =
   let use = (pos, name, numargs, numops) in
   ctx.uses := use :: !(ctx.uses)
*)

let ctx_pushscope ctx doused =
   scope_push ctx.vars;
   scope_push ctx.fieldsassigned;
   if doused then scope_push ctx.varsused
   else ()

let ctx_popscope ctx doused =
   if doused then scope_pop ctx.varsused
   else ();
   scope_pop ctx.fieldsassigned;
   scope_pop ctx.vars

(**************************************************************)
(* debug widgets *)

(*
let dumpmap dumpval m =
   let dumpname name x =
      prerr_string (name ^ " = " ^ dumpval x);
      prerr_newline ()
   in
   Types.StringMap.iter dumpname m
*)

(*
let dumpscope dumpval s =
   let dumpname name x =
      prerr_string (name ^ " = " ^ dumpval x);
      prerr_newline ()
   in
   let rec dumpscope' { parent; names; } = 
      Types.StringMap.iter dumpname !names;
      match parent with
           None -> ()
         | Some p ->
              prerr_string "----";
              prerr_newline ();
              dumpscope' p
   in
   prerr_string "Scope:";
   prerr_newline ();
   dumpscope' s;
   prerr_string "End scope.";
   prerr_newline ()
*)

(**************************************************************)
(* support logic for enums *)

(*
 * Assign a value to every symbol, and insert _ where the values
 * skip. Don't allow smaller explicit values after larger ones,
 * because that's silly and error-prone.
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

(*
 * Enter an enum value into the symbol table.
 *)
let bind_enumerator ctx whichenum (pos2, name, optval) =
   match optval with
        None -> Pos.crashat pos2 ("encodingcheck: No value for " ^ name)
      | Some _ ->
           match name with
                "_" -> ()
              | _ ->
                   if scope_isbound name ctx.enumerators then begin
                      Pos.sayat pos2 ("Duplicate enumerator " ^ name);
                      Util.fail ()
                   end;
                   scope_bind name pos2 !(ctx.vars);
                   scope_bind name whichenum ctx.enumerators

(**************************************************************)
(* subenum expressions *)

(*
 * A subenum expression may use the operators | (union), & (intersection),
 * - (set difference), and ~ (set complement). It may also contain
 * lists of enumeration constants.
 *
 * The variable names it refers to must be either subenums or field
 * names with enum type.
 *
 * Everything must come from a single base enum type.
 *)

(*
 * Figure out which enum a subenumexpr is from. Returns the number
 * it was assigned when its field was declared, or None if there isn't
 * one. Rejects invalid expressions.
 *)
let rec validate_subenumexpr ctx e : int option =
   let merge pos n1 n2 = match n1, n2 with
        None, _ -> None
      | _, None -> None
      | Some n1', Some n2' ->
           if n1' = n2' then Some n1'
           else begin
              Pos.sayat pos ("Subenum is not composed of values from " ^
			     "a single enumeration");
              Util.fail ();
              None
           end
   in
   let rec mergeall pos ns = match ns with
        [] -> Util.crash "validate_subenumexpr: empty mergeall"
      | n :: [] -> n
      | n :: more -> merge pos n (mergeall pos more)
   in

   match e with
        UOP (pos, op, e1) ->
           let _ = match op with
                BITNOT -> ()
              | _ ->
                   Pos.sayat pos ("Invalid set operator");
                   Util.fail ()
           in
           validate_subenumexpr ctx e1
      | BOP (pos, e1, op, e2) ->
           let _ = match op with
                BITOR -> ()
              | BITAND -> ()
              | SUB -> ()
              | _ ->
                   Pos.sayat pos ("Invalid set operator");
                   Util.fail ()
           in
           let n1 = validate_subenumexpr ctx e1 in
           let n2 = validate_subenumexpr ctx e2 in
           merge pos n1 n2
      | FITS (pos, _e, _ty) ->
           Pos.sayat pos ("Invalid set operator");
           Util.fail ();
           None
      | MODE (pos, _name) ->
           Pos.sayat pos ("Invalid set operator");
           Util.fail ();
           None
      | READVAR (pos, "_") ->
           Pos.sayat pos ("Illegal use of _ wildcard name");
           Util.fail ();
           None
      | READVAR (pos, name) -> begin
           match scope_get name ctx.enumerators with
                Some n -> Some n
              | None -> match scope_get name ctx.subenums with
                   Some n -> Some n
                 | None -> match ctx_getenumbyfield ctx name with
                      Some n -> Some n
                    | None ->
                         Pos.sayat pos ("Symbol " ^ name ^ " is not an" ^
				        "enumerated constant, subenum, or a " ^
				        "field with enumerated type");
                         Util.fail ();
                         None
        end
      | READMEMBER (pos, _, _) ->
           Pos.sayat pos ("Unexpected member access");
           Util.fail ();
           None
      | BOOLCONSTANT (pos, _v) ->
           Pos.sayat pos ("Unexpected boolean constant");
           Util.fail ();
           None
      | NUMCONSTANT (pos, _v) ->
           Pos.sayat pos ("Unexpected numeric constant");
           Util.fail ();
           None
      | STRCONSTANT (pos, _s) ->
           Pos.sayat pos ("Unexpected string constant");
           Util.fail ();
           None
      | HERE pos ->
           Pos.sayat pos ("Unexpected '.'");
           Util.fail ();
           None
      | LIST (pos, []) ->
           Pos.sayat pos ("Unexpected empty list");
           Util.fail ();
           None
      | LIST (pos, elems) ->
           let results = List.map (validate_subenumexpr ctx) elems in
           let seen = ref Types.StringSet.empty in
           let checkelem e = match e with
                 READVAR (_pos, name) ->
                    if Types.StringSet.mem name !seen then begin
                       Pos.sayat pos ("Duplicate entry " ^ name);
                       Util.fail ()
                    end else
                       seen := Types.StringSet.add name !seen
               | _ ->
                    Pos.sayat pos ("Explicit list in subenum must contain " ^
				   "only enumeration constants");
                    Util.fail ()
           in
           List.iter checkelem elems;
           mergeall pos results
      | MODIFIER (pos, _modname, _args) ->
           Pos.sayat pos ("Unexpected 'modifier'");
           Util.fail ();
           None
      | PACK (pos, ctor, _args) ->
           Pos.sayat pos ("Unexpected compound type constructor " ^ ctor);
           Util.fail ();
           None
      | CAST (pos, _, _, _) ->
           Pos.sayat pos ("Unexpected cast");
           Util.fail ();
           None
      | ANNOTATE (pos, _, _) ->
           Pos.sayat pos ("Unexpected type annotation");
           Util.fail ();
           None

(*
 * Evaluate a piece of a subenum expression.
 *)
let rec eval_subenumexpr' ctx allsyms e = match e with
     UOP (_pos, _op, e1) ->
        (* the only valid op is BITNOT meaning complement; it's been checked *)
        let v1 = eval_subenumexpr' ctx allsyms e1 in
        Types.StringSet.diff allsyms v1
   | BOP (_pos, e1, op, e2) -> begin
        let v1 = eval_subenumexpr' ctx allsyms e1 in
        let v2 = eval_subenumexpr' ctx allsyms e2 in
        match op with
             BITOR -> Types.StringSet.union v1 v2
           | BITAND -> Types.StringSet.inter v1 v2
           | SUB -> Types.StringSet.diff v1 v2
           | _ -> Util.crash "encodingcheck: eval_subenumexpr': invalid op"
     end
   | FITS _ ->
        Util.crash "encodingcheck: eval_subenumexpr': fits invocation"
   | MODE _ ->
        Util.crash "encodingcheck: eval_subenumexpr': mode clause"
   | READVAR (_pos, name) ->
        if Types.StringSet.mem name allsyms then
           Types.StringSet.singleton name
        else
           (* must be the name of the field, i.e., everything *)
           allsyms
   | READMEMBER _ ->
        Util.crash "encodingcheck: eval_subenumexpr': member access"
   | BOOLCONSTANT _ ->
        Util.crash "encodingcheck: eval_subenumexpr': boolean constant"
   | NUMCONSTANT _ ->
        Util.crash "encodingcheck: eval_subenumexpr': numeric constant"
   | STRCONSTANT _ ->
        Util.crash "encodingcheck: eval_subenumexpr': string constant"
   | HERE _ ->
        Util.crash "encodingcheck: eval_subenumexpr': '.' symbol"
   | LIST (_pos, elems) ->
        let symlist = List.map (eval_subenumexpr' ctx allsyms) elems in
        Types.stringset_unionall symlist
   | MODIFIER _ ->
        Util.crash "encodingcheck: eval_subenumexpr': modifier invocation"
   | PACK _ ->
        Util.crash "encodingcheck: eval_subenumexpr': pack invocation"
   | CAST _ ->
        Util.crash "encodingcheck: eval_subenumexpr': cast"
   | ANNOTATE _ ->
        Util.crash "encodingcheck: eval_subenumexpr': type annotation"

(*
 * Evaluate a whole subenum expression.
 *)          
let eval_subenumexpr ctx whichenum e =
   match ctx_getenumbynum ctx whichenum with
        None ->
           Util.crash "encodingcheck: eval_subenumexpr: nonexistent enum"
      | Some vals ->
	   (* vals is a list of (name, value) and we just need the names *)
	   let syms = List.map (fun (_, s, _) -> s) vals in
	   let symset = Types.stringset_of_list syms in
	   eval_subenumexpr' ctx symset e   

(**************************************************************)
(* main recursive pass *)

let rec check'typename ctx ty = match ty with
     PLAINTYPE _ -> ty
   | WIDTHTYPE (_pos, _name, _arg) ->
	(* XXX disabled until we figure out where to put builtin types *)
(*
        if Types.StringSet.mem name Typerep.builtin_argtypes then
           (* XXX: check against maximum width too *)
           if arg <= 0 then begin
              Pos.sayat pos ("Invalid bit width " ^ string_of_int arg);
              Util.fail ()
           end
           else ()
        else ();
*)
        ty
   | EXPRTYPE (pos, ty') ->
        EXPRTYPE (pos, check'typename ctx ty')

(* explicit enum types are only allowed in fields *)
let check'enumtype ctx fieldname ty = match ty with
     ENUMTYPE (pos, width, vals) ->
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

        let expectednumvals = Util.power 2 width in
        let foundnumvals = List.length vals in
        if foundnumvals > expectednumvals && not toowide then begin
           Pos.sayat pos ("Too many values for " ^ string_of_int width ^
			  "-bit enumeration: found " ^
			  string_of_int foundnumvals ^ ", expected at most " ^
			  string_of_int expectednumvals);
           Util.fail();
        end
        else ();

        if complete && foundnumvals < expectednumvals then begin
           Pos.sayat pos ("Too few values for complete " ^
			  string_of_int width ^
			  "-bit enumeration: found " ^
			  string_of_int foundnumvals ^ ", expected exactly " ^
			  string_of_int expectednumvals);
           Util.fail();
        end
        else ();

        (* If toowide, don't bother trying to assign values. *)
        let vals = if toowide then vals
        else fill_in_enum pos expectednumvals vals
        in

        (* Remember the enumeration and get a unique number for it. *)
        let whichenum = ctx_addenum ctx fieldname vals in

        (* now bind all the symbols *)
        List.iter (bind_enumerator ctx whichenum) vals;

        (* return updated type *)
        ENUMTYPE (pos, width, vals)

let check'fieldref ctx fr = match fr with
     FIELDREF_ (pos, fname, opty, opval) ->
        (* do this first *)
        let opty = match opty with
             None -> None
           | Some ty -> Some (check'typename ctx ty)
        in
        begin
        match fname, opty, opval with
             "_", Some _ty, Some _val -> ()
           | "_", Some (WIDTHTYPE (_pos, "zeros", _width)), None -> ()
           | "_", Some (WIDTHTYPE (_pos, "ones", _width)), None -> ()
           | "_", Some _, None -> begin
                Pos.sayat pos ("Anonymous field with no value given");
                Util.fail ()
             end
           | "_", None, _ -> begin
                Pos.sayat pos ("Anonymous field with no type");
                Util.fail ()
             end
           | _, Some _, _ -> begin
                Pos.sayat pos ("Type annotation on already-typed field");
                Util.fail ()
             end
           | _, None, _ -> ()
        end;
        let fname, opty = match scope_get fname ctx.fields with
             Some _ -> fname, opty
           | None -> if fname <> "_" then begin
                Pos.sayat pos ("Nonexistent field " ^ fname ^ " in form");
                Util.fail ();
                "_", Some (WIDTHTYPE (pos, "zeros", 8))
             end
             else fname, opty
        in
        FIELDREF_ (pos, fname, opty, opval)
(*
     FIELDREF (pos, name) -> begin
        match scope_get name ctx.fields with
             Some _ -> fr
           | None ->
                Pos.sayat pos ("Nonexistent field " ^ name ^ " in form");
                Util.fail ();
                FIELDREFX (pos, "zeros", 8)
     end
   | FIELDREFX (pos, name, width) ->
        (* XXX need a better name than "FIELDREFX" *)
        if name = "zeros" || name = "ones" then ()
        else begin
           Pos.sayat pos ("Invalid constant field specifier " ^
                          name ^ "(" ^ string_of_int width ^ ")");
           Util.fail ()
        end;
        fr
*)

let rec check'expr ctx e = match e with
     UOP (_pos, PLUS, e1) ->
        check'expr ctx e1
   | UOP (pos, op, e1) ->
        let e1' = check'expr ctx e1 in
        UOP (pos, op, e1')
   | BOP (pos, e1, op, e2) -> begin
        let e1' = check'expr ctx e1 in
        let e2' = check'expr ctx e2 in
        match op with
             NEQ ->   UOP (pos, LOGNOT, BOP (pos, e1', EQ, e2'))
           | NOTIN -> UOP (pos, LOGNOT, BOP (pos, e1', IN, e2'))
           | LTEQ ->  UOP (pos, LOGNOT, BOP (pos, e2', LT, e1'))
           | _ -> BOP (pos, e1', op, e2')
     end
   | FITS (pos, e1, ty) ->
        let e1' = check'expr ctx e1 in
        let ty' = check'typename ctx ty in
        FITS (pos, e1', ty')
   | MODE (pos, name) ->
        MODE (pos, name)
   | READVAR (pos, "_") ->
        Pos.sayat pos ("Illegal use of _ wildcard name");
        Util.fail ();
        e
   | READVAR (_pos, name) -> begin
        match scope_get name !(ctx.vars) with
             Some _ ->
                scope_bind name true !(ctx.varsused);
                e
           | None ->
(* no longer tenable now that we have enumerators coming from registers.def *)
(*
                Pos.sayat pos ("No such variable or symbol " ^ name);
                Util.fail ();
*)
                e
     end
   | READMEMBER (pos, e1, name) ->
        let e1' = check'expr ctx e1 in
        READMEMBER (pos, e1', name)
   | BOOLCONSTANT _ -> e
   | NUMCONSTANT _ -> e
   | STRCONSTANT _ -> e
   | HERE _ -> e
   | LIST (pos, elems) ->
        let elems' = List.map (check'expr ctx) elems in
        LIST (pos, elems')
   | MODIFIER (pos, modname, args) ->
        let args' = List.map (check'expr ctx) args in
        MODIFIER (pos, modname, args')
   | PACK (pos, ctor, args) ->
        let args' = List.map (check'expr ctx) args in
        PACK (pos, ctor, args')
   | CAST (pos, newty, oldty, e1) ->
        let e1' = check'expr ctx e1 in
        let oldty' = check'typename ctx oldty in
        let newty' = check'typename ctx newty in
        begin
        match newty', oldty' with
             (* signed widen/narrow *)
             WIDTHTYPE (pos, "int", w2), WIDTHTYPE (_pos, "int", w1) ->
                if w1 = w2 then
                   Pos.sayat pos ("Warning: vacuous cast")
                else ()
             (* unsigned widen/narrow *)
           | WIDTHTYPE (pos, "uint", w2), WIDTHTYPE (_pos, "uint", w1) ->
                if w1 = w2 then
                   Pos.sayat pos ("Warning: vacuous cast")
                else ()
             (* signedness conversion *)
           | WIDTHTYPE (pos, "int", w2), WIDTHTYPE (_pos, "uint", w1) ->
                if w1 <> w2 then begin
                   Pos.sayat pos ("Cast changes both signedness and size");
                   Util.fail ()
                end
                else () 
             (* other signedness conversion *)
           | WIDTHTYPE (pos, "uint", w2), WIDTHTYPE (_pos, "int", w1) ->
                if w1 <> w2 then begin
                   Pos.sayat pos ("Cast changes both signedness and size");
                   Util.fail ()
                end
                else () 
             (* everything else is illegal *)
           | _, _ ->
                Pos.sayat pos ("Illegal type conversion");
                Util.fail ()
        end;
        CAST (pos, newty', oldty', e1')
   | ANNOTATE (pos, ty, e1) ->
        let e1' = check'expr ctx e1 in
        let ty' = check'typename ctx ty in
	ANNOTATE (pos, ty', e1')

let check'optexpr ctx oe = match oe with
     None -> None
   | Some e -> Some (check'expr ctx e)

let check'pattern _ctx pat =
    let seen = ref Types.StringSet.empty in
    let rec docheck p = match p with
        SETVAR (pos, name) ->
           if name = "_" then ()
           else if Types.StringSet.mem name !seen then begin
              Pos.sayat pos ("Duplicate name " ^ name ^ " in assignment");
              Util.fail ()
           end
           else begin
              seen := Types.StringSet.add name !seen
           end;
           SETVAR (pos, name)
      | UNPACK (pos, ctor, args) ->
           let args' = List.map docheck args in
           UNPACK (pos, ctor, args')
   in
   docheck pat

let warn_unused_vars ctx =
   let chkused name used =
      if name = "_" || used then ()
      else
        match scope_get name !(ctx.vars) with
              None -> Util.crash ("encodingcheck: warn_unused_vars: " ^
				  "nonexistent var " ^ name)
            | Some bindpos ->
                 Pos.sayat bindpos ("Warning: value assigned to " ^ name ^
				    " never used")
   in
   scope_iter_bot chkused !(ctx.varsused)

let fail_unassigned_fields ctx encpos =
   let chkassigned name assigned =
      if assigned then ()
      else
         match scope_get name !(ctx.vars) with
              None -> Util.crash ("encodingcheck: fail_unassigned_fields: " ^
				  "nonexistent var " ^ name)
            | Some bindpos ->
                 Pos.sayat bindpos ("Field " ^ name ^
				    " never assigned a value");
                 Pos.sayat encpos ("in this encoding");
                 Util.fail ()
   in
   scope_iter chkassigned !(ctx.fieldsassigned)

(*
 * This is the header part of an encoding or macro definition.
 *
 * It is ok if another definition with the same name and the same args
 * and ops counts already exists, because it's different as long as
 * one of the argument or operand types is different. We don't have
 * types yet so we can't check that.
 *
 * However, we need to mark all the argument and operand symbols as
 * bound.
 *)
let check'insn ctx (INSN (pos, name, args, ops)) =
   let seen = ref Types.StringSet.empty in
   let bind_one (_pos, sym, _optty) =
      if Types.StringSet.mem sym !seen then begin
         Pos.sayat pos ("Duplicate symbol " ^ sym);
         Util.fail ()
      end
      else begin
         seen := Types.StringSet.add sym !seen
      end;
      scope_bind sym pos !(ctx.vars);
      (*
       * If it's already in varsused because it's a field in the form,
       * leave that alone. Otherwise, it isn't used yet.
       *)
      if scope_isbound sym !(ctx.varsused) then ()
      else
         scope_bind sym false !(ctx.varsused)
      ;
      (* If it's a field, it's now been assigned *)
      if scope_isbound sym !(ctx.fieldsassigned) then
         scope_bind sym true !(ctx.fieldsassigned)
      else ()
   in
   List.iter bind_one args;
   List.iter bind_one ops;
   let checkanno (pos, sym, optty) =
      let optty' = match optty with
           None -> None
         | Some ty -> Some (check'typename ctx ty)
      in
      (pos, sym, optty')
   in
   let args' = List.map checkanno args in
   let ops' = List.map checkanno ops in
   INSN (pos, name, args', ops')

let rec check'statement ctx s = match s with
     ASSIGN (pos, pat, e) ->
        let e' = check'expr ctx e in
	let pat' = check'pattern ctx pat in

	(*
	 * Note: we do not check the leading identifier in an UNPACK
	 * (because it's the name of a compound type and
         * those come from a different file) nor do we check that the
         * collection of identifiers found on the left matches the right,
         * because that requires types.
         *)

        let dovar name =
           (* Warn if we replace an unused binding in the current scope. *)
           begin
           match scope_get_bot name !(ctx.vars), scope_get name !(ctx.varsused)
           with
                None, _ -> ()
              | Some _bindpos, None ->
                   Util.crash ("encodingcheck: check'statement: " ^
			       "assign: nonexistent var " ^ name)
              | Some _bindpos, Some true -> ()
              | Some bindpos, Some false ->
                   Pos.sayat bindpos ("Warning: value assigned never used");
                   Pos.sayat pos ("Warning: overwritten here");
           end;

           (* rebind *)
           scope_bind name pos !(ctx.vars);
           (* if it's a field, it's now been assigned, and it's used *)
           if scope_isbound name !(ctx.fieldsassigned) then begin
              scope_bind name true !(ctx.varsused);
              scope_bind name true !(ctx.fieldsassigned)
           end
           else begin
              scope_bind name false !(ctx.varsused)
           end
        in
        let rec getvars p = match p with
              SETVAR (_pos, name) -> [name]
            | UNPACK (_pos, _ctor, args) ->
                 List.concat (List.map getvars args)
        in
        let vars = getvars pat' in
        List.iter dovar vars;

        ASSIGN (pos, pat, e')

   | ENCODE (pos, insn, guard, block) ->
        ctx_pushscope ctx true;

        let insn' = check'insn ctx insn in
        let guard' = check'optexpr ctx guard in

        (* statements allowed in an ENCODE: ASSIGN, WARN *)
        let okstatement s = match s with
             ASSIGN _ -> ()
           | ENCODE _ ->
                Pos.sayat pos ("'encode' nested within encoding");
                Util.fail ()
           | MACRO _ ->
                Pos.sayat pos ("'macro' within encoding");
                Util.fail ()
           | IF (pos, _, _, _) ->
                Pos.sayat pos ("'if' is permitted only in macros");
                Util.fail ()
           | USE (pos, _, _, _) ->
                Pos.sayat pos ("'use' is permitted only in macros");
                Util.fail ()
           | WARN _ -> ()
        in
        List.iter okstatement block;

        let block' = List.map (check'statement ctx) block in

        fail_unassigned_fields ctx pos;

        warn_unused_vars ctx;
        ctx_popscope ctx true;

        ctx_addinsn ctx insn';
        ctx.formused := true;

        ENCODE (pos, insn', guard', block')

   | MACRO (pos, insn, guard, block) ->
        ctx_pushscope ctx true;

        let insn' = check'insn ctx insn in
        let guard' = check'optexpr ctx guard in

        (* statements allowed in an MACRO: ASSIGN, IF, USE, WARN *)
        let okstatement s = match s with
             ASSIGN _ -> ()
           | ENCODE _ ->
                Pos.sayat pos ("'encode' within macro");
                Util.fail ()
           | MACRO _ ->
                Pos.sayat pos ("'macro' nested within macro");
                Util.fail ()
           | IF _ -> ()
           | USE _ -> ()
           | WARN _ -> ()
        in
        List.iter okstatement block;

        ctx.curmacro := Some insn;

        let block' = List.map (check'statement ctx) block in

        warn_unused_vars ctx;
        ctx.curmacro := None;
        ctx_popscope ctx true;

        ctx_addinsn ctx insn';

        MACRO (pos, insn', guard', block')

   | IF (pos, cond, t, f) ->
        let cond' = check'expr ctx cond in

        ctx_pushscope ctx false;
        let t' = List.map (check'statement ctx) t in
        ctx_popscope ctx false;

        ctx_pushscope ctx false;
        let f' = List.map (check'statement ctx) f in
        ctx_popscope ctx false;

        IF (pos, cond', t', f')
        
   | USE (pos, name, args, ops) ->
        begin
        match !(ctx.curmacro) with
             None -> ()
           | Some (INSN (_pos, _curname, _curargs, _curops)) -> ()
(* XXX disabled for the reasons cited
                let here = (name, List.length args, List.length ops) in
                let there = (curname, List.length curargs, List.length curops)
                in
                (*
                 * XXX this will fail improperly if it's supposed to be
                 * invoking something with different types. We can't check
                 * that without types... so we might have to disable this
                 * check and check it after type inference.
                 *)
		if here = there then begin
		   Pos.sayat pos "Recursive 'use'";
		   Util.fail ()
		end
		else ()
*)
        end;

        let args' = List.map (check'expr ctx) args in
        let ops' = List.map (check'expr ctx) ops in

        (*ctx_adduse ctx pos name (List.length args) (List.length ops);*)

        USE (pos, name, args', ops')

   | WARN (pos, str) ->
        (* nothing to do *)
        WARN (pos, str)

let check'decl ctx d = match d with
     FIELD (pos, name, ty, opt_relinfo) ->
        let ty' = check'typename ctx (*name*) ty in
        begin
        match scope_get name !(ctx.vars) with
             Some prevpos ->
                Pos.sayat pos ("Duplicate field name " ^ name);
                Pos.sayat prevpos ("Previous declaration");
                Util.fail ()
           | None -> ()
        end;
        scope_bind name pos !(ctx.vars);
        scope_bind name pos ctx.fields;
        let opt_relinfo' = match opt_relinfo with
             None -> None
           | Some (reloffset) ->
                (* XXX should check reloffset against bit positioning *)
                Some (reloffset)
        in
        FIELD (pos, name, ty', opt_relinfo')

     (* XXX fix this to cutpaste less code *)
   | ENUMFIELD (pos, name, ty, opt_relinfo) ->
        let ty' = check'enumtype ctx name ty in
        begin
        match scope_get name !(ctx.vars) with
             Some prevpos ->
                Pos.sayat pos ("Duplicate field name " ^ name);
                Pos.sayat prevpos ("Previous declaration");
                Util.fail ()
           | None -> ()
        end;
        scope_bind name pos !(ctx.vars);
        scope_bind name pos ctx.fields;
        let opt_relinfo' = match opt_relinfo with
             None -> None
           | Some (reloffset) ->
                (* XXX should check reloffset against bit positioning *)
                Some (reloffset)
        in
        ENUMFIELD (pos, name, ty', opt_relinfo')

   | SUBENUM (pos, name, syms) ->
        let checksym sym =
           if sym = "_" then begin
              Pos.sayat pos ("Subenum " ^ name ^ " contains _");
              Util.fail ();
              (-1)
           end
           else match scope_get sym ctx.enumerators with
	        Some v -> v
	      | None ->
		   Pos.sayat pos ("Symbol " ^ sym ^ " in subenum " ^ name ^
				  " is not an enumerated constant");
		   Util.fail ();
		   (-1)
        in
        let whichenums = List.map checksym syms in
        let whichenums = List.filter (fun n -> n >= 0) whichenums in
        if not (Util.alleq whichenums) then begin
           Pos.sayat pos ("Values in subenum " ^ name ^
			  " are not taken from a single enumeration");
           Util.fail ()
        end
        else begin
           match whichenums with
                [] ->
                   Pos.sayat pos ("Empty subenum");
                   Util.fail ()
              | whichenum :: _ ->
                   scope_bind name whichenum ctx.subenums
        end;
        scope_bind name pos !(ctx.vars);
        SUBENUM (pos, name, syms)

   | SUBENUMEXPR (pos, name, e) -> begin
        (* XXX do we call check'expr on e? *)
        match validate_subenumexpr ctx e with
             None ->
                (* Failed - drop it, replace with something empty *)
                FORM (pos, [], [])
           | Some whichenum ->
                let syms = eval_subenumexpr ctx whichenum e in
                scope_bind name whichenum ctx.subenums;
                scope_bind name pos !(ctx.vars);
                SUBENUM (pos, name, Types.StringSet.elements syms)
     end
   | FORM (pos, fieldrefs, statements) ->
        let fieldrefs' = List.map (check'fieldref ctx) fieldrefs in

        (* statements allowed in a FORM: ASSIGN, ENCODE, MACRO *)
        let okstatement s = match s with
             ASSIGN _ -> ()
           | ENCODE _ -> ()
           | MACRO _ -> ()
           | IF (pos, _, _, _) ->
                Pos.sayat pos ("'if' is permitted only in macros");
                Util.fail ()
           | USE (pos, _, _, _) ->
                Pos.sayat pos ("'use' is permitted only in macros");
                Util.fail ()
           | WARN _ ->
		(*
		 * It might be better to allow this... but it's
		 * awkward downstream.
		 *)
                Pos.sayat pos ("'use' is permitted only in macros and encodings");
                Util.fail ()
        in
        List.iter okstatement statements;

        (* prepare to go through the statements *)
        ctx.formused := false;
        ctx_pushscope ctx true;

        (* remember all the fields in this form *)
	let bindfr fr = match fr with
             FIELDREF_ (_, "_", _, _) -> ()
           | FIELDREF_ (frpos, name, _, None) ->
                scope_bind name frpos !(ctx.vars);
                scope_bind name false !(ctx.fieldsassigned);
                scope_bind name true !(ctx.varsused)
           | FIELDREF_ (frpos, name, _, Some _) ->
                scope_bind name frpos !(ctx.vars);
                scope_bind name true !(ctx.fieldsassigned);
                scope_bind name true !(ctx.varsused)
        in
        List.iter bindfr fieldrefs';

        (* go through the statements *)
        let statements' = List.map (check'statement ctx) statements in

        (* Clear the state *)
        warn_unused_vars ctx;
        ctx_popscope ctx true;
        if !(ctx.formused) = false && fieldrefs <> [] then
           Pos.sayat pos ("Warning: form contains no encodings")
        else ();

        FORM (pos, fieldrefs', statements')

(*
 * Check that all USEs refer to a MACRO or ENCODING whose name exists
 * and which has the right number of args and operands. Since we don't
 * have types yet, we can't check types and therefore can't be sure
 * that things match, or if there are multiple choices which one
 * matches. Therefore we can't check for cross-recursion yet.
 *
 * Actually, don't. As things have developed, it's ok for equivalences
 * declared in opmatch.def (e.g. "add reg, reg, reg = arith(ADD)") to
 * define instructions and it's legitimate to want to USE those. Whether
 * they exist is adequately checked downstream in genencoding.
 *)
(*
let checkuses ctx =
   let checkuse (pos, name, numargs, numops) =   
      match ctx_getinsn ctx name numargs numops with
             Some _ -> ()
           | None ->
                Pos.sayat pos ("Nothing defined matching 'use " ^ name ^ "'");
                Util.fail ()
   in
   let cmp (_p1, n1, a1, o1) (_p2, n2, a2, o2) =
      compare (n1, a1, o1) (n2, a2, o2)
   in
   let uses' = List.sort_uniq cmp !(ctx.uses) in
   List.iter checkuse uses'
*)

let check decls =
   let ctx = newctx () in
   let decls' = List.map (check'decl ctx) decls in
   (*checkuses ctx;*)
   decls'

