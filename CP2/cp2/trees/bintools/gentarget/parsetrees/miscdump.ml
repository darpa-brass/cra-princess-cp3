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

open Dumptools
open Misctree

let dump'endian e = match e with
     BIG -> "big"
   | LITTLE -> "little"

let dump'intencoding i = match i with
     TWOS_COMPLEMENT -> "two's complement"
   | ONES_COMPLEMENT -> "one's complement"
   | SIGN_MAGNITUDE -> "sign-magnitude"

let dump'alignwith aw = match aw with
     ALIGN_LOGVALUE -> "logvalue"
   | ALIGN_VALUE -> "value"

let dump'info info =
   ["INFO"] @
   shortfield "endianness" (dump'endian info.endianness) @
   shortfield "intencoding" (dump'intencoding info.intencoding) @
   shortfield "bytewidth" (string_of_int info.bytewidth) @
   shortfield "addresswidth" (string_of_int info.addresswidth) @
   shortfield "maximumwidth" (string_of_int info.maximumwidth) @
   shortfield "pcunitwidth" (string_of_int info.pcunitwidth) @
   shortfield "align" (dump'alignwith info.align) @
   shortfield "commalign" (dump'alignwith info.commalign) @
   shortfield "maxalign" (string_of_int info.maxalign) @
   shortfield "text_alignment" (string_of_int info.text_alignment) @
   shortfield "rdata_alignment" (string_of_int info.rdata_alignment) @
   shortfield "data_alignment" (string_of_int info.data_alignment) @
   shortfield "bss_alignment" (string_of_int info.bss_alignment) @
   shortfield "temp_label_prefix" info.temp_label_prefix @
   shortfield "entry_sym" info.entry_sym @
   shortfield "default_textorg" (string_of_int info.default_textorg) @
   shortfield "default_dataorg" (string_of_int info.default_dataorg) @
   shortfield "default_bssorg" (string_of_int info.default_bssorg) @
   shortfield "pagesize" (string_of_int info.pagesize) @
   shortfield "elf_machine" info.elf_machine @
   shortfield "elf_use_rela" (string_of_bool info.elf_use_rela) @
   shortfield "do_reginfo" (string_of_bool info.do_reginfo)

let dump info =
   String.concat "\n" (dump'info info)