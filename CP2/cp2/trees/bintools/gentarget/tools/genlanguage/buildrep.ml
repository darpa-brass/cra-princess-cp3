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
 * Check a Langtree (from language.def) against enum types from base.def.
 *
 * This performs the following checks that cannot be in langcheck.ml:
 *    - all TY_ENUM must refer to enumerations that exist
 *    - all E_READENUM must refer to enumeration constants that exist
 * and it also fills in the proper type in E_READENUM since we won't
 * previously know that.
 *
 * This also returns two maps with the enum type info: one that maps
 * enum type names to (pos, bitwidth, members) and one that maps
 * member names to (pos, typename, value).
 *
 * XXX: we also need to check that types appearing in tokens are ok
 * to be in tokens; enums are ok but some types aren't (and, can we
 * please get a clear concept of which aren't?)
 *)

module B = Basetree
module M = Misctree
module T = Langtree

module TR = Typerep
module ER = Exprrep
module R = Rep


(**************************************************************)
(* context *)

type ctx = {
   addrtype: TR.typename;
   numtype: TR.typename;
   enumtypes: (Pos.pos * int * R.enumerator list) Types.StringMap.t ref;
   enumvals: (Pos.pos * string * int) Types.StringMap.t ref;
   compoundtypes: (Pos.pos * (Pos.pos * TR.typename) list) Types.StringMap.t ref;
   operandtags: (Pos.pos * TR.typename) Types.StringMap.t ref;
}

(*
 * XXX: do we need to care that addresses are effectively signed
 * on some platforms? (e.g. mips)
 *)
let newctx addrwidth maxwidth = {
   addrtype = TR.WIDTHTYPE ("uint", addrwidth);
   numtype = TR.WIDTHTYPE ("uint", maxwidth);
   enumtypes = ref Types.StringMap.empty;
   enumvals = ref Types.StringMap.empty;
   compoundtypes = ref Types.StringMap.empty;
   operandtags = ref Types.StringMap.empty;
}


(**************************************************************)
(* matches *)

(*
 * Convert langinfo.keywords[] into rules like langinfo.matches[].
 * langinfo.keywords is an array of kwdecl: (pos, string, token) where:
 *
 *    - string is the spelling of the reserved word
 *    - token is the token to generate
 *      (which is both a token name and possibly a value expression)
 *
 * langinfo.matches is an array of matchdecl: (pos, patterns, token) where:
 *    - token is as in langinfo.keywords
 *    - patterns is a list of token patterns, each of which is a
 *      token name and possibly a value binder pattern
 *
 * Note that the patterns are binders, not expressions. The token
 * value may be either None (for tokens without values), a literal
 * value, or an identifier to bind. Thus
 *   match FOO(s) => BAR(s);
 * binds s on the left and uses it on the right.
 *
 * To match a variable already defined, use a guard condition:
 *   match FOO(s) PCT BAR(t) | s == t => BAZ(s);
 *
 * In the FUTURE I want to allow string match patterns, something
 * like FOO("~s" ~ a) | a == x => BAR(a);
 * where "~s" is like scanf("%s") and the structure of the ~ operator
 * is like the structure of the % operator for printing. (Which is
 * in turn swiped from Python.)
 *
 * For the time being we don't allow guard expressions in the input,
 * which sucks and should be fixed. (XXX)
 *)

let matchdecl_of_kwdecl d =
   match d with
      T.KWDECL (pos, string, tok) ->
         let vpat = T.P_CONSTANT_S (pos, string) in
         let tpat = T.TOKENPAT (pos, "IDENT", Some vpat) in
         T.MATCHDECL (pos, [tpat], tok)


(**************************************************************)
(* build *)

(*
 * Substitute the "number" and "address" types.
 *)
let change'type ctx ty = match ty with
     TR.PLAINTYPE "number" -> ctx.numtype
   | TR.PLAINTYPE "address" -> ctx.addrtype
   | _ -> ty

