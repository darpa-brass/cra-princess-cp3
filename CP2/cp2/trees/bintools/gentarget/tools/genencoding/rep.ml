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
 * Internal representation.
 *)

include Typerep
include Exprrep

type pattern =
    SETVAR of Pos.pos * string
  | UNPACK of Pos.pos * string * pattern list

type assignment = (Pos.pos * pattern * expr)

type statement =
    ASSIGN of assignment
  | IF of (Pos.pos * expr * statement list * statement list)
  | USE of (Pos.pos * string * expr list * expr list * string (*mangled*) )
  | EMIT of (Pos.pos * expr)
  | HOOK of (Pos.pos * string * expr list)
  | WARN of (Pos.pos * string)

(*
 * declarations of various things
 *)

(*
 * The C-level manifestation of types gets somewhat complicated:
 * values of expression type appear at runtime as expression trees
 * (perhaps unsurprisingly) but so do values of coompound type, while
 * enumerations and enumerator constants (including register names)
 * are carried around as integers.
 *
 * For compound types the expression tree is syntactically decomposed
 * into more basic values; for expression types, the encoding
 * procedure evaluates the expression and possibly produces a
 * relocation.
 *)

type enum = {
    name: string;
    definedat: Pos.pos;
    width: int;
    seq: int;  (* sequence number; which enum *)
    (*
     * Values of enums should technically be consts, not plain ints;
     * but if we get a bitfield large enough for plain ints to not
     * have enough range, enumerating it is not very feasible.
     *)
    syms: (Pos.pos * string * int) list;
    symtovalue: int Types.StringMap.t;
    valuetosym: string array;
}

type compoundtype = {
    name: string;
    definedat: Pos.pos;
    members: (Pos.pos * typename) list;
}

(*
 * Operand tags are a syntactic matching tool; they are not types,
 * although they're related to types and have some of the same
 * properties as types.
 *
 * Above the encoding procedure level (e.g. for opmatch.def and all
 * language-level stuff) operands tagged differently are
 * distinguished, and most logic (e.g. signature matching) goes by
 * operand tags.
 *
 * An operand tag is a name (the "longname"); there's also a short
 * name, which is used to generate signature strings and thus for
 * function name mangling. (This short name is also currently exposed
 * in opmatch.def for legacy reasons -- that should get fixed
 * sometime.) Each operand tag also has a type associated with it,
 * which is the type of the operand value. Multiple operand tags can
 * produce values of the same type.
 *
 * Operand tags are syntactically significant (operands that are
 * syntactically the same should be tagged the same) but may not be
 * semantically significant. E.g. some assembly languages strongly
 * distinguish "symbols" and "expressions" and for some instructions
 * only a plain symbol is allowed, but the underlying type of both
 * is (probably) the same.
 *
 * Within the encoding logic, we no longer need to care about
 * syntactic issues and the operand tags are dropped.
 *)

type operandtag = {
    name: string;
    definedat: Pos.pos;

    basetype: typename;
}

type modifier = {
   name: string;
   definedat: Pos.pos;
   argtype: typename;
   resulttype: typename;
}

type field = {
    name: string;
    definedat: Pos.pos;
    ty: typename;
    relocatable: bool;		(* are relocations for this field? *)
    offset: int;		(* byte offset into instruction, often 0 *)
}

type form = {
    name: string;
    definedat: Pos.pos;
    fields: string list;
    types: typename list;
}

type subenum = {
    name: string;
    definedat: Pos.pos;

    enumname: string;
    values: Types.StringSet.t;
}

type encoding = {
    name: string;
    mangledname: string;
    definedat: Pos.pos;
    specargs: (Pos.pos * string * typename) list;
    opargs: (Pos.pos * string * typename) list;
    formname: string;
    alternatives: (Pos.pos * expr * statement list) list;
}

type macro = {
    name: string;
    mangledname: string;
    definedat: Pos.pos;
    specargs: (Pos.pos * string * typename) list;
    opargs: (Pos.pos * string * typename) list;
    expansions: (Pos.pos * expr * statement list) list;
}

type instruction = {
    name: string;
    definedat: Pos.pos;

    operands_ext: string list;    (* operand tags as seen in opmatch.def *)
    operands_int: typename list;  (* operand types as we use ourselves *)

    mangledname_ext : string; (* as issued by opmatch *)
    mangledname_int : string; (* as used internally *)

    encoder: string;
    encoder_mangled: string;
}

type endianness =
     LITTLE_ENDIAN
   | BIG_ENDIAN
