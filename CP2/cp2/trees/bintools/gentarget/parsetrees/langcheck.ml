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

open Langtree
open Typetree
open Exprtree

(**************************************************************)
(* support *)

(*
 * remember a token
 *)

let seentokens = ref Types.StringMap.empty

let addtoken pos tname ttype = 
   seentokens := Types.StringMap.add tname (pos, ttype) !seentokens

(*
 * get type of a token
 *)
let token_type t =
   try
      let (_, tt) = (Types.StringMap.find t (!seentokens)) in
      Some tt
   with Not_found -> None

(*
 * check if a token exists
 *)
let token_exists t =
   match token_type t with
        Some _ -> true
      | None -> false

(* The types legal for values in tokens *)
let ok_token_type t = match t with
     (* allow any plain type (includes enums we can't check here) *)
     Typetree.PLAINTYPE _ -> true
     (* XXX: any width, or do we make a specific type for this? *)
   | Typetree.WIDTHTYPE (_, "uint", _) -> true
   | Typetree.WIDTHTYPE (_, "int", _) -> true
     (* don't allow others (XXX: is this safe?) *)
   | Typetree.WIDTHTYPE (_, _, _) -> false
     (* do not allow expressions *)
   | Typetree.EXPRTYPE _ -> false


(**************************************************************)
(* expression eval *)

(*
 * You can eval expressions in language.def, but only those that are
 * actually constant. ("constant" is determined by the constant-folding
 * logic in the assembler.)
 *
 * Retrieve all the expressions someone calls eval on. Then for each
 * one, check to make sure that it's tested with constantp. Because of
 * the limited amount of material here we can use a very simple notion
 * of expression equivalence without getting hosed.
 *)

let rec get_evals e = match e with
     UOP (pos, EVAL, e1) -> [(pos, e1)]
   | UOP (_pos, _op, e1) -> get_evals e1
   | BOP (_pos, e1, _op, e2) -> get_evals e1 @ get_evals e2
   | FITS (_pos, e1, _ty) -> get_evals e1
   | MODE (_pos, _name) -> []
   | READVAR (_pos, _name) -> []
   | READMEMBER (_pos, e1, _name) -> get_evals e1
   | BOOLCONSTANT (_pos, _x) -> []
   | NUMCONSTANT (_pos, _x) -> []
   | STRCONSTANT (_pos, _x) -> []
   | HERE (_pos) -> []
   | LIST (_pos, es) -> List.concat (List.map get_evals es)
   | MODIFIER (_pos, _name, args) -> List.concat (List.map get_evals args)
   | PACK (_pos, _name, args) -> List.concat (List.map get_evals args)
   | CAST (_pos, _nty, _oty, e1) -> get_evals e1
   | ANNOTATE (_pos, _ty, e1) -> get_evals e1

let rec expr_equiv e e' = match e, e' with
     UOP (_, op, e1), UOP (_, op', e1') ->
        op = op' && expr_equiv e1 e1'
   | BOP (_, e1, op, e2), BOP (_, e1', op', e2') ->
        op = op' && expr_equiv e1 e1' && expr_equiv e2 e2'
   | FITS (_, e1, ty), FITS (_, e1', ty') ->
        ty = ty' && expr_equiv e1 e1'
   | MODE (_, name), MODE (_, name') ->
        name = name'
   | READVAR (_, name), READVAR(_, name') ->
        name = name'
   | READMEMBER (_, e1, name), READMEMBER (_, e1', name') ->
        name = name' && expr_equiv e1 e1'
   | BOOLCONSTANT (_, x), BOOLCONSTANT (_, x') ->
        x = x'
   | NUMCONSTANT (_, x), NUMCONSTANT (_, x') ->
        x = x'
   | STRCONSTANT (_, x), STRCONSTANT (_, x') ->
        x = x'
   | HERE (_), HERE (_) -> true
   | LIST (_, es), LIST (_, es') ->
        exprs_equiv es es'
   | MODIFIER (_, name, args), MODIFIER (_, name', args') ->
        name = name' && exprs_equiv args args'
   | PACK (_, name, args), PACK (_, name', args') ->
        name = name' && exprs_equiv args args'
   | CAST (_, nty, oty, e1), CAST (_, nty', oty', e1') ->
        nty = nty' && oty = oty' && expr_equiv e1 e1'
   | ANNOTATE (_, ty, e1), ANNOTATE (_, ty', e1') ->
        ty = ty' && expr_equiv e1 e1'
   | _, _ -> false
and exprs_equiv es es' =
   if List.length es <> List.length es' then false
   else List.fold_left2 (fun z e e' -> z && expr_equiv e e') true es es'

(*
 * Partially evaluate e under the assumption that (CONSTP d) is false.
 * Returns (Some true) or (Some false) if it has a definite value this
 * way; otherwise None.
 *)
let k_and a b = match a, b with
     Some false, _ -> Some false
   | _, Some false -> Some false
   | Some a', Some b' -> Some (a' && b')
   | _, _ -> None
let k_or a b = match a, b with
     Some true, _ -> Some true
   | _, Some true -> Some true
   | Some a', Some b' -> Some (a' && b')
   | _, _ -> None
let k_xor a b = match a, b with
     Some a', Some b' -> Some (a' <> b')
   | _, _ -> None
let k_not a = match a with
     Some a' -> Some (not a')
   | None -> None

let rec constp_eval d e = match e with
     UOP (_pos, CONSTP, e1) ->
        if expr_equiv d e1 then Some false else None
   | UOP (_pos, LOGNOT, e1) ->
        k_not (constp_eval d e1)
   | UOP (_pos, _, _e1) ->
        None
   | BOP (_pos, e1, LOGAND, e2) ->
        k_and (constp_eval d e1) (constp_eval d e2)
   | BOP (_pos, e1, LOGOR, e2) ->
        k_or (constp_eval d e1) (constp_eval d e2)
   | BOP (_pos, e1, LOGXOR, e2) ->
        k_xor (constp_eval d e1) (constp_eval d e2)
   | BOP (_pos, _e1, _, _e2) -> None
   | FITS (_pos, _e1, _ty) -> None
   | MODE (_pos, _name) -> None
   | READVAR (_pos, _name) -> None
   | READMEMBER (_pos, _e1, _name) -> None
   | BOOLCONSTANT (_pos, x) -> Some x
   | NUMCONSTANT (_pos, _x) -> None
   | STRCONSTANT (_pos, _x) -> None
   | HERE (_pos) -> None
   | LIST (_pos, _es) -> None
   | MODIFIER (_pos, _name, _args) -> None
   | PACK (_pos, _name, _args) -> None
   | CAST (_pos, _nty, _oty, e1) -> constp_eval d e1
   | ANNOTATE (_pos, _ty, e1) -> constp_eval d e1

let constp_tests e guard =
   constp_eval e guard = Some false


(**************************************************************)
(* direct checks *)

let check_blockcomment (pos, _nest, s1, s2) =
   match s1, s2 with
        "/*", "*/" -> ()
      | _, _ -> Pos.crashat pos "For now block comments must be /* */" (*XXX*)

let check_token tname (pos, ttype, istarget) =
   if not istarget then
      Pos.crashat pos "langcheck: token is declared internal"
   ;
   try
      let _ = Types.StringMap.find tname stdtokens in
      Pos.crashat pos ("Redeclaration of builtin token " ^ tname)
   with Not_found -> try
      let (prevpos, _) = Types.StringMap.find tname !seentokens in
      Pos.sayat pos ("Redeclaration of token " ^ tname);
      Pos.crashat prevpos ("Previous declaration")
   with Not_found ->
      if ok_token_type ttype then
         addtoken pos tname ttype
      else
         Pos.crashat pos ("Invalid type for token " ^ tname)

let check_kwdecl (KWDECL (_dpos, _string, TOKENEXPR (rpos, rtoken, _rarg))) =
  (*
   * (generating a standard token from a keyword seems dodgy but
   * there's no clear reason to make it illegal)
   *)
   if not (token_exists rtoken) then
      Pos.crashat rpos ("Unknown token " ^ rtoken ^ " declared as keyword")
   ;
   (* XXX we ought to check arg against the type of token... *)

   ()

let check_matchdecl (MATCHDECL (_dpos, matches, TOKENEXPR (rpos, rtoken, _rarg))) =
   if not (token_exists rtoken) then
      Pos.crashat rpos ("Match rule for unknown token " ^ rtoken)
   ;
   let checkone (TOKENPAT (mpos, mtoken, marg)) =
      let mtype = match token_type mtoken with
           Some tt -> tt
         | None -> Pos.crashat mpos ("Unknown token " ^ mtoken ^
			             " matching token " ^ rtoken)
      in
      match mtype, marg with
           PLAINTYPE (_, "_"), None -> ()
         | PLAINTYPE (_, "_"), Some _ ->
              Pos.crashat mpos ("Extraneous value for token " ^ mtoken)
         | _, Some _ -> ()
         | _, None ->
              Pos.crashat mpos ("Missing value for token " ^ mtoken)
   in
   List.iter checkone matches

let check_tagrule (TAGRULE (_pos, _epats, guard, _tagpos, _tagname, e)) =
   (*List.iter check_exprpattern epats;*) (* XXX? *)
   let evals = get_evals e in
   let testconstant (pos, e) =
      if constp_tests e guard then ()
      else Pos.crashat pos ("Expressions used witih eval must be " ^
			    "constants; use constantp")
   in
   List.iter testconstant evals


(**************************************************************)
(* top level *)

let check props =
   Types.StringMap.iter (addtoken Pos.builtin) stdtokens;

   (* linecomments? *)
   List.iter check_blockcomment props.blockcomments;
   (* letters? *)
   (* subletters? *)
   Types.StringMap.iter check_token props.tokens;
   List.iter check_kwdecl props.keywords;
   List.iter check_matchdecl props.matches;
   (* separators? *)
   List.iter check_tagrule props.tagrules;

   props
