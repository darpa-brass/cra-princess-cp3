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

open Dumptools
open Basetree
open Typedump

let dump'enumerator (pos, name, optval) =
   let valstr = match optval with
        None -> "(none)"
      | Some v -> string_of_int v
   in
   heading name pos @
   shortfield "value" valstr

let dump'decl d = match d with
     ENUMTYPE (pos, name, width, members) ->
        heading' "ENUMTYPE" name pos @
        shortfield "width" (string_of_int width) @
        field "members" (list dump'enumerator members)
   | WRAPTYPE (pos, name, ty, string) ->
        heading' "WRAPTYPE" name pos @
        field "ty" (dump'typename ty) @
        shortfield "format" string
   | COMPOUNDTYPE (pos, name, members) ->
        heading' "COMPOUNDTYPE" name pos @
        field "members" (list (fun (_, t) -> dump'typename t) members)
   | OPERANDTAG (pos, longname, ty) ->
        heading' "OPERANDTAG" longname pos @
        field "ty" (dump'typename ty)
   | SHORTNAME (pos, shortname, longname) ->
        heading' "SHORTNAME" shortname pos @
        shortfield "longname" longname

let dump decls =
   String.concat "\n" (list dump'decl decls)
