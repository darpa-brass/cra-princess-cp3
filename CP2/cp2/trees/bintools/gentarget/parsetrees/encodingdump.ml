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

(* dump for Encodingtree *)

open Dumptools
open Encodingtree

(**************************************************************)
(* main recursion *)

let dump'typename ty =
   Typedump.dump'typename ty

(*
let dump'uop op = match op with
     PLUS -> "+"
   | NEG -> "-"
   | LOGNOT -> "!"
   | BITNOT -> "~"
   | EVAL -> "eval"
   | UNEVAL -> "uneval"

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

let rec dump'expr e = match e with
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
        field "type" (dump'typename ty)
   | MODE (pos, name) ->
        heading' "MODE" name pos
   | READVAR (pos, name) ->
        heading' "READVAR" name pos
   | READMEMBER (pos, e1, name) ->
        heading' "READMEMBER" name pos @
        field "exr" (dump'expr e1)
   | BOOLCONSTANT (pos, k) ->
        heading' "BOOLCONSTANT" (string_of_bool k) pos
   | NUMCONSTANT (pos, k) ->
        heading' "NUMCONSTANT" (string_of_int k) pos
   | STRCONSTANT (pos, k) ->
        heading' "STRCONSTANT" k pos
   | HERE pos ->
        heading "HERE" pos
   | LIST (pos, elems) ->
        heading "LIST" pos @
        indent (list' dump'expr elems)
   | MODIFIER (pos, name, args) ->
        heading' "MODIFIER" name pos @
        indent (list' dump'expr args)
   | PACK (pos, ty, args) ->
        heading' "PACK" ty pos @
        indent (list' dump'expr args)
   | CAST (pos, outty, inty, e1) ->
        heading "CAST" pos @
        field "to-type" (dump'typename outty) @
        field "from-type" (dump'typename inty) @
        field "expr" (dump'expr e1)
   | ANNOTATE (pos, ty, e1) ->
        heading "ANNOTATE" pos @
        field "type" (dump'typename ty) @
        field "expr" (dump'expr e1)
*)
let dump'expr e =
   Exprdump.dump'expr e

let dump'optexpr oe = match oe with
     None -> ["(none)"]
   | Some e -> dump'expr e

let rec dump'pattern pat = match pat with
     SETVAR (pos, name) ->
        heading' "SETVAR" name pos
   | UNPACK (pos, ty, pats) ->
        heading' "UNPACK" ty pos @
        indent (list' dump'pattern pats)

let dump'fieldref fr = match fr with
   FIELDREF_ (pos, name, opty, optval) ->
      heading' "FIELD" name pos @ indent ((
         match opty with
              None -> []
            | Some ty -> [" :: "] @ dump'typename ty
      ) @ (
         match optval with
              None -> []
            | Some v -> [" = "; string_of_int v]
      ))

let dump'param param =
   let (_pos, name, opttype) = param in
   [name] @ match opttype with
        None -> []
      | Some ty -> field "::" (dump'typename ty)

let dump'insn insn = match insn with
     INSN (pos, name, args, ops) ->
        heading' "INSN" name pos @
        field "args" (list' dump'param args) @
        field "ops" (list' dump'param ops)

let rec dump'stmt s = match s with
     ASSIGN (pos, pat, e) ->
        heading "ASSIGN" pos @
        field "pattern" (dump'pattern pat) @
        field "expr" (dump'expr e)
   | ENCODE (pos, insn, guard, stmts) ->
        heading "ENCODE" pos @
        field "insn" (dump'insn insn) @
        field "guard" (dump'optexpr guard) @
        field "stmts" (list dump'stmt stmts)
   | MACRO (pos, insn, guard, stmts) ->
        heading "MACRO" pos @
        field "insn" (dump'insn insn) @
        field "guard" (dump'optexpr guard) @
        field "stmts" (list dump'stmt stmts)
   | IF (pos, cond, ts, fs) ->
        heading "IF" pos @
        field "cond" (dump'expr cond) @
        field "true" (list dump'stmt ts) @
        field "false" (list dump'stmt fs)
   | USE (pos, name, args, ops) ->
        heading' "USE" name pos @
        field "args" (list dump'expr args) @
        field "ops" (list dump'expr ops)
   | WARN (pos, text) ->
        heading' "WARN" text pos

let dump'enummember m =
   let (_pos, name, optval) = m in
   name ^ match optval with
        None -> ""
      | Some n -> " = " ^ string_of_int n

let dump'enumtype ty = match ty with
     ENUMTYPE (pos, width, members) ->
        heading' "ENUMTYPE" (string_of_int width) pos @
        indent (List.map dump'enummember members)

let dump'decl d = match d with
     FIELD (pos, name, ty, opt_relinfo) ->
        heading' "FIELD" name pos @
        field "type" (dump'typename ty) @
        shortfield "relinfo" (
           match opt_relinfo with
                None -> "(none)"
              | Some reloffset ->
                   "offset " ^ string_of_int reloffset
        )
   | ENUMFIELD (pos, name, ty, opt_relinfo) ->
        heading' "ENUMFIELD" name pos @
        field "type" (dump'enumtype ty) @
        shortfield "relinfo" (
           match opt_relinfo with
                None -> "(none)"
              | Some reloffset ->
                   "offset " ^ string_of_int reloffset
        )
   | SUBENUM (pos, name, items) ->
        heading' "SUBENUM" name pos @
        indent items
   | SUBENUMEXPR (pos, name, e) ->
        heading' "SUBENUMEXPR" name pos @
        indent (dump'expr e)
   | FORM (pos, fieldrefs, stmts) ->
        heading "FORM" pos @
        field "fieldrefs" (list dump'fieldref fieldrefs) @
        field "statements" (list dump'stmt stmts)

(**************************************************************)
(* top level *)

let dump decls =
   String.concat "\n" (List.concat (List.map dump'decl decls))

