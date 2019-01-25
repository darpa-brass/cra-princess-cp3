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
 * Common internal representation for expressions.
 *)

type op = EQ | IN | LT
  | STRCAT
  | ADD | SUB | MUL | DIV | MOD | NEG
  | SHL | SHR
  | BITAND | BITOR | BITXOR | BITNOT
  | LOGAND | LOGOR | LOGXOR | LOGNOT
  | CONSTP | DEFINEDP
  | ORD

type const = 
    SMALL of int
  | LARGE of Types.Wide.t

type expr =
    CONST of Pos.pos * Typerep.typename * const
  | STRCONST of Pos.pos * Typerep.typename * string
  | USEVAR of Pos.pos * Typerep.typename * string
  | USEFIELD of Pos.pos * Typerep.typename * expr * string
  | OP of Pos.pos * Typerep.typename * op * expr list
  | FITS of Pos.pos * Typerep.typename * expr * Typerep.typename
  | MODE of Pos.pos * string
  | LIST of Pos.pos * Typerep.typename * expr list
  | MODIFIER of Pos.pos * Typerep.typename * string * expr list
  | PACK of Pos.pos * Typerep.typename * string * expr list
  | CAST of Pos.pos * Typerep.typename * Typerep.typename * expr
  | EVAL of Pos.pos * Typerep.typename
		* string (*field.relfield*) * int (*field.reloffset*)
		* Typerep.typename * expr
  | UNEVAL of Pos.pos * Typerep.typename * expr
  | ANNOTATE of Pos.pos * Typerep.typename * expr
  | COMMENTED of string * expr

(**************************************************************)
(* utility functions *)

let rec exprpos e = match e with
     CONST (pos, _t, _k) -> pos
   | STRCONST (pos, _t, _s) -> pos
   | USEVAR (pos, _t, _name) -> pos
   | USEFIELD (pos, _t, _e, _name) -> pos
   | OP (pos, _t, _op, _args) -> pos
   | FITS (pos, _t, _e, _argty) -> pos
   | MODE (pos, _name) -> pos
   | LIST (pos, _t, _elems) -> pos
   | MODIFIER (pos, _t, _opname, _args) -> pos
   | PACK (pos, _t, _ctor, _args) -> pos
   | CAST (pos, _nt, _ot, _e1) -> pos
   | EVAL (pos, _nt, _relname, _reloffset, _ot, _e1) -> pos
   | UNEVAL (pos, _t, _) -> pos
   | ANNOTATE (pos, _t, _e1) -> pos
   | COMMENTED (_, e1) -> exprpos e1

let rec exprtype e = match e with
     CONST (_, t, _k) -> t
   | STRCONST (_, t, _s) -> t
   | USEVAR (_, t, _name) -> t
   | USEFIELD (_, t, _e, _name) -> t
   | OP (_, t, _op, _args) -> t
   | FITS (_, t, _e, _argty) -> t
   | MODE (_, _name) -> Typerep.PLAINTYPE "bool"
   | LIST (_, t, _elems) -> t
   | MODIFIER (_, t, _opname, _args) -> t
   | PACK (_, t, _ctor, _args) -> t
   | CAST (_, nt, _ot, _e1) -> nt
   | EVAL (_, nt, _relname, _reloffset, _ot, _e1) -> nt
   | UNEVAL (_, t, _) -> t
   | ANNOTATE (_, t, _e1) -> t
   | COMMENTED (_, e1) -> exprtype e1

(**************************************************************)
(* dump *)

let dump'op op = match op with
     EQ -> "=="
   | IN -> "in"
   | LT -> "<"
   | STRCAT -> "++"
   | ADD -> "+"
   | SUB -> "-"
   | MUL -> "*"
   | DIV -> "/"
   | MOD -> "%"
   | NEG -> "-"
   | SHL -> "<<"
   | SHR -> ">>"
   | BITAND -> "&"
   | BITOR -> "|"
   | BITXOR -> "^"
   | BITNOT -> "~"
   | LOGAND -> "&&"
   | LOGOR -> "||"
   | LOGXOR -> "^^"
   | LOGNOT -> "!"
   | CONSTP -> "constantp"
   | DEFINEDP -> "definedp"
   | ORD -> "ord"

let rec dump'expr e = match e with
     CONST (_, t, SMALL k) -> string_of_int k ^ " :: " ^ Typerep.dump'typename t
   | CONST (_, t, LARGE k) -> Types.Wide.to_string k ^ " :: " ^ Typerep.dump'typename t
   | STRCONST (_, t, s) -> "\"" ^ s ^ "\" :: " ^ Typerep.dump'typename t
   | USEVAR (_, t, name) -> name ^ " :: " ^ Typerep.dump'typename t
   | USEFIELD (_, t, e1, name) -> dump'expr e1 ^ "." ^ name ^ " :: " ^ Typerep.dump'typename t
   | OP (_, t, op, es) ->
       let es' = List.map dump'expr es in
       let es'' = String.concat "), (" es' in
       dump'op op ^ "(" ^ es'' ^ ") :: " ^ Typerep.dump'typename t
   | FITS (_, t, e, argty) ->
       let e' = dump'expr e in
       "(" ^ e' ^ " fits " ^ Typerep.dump'typename argty ^ ") :: " ^ Typerep.dump'typename t
   | MODE (_, modename) ->
       "mode " ^ modename
   | LIST (_, t, es) ->
       let es' = List.map dump'expr es in
       let es'' = String.concat ", " es' in
       "[" ^ es'' ^ "] :: [" ^ Typerep.dump'typename t ^ "]"
   | MODIFIER (_, t, opname, args) ->
       let args' = List.map dump'expr args in
       let args'' = String.concat ", " args' in
       "modifier " ^ opname ^ "(" ^ args'' ^ ") :: [" ^ Typerep.dump'typename t ^ "]"
   | PACK (_, t, ctor, args) ->
       let args' = List.map dump'expr args in
       let args'' = String.concat ", " args' in
       "pack " ^ ctor ^ "(" ^ args'' ^ ") :: [" ^ Typerep.dump'typename t ^ "]"
   | CAST (_, nty, oty, e1) ->
       let e1' = dump'expr e1 in
       "cast(" ^ Typerep.dump'typename nty ^ " <= " ^ Typerep.dump'typename oty ^ ") " ^ e1'
   | EVAL (_, nty, relname, reloffset, oty, e1) ->
       let relinfo = " for reloc field " ^ relname ^ " at offset " ^
                     string_of_int reloffset
       in
       let e1' = dump'expr e1 in
       "eval (" ^ e1' ^ ") :: " ^ Typerep.dump'typename oty ^ relinfo ^
              " :: " ^ Typerep.dump'typename nty
   | UNEVAL (_, ty, e1) ->
       let e1' = dump'expr e1 in
       "@" ^ e1' ^ " :: " ^ Typerep.dump'typename ty
   | ANNOTATE (_, ty, e1) ->
       let e1' = dump'expr e1 in
       e1' ^ " <::> " ^ Typerep.dump'typename ty
   | COMMENTED (text, e1) ->
       let e1' = dump'expr e1 in
       e1' ^ " /* " ^ text ^ " */"

