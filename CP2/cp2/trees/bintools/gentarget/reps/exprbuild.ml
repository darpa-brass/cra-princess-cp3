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

module T = Exprtree
module R = Exprrep

module TB = Typebuild


let mkbool pos x =
   let x' = match x with
        true -> "true"
      | false -> "false"
   in
   R.USEVAR (pos, TB.booltype, x')

let rec build'expr e = match e with
     T.UOP (pos, op, e1) -> begin
        let e1' = build'expr e1 in
        match op with
             T.PLUS -> e1'
           | T.NEG -> R.OP (pos, TB.notype, R.NEG, [e1'])
           | T.BITNOT -> R.OP (pos, TB.notype, R.BITNOT, [e1'])
           | T.LOGNOT -> R.OP (pos, TB.notype, R.LOGNOT, [e1'])
           | T.EVAL -> R.EVAL (pos, TB.notype, "???", 0, TB.notype, e1')
           | T.UNEVAL -> R.UNEVAL (pos, TB.notype, e1')
           | T.CONSTP -> R.OP (pos, TB.notype, R.CONSTP, [e1'])
           | T.DEFINEDP -> R.OP (pos, TB.notype, R.DEFINEDP, [e1'])
           | T.ORD -> R.OP (pos, TB.notype, R.ORD, [e1'])
     end
   | T.BOP (pos, e1, T.LTEQ, e2) ->
        build'expr (T.UOP (pos, T.LOGNOT, T.BOP (pos, e2, T.LT, e1)))
   | T.BOP (pos, e1, T.NEQ, e2) ->
        build'expr (T.UOP (pos, T.LOGNOT, T.BOP (pos, e1, T.EQ, e2)))
   | T.BOP (pos, e1, T.NOTIN, e2) ->
        build'expr (T.UOP (pos, T.LOGNOT, T.BOP (pos, e1, T.IN, e2)))
   | T.BOP (pos, e1, op, e2) -> begin
        let e1' = build'expr e1 in
        let e2' = build'expr e2 in
        let args' = [e1'; e2'] in
        let op' = match op with
             T.BITOR -> R.BITOR
           | T.BITXOR -> R.BITXOR
           | T.BITAND -> R.BITAND
           | T.LOGOR -> R.LOGOR
           | T.LOGXOR -> R.LOGXOR
           | T.LOGAND -> R.LOGAND
           | T.SHL -> R.SHL
           | T.SHR -> R.SHR
           | T.EQ -> R.EQ
           | T.NEQ -> assert false (* handled above *)
           | T.IN -> R.IN
           | T.NOTIN -> assert false (* handled above *)
           | T.LT -> R.LT
           | T.LTEQ -> assert false (* handled above *)
           | T.ADD -> R.ADD
           | T.SUB -> R.SUB
           | T.MUL -> R.MUL
           | T.DIV -> R.DIV
           | T.MOD -> R.MOD
           | T.STRCAT -> R.STRCAT
        in
        R.OP (pos, TB.notype, op', args')
     end
   | T.FITS (pos, e1, argty) ->
        let e1' = build'expr e1 in
        let argty' = TB.build'type argty in
        R.FITS (pos, TB.notype, e1', argty')
   | T.MODE (pos, modename) ->
        R.MODE (pos, modename)
   | T.READVAR (pos, name) -> R.USEVAR (pos, TB.notype, name)
   | T.READMEMBER (pos, e1, name) ->
        let e1' = build'expr e1 in
        R.USEFIELD (pos, TB.notype, e1', name)
   | T.BOOLCONSTANT (pos, v) -> mkbool pos v
   | T.NUMCONSTANT (pos, v) -> R.CONST (pos, TB.notype, R.SMALL v)
   | T.STRCONSTANT (pos, text) -> R.STRCONST (pos, TB.notype, text)
   | T.HERE pos -> R.USEVAR (pos, TB.notype, ".")
   | T.LIST (pos, es) -> R.LIST (pos, TB.notype, List.map build'expr es)
   | T.MODIFIER (pos, modname, args) ->
        let args' = List.map build'expr args in
        R.MODIFIER (pos, TB.notype, modname, args')
   | T.PACK (pos, ctor, args) ->
        let args' = List.map build'expr args in
        R.PACK (pos, TB.notype, ctor, args')
   | T.CAST (pos, nt, ot, e1) ->
        let e1' = build'expr e1 in
        let ot' = TB.build'type ot in
        let nt' = TB.build'type nt in
        R.CAST (pos, nt', ot', e1')
   | T.ANNOTATE (pos, ty, e1) ->
        let e1' = build'expr e1 in
        let ty' = TB.build'type ty in
        R.ANNOTATE (pos, ty', e1')

let build'optexpr oe = match oe with
     None -> None
   | Some e -> Some (build'expr e)

