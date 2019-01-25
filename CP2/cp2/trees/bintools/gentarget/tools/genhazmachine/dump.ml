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

open Dumptools
open Rep

let dump'pos pos = Pos.string_of_pos pos
let dump'type ty = [Typerep.dump'typename ty]
let dump'expr e = [Exprrep.dump'expr e] (* XXX...? *)

let dump'mode (name, pos) =
   heading' "MODE" name pos

let dump'enumtype (_name, { name; definedat; width; elements; }) =
   let dump'elem (_pos, name, k) =
      shortfield name (string_of_int k)
   in
   heading' "ENUMTYPE" name definedat @
   shortfield "width" (string_of_int width) @
   field "values" (list dump'elem elements)

let dump'subenum (_name, { name; definedat; ty; selected; }) =
   let dump'sel (sym, tf) =
      shortfield sym (if tf then "true" else "false")
   in
   heading' "SUBENUM" name definedat @
   field "type" (dump'type ty) @
   field "selected" (list dump'sel (Types.StringMap.bindings selected))

let dump'field (_name, { name; definedat; ty; junk; }) =
   ignore junk;
   heading' "FIELD" name definedat @
   field "type" (dump'type ty)

let rec dump'rx definedat rx = match rx with
     ANY -> heading "ANY" definedat
   | SOME p -> heading' "SOME" p definedat
   | SEQ (r1, r2) ->
        heading "SEQ" definedat @
        field "1" (dump'rx definedat r1) @
        field "2" (dump'rx definedat r2)
   | ALT (r1, r2) ->
        heading "ALT" definedat @
        field "1" (dump'rx definedat r1) @
        field "2" (dump'rx definedat r2)
   | OPT r1 ->
        heading "OPT" definedat @
        field "1" (dump'rx definedat r1)
   | PLUS r1 ->
        heading "OPT" definedat @
        field "1" (dump'rx definedat r1)

let dump'predicatedecl (name, { definedat; args; es; }) =
   let dump'arg (name, (argpos, argty)) =
      heading name argpos @
      field "type" (dump'type argty)
   in
   heading' "PREDICATE" name definedat @
   field "args" (list dump'arg (Types.StringMap.bindings args)) @
   field "exprs" (list dump'expr es)

let dump'assignment (pos, name, ty, e) =
   heading' "ASSIGN" name pos @
   field "type" (dump'type ty) @
   dump'expr e

let dump'matcher definedat { guard; assignments; trigger; cond; } =
   field "guard" (dump'expr guard) @
   field "assignments" (list dump'assignment assignments) @
   shortfield "trigger" trigger @
   field "cond" (dump'rx definedat cond)

let dump'hazard { name; definedat; desc; m; } =
   heading' "HAZARD" name definedat @
   shortfield "desc" desc @
   dump'matcher definedat m

let dump'transfer { definedat; m; effects; } =
   let dump'nullification n = match n with
        NULLIFY -> "NULLIFY"
      | EXECUTE -> "EXECUTE"
   in
   let dump'where w = match w with
        STAY -> "STAY"
      | GO -> "GO"
   in
   let dump'effect (n, w) = [dump'nullification n ^ " " ^ dump'where w] in
   
   heading "TRANSFER" definedat @
   dump'matcher definedat m @
   list dump'effect effects

let dump'spec (spec: spec) =
   list dump'mode (Types.StringMap.bindings spec.modes) @
   list dump'enumtype (Types.StringMap.bindings spec.enumtypes) @
   list dump'subenum (Types.StringMap.bindings spec.subenums) @
   list dump'field (Types.StringMap.bindings spec.fields) @
   list dump'predicatedecl
      (Types.stringmap_bindings_inorder spec.predicates spec.predorder) @
   list dump'hazard spec.hazards @
   list dump'transfer spec.transfers

let dump spec =
   String.concat "\n" (dump'spec spec)
   