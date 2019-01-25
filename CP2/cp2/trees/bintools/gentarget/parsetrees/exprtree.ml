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
 * Common expression parse tree.
 *
 * Uses the common typename parse tree in typetree.ml.
 *)

(* operators *)
type uop =
     PLUS
   | NEG
   | LOGNOT
   | BITNOT
   | EVAL (* not sure if this should be a uop or an expr case... *)
   | UNEVAL
   | CONSTP
   | DEFINEDP
   | ORD

type bop =
     BITOR
   | BITXOR
   | BITAND
   | LOGOR
   | LOGXOR
   | LOGAND
   | SHL
   | SHR
   | EQ
   | NEQ
   | IN
   | NOTIN
   | LT
   | LTEQ
   | ADD
   | SUB
   | MUL
   | DIV
   | MOD
   | STRCAT

(* expressions *)
type expr =
     UOP of Pos.pos * uop * expr
   | BOP of Pos.pos * expr * bop * expr
   | FITS of Pos.pos * expr * Typetree.typename
   | MODE of Pos.pos * string
   | READVAR of Pos.pos * string
   | READMEMBER of Pos.pos * expr * string (* not used in encodings *)
   | BOOLCONSTANT of Pos.pos * bool
   | NUMCONSTANT of Pos.pos * int
   | STRCONSTANT of Pos.pos * string (* not used in encodings *)
   | HERE of Pos.pos
   | LIST of Pos.pos * expr list
   | MODIFIER of Pos.pos * string * expr list
   | PACK of Pos.pos * string * expr list
   | CAST of Pos.pos * Typetree.typename * Typetree.typename * expr
   | ANNOTATE of Pos.pos * Typetree.typename * expr
