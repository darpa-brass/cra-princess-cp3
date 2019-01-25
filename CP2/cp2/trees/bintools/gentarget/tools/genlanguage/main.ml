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

(*
 * Generate the sources and headers associated with the target assembly
 * language.
 *)

(**************************************************************)

(*
 * genlanguage - generate MD portions of assembly language parsing
 *
 * The model for assembly languages is that much of the syntax is
 * universal and only the following is MD:
 *    - the token or tokens that introduce line comments
 *    - whether /* */ block comments nest
 *    - the token separating multiple instructions on the same line, if any
 *    - whether the argument of .align is a plain value or a log value
 *    - what characters beyond A-Za-z0-9_. go into identifiers
 *    - the prefix that identifies compiler scratch labels
 *    - zero or more reserved words
 *    - zero or more compound token types (and rules to match them from
 *      base tokens) (these are matched before expressions are parsed)
 *    - zero or more operand tags (and rules to match them from
 *      expressions) (these are matched after expressions are parsed)
 *
 * Token names that have values are written tokname(value), where value
 * can be numeric or symbolic.
 *
 * At the moment all this material is defined in language.def; see
 * parsers/langparse.mly for the form.
 *)

module T = Langtree
module R = Rep


(**************************************************************)
(* main *)

let loadspec dumpinfo specdir =
   let baseinfo = Baselex.read (specdir ^ "/base.def") in
   let miscinfo = Misclex.read (specdir ^ "/misc.def") in
   let langinfo = Langlex.read (specdir ^ "/language.def") in
   Util.checkfail ();

   let spec = Buildrep.build baseinfo miscinfo langinfo in

   let vals = [
      ("letters", List.length spec.R.letters);
      ("subletters", List.length spec.R.subletters);
      ("enum types", Types.StringMap.cardinal spec.R.enumtypes);
      ("enum values", Types.StringMap.cardinal spec.R.enumvals);
      ("operand tags", Types.StringMap.cardinal spec.R.operandtags);
      ("tokens", Types.StringMap.cardinal spec.R.tokens);
      ("match rules", List.length spec.R.matches);
      ("tag rules", List.length spec.R.tagrules);
   ] in
   let printval (name, num) =
      Util.say ("   " ^ string_of_int num ^ " " ^ name)
   in
   Util.say "Loaded:";
   List.iter printval vals;

   Dumpinfo.trydump' "load" dumpinfo Dump.dump spec;
   spec

let prepspec dumpinfo spec =
   (* type inference *)
   let spec = Typeinf.typeinf spec in
   Dumpinfo.trydump' "typeinf" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec true(*beforenumerate*);
   Util.checkfail ();

   Util.say ("Spec validated; any further errors are downstream bugs.");

   (* numerate *)
   let spec = Transform.numerate spec in
   Dumpinfo.trydump' "numerate" dumpinfo Dump.dump spec;
   Util.checkfail ();
   Typecheck.typecheck spec false(*beforenumerate*);
   Util.checkfail ();

   spec

let generate dodumps specdir =
   let dumpinfo = Dumpinfo.make dodumps "genlanguage" in
   let spec = loadspec dumpinfo specdir in
   let spec' = prepspec dumpinfo spec in

   let header = Mklang.generate_header spec' in
   let source = Mklang.generate_source spec' in
   let operheader = Mklang.generate_operheader spec' in
   let opersource = Mklang.generate_opersource spec' in
   Output.output (Dumpinfo.tag dumpinfo "h") "targettoken.h" header;
   Output.output (Dumpinfo.tag dumpinfo "c") "targettoken.c" source;
   Output.output (Dumpinfo.tag dumpinfo "oh") "targetoper.h" operheader;
   Output.output (Dumpinfo.tag dumpinfo "oc") "targetoper.c" opersource

let main argv = match argv with
     [_argv0; specdir] -> generate false specdir
   | [_argv0; "-d"; specdir] -> generate true specdir
   | _ -> Util.say ("Usage: genlanguage [-d] specdir"); Util.die ()

let _ = main (Array.to_list Sys.argv)
