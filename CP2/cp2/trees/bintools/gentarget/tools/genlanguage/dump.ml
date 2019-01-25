(*
 * Copyright (c) 2017, 2018
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

(* dump for genlanguage rep *)
open Dumptools
open Rep

let dump'typename = Typerep.dump'typename
let dump'expr e = [Exprrep.dump'expr e]

let dump'pattern p = match p with
     None -> "none"
   | Some (BIND (_pos, _ty, name)) -> "bind " ^ name
   | Some (MATCHSTR (_pos, k)) -> "eq " ^ k
   | Some (MATCHINT (_pos, k)) -> "eq " ^ string_of_int k

let dump'enumerator (pos, name, value) =
   heading name pos @
   shortfield "value" (string_of_int value)

let dump'enumerator2 (_, en) = dump'enumerator en

let dump'tokenexpr (_pos, tokname, optval) =
   [tokname] @
   match optval with
        None -> shortfield "novalue" ""
      | Some x -> field "value" (dump'expr x)

let dump'tagexpr (_pos, tagname, optval) =
   [tagname] @
   match (Some optval) (* XXX *) with
        None -> shortfield "novalue" ""
      | Some x -> field "value" (dump'expr x)

let dump'tokenpattern (pos, tokname, pat) =
   heading' "TOKEN" tokname pos @
   shortfield "binder" (dump'pattern pat)

let dump'exprpattern xp = match xp with
     TOKEN tpat ->
        dump'tokenpattern tpat
   | EXPR (pos, tps, pat) ->
        heading "EXPR" pos @
        field "tokens" (list dump'tokenpattern tps) @
        shortfield "binder" (dump'pattern pat)
   | EXPRANY (pos, pat) ->
        heading "EXPRANY" pos @
        shortfield "binder" (dump'pattern pat)

let dump'enumtype (name, (pos, width, members)) =
   heading' "ENUMTYPE" name pos @
   shortfield "width" (string_of_int width) @
   field "members" (list dump'enumerator members)

let dump'token (name, (pos, ty, istarget)) =
   heading' (if istarget then "TOKEN" else "STDTOKEN") name pos @
   shortfield "type" (dump'typename ty)

let dump'matchdecl (pos, pats, te) =
   heading "MATCH" pos @
   field "pattern" (list dump'tokenpattern pats) @
   field "result" (dump'tokenexpr te)

let dump'tagrule (pos, pats, guard, e) =
   heading "TAGRULE" pos @
   field "pattern" (list dump'exprpattern pats) @
   field "guard" (dump'expr guard) @
   field "result" (dump'tagexpr e)

let dump'spec spec =
   let enumtypes = Types.StringMap.bindings spec.enumtypes in
   let enumvals = Types.StringMap.bindings spec.enumvals in
   let tokens = Types.StringMap.bindings spec.tokens in

   field "letters" spec.letters @
   field "subletters" spec.subletters @
   field "enumtypes" (list dump'enumtype enumtypes) @
   field "enumvals" (list dump'enumerator2 enumvals) @
   field "tokens" (list dump'token tokens) @
   field "matches" (list dump'matchdecl spec.matches) @
   field "tagrules" (list dump'tagrule spec.tagrules)

let dump spec =
   String.concat "\n" (dump'spec spec)
