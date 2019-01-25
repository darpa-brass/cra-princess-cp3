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
 * Generate encoding procedures.
 *)

module G = Gcode

open Rep

(**************************************************************)
(* context *)

(*
 * packnum is an integer that's used to number the scratch structures
 * used to generate code for PACK expressions. It's kind of a hack,
 * and we'd be better off getting rid of it and doing a transform on
 * the representation to produce the scratch vars (and the assignments
 * to them) up front.
 *
 * similarly, held is a hack used to pile up statements produced in
 * mk'expr while emitting code for PACK expressions. Currently every
 * call to hold must be followed in the same scope by a call to unhold
 * (or unhold_with) -- this is not enforced and if it gets messed up
 * the held statements will mysteriously appear in some later function
 * and cause horrible confusion. The same transform would allow
 * getting rid of it.
 *
 * Better yet would be to do a big transform pass that gets rid of
 * compound types entirely.
 *
 * XXX.
 *)

type context = {
   spec: spec;
   boundvars: Types.StringSet.t ref;
   packnum: int ref;
   held: G.stmt list ref;
}

let newcontext spec = {
   spec;
   boundvars = ref Types.StringSet.empty;
   packnum = ref 0;
   held = ref [];
}

let getpacknum ctx =
   let ret = !(ctx.packnum) in
   ctx.packnum := ret + 1;
   ret

let clearpacknum ctx =
   ctx.packnum := 0

let hold ctx stmts =
   ctx.held := !(ctx.held) @ stmts

let unhold ctx =
   let ret = !(ctx.held) in
   ctx.held := [];
   ret

let unhold_with ctx s =
   match unhold ctx with
        [] -> s
      | stmts -> G.BLOCK (stmts @ [s])

(**************************************************************)
(* code generation tools *)

let ty'ucharptr = G.POINTER G.UCHAR
let ty'u32 = G.TYPEDEFNAME "uint32_t"
let ty'label = G.POINTER (G.STRUCTTYPE "label")
let ty'operator = G.ENUMTYPE "operators"
let ty'expr = G.POINTER (G.STRUCTTYPE "expr")
let ty'reginfo = G.STRUCTTYPE "reginfo"

let ty'tok = G.ENUMTYPE "toktypes"
let ty'ttok = G.ENUMTYPE "targettoktypes"

let ty'relocfield = G.ENUMTYPE "reloc_field"

let ty'umachword = G.TYPEDEFNAME "u_machword"
let ty'umachlarge = G.TYPEDEFNAME "u_machlarge"

(**************************************************************)
(* support *)

let varname name =
   let len = String.length name in
   if String.get name 0 = '.' then
      "var__" ^ String.sub name 1 (len - 1)
   else
      "var_" ^ name

let string_of_const c = match c with
     SMALL k -> string_of_int k
   | LARGE k -> Types.Wide.to_string k

let mk'type ctx t = match t with
     PLAINTYPE "bool" -> G.BOOL
   | PLAINTYPE name -> begin
        (* XXX probably wrong in the long run *)
        try
           let _ = Types.StringMap.find name ctx.spec.compoundtypes in
           G.POINTER (G.STRUCTTYPE ("compound_" ^ name))
        with Not_found ->
           G.TYPEDEFNAME name
     end
   | WIDTHTYPE ("int", n) -> G.TYPEDEFNAME (inttype n)
   | WIDTHTYPE ("uint", n) -> G.TYPEDEFNAME (uinttype n)
   | WIDTHTYPE ("zeros", n) -> G.TYPEDEFNAME (uinttype n)
   | WIDTHTYPE ("ones", n) -> G.TYPEDEFNAME (uinttype n)
   | EXPRTYPE _ -> ty'expr
   | LISTTYPE _ -> Util.crash "mkencoding: mk'type: list type"
   | TMPTYPE _ -> Util.crash "mkencoding: mk'type: leftover scratch type"
   | _ -> Util.crash "mkencoding: mk'type: unexpected type"

let field_cutype t = match t with
     WIDTHTYPE ("int", n) -> G.TYPEDEFNAME (uinttype n)
   | WIDTHTYPE ("uint", n) -> G.TYPEDEFNAME (uinttype n)
   | WIDTHTYPE ("zeros", n) -> G.TYPEDEFNAME (uinttype n)
   | WIDTHTYPE ("ones", n) -> G.TYPEDEFNAME (uinttype n)
   | _ -> Util.crash "mkencoding: field_cutype: unexpected type"

let fieldtypewidth t = match t with
     WIDTHTYPE ("int", n) -> n
   | WIDTHTYPE ("uint", n) -> n
   | WIDTHTYPE ("zeros", n) -> n
   | WIDTHTYPE ("ones", n) -> n
   | _ -> Util.crash "mkencoding: fieldtypewidth: unexpected type"

(**************************************************************)
(* output *)

(* XXX this needs to be configurable *)
let sendunit ctx e =
   let name = "add" ^ string_of_int ctx.spec.pcunitwidth in
   let lineno = G.READVAR (G.INT, "line") in
   [G.voidcall name [lineno; e]]

(**************************************************************)
(* exprs *)

