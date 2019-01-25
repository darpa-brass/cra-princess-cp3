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
 * Abstract output code representation.
 *
 * This is supposed to be significantly simpler in form than C code,
 * so it can be output more easily, checked, and then afterwards
 * lowered to the representation in ccode.ml.
 *)

type op =
     ADD | SUB | MUL | DIV | MOD | NEG
   | LSHIFT | RSHIFT
   | BITAND | BITOR | BITXOR | BITNOT
   | EQ | LT
   | LOGAND | LOGOR | LOGXOR | LOGNOT
   | COND
   | ADDROF

type gtype =
     VOID
   | BOOL
   | CHAR | UCHAR
   | INT | UINT | LONG | ULONG | LONGLONG | ULONGLONG
   | INTBITS of int | UINTBITS of int
   | ENUMTYPE of string | STRUCTTYPE of string | UNIONTYPE of string
   | ANONSTRUCT of (gtype * string) list
   | ANONUNION of (gtype * string) list
   | TYPEDEFNAME of string
   | POINTER of gtype
   | ARRAY of (gtype * string)
   | CONST of gtype

type callee =
     CALLOP of op
   | CALLFUNC of string

type expr =
     INTCONSTANT of gtype * string
   | STRINGCONSTANT of string
   | READVAR of gtype * string
   | READFIELD of gtype * expr * string
   | READARRAY of gtype * expr * expr
   | READPOINTER of gtype * expr
   | CALL of gtype * callee * expr list
   | CAST of gtype * gtype * expr
   | SIZEOF of gtype
(*
   | PPEXPR of gtype * expr ppcond
*)
   | PPDEFINED of string
   | EXPRCOMMENT of gtype * string * expr

and 't ppcond =
     PPIF of expr * 't * 't ppcond
   | PPELSE of 't
   | PPENDIF

type pattern =
     WRITEVAR of gtype * string
   | WRITEFIELD of gtype * expr * string
   | WRITEPOINTER of gtype * expr

type stmt =
     BLOCK of stmt list
   | ASSERT of expr
   | ASSIGN of pattern * expr
   | IGNORE of expr
   | IF of expr * stmt * stmt
   | SWITCH of expr * (expr * stmt) list * stmt option
   | LOOP of stmt(*init*) * stmt * expr(*cond*) * stmt * stmt(*cycle*)
   | BREAK
   | RETURN of expr option
   | LOCAL of gtype * string
   | ULOCAL of gtype * string  (* tagged UNUSED *)
   | PPSTMT of stmt list ppcond
   | PPERROR of string
   | BLANKLINESTMT
   | STMTCOMMENT of string

type storageclass =
     GLOBAL
   | STATIC
   | USTATIC  (* static UNUSED *)
   | EXTERN

type initializer_ =
     INITSCALAR of expr
   | INITARRAY of initializer_ list
   | INITINDEXEDARRAY of (int * initializer_) list
   | INITSTRUCT of (string * initializer_) list

type decl =
     TYPEDEF of gtype * string
   | ENUMDECL of string * (string * int option * string option) list
   | STRUCTDECL of string * (gtype * string) list
   | STRUCTDECL' of string
   | VARARRAYDECL of gtype * string * bool(*use_remunsorted*)
   | DEFINE of string * expr option
   | UNDEF of string
   | VARDECL of storageclass * gtype * string
   | VARDECL' of storageclass * gtype * string * initializer_
   | FUNCDECL of storageclass * gtype * string * (gtype * string) list
   | FUNCTION of storageclass * gtype * string * (gtype * string) list * stmt
   | PPDECL of decl list ppcond
   | BLANKLINEDECL
   | DECLCOMMENT of string

type include_ =
     SYSINCLUDE of string
   | LOCALINCLUDE of string
   | BLANKLINEINCLUDE

type file =
   FILE of string option(*include guard*) * include_ list * decl list


(* helpers *)

(* types *)
let charptr = POINTER (CHAR)
let constcharptr = POINTER (CONST CHAR)

let tysuffix ty = match ty with
     UCHAR | UINT -> "U"
   | ULONG  -> "UL"
   | ULONGLONG -> "ULL"
   | CHAR | INT -> ""
   | LONG -> "L"
   | LONGLONG -> "LL"
   | TYPEDEFNAME "uint8_t" -> "U"  (* aargh XXX *)
   | TYPEDEFNAME "uint16_t" -> "U"  (* aargh XXX *)
   | TYPEDEFNAME "uint32_t" -> "U"  (* aargh XXX *)
   | TYPEDEFNAME "uint64_t" -> "ULL"  (* aargh XXX *)
   | UINTBITS _ -> "U" (* XXX: should these be allowed? *)
   | INTBITS _ -> ""
   | _ -> ""

(* constants *)
let boolconst x = READVAR (BOOL, if x then "true" else "false")
let zero ty = INTCONSTANT (ty, "0" ^ tysuffix ty)
let one ty = INTCONSTANT (ty, "1" ^ tysuffix ty)
let null = READVAR (POINTER VOID, "NULL")

(* expressions *)

let uop op ty e = CALL (ty, CALLOP op, [e])
let bop op ty e1 e2 = CALL (ty, CALLOP op, [e1; e2])
let lognot = uop LOGNOT BOOL
let logand = bop LOGAND BOOL
let logor = bop LOGOR BOOL
let neg = uop NEG
let eq = bop EQ BOOL
let lt = bop LT BOOL
let add = bop ADD
let sub = bop SUB
let mul = bop MUL
let div = bop DIV
let mod_ = bop MOD
let lshift = bop LSHIFT
let rshift = bop RSHIFT
let bitnot = uop BITNOT
let bitand = bop BITAND
let bitor = bop BITOR
let bitxor = bop BITXOR
let addrof = uop ADDROF
let ne e1 e2 = lognot (eq e1 e2)
let gt e1 e2 = lt e2 e1
let lteq e1 e2 = lognot (gt e1 e2)
let gteq e1 e2 = lognot (lt e1 e2)

let condexpr ty cond et ef = CALL (ty, CALLOP COND, [cond; et; ef])

let call ty callee args =
   CALL (ty, CALLFUNC callee, args)
let streq a b = lognot (call INT "strcmp" [a; b])

(* statements *)
let skip = BLOCK []
let voidcall callee args =
   IGNORE (call VOID callee args)
let retval e =
   RETURN (Some e)
let retvoid =
   RETURN None
let incr ty varname =
   ASSIGN (WRITEVAR (ty, varname), add ty (READVAR (ty, varname)) (one ty))
let decr ty varname =
   ASSIGN (WRITEVAR (ty, varname), sub ty (READVAR (ty, varname)) (one ty))
let simplefor ty x lo hi stmts =
   LOOP (ASSIGN (WRITEVAR (ty, x), lo),
         BLOCK [],
         lt (READVAR (ty, x)) hi,
         BLOCK stmts,
         incr ty x)


(* decls *)
let defineif name onoff =
   match onoff with
        true -> DEFINE (name, None)
      | false -> UNDEF name

(* tools *)

let gexprtype e = match e with
     INTCONSTANT (t, _) -> t
   | STRINGCONSTANT _ -> POINTER (CONST CHAR)
   | READVAR (t, _) -> t
   | READFIELD (t, _, _) -> t
   | READARRAY (t, _, _) -> t
   | READPOINTER (t, _) -> t
   | CALL (t, _, _) -> t
   | CAST (nt, _ot, _) -> nt
   | SIZEOF _ -> ULONG
(*
   | PPEXPR (t, _) -> t
*)
   | PPDEFINED _ -> BOOL
   | EXPRCOMMENT (t, _, _) -> t
