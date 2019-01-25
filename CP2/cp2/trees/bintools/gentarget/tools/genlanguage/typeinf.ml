(*
 * Copyright (c) 2018
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
 * Type inference for language material.
 *)

module TI = Exprtypeinf
open Typerep
open Exprrep
open Rep


(**************************************************************)
(* context *)

type infctx = {
   tictx: TI.context;

   spec: spec;

   addresstype: typename;
   seentokens: (Pos.pos * typename) Types.StringMap.t ref;
   vars: typename Types.scope ref;
}

(*
 * callbacks for Exprtypeinf
 *)

let unalias_type _ctx ty =
   (* no type alias names here *)
   ty

let lookup_compoundtype ctx name =
   try
      let (_pos, elements) =
         Types.StringMap.find name ctx.spec.compoundtypes
      in
      Some elements
   with Not_found -> None

let lookup_variable ctx name =
   Types.scope_find name !(ctx.vars)

let lookup_modifier _ctx _name =
   (* modifiers not allowed here *)
   None

let scope_push ctx =
   ctx.vars := Types.scope_push !(ctx.vars)

let scope_pop ctx =
   ctx.vars := Types.scope_pop !(ctx.vars)

(*
 * context
 *)

let infctx_new spec = 
   let addresstype = spec.addrtype in
   let ctx0 = {
      tictx = TI.newctx ();
      spec = spec;
      addresstype;
      seentokens = ref Types.StringMap.empty;
      vars = ref Types.emptyscope;
   } in
   (* close in the base context *)
   let callbacks = {
      TI.unalias_type = unalias_type ctx0;
      TI.lookup_compoundtype = lookup_compoundtype ctx0;
      TI.lookup_variable = lookup_variable ctx0;
      TI.lookup_modifier = lookup_modifier ctx0;
   } in
   TI.setcallbacks ctx0.tictx callbacks;
   ctx0

(*
 * remember a token
 *)

let addtoken ctx pos tname ttype = 
   ctx.seentokens := Types.StringMap.add tname (pos, ttype) !(ctx.seentokens)

(*
 * get type of a token
 *)

let token_type ctx t =
   try
      let (_, tt) = (Types.StringMap.find t !(ctx.seentokens)) in
      Some tt
   with Not_found -> None


(**************************************************************)
(* inference pass *)

