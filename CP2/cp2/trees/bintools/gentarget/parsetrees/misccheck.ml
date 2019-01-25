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

open Misctree


let checkwidth w what =
   if w <= 0 || w > Types.maxintwidth then begin
(*
      Pos.sayat pos ("Invalid " ^ what ^ " " ^ string_of_int w);
*)
      Util.say ("misc.def: Invalid " ^ what ^ " " ^ string_of_int w);
      Util.fail ();
   end

let checkrange w n what =
   if Types.Wide.ge (Types.Wide.of_int n) (Types.Wide.twoN w) then begin
(*
      Pos.sayat pos ("Out of range " ^ what ^ " " ^ string_of_int n);
*)
      Util.say ("misc.def: Out of range " ^ what ^ " " ^ string_of_int n);
      Util.fail ();
   end

let check info =
   checkwidth info.bytewidth "bytewidth";
   checkwidth info.addresswidth "addresswidth";
   checkwidth info.maximumwidth "maximumwidth";
   checkwidth info.pcunitwidth "pcunitwidth";
   checkwidth info.maxalign "maxalign";
   checkwidth info.text_alignment "alignment";
   checkwidth info.rdata_alignment "alignment";
   checkwidth info.data_alignment "alignment";
   checkwidth info.bss_alignment "alignment";
   checkrange info.addresswidth info.default_textorg "default_textorg";
   checkrange info.addresswidth info.default_dataorg "default_dataorg";
   checkrange info.addresswidth info.default_bssorg "default_bssorg";
   checkrange info.addresswidth info.pagesize "pagesize";
   info
