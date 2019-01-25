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

(* dump for Langtree *)
open Dumptools
open Langtree

(*
let dump'uop op = match op with
     UOP_PLUS -> "+"
   | UOP_NEG -> "-"
   | UOP_LOGNOT -> "!"

let dump'bop op = match op with
     BOP_LOGOR -> "||"
   | BOP_LOGXOR -> "^^"
   | BOP_LOGAND -> "&&"
   | BOP_EQ -> "=="
   | BOP_NEQ -> "!="
   | BOP_LT -> "<"
   | BOP_LTEQ -> "<="
   | BOP_ADD -> "+"
   | BOP_SUB -> "-"
   | BOP_MUL -> "*"
   | BOP_DIV -> "/"
   | BOP_MOD -> "%"
*)

let dump'typename = Typedump.dump'typename
let dump'expr = Exprdump.dump'expr

(*
let rec dump'expr e = match e with
     BOOLCONSTANT (pos, k) ->
        heading' "BOOL" (string_of_bool k) pos
   | NUMCONSTANT (pos, k) ->
        heading' "NUMBER" (string_of_int k) pos
   | STRCONSTANT (pos, k) ->
        heading' "STRING" k pos
   | READVAR (pos, ty, name) ->
        heading' "READVAR" name pos @
        field "type" (dump'typename ty)
   | UOP (pos, ty, op, e1) ->
        heading' "UOP" (dump'uop op) pos @
        field "type" (dump'typename ty) @
        indent (dump'expr e1)
   | BOP (pos, ty, e1, op, e2) ->
        heading' "BOP" (dump'bop op) pos @
        field "type" (dump'typename ty) @
        indent (dump'expr e1) @
        indent (dump'expr e2)
*)

let dump'optexpr oe = match oe with
     None -> []
   | Some e -> dump'expr e

let dump'tokvalpattern vp = match vp with
     None -> []
   | Some (P_BINDER (_pos, _ty, name)) -> ["bind " ^ name]
   | Some (P_CONSTANT_S (_pos, k)) -> ["eq " ^ k]
   | Some (P_CONSTANT_N (_pos, k)) -> ["eq " ^ string_of_int k]

let dump'tokenpattern (TOKENPAT (_pos, tokname, valpat)) =
   [tokname] @
   indent (dump'tokvalpattern valpat)

let dump'tokenexpr (TOKENEXPR (_pos, tokname, optval)) =
   [tokname] @
   indent (dump'optexpr optval)

let dump'linecomment (_pos, text) =
   [text]

let dump'blockcomment (_pos, nest, left, right) =
   [
      if nest then "nested" else "unnested";
      left;
      right;
   ]

let dump'token (name, (pos, ty, istarget)) =
   heading' (if istarget then "TOKEN" else "STDTOKEN") name pos @
   indent (dump'typename ty)

let dump'kwdecl (KWDECL (pos, name, te)) =
   heading' "KWDECL" name pos @
   indent (dump'tokenexpr te)

let dump'matchdecl (MATCHDECL (pos, pats, te)) =
   heading "MATCHDECL" pos @
   field "pattern" (list dump'tokenpattern pats) @
   field "result" (dump'tokenexpr te)

let dump'separator (_pos, text) =
   [text]

let dump'exprpattern xp = match xp with
     XP_TOKEN (pos, tp) ->
        heading "TOKEN" pos @
        field "token" (dump'tokenpattern tp)
   | XP_EXPR (pos, tps, tvp) ->
        heading "EXPR" pos @
        field "tokens" (list dump'tokenpattern tps) @
        field "binder" (dump'tokvalpattern tvp)
   | XP_EXPRANY (pos, tvp) ->
        heading "EXPRANY" pos @
        field "binder" (dump'tokvalpattern tvp)

let dump'tagrule (TAGRULE (pos, pats, guard, _rpos, optag, e)) =
   heading "TAGRULE" pos @
   field "pattern" (list dump'exprpattern pats) @
   field "guard" (dump'expr guard) @
   shortfield "optag" optag @
   field "expr" (dump'expr e)

let dump'props props = 
   ["PROPERTIES"] @
   field "linecomments" (list dump'linecomment props.linecomments) @
   field "blockcomments" (list dump'blockcomment props.blockcomments) @
   field "letters" props.letters @
   field "subletters" props.subletters @
   (
      let tokenlist = Types.StringMap.bindings props.tokens in
      field "tokens" (list dump'token tokenlist)
   ) @
   field "keywords" (list dump'kwdecl props.keywords) @
   field "matches" (list dump'matchdecl props.matches) @
   field "separators" (list dump'separator props.separators) @
   field "tagrules" (list dump'tagrule props.tagrules)

let dump props =
   String.concat "\n" (dump'props props)
