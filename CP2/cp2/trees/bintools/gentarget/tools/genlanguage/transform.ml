(*
 * Copyright (c) 2016, 2017, 2018
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

module ET = Exprtransform
open Rep

(**************************************************************)
(* numerate pass *)

let numerate'typename = ET.numerate'typename
let numerate'expr = ET.numerate'expr

let numerate'compoundtype ctx (pos, members) =
   let numerate'member (mpos, ty) =
      (mpos, numerate'typename ctx ty)
   in
   let members' = List.map numerate'member members in
   (pos, members')

(*
 * XXX: currently we can't do this or the tagrules code splodes.  It
 * needs to know the token type to match on, and that's keyed to the
 * enumeration type, so if we numerate here it thinks everything
 * should be a number and nothing works.
 *
 * This needs to be cleaned up. Possibly the operandtags in the rep
 * need to store both the full type and the representation-level
 * (numerated) type.
 *)
let numerate'operandtag _ctx (pos, ty) =
(* XXX
   let ty' = numerate'typename ctx ty in
   (pos, ty')
*)
   (pos, ty)

let numerate'token ctx (pos, ty, istarget) =
   let ty' = numerate'typename ctx ty in
   (pos, ty', istarget)

let numerate'tokvalpattern ctx vpat =
   match vpat with
        BIND (pos, ty, name) ->
           BIND (pos, numerate'typename ctx ty, name)
      | _ -> vpat

let numerate'tokvalpattern_opt ctx ovpat =
   match ovpat with
        None -> None
      | Some vpat -> Some (numerate'tokvalpattern ctx vpat)

let numerate'tokenpattern ctx (pos, name, ovpat) =
   (pos, name, numerate'tokvalpattern_opt ctx ovpat)

let numerate'tokenexpr ctx (pos, name, opte) =
   let opte' = match opte with
        None -> None
      | Some e -> Some (numerate'expr ctx e)
   in
   (pos, name, opte')

let numerate'matchdecl ctx (pos, pats, te) =
   let pats' = List.map (numerate'tokenpattern ctx) pats in
   let te' = numerate'tokenexpr ctx te in
   (pos, pats', te')

let numerate'exprpattern ctx epat =
   match epat with
        TOKEN tpat ->
           let tpat' = numerate'tokenpattern ctx tpat in
           TOKEN tpat'
      | EXPR (pos, tpats, ovpat) ->
           let tpats' = List.map (numerate'tokenpattern ctx) tpats in
           let ovpat' = numerate'tokvalpattern_opt ctx ovpat in
           EXPR (pos, tpats', ovpat')
      | EXPRANY (pos, ovpat) ->
           let ovpat' = numerate'tokvalpattern_opt ctx ovpat in
           EXPRANY (pos, ovpat')

let numerate'tagrule ctx (pos, pats, guard, (rpos, tag, e)) =
   let pats' = List.map (numerate'exprpattern ctx) pats in
   let guard' = numerate'expr ctx guard in
   let e' = numerate'expr ctx e in
   (pos, pats', guard', (rpos, tag, e'))

let numerate langinfo =
   let enumtypes = langinfo.enumtypes in

   let load name (_pos, width, syms) =
      let doadd map (_sympos, sym, symval) =
         Types.StringMap.add sym symval map
      in
      let symtovalue = List.fold_left doadd Types.StringMap.empty syms in
      { ET.name; ET.width; ET.symtovalue; }
   in
   let ctx = ET.numeratectx_new (Types.StringMap.mapi load enumtypes) in

   let compoundtypes = Types.StringMap.map (numerate'compoundtype ctx) langinfo.compoundtypes in
   let operandtags = Types.StringMap.map (numerate'operandtag ctx) langinfo.operandtags in
   let tokens = Types.StringMap.map (numerate'token ctx) langinfo.tokens in
   let matches = List.map (numerate'matchdecl ctx) langinfo.matches in
   let tagrules = List.map (numerate'tagrule ctx) langinfo.tagrules in
   { langinfo with compoundtypes; operandtags; tokens; matches; tagrules; }
