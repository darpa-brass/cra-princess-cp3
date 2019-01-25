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

(* dump for Gcode *)

open Dumptools
open Gcode

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
   | LOGAND -> "&&"
   | LOGOR -> "||"
   | LOGXOR -> "^^"
   | LOGNOT -> "!"
   | COND -> "?:"
   | ADDROF -> "&"

let rec dump'gtype t = match t with
     VOID -> "void"
   | BOOL -> "bool"
   | CHAR -> "char"
   | UCHAR -> "unsigned char"
   | INT -> "int"
   | UINT -> "unsigned"
   | LONG -> "long"
   | ULONG -> "unsigned long"
   | LONGLONG -> "long long"
   | ULONGLONG -> "unsigned long long"
   | INTBITS n -> "int" ^ string_of_int n ^ "_t"
   | UINTBITS n -> "uint" ^ string_of_int n ^ "_t"
   | ENUMTYPE x -> "enum " ^ x
   | STRUCTTYPE x -> "struct " ^ x
   | UNIONTYPE x -> "union " ^ x
   | ANONSTRUCT _members -> "struct { ... }" (* XXX? *)
   | ANONUNION _members -> "union { ... }" (* XXX? *)
   | TYPEDEFNAME x -> x
   | POINTER (CONST t') -> "const " ^ (dump'gtype t') ^ " * "
   | POINTER t' -> (dump'gtype t') ^ " *"
   | ARRAY (t', sz) -> (dump'gtype t') ^ "[" ^ sz ^ "]"
   | CONST t' -> (dump'gtype t') ^ " const"

let dump'callee q = match q with
     CALLOP op -> "op " ^ dump'op op
   | CALLFUNC f -> "func " ^ f

let rec dump'expr e = match e with
     INTCONSTANT (t, k) ->
        heading' "INTCONSTANT" k nowhere @
        shortfield "type" (dump'gtype t)
   | STRINGCONSTANT k ->
        heading' "STRINGCONSTANT" k nowhere
   | READVAR (t, x) ->
        heading' "READVAR" x nowhere @
        shortfield "type" (dump'gtype t)
   | READFIELD (t, e, f) ->
        heading' "READFIELD" f nowhere @
        field "e" (dump'expr e) @
        shortfield "type" (dump'gtype t)
   | READARRAY (t, e1, e2) ->
        heading "READARRAY" nowhere @
        field "e1" (dump'expr e1) @
        field "e2" (dump'expr e2) @
        shortfield "type" (dump'gtype t)
   | READPOINTER (t, e) ->
        heading "READPOINTER" nowhere @
        field "e" (dump'expr e) @
        shortfield "type" (dump'gtype t)
   | CALL (t, what, args) ->
        heading' "CALL" (dump'callee what) nowhere @
        indent (list' dump'expr args) @
        shortfield "type" (dump'gtype t)
   | CAST (nty, oty, e) ->
        heading "CAST" nowhere @
        shortfield "newtype" (dump'gtype nty) @
        shortfield "oldtype" (dump'gtype oty) @
        field "e" (dump'expr e)
   | SIZEOF ty ->
        heading "SIZEOF" nowhere @
        shortfield "type" (dump'gtype ty)

(*
 * For some reason this and the other two cases can't share
 * dump'ppcond. The other two cases work fine together, but
 * this one makes the function monomorphic, even if it's
 * declared first with type annotations. Buh. So I've just
 * taken PPEXPR out of gcode as we'll probably never want it
 * anyway.
 *)
(*
   | PPEXPR (t, ppc) ->
        heading "PPEXPR" nowhere @
        indent (dump'ppcond true dump'expr ppc) @
        shortfield "type" (dump'gtype t)
*)
   | PPDEFINED x ->
        heading' "PPDEFINED" x nowhere
   | EXPRCOMMENT (_t, text, e) ->
        ("/* " ^ text ^ " */") :: dump'expr e

let rec dump'ppcond top dump'sub ppc =
  match ppc with
     PPIF (e, x, more) ->
        heading (if top then "PPIF" else "PPELIF") nowhere @
        field "e" (dump'expr e) @
        dump'sub x @
        dump'ppcond false dump'sub more
   | PPELSE x ->
        heading "PPELSE" nowhere @
        dump'sub x @
        heading "PPENDIF" nowhere
   | PPENDIF ->
        heading "PPENDIF" nowhere

let dump'optexpr oe = match oe with
     None -> ["[nil]"]
   | Some e -> dump'expr e

let dump'pattern pat = match pat with
     WRITEVAR (t, x) ->
        heading' "WRITEVAR" x nowhere @
        shortfield "type" (dump'gtype t)
   | WRITEFIELD (t, e, f) ->
        heading' "WRITEFIELD" f nowhere @
        field "e" (dump'expr e) @
        shortfield "type" (dump'gtype t)
   | WRITEPOINTER (t, e) ->
        heading "WRITEPOINTER" nowhere @
        field "e" (dump'expr e) @
        shortfield "type" (dump'gtype t)

let rec dump'stmt s = match s with
     BLOCK zs ->
        heading "BLOCK" nowhere @
        indent (list dump'stmt zs)
   | ASSERT e ->
        heading "ASSERT" nowhere @
        field "e" (dump'expr e)
   | ASSIGN (pat, e) ->
        heading "ASSIGN" nowhere @
        field "pat" (dump'pattern pat) @
        field "e" (dump'expr e)
   | IGNORE e ->
        heading "IGNORE" nowhere @
        field "e" (dump'expr e)
   | IF (cond, ts, fs) ->
        heading "IF" nowhere @
        field "cond" (dump'expr cond) @
        field "true" (dump'stmt ts) @
        field "false" (dump'stmt fs)
   | SWITCH (cond, cases, defcase) ->
        let dump'case (e, s) =
           field "case" (dump'expr e) @
           field "block" (dump'stmt s)
        in
        heading "SWITCH" nowhere @
        field "cond" (dump'expr cond) @
        List.concat (List.map dump'case cases) @
        begin
        match defcase with
             Some s -> field "default" (dump'stmt s)
           | None -> []
        end
   | LOOP (init, pre, cond, post, cycle) ->
        heading "LOOP" nowhere @
        field "init" (dump'stmt init) @
        field "pre" (dump'stmt pre) @
        field "cond" (dump'expr cond) @
        field "post" (dump'stmt post) @
        field "cycle" (dump'stmt cycle)
   | BREAK ->
        heading "BREAK" nowhere
   | RETURN oe ->
        heading "RETURN" nowhere @
        field "value" (dump'optexpr oe)
   | LOCAL (t, x) ->
        heading' "LOCAL" x nowhere @
        shortfield "type" (dump'gtype t)
   | ULOCAL (t, x) ->
        heading' "LOCAL" x nowhere @
        shortfield "type" (dump'gtype t)
   | PPSTMT ppc ->
        heading "PPSTMT" nowhere @
        indent (dump'ppcond true (list dump'stmt) ppc)
   | PPERROR msg ->
        heading "PPERROR" nowhere @
        indent (shortfield "msg" msg)
   | BLANKLINESTMT ->
        heading "BLANKLINESTMT" nowhere
   | STMTCOMMENT text ->
        [("/* " ^ text ^ " */")]

let dump'storageclass sc = match sc with
     GLOBAL -> "global"
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

let dump'param (t, x) =
     [x ^ " :: " ^ dump'gtype t]

let dump'enumerator (name, on, oc) =
    let on' = match on with
         None -> ""
       | Some n -> "=" ^ string_of_int n
    in
    let oc' = match oc with
         None -> ""
       | Some txt -> " /* " ^ txt ^ " */"
    in
    [name ^ on' ^ oc']

let rec dump'decl d = match d with
     TYPEDEF (t, name) ->
        heading' "TYPEDEF" name nowhere @
        shortfield "type" (dump'gtype t)
   | ENUMDECL (name, elems) ->
        heading' "ENUMDECL" name nowhere @
        indent (list dump'enumerator elems)
   | STRUCTDECL (name, members) ->
        heading' "STRUCTDECL" name nowhere @
        indent (list dump'param members)
   | STRUCTDECL' name ->
        heading' "STRUCTDECL'" name nowhere
   | VARARRAYDECL (ty, name, use_remunsorted) ->
        heading' "MODARRAYDECL" name nowhere @
        shortfield "type" (dump'gtype ty) @
        shortfield "use_remunsorted" (string_of_bool use_remunsorted)
   | DEFINE (sym, oe) ->
        heading' "DEFINE" sym nowhere @
        field "expansion" (dump'optexpr oe)
   | UNDEF sym ->
        heading' "UNDEF" sym nowhere
   | VARDECL (sc, t, x) ->
        heading' "VARDECL" x nowhere @
        shortfield "storageclass" (dump'storageclass sc) @
        shortfield "type" (dump'gtype t)
   | VARDECL' (sc, t, x, init) ->
        heading' "VARDECL'" x nowhere @
        shortfield "storageclass" (dump'storageclass sc) @
        shortfield "type" (dump'gtype t) @
	field "initializer" (dump'initializer init)
   | FUNCDECL (sc, t, name, params) ->
        heading' "FUNCDECL" name nowhere @
        shortfield "storageclass" (dump'storageclass sc) @
        shortfield "type" (dump'gtype t) @
        field "params" (list' dump'param params)
   | FUNCTION (sc, t, name, params, body) ->
        heading' "FUNCTION" name nowhere @
        shortfield "storageclass" (dump'storageclass sc) @
        shortfield "type" (dump'gtype t) @
        field "params" (list' dump'param params) @
        field "body" (dump'stmt body)
   | PPDECL ppc ->
        heading "PPDECL" nowhere @
        indent (dump'ppcond true (list dump'decl) ppc)
   | BLANKLINEDECL ->
        heading "BLANKLINEDECL" nowhere
   | DECLCOMMENT text ->
        [("/* " ^ text ^ " */")]

let dump'include inc = match inc with
     SYSINCLUDE name -> ["<" ^ name ^ ">"]
   | LOCALINCLUDE name -> ["\"" ^ name ^ "\""]
   | BLANKLINEINCLUDE -> [""]

let dump'file f = match f with
     FILE (optguard, incs, decls) ->
        (match optguard with
              None -> heading "FILE" nowhere
            | Some guard -> heading' "FILE" guard nowhere
        ) @
        field "includes" (list dump'include incs) @
        field "decls" (list dump'decl decls)

let dump f =
   String.concat "\n" (dump'file f)