let rec scratchvars'expr ctx e =
   let r1 e1 = scratchvars'expr ctx e1 in
   let rn es = List.concat (List.map (scratchvars'expr ctx) es) in
   match e with
        CONST _ -> []
      | STRCONST _ -> []
      | USEVAR _ -> []
      | USEFIELD (_pos, _ty, e1, _name) -> r1 e1
      | OP (_pos, _ty, _op, args) -> rn args
      | FITS (_pos, _ty, e1, _argty) -> r1 e1
      | MODE _ -> []
      | LIST (_pos, _ty, elems) -> rn elems
      | MODIFIER (_pos, _ty, _opname, args) -> rn args
      | PACK (_pos, _ty, ctor, args) ->
           let n = string_of_int (getpacknum ctx) in
           G.LOCAL (G.STRUCTTYPE ("compound_" ^ ctor), "pack_" ^ n) ::
           rn args
      | CAST (_pos, _nty, _oty, e1) -> r1 e1
      | EVAL (_pos, _nty, _relname, _reloffset, _oty, e1) -> r1 e1
      | UNEVAL (_pos, _ty, e1) -> r1 e1
      | ANNOTATE (_pos, _t, e1) -> r1 e1
      | COMMENTED (_, e1) -> r1 e1

let makeconst' ctx ty k =
   let s = string_of_const k in
   let suffix = match ty with
        WIDTHTYPE ("uint", w) ->
           if w > 32 then "UL" else "U"
      | WIDTHTYPE ("int", w) ->
           if w > 32 then "L" else ""
      | _ ->
           Util.crash "mkencoding: makeconst: invalid type"
   in
   G.INTCONSTANT (mk'type ctx ty, s ^ suffix)

let makeconst ctx ty x =
   makeconst' ctx ty (SMALL x)

let makeones ctx ty bits =
   makeconst' ctx ty (LARGE (Types.Wide.ones bits))

let mk'op ty op args = match op, args with
     EQ, [e1; e2] -> G.eq e1 e2
   | LT, [e1; e2] -> G.lt e1 e2
   | STRCAT, [e1; e2] -> G.call G.INT "dostrdup2" [e1; e2]
   | ADD, [e1; e2] -> G.add ty e1 e2 
   | SUB, [e1; e2] -> G.sub ty e1 e2
   | MUL, [e1; e2] -> G.mul ty e1 e2
   | DIV, [e1; e2] -> G.div ty e1 e2
   | MOD, [e1; e2] -> G.mod_ ty e1 e2
   | NEG, [e1]     -> G.neg ty e1
   | SHL, [e1; e2] -> G.lshift ty e1 e2
   | SHR, [e1; e2] -> G.rshift ty e1 e2
   | BITAND, [e1; e2] -> G.bitand ty e1 e2
   | BITOR, [e1; e2]  -> G.bitor ty e1 e2
   | BITXOR, [e1; e2] -> G.bitxor ty e1 e2
   | BITNOT, [e1]     -> G.bitnot ty e1
   | LOGAND, [e1; e2] -> G.logand e1 e2
   | LOGOR, [e1; e2]  -> G.logor e1 e2
   | LOGXOR, [e1; e2] ->
        let t = G.boolconst true in
        G.lognot (G.eq (G.eq e1 t) (G.eq e2 t))
   | LOGNOT, [e1]     -> G.lognot e1
   | CONSTP, [e1] -> G.call G.BOOL "is_constant" [e1]
   | DEFINEDP, [e1] -> G.call G.BOOL "has_defined_symbols" [e1]
   | ORD, [e1] -> e1

     (* illegal cases - enumerate to avoid forgetting new ops when added *)

   | IN, _ -> Util.crash "mkencoding: mk'op: Leftover IN operator"

   | EQ, _ | LT, _
   | STRCAT, _
   | ADD, _ | SUB, _ | MUL, _ | DIV, _ | MOD, _ | NEG, _
   | SHL, _ | SHR, _
   | BITAND, _ | BITOR, _ | BITXOR, _ | BITNOT, _
   | LOGAND, _ | LOGOR, _ | LOGXOR, _ | LOGNOT, _
   | CONSTP, _ | DEFINEDP, _
   | ORD, _ ->
        Util.crash "mkencoding: mk'op: illegal operator signature"

let mk'op'expr pos op args =
   let unary opname e1 =
      G.call ty'expr "mkexpr_unary" [G.READVAR (ty'operator, opname); e1]
   in
   let binary e1 opname e2 =
      G.call ty'expr "mkexpr_binary" [e1; G.READVAR (ty'operator, opname); e2]
   in
   let bad s =
      Pos.crashat pos ("mkencoding: mk'op'expr: Unexpected operator " ^ s)
   in
   match op, args with
        ADD, [e1; e2] -> binary e1 "OP_ADD" e2
      | SUB, [e1; e2] -> binary e1 "OP_SUB" e2
      | NEG, [e1] -> unary "OP_NEG" e1
      | EQ, _ -> bad "eq"
      | LT, _ -> bad "lt"
      | MUL, _ -> bad "mul"
      | DIV, _ -> bad "div"
      | MOD, _ -> bad "mod"
      | SHL, _ -> bad "shl"
      | SHR, _ -> bad "shr"
      | BITAND, _ -> bad "bitand"
      | BITOR, _ -> bad "bitor"
      | BITXOR, _ -> bad "bitxor"
      | BITNOT, _ -> bad "bitnot"
      | LOGAND, _ -> bad "logand"
      | LOGOR, _ -> bad "logor"
      | LOGXOR, _ -> bad "logxor"
      | LOGNOT, _ -> bad "lognot"
      | IN, _ ->
           Pos.crashat pos "mkencoding: mk'op'expr: Leftover IN operator"
      | _, _ ->
           Pos.crashat pos "mkencoding: mk'op'expr: Bad operator signature"

