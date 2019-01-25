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

(* dump for Ccode *)

open Dumptools
open Ccode

let nowhere = Pos.nowhere

let dump'op op = match op with
     ADD -> "+"
   | SUB -> "-"
   | MUL -> "*"
   | DIV -> "/"
   | MOD -> "%"
   | NEG -> "-"
   | LSHIFT -> "<<"
   | RSHIFT -> ">>"
   | BITAND -> "&"
   | BITOR -> "|"
   | BITXOR -> "^"
   | BITNOT -> "~"
   | EQ -> "=="
   | LT -> "<"
   | GT -> ">"
   | LTEQ -> "<="
   | GTEQ -> ">="
   | LOGAND -> "&&"
   | LOGOR -> "||"
   | LOGNOT -> "!"
   | COND -> "?:"
   | ADDROF -> "&"

let rec dump'type ct = match ct with
     VOID -> "void"
   | INT -> "int"
   | UINT -> "unsigned"
   | LONG -> "long"
   | ULONG -> "unsigned long"
   | LONGLONG -> "long long"
   | ULONGLONG -> "unsigned long long"
   | ARRAYTYPE (ty', sz) -> dump'type ty' ^ "[" ^ sz ^ "]"
   | NAMEDTYPE s -> s
   | ANONSTRUCT _members -> "struct { ... }"
   | ANONUNION _members -> "union { ... }"

let rec dump'expr e = match e with
     CONSTANT s -> heading' "CONSTANT" s nowhere
   | READVAR s -> heading' "READVAR" s nowhere
   | OP (op, args) ->
        heading' "OP" (dump'op op) nowhere @
        indent (list' dump'expr args)
   | CALL (name, args) ->
        heading' "CALL" name nowhere @
        indent (list' dump'expr args)
   | GETFIELD (e, name) ->
        heading' "GETFIELD" name nowhere @
        field "e" (dump'expr e)
   | GETFIELD' (e, name) ->
        heading' "GETFIELD'" name nowhere @
        field "e" (dump'expr e)
   | GETARRAY (e1, e2) ->
        heading "GETARRAY" nowhere @
        field "e1" (dump'expr e1) @
        field "e2" (dump'expr e2)
   | GETPOINTER e1 ->
        heading "GETPOINTER" nowhere @
        field "e1" (dump'expr e1)
   | CAST (ty, e) ->
        heading' "CAST" (dump'type ty) nowhere @
        field "e" (dump'expr e)
   | SIZEOF ty ->
        heading' "SIZEOF" (dump'type ty) nowhere
   | COMMENTED (text, e) ->
        ("/* " ^ text ^ " */ ") :: dump'expr e

let dump'sc sc = match sc with
     AUTO -> "auto/default"
   | STATIC -> "static"
   | USTATIC -> "static UNUSED"
   | EXTERN -> "extern"

let rec dump'initializer init = match init with
     INITSCALAR e -> dump'expr e
   | INITARRAY inits' ->
        heading "INITARRAY" nowhere @
        indent (list dump'initializer inits')
   | INITINDEXEDARRAY inits' ->
        let dump'one (ix, init') =
           shortfield "index" (string_of_int ix) @
           dump'initializer init'
        in
        indent (list dump'one inits')
   | INITSTRUCT inits' ->
        let dump'one (field, init') =
           shortfield "field" field @
           dump'initializer init'
        in
        indent (list dump'one inits')

let dump'param (PARAM (ty, name)) =
   [name ^ " :: " ^ dump'type ty]

let dump'enumerator en = match en with
     ENUMPLAIN s -> [s]
   | ENUMVALUE (s, n) -> [s ^ "=" ^ string_of_int n]
   | ENUMCOMMENT s -> ["/* " ^ s ^ "*/"]
   | ENUMBLANKLINE -> [""]

let dump'funcheader sc ty params =
   shortfield "sc" (dump'sc sc) @
   shortfield "ty" (dump'type ty) @
   field "params" (list' dump'param params)

let rec dump'stmt s = match s with
     BLANKLINE -> [""]
   | SHORTCOMMENT s -> ["/* " ^ s ^ " */"]
   | BLOCKCOMMENT s -> ["/* " ^ s ^ " */"]
   | BLOCK zs ->
        "{" :: (list dump'stmt zs) @ ["}"]
   | ASSERT e ->
        heading "ASSERT" nowhere @
        field "e" (dump'expr e)
   | ASSIGN (name, e) ->
        heading' "ASSIGN" name nowhere @
        field "e" (dump'expr e)
   | ASSIGN' (pfx, lhs, sfx, e) ->
        heading "ASSIGN'" nowhere @
        shortfield "prefix" pfx @
        field "lhs" (dump'expr lhs) @
        shortfield "suffix" sfx @
        field "e" (dump'expr e)
   | POSTINCR name ->
        heading' "POSTINCR" name nowhere
   | IGNORE e ->
        heading "IGNORE" nowhere @
        field "e" (dump'expr e)
   | IF (cond, ts, fs) ->
        heading "IF" nowhere @
        field "cond" (dump'expr cond) @
        field "true" (dump'stmt ts) @
        field "false" (dump'stmt fs)
   | FOR (init, cond, cycle, body) ->
        heading "FOR" nowhere @
        field "init" (dump'stmt init) @
        field "cond" (dump'expr cond) @
        field "cycle" (dump'stmt cycle) @
        field "body" (dump'stmt body)
   | SWITCH (cond, cases) ->
        let dump'case (k, s) =
           let name = 
              match k with
                   Some x -> "case " ^ x
                 | None -> "default"
           in
           field name (dump'stmt s)
        in
        heading "SWITCH" nowhere @
        field "cond" (dump'expr cond) @
        List.concat (List.map dump'case cases)
   | BREAK ->
        heading "BREAK" nowhere
   | RETURN ->
        heading "RETURN" nowhere
   | RETURNVAL e ->
        heading "RETURN" nowhere @
        field "e" (dump'expr e)
   | SYSINCLUDE name ->
        heading' "SYSINCLUDE" name nowhere
   | LOCALINCLUDE name ->
        heading' "LOCALINCLUDE" name nowhere
   | IFDEF sym ->
        heading' "IFDEF" sym nowhere
   | IFNDEF sym ->
        heading' "IFNDEF" sym nowhere
   | ENDIF None ->
        heading "ENDIF" nowhere
   | ELSE (Some sym) ->
        heading' "ELSE" sym nowhere
   | ELSE None ->
        heading "ELSE" nowhere
   | ENDIF (Some sym) ->
        heading' "ENDIF" sym nowhere
   | DEFINE (sym, e) ->
        heading' "DEFINE" sym nowhere @
        field "e" (dump'expr e)
   | DEFINE' sym ->
        heading' "DEFINE'" sym nowhere
   | UNDEF sym ->
        heading' "UNDEF" sym nowhere
   | PPERROR msg ->
        heading "PPERROR" nowhere @
        shortfield "msg" msg
   | VAR (sc, ty, name) ->
        heading' "VAR" name nowhere @
        shortfield "sc" (dump'sc sc) @
        shortfield "ty" (dump'type ty)
   | VAR' (sc, ty, name, init) ->
        heading' "VAR" name nowhere @
        shortfield "sc" (dump'sc sc) @
        shortfield "ty" (dump'type ty) @
        field "initializer" (dump'initializer init)
   | UVAR (sc, ty, name) ->
        heading' "UVAR" name nowhere @
        shortfield "sc" (dump'sc sc) @
        shortfield "ty" (dump'type ty)
   | TYPEDEF (ty, name) ->
        heading' "TYPEDEF" name nowhere @
        shortfield "ty" (dump'type ty)
   | FUNCTION (sc, ty, name, params, body) ->
        heading' "FUNCTION" name nowhere @
        dump'funcheader sc ty params @
        field "body" (dump'stmt body)
   | FUNCDECL (sc, ty, name, params) ->
        heading' "FUNCDECL" name nowhere @
        dump'funcheader sc ty params
   | STRUCTDECL (name, members) ->
        heading' "STRUCTDECL" name nowhere @
        indent (list dump'stmt members)
   | STRUCTDECL' name ->
        heading' "STRUCTDECL'" name nowhere
   | ENUMDECL (name, members) ->
        heading' "ENUMDECL" name nowhere @
        indent (list dump'enumerator members)
   | VARARRAYDECL (ty, name, use_remunsorted) ->
        heading' "MODARRAYDECL" name nowhere @
        shortfield "ty" (dump'type ty) @
        shortfield "use_remunsorted" (string_of_bool use_remunsorted)

let dump decls =
   String.concat "\n" (List.concat (List.map dump'stmt decls))

