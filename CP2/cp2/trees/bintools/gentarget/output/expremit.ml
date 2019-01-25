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

module G = Gcode
module TE = Typeemit
open Typerep
open Exprrep

(* convert to the more complex form like e.g. exprtypecheck only when needed *)
type ctx = {
   emit'varname: string -> string;
                      (* the type is the _result_ type *)
   emit'eval: Pos.pos -> typename -> G.expr -> G.expr
}

(* by default, crash on EVAL *)
let default_eval pos _ty _e =
   Pos.crashat pos "expremit: eval expression (NOTYET)"

let defaultctx = {
   emit'varname = (fun x -> x);
   emit'eval = default_eval;
}

let emit'op op =
   (* XXX there must be a cleaner way to write this *)
   if op = CONSTP then
      G.CALLFUNC "is_constant"
   else if op = DEFINEDP then
      G.CALLFUNC "is_defined"
   else
   let op' = match op with
        EQ -> G.EQ
      | IN -> Util.crash "expremit: leftover IN expression"
      | LT -> G.LT
      | STRCAT -> Util.crash "expremit: STRCAT on non-strings"
      | ADD -> G.ADD
      | SUB -> G.SUB
      | MUL -> G.MUL
      | DIV -> G.DIV
      | MOD -> G.MOD
      | NEG -> G.NEG
      | SHL -> G.LSHIFT
      | SHR -> G.RSHIFT
      | BITAND -> G.BITAND
      | BITOR -> G.BITOR
      | BITXOR -> G.BITXOR
      | BITNOT -> G.BITNOT
      | LOGAND -> G.LOGAND
      | LOGOR -> G.LOGOR
      | LOGXOR -> G.LOGXOR
      | LOGNOT -> G.LOGNOT
      | CONSTP -> assert false
      | DEFINEDP -> assert false
      | ORD -> assert false
   in
   G.CALLOP op'