let rec mk'expr ctx e =
  let bad pos msg =
     Pos.crashat pos ("mkencoding: mk'expr: illegal expression: " ^ msg)
  in
  match e with
     CONST (pos, PLAINTYPE "bool", k) ->
        let k' = match k with
              SMALL 0 -> false
            | SMALL 1 -> true
            | _ -> bad pos ("invalid boolean " ^ string_of_const k)
        in
        G.boolconst k'
   | CONST (pos, ty, k) ->
        let suffix = match ty with
             WIDTHTYPE ("int", n) -> if n <= 32 then "" else "LL"
	   | WIDTHTYPE ("uint", n)
	   | WIDTHTYPE ("zeros", n)
	   | WIDTHTYPE ("ones", n) -> if n <= 32 then "U" else "ULL"

	   | PLAINTYPE name -> bad pos ("number constant of type " ^ name)
	   | WIDTHTYPE (name, _) -> bad pos ("number constant of type " ^ name)
	   | EXPRTYPE _ -> bad pos "numeric constant of expression type"
	   | LISTTYPE _ -> bad pos "numeric constant of list type"
	   | TMPTYPE _ -> bad pos "unresolved scratch type"
        in            
        let ks = string_of_const k ^ suffix in
        G.INTCONSTANT (mk'type ctx ty, ks)
   | STRCONST (_pos, _ty, s) ->
        (* these are not allowed to appear here, but whatever *)
        G.STRINGCONSTANT s
   | USEVAR (_pos, ty, name) ->
        (* blah this is ugly *)
        if ty = PLAINTYPE "bool" then
           G.READVAR (G.BOOL, name)
        else if name = "." then
           G.call ty'expr "mkexpr_label" [
                 G.call ty'label "label_declaredot" [G.READVAR (G.INT, "line")]
           ]
        else
           G.READVAR (mk'type ctx ty, varname name)
   | USEFIELD (pos, _t, _e1, _name) ->
        (* these aren't allowed/possible in here *)
        bad pos "structure field reference"
   | OP (pos, t, op, args) -> begin
        match t with
             (* XXX *)
             EXPRTYPE _ ->
                mk'op'expr pos op (List.map (mk'expr ctx) args)
           | WIDTHTYPE ("int", _)
           | WIDTHTYPE ("uint", _)
           | _ -> mk'op (mk'type ctx t) op (List.map (mk'expr ctx) args)
     end
   | FITS (pos, _t, e1, argty) -> begin
        (*
         * typecheck checks that e1 and argty have the same signedness, so
         * we don't need to check again here.
         *
         * XXX: maybe we should remove FITS expressions upstream and
         * replace them with comparisons.
         *)
        let e1' = mk'expr ctx e1 in
        let ty'e1 = exprtype e1 in
        let ty'e1' = mk'type ctx ty'e1 in
        match argty with
            WIDTHTYPE ("uint", width) ->
               let ones = makeones ctx ty'e1 width in
               mk'op G.BOOL LOGNOT [mk'op ty'e1' LT [ones; e1']]
          | WIDTHTYPE ("int", width) ->
               let ones = makeones ctx ty'e1 (width - 1) in
               let negones = mk'op ty'e1' NEG [ones] in
               let one = makeconst ctx ty'e1 1 in
               let minval = G.sub ty'e1' negones one in
               let postest = G.lognot (G.lt ones e1') in
               let negtest = G.lognot (G.lt e1' minval) in
               G.logand postest negtest
          | _ -> Pos.crashat pos "mkencoding: invalid FITS type"
     end
   | MODE (_pos, modename) ->
        G.call G.BOOL "modeison" [G.STRINGCONSTANT modename]
   | LIST (pos, _t, _elems) -> bad pos "list expression" (* XXX do we need this? *)
   | MODIFIER (_pos, _t, modname, args) ->
        let modname' = G.STRINGCONSTANT modname in
        let args' = List.map (mk'expr ctx) args in
        G.call ty'expr "mkexpr_modifier" (modname' :: args')
   | PACK (_pos, _ty, ctor, args) -> begin
        let n = getpacknum ctx in
        let gty = G.STRUCTTYPE ("compound_" ^ ctor) in
        let tmp = G.READVAR (gty, "pack_" ^ string_of_int n) in
        let assignone (i, arg) =
           let ty'arg' = mk'type ctx (exprtype arg) in
           G.ASSIGN (G.WRITEFIELD (ty'arg', tmp, "m" ^ string_of_int i),
                     mk'expr ctx arg)
        in
        let assigns = List.map assignone (Util.number args) in
        hold ctx assigns;
        G.addrof (G.POINTER gty) tmp

(*
        (* XXX this should not be hardwired *)
        (* XXX also note that mkexpr calls need expr_destroy to not leak *)
        match ctor, args with
             "mem", [offset; reg] ->
                let offset' = mk'expr ctx offset in
                let reg' = mk'expr ctx reg in

                (* AAAARGH *)
                let ttok_reg = G.READVAR (ty'ttok, "TTOK_REGCLASS_GENERALREG") in
                let reg_e = G.call ty'expr "mkexpr_targetnum" [ttok_reg; reg'] in

                let parens = G.READVAR (ty'operator, "OP_PARENS") in
                let parenreg = G.call ty'expr "mkexpr_unary" [parens; reg_e] in
                G.call ty'expr "mkexpr_juxtapose" [offset'; parenreg]
           | _, _ ->
                Pos.crashat pos ("Cannot pack values of type " ^ ctor ^ " yet")
*)
     end
   | CAST (pos, nt, ot, e1) -> begin
        let e1' = mk'expr ctx e1 in
        let nt' = mk'type ctx nt in
        let ot' = mk'type ctx ot in
        match nt, ot with
             WIDTHTYPE ("uint", nw), WIDTHTYPE ("uint", ow)
           | WIDTHTYPE ("uint", nw), WIDTHTYPE ("zeros", ow)
           | WIDTHTYPE ("uint", nw), WIDTHTYPE ("ones", ow) ->
                if nw > ow then
                   (* unsigned widen *)
                   G.CAST (mk'type ctx nt, mk'type ctx ot, e1')
                else if nw < ow then
                   (* unsigned narrow *)
                   G.CAST (mk'type ctx nt, mk'type ctx ot, e1')
                else
                   (* nop, just discard it *)
                   e1'
           | WIDTHTYPE ("int", nw), WIDTHTYPE ("int", ow) ->
                let unt = WIDTHTYPE ("uint", nw) in
                let uot = WIDTHTYPE ("uint", ow) in
                let unt' = mk'type ctx unt in
                let uot' = mk'type ctx uot in
                if nw > ow then
                   (* signed widen *)
                   let unsigned_e1' = G.CAST (uot', ot', e1') in
                   let wide_e1' = G.CAST (unt', uot', unsigned_e1') in
                   let one = G.one unt' in
                   let shiftamount = makeconst ctx unt (ow - 1) in
                   let signbit = G.lshift unt' one shiftamount in
                   let testsignbit = G.bitand unt' signbit wide_e1' in
                   let nw_ones = makeones ctx unt nw in
                   let ow_ones = makeones ctx unt ow in
                   let ones = G.sub unt' nw_ones ow_ones in
                   let zero = G.zero unt' in
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
                   Pos.crashat pos "mkencoding: Unsafe signedness change cast"
           | WIDTHTYPE ("int", nw), WIDTHTYPE ("uint", ow) ->
                if ow = nw then
                   (* safe signedness change *)
                   G.CAST (nt', ot', e1')
                else
                   Pos.crashat pos "mkencoding: Unsafe signedness change cast"
           | _, _ ->
                bad pos "invalid cast expression"
     end
   | EVAL (_pos, _nt, relname, reloffset, _ot, e1) -> begin
        let e1' = mk'expr ctx e1 in
        let lineno = G.READVAR (G.INT, "line") in
        let rfield = G.READVAR (ty'relocfield, "RELOC_FIELD_" ^ relname) in
        let roffset = G.INTCONSTANT (ty'umachword, string_of_int reloffset) in
        G.call ty'umachlarge "process_expr" [lineno; e1'; rfield; roffset]
     end
   | UNEVAL (_pos, _ty, e1) ->
        let e1' = mk'expr ctx e1 in
        (* XXX what if e1 isn't a number? *)
        G.call ty'expr "mkexpr_number" [e1']
   | ANNOTATE (_pos, _ty, e1) ->
        (* can just discard the annotation (XXX: is this what we want?) *)
        mk'expr ctx e1
   | COMMENTED (text, e1) ->
        let e1' = mk'expr ctx e1 in
        G.EXPRCOMMENT (G.gexprtype e1', text, e1')


(**************************************************************)
(* statements *)

let rec scratchvars'pat ctx pat t = match pat with
     SETVAR (_pos, name) ->
        if not (Types.StringSet.mem name !(ctx.boundvars)) then begin
           ctx.boundvars := Types.StringSet.add name !(ctx.boundvars);
           [G.LOCAL (mk'type ctx t, varname name)]
        end else
           []
   | UNPACK (_pos, "modimm", [arg0; arg1]) ->
        (* XXX this should not exist *)
        scratchvars'pat ctx arg0 (WIDTHTYPE ("uint", 4)) @
        scratchvars'pat ctx arg1 (WIDTHTYPE ("uint", 8))
   | UNPACK (_pos, ctor, subpats) ->
        let ct = Types.StringMap.find ctor ctx.spec.compoundtypes in
        let recurse (subpat, (_pos, subt)) =
           scratchvars'pat ctx subpat subt
        in
        List.concat (List.map recurse (Util.zip subpats ct.members))

let scratchvars'assignment ctx (_pos, pat, e) =
   let t = exprtype e in
   scratchvars'pat ctx pat t @
     scratchvars'expr ctx e

let rec scratchvars'statement ctx s = match s with
     ASSIGN a -> scratchvars'assignment ctx a
   | IF (_pos, cond, t, f) ->
        scratchvars'expr ctx cond @
          List.concat (List.map (scratchvars'statement ctx) t) @
          List.concat (List.map (scratchvars'statement ctx) f)
   | USE (_pos, _name, specargs, opargs, _mname) ->
        List.concat (List.map (scratchvars'expr ctx) specargs) @
          List.concat (List.map (scratchvars'expr ctx) opargs)
   | EMIT (_pos, e) ->
        scratchvars'expr ctx e
   | HOOK (_pos, _name, args) ->
        List.concat (List.map (scratchvars'expr ctx) args)
   | WARN _ -> []

(*
 * Check that an operand of compound type matches the expected
 * structure.
 *
 * Note that in theory the operand matching should guarantee the
 * structure of the input expression matches what's expected. But
 * that's not in place yet. (XXX)
 *)
(*
let fieldcheck ctx e ctor =
    let _ct = Types.StringMap.find ctor ctx.spec.compoundtypes in

    (*
     * For now we have only one of these, and it's "mem": offset(reg).
     * XXX this should be driven by the compound type decl for "mem".
     *)

(*
    let stringeq e1 e2 = G.lognot (G.call G.int "strcmp" [e1; e2]) in
*)

    (* top level is juxtapose *)
    let e_type = G.READFIELD (G.ENUMTYPE "exprtypes", e, "x_type") in

    (* lhs is arbitrary *)
    (*let lhs = G.READFIELD (ty'expr, e, "x_u.u_juxtapose.arg1") in*)

    (* rhs is a register in parens *)
    let rhs_xu = G.READFIELD (G.UNIONTYPE "", e, "x_u") in
    let rhs_jux = G.READFIELD (G.STRUCTTYPE "", rhs_xu, "u_juxtapose") in
    let rhs = G.READFIELD (ty'expr, rhs_jux, "arg2") in
    let rhs_type = G.READFIELD (G.ENUMTYPE "exprtypes", rhs, "x_type") in
    let rhs_oper' = G.READFIELD (G.UNIONTYPE "", rhs, "x_u") in
    let rhs_oper = G.READFIELD (G.STRUCTTYPE "", rhs_oper', "u_operator") in
    let rhs_op = G.READFIELD (G.ENUMTYPE "operators", rhs_oper, "op") in
    let rhs_arg1 = G.READFIELD (ty'expr, rhs_oper, "arg1") in
    let rhs_arg2 = G.READFIELD (ty'expr, rhs_oper, "arg2") in
    let rhs_arg1_type = G.READFIELD (G.ENUMTYPE "exprtypes", rhs_arg1, "x_type") in
    let rhs_arg1_targ' = G.READFIELD (G.UNIONTYPE "", rhs_arg1, "x_u") in
    let rhs_arg1_targ = G.READFIELD (G.STRUCTTYPE "", rhs_arg1_targ', "u_target") in
    let rhs_arg1_ttok = G.READFIELD (G.ENUMTYPE "targettokentypes", rhs_arg1_targ, "ttok") in
    (*let e_rhs_arg1_val = G.READFIELD (ty, rhs_arg1_targ, "val") in*)

    [
       G.ASSERT(G.eq e_type (G.READVAR (G.ENUMTYPE "exprtypes", "EXPR_JUXTAPOSE")));

       G.ASSERT(G.eq rhs_type (G.READVAR (G.ENUMTYPE "exprtypes", "EXPR_OPERATOR")));
       G.ASSERT(G.eq rhs_arg2 G.null);
       G.ASSERT(G.eq rhs_op (G.READVAR (G.ENUMTYPE "exprtypes", "OP_PARENS")));
       G.ASSERT(G.eq rhs_arg1_type (G.READVAR (G.ENUMTYPE "exprtypes", "EXPR_TARGET")));
       G.ASSERT(G.eq rhs_arg1_ttok (G.READVAR (G.ENUMTYPE "targettokentypes", "TTOK_REGCLASS_GENERALREG")));
    ]
*)

let (*rec*) patprepare _ctx _e pat : G.stmt list = match pat with
     SETVAR (_pos, _name) -> []
   | UNPACK (_pos, _ctor, _subpats) -> []
(*
        (fieldcheck ctx e ctor) @
           List.concat (List.map (patprepare ctx e) subpats)
*)

(*
 * Retrieve the n'th field of compound type named by ctor, in e.
 *)
let compoundfield ctx e ctor n =
   let ct = Types.StringMap.find ctor ctx.spec.compoundtypes in
   let (_mpos, mty) = List.nth ct.members n in
   let mty' = mk'type ctx mty in
   G.READFIELD (mty', e, "m" ^ string_of_int n)

(*
   let ty'x_u = G.UNIONTYPE "" in
   let ty'u_targ = G.STRUCTTYPE "" in
   let ty'val = G.charptr in
   let ty'u_op = G.STRUCTTYPE "" in
   let ty'u_jux = G.STRUCTTYPE "" in

   let x_u ee = G.READFIELD (ty'x_u, ee, "x_u") in
   let u_jux ee = G.READFIELD (ty'u_jux, x_u ee, "u_juxtapose") in
   let u_op ee = G.READFIELD (ty'u_op, x_u ee, "u_operator") in
   let u_targ ee = G.READFIELD (ty'u_targ, x_u ee, "u_target") in

   (*
    * For now we have only one of these, and it's "mem": offset(reg).
    * XXX this should be driven by the compound type decl for "mem".
    *)   
   match n with
        0 -> G.READFIELD (ty'expr, u_jux e, "arg1")
      | 1 ->
           let rhs = G.READFIELD (ty'expr, u_jux e, "arg2") in
           let rhs_sub = G.READFIELD (ty'expr, u_op rhs, "arg1") in
           let val_ = G.READFIELD (ty'val, u_targ rhs_sub, "val") in
           G.call G.INT "atoi" [val_]
      | _ -> assert(false) (* out of range compoundfield *)
*)

let rec patassign ctx pat e = match pat with
     SETVAR (_pos, name) ->
        let ty = G.gexprtype e in (* XXX *)
        G.ASSIGN (G.WRITEVAR (ty, varname name), e)
   | UNPACK (_pos, "modimm", [arg0; arg1]) ->
        (* XXX this should not exist *)
        let ln = G.READVAR (G.INT, "line") in
        G.BLOCK [
           patassign ctx arg0 (G.call G.UINT "modimm_hack_a" [ln; e]);
           patassign ctx arg1 (G.call G.UINT "modimm_hack_b" [ln; e]);
        ]
   | UNPACK (_pos, ctor, subpats) -> 
        let recurse (n, subpat) =
           patassign ctx subpat (compoundfield ctx e ctor n)
        in
        G.BLOCK (List.map recurse (Util.number subpats))

let rec mk'statement ctx s = match s with
     ASSIGN (_pos, pat, e) -> begin
        let e' = mk'expr ctx e in

        let a = (patassign ctx pat e') in

        (* XXX get rid of this match eventually; for now reduce output diff *)
        let held = unhold ctx in
        match held, patprepare ctx e' pat with
             [], [] -> a
           | stmts1, stmts2 -> G.BLOCK (stmts1 @ stmts2 @ [a]) (* XXX unwrap a *)
     end
   | USE (_pos, _name, args, ops, resolvedname) ->
        let lineno = G.READVAR (G.INT, "line") in
        let args' = List.map (mk'expr ctx) args in
        let ops' = List.map (mk'expr ctx) ops in
        unhold_with ctx (G.voidcall resolvedname (lineno :: args' @ ops'))
   | IF (_pos, c, t, f) ->
        let block ss = G.BLOCK (List.map (mk'statement ctx) ss) in
        let c' = mk'expr ctx c in
        unhold_with ctx (G.IF (c', block t, block f))
   | EMIT (_pos, e) ->
        let e' = mk'expr ctx e in
        unhold_with ctx (G.BLOCK (sendunit ctx e'))
   | HOOK (_pos, name, args) ->
        let args' = List.map (mk'expr ctx) args in
        unhold_with ctx (G.voidcall name args')
   | WARN (_pos, text) ->
        (* XXX might need to escape parts of the message... *)
        G.voidcall "file_warn" [
			G.READVAR (G.INT, "line");
			G.STRINGCONSTANT text;
		 ]


(**************************************************************)
(* encodings *)

let scratchvars'alternative ctx (_pos, guard, results) =
   scratchvars'expr ctx guard @
   List.concat (List.map (scratchvars'statement ctx) results)

let mk'alternative ctx (_pos, guard, results) =
   let s = G.BLOCK ((List.map (mk'statement ctx) results) @ [G.retvoid]) in
   let guard' = mk'expr ctx guard in
   unhold_with ctx (G.IF (guard', s, G.skip))

let encoding_macro_params ctx specargs opargs =
   let one_param (_pos, name, t) =
      ctx.boundvars := Types.StringSet.add name !(ctx.boundvars);
      [(mk'type ctx t, varname name)]
   in
     List.concat (List.map one_param specargs)
   @ List.concat (List.map one_param opargs)

let ignore_encoding_macro_params ctx specargs opargs =
   let one_param (_pos, name, t) =
      if name = "_" then [G.IGNORE (G.READVAR (mk'type ctx t, varname name))]
      else []
   in
   List.concat (List.map one_param (specargs @ opargs))

let mk'encodingdecl ctx ({ mangledname; specargs; opargs; _ } : encoding) =
   let params = encoding_macro_params ctx specargs opargs in
   let lineno = (G.INT, "line") in
   let params = lineno :: params in
   G.FUNCDECL (G.STATIC, G.VOID, mangledname, params)

let mk'encoding ctx { name; mangledname; definedat; specargs; opargs;
                      alternatives; _ } =
   ctx.boundvars := Types.StringSet.empty;

   let params = encoding_macro_params ctx specargs opargs in
   let lineno = (G.INT, "line") in
   let params = lineno :: params in

   let ignores = ignore_encoding_macro_params ctx specargs opargs in

   clearpacknum ctx;
   let scratch =
      List.concat (List.map (scratchvars'alternative ctx) alternatives)
   in
   clearpacknum ctx;

   let stmts =
        scratch
      @ [G.BLANKLINESTMT]
      @ ignores
      @ List.map (mk'alternative ctx) alternatives
   in

   [
      G.DECLCOMMENT ("Encoding " ^ name ^ " defined at " ^
		      Pos.string_of_pos definedat);
      G.FUNCTION (G.STATIC, G.VOID, mangledname, params, G.BLOCK stmts);
      G.BLANKLINEDECL;
   ]


(**************************************************************)
(* macros *)

let scratchvars'expansion ctx (_pos, guard, stmts) =
   scratchvars'expr ctx guard @
   List.concat (List.map (scratchvars'statement ctx) stmts)

let mk'expansion ctx (_pos, guard, stmts) =
   let s = G.BLOCK ((List.map (mk'statement ctx) stmts) @ [G.retvoid]) in
   let guard' = mk'expr ctx guard in
   unhold_with ctx (G.IF (guard', s, G.skip))

let mk'macrodecl ctx ({ mangledname; specargs; opargs; _ } : macro) =
   let params = encoding_macro_params ctx specargs opargs in
   let lineno = (G.INT, "line") in
   let params = lineno :: params in
   G.FUNCDECL (G.STATIC, G.VOID, mangledname, params)

let mk'macro ctx { name; mangledname; definedat; specargs; opargs;
		   expansions; } =

   ctx.boundvars := Types.StringSet.empty;

   let params = encoding_macro_params ctx specargs opargs in
   let lineno = (G.INT, "line") in
   let params = lineno :: params in

   let ignores = ignore_encoding_macro_params ctx specargs opargs in

   clearpacknum ctx;
   let scratch =
      List.concat (List.map (scratchvars'expansion ctx) expansions)
   in
   clearpacknum ctx;

   let stmts =
        scratch
      @ [G.BLANKLINESTMT]
      @ ignores
      @ List.map (mk'expansion ctx) expansions
   in

   (*
    * For now silence all unused variable warnings in the output code.
    * This should become more discriminating so it still warns about
    * real issues while not warning about, e.g. variables assigned at
    * the form level that are not used in macros defined in that form.
    * Or maybe not - we should probably be issuing such warnings
    * ourselves anyway. XXX(?)
    *
    * Also, we ought to be able to avoid emitting the unused variables
    * entirely. XXX.
    *
    * Note: this logic must come *after* scratchvars'expansion so that
    * ctx.boundvars is fully populated. Otherwise it doesn't work to
    * silence the warnings that actually appear.
    *)
   let ignoreit name = G.IGNORE (G.READVAR (G.UINT(*XXX*), varname name)) in
   let
      ignvars = List.map ignoreit (Types.StringSet.elements !(ctx.boundvars))
   in
   let stmts = stmts @ ignvars in

   [
      G.DECLCOMMENT ("Macro " ^ name ^ " defined at " ^
		      Pos.string_of_pos definedat);
      G.FUNCTION (G.STATIC, G.VOID, mangledname, params, G.BLOCK stmts);
      G.BLANKLINEDECL;
   ]

(**************************************************************)
(* instruction *)

let instruction_params ctx operands =
   (* XXX how much of this mess is really necessary? *)
   let paraminfo (i, t) =
      (mk'type ctx t, mk'type ctx t, "op_" ^ string_of_int i)
   in
   let info =
      List.map paraminfo (Util.number operands)
   in
   let hparams = List.map (fun (_, xt, n) -> (xt, n)) info in
   let cparams = List.map (fun (it, _, n) -> (it, n)) info in
   let readparams = List.map (fun (it, _, n) -> G.READVAR (it, n)) info in
   (hparams, cparams, readparams) 

let mk'instruction ctx { name; definedat;
                         (*operands_ext;*) operands_int;
                         mangledname_ext; (*mangledname_int;*)
			 (*encoder;*) encoder_mangled; } =

   let funcname = "insn_" ^ mangledname_ext in

   let (hparams, _, readparams) = instruction_params ctx operands_int in

   let lineno = (G.INT, "line") in
   let pubparams = lineno :: hparams in

   let uselineno = G.READVAR (G.INT, "line") in
   let pubopargs = uselineno :: readparams in
   let pubstmts = [
      G.voidcall encoder_mangled pubopargs;
   ]
   in
   [
      G.DECLCOMMENT ("Insn " ^ name ^ " defined at " ^
		      Pos.string_of_pos definedat);
      G.FUNCTION (G.GLOBAL, G.VOID, funcname, pubparams, G.BLOCK pubstmts);
      G.BLANKLINEDECL;
   ]

let mk'header ctx { mangledname_ext; operands_int; _ } =
   let funcname = "insn_" ^ mangledname_ext in

   let (hparams, _, _) = instruction_params ctx operands_int in

   G.FUNCDECL (G.GLOBAL, G.VOID, funcname, hparams)

(**************************************************************)
(* reginfo hacks *)

(* see transform.ml for more info *)
(* XXX XXX all gross and ultimately mips-specific *)

(* the general form of this is taken from the older handwritten version *)

let reginfo_hook_decls () =
   let ty'u32ptr = G.POINTER ty'u32 in

   let hookfunc what extras =
      let read'reginfo = G.READVAR (ty'u32, "myreginfo.r_" ^ what ^ "regs") in
      G.FUNCTION (G.STATIC, G.VOID, "reginfo_use_" ^ what ^ "_reg",
                  [(G.UINT, "reg")],
         G.BLOCK (extras @ [
            G.voidcall "reginfo_use_reg" [
                       G.addrof ty'u32ptr read'reginfo;
                       G.READVAR (G.UINT, "reg");
                   ]
         ]))
   in [
   G.STRUCTDECL ("reginfo", [
                    (ty'u32, "r_gpregs");
                    (ty'u32, "r_cop0regs");
                    (ty'u32, "r_fpregs");
                    (ty'u32, "r_cop2regs");
                    (ty'u32, "r_cop3regs");
                    (ty'u32, "r_gp");
                ]);
   G.VARDECL (G.STATIC, ty'reginfo, "myreginfo");
   G.FUNCTION (G.STATIC, G.VOID, "reginfo_use_reg", [
                 (ty'u32ptr, "info");
                 (G.UINT, "reg")
               ],
     G.BLOCK [
	G.ASSERT (G.lt (G.READVAR (G.UINT, "reg"))
                       (G.INTCONSTANT (G.UINT, "32")));
	G.ASSIGN (G.WRITEPOINTER (ty'u32, G.READVAR (ty'u32ptr, "info")),
                  G.bitor ty'u32
                      (G.READPOINTER (ty'u32, G.READVAR (ty'u32ptr, "info")))
                      (G.lshift G.UINT (G.one G.UINT) (G.READVAR (G.UINT, "reg"))));
     ]);
   (* the actual hook functions called by the generated code *)
   hookfunc "gp" [G.IF (G.eq (G.READVAR (G.UINT, "reg")) (G.zero G.UINT), G.retvoid, G.skip)];
   hookfunc "cop0" [];
   hookfunc "fp" [];
   hookfunc "cop2" [];
   hookfunc "cop3" [];
]

let reginfo_generate_stmts () =
   let ty'size = G.TYPEDEFNAME "size_t" in
   let ty'reginfo = G.STRUCTTYPE "reginfo" in
   let ty'reginfoptr = G.POINTER ty'reginfo in
   let decls = [
      G.LOCAL (G.UINT, "snum");
      G.LOCAL (ty'ucharptr, "p");
      G.LOCAL (ty'size, "i");
      G.BLANKLINESTMT;
   ] in
   let stmts = [
      G.ASSIGN (G.WRITEVAR (G.UINT, "snum"),
                G.call G.UINT "getsection" [
                                  G.STRINGCONSTANT ".reginfo";
                                  G.boolconst true;
                                  G.boolconst false;
                                  G.boolconst true;
                                  G.boolconst false;
                               ]);
      (* note: that 2 is interpreted as 2^2 *)
      G.voidcall "align_section" [
            G.READVAR (G.UINT, "snum");
            G.INTCONSTANT (G.UINT, "2");
      ];
      G.ASSERT (G.eq (G.SIZEOF ty'reginfo)
                     (G.INTCONSTANT (ty'size, "24")));
      G.ASSIGN (G.WRITEVAR (ty'ucharptr, "p"),
                G.CAST (G.POINTER G.UCHAR,
                        ty'reginfoptr,
                        G.addrof ty'reginfoptr (G.READVAR (ty'reginfo, "myreginfo"))));
      G.simplefor ty'size "i" (G.zero ty'size) (G.SIZEOF ty'reginfo) [
         G.voidcall "section_addbyte" [
                    G.READVAR (G.UINT, "snum");
                    G.INTCONSTANT (G.INT, "-1");
                    G.READARRAY (G.UCHAR, G.READVAR (G.POINTER G.UCHAR, "p"),
                                 G.READVAR (ty'size, "i"));
                ];
      ];
   ] in
   decls @ stmts


(**************************************************************)
(* toplevel *)

(* XXX this is a temporary hack *)
let expr_bodges ctx =
   (*
    * XXX at some point we need to deal with this somehow/somewhere
    *)
   let hooks = if ctx.spec.do_reginfo then
      reginfo_hook_decls ()
   else []
   in
   let gensections =
      let stmts = if ctx.spec.do_reginfo then
         reginfo_generate_stmts ()
      else []
      in
      G.FUNCTION (G.GLOBAL, G.VOID, "target_generate_special_sections", [],
         G.BLOCK stmts)
   in
   let call_process_expr field =
      let callargs = [
         G.READVAR (G.INT, "linenum");
         G.READVAR (ty'expr, "x");
         G.READVAR (G.ENUMTYPE "reloc_field", field);
         G.READVAR (G.UINT, "offset");
      ] in
      let call = G.call ty'umachword "process_expr" callargs in
      G.retval call
   in
   let process_expr_qword =
      (*
       * XXX for now assume that RELOC_FIELD_DATA64 exists if and only
       * if the addresswidth is 64 bits.
       *)
      let params = [
         (G.INT, "linenum");
         (ty'expr, "x");
         (G.UINT, "offset");
      ] in
      let stmts =
         if ctx.spec.addresswidth = 64 then
            [call_process_expr "RELOC_FIELD_DATA64"]
         else
            let msg = "No 64-bit relocations on this architecture" in
            [
               G.IGNORE (G.READVAR (ty'expr, "x"));
               G.IGNORE (G.READVAR (G.UINT, "offset"));
               G.voidcall "file_err" [G.READVAR (G.INT, "linenum");
                                      G.STRINGCONSTANT msg;];
            ]
      in
      G.FUNCTION (G.GLOBAL, ty'umachword, "process_expr_qword",
                  params, G.BLOCK stmts)
   in
   let process_expr_word =
      (* XXX for now assume that RELOC_FIELD_DATA32 exists *)
      let params = [
         (G.INT, "linenum");
         (ty'expr, "x");
         (G.UINT, "offset");
      ] in
      let stmt = call_process_expr "RELOC_FIELD_DATA32" in
      G.FUNCTION (G.GLOBAL, ty'umachword, "process_expr_word",
                  params, G.BLOCK [stmt])
   in
   let process_expr_hword =
      (* XXX for now assume that RELOC_FIELD_DATA16 exists *)
      let params = [
         (G.INT, "linenum");
         (ty'expr, "x");
         (G.UINT, "offset");
      ] in
      let stmt = call_process_expr "RELOC_FIELD_DATA16" in
      G.FUNCTION (G.GLOBAL, ty'umachword, "process_expr_hword",
                  params, G.BLOCK [stmt])
   in
   hooks @ [
      gensections;
      G.BLANKLINEDECL;
      process_expr_qword;
      process_expr_word;
      process_expr_hword;
      G.BLANKLINEDECL;
   ]

let mkencoding spec _myheadername =
   let ctx = newcontext spec in

   let headers = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "stdlib.h";
      G.SYSINCLUDE "string.h";
      G.SYSINCLUDE "assert.h";
      (* XXX these really ought to be parameterized *)
      G.LOCALINCLUDE "common.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "targetdefs.h";
      G.LOCALINCLUDE "mem.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "expr.h";
      G.LOCALINCLUDE "load.h";
      G.LOCALINCLUDE "label.h";
      G.LOCALINCLUDE "section.h";
      G.LOCALINCLUDE "reloc.h";
      G.LOCALINCLUDE "sectionops.h";
      G.LOCALINCLUDE "relocops.h";
      G.LOCALINCLUDE "as.h";
      G.LOCALINCLUDE "modeinfo.h";
      G.LOCALINCLUDE "targetoper.h";
      G.LOCALINCLUDE "targetmatch.h";
      (*G.LOCALINCLUDE myheadername;*)
      G.BLANKLINEINCLUDE;
   ] in

   (* XXX: this should probably go away *)
   let bodges = expr_bodges ctx @ [G.BLANKLINEDECL] in

   let encodingdecls = List.map (mk'encodingdecl ctx) spec.encodings in
   let macrodecls = List.map (mk'macrodecl ctx) spec.macros in
   let decls = encodingdecls @ macrodecls in

   let encodings = List.map (mk'encoding ctx) spec.encodings in
   let macros = List.map (mk'macro ctx) spec.macros in
   let instructions = List.map (mk'instruction ctx) spec.instructions in
   let body = List.concat (encodings @ macros @ instructions) in

   let source = G.FILE (None, headers, bodges @ decls @ body) in

   let hdecls = List.map (mk'header ctx) spec.instructions in
   let header = G.FILE (Some "TARGETINSNS_H", [], hdecls) in

   (header, source)
