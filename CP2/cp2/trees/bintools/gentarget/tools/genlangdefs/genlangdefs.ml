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
 * Generate the langdefs.h file with basic definitions for the target
 * assembly language.
 *
 * XXX: should this be rolled into genlanguage?
 *)

(**************************************************************)

(*
 * Things we need to generate:
 *
 * AS_LINECOMMENT_ONECHAR
 *    a string #define with the single-character comment chars
 * AS_LINECOMMENT_TWOCHAR
 *    a string #define with the alternate two-character comment delimiters
 * AS_BLOCKCOMMENTS_NEST
 *    a #define or #undef: whether block comments nest
 * AS_SEPARATOR_TOKEN
 *    a #define with the token name (e.g. TOK_SEMIC) for the
 *    token that separates instructions on the same line
 *
 * These had been stuffed in targetdefs.h, but they don't belong
 * there and they come from the language definition file, not the
 * misc definitions file.
 *)

open Langtree
module G = Gcode

(**************************************************************)
(* langdefs.h *)

let generate_header props =

   (* line-comments *)
   let addlinecomment (ones, twos) (pos, text) =
      if String.length text = 1 then (text :: ones, twos)
      else if String.length text = 2 then (ones, text :: twos)
      else begin
         Pos.sayat pos ("Cannot handle line-comment delimiter " ^ text ^
                        " with current infrastructure (too large)");
         Util.fail ();
         (ones, twos)
      end
   in
   let (ones, twos) =
      List.fold_left addlinecomment ([], []) props.linecomments
   in
   let onecharstr = String.concat "" ones in
   let twocharstr = match twos with
        [] -> ""
      | [s] -> s
      | s :: _ -> 
           Util.say ("Cannot handle line-comment delimiter " ^ s ^
                          " with current infrastructure (too many)");
           Util.fail ();
           s
   in
   let onecharexpr = G.STRINGCONSTANT onecharstr in
   let twocharexpr = G.STRINGCONSTANT twocharstr in

   (* block comments *)
   let nest = match props.blockcomments with
        [(_pos, nest, "/*", "*/")] -> nest
      | [] ->
           Util.say ("No block-comment delimiters declared ");
           Util.fail ();
           false
      | (pos, nest, a, b) :: _ ->
           Pos.sayat pos ("Cannot handle block-comment delimiters " ^
                          a ^ " " ^ b ^
                          " with current infrastructure (too many)");
           Util.fail ();
           nest
   in

   (* separators *)
   let sepstr = match props.separators with
        [(pos, sep)] ->
           if String.length sep = 1 then sep
           else begin
              Pos.sayat pos ("Cannot handle separator token " ^ sep ^
                             " with current infrastructure (too long)");
              Util.fail ();
              ";"
           end
      | [] -> ""
      | (pos, sep) :: _ ->
           Pos.sayat pos ("Cannot handle separator token " ^ sep ^
                          " with current infrastructure (too many)");
           Util.fail ();
           sep
   in
   let sepexpr =
      let septokstr s = match s with
         (* XXX there should be a real table of these somewhere *)
           ";" -> "TOK_SEMIC"
         | _ -> 
              Util.say ("genlangdefs: Don't know token name for " ^ sepstr ^
                             " yet (please fix me)");
              Util.fail ();
              "TOK_SEMIC"
      in
      let sepexpr s =
         G.READVAR (G.ENUMTYPE "toktypes", septokstr s)
      in
      if sepstr = "" then None else Some (sepexpr sepstr)
   in

   let decls = [
      G.DEFINE ("AS_LINECOMMENT_ONECHAR", Some onecharexpr);
      G.DEFINE ("AS_LINECOMMENT_TWOCHAR", Some twocharexpr);
      (if nest then
          G.DEFINE ("AS_BLOCKCOMMENTS_NEST", None)
       else
          G.UNDEF "AS_BLOCKCOMMENTS_NEST"
      );
      (if sepexpr <> None then
          G.DEFINE ("AS_SEPARATOR_TOKEN", sepexpr)
       else
          G.UNDEF "AS_SEPARATOR_TOKEN"
      );
   ]
   in
   G.FILE (Some "LANGDEFS_H", [], decls)

let emit_langdefs dumpinfo props = 
   let code = generate_header props in
   Util.checkfail ();
   Output.output (Dumpinfo.tag dumpinfo "h") "langdefs.h" code

(**************************************************************)
(* main *)

let compile props =
   let dumpinfo = Dumpinfo.make false(*dodumps*) "genlangdefs" in

   emit_langdefs dumpinfo props

let main argv =
   let path = match argv with
	[_; path] -> path
      | argv0 :: _ -> begin
	   prerr_string (argv0 ^ ": usage: genlangdefs language.def\n");
	   Util.die ()
	end
      | [] -> begin
	   prerr_string ("genlangdefs: usage: genlangdefs language.def\n");
	   Util.die ()
	end
   in
   let props = Langlex.read path in
   compile props

let _ = main (Array.to_list Sys.argv)
