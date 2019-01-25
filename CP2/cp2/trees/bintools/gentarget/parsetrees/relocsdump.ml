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

(* dump for Relocstree *)

open Dumptools
open Relocstree

(**************************************************************)
(* main recursion *)

let dump'relocstyle rs = match rs with
     REL -> "Rel"
   | RELA -> "RelA"

let dump'howmany hm = match hm with
     ONE -> "one"
   | MANY -> "many"
   | MANYATONCE -> "manyatonce"

let dump'typename ty =
   Typedump.dump'typename ty

let dump'opttypename otn = match otn with
     None -> ["(none)"]
   | Some tn -> dump'typename tn

let dump'expr e =
   Exprdump.dump'expr e

let dump'optexpr oe = match oe with
     None -> ["(none)"]
   | Some e -> dump'expr e

let rec dump'pattern pat = match pat with
     WRITEVAR (pos, name) ->
        heading' "WRITEVAR" name pos
   | WRITEFIELD (pos, pat', name) ->
        heading' "WRITEFIELD" name pos @
        field "pattern" (dump'pattern pat')
   | UNPACK (pos, name, pats') ->
        heading' "UNPACK" name pos @
        field "members" (list dump'pattern pats')

let rec dump'statement s = match s with
     ASSIGN (pos, pat, e) ->
        heading "ASSIGN" pos @
        field "pattern" (dump'pattern pat) @
        field "expr" (dump'expr e)
   | IF (pos, cond, ts, fs) ->
        heading "IF" pos @
        field "cond" (dump'expr cond) @
        field "true" (list dump'statement ts) @
        field "false" (list dump'statement fs)
   | WARN (pos, text) ->
        heading' "WARN" text pos
   | REQUIRE (pos, e) ->
        heading "REQUIRE" pos @
        field "expr" (dump'expr e)
   | BLOCK (stmts) ->
        ["BLOCK"] @
        indent (list (dump'statement) stmts)

let dump'code (c: code) =
   let value' = match c.value with
        None -> shortfield "value" "[internal]"
      | Some k -> shortfield "value" (string_of_int k)
   in
   let semantics' = match c.semantics with
        NOP -> shortfield "semantics" "nop"
      | UNSUPPORTED -> shortfield "semantics" "unsupported"
      | APPLYIN (op, fields, cangenerate) ->
           let fieldstr = String.concat ", " fields in
           let genstr = if cangenerate then "" else " nogenerate" in
           shortfield "apply" (op ^ " in " ^ fieldstr ^ genstr)
   in
   heading' "CODE" c.name c.definedat @
   value' @ semantics'

let dump'groupdecl gd = match gd with
     GD_MATCH (pos, howmany, e, name) ->
        heading' "MATCH" name pos @
        shortfield "howmany" (dump'howmany howmany) @
        field "expr" (dump'expr e)
   | GD_WHENINPUT (pos, e) ->
        heading "WHEN INPUT" pos @
        field "expr" (dump'expr e)
   | GD_WHENOUTPUT (pos, e) ->
        heading "WHEN OUTPUT" pos @
        field "expr" (dump'expr e)
   | GD_ORDER (pos, ordering) ->
        heading "ORDER" pos @
        indent ordering
   | GD_INPUT (pos, block) ->
        heading "INPUT" pos @
        indent (list dump'statement block)
   | GD_OUTPUT (pos, block) ->
        heading "OUTPUT" pos @
        indent (list dump'statement block)
   | GD_RESOLVE (pos, block) ->
        heading "RESOLVE" pos @
        indent (list dump'statement block)
        
let dump'decl d = match d with
     D_FIELD f ->
        heading' "FIELD" f.name f.definedat @
        (if f.extname <> f.name then
           shortfield "extname" f.extname
         else []) @
        shortfield "frominstruction" (string_of_bool f.frominstruction) @
        field "readop" (List.concat (List.map dump'statement f.readop)) @
        field "writeop" (list dump'statement f.writeop) @
        begin
           match f.typename with
               None -> shortfield "typename" "[none]"
             | Some tyn -> field "typename" (dump'typename tyn)
        end
   | D_MODIFIER m ->
        heading' "MODIFIER" m.name m.definedat @
        shortfield "arg" m.arg @
        indent (list dump'statement m.block)
   | D_OP op ->
        heading' "OP" op.name op.definedat @
        field "computation" (list dump'statement op.computation)
   | D_CODES (pos, binfmt, codes) ->
        heading "CODES" pos @
        shortfield "binfmt" binfmt @
        indent (list dump'code codes)
   | D_SUBST s ->
        let dump'one (pos, x, extval, intval) =
           heading x pos @
           field "extval" (dump'expr extval) @
           field "intval" (dump'expr intval)
        in
        heading "SUBST" s.definedat @
        shortfield "binfmt" s.binfmt @
        field "guard" (dump'expr s.guard) @
        field "body" (list dump'one s.body)
   | D_GROUP g ->
        heading "GROUP" g.definedat @
        shortfield "binfmt" g.binfmt @
        list dump'groupdecl g.groupdecls
(* XXX
   | D_MACHINE (pos, name) ->
        heading' "MACHINE" name pos
   | D_RELOCSTYLE (pos, style) ->
        heading' "RELOCSTYLE" (dump'relocstyle style) pos
*)

(**************************************************************)
(* top level *)

let dump decls =
   String.concat "\n" (List.concat (List.map dump'decl decls))

