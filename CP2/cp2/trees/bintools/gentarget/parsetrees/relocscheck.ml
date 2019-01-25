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

(*
 * Local checks/fixups on Relocstree, the relocs.def parse tree.
 *)

open Relocstree

(* XXX write me *)

(**************************************************************)
(* assign code numbers for internal relocations *)

let privcodes'codes cs =
   let largest = ref 0 in
   let inspect (c: code) =
      match c.value with
           Some n -> if n > !largest then largest := n else ()
         | None -> ()
   in
   List.iter inspect cs;
   let update (c: code) =
      match c.value with
           Some _ -> c
         | None ->
              let n = 1 + !largest in
              largest := n;
              { c with value = (Some n); }
   in
   List.map update cs

let privcodes'decl d = match d with
     D_CODES (pos, binfmt, codes) ->
        (* each binfmt has its own independent code space *)
        let codes' = privcodes'codes codes in
        D_CODES (pos, binfmt, codes')
   | _ -> d

let privcodes decls =
   List.map privcodes'decl decls

(**************************************************************)
(* toplevel *)

let check decls =
   (* let decls = check'decls decls in *)
   privcodes decls
