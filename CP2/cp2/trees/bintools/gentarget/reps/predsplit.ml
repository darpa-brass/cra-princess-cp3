(*
 * Copyright (c) 2018
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

open Exprrep

(*
 * Split up instruction predicates.
 *
 * First, convert to conjunctive normal form and make a list of
 * clauses to be ANDed together.
 *
 * Second, divide the list into two parts that do and do not depend on
 * the predicate args. These will be consumed by genhazmachine and
 * genencodings respectively.
 *
 * This runs on Exprrep (not on Exprtree) and should be run after
 * type inference and typechecking so we have types to tell which
 * expressions are boolean. And so we aren't forced to deal with
 * ill-formed expressions.
 *
 * This means that it should be called separately from both
 * genhazmachine and genencodings, specifically on the expressions
 * from the hazard predicates. The top-level iteration will probably
 * need to be different in each case. Also we need to be certain that
 * nothing run first changes the expressions such that genhazmachine
 * and genencodings get different results, as that would make a big
 * mess.
 *)

(* begin mandatory cutpaste *)
type which = TAKE_ARGDEP | TAKE_ARGINDEP
(* end mandatory cutpaste *)

(* local temporary expression type to make things more concise *)
type myexpr =
     MYLEAF of expr
   | MYCONST of Pos.pos * bool
   | MYNOT of Pos.pos * myexpr
   | MYAND of Pos.pos * myexpr * myexpr
   | MYOR of Pos.pos * myexpr * myexpr

let booltype = Typerep.booltype

(**************************************************************)
(* pre-pass *)

(*
 * Pre-pass: examine the boolean portion of the expression and
 * convert to myexpr. This means:
 *    - change e1 EQ e2 to NOT (e1 XOR e2) if boolean
 *    - then change e1 XOR e2 to (a || b) && (!a || !b)
 *    - remove vacuous CAST
 *    - remove redundant ANNOTATE
 *    - remove COMMENTED
 *
 * plus crash on anything that turns up that shouldn't be there.
 *
 * This should give us boolean-typed leaves and expressions limited
 * to LOGAND LOGOR, and LOGNOT, which can be represented in myexpr.
 *)

let rec pre'expr e =
   let die pos msg =
      Pos.crashat pos ("hazpredsplit: pre'expr: " ^ msg)
   in
   let checkbooltype pos ty what =
      if ty = booltype then ()
      else die pos ("unexpected non-boolean " ^ what ^ " of type " ^ 
                    Typerep.dump'typename ty ^ "\nIn: " ^ dump'expr e)
   in
   let xor pos e1 e2 =
      let x1 = MYOR (pos, e1, e2) in
      let x2 = MYOR (pos, MYNOT (pos, e1), MYNOT (pos, e2)) in
      MYAND (pos, x1, x2)
   in
   match e with
        CONST (pos, _, _) -> die pos "unexpected CONST"
      | STRCONST (pos, _, _) -> die pos "unexpected STRCONST"
      | USEVAR (pos, ty, name) -> begin
           checkbooltype pos ty "USEVAR";
           match name with
                "true" -> MYCONST (pos, true)
              | "false" -> MYCONST (pos, false)
              | _ ->
                   (* might be an assignedvar or a use of another predicate *)
                   MYLEAF e
        end
      | USEFIELD (pos, _, _, _) -> die pos "unexpected USEFIELD"
      | OP (pos, ty, LOGAND, [e1; e2]) ->
           checkbooltype pos ty "LOGAND";
           let e1' = pre'expr e1 in
           let e2' = pre'expr e2 in
           MYAND (pos, e1', e2')
      | OP (pos, ty, LOGOR, [e1; e2]) ->
           checkbooltype pos ty "LOGOR";
           let e1' = pre'expr e1 in
           let e2' = pre'expr e2 in
           MYOR (pos, e1', e2')
      | OP (pos, ty, LOGXOR, [e1; e2]) ->
           checkbooltype pos ty "LOGXOR";
           let e1' = pre'expr e1 in
           let e2' = pre'expr e2 in
           xor pos e1' e2'
      | OP (pos, ty, LOGNOT, [e1]) ->
           checkbooltype pos ty "LOGNOT";
           let e1' = pre'expr e1 in
           MYNOT (pos, e1')
      | OP (pos, ty, EQ, [e1; e2]) ->
           checkbooltype pos ty "EQ";
           if exprtype e1 = booltype then
              let e1' = pre'expr e1 in
              let e2' = pre'expr e2 in
              MYNOT (pos, xor pos e1' e2')
           else MYLEAF e
      | OP _ -> MYLEAF e
      | FITS _ -> MYLEAF e
      | MODE _ -> MYLEAF e
      | LIST (pos, _, _) -> die pos "unexpected LIST"
      | MODIFIER (pos, _, _, _) -> die pos "unexpected MODIFIER"
      | PACK (pos, _, _, _) -> die pos "unexpected PACK"
      | CAST (pos, nty, oty, e1) ->
           checkbooltype pos nty "CAST";
           if nty <> oty then die pos "invalid cast to boolean"
           else pre'expr e1
      | EVAL (pos, _, _, _, _, _) -> die pos "unexpected EVAL"
      | UNEVAL (pos, _, _) -> die pos "unexpected UNEVAL"
      | ANNOTATE (pos, ty, e1) ->
           checkbooltype pos ty "ANNOTATE";
           pre'expr e1
      | COMMENTED (_txt, e1) -> pre'expr e1

(**************************************************************)
(* cnf *)

(*
 * conjunctive normal form: NOT and OR are pushed down and AND is
 * pulled up. This will put all the ANDs at the top, and then we
 * can extract a list of the components.
 *
 * I can haz exponential blowup!
 *)

let rec cnf'expr'top e =
    match e with
        MYNOT (_pos1, MYCONST (pos2, x)) -> MYCONST (pos2, not x)
      | MYNOT (_pos1, MYNOT (_pos2, e1)) -> e1
      | MYNOT (pos1, MYAND (pos2, e1, e2)) ->
           let e1' = cnf'expr'top (MYNOT (pos1, e1)) in
           let e2' = cnf'expr'top (MYNOT (pos1, e2)) in
           cnf'expr'top (MYOR (pos2, e1', e2'))
      | MYNOT (pos1, MYOR (pos2, e1, e2)) ->
           let e1' = cnf'expr'top (MYNOT (pos1, e1)) in
           let e2' = cnf'expr'top (MYNOT (pos1, e2)) in
           cnf'expr'top (MYAND (pos2, e1', e2'))
      | MYOR (pos1, MYAND (pos2, e1a, e1b), e2) ->
           MYAND (pos2, MYOR (pos1, e1a, e2), MYOR (pos2, e1b, e2))
      | MYOR (pos1, e1, MYAND (pos2, e2a, e2b)) ->
           MYAND (pos2, MYOR (pos1, e1, e2a), MYOR (pos2, e1, e2b))
      | _ -> e

and cnf'expr'rec e =
   match e with
        MYLEAF _ -> e
      | MYCONST _ -> e
      | MYNOT (pos, e1) ->
           let e1' = cnf'expr'rec e1 in
           cnf'expr'top (MYNOT (pos, e1'))
      | MYAND (pos, e1, e2) ->
           let e1' = cnf'expr'rec e1 in
           let e2' = cnf'expr'rec e2 in
           cnf'expr'top (MYAND (pos, e1', e2'))
      | MYOR (pos, e1, e2) ->
           let e1' = cnf'expr'rec e1 in
           let e2' = cnf'expr'rec e2 in
           cnf'expr'top (MYOR (pos, e1', e2'))

let cnf'expr e = cnf'expr'rec e

(**************************************************************)
(* listify and reconv *)

let rec listify e = match e with
     MYAND (_pos, e1, e2) ->
        let e1' = listify e1 in
        let e2' = listify e2 in
        e1' @ e2'
   | _ -> [e]

(* convert back to exprrep *)
let rec reconv e = match e with
     MYLEAF e0 -> e0
   | MYCONST (pos, x) -> USEVAR (pos, booltype, if x then "true" else "false")
   | MYNOT (pos, e1) -> OP (pos, booltype, LOGNOT, [reconv e1])
   | MYAND (pos, e1, e2) -> OP (pos, booltype, LOGAND, [reconv e1; reconv e2])
   | MYOR (pos, e1, e2) -> OP (pos, booltype, LOGOR, [reconv e1; reconv e2])

(**************************************************************)
(* uses_args *)

let isarg argmap name =
   try
      ignore (Types.StringMap.find name argmap);
      true
   with Not_found -> false

let rec expr_uses_args ctx e = match e with
     CONST _ -> false
   | STRCONST _ -> false
   | USEVAR (_pos, _ty, name) -> isarg ctx name
   | USEFIELD (_pos, _ty, e1, _name) -> expr_uses_args ctx e1
   | OP (_pos, _ty, _op, es) -> List.exists (expr_uses_args ctx) es
   | FITS (_pos, _ty, e1, _argty) -> expr_uses_args ctx e1
   | MODE _ -> false
   | LIST (_pos, _ty, es) -> List.exists (expr_uses_args ctx) es
   | MODIFIER (_pos, _ty, _name, es) -> List.exists (expr_uses_args ctx) es
   | PACK (_pos, _ty, _name, es) -> List.exists (expr_uses_args ctx) es
   | CAST (_pos, _nty, _oty, e1) -> expr_uses_args ctx e1
   | EVAL (_pos, _nty, _, _, _ty, e1) -> expr_uses_args ctx e1
   | UNEVAL (_pos, _ty, e1) -> expr_uses_args ctx e1
   | ANNOTATE (_pos, _ty, e1) -> expr_uses_args ctx e1
   | COMMENTED (_txt, e1) -> expr_uses_args ctx e1

(**************************************************************)
(* interface *)

(*
 * "which" says whether to take the expression parts that are or
 * are not listed in "argmap". "argmap" is a StringMap; doesn't
 * matter what it maps to.
 *)
let predsplit which argmap e =
   let es =
      List.map reconv (listify (cnf'expr (pre'expr e)))
   in
   let argdep e = expr_uses_args argmap e in
   let argindep e = not (expr_uses_args argmap e) in
   let f = match which with
        TAKE_ARGDEP -> argdep
      | TAKE_ARGINDEP -> argindep
   in
   List.filter f es