let emit'string'op op args =
   let func t n a = G.CALL (t, G.CALLFUNC n, a) in
   match op with
        EQ -> G.lognot (func G.INT "strcmp" args)
      | IN -> Util.crash "expremit: leftover IN expression"
      | LT -> G.lt (func G.INT "strcmp" args) (G.zero G.INT)
      | STRCAT -> func G.charptr "dostrdup2" args
      | _ -> Util.crash ("expremit: invalid string operator " ^ dump'op op)

let isstring args =
   let check sofar arg =
      if exprtype arg = PLAINTYPE "string" then true else sofar
   in
   List.fold_left check false args

let rec emit'expr' ctx e =
   let makeconst pos ty x =
      emit'expr' ctx (CONST (pos, ty, SMALL x))
   in
   let makeones pos ty bits =
      emit'expr' ctx (CONST (pos, ty, LARGE (Types.Wide.ones bits)))
   in
 match e with
     CONST (_pos, PLAINTYPE "bool", (SMALL 0)) ->
        G.READVAR (G.BOOL, "false")
   | CONST (_pos, PLAINTYPE "bool", (SMALL 1)) ->
        G.READVAR (G.BOOL, "true")
   | CONST (pos, ty, k) ->
        let ty' = TE.emit'type pos ty in
        let suffix = match ty with
             WIDTHTYPE ("int", width) -> if width > 32 then "LL" else ""
           | WIDTHTYPE ("uint", width) -> if width > 32 then "ULL" else "U"
           | _ -> ""
        in
        let k' = match k with
             SMALL n -> string_of_int n
           | LARGE n -> Types.Wide.to_string n
        in
        G.INTCONSTANT (ty', k' ^ suffix)
   | STRCONST (_pos, _ty, s) ->
        G.STRINGCONSTANT s
   | USEVAR (pos, ty, name) ->
        G.READVAR (TE.emit'type pos ty, ctx.emit'varname name)
   | USEFIELD (pos, ty, e1, name) ->
        let e1' = emit'expr' ctx e1 in
        G.READFIELD (TE.emit'type pos ty, e1', name)
   | OP (_pos, _ty, ORD, [arg]) ->
        emit'expr' ctx arg
   | OP (pos, ty, op, args) ->
        let ty' = TE.emit'type pos ty in
        let args' = List.map (emit'expr' ctx) args in
        (* XXX we should probably put this logic in gtoc *)
        if isstring args then
           emit'string'op op args'
        else
           G.CALL (ty', emit'op op, args')
   | FITS (pos, _ty, e1, ty'arg) ->
        let ty'e1 = exprtype e1 in
        let ty'e1' = TE.emit'type pos ty'e1 in
        (*let ty' = TE.emit'type pos ty in*)
        let e1' = emit'expr' ctx e1 in
        (*let ty'arg' = TE.emit'type pos ty'arg in*)
        let e1'' = match ty'arg with
             WIDTHTYPE ("uint", width) ->
                let ones = makeones pos ty'e1 width in
                G.lognot (G.lt ones e1')
           | WIDTHTYPE ("int", width) ->
                (* XXX crash if width is 0? *)
                let ones = makeones pos ty'e1 (width - 1) in
                let negones = G.neg ty'e1' ones in
                let one = G.INTCONSTANT (ty'e1', "1") in
                let minval = G.sub ty'e1' negones one in
                let postest = G.lognot (G.lt ones e1') in
                let negtest = G.lognot (G.lt e1' minval) in
                G.logand postest negtest
           | _ -> Pos.crashat pos "expremit: invalid FITS type"
        in
        e1''
   | MODE (_pos, name) ->
        G.call G.BOOL "modeison" [G.STRINGCONSTANT name]
   | LIST (pos, _ty, _members) ->
        Pos.crashat pos "expremit: leftover list expression"
   | MODIFIER (pos, ty, name, args) ->
        let ty' = TE.emit'type pos ty in
        let name' = "modifier_" ^ name in
        let linenum = G.READVAR (G.INT, "linenum") in
        let args' = linenum :: List.map (emit'expr' ctx) args in
        G.CALL (ty', G.CALLFUNC name', args')
(*
   | PACK (_pos, _ty, "mem", [e1; reg]) ->
        (* XXX this should not exist and is hopefully temporary *)
        let e1' = emit'expr' ctx e1 in
        let reg' = emit'expr' ctx reg in
        (* produce what the hack in genencoding expects to receive *)
        let type'expr = G.POINTER (G.STRUCTTYPE "expr") in
        let reg_1 = G.call type'expr "mkexpr_targetnum" [
           G.READVAR (G.INT, "TTOK_REGCLASS_GENERALREG");
           reg';
        ] in
        let reg_2 = G.call type'expr "mkexpr_unary" [
           G.READVAR (G.INT, "OP_PARENS");
           reg_1;
        ] in
        G.call type'expr "mkexpr_juxtapose" [e1'; reg_2]
*)
   | PACK (pos, _ty, _name, _args) ->
        (* XXX *)
        Pos.crashat pos "expremit: pack expression (NOTYET)"
   | CAST (pos, nt, ot, e1) -> begin
        let nt' = TE.emit'type pos nt in
        let ot' = TE.emit'type pos ot in
        let e1' = emit'expr' ctx e1 in
        match nt, ot with
             WIDTHTYPE ("uint", nw), WIDTHTYPE ("uint", ow)
           | WIDTHTYPE ("uint", nw), WIDTHTYPE ("zeros", ow)
           | WIDTHTYPE ("uint", nw), WIDTHTYPE ("ones", ow) ->
                if nw > ow then
                   (* unsigned widen *)
                   G.CAST (nt', ot', e1')
                else if nw < ow then
                   (* unsigned narrow *)
                   G.CAST (nt', ot', e1')
                else
                   (* nop, just discard it *)
                   e1'
           | WIDTHTYPE ("int", nw), WIDTHTYPE ("int", ow) ->
                let unt = WIDTHTYPE ("uint", nw) in
                let uot = WIDTHTYPE ("uint", ow) in
                let unt' = TE.emit'type pos unt in
                let uot' = TE.emit'type pos uot in
                if nw > ow then
                   (* signed widen *)
                   let unsigned_e1' = G.CAST (uot', ot', e1') in
                   let wide_e1' = G.CAST (unt', uot', unsigned_e1') in
                   let one = makeconst pos unt 1 in
                   let shiftamount = makeconst pos unt (ow - 1) in
                   let signbit = G.lshift unt' one shiftamount in
                   let testsignbit = G.bitand unt' signbit wide_e1' in
                   let nw_ones = makeones pos unt nw in
                   let ow_ones = makeones pos unt ow in
                   let ones = G.sub unt' nw_ones ow_ones in
                   let zero = makeconst pos unt 0 in
                   let maybeones = G.condexpr unt' testsignbit ones zero in
                   let extended_e1' = G.bitor unt' wide_e1' maybeones in
                   G.CAST (nt', unt', extended_e1')
                else if nw < ow then
                   (* signed narrow *)
                   G.CAST (nt', ot', e1')
                else
                   (* nop, just discard it *)
                   e1'
           | WIDTHTYPE ("uint", nw), WIDTHTYPE ("int", ow) ->
                if ow = nw then
                   (* safe signedness change *)
                   G.CAST (nt', ot', e1')
                else
                   Pos.crashat pos "expremit: Unsafe signedness change cast"
           | WIDTHTYPE ("int", nw), WIDTHTYPE ("uint", ow) ->
                if ow = nw then
                   (* safe signedness change *)
                   G.CAST (nt', ot', e1')
                else
                   Pos.crashat pos "expremit: Unsafe signedness change cast"
           | EXPRTYPE _, EXPRTYPE _ ->
                (* XXX it is not clear if this should really be allowed *)
                (* XXX: do nothing, the runtime type is "struct expr *" *)
                e1'
           | _, _ ->
                Pos.crashat pos "expremit: invalid cast expression"
     end
   | EVAL (pos, ty, _relfield, _reloffset, _ty'e, e) ->
        let e' = emit'expr' ctx e in
        ctx.emit'eval pos ty e'
   | UNEVAL (pos, _ty, _e) ->
        (* XXX *)
        Pos.crashat pos "expremit: uneval expression (NOTYET)"
   | ANNOTATE (_pos, _ty, e) ->
        emit'expr' ctx e
   | COMMENTED (txt, e) ->
        (* XXX shouldn't we carry these around? *)
        let pos = exprpos e in
        let ty = exprtype e in
        G.EXPRCOMMENT (TE.emit'type pos ty, txt, emit'expr' ctx e)

let emit'expr e =
   emit'expr' defaultctx e
