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
 * The relocs.def file defines some basics:
 *    - the ELF machine type, the EM_* symbol from elf.h (e.g. EM_MIPS);
 *    - the relocation style (Rel vs. RelA) output by the assembler by
 *      default;
 *
 * and the rest is about relocations:
 *    - fields used in the relocation declarations
 *    - relocation names and codes and semantics
 *    - "magic" transformations on relocs
 *    - relocation grouping for insane cpus
 *
 * Note that these additional basic elf info things emitted into elfdefs.h
 * are derived from other configuration:
 *    - the "class" (ELFCLASS32 vs. ELFCLASS64), aka the machine word size
 *    - the endianness (ELFDATA2MSB vs. ELFDATA2LSB)
 *
 * In the long run the endianness shouldn't be compiled in for biendian
 * machines, but we can't do that yet. (XXX)
 *
 * Also in the long run I'm not sure it makes sense to have separate
 * 32-bit and 64-bit configs for some machines, in which case that
 * should also be determined on the fly.
 *
 * Note that if you pick an invalid machine symbol it won't be
 * detected until you try to compile the output against elf.h and that
 * fails.  Maybe the list should be built into the generator... but it
 * doesn't seem worthwhile, and having separate copies in the code
 * generator and in elf.h seems like a bad plan.
 *)

type relocstyles = REL | RELA
type howmany = ONE | MANY | MANYATONCE

(* use the common type and expression trees *)
include Typetree
include Exprtree

(* XXX rename to SETVAR/SETFIELD *)
type pattern =
     WRITEVAR of Pos.pos * string
   | WRITEFIELD of Pos.pos * pattern * string
   | UNPACK of Pos.pos * string * pattern list

type statement =
     ASSIGN of Pos.pos * pattern * expr
   | IF of Pos.pos * expr * statement list * statement list
   | WARN of Pos.pos * string
   | REQUIRE of Pos.pos * expr
   | BLOCK of statement list

type relocfield = {
   name: string;
   extname: string; (* field in encodings.def, if different *)
   definedat: Pos.pos;

   frominstruction: bool;
   readop: statement list;
   writeop: statement list;
   typename: typename option;
}

type modifierdecl = {
   name: string;
   definedat: Pos.pos;

   arg: string;
   block: statement list
}

type op = {
   name: string;
   definedat: Pos.pos;

   computation: statement list;
}

type codesemantics =
     NOP
   | UNSUPPORTED
                (* op *) (* fields *)  (* cangenerate *)
   | APPLYIN of string * string list * bool

type code = {
   name: string;
   definedat: Pos.pos;

   value: int option;
   semantics: codesemantics;
}

type substitution = {
   definedat: Pos.pos;
   binfmt: string;
   guard: expr;
   body: (Pos.pos * string(*var*) * expr(*extval*) * expr(*intval*)) list;
}

type groupdecl =
     GD_MATCH of Pos.pos * howmany * expr * string
   | GD_WHENINPUT of Pos.pos * expr
   | GD_WHENOUTPUT of Pos.pos * expr
   | GD_ORDER of Pos.pos * string list
   | GD_INPUT of Pos.pos * statement list
   | GD_OUTPUT of Pos.pos * statement list
   | GD_RESOLVE of Pos.pos * statement list

type grouping = {
   definedat: Pos.pos;
   binfmt: string;
   groupdecls: groupdecl list;
}

type decl =
     D_FIELD of relocfield
   | D_MODIFIER of modifierdecl
   | D_OP of op
   | D_CODES of Pos.pos * string(*binfmt*) * code list
   | D_SUBST of substitution
   | D_GROUP of grouping
(* XXX
   | D_MACHINE of Pos.pos * string
   | D_RELOCSTYLE of Pos.pos * relocstyles
*)
