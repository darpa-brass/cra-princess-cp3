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
 * Generate basic declarations: targetdefs.h and targetelfdefs.h.
 *)

(**************************************************************)

(*
 * Things we need to generate:
 *
 * Types:
 *    [su]_mach{byte,word,large}
 *
 * Defines:
 *    AS_ALIGNS_BY_LOGVALUE (or not)
 *    AS_COMM_ALIGNS_BY_LOGVALUE (or not)
 *    TEMP_LABEL_PREFIX
 *    ENTRY_SYM
 *    DEFAULT_TEXTORG
 *    DEFAULT_DATAORG
 *    DEFAULT_BSSORG
 *    TARGET_MAXALIGN
 *    TARGET_PAGESIZE
 *    TARGET_TEXT_ALIGNMENT
 *    TARGET_RDATA_ALIGNMENT
 *    TARGET_DATA_ALIGNMENT
 *    TARGET_BSS_ALIGNMENT
 *    TARGET_ENDIANNESS
 *    TARGET_INTENCODING
 *    MIPS_ISSUE_REGINFO (or not)
 *
 * All of this stuff is right in misc.def.
 *)

open Misctree
module G = Gcode

(**************************************************************)
(* targetdefs.h *)

let is_value align =
   match align with
        ALIGN_LOGVALUE -> false
      | ALIGN_VALUE -> true

let is_logvalue align =
   match align with
        ALIGN_LOGVALUE -> true
      | ALIGN_VALUE -> false

let make_endian e = match e with
     BIG -> "MY_BIG_ENDIAN"
   | LITTLE -> "MY_LITTLE_ENDIAN"

let make_intencoding i = match i with
     TWOS_COMPLEMENT -> "MY_TWOS_COMPLEMENT"
   | ONES_COMPLEMENT -> "MY_ONES_COMPLEMENT"
   | SIGN_MAGNITUDE -> "MY_SIGN_MAGNITUDE"

let define name expr =
   G.DEFINE (name, Some expr)

let intdefine name ty n =
   define name (G.INTCONSTANT (ty, string_of_int n))

let generate_misc info =

   let defs = [
      G.TYPEDEF (G.INTBITS info.bytewidth, "s_machbyte");
      G.TYPEDEF (G.UINTBITS info.bytewidth, "u_machbyte");
      G.TYPEDEF (G.INTBITS info.addresswidth, "s_machword");
      G.TYPEDEF (G.UINTBITS info.addresswidth, "u_machword");
      G.TYPEDEF (G.INTBITS info.maximumwidth, "s_machlarge");
      G.TYPEDEF (G.UINTBITS info.maximumwidth, "u_machlarge");

      (G.defineif "AS_ALIGNS_BY_VALUE" (is_value info.align));
      (G.defineif "AS_ALIGNS_BY_LOGVALUE" (is_logvalue info.align));
      (G.defineif "AS_COMM_ALIGNS_BY_VALUE" (is_value info.commalign));
      (G.defineif "AS_COMM_ALIGNS_BY_LOGVALUE" (is_logvalue info.commalign));

      define "TEMP_LABEL_PREFIX" (G.STRINGCONSTANT info.temp_label_prefix);
      define "ENTRY_SYM" (G.STRINGCONSTANT info.entry_sym);

      intdefine "DEFAULT_TEXTORG" G.INT info.default_textorg;
      intdefine "DEFAULT_DATAORG" G.INT info.default_dataorg;
      intdefine "DEFAULT_BSSORG" G.INT info.default_bssorg;

      intdefine "TARGET_MAXALIGN" G.INT info.maxalign;
      intdefine "TARGET_PAGESIZE" G.INT info.pagesize;

      intdefine "TARGET_TEXT_ALIGNMENT"  G.INT info.text_alignment;
      intdefine "TARGET_RDATA_ALIGNMENT" G.INT info.rdata_alignment;
      intdefine "TARGET_DATA_ALIGNMENT"  G.INT info.data_alignment;
      intdefine "TARGET_BSS_ALIGNMENT"   G.INT info.bss_alignment;

      define "TARGET_ENDIANNESS"
                (G.READVAR (G.INT, make_endian info.endianness));

      define "TARGET_INTENCODING"
                (G.READVAR (G.INT, make_intencoding info.intencoding));

      G.defineif "MIPS_ISSUE_REGINFO" info.do_reginfo
   ]
   in

   G.FILE (Some "TARGETDEFS_H", [], defs)

let emit_targetdefs dumpinfo props = 
   let code = generate_misc props in
   Output.output (Dumpinfo.tag dumpinfo "h") "targetdefs.h" code

(**************************************************************)
(* targetelfdefs.h *)

let make_elfclass w =
   "ELFCLASS" ^ string_of_int w

let make_elfendian e = match e with
     BIG -> "ELFDATA2MSB"
   | LITTLE -> "ELFDATA2LSB"

let generate_elf info =

   let defs = [
      define "TARGET_ELF_CLASS"
                (G.READVAR (G.INT, make_elfclass info.addresswidth));
      define "TARGET_ELF_ENDIANNESS"
                (G.READVAR (G.INT, make_elfendian info.endianness));
      define "TARGET_ELF_MACHINE"
                (G.READVAR (G.INT, "EM_" ^ info.elf_machine));

      G.defineif "TARGET_ELF_USE_REL" (not info.elf_use_rela);
      G.defineif "TARGET_ELF_USE_RELA" (info.elf_use_rela);
      G.defineif "TARGET_ELF_USE_R_EXT" (info.elf_use_r_ext);
   ]
   in

   G.FILE (Some "TARGETELFDEFS_H", [], defs)

let emit_targetelfdefs dumpinfo info = 
   let code = generate_elf info in
   Output.output (Dumpinfo.tag dumpinfo "eh") "targetelfdefs.h" code

(**************************************************************)
(* main *)

let compile info =
   let dumpinfo = Dumpinfo.make false(*dodumps*) "genmisc" in

   emit_targetdefs dumpinfo info;
   emit_targetelfdefs dumpinfo info

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
   let info = Misclex.read path in
   compile info

let _ = main (Array.to_list Sys.argv)
