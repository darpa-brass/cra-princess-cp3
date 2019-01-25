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

module G = Gcode
open Modetree

(**************************************************************)
(* targetmodes.h *)

let mk_targetmodes_h spec =
   let nmodes = string_of_int (List.length spec) in
   let def = G.DEFINE ("NUMMODES", Some (G.INTCONSTANT (G.INT, nmodes))) in
   G.FILE (Some "TARGETMODES_H", [], [def])

(**************************************************************)
(* targetmodes.c *)

let mk_unsuppfunc name =
   let args = [
      (G.UINT, "linenum");
      (G.BOOL, "val");
   ] in
   let call =
      G.voidcall "file_warn" [G.READVAR (G.UINT, "linenum");
                              G.STRINGCONSTANT (name ^ " not supported")]
   in

   let body = G.IF (G.READVAR (G.BOOL, "val"), G.BLOCK [call], G.BLOCK []) in

   G.FUNCTION (G.STATIC, G.VOID, name ^ "_mode", args, G.BLOCK [body])

let mk_targetmodes_c spec =
   let includes = [
      G.SYSINCLUDE "string.h";
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "assert.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "common.h";
      G.LOCALINCLUDE "modeinfo.h";
      G.LOCALINCLUDE "targetmodes.h";
   ] in

   let mk_func { name; (*definedat;*) modetype; } =
      match modetype with
           UNSUPPORTED -> [mk_unsuppfunc name]
         | _ -> []
   in
   let funcs = List.concat (List.map mk_func spec) in

   let mk_initializer { name; (*definedat;*) modetype; } =
      let null = G.READVAR (G.POINTER G.VOID, "NULL") in
      let setfunc, defval = match modetype with
           UNSUPPORTED -> G.READVAR (G.VOID(*XXX*), name ^ "_mode"), false
         | DEFAULT_OFF -> null, false
         | DEFAULT_ON -> null, true
      in

      G.INITSTRUCT [
         ("name", G.INITSCALAR (G.STRINGCONSTANT name));
         ("setfunc", G.INITSCALAR setfunc);
         ("defval", G.INITSCALAR (G.boolconst defval));
      ]
   in

   let initializers =
      List.map mk_initializer spec
   in
   let init = G.INITARRAY initializers in

   let ty'table = G.CONST (G.ARRAY (G.STRUCTTYPE "modeinfo", "NUMMODES")) in
   let table = G.VARDECL' (G.GLOBAL, ty'table, "modeinfo", init) in

   G.FILE (None, includes, funcs @ [table])

(**************************************************************)
(* toplevel *)

let mkmodes spec =
   let targetmodes_h = mk_targetmodes_h spec in
   let targetmodes_c = mk_targetmodes_c spec in
   (targetmodes_h, targetmodes_c)
