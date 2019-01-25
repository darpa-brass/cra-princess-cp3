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
 * Abstract representation for C code. This contains only what we need,
 * not the full language.
 *)

type op =
     ADD | SUB | MUL | DIV | MOD | NEG
   | LSHIFT | RSHIFT
   | BITAND | BITOR | BITXOR | BITNOT
   | EQ | LT | GT | LTEQ | GTEQ
   | LOGAND | LOGOR | LOGNOT
   | COND
   | ADDROF

type ctype =
     VOID
   | INT | UINT | LONG | ULONG | LONGLONG | ULONGLONG
   | NAMEDTYPE of string
   | ARRAYTYPE of ctype * string
   | ANONSTRUCT of (ctype * string) list
   | ANONUNION of (ctype * string) list

type expr =
     CONSTANT of string
   | READVAR of string
   | OP of (op * expr list)
   | CALL of (string * expr list)
   | GETFIELD of (expr * string) (* -> *) (* XXX better names please *)
   | GETFIELD' of (expr * string) (* . *)
   | GETARRAY of (expr * expr) (* [] *)
   | GETPOINTER of expr (* * *)
   | CAST of (ctype * expr)
   | SIZEOF of ctype
   | COMMENTED of (string * expr)

type storageclass =
     AUTO
   | STATIC
   | USTATIC  (* static UNUSED *)
   | EXTERN

type initializer_ =
     INITSCALAR of expr
   | INITARRAY of initializer_ list
   | INITINDEXEDARRAY of (int * initializer_) list
   | INITSTRUCT of (string * initializer_) list
   
type param =
     PARAM of (ctype * string)

type enumerator =
     ENUMPLAIN of string
   | ENUMVALUE of string * int
     (* XXX these shouldn't need to exist *)
   | ENUMCOMMENT of string
   | ENUMBLANKLINE

type stmt =
     BLANKLINE
   | SHORTCOMMENT of string
   | BLOCKCOMMENT of string
   | BLOCK of stmt list
   | ASSERT of expr
   | ASSIGN of string * expr
     (* ASSIGN' (s1, e0, s2, e) is basically s1 ^ e0 ^ s2 = e. gross XXX *)
   | ASSIGN' of string * expr * string * expr
   | POSTINCR of string
   | IGNORE of expr
   | IF of (expr * stmt * stmt)
   | FOR of (stmt * expr * stmt * stmt) (* XXX: blah *)
   | SWITCH of (expr * (string option * stmt) list)
   | BREAK
   | RETURN
   | RETURNVAL of expr
   | SYSINCLUDE of string
   | LOCALINCLUDE of string
   | IFDEF of string
   | IFNDEF of string
   | ELSE of string option
   | ENDIF of string option
   | DEFINE of string * expr
   | DEFINE' of string
   | UNDEF of string
   | PPERROR of string
   | VAR of (storageclass * ctype * string)
   | VAR' of (storageclass * ctype * string * initializer_)
   | UVAR of (storageclass * ctype * string)  (* tagged UNUSED *)
   | TYPEDEF of (ctype * string)
   | FUNCTION of (storageclass * ctype * string * param list * stmt)
   | FUNCDECL of (storageclass * ctype * string * param list)
   | STRUCTDECL of (string * stmt list)
   | STRUCTDECL' of string
   | ENUMDECL of (string * enumerator list)
   | VARARRAYDECL of (ctype * string * bool(*use_remunsorted*))

(* types *)


(* expressions *)

let cfalse = CONSTANT "false"
let ctrue = CONSTANT "true"
let cnull = CONSTANT "NULL"
let czero = CONSTANT "0"
let czerou = CONSTANT "0U"
let czeroul = CONSTANT "0UL"

let intconst n = CONSTANT (string_of_int n)
let uintconst n = CONSTANT (string_of_int n ^ "U")
let longconst n = CONSTANT (string_of_int n ^ "L")
let ulongconst n = CONSTANT (string_of_int n ^ "UL")
let llconst n = CONSTANT (string_of_int n ^ "LL")
let ullconst n = CONSTANT (string_of_int n ^ "ULL")

let bop op e1 e2 = OP (op, [e1; e2])
let uop op e1 = OP (op, [e1])

let add = bop ADD
let sub = bop SUB
let mul = bop MUL
let div = bop DIV
let mod_ = bop MOD
let neg = uop NEG
let lshift = bop LSHIFT
let rshift = bop RSHIFT
let bitand = bop BITAND
let bitor = bop BITOR
let bitxor = bop BITXOR
let bitnot = uop BITNOT
let eq = bop EQ
let lt = bop LT
let gt = bop GT
let lteq = bop LTEQ
let gteq = bop GTEQ
let logand = bop LOGAND
let logor = bop LOGOR
let lognot = uop LOGNOT
let addrof = uop ADDROF

let ifexpr e1 e2 e3 = OP (COND, [e1; e2; e3])
let ne e1 e2 = lognot (eq e1 e2)

let skip = BLOCK []

let call name args = CALL (name, args)
let callv name args = IGNORE (CALL (name, args))

let simplefor x lo hi stmts =
   FOR (ASSIGN (x, lo), lt (READVAR x) hi, POSTINCR x, BLOCK stmts)

