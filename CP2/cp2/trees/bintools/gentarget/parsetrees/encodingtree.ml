(*
 * Copyright (c) 2016
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
 * The encoding.def file defines three kinds of things:
 *    fields (name, type)
 *    forms (name, list of field names)
 *    encodings (name, operands, args, cases)
 *)

(* Use the common type and expression infrastructure *)
include Typetree
include Exprtree

type pattern =
     SETVAR of Pos.pos * string
   | UNPACK of Pos.pos * string * pattern list

type fieldref =
     FIELDREF_ of Pos.pos * string * typename option * int option

type param = (Pos.pos * string * typename option)
type insn = INSN of Pos.pos * string * param list * param list

type statement =
     ASSIGN of Pos.pos * pattern * expr
   | ENCODE of Pos.pos * insn * expr option * statement list
   | MACRO of Pos.pos * insn * expr option * statement list
   | IF of Pos.pos * expr * statement list * statement list
   | USE of Pos.pos * string * expr list * expr list
   | WARN of Pos.pos * string

type enumtype =
   ENUMTYPE of Pos.pos * int * (Pos.pos * string * int option) list

type decl =
     FIELD of Pos.pos * string * typename * int option
   | ENUMFIELD of Pos.pos * string * enumtype * int option
   | SUBENUM of Pos.pos * string * string list
   | SUBENUMEXPR of Pos.pos * string * expr
   | FORM of Pos.pos * fieldref list * statement list

