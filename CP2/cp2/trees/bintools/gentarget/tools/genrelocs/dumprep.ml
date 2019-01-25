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

open Dumptools
open Rep

let dump'typename ty = Typerep.dump'typename ty
let dump'expr e = [Exprrep.dump'expr e]

let rec dump'pattern pat = match pat with
     SETVAR (pos, name) ->
        heading' "SETVAR" name pos
   | SETFIELD (pos, e, name) ->
        heading' "SETFIELD" name pos @
        field "e" (dump'expr e)
   | UNPACK (pos, name, pats) ->
        heading' "UNPACK" name pos @
        field "members" (list dump'pattern pats)

let rec dump'statement s = match s with
     ASSIGN (pos, pat, e) ->
	heading "ASSIGN" pos @
	field "pattern" (dump'pattern pat) @
	field "e" (dump'expr e)
   | IF (pos, cond, t, f) ->
        heading "IF" pos @
        field "cond" (dump'expr cond) @
        field "t" (dump'statement t) @
        field "f" (dump'statement f)
   | WARN (pos, msg) ->
        heading "WARN" pos @
        shortfield "msg" msg
   | REQUIRE (pos, e) ->
        heading "REQUIRE" pos @
        field "e" (dump'expr e)
   | BLOCK ss ->
        indent (list dump'statement ss)

let dump'encfield (_, { name; definedat; ty; offset; }) =
   heading' "ENCFIELD" name definedat @
   shortfield "ty" (dump'typename ty) @
(*
   shortfield "relfield" (
      match relfield with
           None -> "<none>"
         | Some s -> s
   ) @
*)
   shortfield "offset" (string_of_int offset)

let dump'modifier { name; definedat;
                    argname; argtype;
                    symname; resulttype;
                    semantics; } =
   heading' "MODIFIER" name definedat @
   shortfield "argname" argname @
   shortfield "argtype" (dump'typename argtype) @
   shortfield "symname" symname @
   shortfield "resulttype" (dump'typename resulttype) @
   field "semantics" (list dump'statement semantics)

let dump'relocfield { fieldname; extfieldname; definedat; symname;
                      input; output;
                      ty; frominstruction; } =
   heading' "RELOCFIELD" fieldname definedat @
   shortfield "extfieldname" extfieldname @
   shortfield "symname" symname @
   shortfield "ty" (dump'typename ty) @
   shortfield "frominstruction" (string_of_bool frominstruction) @
   field "input" (list dump'statement input) @
   field "output" (list dump'statement output)

let dump'operation { opername; definedat; actions; } =
   heading' "OPERATION" opername definedat @
   indent (list dump'statement actions)

let dump'code binfmt { symname; definedat; num; behavior; } =
   heading' "CODE" symname definedat @
   shortfield "binfmt" binfmt @
   shortfield "num" (string_of_int num) @
   shortfield "behavior" (
      match behavior with
           NOP -> "NOP"
         | UNSUPPORTED -> "UNSUPPORTED"
         | APPLYIN (oper, rfs, dogenerate) ->
              let genstr = if dogenerate then "" else " nogenerate" in
              "APPLYIN " ^ oper ^ " " ^ (String.concat ", " rfs) ^ genstr
   )

let dump'codes (binfmt, cs) =
   list (dump'code binfmt) cs

let dump'spec { encfields; modifiers; relocfields; operations; allcodes; } =
   let encfieldlist = Types.StringMap.bindings encfields in
   list dump'encfield encfieldlist @
   list dump'modifier modifiers @
   list dump'relocfield relocfields @
   list dump'operation operations @
   let allcodelist = Types.StringMap.bindings allcodes in
   list dump'codes allcodelist

(* XXX this should just return a string and main should be using dumpinfo *)
let dump name spec =
   let text = String.concat "\n" (dump'spec spec) in
   Util.writeout ("genrelocs-" ^ name ^ ".dump") text

