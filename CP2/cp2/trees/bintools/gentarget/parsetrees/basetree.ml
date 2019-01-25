(*
 * Copyright (c) 2017, 2018
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
 * Base definitions for machine descriptions.
 *
 * This file declares types that are used elsewhere in the description.
 * The following types are built in:
 *
 *    bool
 *    string
 *    int(width)
 *    uint(width)
 *    zeros(width)
 *    ones(width)
 *
 * New types can be declared here as follows:
 *    enumerated types
 *    compound types
 *
 * Other things that can be declared here:
 *    operand tags
 *    "shortnames" for operand tags
 *
 * An enumerated type has a width as well as a list of identifiers that
 * are the enumeration constants, some of which may be _. The identifiers
 * can be explicitly assigned values, or autonumbered.
 *
 * A compound type is basically a tuple with a constructor name: the
 * name of the type is also the constructor name, and there are then
 * one or more elements of other types. There aren't sums, or records
 * with field names, since no compelling use case for them in any
 * description has appeared yet.
 *
 * Only types with widths can appear in instruction encodings.
 * (The "zeros" and "ones" types, which have one value for the given
 * width, exist specifically to allow handling constant instruction
 * fields in a tidy fashion.)
 *
 * The "expression of T" type means a value that appears at runtime
 * in the assembler as expression abstract syntax, which produces a
 * T when evaluated. Only integer types may be used as T, and, maybe,
 * booleans -- assembler-level expressions are basically address
 * arithmetic.
 *
 * Operand tags are the syntactic classification scheme for operands.
 * Based on syntactic rules (appearing elsewhere) each operand in the
 * assembler input is tagged. This identifies what kind of operand it
 * is, which is then used when matching instruction signatures.
 *
 * Operand tags are not types, though they have some of the properties
 * of types and each one has a type attached to it (which is the type
 * of the operand's value).
 *
 * A shortname is a shorter form of an operand tag name that can be
 * used in certain contexts. Mostly this is for making mangled names
 * in the output shorter, but for now at least shortnames can also be
 * used as shorthand in opmatch.def.
 *)

open Typetree

type decl =
                 (* definedat name width members *)
     ENUMTYPE of Pos.pos * string * int *
			(Pos.pos * string * int option) list
                 (* definedat name basetype formatstring *)
   | WRAPTYPE of Pos.pos * string * typename * string
   | COMPOUNDTYPE of Pos.pos * string * (Pos.pos * typename) list
                 (* definedat longname underlying-type *)
   | OPERANDTAG of Pos.pos * string * typename
                 (* definedat shortname longname *)
   | SHORTNAME of Pos.pos * string * string
