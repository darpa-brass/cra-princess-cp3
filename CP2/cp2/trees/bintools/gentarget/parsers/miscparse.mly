%{
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

open Pos
module T = Misctree

let pos () = Pos.fromparser ()


let checkendian pos str def =
   match str with
        "big" -> T.BIG
      | "little" -> T.LITTLE
      | _ ->
	   Pos.sayat pos ("Invalid endianness " ^ str);
           Util.fail ();
           def

let checkenc pos str def =
   match str with
        "twos_complement" -> T.TWOS_COMPLEMENT
      | "ones_complement" -> T.ONES_COMPLEMENT
      | "sign_magnitude" -> T.SIGN_MAGNITUDE
      | _ ->
	   Pos.sayat pos ("Invalid integer type " ^ str);
           Util.fail ();
           def

let checkalign pos str def =
   match str with
        "value" -> T.ALIGN_VALUE
      | "logvalue" -> T.ALIGN_LOGVALUE
      | _ ->
	   Pos.sayat pos ("Invalid alignment method " ^ str);
           Util.fail ();
           def

let checkbool pos str def =
   match str with
        "true" -> true
      | "false" -> false
      | _ ->
	   Pos.sayat pos ("Invalid do_reginfo setting " ^ str);
           Util.fail ();
           def

type decl =
    NUM of (Pos.pos * string * int)
  | STR of (Pos.pos * string * string)
  | ENUM of (Pos.pos * string * string)

let declpos decl = match decl with
     NUM (pos, _name, _val) -> pos
   | STR (pos, _name, _val) -> pos
   | ENUM (pos, _name, _val) -> pos

let declname decl = match decl with
     NUM (_pos, name, _val) -> name
   | STR (_pos, name, _val) -> name
   | ENUM (_pos, name, _val) -> name

let collect decls =
   let doadd tbl decl =
      let pos = declpos decl in
      let name = declname decl in
      if Types.StringMap.mem name tbl then begin
         Pos.sayat pos ("Duplicate definition of " ^ name);
         Util.fail ()
      end;
      Types.StringMap.add name decl tbl
   in
   let tbl = List.fold_left doadd Types.StringMap.empty decls in
   let get name dfl =
      try
         Types.StringMap.find name tbl
      with Not_found ->
         Util.say ("misc.def: No definition of " ^ name);
         Util.fail ();
         dfl
   in
   let getint name dfl =
      match (get name (NUM (Pos.builtin, name, dfl))) with
           NUM (_pos, _name, value) -> ( (*pos,*) value)
         | decl ->
              let pos = declpos decl in
              Pos.sayat pos ("Expected number");
              Util.fail();
              ( (*pos,*) dfl)
   in
   let getstr name dfl =
      match (get name (STR (Pos.builtin, name, dfl))) with
           STR (_pos, _name, value) -> ( (*pos,*) value)
         | decl ->
              let pos = declpos decl in
              Pos.sayat pos ("Expected number");
              Util.fail();
              ( (*pos,*) dfl)
   in
   let getenum name f dfl dfl2 =
      match (get name (ENUM (Pos.builtin, name, dfl2))) with
           ENUM (pos, _name, value) -> ( (*pos,*) f pos value dfl)
         | decl ->
              let pos = declpos decl in
              Pos.sayat pos ("Expected identifier");
              Util.fail();
              ( (*pos,*) dfl)
   in

   {
      T.endianness = (getenum "endianness" checkendian T.BIG "");
      T.intencoding = (getenum "intencoding" checkenc T.TWOS_COMPLEMENT "");

      T.bytewidth = (getint "bytewidth" 8);
      T.addresswidth = (getint "addresswidth" 32);
      T.maximumwidth = (getint "maximumwidth" 64);

      T.pcunitwidth = (getint "pcunitwidth" 32);

      T.align = (getenum "alignwith" checkalign T.ALIGN_LOGVALUE "");
      T.commalign = (getenum "commalignwith" checkalign T.ALIGN_LOGVALUE "");
      T.maxalign = (getint "maxalign" 2);
      T.text_alignment = (getint "text_alignment" 4);     
      T.rdata_alignment = (getint "rdata_alignment" 4);     
      T.data_alignment = (getint "data_alignment" 4);     
      T.bss_alignment = (getint "bss_alignment" 4);     

      T.temp_label_prefix = (getstr "temp_label_prefix" ".L");
      T.entry_sym = (getstr "entry_sym" "__start");
      T.default_textorg = (getint "default_textorg" 0x00400000);
      (* XXX shouldn't there be a default_rdataorg? *)
      T.default_dataorg = (getint "default_dataorg" 0);
      T.default_bssorg = (getint "default_bssorg" 0);
      T.pagesize = (getint "pagesize" 4096);

      T.elf_machine = (getstr "elf_machine" "ENIAC");
      T.elf_use_rela = (getenum "elf_use_rela" checkbool false "");
      T.elf_use_r_ext = (getenum "elf_use_r_ext" checkbool false "");

      T.do_reginfo = (getenum "do_reginfo" checkbool false "");
   }

%}

%token EOF
%token <int> NUMBER
%token <string> QSTRING IDENT
%token COLON EQ SEMIC

%type <Misctree.info> file

%start file

%%

file:
   decls EOF			{ collect (List.rev $1) }
;

/*
 * Declarations
 */

decls: /* built in reverse order */
     decl		{ [$1] }
   | decls decl		{ $2 :: $1 }
;

decl:
     IDENT EQ NUMBER SEMIC	{ NUM (pos (), $1, $3) }
   | IDENT EQ QSTRING SEMIC	{ STR (pos (), $1, $3) }
   | IDENT COLON IDENT SEMIC	{ ENUM (pos (), $1, $3) }
;

%%
