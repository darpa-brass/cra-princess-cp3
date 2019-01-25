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
 * Common internal representation for types.
 *)

let builtin_plaintypes = Types.StringSet.of_list [
   "bool";
   "string";
]
let builtin_argtypes = Types.StringSet.of_list [
   "int";
   "uint";
   "zeros";
   "ones";
]

type typename =
     PLAINTYPE of string
   | WIDTHTYPE of string * int
   | EXPRTYPE of typename (* expression returning t *)
   | LISTTYPE of typename
   | TMPTYPE of int  (* scratch types used during inference only *)

(* dump *)
let rec dump'typename ty = match ty with
     PLAINTYPE name -> name
   | WIDTHTYPE (name, arg) -> name ^ "(" ^ string_of_int arg ^ ")"
   | EXPRTYPE ty1 -> "expr(" ^ dump'typename ty1 ^ ")"
   | LISTTYPE ty1 -> "[" ^ dump'typename ty1 ^ "]"
   | TMPTYPE k -> ".tmp" ^ string_of_int k

let booltype = PLAINTYPE "bool"
let stringtype = PLAINTYPE "string"

(*
 * XXX: should change these to use base types based on the minimum widths
 * guaranteed in the standard, instead of explicit widths where the value
 * of the type being that width is negligible.
 *
 * XXX: these are currently cutpasted in gtoc.ml because of subdir access
 * restrictions. this whole thing needs to be improved anyway...
 *)

let inttype width =
   if width <= 8 then "int8_t"
   else if width <= 16 then "int16_t"
   else if width <= 32 then "int32_t"
   else if width <= 64 then "int64_t"
   else Util.crash ("typerep: too wide inttype " ^ string_of_int width)

let uinttype width =
   if width <= 8 then "uint8_t"
   else if width <= 16 then "uint16_t"
   else if width <= 32 then "uint32_t"
   else if width <= 64 then "uint64_t"
   else Util.crash ("typerep: too wide uinttype " ^ string_of_int width)
