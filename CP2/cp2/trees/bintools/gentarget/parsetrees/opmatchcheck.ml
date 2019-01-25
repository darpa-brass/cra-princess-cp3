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
 * Preliminary local checks/fixups on Opmatchtree, the opmatch.def
 * parse tree.
 *
 * Things this does:
 *    - check for duplicates
 *    - otherwise bupkis, at least for now (XXX?)
 *)

open Opmatchtree

type sig_ = string * string list

let string_of_sig (name, optypes) =
   match optypes with
        [] -> name
      | _ -> name ^ " " ^ String.concat ", " optypes

module SigKey = struct
   type t = sig_
   let compare = Pervasives.compare
end
module SigMap = Map.Make(SigKey)

let check insns =
   let seen = ref SigMap.empty in
   let checkinsn { name; definedat; operandtags; _ } =
      let opjusttags = List.map (fun (_pos, ty) -> ty) operandtags in
      let sig_ = (name, opjusttags) in
      try
         let prevpos = SigMap.find sig_ !seen in
         Pos.sayat definedat ("Duplicate instruction " ^ string_of_sig sig_);
         Pos.sayat prevpos ("Previous definition was here");
         Util.fail ()
      with Not_found ->
         seen := SigMap.add sig_ definedat !seen
   in
   List.iter checkinsn insns;
   insns

