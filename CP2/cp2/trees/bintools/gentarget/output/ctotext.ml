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

module C = Ccode
open C
module T = Textrep

let rec prune_semic texts =
   match texts with
        [T.SUFFIX s] -> if s = ";" then [] else texts
      | [T.SUFFIX s; T.NL] -> if s = ";" then [] else texts
      | [] -> []
      | t :: more -> t :: (prune_semic more)

let emit'op op = match op with
     ADD -> T.OPERATOR "+"
   | SUB -> T.OPERATOR "-"
   | MUL -> T.OPERATOR "%"
   | DIV -> T.OPERATOR "/"
   | MOD -> T.OPERATOR "%"
   | NEG -> T.PREFIX "-"
   | LSHIFT -> T.OPERATOR "<<"
   | RSHIFT -> T.OPERATOR ">>"
   | BITAND -> T.OPERATOR "&"
   | BITOR -> T.OPERATOR "|"
   | BITXOR -> T.OPERATOR "^"
   | BITNOT -> T.PREFIX "~"
   | EQ -> T.OPERATOR "=="
   | LT -> T.OPERATOR "<"
   | GT -> T.OPERATOR ">"
   | LTEQ -> T.OPERATOR "<="
   | GTEQ -> T.OPERATOR ">="
   | LOGAND -> T.OPERATOR "&&"
   | LOGOR -> T.OPERATOR "||"
   | LOGNOT -> T.PREFIX "!"
   | COND -> T.OPERATOR "?:"
   | ADDROF -> T.PREFIX "&"

