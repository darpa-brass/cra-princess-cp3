(*
 * Copyright (c) 2016, 2018
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
 * top-level iteration for passes with guts elsewhere
 *)

(* regexp compilation *)
let compile_regexps dumpinfo spec =
   let { Rep.hazards; Rep.transfers; } = spec in

   let compile'matcher m =
      Rx.compile_rx dumpinfo m.Rep.cond
   in
   let compile'hazard (h: Rep.hazard) =
      compile'matcher h.Rep.m
   in
   let compile'transfer (t: Rep.transfer) =
      compile'matcher t.Rep.m
   in
   let (haz_dfas, hazdumps) =
      Util.unzip (List.map compile'hazard hazards)
   in
   let (xfer_dfas, xferdumps) =
      Util.unzip (List.map compile'transfer transfers)
   in
   (haz_dfas, xfer_dfas, String.concat "\n" (hazdumps @ xferdumps))

(* predicate splitting *)
let predsplit spec =
   let { Rep.predicates; Rep.predorder; } = spec in
   let splitone _name { Rep.definedat; Rep.args; Rep.afields; Rep.es; } =
      let e = match es with
           [e] -> e
         | _ -> Util.crash "main: splitone: already split"
      in
      let es = Predsplit.predsplit Predsplit.TAKE_ARGDEP args e in
      
      (* compute cfields *)
      let cfields =
         let gettype (f: Rep.field) = f.Rep.ty in
         let collect = Transform.collect_fields gettype spec.Rep.fields in
         List.fold_left collect Types.StringMap.empty es
      in
      { Rep.definedat; Rep.args; Rep.afields; Rep.cfields; Rep.es; }
   in
   let predicates =
      Types.stringmap_mapi_inorder splitone predicates predorder
   in
   { spec with Rep.predicates; }

(*
 * actual main
 *)

let loadspec dumpinfo specdir =
   let baseinfo = Baselex.read (specdir ^ "/base.def") in
   let modeinfo = Modelex.read (specdir ^ "/modes.def") in
   let encodinginfo = Encodinglex.read (specdir ^ "/encoding.def") in
   let hazinfo = Hazardlex.read (specdir ^ "/hazards.def") in
   Util.checkfail ();

   (* XXX should really dump before doing this *)
   let hazinfo = Hazresolve.hazresolve hazinfo baseinfo encodinginfo in

   let rep = Buildrep.build baseinfo modeinfo encodinginfo hazinfo in

   let nhaz = List.length hazinfo.Hazardtree.hazards in
   Util.say ("Loaded " ^ string_of_int nhaz ^ " hazard definitions");

   Dumpinfo.trydump' "load" dumpinfo Dump.dump rep;
   rep

let prepspec dumpinfo spec =
   (* type inference first *)
   let spec = Typeinf.typeinf spec in
   Dumpinfo.trydump' "typeinf" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   let spec = Transform.number_matchers spec in

   (* prime predicate pairing / regexp alphabets before predicate splitting *)
   Predpair.setup spec;

   let spec = predsplit spec in
   Dumpinfo.trydump' "predsplit" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   Util.say ("Spec validated; any further errors are downstream bugs.");

   (* compile the regexps *)
   let (haz_dfas, xfer_dfas, dump) = compile_regexps dumpinfo spec in
   Dumpinfo.trydump' "automata" dumpinfo (fun s -> s) dump;
   Util.checkfail ();

   (* numerate and delist *)
   let spec = Transform.numerate spec in
   Dumpinfo.trydump' "numerate" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   let spec = Transform.delist spec in
   Dumpinfo.trydump' "delist" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   let spec = Transform.widen spec in
   Dumpinfo.trydump' "widen" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec;
   Util.checkfail ();

   (spec, haz_dfas, xfer_dfas)

let generate dodumps specdir =
   let dumpinfo = Dumpinfo.make dodumps "genhazmachine" in
   let spec = loadspec dumpinfo specdir in
   let (spec', haz_dfas, xfer_dfas) = prepspec dumpinfo spec in

   let hsym = "TARGETHAZ_H" in
   let hname = "targethaz.h" in
   let cname = "targethaz.c" in
   let hfile = Mkhazmachine.mkheader hsym spec' in
   let cfile = Mkhazmachine.mksource hname spec' haz_dfas xfer_dfas in
   Output.output (Dumpinfo.tag dumpinfo "h") hname hfile;
   Output.output (Dumpinfo.tag dumpinfo "c") cname cfile

let main argv = match argv with
     [_argv0; specdir] -> generate false specdir
   | [_argv0; "-d"; specdir] -> generate true specdir
   | _ -> Util.say ("Usage: genencoding [-d] specdir"); Util.die ()

let _ = main (Array.to_list Sys.argv)
