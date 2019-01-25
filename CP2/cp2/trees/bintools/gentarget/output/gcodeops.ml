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
 * Functions for emitting gcode.
 *)

open Gcode

(*
 * tools
 *)

let expr_of_pat pat = match pat with
     WRITEVAR (t, x) -> READVAR (t, x)
   | WRITEFIELD (t, e, field) -> READFIELD (t, e, field)
   | WRITEPOINTER (t, e) -> READPOINTER (t, e)

(*
 * constant wrappers
 *)

let intconstant k = INTCONSTANT (INT, string_of_int k)
let uintconstant k = INTCONSTANT (UINT, string_of_int k)
let longconstant k = INTCONSTANT (LONG, string_of_int k)
let ulongconstant k = INTCONSTANT (ULONG, string_of_int k)
let longlongconstant k = INTCONSTANT (LONGLONG, string_of_int k)
let ulonglongconstant k = INTCONSTANT (ULONGLONG, string_of_int k)

let intconstant' k = INTCONSTANT (INT, Types.Wide.to_string k)
let uintconstant' k = INTCONSTANT (UINT, Types.Wide.to_string k)
let longconstant' k = INTCONSTANT (LONG, Types.Wide.to_string k)
let ulongconstant' k = INTCONSTANT (ULONG, Types.Wide.to_string k)
let longlongconstant' k = INTCONSTANT (LONGLONG, Types.Wide.to_string k)
let ulonglongconstant' k = INTCONSTANT (ULONGLONG, Types.Wide.to_string k)

let typedintconst t k = INTCONSTANT (t, string_of_int k)
let typedintconst' t k = INTCONSTANT (t, Types.Wide.to_string k)

(*
 * operator wrappers 
 *)

let uop op t e = CALL (t, CALLOP op, [e])
let bop op t e1 e2 = CALL (t, CALLOP op, [e1; e2])
let ternop op t e1 e2 e3 = CALL (t, CALLOP op, [e1; e2; e3])

(* basic *)
let add = bop ADD
let sub = bop SUB 
let mul = bop MUL
let div = bop DIV
let mod = bop MOD
let neg = uop NEG
let lshift = bop LSHIFT
let rshift = bop RSHIFT
let bitand = bop BITAND
let bitor = bop BITOR
let bitxor = bop BITXOR
let bitnot = uop BITNOT
let eq = bop EQ
let lt = bop LT
let logand = bop LOGAND
let logor = bop LOGOR
let lognot = uop LOGNOT
let cond = ternop COND
let addrof = uop ADDROF
let ppdefined = uop PPDEFINED

(* compound *)
let neq t e1 e2 = lognot BOOL (eq t e1 e2)
let gt t e1 e2 = lt t e2 e1
let lteq t e1 e2 = lognot t (gt e1 e2)
let gteq t e1 e2 = lognot t (lt e1 e2)

(* expr *)
let call t func args = CALL (t, CALLFUNC func, args)
let readvarfield t'field t'x x field =
   READFIELD (t'field, READVAR (t'x, x), field)

(* stmt *)
let assignvar t x e = ASSIGN (WRITEVAR (t, x), e)
let assignptr t e1 e2 = ASSIGN (WRITEPOINTER (POINTER t, x), e)
let incr pat =
   let e = expr_of_pat pat in
   let t'e = gtype_of_expr e in
   ASSIGN (pat, add t'e e (typedintconst t'e 1))
let decr pat =
   let e = expr_of_pat pat in
   let t'e = gtype_of_expr e in
   ASSIGN (pat, sub t'e e (typedintconst t'e 1))