let rec emit'ctype ty = match ty with
     VOID -> [T.WORD "void"]
   | INT -> [T.WORD "int"]
   | UINT -> [T.WORD "unsigned"; T.WORD "int"]
   | LONG -> [T.WORD "long"]
   | ULONG -> [T.WORD "unsigned"; T.WORD "long"]
   | LONGLONG -> [T.WORD "long"; T.WORD "long"]
   | ULONGLONG -> [T.WORD "unsigned"; T.WORD "long"; T.WORD "long"]
   | ARRAYTYPE (ty', sz) ->
        emit'ctype ty' @ [T.PREFIX "["; T.WORD sz; T.SUFFIX "]"]
   | NAMEDTYPE x -> [T.WORD x]
   | ANONSTRUCT members -> emit'anonagg "struct" members
   | ANONUNION members -> emit'anonagg "union" members

and emit'anonagg kind members =
   let emit'member (ty, name) =
      emit'ctype ty @ [T.WORD name; T.SUFFIX ";"; T.NL]
   in
   [T.WORD kind; T.PREFIX "{"; T.NL] @
   List.concat (List.map emit'member members) @
   [T.NL; T.SUFFIX "}"; T.NL]

let rec emit'expr e = match e with
     CONSTANT s -> [T.WORD s]
   | READVAR s -> [T.WORD s]
   | OP (op, es) -> begin
        let op' = (emit'op op) in
        let es' = List.map emit'expr es in
        match op, es' with
             _, [e1] -> op' :: e1
           | _, [e1; e2] -> [T.PARENS (e1 @ [op'] @ e2)]
           | COND, [e1; e2; e3] ->
		[T.PARENS (e1 @ [T.OPERATOR "?"] @ e2 @ [T.OPERATOR ":"] @ e3)]
           | _ -> Util.crash "emit: expr: invalid operator invocation"
     end
   | CALL (name, es) ->
        let es' = List.map emit'expr es in
        let es'' = Util.intersperse [T.SUFFIX ","] es' in
        [T.WORD name; T.PARENS (List.concat es'')]
   | GETFIELD (e1, name) ->
        let e1' = emit'expr e1 in
        [T.PARENS (e1' @ [T.OPERATOR "->"; T.WORD name])]
   | GETFIELD' (e1, name) ->
        let e1' = emit'expr e1 in
        [T.PARENS (e1' @ [T.OPERATOR "."; T.WORD name])]
   | GETARRAY (e1, e2) ->
        let e1' = emit'expr e1 in
        let e2' = emit'expr e2 in
        [T.PARENS (e1' @ [T.PREFIX "["] @ e2' @ [T.SUFFIX "]"])]
   | GETPOINTER (e1) ->
        let e1' = emit'expr e1 in
        [T.PARENS ([T.PREFIX "*"] @ e1')]
   | CAST (ty, e1) ->
        (T.PARENS (emit'ctype ty)) :: emit'expr e1
   | SIZEOF ty ->
        [T.WORD "sizeof"; T.PARENS (emit'ctype ty)]
   | COMMENTED (text, e1) ->
        emit'expr e1 @ [T.WORD "/*"; T.WORD text; T.WORD "*/"]

let emit'sc sc = match sc with
     AUTO -> T.WORD ""
   | STATIC -> T.WORD "static"
   | USTATIC -> T.WORD "static UNUSED"
   | EXTERN -> T.WORD "extern"

let rec emit'initializer init = match init with
     INITSCALAR e -> emit'expr e
   | INITARRAY inits ->
        let emit'one init' =
           emit'initializer init' @
           [T.SUFFIX ","; T.NL]
        in
        [T.BRACES (T.NL :: List.concat (List.map emit'one inits))]
   | INITINDEXEDARRAY inits ->
        let emit'one (ix, init') =
           [T.WORD (string_of_int ix); T.SUFFIX ":" ] @
           emit'initializer init' @
           [T.SUFFIX ","; T.NL]
        in
        [T.BRACES (T.NL :: List.concat (List.map emit'one inits))]
   | INITSTRUCT inits ->
        let emit'one (name, init') =
           [T.PREFIX "."; T.WORD name; T.SUFFIX "=" ] @
           emit'initializer init' @
           [T.SUFFIX ","; T.NL]
        in
        [T.BRACES (T.NL :: List.concat (List.map emit'one inits))]

let emit'param (PARAM (ty, name)) =
   emit'ctype ty @ [T.WORD name]

let emit'enumerator en = match en with
     ENUMPLAIN sym -> [
        T.WORD sym;
        T.SUFFIX ",";
        T.NL;
     ]
   | ENUMVALUE (sym, n) -> [
        T.WORD sym;
        T.WORD (string_of_int n);
        T.SUFFIX ",";
        T.NL;
     ]
   | ENUMCOMMENT text -> [
	T.OPERATOR "/*";
	T.WORD text;
	T.OPERATOR "*/";
	T.NL
     ]
   | ENUMBLANKLINE -> [T.NL]

let emit'funcheader sc ty name params =
   let params' = List.map emit'param params in
   let params'' = List.concat (Util.intersperse [T.SUFFIX ","] params') in
   let params''' = match params'' with
        [] -> [T.WORD "void"]
      | _ -> params''
   in
   emit'sc sc :: emit'ctype ty @
	[T.WORD name; T.PARENS params''']

let rec emit'stmt s = match s with
     BLANKLINE -> [T.NL]
   | SHORTCOMMENT text -> [
	T.OPERATOR "/*";
	T.WORD text;
	T.OPERATOR "*/";
	T.NL
     ]
   | BLOCKCOMMENT text ->  [
	T.SUFFIX "/*";
	T.NL;
	T.OPERATOR "*";
	T.WORD text;
	T.NL;
        T.SPACE;
	T.PREFIX "*/";
	T.NL
     ]
   | BLOCK ss -> [
	T.BRACES [
	   T.NL;
	   T.INDENT (List.concat (List.map emit'stmt ss))
	];
	T.NL
     ]
   | ASSERT e ->
        let e' = emit'expr e in
        [T.WORD "assert"; T.PARENS e'; T.SUFFIX ";"; T.NL]
   | ASSIGN (var, e) ->
	[T.WORD var; T.OPERATOR "="] @ emit'expr e @ [T.SUFFIX ";"; T.NL]
   | ASSIGN' (pfx, lhs, sfx, e) ->
	[T.WORD pfx] @ emit'expr lhs @ [T.WORD sfx; T.OPERATOR "="] @ emit'expr e @ [T.SUFFIX ";"; T.NL]
   | POSTINCR var ->
        (* XXX this ought to have a ; after it *)
        [T.WORD var; T.SUFFIX "++"]
   | IGNORE (READVAR name) ->
        let e' = emit'expr (READVAR name) in
        T.PARENS [T.WORD "void"] :: e' @ [T.SUFFIX ";"; T.NL]
   | IGNORE e ->
	emit'expr e @ [T.SUFFIX ";"; T.NL]
   | IF (e, t, BLOCK []) -> [
	T.WORD "if";
	T.SPACE;
	T.PARENS (emit'expr e);
     ] @ emit'stmt t
   | IF (e, t, f) -> [
	T.WORD "if";
	T.SPACE;
	T.PARENS (emit'expr e);
     ] @ emit'stmt t @ [
	T.WORD "else"
     ] @ emit'stmt f
   | FOR (init, pred, cycle, block) -> [
        T.WORD "for";
        T.PARENS (
           emit'stmt init @
           (* this comes with the stmt *)
           (* [T.SUFFIX ";"] @ *)
           emit'expr pred @
           [T.SUFFIX ";"] @
           (prune_semic (emit'stmt cycle))
        );
     ] @ emit'stmt block
   | SWITCH (cond, cases) ->
     let emit'case (k, s) =
        let k' = match k with
             Some kk -> [
                T.WORD "case";
                T.WORD kk;
             ]
           | None -> [
                T.WORD "default";
             ]
         in
         k' @ [T.SUFFIX ":"] @ emit'stmt s
     in [
        T.WORD "switch";
        T.PARENS (
           emit'expr cond
        );
     ] @ [T.BRACES (T.NL :: List.concat (List.map emit'case cases))] @ [T.NL]
   | BREAK -> [
	T.WORD "break";
	T.SUFFIX ";";
	T.NL
     ]
   | RETURN -> [
	T.WORD "return";
	T.SUFFIX ";";
	T.NL
     ]
   | RETURNVAL e ->
        let e' = emit'expr e in
	T.WORD "return" :: e' @ [T.SUFFIX ";"; T.NL]
   | SYSINCLUDE name -> [
        T.WORD "#include";
        T.PREFIX "<";
        T.WORD name;
        T.SUFFIX ">";
	T.NL
     ]
   | LOCALINCLUDE name -> [
        T.WORD "#include";
        T.PREFIX "\"";
        T.WORD name;
        T.SUFFIX "\"";
	T.NL
     ]
   | IFDEF name -> [
        T.WORD "#ifdef";
        T.WORD name;
	T.NL
     ]
   | IFNDEF name -> [
        T.WORD "#ifndef";
        T.WORD name;
	T.NL
     ]
   | ELSE oname ->
        let namebits = match oname with
             None -> []
           | Some name -> [
                T.OPERATOR "/*";
                T.WORD name;
                T.OPERATOR "*/";
             ]
        in
        [T.WORD "#else"] @ namebits @ [T.NL]
   | ENDIF oname ->
        let namebits = match oname with
             None -> []
           | Some name -> [
                T.OPERATOR "/*";
                T.WORD name;
                T.OPERATOR "*/";
             ]
        in
        [T.WORD "#endif"] @ namebits @ [T.NL]
   | DEFINE (name, e) ->
        let e' = emit'expr e in
        [T.WORD "#define"; T.WORD name] @ e' @ [T.NL]
   | DEFINE' name ->
        [T.WORD "#define"; T.WORD name; T.NL]
   | UNDEF name ->
        [T.WORD "#undef"; T.WORD name; T.NL]
   | PPERROR msg ->
        [T.WORD "#error"; T.WORD msg; T.NL]
   | VAR (sc, ARRAYTYPE (ty, sz), name) ->
        (* XXX this is gross *)
        emit'stmt (VAR (sc, ty, name ^ "[" ^ sz ^ "]"))
   | VAR' (sc, ARRAYTYPE (ty, sz), name, init) ->
        (* XXX this is gross *)
        emit'stmt (VAR' (sc, ty, name ^ "[" ^ sz ^ "]", init))
   | VAR (sc, ty, name) ->
        emit'sc sc :: emit'ctype ty @ [T.WORD name; T.SUFFIX ";"; T.NL]
   | VAR' (sc, ty, name, init) ->
        emit'sc sc :: emit'ctype ty @ [T.WORD name; T.OPERATOR "="] @
        emit'initializer init @ [T.SUFFIX ";"; T.NL] 
   | UVAR (sc, ty, name) ->
        T.WORD "UNUSED" ::
        emit'sc sc :: emit'ctype ty @ [T.WORD name; T.SUFFIX ";"; T.NL]
   | TYPEDEF (ty, name) ->
        [T.WORD "typedef"] @ emit'ctype ty @ [T.WORD name; T.SUFFIX ";"; T.NL]
   | FUNCTION (sc, ty, name, params, body) ->
        emit'funcheader sc ty name params @ emit'stmt body
   | FUNCDECL (sc, ty, name, params) -> 
        emit'funcheader sc ty name params
        @ [T.SUFFIX ";"; T.NL]
   | STRUCTDECL (name, members) -> [
        T.WORD "struct";
        T.WORD name;
	T.BRACES [
           T.NL;
           T.INDENT (List.concat (List.map emit'stmt members));
        ];
        T.SUFFIX ";";
        T.NL;
     ]
   | STRUCTDECL' name -> [
        T.WORD "struct";
        T.WORD name;
        T.SUFFIX ";";
        T.NL;
     ]
   | ENUMDECL (name, members) -> [
        T.WORD "enum";
        T.WORD name;
	T.BRACES [
           T.NL;
           T.INDENT (List.concat (List.map emit'enumerator members));
        ];
        T.SUFFIX ";";
        T.NL;
     ]
   | VARARRAYDECL (ty, name, use_remunsorted) ->
        let namearg = [T.WORD name] in
        let tyarg = emit'ctype ty in
        let inlarg = [T.WORD "static"; T.WORD "UNUSED"; T.WORD "inline"] in
        let comma = [T.SUFFIX ","] in
        let main = [
           T.WORD "DECLARRAY_FULL";
           T.PARENS (namearg @ comma @ tyarg @ comma @ inlarg);
           T.SUFFIX ";";
           T.NL;
           T.WORD "DEFARRAY_FULL";
           T.PARENS (namearg @ comma @ tyarg @ comma @ inlarg);
           T.SUFFIX ";";
           T.NL;
        ] in
        let remunsorted = if use_remunsorted then [
           T.WORD "DECLARRAY_REMUNSORTED_FULL";
           T.PARENS (namearg @ comma @ inlarg);
           T.SUFFIX ";";
           T.NL;
           T.WORD "DEFARRAY_REMUNSORTED_FULL";
           T.PARENS (namearg @ comma @ tyarg @ comma @ inlarg);
           T.SUFFIX ";";
           T.NL;
        ] else [] in
        main @ remunsorted

let ctotext stmts =
   List.concat (List.map emit'stmt stmts)