(* ugh this is messy, should I guess have a type transformer in exprutil  *)
let change'expr ctx e = match e with
     ER.CONST (pos, ty, k) ->
         ER.CONST (pos, change'type ctx ty, k)
   | ER.STRCONST (pos, ty, s) ->
         ER.STRCONST (pos, change'type ctx ty, s)
   | ER.USEVAR (pos, ty, name) ->
         ER.USEVAR (pos, change'type ctx ty, name)
   | ER.USEFIELD (pos, ty, e1, name) ->
        ER.USEFIELD (pos, change'type ctx ty, e1, name)
   | ER.OP (pos, ty, op, args) ->
        ER.OP (pos, change'type ctx ty, op, args)
   | ER.FITS (pos, ty, e, argty) ->
        ER.FITS (pos, change'type ctx ty, e, change'type ctx argty)
   | ER.MODE (pos, name) ->
        ER.MODE (pos, name)
   | ER.LIST (pos, ty, args) ->
        ER.LIST (pos, change'type ctx ty, args)
   | ER.MODIFIER (pos, ty, name, args) ->
        ER.MODIFIER (pos, change'type ctx ty, name, args)
   | ER.PACK (pos, ty, name, args) ->
        ER.PACK (pos, change'type ctx ty, name, args)
   | ER.CAST (pos, nty, oty, e1) ->
        ER.CAST (pos, change'type ctx nty, change'type ctx oty, e1)
   | ER.EVAL (pos, ty, rf, ro, ty2, e1) ->
        ER.EVAL (pos, change'type ctx ty, rf, ro, change'type ctx ty2, e1)
   | ER.UNEVAL (pos, ty, e1) ->
        ER.UNEVAL (pos, change'type ctx ty, e1)
   | ER.ANNOTATE (pos, ty, e1) ->
        ER.ANNOTATE (pos, change'type ctx ty, e1)
   | ER.COMMENTED (txt, e1) ->
        ER.COMMENTED (txt, e1)

let build'type ctx ty =
   let ty' = Typebuild.build'type ty in
   change'type ctx ty'

let build'expr ctx e =
   let e' = Exprbuild.build'expr e in
   Exprutil.xform (change'expr ctx) e'

let build'optexpr ctx oe = match oe with
     None -> None
   | Some e -> Some (build'expr ctx e)

let build'token ctx (pos, ty, istarget) =
   (pos, build'type ctx ty, istarget)

let build'tokvalpattern ctx tvpat = match tvpat with
     T.P_BINDER (pos, ty, name) -> R.BIND (pos, build'type ctx ty, name)
   | T.P_CONSTANT_S (pos, k) -> R.MATCHSTR (pos, k)
   | T.P_CONSTANT_N (pos, k) -> R.MATCHINT (pos, k)

let build'tokvalpattern_opt ctx otvpat = match otvpat with
     None -> None
   | Some tvpat -> Some (build'tokvalpattern ctx tvpat)

let build'tokenpattern ctx (T.TOKENPAT (pos, name, otvpat)) =
   (pos, name, build'tokvalpattern_opt ctx otvpat)

let build'match ctx (T.MATCHDECL (pos, tpats, T.TOKENEXPR (tpos, tname, e))) =
   let tpats' = List.map (build'tokenpattern ctx) tpats in
   let e' = build'optexpr ctx e in
   (pos, tpats', (tpos, tname, e'))

let build'exprpattern ctx epat = match epat with
     T.XP_TOKEN (_pos, tpat) ->
        let tpat' = build'tokenpattern ctx tpat in
        R.TOKEN (tpat')
   | T.XP_EXPR (pos, tpats, otvpat) ->
        let tpats' = List.map (build'tokenpattern ctx) tpats in
        let otvpat' = build'tokvalpattern_opt ctx otvpat in
        R.EXPR (pos, tpats', otvpat')
   | T.XP_EXPRANY (pos, otvpat) ->
        let otvpat' = build'tokvalpattern_opt ctx otvpat in
        R.EXPRANY (pos, otvpat')

let build'tagrule ctx (T.TAGRULE (pos, pats, guard, rpos, tag, e)) =
   let pats' = List.map (build'exprpattern ctx) pats in
   let guard' = build'expr ctx guard in
   let e' = build'expr ctx e in
   (pos, pats', guard', (rpos, tag, e'))

let build'langinfo ctx langinfo =
   (*enumtypes enumvals operandtags addrwidth maxwidth*)

   let kwmatches =
      List.map matchdecl_of_kwdecl langinfo.T.keywords
   in
   let matches = kwmatches @ langinfo.T.matches in

   let tokens = Types.StringMap.map (build'token ctx) langinfo.T.tokens in
   let matches = List.map (build'match ctx) matches in
   let tagrules = List.map (build'tagrule ctx) langinfo.T.tagrules in

   {
      R.addrtype = ctx.addrtype;
      R.numtype = ctx.numtype;
      R.letters = langinfo.T.letters;
      R.subletters = langinfo.T.subletters;
      R.enumtypes = !(ctx.enumtypes);
      R.enumvals = !(ctx.enumvals);
      R.compoundtypes = !(ctx.compoundtypes);
      R.operandtags = !(ctx.operandtags);
      R.tokens;
      R.matches;
      R.tagrules;
   }


(**************************************************************)
(* base elements *)

let build'basedecl ctx d = match d with
     B.ENUMTYPE (pos, name, width, members) ->

        let fixmember (mpos, mname, optmval) =
           (* it's been through basecheck so there should be a value *)
           let mval = match optmval with
                Some n -> n
              | None -> Pos.crashat mpos ("langmerge: no value for " ^ mname)
           in
           (mpos, mname, mval)
        in
        let members' = List.map fixmember members in

        ctx.enumtypes :=
           Types.StringMap.add name (pos, width, members') !(ctx.enumtypes);

        let addmember (mpos, mname, mval) =
           if mname <> "_" then
              ctx.enumvals :=
                 Types.StringMap.add mname (mpos, name, mval) !(ctx.enumvals)
        in
        List.iter addmember members'

   | B.COMPOUNDTYPE (pos, name, elements) ->
        let build (epos, ty) =
           (epos, build'type ctx ty)
        in
        let elements' = List.map build elements in
        ctx.compoundtypes :=
           Types.StringMap.add name (pos, elements') !(ctx.compoundtypes)
        
   | B.OPERANDTAG (pos, n, t) ->
        let t' = build'type ctx t in
        ctx.operandtags := Types.StringMap.add n (pos, t') !(ctx.operandtags)
   | _ -> ()

(**************************************************************)
(* builtin tokens *)

let addbuiltins langinfo =
   let f _tok1 _tok2 =
      (* duplicate tokens should be caught by langcheck *)
      Util.crash "buildrep: addbuiltins: leftover duplicate token"
   in
   let stdtokens =
      let fix ty = (Pos.builtin, ty, false) in
      Types.StringMap.map fix Langtree.stdtokens
   in
   let tokens = Types.stringmap_union f stdtokens langinfo.T.tokens in
   { langinfo with T.tokens; }


(**************************************************************)
(* toplevel *)

let build baseinfo miscinfo langinfo =
   let ctx = newctx miscinfo.M.addresswidth miscinfo.M.maximumwidth in

   let langinfo = addbuiltins langinfo in

   List.iter (build'basedecl ctx) baseinfo;
   build'langinfo ctx langinfo
