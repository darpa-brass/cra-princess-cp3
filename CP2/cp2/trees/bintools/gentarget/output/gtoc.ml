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
 * Transform from Gcode to Ccode.
 *)

module G = Gcode
module C = Ccode

(**************************************************************)
(* support *)

let rec ispointer ty = match ty with
     G.CONST ty' -> ispointer ty'
   | G.POINTER _ -> true
   | _ -> false

let intsignedness ty = match ty with
     G.INT | G.LONG | G.LONGLONG | G.INTBITS _ -> Some true
   | G.UINT | G.ULONG | G.ULONGLONG | G.UINTBITS _ -> Some false
   | G.TYPEDEFNAME "intmax_t" -> Some true
   | G.TYPEDEFNAME "uintmax_t" -> Some false
   | _ -> None

let intsize ty = match ty with
     G.INT | G.UINT -> (Some 16, None)
   | G.LONG | G.ULONG -> (Some 32, None)
   | G.LONGLONG | G.ULONGLONG -> (Some 64, None)
   | G.INTBITS w -> (None, Some w)
   | G.UINTBITS w -> (None, Some w)
     (* XXX should do better than "256" here... *)
   | G.TYPEDEFNAME "intmax_t" -> (Some 256, None)
   | G.TYPEDEFNAME "uintmax_t" -> (Some 256, None)
   | _ -> (None, None)

(**************************************************************)
(* primary translation *)

let trans'op op = match op with
     G.ADD -> C.ADD
   | G.SUB -> C.SUB
   | G.MUL -> C.MUL
   | G.DIV -> C.DIV
   | G.MOD -> C.MOD
   | G.NEG -> C.NEG
   | G.LSHIFT -> C.LSHIFT
   | G.RSHIFT -> C.RSHIFT
   | G.BITAND -> C.BITAND
   | G.BITOR -> C.BITOR
   | G.BITXOR -> C.BITXOR
   | G.BITNOT -> C.BITNOT
   | G.EQ -> C.EQ
   | G.LT -> C.LT
   | G.LOGAND -> C.LOGAND
   | G.LOGOR -> C.LOGOR
   | G.LOGXOR -> Util.crash "gtoc: leftover LOGXOR expression"
   | G.LOGNOT -> C.LOGNOT
   | G.COND -> C.COND
   | G.ADDROF -> C.ADDROF

(* XXX cutpasted from typerep.ml *)
let inttype width =
   if width <= 8 then "int8_t"
   else if width <= 16 then "int16_t"
   else if width <= 32 then "int32_t"
   else if width <= 64 then "int64_t"
   else Util.crash ("typerep: too wide inttype " ^ string_of_int width)

(* XXX cutpasted from typerep.ml *)
let uinttype width =
   if width <= 8 then "uint8_t"
   else if width <= 16 then "uint16_t"
   else if width <= 32 then "uint32_t"
   else if width <= 64 then "uint64_t"
   else Util.crash ("typerep: too wide uinttype " ^ string_of_int width)