let typeinf'expr ctx e = TI.inf'expr ctx.tictx e
let unify ctx pos ty1 ty2 = ignore (TI.unify' ctx.tictx pos ty1 ty2)


(*
let typenamepos ty = match ty with
     PLAINTYPE (pos, _) -> pos
   | WIDTHTYPE (pos, _,  _) -> pos
   | EXPRTYPE (pos, _) -> pos

let rec typeinf'expr ctx e = match e with
     BOOLCONSTANT _ -> e
   | NUMCONSTANT _ -> e
   | STRCONSTANT _ -> e
   | READVAR (pos, _, name) -> begin
        let ty = 
           try Types.StringMap.find name !ctx
           with Not_found ->
              PLAINTYPE (Pos.builtin, "_")
        in
        READVAR (pos, ty, name)
     end
   | UOP (pos, _, op, e1) ->
        let e1' = typeinf'expr ctx e1 in
        let ty = match op, exprtype e1' with
             UOP_PLUS, WIDTHTYPE (typos, tn, tw) -> WIDTHTYPE (typos, tn, tw)
           | UOP_NEG, WIDTHTYPE (typos, tn, tw) -> WIDTHTYPE (typos, tn, tw)
           | UOP_LOGNOT, PLAINTYPE (typos, "bool") -> PLAINTYPE (typos, "bool")
           | _, _ -> Pos.crashat pos ("Invalid type for unary " ^ uopstr op)
        in
        UOP (pos, ty, op, e1')
    | BOP (pos, _, e1, op, e2) ->
        let e1' = typeinf'expr ctx e1 in
        let e2' = typeinf'expr ctx e2 in
        let ty = match exprtype e1', op, exprtype e2' with
             PLAINTYPE (typos, "bool"), BOP_LOGOR, PLAINTYPE (_typos2, "bool") -> PLAINTYPE (typos, "bool")
           | PLAINTYPE (typos, "bool"), BOP_LOGXOR, PLAINTYPE (_typos2, "bool") -> PLAINTYPE (typos, "bool")
           | PLAINTYPE (typos, "bool"), BOP_LOGAND, PLAINTYPE (_typos2, "bool") -> PLAINTYPE (typos, "bool")
           | t1, BOP_EQ, t2 -> if t1 = t2 then PLAINTYPE (typenamepos t1, "bool") else
                Pos.crashat pos ("Mismatched types for binary ==")
           | t1, BOP_NEQ, t2 -> if t1 = t2 then PLAINTYPE (typenamepos t1, "bool") else
                Pos.crashat pos ("Mismatched types for binary !=")
           | PLAINTYPE (typos, "string"), BOP_LT, PLAINTYPE (_typos2, "string") -> PLAINTYPE (typos, "bool")
           | PLAINTYPE (typos, "string"), BOP_LTEQ, PLAINTYPE (_typos2, "string") -> PLAINTYPE (typos, "bool")
           | WIDTHTYPE (typos, _tn, _tw), BOP_LT, WIDTHTYPE (_typos2, _tn2, _tw2) -> PLAINTYPE (typos, "bool")
           | WIDTHTYPE (typos, _tn, _tw), BOP_LTEQ, WIDTHTYPE (_typos2, _tn2, _tw2) -> PLAINTYPE (typos, "bool")
           | PLAINTYPE (typos, "string"), BOP_ADD, PLAINTYPE (_typos2, "string") -> PLAINTYPE (typos, "string")
           | WIDTHTYPE (typos, tn, tw), BOP_ADD, WIDTHTYPE (_typos2, _tn2, _tw2) -> WIDTHTYPE (typos, tn, tw)
           | WIDTHTYPE (typos, tn, tw), BOP_SUB, WIDTHTYPE (_typos2, _tn2, _tw2) -> WIDTHTYPE (typos, tn, tw)
           | WIDTHTYPE (typos, tn, tw), BOP_MUL, WIDTHTYPE (_typos2, _tn2, _tw2) -> WIDTHTYPE (typos, tn, tw)
           | WIDTHTYPE (typos, tn, tw), BOP_DIV, WIDTHTYPE (_typos2, _tn2, _tw2) -> WIDTHTYPE (typos, tn, tw)
           | WIDTHTYPE (typos, tn, tw), BOP_MOD, WIDTHTYPE (_typos2, _tn2, _tw2) -> WIDTHTYPE (typos, tn, tw)
           | t1, _, t2 ->
                (* blah *)
                let t1s = String.concat " " (Typedump.dump'typename t1) in
                let t2s = String.concat " " (Typedump.dump'typename t2) in
                Pos.crashat pos ("Invalid types for binary " ^ bopstr op ^
				 ": " ^ t1s ^ " and " ^ t2s)
        in
        BOP (pos, ty, e1', op, e2')
*)

let typeinf'token ctx tokname (pos, ty, istarget) =
   addtoken ctx pos tokname ty;
   (pos, ty, istarget)

let typeinf'tokvalpattern ctx tokname ty pat = match pat with
     BIND (pos, _, name) ->
        ctx.vars := Types.scope_add name ty !(ctx.vars);
        BIND (pos, ty, name)
   | MATCHSTR (pos, s) -> begin
        match ty with
             PLAINTYPE "string" ->
                MATCHSTR (pos, s)
           | _ ->
                Pos.crashat pos ("Wrong type matching token " ^ tokname ^
                                 " (expected string)")
     end
   | MATCHINT (pos, n) -> begin
        match ty with
             WIDTHTYPE (_tn, _tw) -> (* XXX? *)
                MATCHINT (pos, n)
           | _ ->
                Pos.crashat pos ("Wrong type matching token " ^ tokname ^
                                 " (expected number)")
     end

let typeinf'tokvalpattern_opt ctx tokname ty otvpat = match otvpat with
     None -> None
   | Some tvpat -> Some (typeinf'tokvalpattern ctx tokname ty tvpat)

let typeinf'tokenpattern ctx (pos, tokname, otvpat) =
   let ty =
      match token_type ctx tokname with
           None -> Pos.crashat pos ("Unknown token " ^ tokname)
         | Some ty ->ty
   in
   (pos, tokname, typeinf'tokvalpattern_opt ctx tokname ty otvpat)

let typeinf'tokenexpr ctx (pos, tokname, oe) =
   let oe' =  match oe with
        None -> None
      | Some e ->
           let ty = 
	      match token_type ctx tokname with
		   None -> Pos.crashat pos ("Unknown token " ^ tokname)
		 | Some ty ->ty
           in
           let e' = typeinf'expr ctx e in
           let ty'e = exprtype e' in
           unify ctx pos ty'e ty;
           Some e'
   in
   (pos, tokname, oe')

let typeinf'matchdecl ctx (pos, pats, e) =
   scope_push ctx;
   let pats' = List.map (typeinf'tokenpattern ctx) pats in
   let e' = typeinf'tokenexpr ctx e in
   scope_pop ctx;
   (pos, pats', e')

let typeinf'exprpattern ctx epat = match epat with
     TOKEN tpat ->
         let tpat' = typeinf'tokenpattern ctx tpat in
         TOKEN tpat'
   | EXPR (pos, tpats, otvpat) ->
         let tpats' = List.map (typeinf'tokenpattern ctx) tpats in
         (* expressions are always address type *)
         let tokname = "<expression>" in
         let ty = EXPRTYPE ctx.addresstype in
         let otvpat' = typeinf'tokvalpattern_opt ctx tokname ty otvpat in
         EXPR (pos, tpats', otvpat')
   | EXPRANY (pos, otvpat) ->
         (* expressions are always address type *)
         let tokname = "<expression>" in
         let ty = EXPRTYPE ctx.addresstype in
         let otvpat' = typeinf'tokvalpattern_opt ctx tokname ty otvpat in
         EXPRANY (pos, otvpat')

let typeinf'tagrule ctx (pos, epats, guard, (tagpos, tag, e)) =
   scope_push ctx;
   let epats' = List.map (typeinf'exprpattern ctx) epats in
   let guard' = typeinf'expr ctx guard in
   let e' = typeinf'expr ctx e in
   scope_pop ctx;
   (pos, epats', guard', (tagpos, tag, e'))


(**************************************************************)
(* resolve pass *)

let typeres'typename ctx e = TI.res'type ctx.tictx e
let typeres'expr ctx e = TI.res'expr ctx.tictx e

let typeres'token _ctx _tokname (pos, ty, istarget) =
   (* this type should always be a real type *)
   (pos, ty, istarget)

let typeres'tokvalpattern ctx pat = match pat with
     BIND (pos, ty, name) ->
        let ty' = typeres'typename ctx ty in
        BIND (pos, ty', name)
   | MATCHSTR (pos, s) ->
        MATCHSTR (pos, s)
   | MATCHINT (pos, n) ->
        MATCHINT (pos, n)

let typeres'tokvalpattern_opt ctx otvpat = match otvpat with
     None -> None
   | Some tvpat -> Some (typeres'tokvalpattern ctx tvpat)

let typeres'tokenpattern ctx (pos, tokname, otvpat) =
   (pos, tokname, typeres'tokvalpattern_opt ctx otvpat)

let typeres'tokenexpr ctx (pos, name, oe) =
   let oe' =  match oe with
        None -> None
      | Some e -> Some (typeres'expr ctx e)
   in
   (pos, name, oe')

let typeres'matchdecl ctx (pos, pats, e) =
   let pats' = List.map (typeres'tokenpattern ctx) pats in
   (pos, pats', typeres'tokenexpr ctx e)

let typeres'exprpattern ctx epat = match epat with
     TOKEN tpat ->
         let tpat' = typeres'tokenpattern ctx tpat in
         TOKEN tpat'
   | EXPR (pos, tpats, otvpat) ->
         let tpats' = List.map (typeres'tokenpattern ctx) tpats in
         let otvpat' = typeres'tokvalpattern_opt ctx otvpat in
         EXPR (pos, tpats', otvpat')
   | EXPRANY (pos, otvpat) ->
         let otvpat' = typeres'tokvalpattern_opt ctx otvpat in
         EXPRANY (pos, otvpat')

let typeres'tagrule ctx (pos, epats, guard, (tagpos, tag, e)) =
   let epats' = List.map (typeres'exprpattern ctx) epats in
   let guard' = typeres'expr ctx guard in
   let e' = typeres'expr ctx e in
   (pos, epats', guard', (tagpos, tag, e'))

(**************************************************************)
(* check-done pass *)

let typedone'typename = TI.done'typename
let typedone'typename'fatal = TI.done'typename'fatal
let typedone'expr = TI.done'expr

let typedone'token _tokname (pos, ty, _istarget) =
   (* this type should always be a real type *)
   typedone'typename'fatal pos "token declaration" ty

let typedone'tokvalpattern pat = match pat with
     BIND (pos, ty, name) ->
        typedone'typename pos ("binding of " ^ name) ty
   | MATCHSTR (_pos, _s) -> ()
   | MATCHINT (_pos, _n) -> ()

let typedone'tokvalpattern_opt otvpat = match otvpat with
     None -> ()
   | Some tvpat -> typedone'tokvalpattern tvpat

let typedone'tokenpattern (_pos, _tokname, otvpat) =
   typedone'tokvalpattern_opt otvpat

let typedone'tokenexpr (_pos, _name, oe) =
   match oe with
        None -> ()
      | Some e -> typedone'expr e

let typedone'matchdecl (_pos, pats, e) =
   List.iter typedone'tokenpattern pats;
   typedone'tokenexpr e

let typedone'exprpattern epat = match epat with
     TOKEN tpat ->
        typedone'tokenpattern tpat
   | EXPR (_pos, tpats, otvpat) ->
        List.iter typedone'tokenpattern tpats;
        typedone'tokvalpattern_opt otvpat
   | EXPRANY (_pos, otvpat) ->
        typedone'tokvalpattern_opt otvpat

let typedone'tagrule (_pos, epats, guard, (_tagpos, _tag, e)) =
   List.iter typedone'exprpattern epats;
   typedone'expr guard;
   typedone'expr e


(**************************************************************)
(* top level *)

let typeinf props =
   let ctx = infctx_new props in

   let addenum enumname (_pos, _width, members) =
      let addmem (_mpos, mname, _mval) =
         ctx.vars := Types.scope_add mname (PLAINTYPE enumname) !(ctx.vars)
      in
      List.iter addmem members
   in
   Types.StringMap.iter addenum props.enumtypes;
   addenum "bool" (Pos.builtin, 1, [
                      (Pos.builtin, "true", 0);
                      (Pos.builtin, "false", 1)
                  ]);

   let tokens = Types.StringMap.mapi (typeinf'token ctx) props.tokens in
   let matches = List.map (typeinf'matchdecl ctx) props.matches in
   let tagrules = List.map (typeinf'tagrule ctx) props.tagrules in

   let tokens = Types.StringMap.mapi (typeres'token ctx) tokens in
   let matches = List.map (typeres'matchdecl ctx) matches in
   let tagrules = List.map (typeres'tagrule ctx) tagrules in

   Types.StringMap.iter typedone'token tokens;
   List.iter typedone'matchdecl matches;
   List.iter typedone'tagrule tagrules;

   { props with tokens; matches; tagrules; }
