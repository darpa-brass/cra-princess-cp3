(*
 * Copyright (c) 2016, 2017
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

let loadspec dodumps specdir =
   (*
    * Five things to load:
    *    - base.def (base types)
    *    - misc.def (miscellaneous info)
    *    - encoding.def (encoding definitions)
    *    - modifiers.def (expression modifiers)
    *    - relocs.def (general and ELF relocations)
    *)
   let baseinfo = Baselex.read (specdir ^ "/base.def") in
   let miscinfo = Misclex.read (specdir ^ "/misc.def") in
   let encodinginfo = Encodinglex.read (specdir ^ "/encoding.def") in
   let modinfo = Modifierlex.read (specdir ^ "/modifiers.def") in
   let relocinfo = Relocslex.read (specdir ^ "/relocs.def") in
   Util.checkfail ();
   (* Should we dump the info trees if dodumps is on? *)

   let rep = Buildrep.build
		baseinfo
		miscinfo
		encodinginfo
		modinfo
		relocinfo
   in

(*
   let vals = [
      ("enums",        Types.StringMap.cardinal rep.Rep.enums);
      ("operandtags",  Types.StringMap.cardinal rep.Rep.operandtags);
      ("fields",       Types.StringMap.cardinal rep.Rep.fields);
      ("forms",        Types.StringMap.cardinal rep.Rep.forms);
      ("subenums",     Types.StringMap.cardinal rep.Rep.subenums);
      ("encodings",    List.length rep.Rep.encodings);
      ("macros",       List.length rep.Rep.macros);
      ("instructions", List.length rep.Rep.instructions);
   ] in
   let printval (name, table) =
      Util.say ("   " ^ string_of_int table ^ " " ^ name)
   in
   Util.say "Loaded:";
   List.iter printval vals;
*)
   if dodumps then Dumprep.dump "load" rep else ();
   rep

let prepspec dodumps spec =
   let spec = Typeinf.typeinf spec in
   if dodumps then Dumprep.dump "typeinf" spec else ();
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   Util.say ("Spec validated; any further errors are downstream bugs.");

(*
   let spec = Transform.numerate spec in
   if dodumps then Dumprep.dump "numerate" spec else ();
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   let spec = Transform.delist spec in
   if dodumps then Dumprep.dump "delist" spec else ();
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   let spec = if spec.Rep.do_reginfo then begin
      let spec = Transform.registrate spec in
      if dodumps then Dumprep.dump "registrate" spec else ();
      Util.checkfail ();
      Typecheck.typecheck spec;
      Util.checkfail ();
      spec
   end
   else spec
   in

   let spec = Transform.inform spec in
   if dodumps then Dumprep.dump "inform" spec else ();
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();
*)
   spec

let generate dodumps specdir =
   let dumpinfo = Dumpinfo.make dodumps "genrelocs" in
   let spec = loadspec dodumps specdir in
   let spec' = prepspec dodumps spec in
   let
      (elfreloc_h, targetreloc_h, targetreloc_c, treloc_c) =
         Mkrelocs.mkrelocs spec'
   in
   Output.output (Dumpinfo.tag dumpinfo "erh") "elfreloc.h" elfreloc_h;
   Output.output (Dumpinfo.tag dumpinfo "ash") "targetreloc.h" targetreloc_h;
   Output.output (Dumpinfo.tag dumpinfo "asc") "targetreloc.c" targetreloc_c;
   Output.output (Dumpinfo.tag dumpinfo "ldh") "treloc.c" treloc_c

let main argv = match argv with
     [_argv0; specdir] -> generate false specdir
   | [_argv0; "-d"; specdir] -> generate true specdir
   | _ -> Util.say ("Usage: genrelocs [-d] specdir"); Util.die ()

let _ = main (Array.to_list Sys.argv)