let rec trans'type t =
  let trans'member (t, x) =
     (trans'type t, x)
  in
  match t with
     G.VOID -> C.VOID
   | G.BOOL -> C.NAMEDTYPE "bool"
   | G.CHAR -> C.NAMEDTYPE "char"
   | G.UCHAR -> C.NAMEDTYPE "unsigned char"
   | G.INT -> C.INT
   | G.UINT -> C.UINT
   | G.LONG -> C.LONG
   | G.ULONG -> C.ULONG
   | G.LONGLONG -> C.LONGLONG
   | G.ULONGLONG -> C.ULONGLONG
(*
   | G.INTBITS n -> C.NAMEDTYPE ("int" ^ string_of_int n ^ "_t")
   | G.UINTBITS n -> C.NAMEDTYPE ("uint" ^ string_of_int n ^ "_t")
*)
   | G.INTBITS n -> C.NAMEDTYPE (inttype n)
   | G.UINTBITS n -> C.NAMEDTYPE (uinttype n)
   | G.ENUMTYPE name -> C.NAMEDTYPE ("enum " ^ name)
   | G.STRUCTTYPE name -> C.NAMEDTYPE ("struct " ^ name)
   | G.UNIONTYPE name -> C.NAMEDTYPE ("union " ^ name)
   | G.ANONSTRUCT members -> C.ANONSTRUCT (List.map trans'member members)
   | G.ANONUNION members -> C.ANONUNION (List.map trans'member members)
   | G.TYPEDEFNAME name -> C.NAMEDTYPE name
   | G.POINTER (G.CONST t') -> begin match trans'type t' with
          C.NAMEDTYPE s -> C.NAMEDTYPE ("const " ^ s ^ " *")
        | _ -> Util.crash "gtoc: trans'type: unsupported const pointer type"
     end
   | G.POINTER t' -> begin match trans'type t' with
          C.NAMEDTYPE s -> C.NAMEDTYPE (s ^ " *")
        | _ -> Util.crash "gtoc: trans'type: unsupported pointer type"
     end
   | G.ARRAY (t', sz) -> C.ARRAYTYPE (trans'type t', sz)
   | G.CONST t' -> begin match trans'type t' with
          C.NAMEDTYPE s -> C.NAMEDTYPE (s ^ " const")
        | C.ARRAYTYPE (C.NAMEDTYPE s, sz) ->
             C.ARRAYTYPE(C.NAMEDTYPE ("const " ^ s), sz)
        | _ -> Util.crash "gtoc: trans'type: unsupported const type"
     end

let rec trans'ppcond trans'sub pp = match pp with
     G.PPIF (G.PPDEFINED x, block, more) ->
        C.IFDEF x :: trans'sub block @ [C.ELSE None] @ trans'ppcond trans'sub more @ [C.ENDIF None]
   | G.PPIF (G.CALL (_t, G.CALLOP G.LOGNOT, [G.PPDEFINED x]), block, more) ->
        C.IFNDEF x :: trans'sub block @ [C.ELSE None] @ trans'ppcond trans'sub more @ [C.ENDIF None]
   | G.PPIF _ ->
        Util.crash "gtoc: unsupported #if form"
   | G.PPELSE block ->
        trans'sub block
   | G.PPENDIF ->
        []

let rec trans'expr e = match e with
     G.INTCONSTANT (_t, k) -> C.CONSTANT k
   | G.STRINGCONSTANT k ->
        (* XXX escape properly *)
        C.CONSTANT ("\"" ^ k ^ "\"")
   | G.READVAR (_t, x) -> C.READVAR x
   | G.READFIELD (_t, e', f) ->
        let e'' = trans'expr e' in
        if ispointer (G.gexprtype e') then
           C.GETFIELD (e'', f)
        else
           C.GETFIELD' (e'', f)
   | G.READARRAY (_t, e1, e2) ->
        let e1' = trans'expr e1 in
        let e2' = trans'expr e2 in
        C.GETARRAY (e1', e2')
   | G.READPOINTER (_t, e) ->
        let e' = trans'expr e in
        C.GETPOINTER e'
   | G.CALL (_t, G.CALLOP op, args) ->
        C.OP (trans'op op, List.map trans'expr args)
   | G.CALL (_t, G.CALLFUNC f, args) -> C.CALL (f, List.map trans'expr args)
   | G.CAST (newt, oldt, e') -> begin
        let e' = trans'expr e' in
        if newt = oldt then
           e' (* nop *)
        else if intsignedness newt = intsignedness oldt then
           C.CAST (trans'type newt, e')
        else if intsize newt = intsize oldt then
           C.CAST (trans'type newt, e')
        else if newt = G.VOID then
           C.CAST (trans'type newt, e')
        else
           (* XXX make this message more specific *)
           Util.crash ("gtoc: Invalid/unsafe cast: " ^
                       Gdump.dump'gtype newt ^ " <= " ^
                       Gdump.dump'gtype oldt)
     end
   | G.SIZEOF ty -> C.SIZEOF (trans'type ty)
(*
   | G.PPEXPR (_t, _pp) -> Util.crash "gtoc: PPEXPR unsupported"
*)
   | G.PPDEFINED _ -> Util.crash "gtoc: PPDEFINED outside #if"
   | G.EXPRCOMMENT (_t, text, e') -> C.COMMENTED (text, trans'expr e')

let trans'pattern pat = match pat with
     G.WRITEVAR (_t, x) -> Types.OIL x
   | G.WRITEFIELD (_t, e, f) -> begin 
        let op = match G.gexprtype e with
             G.POINTER _ -> "->"
           | _ -> "."
        in
        match trans'expr e with
             C.READVAR x -> Types.OIL (x ^ op ^ f)
           | e' -> Types.WATER ("", e', op ^ f)
     end
   | G.WRITEPOINTER (_t, e) -> begin
        match trans'expr e with
             C.READVAR x -> Types.OIL ("*" ^ x)
           | e' -> Types.WATER ("*", e', "")
     end

let rec trans'stmt s = match s with
     G.BLOCK zs -> [C.BLOCK (trans'stmts zs)]
   | G.ASSERT e -> [C.ASSERT (trans'expr e)]
   | G.ASSIGN (pat, e) -> begin
        let e' = trans'expr e in
        match trans'pattern pat with
             Types.OIL p0 -> [C.ASSIGN (p0, e')]
           | Types.WATER (p0, p1, p2) -> [C.ASSIGN' (p0, p1, p2, e')]
     end
   | G.IGNORE e -> [C.IGNORE (trans'expr e)]
   | G.IF (cond, ts, fs) ->
        [C.IF (trans'expr cond, trans'stmt_reduce ts,
                                trans'stmt_reduce fs)]
   | G.SWITCH (cond, cases, defcase) ->
        let trans'case (e, s) =
           let e' = match trans'expr e with
                C.CONSTANT k -> k
              | C.READVAR x -> x
              | _ -> Util.crash "gtoc: Invalid switch case"
           in
           let s' = match trans'stmt s with
                [ss'] -> ss'
              | s' -> C.BLOCK s'
           in
           (Some e', s')
        in
        let cases' = List.map trans'case cases in
        let defcase' = match defcase with
             None -> []
           | Some s -> [(None, C.BLOCK (trans'stmt s))]
        in
        [C.SWITCH (trans'expr cond, cases' @ defcase')]
   | G.LOOP (init, pre, cond, post, cycle) ->
        begin match pre with
             G.BLOCK [] -> ()
           | _ -> Util.crash "gtoc: unsupported loop with pre-cond statements"
        end;
        let init' = trans'stmt init in
        let cond' = trans'expr cond in
        let post' = trans'stmt_reduce post in
        let cycle' = trans'stmt_reduce cycle in
        let mkfor q = C.FOR (q, cond', cycle', post') in
        begin
        match init' with
             [init''] -> [mkfor init'']
           | _ -> [C.BLOCK (init' @ [mkfor (C.BLOCK [])])]
        end
   | G.BREAK -> [C.BREAK]
   | G.RETURN None -> [C.RETURN]
   | G.RETURN (Some e) -> [C.RETURNVAL (trans'expr e)]
   | G.LOCAL (t, x) -> [C.VAR (C.AUTO, trans'type t, x)]
   | G.ULOCAL (t, x) -> [C.UVAR (C.AUTO, trans'type t, x)]
   | G.PPSTMT pp -> trans'ppcond trans'stmts pp
   | G.PPERROR msg -> [C.PPERROR msg]
   | G.BLANKLINESTMT -> [C.BLANKLINE]
   | G.STMTCOMMENT text -> [C.BLOCKCOMMENT text]

and trans'stmts zs =
   List.concat (List.map trans'stmt zs)

and trans'stmt_reduce s =
   match trans'stmt s with
        [s'] -> s'
      | zs -> C.BLOCK zs

let trans'storageclass cl = match cl with
     G.GLOBAL -> C.AUTO  (* XXX this is poorly arranged *)
   | G.STATIC -> C.STATIC
   | G.USTATIC -> C.USTATIC
   | G.EXTERN -> C.EXTERN

let rec trans'initializer init = match init with
     G.INITSCALAR e -> C.INITSCALAR (trans'expr e)
   | G.INITARRAY inits -> C.INITARRAY (List.map trans'initializer inits)
   | G.INITINDEXEDARRAY inits ->
        let trans'one (n, init') = (n, trans'initializer init') in
        C.INITINDEXEDARRAY (List.map trans'one inits)
   | G.INITSTRUCT inits ->
        let trans'one (n, init') = (n, trans'initializer init') in
        C.INITSTRUCT (List.map trans'one inits)

let trans'param (t, name) = C.PARAM (trans'type t, name)

let trans'funcheader cl t params =
   (trans'storageclass cl, trans'type t, List.map trans'param params)

let rec trans'decl d = match d with
     G.TYPEDEF (t, name) ->
        [C.TYPEDEF (trans'type t, name)]
   | G.ENUMDECL (name, enumerators) ->
        let trans'enumerator (x, optnum, optcomment) =
           let comment' = match optcomment with
                None -> []
              | Some text -> [C.ENUMCOMMENT text]
           in
           comment' @ match optnum with
                None -> [C.ENUMPLAIN x]
              | Some k -> [C.ENUMVALUE (x, k)]
        in
        let enumerators' =
           List.concat (List.map trans'enumerator enumerators)
        in
        [C.ENUMDECL (name, enumerators')]
   | G.STRUCTDECL (name, members) ->
        let trans'member (t, x) =
           C.VAR (C.AUTO, trans'type t, x)
        in
        let members' = List.map trans'member members in
        [C.STRUCTDECL (name, members')]
   | G.STRUCTDECL' name ->
        [C.STRUCTDECL' name]
   | G.VARARRAYDECL (ty, name, use_remunsorted) ->
        [C.VARARRAYDECL (trans'type ty, name, use_remunsorted)]
   | G.DEFINE (name, Some e) -> [C.DEFINE (name, trans'expr e)]
   | G.DEFINE (name, None) -> [C.DEFINE' name]
   | G.UNDEF name -> [C.UNDEF name]
   | G.VARDECL (cl, t, x) -> [C.VAR (trans'storageclass cl, trans'type t, x)]
   | G.VARDECL' (cl, t, x, init) -> [C.VAR' (trans'storageclass cl, trans'type t, x, trans'initializer init)]
   | G.FUNCDECL (cl, t, name, params) ->
        let (cl', t', params') = trans'funcheader cl t params in
        [C.FUNCDECL (cl', t', name, params')]
   | G.FUNCTION (cl, t, name, params, body) ->
        let (cl', t', params') = trans'funcheader cl t params in
        [C.FUNCTION (cl', t', name, params', trans'stmt_reduce body)]
   | G.PPDECL pp -> trans'ppcond trans'decls pp
   | G.BLANKLINEDECL -> [C.BLANKLINE]
   | G.DECLCOMMENT text -> [C.BLOCKCOMMENT text]

and trans'decls ds =
   List.concat (List.map trans'decl ds)

let trans'include inc = match inc with
     G.SYSINCLUDE name -> C.SYSINCLUDE name
   | G.LOCALINCLUDE name -> C.LOCALINCLUDE name
   | G.BLANKLINEINCLUDE -> C.BLANKLINE

let trans'file' incs decls =
   let incs' = List.map trans'include incs in
   let decls' = trans'decls decls in
   incs' @ decls'

let trans'file f = match f with
     G.FILE (Some sym, incs, decls) ->
        let body' = trans'file' incs decls in
        C.IFNDEF sym :: C.DEFINE' sym :: body' @ [C.ENDIF (Some sym)]
   | G.FILE (None, incs, decls) ->
        trans'file' incs decls

let gtoc f = trans'file f
