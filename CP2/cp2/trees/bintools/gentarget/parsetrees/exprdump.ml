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

module T = Typedump

open Dumptools
open Exprtree

let dump'uop op = match op with
     PLUS -> "+"
   | NEG -> "-"
   | LOGNOT -> "!"
   | BITNOT -> "~"
   | EVAL -> "eval"
   | UNEVAL -> "uneval"
   | CONSTP -> "constantp"
   | DEFINEDP -> "definedp"
   | ORD -> "ord"

let dump'bop op = match op with
     BITOR -> "|"
   | BITXOR -> "^"
   | BITAND -> "&"
   | LOGOR -> "||"
   | LOGXOR -> "^^"
   | LOGAND -> "&&"
   | SHL -> "<<"
   | SHR -> ">>"
   | EQ -> "=="
   | NEQ -> "!="
   | IN -> "in"
   | NOTIN -> "notin"
   | LT -> "<"
   | LTEQ -> "<="
   | ADD -> "+"
   | SUB -> "-"
   | MUL -> "*"
   | DIV -> "/"
   | MOD -> "%"
   | STRCAT -> "++"

let rec dump'expr e =
  match e with
     UOP (pos, op, e1) ->
        heading' "UOP" (dump'uop op) pos @
        indent (dump'expr e1)
   | BOP (pos, e1, op, e2) ->
        heading' "BOP" (dump'bop op) pos @
        indent (dump'expr e1) @
        indent (dump'expr e2)
   | FITS (pos, e1, ty) ->
        heading "FITS" pos @
        field "expr" (dump'expr e1) @
        field "type" (T.dump'typename ty)
   | MODE (pos, name) ->
        heading' "MODE" name pos
   | READVAR (pos, name) ->
        heading' "READVAR" name pos
   | READMEMBER (pos, e1, name) ->
        heading' "READMEMBER" name pos @
        field "expr" (dump'expr e1)
   | BOOLCONSTANT (pos, k) ->
        heading' "BOOLCONSTANT" (string_of_bool k) pos
   | NUMCONSTANT (pos, k) ->
        heading' "NUMCONSTANT" (string_of_int k) pos
   | STRCONSTANT (pos, k) ->
        heading' "NUMCONSTANT" k pos
   | HERE pos ->
        heading "HERE" pos
   | LIST (pos, elems) ->
        let sizestr = "(" ^ string_of_int (List.length elems) ^ " items)" in
        heading' "LIST" sizestr pos @
        indent (list' dump'expr elems)
   | MODIFIER (pos, name, args) ->
        heading' "MODIFIER" name pos @
        indent (list' dump'expr args)
   | PACK (pos, ty, args) ->
        heading' "PACK" ty pos @
        indent (list' dump'expr args)
   | CAST (pos, outty, inty, e1) ->
        heading "CAST" pos @
        field "to-type" (T.dump'typename outty) @
        field "from-type" (T.dump'typename inty) @
        field "expr" (dump'expr e1)
   | ANNOTATE (pos, ty, e1) ->
        heading "ANNOTATE" pos @
        field "type" (T.dump'typename ty) @
        field "expr" (dump'expr e1)