(* XXX notyet: modes *)
(* | DYNAMIC_ENDIAN littlemode *)

type spec = {
    pcunitwidth: int;
    addresswidth: int;
    endian: endianness;
    do_reginfo: bool;

    enums: enum Types.StringMap.t;
    operandtags: operandtag Types.StringMap.t;
    compoundtypes: compoundtype Types.StringMap.t;

    modifiers: modifier Types.StringMap.t;

    fields: field Types.StringMap.t;
    forms: form Types.StringMap.t;

    subenums: subenum Types.StringMap.t;
    (*
     * These are lists because the same name can have multiple
     * forms with different operands... and also different guard
     * expressions.
     *)
    encodings: encoding list;
    macros: macro list;
    instructions: instruction list;
}

(**************************************************************)
(* dump *)

let dump'pos pos = Pos.string_of_pos pos

let dump'enum out _ { name; definedat; width; syms; symtovalue; valuetosym; } =
   output_string out ("enum " ^ name ^ " at " ^ dump'pos definedat ^ ":\n");
   output_string out ("   width " ^ string_of_int width ^ "\n");

   output_string out ("   syms:\n");
   let printsym (pos, n, v) =
      output_string out ("      " ^ n ^ " " ^ string_of_int v ^ " at " ^
			 dump'pos pos ^ "\n")
   in
   List.iter printsym syms;

   output_string out ("   symtovalue:\n");
   let printsv n v =
      output_string out ("      " ^ n ^ " ->  " ^ string_of_int v ^ "\n")
   in
   Types.StringMap.iter printsv symtovalue;

   output_string out ("   valuetosym:\n");
   for i = 0 to (Array.length valuetosym - 1) do
      output_string out ("      " ^ string_of_int i ^ ": " ^ Array.get valuetosym i ^
                 "\n")
   done

let dump'compoundtype out _ { name; definedat; members; } =
   let dump'typearg (pos, ty) =
      "      " ^ dump'typename ty ^ " at " ^ dump'pos pos ^ "\n"
   in
   output_string out ("compound type " ^ name ^ " at " ^
	dump'pos definedat ^ ":\n");
   let members' = List.map dump'typearg members in
   List.iter (output_string out) members'

let dump'operandtag out _ { name; definedat; basetype; } =
   output_string out ("operandtag " ^ name ^ " at " ^
                      dump'pos definedat ^ "\n");
   output_string out ("   basetype: " ^ dump'typename basetype ^ "\n")

let dump'field out _ { name; definedat; relocatable; offset; ty; } =
   let relinfo = match relocatable with
        false -> ""
      | true -> ": relfield " ^ name ^ " offset " ^ string_of_int offset
   in
   output_string out ("field " ^ name ^ " at " ^ dump'pos definedat ^
             ": " ^ dump'typename ty ^ relinfo ^ "\n")

let dump'form out _ { name; definedat; fields; types; } =
   output_string out ("form " ^ name ^ " at " ^ dump'pos definedat ^ ":\n");
   output_string out ("   fields:\n");
   let printfield f =
      output_string out ("      " ^ f ^ "\n")
   in
   List.iter printfield fields;
   output_string out ("   types:\n");
   let printtype t =
      output_string out ("      " ^ dump'typename t ^ "\n")
   in
   List.iter printtype types

let dump'subenum out _ { name; definedat; enumname; values; } =
   output_string out ("subenum " ^ name ^ " at " ^ dump'pos definedat ^
	      ":\n");
   output_string out ("   from enum " ^ enumname ^ ":\n");
   let printval s =
      output_string out ("      " ^ s ^ "\n")
   in
   Types.StringSet.iter printval values

let rec dump'pat p = match p with
     SETVAR (_pos, name) -> name
   | UNPACK (_pos, ctor, pats) ->
       let pats = String.concat ", " (List.map dump'pat pats) in
       ctor ^ "(" ^ pats ^ ")"

let dump'assignment out (_pos, pat, e) =
   output_string out ("      -> set " ^ dump'pat pat ^ " =\n");
   output_string out ("             " ^ dump'expr e ^ "\n")

let rec dump'statement out ms = match ms with
     ASSIGN (_pos, pat, e) ->
        output_string out ("      -> set " ^ dump'pat pat ^ " =\n");
        output_string out ("             " ^ dump'expr e ^ "\n")
   | IF (_pos, c, t, f) ->
       let c' = dump'expr c in
       (* XXX would be nice to have indent for this *)
       output_string out ("      -> if (" ^ c' ^ ")\n");
       List.iter (dump'statement out) t;
       output_string out ("         else\n");
       List.iter (dump'statement out) f;
   | USE (_pos, name, es, ops, resolvedname) ->
       let es' = List.map dump'expr es in
       let es'' = String.concat "), (" es' in
       let ops' = List.map dump'expr ops in
       let ops'' = String.concat ", " ops' in
       output_string out ("      -> use " ^ name ^ "(" ^ es'' ^ ") " ^
                          ops'' ^ " ~~> " ^ resolvedname ^ "\n")
   | EMIT (_pos, e) ->
       let e' = dump'expr e in
       output_string out ("      -> emit " ^ e' ^ "\n")
   | HOOK (_pos, name, args) ->
       let args' = String.concat "), " (List.map dump'expr args) in
       output_string out ("      -> hook " ^ name ^ " (" ^ args' ^ ")\n")
   | WARN (_pos, text) ->
       output_string out ("      -> warn " ^ text ^ "\n")

let dump'encoding out { name; mangledname; definedat; specargs; opargs;
			alternatives; } =
   output_string out ("encoding " ^ name ^ " (" ^ mangledname ^ ") at " ^
		      dump'pos definedat ^ ":\n");

   output_string out ("   specargs:\n");
   let print_specarg (_, name, t) =
      output_string out ("      " ^ name ^ " :: " ^ dump'typename t ^ "\n")
   in
   List.iter print_specarg specargs;

   output_string out ("   opargs:\n");
   let print_oparg (_, n, t) =
      output_string out ("      " ^ n ^ " :: " ^ dump'typename t ^ "\n")
   in
   List.iter print_oparg opargs;

   output_string out ("   alternatives:\n");
   let print_alt (_pos, e, block) =
      output_string out ("      " ^ dump'expr e ^ "\n");
      List.iter (dump'statement out) block
   in
   List.iter print_alt alternatives

let dump'macro out { name; mangledname; definedat; specargs; opargs;
		     expansions; } =
   output_string out ("macro " ^ name ^ " (" ^ mangledname ^ ") at " ^
		      dump'pos definedat ^ ":\n");

   output_string out ("   specargs:\n");
   let print_specarg (_pos, name, t) =
      output_string out ("      " ^ name ^ " :: " ^ dump'typename t ^ "\n")
   in
   List.iter print_specarg specargs;

   output_string out ("   opargs:\n");
   let print_oparg (_, n, t) =
      output_string out ("      " ^ n ^ " :: " ^ dump'typename t ^ "\n")
   in
   List.iter print_oparg opargs;

   output_string out ("   expansions:\n");
   let print_exp (_pos, e, block) =
      output_string out ("      " ^ dump'expr e ^ "\n");
      List.iter (dump'statement out) block
   in
   List.iter print_exp expansions

let dump'instruction out { name; definedat;
			   operands_ext; operands_int;
			   mangledname_ext; mangledname_int;
			   encoder; encoder_mangled; } =
   output_string out ("instruction " ^ name ^ " at " ^
		      dump'pos definedat ^ ":\n");
   output_string out ("   signature: " ^ mangledname_ext ^
                      " as " ^ mangledname_int ^ "\n");
   output_string out ("   operands:\n");
   let printop (longname, ty) =
      output_string out ("      " ^ longname ^ " as " ^
                         dump'typename ty ^ "\n")
   in
   List.iter printop (Util.zip operands_ext operands_int);

   output_string out ("   encoder: " ^ encoder ^ "\n");
   output_string out ("   signature: " ^ encoder_mangled ^ "\n")

let dump'spec out { pcunitwidth;
                    enums; compoundtypes; operandtags;
                    fields; forms; subenums;
                    encodings; macros; instructions; } =
   let iter = Types.StringMap.iter in
   output_string out ("pcunit width: " ^ string_of_int pcunitwidth ^ "\n");
   iter (dump'enum out) enums;
   iter (dump'compoundtype out) compoundtypes;
   iter (dump'operandtag out) operandtags;
   iter (dump'field out) fields;
   iter (dump'form out) forms;
   iter (dump'subenum out) subenums;
   List.iter (dump'encoding out) encodings;
   List.iter (dump'macro out) macros;
   List.iter (dump'instruction out) instructions

let dump name spec =
   let out = open_out ("genencoding-" ^ name ^ ".dump") in
   dump'spec out spec;
   close_out out
