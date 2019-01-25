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

(*
 * Shared type inference implementation. This file includes:
 *    - the type inference machinery
 *    - the type inference logic for the common expression representation
 *)

(**************************************************************)
(* our context *)

(*
 * note: currently nothing uses unalias_type; but we might put type
 * aliases back in, so don't remove it just yet.
 *)

(* BEGIN MANDATORY CUTPASTE *)
type callbacks = {
   (* resolve type alias names (provded by client) *)
   unalias_type: (Typerep.typename -> Typerep.typename);

   (* look up a compound type (provided by client) *)
   lookup_compoundtype: (string ->
	(Pos.pos * Typerep.typename) list option);
		(* definedat, argtys *)

   (* look up a variable (provided by client) *)
   lookup_variable: (string -> Typerep.typename option);

   (* look up a modifier (provided by client) *)
   lookup_modifier: (string ->
	(Pos.pos * Typerep.typename * Typerep.typename) option);
		(* definedat, argtype, resulttype *)

}
(* END MANDATORY CUTPASTE *)

(*
 * Note that for now we assume the parent closes in its own context
 * into the callbacks, so it isn't exposed to us directly.
 *)
type context = {
   (* callbacks provided by client *)
   callbacks: callbacks ref;

   (* the types we make up during inference, and a real type for each *)
   nexttmptype: int ref;
   tmptypes: (typename * Pos.pos) Types.IntMap.t ref;
}

(*
 * Dummy versions of the callbacks. These are needed (and the callbacks
 * need to be refs) in order to permit construction of a parent context
 * first, and then assignment of the callbacks that have the parent
 * context closed into them.
 *
 * This is the least untidy way I could come up with of dealing with
 * the situation. Using modules and functors doesn't help.
 *
 * The parent should assign the callbacks it needs to change after
 * construction.
 *)

let default_unalias_type t = t
let default_lookup_compoundtype _ = None
let default_lookup_variable _ = None
let default_lookup_modifier _ = None

let default_callbacks = {
   unalias_type = default_unalias_type;
   lookup_compoundtype = default_lookup_compoundtype;
   lookup_variable = default_lookup_variable;
   lookup_modifier = default_lookup_modifier;
}

let newctx () = {
   callbacks = ref default_callbacks;

   nexttmptype = ref 0;
   tmptypes = ref Types.IntMap.empty;
}

let setcallbacks ctx callbacks =
   ctx.callbacks := callbacks

let unalias_type ctx ty =
   !(ctx.callbacks).unalias_type ty

let lookup_compoundtype ctx name =
   !(ctx.callbacks).lookup_compoundtype name

let lookup_variable ctx name =
   !(ctx.callbacks).lookup_variable name

let lookup_modifier ctx name =
   !(ctx.callbacks).lookup_modifier name

(**************************************************************)
(* unification *)

(*
 * Type used when we need to make something up.
 *)
let failuretype = WIDTHTYPE ("uint", 8)

(*
 * Print out the temporary types table
 *)
(*
let print_tmptypes ctx =
   let p (n, (t, pos)) =
      prerr_string ("   " ^ Pos.string_of_pos pos ^ ": " ^ string_of_int n ^
		    " -> " ^ dump'typename t);
      prerr_newline ()
   in
   List.iter p (Types.IntMap.bindings !(ctx.tmptypes))
*)

(*
 * Allocate a new temporary type. Initially it resolves to itself.
 *)
let ctx_newtmptype ctx pos =
   let n = !(ctx.nexttmptype) in
   let t = TMPTYPE n in
   ctx.nexttmptype := n + 1;
   ctx.tmptypes := Types.IntMap.add n (t, pos) !(ctx.tmptypes);
   t

(*
 * Look up what a temporary type resolves to, by number.
 *)
let ctx_gettmptype ctx n =
   (* should never fail to find something *)
   Types.IntMap.find n !(ctx.tmptypes)

(*
 * Report a type mismatch between two types.
 * 
 * POS is the location where we discovered the problem. TY1 is the
 * first real type and TY2 is the second; the position of each is
 * where that real type was found.
 *)
let rec mismatch pos ty1 ty1'pos ty2 ty2'pos =
   let tn1 = dump'typename ty1 in
   let tn2 = dump'typename ty2 in
   if pos = ty1'pos then begin
      Pos.sayat ty1'pos ("Type mismatch: found type " ^ tn1 ^
                         " here, but it also has type " ^ tn2);
      Pos.sayat ty2'pos ("arising from here.");
      Util.fail ()
   end
   else if pos = ty2'pos then
      mismatch pos ty2 ty2'pos ty1 ty1'pos
   else begin
      Pos.sayat pos ("Type mismatch: ambiguous type derivation.");
      Pos.sayat ty1'pos ("   " ^ tn1 ^ " comes from here, and");
      Pos.sayat ty2'pos ("   " ^ tn2 ^ " comes from here.");
      Util.fail ()
   end

