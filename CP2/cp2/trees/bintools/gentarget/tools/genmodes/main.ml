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

module Dumprep = struct
   (* XXX this should just return a string and main should be using dumpinfo *)
   let dump name spec =
      let text = Modedump.dump spec in
      Util.writeout ("genrelocs-" ^ name ^ ".dump") text
end

let loadspec dodumps specdir =
   (* All we need is modes.def *)
   let modeinfo = Modelex.read (specdir ^ "/modes.def") in

   let rep = modeinfo in
   if dodumps then Dumprep.dump "load" rep else ();
   rep

let prepspec dodumps spec =
(*
   let spec = Typeinf.typeinf spec in
   if dodumps then Dumprep.dump "typeinf" spec else ();
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();
   Util.say ("Spec validated; any further errors are downstream bugs.");
*)
   let _ = dodumps in
   spec

let generate dodumps specdir =
   let dumpinfo = Dumpinfo.make dodumps "genmodes" in
   let spec = loadspec dodumps specdir in
   let spec' = prepspec dodumps spec in
   let
      (targetmodes_h, targetmodes_c) =
         Mkmodes.mkmodes spec'
   in
   Output.output (Dumpinfo.tag dumpinfo "h") "targetmodes.h" targetmodes_h;
   Output.output (Dumpinfo.tag dumpinfo "c") "targetmodes.c" targetmodes_c

let main argv = match argv with
     [_argv0; specdir] -> generate false specdir
   | [_argv0; "-d"; specdir] -> generate true specdir
   | _ -> Util.say ("Usage: genmodes [-d] specdir"); Util.die ()

let _ = main (Array.to_list Sys.argv)
