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
 * Internal representation.
 *)


include Typerep
include Exprrep

type pattern =
    SETVAR of Pos.pos * string
  | SETFIELD of Pos.pos * expr * string
  | UNPACK of Pos.pos * string * pattern list

type assignment = (Pos.pos * pattern * expr)

type statement =
    ASSIGN of assignment
  | IF of (Pos.pos * expr * statement * statement)
  | WARN of (Pos.pos * string)
  | REQUIRE of (Pos.pos * expr)
  | BLOCK of statement list


(*
 * The various kinds of declarations
 *)


(* encoding-level field from encodings.def *)
type encfield = {
    name: string;
    definedat: Pos.pos;
    canuse: bool;
    ty: typename;
    bitpos: int;		(* bit position field starts at *)
    (*
     * Byte offset into instruction. This is applied by altering the
     * offset recorded in the output object file, by adding this amount
     * to the address at which the instruction (or data item) began.
     * Usually this should be zero as most instruction field relocations
     * are defined such that the relocation entry should point at the
     * instruction beginning. Currently it is only used for some mips
     * relocations and there it's wrong. Arguably it should be removed.
     * (XXX)
     *)
    offset: int;		(* byte offset into instruction, often 0 *)
}

(* instruction form from encodings.def *)
type form = {
    name: string;
    definedat: Pos.pos;
    fields: string list;
    types: typename list;
}

(* modifier *)
type modifier = {
   name: string;
   definedat: Pos.pos;
   argname: string;
   argtype: typename;
   symname: string;
   resulttype: typename;
   semantics: statement list;
}

(* relocation-level field from relocs.def *)
type relocfield = {
   fieldname: string;		(* internal name *)
   extfieldname: string;	(* name in encodings.def *)
   definedat: Pos.pos;

   symname: string;		(* enumeration name in output *)
   input: statement list;
   output: statement list;

   ty: typename;
   frominstruction: bool;
}

(* relocation operation *)
type operation = {
   opername: string;
   definedat: Pos.pos;

   actions: statement list;
}

(* relocation code *)
type codebehavior =
     NOP
   | UNSUPPORTED
                (* op *) (* fields *)  (* dogenerate *)
   | APPLYIN of string * string list * bool

type code = {
   symname: string;
   definedat: Pos.pos;
   num: int;
   behavior: codebehavior;
}

(* complete spec *)
type spec = {
   addresswidth: int;
   pcunitwidth: int;
   compoundtypes: (Pos.pos * typename) list Types.StringMap.t;
   encfields: encfield Types.StringMap.t;
   modifiers: modifier list;
   relocfields: relocfield list;
   operations: operation list;
   allcodes: (code list) Types.StringMap.t; (* binary format -> code table *)
}