(*
 * Resolve temporary type N to type TY. If N is already pointing
 * to some other temporary type (besides itself), resolve that one
 * too. If it's pointing to a real type, that's a type error unless
 * they're the same type.
 *
 * TY'POS is the location where TY came from. POS is where the
 * resolution happened.
 *)
let rec resolve ctx pos n ty ty'pos =
(*
   prerr_string ("Resolve: " ^ string_of_int n ^ " -> " ^ dump'typename ty);
   prerr_newline ();
*)
   (* find what it resolves to *)
   let (res, res'pos) = Types.IntMap.find n !(ctx.tmptypes) in
   match res with
        (* a temporary type *)
        TMPTYPE n' -> begin
           assert (n' <= n);
           ctx.tmptypes := Types.IntMap.add n (ty, ty'pos) !(ctx.tmptypes);
(*
           print_tmptypes ctx;
*)
           if n != n' then
               resolve ctx pos n' ty ty'pos
           else ()
        end
      | EXPRTYPE (TMPTYPE n') -> begin
           match ty with
                EXPRTYPE ty' ->
                   resolve ctx pos n' ty' ty'pos
              | _ ->
                   mismatch pos ty ty'pos res res'pos
        end
      | _ ->
        (* a real type *)
        if res = ty then ()
        else match res, ty with
             EXPRTYPE res', EXPRTYPE (TMPTYPE n') ->
                resolve ctx pos n' res' res'pos
           | _ -> mismatch pos ty ty'pos res res'pos

(*
 * Resolve all temporary types NS to type TY.
 *)
let resolveall ctx pos ns ty ty'pos =
   let ns' = List.sort_uniq Pervasives.compare ns in
   List.iter (fun n -> resolve ctx pos n ty ty'pos) ns'

(*
 * Record that TY1 and TY2 are the same type.
 *
 * If one isn't a scratch type, use that to resolve the other.
 * If neither is a scratch type, that's a type error.
 *
 * If both are scratch types, look at their current resolutions.
 *
 * If both resolutions are also scratch types, use the lower-numbered
 * one to resolve the higher-numbered one. This way references in the
 * resolutions point only downward in the list of scratch types so
 * they can't become circular.
 *
 * If one of the resolutions is not a scratch type, use that to
 * resolve the other one.
 *
 * Return the resulting type (either the real type or the lower-
 * numbered scratch type) so it can be substituted into the rep
 * immediately.
 *)
let rec unify' ctx pos ty1 ty2 =
(*
   prerr_string ("Unify: " ^ dump'typename ty1 ^ " == " ^ dump'typename ty2);
   prerr_newline ();
*)
   match (ty1, ty2) with
      (TMPTYPE n1, TMPTYPE n2) -> begin
         let (res1, res1'pos) = ctx_gettmptype ctx n1 in
         let (res2, res2'pos) = ctx_gettmptype ctx n2 in
         match (res1, res2) with
              TMPTYPE n1', TMPTYPE n2' ->
                 (* up to four temporary types around; pick the smallest *)
                 assert(n1' <= n1);
                 assert(n2' <= n2);
                 let (ty, ty'pos) =
                    if n1' < n2' then (TMPTYPE n1', res1'pos)
                    else (TMPTYPE n2', res2'pos)
                 in
                 resolveall ctx pos [n1; n2; n1'; n2'] ty ty'pos;
                 ty
            | _, TMPTYPE n2' ->
                 resolveall ctx pos [n2; n2'] res1 res1'pos;
                 res1
            | TMPTYPE n1', _ ->
                 resolveall ctx pos [n1; n1'] res2 res2'pos;
                 res2
            | _, _ ->
                 if res1 = res2 then ()
                 else mismatch pos res1 res1'pos res2 res2'pos;
                 res1
      end
    | (TMPTYPE n1, _) -> resolve ctx pos n1 ty2 pos; ty2
    | (_, TMPTYPE n2) -> resolve ctx pos n2 ty1 pos; ty1
    | (EXPRTYPE ty1', EXPRTYPE ty2') -> unify' ctx pos ty1' ty2'
    | (_, _) ->
         if ty1 = ty2 then ()
         else mismatch pos ty1 pos ty2 pos;
         ty1

(*
 * Unify all the types and return the result.
 *)
let unify ctx pos types =
   match types with
        [] -> ctx_newtmptype ctx pos
      | [arg] -> arg
      | arg :: more -> List.fold_left (unify' ctx pos) arg more


let rec improvetype ctx ty = match ty with
     TMPTYPE n ->
        let (ty', _pos) = Types.IntMap.find n !(ctx.tmptypes) in
        ty'
   | EXPRTYPE ty' -> EXPRTYPE (improvetype ctx ty')
   | _ -> ty

(**************************************************************)
(* expressions *)

(*
 * widths for constants
 *
 * ilog2 produces k such that 2^k = x, rounded down. So if
 * x is 1, it yields 0; if x is 2 or 3, it yields 1. These
 * values need 1 bit and 2 bits respectively to represent,
 * so we need to add 1 to the ilog2 result to get the bitwidth.
 *
 * If the value is less than zero, it needs an extra bit relative to
 * the positive value.
 *)

let bitwidth_of_int x =
   if x = 0 then 1
   else if x < 0 then 2 + (Util.ilog2 (-x))
   else 1 + (Util.ilog2 x)

(* unused (for now?
let bitwidth_of_wide x =
   if Types.Wide.iszero x then 1
   else if Types.Wide.isneg x then 2 + (Types.Wide.ilog2 (Types.Wide.neg x))
   else 1 + (Types.Wide.ilog2 x)
*)

(*
 * The largest shift amount we conceivably have to think about is
 * one more than the maximum field width we support. Currently this
 * will end up being uint(8).
 *)
let shifttype = WIDTHTYPE ("uint", bitwidth_of_int (Types.maxintwidth + 1))

let inf'shift ctx pos args = match args with
     [num; count] ->
        let _ = unify' ctx pos shifttype count in
        unify ctx pos [num]
   | _ -> assert false (* already checked *)

let inf'op ctx pos op ty'args = match op with
     EQ -> ignore(unify ctx pos ty'args); booltype
   | IN -> begin
        match ty'args with
             [t1; LISTTYPE t2] -> ignore(unify ctx pos [t1; t2]); booltype
           | [t1; t2] -> ignore(unify ctx pos [LISTTYPE t1; t2]); booltype
           | _ -> assert false (* already checked *)
     end
   | LT -> ignore(unify ctx pos ty'args); booltype
   | STRCAT -> unify ctx pos ty'args
   | ADD -> unify ctx pos ty'args
   | SUB -> unify ctx pos ty'args
   | MUL -> unify ctx pos ty'args
   | DIV -> unify ctx pos ty'args
   | MOD -> unify ctx pos ty'args
   | NEG -> unify ctx pos ty'args
   | SHL -> inf'shift ctx pos ty'args
   | SHR -> inf'shift ctx pos ty'args
   | BITAND -> unify ctx pos ty'args
   | BITOR -> unify ctx pos ty'args
   | BITXOR -> unify ctx pos ty'args
   | BITNOT -> unify ctx pos ty'args
   | LOGAND -> unify ctx pos (booltype :: ty'args)
   | LOGOR -> unify ctx pos (booltype :: ty'args)
   | LOGXOR -> unify ctx pos (booltype :: ty'args)
   | LOGNOT -> unify ctx pos (booltype :: ty'args)
   | CONSTP
   | DEFINEDP ->
        let t = ctx_newtmptype ctx pos in
        ignore (unify ctx pos (EXPRTYPE t :: ty'args));
        booltype
   | ORD ->
        (*
         * XXX: to do this properly requires introducing width variables.
         * should do that (nothing particularly awful about it) but not
	 * right now. instead, pretend the result is uint(8) because that
         * happens to work for what I need right now. (XXX)
         *)
        WIDTHTYPE ("uint", 8)

let numopargs op = match op with
     EQ | IN | LT -> 2
   | STRCAT -> 2
   | ADD | SUB | MUL | DIV | MOD -> 2
   | NEG -> 1
   | SHL | SHR -> 2
   | BITAND | BITOR | BITXOR -> 2
   | BITNOT -> 1 
   | LOGAND | LOGOR | LOGXOR -> 2
   | LOGNOT -> 1
   | CONSTP | DEFINEDP -> 1
   | ORD -> 1

let inf'modifieruse ctx modname ty'args =
   match lookup_modifier ctx modname with
        Some (definedat, argtype, resulttype) -> begin
           match ty'args with
              [ty'arg] ->
                 ignore (unify' ctx definedat argtype ty'arg);
                 resulttype
              | _ ->
                 Util.say ("Invalid arguments for expression modifier " ^
			   modname);
                 Util.say ("Expected " ^ dump'typename argtype);
                 Util.fail ();
                 failuretype
        end
      | None ->
           Util.say ("Unknown expression modifier " ^ modname);
           Util.fail ();
           failuretype

let rec inf'expr ctx e = match e with
     CONST (pos, _, k) ->
        let ty = ctx_newtmptype ctx pos in
        CONST (pos, ty, k)
   | STRCONST (pos, _, s) ->
        let ty = PLAINTYPE "string" in
        STRCONST (pos, ty, s)
   | USEVAR (pos, _, name) -> begin
        match lookup_variable ctx name with
             Some ty -> USEVAR(pos, ty, name)
           | None ->
                (*
                 * Can't in general be caught upstream because enumerators
                 * can come from base.def and enumerators are valid in most
                 * expression contexts.
                 *)
                (* should have been caught upstream (e.g. Encodingcheck) *)
                Pos.sayat pos ("Unbound variable " ^ name);
                Util.fail ();
                USEVAR (pos, failuretype, name)
     end
   | USEFIELD (pos, _, e1, name) ->
        (*
         * Don't bother trying to deduce the type from the field name.
         * We shouldn't need it, and it destroys the scoping of record
         * field names and causes problems.
         *)
        let e1' = inf'expr ctx e1 in
        let ty'e1 = exprtype e1' in
        (* XXX we need the type of the field; can't do this yet *)
        let _ = (ty'e1, name) in
        let ty = ctx_newtmptype ctx pos in
        USEFIELD (pos, ty, e1', name)
   | OP (pos, _, op, args) ->
        (* If the number of args is wrong, upstream must have belched *)
        if List.length args != numopargs op then
           Pos.crashat pos ("Wrong number of args for " ^ dump'op op)
        else ();
        let args' = List.map (inf'expr ctx) args in
        let ty'args = List.map exprtype args' in
        let ty = inf'op ctx pos op ty'args in
        OP (pos, ty, op, args')
   | FITS (pos, _, e1, argty) ->
        let argty = unalias_type ctx argty in
        let e1' = inf'expr ctx e1 in
        (* don't unify the type of e1 with argty - whole point is it might be wider *)
        FITS (pos, booltype, e1', argty)
   | MODE (pos, modename) ->
        (* for now at least, type is always bool *)
        MODE (pos, modename)
   | LIST (pos, _, elems) ->
        let elems' = List.map (inf'expr ctx) elems in
        let ty = match elems' with
             [] -> ctx_newtmptype ctx pos
           | e1 :: _ -> LISTTYPE (exprtype e1)
        in
        LIST (pos, ty, elems')
   | MODIFIER (pos, _, modname, args) ->
        let args' = List.map (inf'expr ctx) args in
        let ty'args = List.map exprtype args' in
        let ty = inf'modifieruse ctx modname ty'args in
        MODIFIER (pos, ty, modname, args')
   | PACK (pos, _, ctor, args) -> begin
        let args' = List.map (inf'expr ctx) args in
        let ty'args = List.map exprtype args' in
        let ty = Typerep.PLAINTYPE ctor in
        begin
        match lookup_compoundtype ctx ctor with
             None ->
                Pos.sayat pos ("Cannot pack non-compound type " ^ ctor);
                Util.fail ()
           | Some argtys ->
	       let numargtys = List.length argtys in
	       let numargs = List.length args in
	       if numargtys <> numargs then begin
		  Pos.sayat pos ("Wrong number of elements for " ^ ctor ^
                                 "; " ^ "expected " ^ string_of_int numargtys ^
				 " but found " ^ string_of_int numargs);
		  Util.fail ()
	       end;
	       let pairs = Util.zip' argtys ty'args in
	       let dopair ((_pos2, argty), ty) =
                  (*
                   * XXX: pos2 is the location where argty was given
		   * (in the operands file) -- we want this position,
		   * but currently we can't get it into the
		   * unification logic. The pos argument it takes is
		   * the location where the unification takes place...
		   *)
		  ignore (unify' ctx pos argty ty)
	       in
	       List.iter dopair pairs
        end;
        PACK (pos, ty, ctor, args')
     end
   | CAST (pos, nt, ot, e1) ->
        let nt = unalias_type ctx nt in
        let ot = unalias_type ctx ot in
        let e1' = inf'expr ctx e1 in
        let ty'e1 = exprtype e1' in
        ignore (unify' ctx pos ot ty'e1);
        CAST (pos, nt, ot, e1')
   | EVAL (pos, _nty, relname, reloffset, _oty, e1) ->
        let e1' = inf'expr ctx e1 in
        let ty'e1 = exprtype e1' in
        let nty = match ty'e1 with
             EXPRTYPE t -> t
           | _ ->
             let nty = ctx_newtmptype ctx pos in
             ignore (unify' ctx pos (EXPRTYPE nty) ty'e1);
             nty
        in
        EVAL (pos, nty, relname, reloffset, ty'e1, e1')
   | UNEVAL (pos, _, e1) ->
        let e1' = inf'expr ctx e1 in
	let ty = ctx_newtmptype ctx pos in
        UNEVAL (pos, ty, e1')
   | ANNOTATE (pos, ty, e1) ->
        let ty = unalias_type ctx ty in
        let e1' = inf'expr ctx e1 in
        let ty'e1 = exprtype e1' in
        ignore (unify' ctx pos ty ty'e1);
        ANNOTATE (pos, ty, e1')
   | COMMENTED (text, e1) ->
        let e1' = inf'expr ctx e1 in
        COMMENTED (text, e1')

(**************************************************************)
(* resolve inferred types *)

let rec res'type ctx t = match t with
     TMPTYPE n -> begin
        let (t', _pos) = ctx_gettmptype ctx n in
        t'
     end
   | EXPRTYPE t' -> EXPRTYPE (res'type ctx t')
   | _ -> t

let rec res'expr ctx e = match e with
     CONST (pos, t, k) ->
        let t' = res'type ctx t in
        let embiggen x = match x with
             SMALL x' -> LARGE (Types.Wide.of_int x')
           | LARGE x' -> LARGE x'
        in
        let k = match t' with
             WIDTHTYPE ("int", n) -> if n > 24 then embiggen k else k
           | WIDTHTYPE ("uint", n) -> if n > 24 then embiggen k else k
           | _ -> k
        in
        CONST (pos, t', k)
   | STRCONST (pos, t, s) ->
        let t' = res'type ctx t in
        assert (t' = t); (* should always be "string" *)
        STRCONST (pos, t', s)
   | USEVAR (pos, t, name) ->
        USEVAR (pos, res'type ctx t, name)
   | USEFIELD (pos, t, e1, name) ->
        let t' = res'type ctx t in
        let e1' = res'expr ctx e1 in
        USEFIELD (pos, t', e1', name)
   | OP (pos, t, op, args) ->
        let t' = res'type ctx t in
        let args' = List.map (res'expr ctx) args in
        OP (pos, t', op, args')
   | FITS (pos, t, e1, argty) ->
        let e1' = res'expr ctx e1 in
        let t' = res'type ctx t in
        (* argty came from upstream and doesn't need resolving *)
        FITS (pos, t', e1', argty)
   | MODE (pos, modename) ->
        MODE (pos, modename)
   | LIST (pos, t, elems) ->
        let t' = res'type ctx t in
        let elems' = List.map (res'expr ctx) elems in
        LIST (pos, t', elems')
   | MODIFIER (pos, t, modname, args) ->
        let t' = res'type ctx t in
        let args' = List.map (res'expr ctx) args in
        MODIFIER (pos, t', modname, args')
   | PACK (pos, t, ctor, args) ->
        let t' = res'type ctx t in
        let args' = List.map (res'expr ctx) args in
        PACK (pos, t', ctor, args')
   | CAST (pos, nt, ot, e1) ->
        let nt' = res'type ctx nt in
        let ot' = res'type ctx ot in
        let e1' = res'expr ctx e1 in
        CAST (pos, nt', ot', e1')
   | EVAL (pos, nt, relname, reloffset, ot, e1) ->
        let nt' = res'type ctx nt in
        let ot' = res'type ctx ot in
        let e1' = res'expr ctx e1 in
        EVAL (pos, nt', relname, reloffset, ot', e1')
   | UNEVAL (pos, ty, e1) ->
        let ty' = res'type ctx ty in
        let e1' = res'expr ctx e1 in
        UNEVAL (pos, ty', e1')
   | ANNOTATE (pos, ty, e1) ->
        let ty' = res'type ctx ty in
        let e1' = res'expr ctx e1 in
        ANNOTATE (pos, ty', e1')
   | COMMENTED (text, e1) ->
        let e1' = res'expr ctx e1 in
        COMMENTED (text, e1')

(**************************************************************)
(* make sure we're done (no temporary types left) *)

let done'typename pos what ty = match ty with
     TMPTYPE n -> begin
        Pos.sayat pos ("Leftover temporary type " ^ string_of_int n ^
		       " in " ^ what);
        Util.fail ()
     end
   | _ -> ()

let done'typename'fatal pos what ty = match ty with
     TMPTYPE n ->
        Pos.crashat pos ("Leftover temporary type " ^ string_of_int n ^
		         " in " ^ what)
   | _ -> ()

let rec done'expr e = match e with
     CONST (pos, t, _k) -> done'typename pos "constant" t
   | STRCONST (pos, t, _s) -> done'typename pos "string constant" t
   | USEVAR (pos, t, name) -> done'typename pos ("use of variable " ^ name) t
   | USEFIELD (pos, t, e1, name) ->
        done'expr e1;
        done'typename pos ("use of field " ^ name) t
   | OP (pos, t, op, args) ->
        List.iter done'expr args;
        done'typename pos ("result of " ^ dump'op op) t
   | FITS (pos, t, e1, argty) ->
        done'expr e1;
        done'typename pos ("result of fits") t;
        (* just in case *)
        done'typename'fatal pos ("type argument of fits") argty
   | MODE (_pos, _modename) ->
        ()
   | LIST (pos, t, elems) ->
        List.iter done'expr elems;
        done'typename pos ("list expression") t
   | MODIFIER (pos, t, modname, args) ->
        List.iter done'expr args;
        done'typename pos ("modifier " ^ modname ^ " invocation") t
   | PACK (pos, t, ctor, args) ->
        List.iter done'expr args;
        done'typename pos ("pack of " ^ ctor) t
   | CAST (pos, nt, ot, e1) ->
        done'expr e1;
        done'typename'fatal pos "cast result" nt;
        done'typename'fatal pos "cast expectation" ot
   | EVAL (pos, nt, _relname, _reloffset, ot, e1) ->
        done'expr e1;
        done'typename'fatal pos "eval result" nt;
        done'typename'fatal pos "eval expectation" ot
   | UNEVAL (pos, ty, e1) ->
        done'expr e1;
        done'typename'fatal pos "uneval result" ty
   | ANNOTATE (pos, ty, e1) ->
        done'expr e1;
        done'typename'fatal pos "explicit type annotation" ty
   | COMMENTED (_text, e1) ->
        done'expr e1

