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

open Typerep
open Exprrep
open Rep
module ET = Exprtransform
module EU = Exprutil

module EE = Expremit
module G = Gcode

(**************************************************************)
(* extra hook into numerate *)

(*
 * XXX this should go away. It is here because currently numerate
 * can't numerate the types of operandtags (that breaks
 * generate_opermatch) but we also need the numerated type in struct
 * operand. This is all wrong and needs to be fixed up; probably
 * spec.operandtags should carry both types around.
 *)

let numerate'typename spec ty =
   let load name (_pos, width, members) =
      let doadd tbl (_mpos, mname, mval) =
         Types.StringMap.add mname mval tbl
      in
      let symtovalue = List.fold_left doadd Types.StringMap.empty members in
      { Exprtransform.name; width; symtovalue; }
   in
   let enumtypes = Types.StringMap.mapi load spec.enumtypes in
   let nctx = Exprtransform.numeratectx_new enumtypes in
   Exprtransform.numerate'typename nctx ty


(**************************************************************)
(* some support logic *)

let nextvar = ref 0
let getvar prefix =
	let n = !nextvar in
	nextvar := !nextvar + 1;
	prefix ^ string_of_int n

let string_of_const k = match k with
     SMALL k' -> string_of_int k'
   | LARGE k' -> Types.Wide.to_string k'

let token_is_target spec tokname =
   let (_pos, _ty, istarget) = Types.StringMap.find tokname spec.tokens in
   istarget      

(*
 * see call site below for explanation
 *)
let hack_numbers x =
   let hn_e e = match e with
        CONST (pos, ty, n) -> STRCONST (pos, ty, (string_of_const n))
      | _ -> e
   in
   EU.xform hn_e x

let charlist_of_string s =
   let cs = ref [] in
   let add c =
      cs := c :: !cs
   in
   String.iter add s;
   List.rev !cs

(*
 * this is a standard function in many cons-based languages... but not ocaml
 *)
let rec divide_list f xs =
   match xs with
        [] -> ([], [], [])
      | x :: more ->
           if f x then ([], [x], more)
           else let (pre, mid, post) = divide_list f more in
                (x :: pre, mid, post)

(*
 * Assumes variables named "l__ul" and "l__end" exist.
 *)
let dostrtoul nope e =
   let read'ul = G.READVAR (G.ULONG, "l__ul") in
   let write'ul = G.WRITEVAR (G.ULONG, "l__ul") in
   let read'end = G.READVAR (G.charptr, "l__end") in
   let read'errno = G.READVAR (G.INT, "errno") in
   let write'errno = G.WRITEVAR (G.INT, "errno") in

   let a'end = G.addrof (G.POINTER G.charptr) read'end in
   let len'end = G.call G.UINT "strlen" [read'end] in
   let z = G.zero G.INT in
   let stmts = [
      G.ASSIGN (write'errno, G.zero G.INT);
      G.ASSIGN (write'ul, G.call G.ULONG "strtoul" [e; a'end; z]);
      G.IF (G.logor (G.ne read'errno z) (G.ne len'end z), nope, G.skip);
      (* XXX should check bounds if result narrower than unsigned long... *)
   ] in
   (stmts, read'ul)

(**************************************************************)
(* accessors for struct token *)

let type'toktypes = G.ENUMTYPE "toktypes"
let type'targettoktypes = G.ENUMTYPE "targettoktypes"

let _tTOK_IDENT = G.READVAR (type'toktypes, "TOK_IDENT")
let _tTOK_NUMBER = G.READVAR (type'toktypes, "TOK_NUMBER")
let _tTOK_STRING = G.READVAR (type'toktypes, "TOK_STRING")
let tTOK_TARGET = G.READVAR (type'toktypes, "TOK_TARGET")

let type'token = G.POINTER (G.STRUCTTYPE "token")
let token'read'type e = G.READFIELD (type'toktypes, e, "t_type")
let token'read'ttype e = G.READFIELD (type'targettoktypes, e, "t_ttype")
let token'read'value e = G.READFIELD (G.charptr, e, "t_value")


(**************************************************************)
(* accessors for struct expr *)

let type'exprtypes = G.ENUMTYPE "exprtypes"
let _eEXPR_TARGET = G.READVAR (type'exprtypes, "EXPR_TARGET")
let eEXPR_STR = G.READVAR (type'exprtypes, "EXPR_STR")
let eEXPR_NUM = G.READVAR (type'exprtypes, "EXPR_NUM")
let _eEXPR_IDENT = G.READVAR (type'exprtypes, "EXPR_IDENT")
let _eEXPR_OPERATOR = G.READVAR (type'exprtypes, "EXPR_OPERATOR")
let _eEXPR_MODIFIER = G.READVAR (type'exprtypes, "EXPR_MODIFIER")
let _eEXPR_JUXTAPOSE = G.READVAR (type'exprtypes, "EXPR_JUXTAPOSE")

let type'expr = G.POINTER (G.STRUCTTYPE "expr")
let expr'read'type e =
   G.READFIELD (type'exprtypes, e, "x_type")
let expr'read'u e =
   G.READFIELD (G.UNIONTYPE "", e, "x_u")
let expr'read'u_str e =
   G.READFIELD (G.constcharptr, expr'read'u e, "u_str")
let expr'read'u_num e =
   G.READFIELD (G.TYPEDEFNAME "u_machlarge", expr'read'u e, "u_num")
let expr'read'u_target e =
   G.READFIELD (G.STRUCTTYPE "", expr'read'u e, "u_target")
let _expr'read'u_target_ttok e =
   G.READFIELD (type'targettoktypes, expr'read'u_target e, "ttok")
let _expr'read'u_target_val e =
   G.READFIELD (G.constcharptr, expr'read'u_target e, "val")
let expr'write'u_str e =
   G.WRITEFIELD (G.constcharptr, expr'read'u e, "u_str")
let expr'write'u_num e =
   G.WRITEFIELD (G.TYPEDEFNAME "u_machlarge", expr'read'u e, "u_num")


(**************************************************************)
(* expremit *)

let evalstmts = ref []

let emit'eval _pos ty e =
   let bytype str num =
      if ty = Typerep.PLAINTYPE "string" then str else num
   in
   let gty = bytype G.charptr (G.TYPEDEFNAME "u_machlarge") in
   let local = G.LOCAL (gty, "tmp") in
   let read'tmp = G.READVAR (gty, "tmp") in
   let write'tmp = G.WRITEVAR (gty, "tmp") in
   let stmts = [
      local;
      G.ASSERT (G.eq (expr'read'type e) (bytype eEXPR_STR eEXPR_NUM));
      G.ASSIGN (write'tmp, bytype (expr'read'u_str e) (expr'read'u_num e));
      G.ASSIGN (bytype (expr'write'u_str e) (expr'write'u_num e),
                bytype G.null (G.zero gty));
      G.voidcall "expr_destroy" [e];
   ] in
   evalstmts := !evalstmts @ stmts;
   read'tmp

let getevalstmts () =
   let ret = !evalstmts in
   evalstmts := [];
   ret

let eectx = {
   EE.emit'varname = (fun name -> name);
   EE.emit'eval = emit'eval;
}

let emit'expr e = Expremit.emit'expr' eectx e


(**************************************************************)
(* matches *)

(*
 * Digest the match expressions.
 * Produces allmatches, which is a list of onematch:
 *    (matchtokens, matchbinders, pred, result) where
 *    - matchtokens is a list of token names
 *    - matchbinders is a list of variable names to bind, or None
 *    - pred is a predicate expression to run on matchbinders
 *    - result (rpos, rtoken, rval) the token (name and value expr) to produce
 *)

type onematch =
   ONEMATCH of string list * string option list * expr * tokenexpr

let build_match numtype (pos, matchtokens, (rpos, rtoken, rarg)) =

   let unpack (_pos, matchtoken, matchval) =
      (matchtoken, matchval)
   in
   let (matchtokens, matchvals) = Util.unzip (List.map unpack matchtokens) in

   (*
    * Convert matchvals[] into an array of bound variable names and
    * a predicate expression.
    *
    * Stick user_ in front of the user's variables and call ours
    * gen_, to avoid conflicts. This gives us variable names we can
    * emit straight into the output.
    *)
   let process_matchval mv =
       match mv with
            None -> (None, [])
          | Some (BIND (_pos, _ty, name)) ->
               (* variable; stick user_ in front of the name *)
               (Some ("user_" ^ name), [])
          | Some (MATCHSTR (vpos, str)) ->
               let tystring = Typerep.PLAINTYPE "string" in
               let var = getvar "gen_"  in
               let newpred =
                  OP (vpos, tystring, EQ, [
                           USEVAR (vpos, tystring, var);
                           STRCONST (vpos, tystring, str);
                       ])
               in
                  (Some var, [newpred])
          | Some (MATCHINT (vpos, n)) ->
               let var = getvar "gen_"  in
               let newpred =
                  OP (vpos, numtype, EQ, [
                           USEVAR (vpos, numtype, var);
                           CONST (vpos, numtype, SMALL n);
                       ])
               in
                  (Some var, [newpred])
   in

   let results = List.map process_matchval matchvals in
   let (matchvals, preds) = Util.unzip results in
   let preds = List.concat preds in
   let tybool = Typerep.PLAINTYPE "bool" in
   let addpred pred newpred =
      OP (pos, tybool, LOGAND, [pred; newpred])
   in
   let tru = USEVAR (pos, tybool, "true") in
   let pred = List.fold_left addpred tru preds in

   (*
    * Now go through arg and stick user_ in front of the variable
    * names used there.
    *)
   let change var =
           "user_" ^ var
   in
   let rarg = EU.alphachange_opt change rarg in

   (*
    * Run the simple optimizer on the predicate expression to avoid
    * emitting "&& true" on the end.
    *)
   let pred = EU.baseopt pred in

   ONEMATCH (matchtokens, matchvals, pred, (rpos, rtoken, rarg))

(*
 * Note: while we should check for duplicate token sequences, it's
 * perfectly ok to have duplicate token sequences with different value
 * guards, e.g. match FOO(n) | n > 3 => BAR(n-3); along with match
 * FOO(n) | n <= 3 => BAZ(n); ... and checking for overlap is somewhere
 * between tedious and undecidable depending on what we allow in those
 * expressions. So for now at least let's not bother.
 *)

(**************************************************************)
(* enum targettoktypes *)

let generate_targettoktypes mdtokens =
   let mktoken (t, _) =
      let upname = Upcase.upcase t in
      ("TTOK_" ^ upname, None, None)
   in
   let enumentries = 
        [("TTOK_NIL", None, Some "Invalid")]
      @ List.map mktoken (Types.StringMap.bindings mdtokens)
   in
   G.ENUMDECL ("targettoktypes", enumentries)


(**************************************************************)
(* letter handling *)

let generate_letterdecl name =
   let params = [
      (G.INT, "ch");
   ] in
   G.FUNCDECL (G.GLOBAL, G.INT, "is_" ^ name, params)

(*
 * Generate is_letter (or is_subletter), which tests whether a
 * character counts as a letter. This is true if (a) it's a letter,
 * (b) it's "_" or "."; (c) it's supplied by the machine description
 * as an additional letter.
 *)
let generate_letterfunc moreletters name =
   let params = [
      (G.INT, "ch");
   ] in

   let laz = "abcdefghijklmnopqrstuvwxyz" in
   let lAZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" in
   let allstr = laz ^ lAZ ^ "_." ^ String.concat "" moreletters in
   let letters = charlist_of_string allstr in

   let mkcase c =
      (* XXX this should produce character constants *)
      let cs = string_of_int (Char.code c) in
      (G.INTCONSTANT (G.CHAR, cs), G.retval (G.one G.INT))
   in
   let cases = List.map mkcase letters in

   let stmts = [
      G.SWITCH (G.READVAR (G.INT, "ch"), cases, Some G.BREAK);
      G.retval (G.zero G.INT);
   ] in

   G.FUNCTION (G.GLOBAL, G.INT, "is_" ^ name, params, G.BLOCK stmts)


(**************************************************************)
(* substitute funcs *)

(*
 * Write out a substitution function for each match rule.
 *
 * The function returns the change in current token position, that is,
 * the number of entries in the token array that have been nulled and
 * should be skipped over.
 *)
let generate_substfunc mdtokens (i, mrule) =
   let ONEMATCH (_matchtokens, matchbinders, _pred, result) = mrule in
   let (_prodpos, prodtoken, prodval) = result in

   let n = List.length matchbinders in
   let n1 = n - 1 in

   let ty'toksym = G.ENUMTYPE "toktypes" in
   let ty'ttoksym = G.ENUMTYPE "targettoktypes" in
   let ty'tok = G.POINTER (G.STRUCTTYPE "token") in
   let ty'toks = G.POINTER (G.STRUCTTYPE "tokenarray") in
   let ty'val = G.constcharptr in

   let params = [
      (ty'toks, "toks");
      (G.UINT, "i");
   ] in

   let jdecl =
      if n > 1 then
	 [G.LOCAL (G.UINT, "j")]
      else []
   in
   let binders =
      let wmb mb = match mb with
           None -> []
         | Some mbs -> [G.LOCAL (G.charptr, mbs)]
      in
      List.concat (List.map wmb matchbinders)
   in
   let valdecl = match prodval with
        None -> []
      | Some _ -> [G.LOCAL (ty'val, "val")]
   in
   let decls = jdecl @ [
      G.LOCAL (ty'tok, "nt");
      G.LOCAL (ty'tok, "ot");
   ] @ binders @ valdecl @ [G.BLANKLINESTMT]
   in

   (* bind the binders *)
   (* FUTURE: bind only the ones used in the prodval expression *)
   let bindstmts =
      let wbind (j, mb) =
         let js = string_of_int j in
         match mb with
              None -> []
            | Some mbs ->
                 let tg =
                    G.call ty'tok "tokenarray_get" [
                               G.READVAR (ty'toks, "toks");
                               G.add G.UINT (G.READVAR (G.UINT, "i"))
                                            (G.INTCONSTANT (G.UINT, js));
                            ]
                 in [
	            G.ASSIGN (G.WRITEVAR (G.charptr, mbs),
                              G.READFIELD (G.charptr, tg, "t_value"));
                    G.IGNORE (G.CAST (G.VOID, G.charptr, G.READVAR (G.charptr, mbs)));
                 ]
      in
      List.concat (List.map wbind (Util.number matchbinders))
   in

   (*
    * XXX this is going to leak the memory for the value string in
    * some cases...
    *)
   let toksym, ttoksym = 
      if Types.StringMap.mem prodtoken mdtokens then
         ("TOK_TARGET", Some ("TTOK_" ^ Upcase.upcase prodtoken))
      else
         ("TOK_" ^ Upcase.upcase prodtoken, None)
   in

   let valstmt, valexpr =
      match prodval with
           Some pv ->
              (*
               * XXX: our stuff is set up for having integer
               * values distinct from strings but the token logic
               * currently in the assembler doesn't atoi() until
               * downstream of all the token frobbing.  Decide
               * how it should be and update one or the
               * other. For now, just hack things.
               *)
              let pv = hack_numbers pv in
              let pv' = emit'expr pv in
              [G.ASSIGN (G.WRITEVAR (ty'val, "val"), pv')] @ getevalstmts (),
                 G.READVAR (ty'val, "val")
         | None ->
              [], G.null
   in
   let tokstmt1 = [
      G.ASSIGN (G.WRITEVAR (ty'tok, "nt"),
                G.call ty'tok "token_create" [
                                  G.READVAR (ty'toksym, toksym);
                                  valexpr
                              ]
               )
   ] in
   let tokstmt2 = match ttoksym with
        Some ts -> [
           G.ASSIGN (G.WRITEFIELD (ty'ttoksym, G.READVAR (ty'tok, "nt"), "t_ttype"), G.READVAR (ty'ttoksym, ts))
        ]
      | None -> []
   in

   let cleanstmts =
      if n > 1 then [
          G.simplefor G.UINT "j" (G.zero G.UINT) (G.INTCONSTANT (G.UINT, string_of_int n)) [
             G.ASSIGN (G.WRITEVAR (ty'tok, "ot"),
                       G.call ty'tok "tokenarray_get" [
                                       G.READVAR (ty'toks, "toks");
                                       G.add G.UINT (G.READVAR (G.UINT, "i"))
                                                    (G.READVAR (G.UINT, "j"));
                                   ]);
             G.voidcall "token_destroy" [G.READVAR (ty'tok, "ot")];
          ]
      ] else [
          G.ASSIGN (G.WRITEVAR (ty'tok, "ot"),
                    G.call ty'tok "tokenarray_get" [
                                       G.READVAR (ty'toks, "toks");
                                       G.READVAR (G.UINT, "i");
                                  ]);
          G.voidcall "token_destroy" [G.READVAR (ty'tok, "ot")];
      ]
   in

   let n1s = string_of_int n1 in
   let nullstmts =
      if n1 > 1 then [
         G.simplefor G.UINT "j" (G.zero G.UINT) (G.INTCONSTANT (G.UINT, n1s)) [
            G.voidcall "tokenarray_set" [
                                   G.READVAR (ty'toks, "toks");
                                   G.add G.UINT (G.READVAR (G.UINT, "i"))
                                                (G.READVAR (G.UINT, "j"));
                                   G.null;
                      ];
         ]
      ] else if n1 = 1 then [
         G.voidcall "tokenarray_set" [
                                G.READVAR (ty'toks, "toks");
                                (* wut XXX *)
                                G.add G.UINT (G.READVAR (G.UINT, "i"))
                                             (G.zero G.UINT);
                                G.null;
                   ];
      ] else [
         (* nothing *)
      ]
   in

   let insertstmt = [
      G.voidcall "tokenarray_set" [
                            G.READVAR (ty'toks, "toks");
                            G.add G.UINT (G.READVAR (G.UINT, "i"))
                                         (G.INTCONSTANT (G.UINT, n1s));
                            G.READVAR (ty'tok, "nt");
                        ];
   ] in
   let returnstmt = [
       G.retval (G.INTCONSTANT (G.UINT, n1s));
   ] in

   let stmts =
      bindstmts @ [G.BLANKLINESTMT] @
      valstmt @ tokstmt1 @ tokstmt2 @
      cleanstmts @ nullstmts @
      insertstmt @ returnstmt
   in

   G.FUNCTION (G.STATIC, G.UINT, "subst_" ^ string_of_int i,
               params, G.BLOCK (decls @ stmts))


(**************************************************************)
(* match funcs *)

(*
 * Write out a match function for each match rule.
 *)
let generate_matchfunc mdtokens (i, mrule) =
   let ONEMATCH (matchtokens, matchbinders, pred, _result) = mrule in

   let ty'toksym = G.ENUMTYPE "toktypes" in
   let ty'ttoksym = G.ENUMTYPE "targettoktypes" in
   let ty'tok = G.POINTER (G.STRUCTTYPE "token") in
   let ty'toks = G.POINTER (G.STRUCTTYPE "tokenarray") in

   let params = [
      (ty'toks, "toks");
      (G.UINT, "i");
   ] in

   let binders =
      let w_mb omb = match omb with
	   None -> []
	 | Some mb -> [G.LOCAL (G.charptr, mb)]
      in
      List.concat (List.map w_mb matchbinders)
   in

   let decls = [
      G.LOCAL (G.UINT, "num");
      G.LOCAL (ty'tok, "t");
   ] @ binders @ [
      G.LOCAL (G.BOOL, "ok");
      G.BLANKLINESTMT;
   ] in

   (* if the sequence is longer than the number of tokens, it doesn't match *)
   let nmt = List.length matchtokens in
   assert (nmt > 0);

   let stmts1 = [
      G.ASSIGN (G.WRITEVAR (G.UINT, "num"),
                G.call G.UINT "tokenarray_num" [G.READVAR (ty'toks, "toks")]);
      G.IF (G.gt (G.add G.UINT (G.READVAR (G.UINT, "i"))
                               (G.INTCONSTANT (G.UINT, string_of_int nmt)))
                 (G.READVAR (G.UINT, "num")),
            G.retval (G.boolconst false),
            G.skip);
      G.BLANKLINESTMT;
   ] in

   (* check each token *)
   let checkmt (j, (mt, mb)) =
      let mtu = Upcase.upcase mt in
      let js = string_of_int j in
      let cond =
         if Types.StringMap.mem mt mdtokens then
            G.logor (G.ne (G.READFIELD (ty'toksym, G.READVAR (ty'tok, "t"), "t_type"))
                          (G.READVAR (ty'toksym, "TOK_TARGET")))
                    (G.ne (G.READFIELD (ty'ttoksym, G.READVAR (ty'tok, "t"), "tt_type"))
                          (G.READVAR (ty'ttoksym, "TTOK_" ^ mtu)))
         else
            G.ne (G.READFIELD (ty'toksym, G.READVAR (ty'tok, "t"), "t_type"))
                 (G.READVAR (ty'toksym, "TOK_" ^ mtu))
      in
      let mbx = 
	 match mb with
	      None -> []
	    | Some mbs -> [
	         (* XXX skip if the variable isn't used in the predicate *)
                 G.ASSIGN (G.WRITEVAR (G.charptr, mbs),
                          (G.READFIELD (G.charptr, G.READVAR (ty'tok, "t"), "t_value")));
                 G.IGNORE (G.CAST (G.VOID, G.charptr, G.READVAR (G.charptr, mbs)));
              ]
      in [
         G.ASSIGN (G.WRITEVAR (ty'tok, "t"),
                   G.call ty'tok "tokenarray_get" [
                                    G.READVAR (ty'toks, "toks");
                                    G.add G.UINT (G.READVAR (G.UINT, "i"))
                                                 (G.INTCONSTANT (G.UINT, js));
                                ]);
         G.ASSERT (G.ne (G.READVAR (ty'tok, "t")) G.null);
         G.IF (cond, G.retval (G.boolconst false), G.skip);
      ] @ mbx
   in
   let mtstmts =
      List.concat (List.map checkmt (Util.number (Util.zip matchtokens matchbinders)))
   in

   (* all the tokens are the right types; now apply the predicate *)

   let pred' = emit'expr pred in
   let stmts2 = getevalstmts () @ [
      G.ASSIGN (G.WRITEVAR (G.BOOL, "ok"), pred');
      G.retval (G.READVAR (G.BOOL, "ok"))
   ]
   in
   let stmts = stmts1 @ mtstmts @ [G.BLANKLINESTMT] @ stmts2 in

   G.FUNCTION (G.STATIC, G.BOOL, "match_" ^ string_of_int i,
               params, G.BLOCK (decls @ stmts))


(**************************************************************)
(* target_scantokens *)

let generate_scantokens allmatches =
   let ty'toks = G.POINTER (G.STRUCTTYPE "tokenarray") in

   let params = [
      (G.INT, "line");
      (ty'toks, "toks");
   ] in
   let decls = [
      G.LOCAL (G.UINT, "i");
      G.LOCAL (G.UINT, "num");
   ] @ [G.BLANKLINESTMT]
   in

   let matchcalls =
      (* try each match *)
      let wmatch (i, _) =
	  let is = string_of_int i in
          let args = [
             G.READVAR (ty'toks, "toks");
             G.READVAR (G.UINT, "i");
          ] in
          G.IF (G.call G.BOOL ("match_" ^ is) args,
                G.ASSIGN (G.WRITEVAR (G.UINT, "i"),
                          G.add G.UINT (G.READVAR (G.UINT, "i"))
                                       (G.call G.UINT ("subst_" ^ is) args)),
                G.skip)
      in
      List.map wmatch (Util.number allmatches)
   in

   let stmts = [
      G.IGNORE (G.CAST (G.VOID, G.INT, G.READVAR (G.INT, "line")));
      G.ASSIGN (G.WRITEVAR (G.UINT, "num"),
                G.call G.UINT "tokenarray_num" [G.READVAR (ty'toks, "toks")]);
      G.simplefor G.UINT "i" (G.zero G.UINT) (G.READVAR (G.UINT, "num")) matchcalls;
      G.BLANKLINESTMT;
   ] in

   G.FUNCTION (G.GLOBAL, G.VOID, "target_scantokens",
               params, G.BLOCK (decls @ stmts))


(**************************************************************)
(* operand typing things *)

(*
 * Get the members of a compound type
 *)
let spec_compoundmembers_of_typename spec tyname =
   try
      Some (Types.StringMap.find tyname spec.compoundtypes)
   with Not_found -> None

(*
 * Get the gcode type of a rep type.
 *
 * This version produces an anonymous struct when a compound type
 * comes up, which might or might not be what's wanted.
 *
 * It also produces the numerated version, because that's what we
 * need at the call site.
 *)
let gtype_of_typename spec ty =
   let wrong msg =
      Util.crash ("mklang: gtype_of_typename: " ^ msg)
   in
   match numerate'typename spec ty with
        PLAINTYPE "_" -> G.VOID
      | PLAINTYPE "bool" -> G.BOOL
      | PLAINTYPE "string" -> G.constcharptr
      | PLAINTYPE tyname -> begin
           match spec_compoundmembers_of_typename spec tyname with
                Some _ ->
                   G.STRUCTTYPE ("compound_" ^ tyname)
               | None ->
                   wrong ("Unknown type " ^ tyname)
        end
      | WIDTHTYPE ("int", width) ->
           (* XXX notyet *)
           (*G.INTBITS width*)
           G.TYPEDEFNAME (Typerep.inttype width)
      | WIDTHTYPE ("uint", width) ->
           (* XXX notyet *)
           (*G.UINTBITS width*)
           G.TYPEDEFNAME (Typerep.uinttype width)
      | WIDTHTYPE (tyname, width) ->
           wrong ("Unknown type " ^ tyname ^ "(" ^ string_of_int width ^ ")")
      | EXPRTYPE _ -> type'expr
      | LISTTYPE _ -> wrong "leftover list type"
      | TMPTYPE _ -> wrong "leftover scratch type"


(*
 * Generate an initializer (as a list of assignments) for a gcode value
 * of a rep type, corresponding to gtype_of_typename. The value is written
 * as a field FIELD from the expression E.
 *)
let rec ginit_of_typename spec e field ty =
   let wrong msg =
      Util.crash ("mklang: ginit_of_typename: " ^ msg)
   in
   let ty' = gtype_of_typename spec ty in
   match numerate'typename spec ty with
        PLAINTYPE "_" -> []
      | PLAINTYPE "bool" ->
           [G.ASSIGN (G.WRITEFIELD (G.BOOL, e, field),
                     G.boolconst false)]
      | PLAINTYPE "string" ->
           [G.ASSIGN (G.WRITEFIELD (G.constcharptr, e, field),
                     G.null)]
      | PLAINTYPE tyname -> begin
	   match spec_compoundmembers_of_typename spec tyname with
                Some (_pos, submembers) ->
                   let mksub (i, (_subpos, subty)) =
                      let subfield = ("m" ^ string_of_int i) in
                      let sube = G.READFIELD (G.STRUCTTYPE "", e, field) in
                      ginit_of_typename spec sube subfield subty
                   in
                   List.concat (List.map mksub (Util.number submembers))
              | None ->
                   wrong ("Unknown type " ^ tyname)
        end
      | WIDTHTYPE ("int", _width) ->
           [G.ASSIGN (G.WRITEFIELD (ty', e, field), G.zero ty')]
      | WIDTHTYPE ("uint", _width) ->
           [G.ASSIGN (G.WRITEFIELD (ty', e, field), G.zero ty')]
      | WIDTHTYPE (tyname, width) ->
           wrong ("Unknown type " ^ tyname ^ "(" ^ string_of_int width ^ ")")
      | EXPRTYPE _ ->
           [G.ASSIGN (G.WRITEFIELD (type'expr, e, field), G.null)]
      | LISTTYPE _ -> wrong "leftover list type"
      | TMPTYPE _ -> wrong "leftover scratch type"

(*
 * Same, but a cleanup call.
 *)
let rec gcleanup_of_typename spec e field ty =
   let wrong msg =
      Util.crash ("mklang: gcleanup_of_typename: " ^ msg)
   in
   match numerate'typename spec ty with
        PLAINTYPE "_" -> []
      | PLAINTYPE "bool" -> []
      | PLAINTYPE "string" ->
           (* for now at least the string is const and owned elsewhere *)
           []
      | PLAINTYPE tyname -> begin
           match spec_compoundmembers_of_typename spec tyname with
                Some (_pos, submembers) ->
                   let mksub (i, (_subpos, subty)) =
                      let subfield = ("m" ^ string_of_int i) in
                      let sube = G.READFIELD (G.STRUCTTYPE "", e, field) in
                      gcleanup_of_typename spec sube subfield subty
                   in
                   List.concat (List.map mksub (Util.number submembers))
               | None ->
                   wrong ("Unknown type " ^ tyname)
        end
      | WIDTHTYPE ("int", _width) -> []
      | WIDTHTYPE ("uint", _width) -> []
      | WIDTHTYPE (tyname, width) ->
           wrong ("Unknown type " ^ tyname ^ "(" ^ string_of_int width ^ ")")
      | EXPRTYPE _ ->
           [G.voidcall "expr_destroy" [
              G.READFIELD (type'expr, e, field);
           ]]
      | LISTTYPE _ -> wrong "leftover list type"
      | TMPTYPE _ -> wrong "leftover scratch type"

(*
 * Same, but assign FROM to the field.
 *)
let rec gassign_of_typename spec e field ty from =
   let gty = gtype_of_typename spec ty in
   match ty, from with
        PLAINTYPE tyname, PACK (_fpos, _fty, _compoundname, args) -> begin
           match spec_compoundmembers_of_typename spec tyname with
                None ->
                   Util.crash ("mklang: gassign_of_typename: " ^
			       "Unknown type " ^ tyname)
              | Some (_pos, submembers) ->
                   let mksub (i, (_subpos, subty)) =
                      let subfield = ("m" ^ string_of_int i) in
                      let sube = G.READFIELD (G.STRUCTTYPE "", e, field) in
                      let from' = List.nth args i in
                      gassign_of_typename spec sube subfield subty from'
                   in
                   List.concat (List.map mksub (Util.number submembers))
        end
      | _ ->
           let from' = emit'expr from in
           getevalstmts () @ [G.ASSIGN (G.WRITEFIELD (gty, e, field), from')]


(**************************************************************)
(* tagrules *)

(*
 * Generate an operandtag matcher for a single tagrule for TAGNAME, whose
 * type is TAGTY, where the rule contents are EXPRPATS and the result
 * expression is TAGEXPR.
 *
 * The matcher is its own function because it's useful to be able to return
 * early from it. Plus it needs its own scope.
 *)
let generate_tagrule spec tagname tagty guard rulenum rulepos exprpats tagexpr =
   (*
    * exprpats is a list of pattern elements that we want to match
    * against the input token sequence. Each is one of the following:
    *    TOKEN - match a specific token
    *    EXPR - match a sequence of specific tokens and pass them to the
    *           expression parser
    *    EXPRANY - match a sequence of any tokens and pass them to the
    *           expression parser.
    *
    * Each token or expression can bind a value and the value of the
    * resulting operand is constructed with tagexpr.
    *
    * We know that tagexpr must produce a value of the type expected
    * by this operandtag because the typechecker checks it against that
    * type.
    *
    * For now we allow at most one EXPRANY in the pattern list; this
    * lets us identify unambiguously what's supposed to get sent to the
    * expression parser.
    *)

   let type'operand = G.POINTER (G.STRUCTTYPE "operand") in
   let type'tokarray = G.POINTER (G.STRUCTTYPE "tokenarray") in

   let nope = G.retval (G.boolconst false) in

   let params = [
      (G.INT, "lineno");
      (type'operand, "oper");
      (type'tokarray, "toks");
   ] in
   let read'lineno = G.READVAR (G.INT, "lineno") in
   let read'oper = G.READVAR (type'operand, "oper") in
   let read'toks = G.READVAR (type'tokarray, "toks") in

   let is = "is_" ^ tagname in
   let write'is = G.WRITEFIELD (G.BOOL, read'oper, is) in

   (*
    * We need a scratch var for every value bound by one of the patterns.
    *)
(* XXX
   let scratchname name = "b" ^ "_" ^ name in
*)
   let scratchname name = name in
   let _read'scratch ty name =
      let ty' = gtype_of_typename spec ty in
      G.READVAR (ty', scratchname name)
   in
   let write'scratch ty name =
      let ty' = gtype_of_typename spec ty in
      G.WRITEVAR (ty', scratchname name)
   in

   let makescratch'p pat =
      match pat with
           BIND (_pos, _ty, "_") -> []
         | BIND (_pos, ty, name) ->
              let idname = scratchname name in
              let ty' = gtype_of_typename spec ty in
              [G.LOCAL (ty', idname)]
         | MATCHSTR _ -> []
         | MATCHINT _ -> []
   in
   let makescratch'tp (_pos, _tokname, optp) =
      match optp with
           None -> []
         | Some p -> makescratch'p p
   in
   let makescratch'ep ep =
      match ep with
           TOKEN tp -> makescratch'tp tp
         | EXPR (_pos, tps, optp) -> begin
              let tps' = List.concat (List.map makescratch'tp tps) in
              match optp with
                   None -> tps'
                 | Some p -> makescratch'p p @ tps'
           end
         | EXPRANY (_pos, optp) -> begin
              match optp with
                   None -> []
                 | Some p -> makescratch'p p
           end
   in
   let scratchvars = List.concat (List.map makescratch'ep exprpats) in

   (*
    * XXX add l__ to avoid conflicts with the user-defined scratch vars;
    * those ought to be prefixed instead but currently expremit can't do
    * that.
    *)
   let locals =
      G.LOCAL (G.UINT, "l__num") ::
      G.LOCAL (type'token, "l__t") ::
      G.LOCAL (type'expr, "l__x") ::
      G.LOCAL (G.ULONG, "l__ul") ::
      G.LOCAL (G.charptr, "l__end") ::
      scratchvars
   in
   let read'num = G.READVAR (G.UINT, "l__num") in
   let read't = G.READVAR (type'token, "l__t") in
   let write'num = G.WRITEVAR (G.UINT, "l__num") in
   let write't = G.WRITEVAR (type'token, "l__t") in
   let read'x = G.READVAR (type'expr, "l__x") in
   let write'x = G.WRITEVAR (type'expr, "l__x") in
   let read'ul = G.READVAR (G.ULONG, "l__ul") in
   let read'end = G.READVAR (G.charptr, "l__end") in

   let ign'lineno = G.IGNORE read'lineno in
   let ign't = G.IGNORE read't in
   let ign'x = G.IGNORE read'x in
   let ign'ul = G.IGNORE read'ul in
   let ign'end = G.IGNORE read'end in

   (*
    * Divide the list of pattern entries into the ones before an EXPRANY,
    * the first EXPRANY, and everything after it. If there's another
    * EXPRANY, complain.
    *)
   let is_exprany ep =
      match ep with
           EXPRANY _ -> true
         | _ -> false
   in
   let (exprpats_begin, exprpats_any, exprpats_end) =
      divide_list is_exprany exprpats
   in
   if List.exists is_exprany exprpats_end then begin
      Pos.sayat rulepos ("genlanguage: Cannot currently handle tagrules " ^
                         "with multiple [*] patterns");
      Util.fail ()
   end;

   (* 
    * The first thing we do is compare the number of tokens we've gotten
    * against the minimum number we must have to match. This will ensure
    * the somewhat naive code below doesn't run off the end of the token
    * array.
    *)
   
   let num = G.call G.UINT "tokenarray_num" [read'toks] in
   let setnum = G.ASSIGN (write'num, num) in

   let getmintokens epats =
      let count z ep =
         match ep with
              TOKEN _ -> z + 1
            | EXPR (_pos, tps, _) -> z + List.length tps
              (* must be at least one token in an expression *)
            | EXPRANY _ -> z + 1
      in
      List.fold_left count 0 epats
   in
   let mintokens = getmintokens exprpats in
   let numtokens_begin = getmintokens exprpats_begin in
   let numtokens_end = getmintokens exprpats_end in
   assert (numtokens_begin + numtokens_end <= mintokens);
   let countcheck =
      let min = G.INTCONSTANT (G.UINT, string_of_int mintokens ^ "U") in
      let test = G.lt read'num min in
      G.IF (test, nope, G.skip)
   in

   (*
    * Now test all the tokens
    *)

   let test'p pat =
      match pat with
           BIND (_pos, _ty, "_") -> []
         | BIND (_pos, ty, name) ->
              let strvalue = token'read'value read't in
              let (valstmts, value) = match ty with
                   PLAINTYPE "string" ->
                      (* XXX would be nice not to make this copy *)
                      ([], G.call G.charptr "dostrdup" [strvalue])
                 | _ ->
                      (* XXX this should not be using atol *)
                      dostrtoul nope strvalue
              in
              valstmts @ [G.ASSIGN (write'scratch ty name, value)]
         | MATCHSTR (_pos, s) ->
              let s' = G.STRINGCONSTANT s in
              let test = G.streq (token'read'value read't) s' in
              [G.IF (G.lognot test, nope, G.skip)]
         | MATCHINT (_pos, n) ->
              let n' = G.INTCONSTANT (G.UINT, string_of_int n) in
              (* XXX this should not be using atol *)
              let (vstmts, v') = dostrtoul nope (token'read'value read't) in
              let test = G.eq n' v' in
              vstmts @ [G.IF (G.lognot test, nope, G.skip)]
   in
   let test'optp optpat =
      match optpat with
           None -> []
         | Some p -> test'p p
   in
   let test'tp make'i i (_pos, tokname, optbinder) =
      let i' = make'i !i in
      let get = G.call type'token "tokenarray_get" [read'toks; i'] in
      i := !i + 1;

      let testtype =
         if token_is_target spec tokname then begin
            let tokname' = G.READVAR (type'targettoktypes, "TTOK_" ^ tokname) in
            let t1 = G.eq (token'read'type read't) tTOK_TARGET in
            let t2 = G.eq (token'read'ttype read't) tokname' in
            G.logand t1 t2
         end else begin
            let tokname' = G.READVAR (type'toktypes, "TOK_" ^ tokname) in
            G.eq (token'read'type read't) tokname'
         end
      in
      [
         G.ASSIGN (write't, get);
         G.IF (G.lognot testtype, nope, G.skip);
      ] @ test'optp optbinder
   in
   let test'ep make'i i imax ep =
      let doparse i1 i2 =
         let parse = G.call type'expr "parserange" [
            read'lineno;
            read'toks;
            i1;
            i2;
            G.boolconst true;
         ] in
         G.ASSIGN (write'x, parse)
      in
      let checkparse =
         G.IF (G.eq read'x G.null, nope, G.skip)
      in
      let dofoldconst =
         let foldconst = G.call type'expr "fold_constant_arithmetic" [
            read'x;
            G.boolconst true;
         ] in
         G.ASSIGN (write'x, foldconst)
      in
      let doexpr i1 i2 optbinder =
         match optbinder with
              None
            | Some (BIND (_, _, "_")) -> [
                 doparse i1 i2;
                 checkparse;
                 G.voidcall "expr_destroy" [read'x];
              ]
            | Some (BIND (_pos, ty, name)) -> [
                 doparse i1 i2;
                 checkparse;
                 dofoldconst;
                 G.ASSIGN (write'scratch ty name, read'x);
              ]
            | Some (MATCHSTR (pos, _)) ->
                 Pos.crashat pos ("mklang: generate_tagrule: " ^
                                  "Invalid string match on expression")
            | Some (MATCHINT (pos, _)) ->
                 Pos.crashat pos ("mklang: generate_tagrule: " ^
                                  "Invalid integer match on expression")
      in

      match ep with
           TOKEN tp -> test'tp make'i i tp
         | EXPR (_pos, tps, optbinder) ->
              let i1 = !i in
              let tps' = List.concat (List.map (test'tp make'i i) tps) in
              let i2 = !i in
              tps' @ doexpr (make'i i1) (make'i i2) optbinder
         | EXPRANY (_pos, optbinder) ->
              doexpr (make'i !i) imax optbinder
   in
   let test'eps make_i imax eps =
      let i = ref 0 in
      List.concat (List.map (test'ep make_i i imax) eps)
   in

   let make_i_begin i =
      G.INTCONSTANT (G.UINT, string_of_int i ^ "U")
   in
   let imax_begin =
      G.INTCONSTANT (G.UINT, string_of_int numtokens_begin ^ "U")
   in
   let make_i_any i =
      make_i_begin (i + numtokens_begin)
   in
   let imax_any =
      let nte = G.INTCONSTANT (G.UINT, string_of_int numtokens_end ^ "U") in
      G.sub G.UINT read'num nte
   in
   let make_i_end i =
      G.add G.UINT imax_any (G.INTCONSTANT (G.UINT, string_of_int i ^ "U"))
   in

   let tests_begin = test'eps make_i_begin imax_begin exprpats_begin in
   let tests_any =   test'eps make_i_any   imax_any   exprpats_any in
   let tests_end =   test'eps make_i_end   num        exprpats_end in
   let tests = tests_begin @ tests_any @ tests_end in

   (*
    * If there isn't a [*], there shouldn't be anything after it either,
    * and in this case we need to make sure that there aren't more tokens
    * at the end that we haven't looked at.
    *)
   let checksize =
      match exprpats_any with
           [] ->
              assert (exprpats_end = []);
              let i = make_i_begin numtokens_begin in
              [
                 G.IF (G.ne read'num i, nope, G.skip);
              ]
         | _ -> []
   in

   let guard' = emit'expr guard in
   let checkguard =
      getevalstmts () @
      [G.IF (G.lognot guard', nope, G.skip)]
   in

   let (_pos, _tagname, e) = tagexpr in
(*
   let e' = emit'expr e in
*)
   let setis = G.ASSIGN (write'is, G.boolconst true) in
(*
   let presetval = getevalstmts () in
*)
   let setval =
(*
      let tagty' = gtype_of_typename spec tagty in
      G.ASSIGN (G.WRITEFIELD (tagty', read'oper, "val_" ^ tagname), e')
*)
      gassign_of_typename spec read'oper ("val_" ^ tagname) tagty e
   in

   let stmts =
      G.BLANKLINESTMT ::
      ign'lineno ::
      ign't ::
      ign'x ::
      ign'ul ::
      ign'end ::
      setnum ::
      countcheck ::
      tests @
      checksize @
      checkguard @
      [setis] @
(*
      presetval @
*)
      setval @ [
      G.retval (G.boolconst true);
   ] in

   let fname = "tagrulematch_" ^ string_of_int rulenum in
   G.FUNCTION (G.STATIC, G.BOOL, fname, params, G.BLOCK (locals @ stmts))

(* wrapper to set the arguments into place XXX should not exist *)
let generate_tagrule' spec (rulenum, (rulepos, exprpats, guard, tagexpr)) =
   let (_epos, tagname, _real_tagexpr) = tagexpr in
   let (_tagpos, tagty) = Types.StringMap.find tagname spec.operandtags in

   generate_tagrule spec tagname tagty guard rulenum rulepos exprpats tagexpr

(*
 * Get all the rules that produce TAGNAME.
 *)
let get_output_tagrules spec tagname =
   let filt (_n, (_pos, _epats, _guard, resulttag)) =
      let (_resultpos, resulttagname, _) = resulttag in
      tagname = resulttagname
   in
   List.filter filt (Util.number spec.tagrules)

(*
 * Generate the operandtag matcher for TAGNAME, whose type is TAGTY.
 *)
let generate_opermatch spec (tagname, (tagpos, _tagty)) =
   let type'operand = G.POINTER (G.STRUCTTYPE "operand") in
   let type'tokarray = G.POINTER (G.STRUCTTYPE "tokenarray") in
   (*let type'ttt = G.ENUMTYPE "targettoktypes" in*)

   let params = [
      (G.INT, "lineno");
      (type'operand, "oper");
      (type'tokarray, "toks");
   ] in
   let read'lineno = G.READVAR (G.INT, "lineno") in
   let read'oper = G.READVAR (type'operand, "oper") in
   let read'toks = G.READVAR (type'tokarray, "toks") in

   let rules = get_output_tagrules spec tagname in

   let igns = if List.length rules = 0 then begin
      (* XXX this warning should happen earlier... *)
      Pos.sayat tagpos ("Warning: no rules for operand tag " ^ tagname);
      [G.IGNORE read'lineno; G.IGNORE read'oper; G.IGNORE read'toks]
   end
   else []
   in

   let callrule (num, (_pos, _epats, _guard, _tagexpr)) =
      let call = G.call G.BOOL ("tagrulematch_" ^ string_of_int num) [
         read'lineno;
         read'oper;
         read'toks;
      ] in
      G.IF (call, G.retvoid, G.skip)
   in
   let callrules = List.map callrule rules in
(*
   (* for now this is identical to what was in opmatch *)

   let onetokmatch t =
      let num =
         G.call G.UINT "tokenarray_num" [read'toks]
      in
      let get =
         G.call type'token "tokenarray_get" [read'toks; G.zero G.UINT]
      in
      let testlen = G.eq num (G.one G.UINT) in
      let testval = G.eq (token'read'type get) t in
      G.logand testlen testval
   in
   let basematch s =
      G.eq read'x_type s
   in
   let targmatch s =
      G.logand (G.eq read'x_type eEXPR_TARGET) (G.eq read'x_u_target_ttok s)
   in
   let nomatch () =
      Util.crash ("Don't know how to match operand tag " ^ tagname)
   in
   let matchexpr = match tagty with
        PLAINTYPE "string" -> onetokmatch tTOK_STRING
      | PLAINTYPE tyname -> begin
           let optmembers = spec_compoundmembers_of_typename spec tyname in
           match optmembers with
                None ->
                   (* XXX for now all of these are register classes but
                      this needs to be stronger *)
                   let upname = Upcase.upcase tyname in
                   let read =
                      G.READVAR (type'ttt, "TTOK_REGCLASS_" ^ upname)
                   in
                   targmatch read
              | Some _members ->
                   (* it's a compound type *)
		   (* XXX this should come from a syntactic-form description *)
		   match tyname with
			"mem" ->
			   (* XXX this should match the specific syntax *)
			   (* (but for now it's checked downstream) *)
			   G.boolconst true
		      | _ -> nomatch ()
        end
      | WIDTHTYPE ("int", _w) -> basematch eEXPR_NUM
      | WIDTHTYPE ("uint", _w) -> basematch eEXPR_NUM
      | WIDTHTYPE (tyname, _w) ->
           Util.crash ("opmatch: domatch: invalid argtype " ^ tyname)
      | EXPRTYPE _ -> begin
	   (* XXX this should come from a syntactic-form description *)
	   match tagname with
		"symbol" -> onetokmatch tTOK_IDENT
	      | "expr"
	      | "s16expr"
	      | "u16expr" -> G.boolconst true
	      | _ -> nomatch ()
        end
      | LISTTYPE _ ->
           Util.crash "mklang: leftover list expression"
      | TMPTYPE _ ->
           Util.crash "mklang: leftover scratch type"
   in
*)
   let stmts = igns @ callrules in

   let funcname = "opermatch_" ^ tagname in
   [
      G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK stmts);
      G.BLANKLINEDECL;
   ]

(**************************************************************)
(* operands *)

let generate_compoundstruct spec (name, (_pos, submembers)) =
   let mksub (i, (_subpos, subty)) =
      (gtype_of_typename spec subty, "m" ^ string_of_int i)
   in
   let submembers' =
      List.map mksub (Util.number submembers)
   in
   G.STRUCTDECL ("compound_" ^ name, submembers')

let generate_compoundstructs spec =
   let b = (Types.StringMap.bindings spec.compoundtypes) in
   List.map (generate_compoundstruct spec) b

(*
 * Generate struct operand.
 *)
let generate_operstruct spec =
   let genmem (name, (_pos, ty)) =
      let withoutval = [ (G.BOOL, "is_" ^ name); ] in
      let withval ty' = withoutval @ [ (ty', "val_" ^ name) ] in
      match gtype_of_typename spec ty with
           G.VOID -> withoutval
         | ty' -> withval ty'
   in
   let opermembers =
      List.concat (List.map genmem (Types.StringMap.bindings spec.operandtags))
   in
   G.STRUCTDECL ("operand", opermembers)

(*
 * Generate decls for the struct operand methods.
 *)
let generate_opermethoddecls _spec =
   let type'operand = G.POINTER (G.STRUCTTYPE "operand") in
   let type'tokarray = G.POINTER (G.STRUCTTYPE "tokenarray") in

   let fname_init = "operand_init" in
   let params_init = [
      (type'operand, "oper");
   ] in
   let func_init =
      G.FUNCDECL (G.GLOBAL, G.VOID, fname_init, params_init)
   in

   let fname_cleanup = "operand_cleanup" in
   let params_cleanup = params_init in
   let func_cleanup =
      G.FUNCDECL (G.GLOBAL, G.VOID, fname_cleanup, params_cleanup)
   in

   let fname_match = "operand_match" in
   let params_match = [
      (G.INT, "lineno");
      (type'operand, "oper");
      (type'tokarray, "toks");
   ] in
   let func_match =      
      G.FUNCDECL (G.GLOBAL, G.VOID, fname_match, params_match)
   in

   [ func_init; func_cleanup; func_match; ]

(*
 * Generate the struct operand methods.
 *)
let generate_opermethods spec =
   let type'operand = G.POINTER (G.STRUCTTYPE "operand") in
   let type'tokarray = G.POINTER (G.STRUCTTYPE "tokenarray") in

   let fname_init = "operand_init" in
   let params_init = [
      (type'operand, "oper");
   ] in
   let read'oper = G.READVAR (type'operand, "oper") in
   let onestmt_init (name, (_pos, ty)) =
     let write'is = G.WRITEFIELD (G.BOOL, read'oper, "is_" ^ name) in
(*
     let write'exprval = G.WRITEFIELD (G.BOOL, read'oper, "exprval_" ^ name) in
*)
     [
        G.ASSIGN (write'is, G.boolconst false);
(*
        G.ASSIGN (write'exprval, G.null);
*)
     ] @
     ginit_of_typename spec read'oper ("val_" ^ name) ty
   in
   let stmts_init =
      let bindings = Types.StringMap.bindings spec.operandtags in
      List.concat (List.map onestmt_init bindings)
   in
   let func_init =
      G.FUNCTION (G.GLOBAL, G.VOID, fname_init, params_init,
                  G.BLOCK stmts_init)
   in

   let fname_cleanup = "operand_cleanup" in
   let params_cleanup = params_init in
   let onestmt_cleanup (name, (_pos, ty)) =
      gcleanup_of_typename spec read'oper ("val_" ^ name) ty
   in
   let stmts_cleanup =
      let bindings = Types.StringMap.bindings spec.operandtags in
      (* XXX temporary *) G.IGNORE (read'oper) ::
      List.concat (List.map onestmt_cleanup bindings)
   in
   let func_cleanup =
      G.FUNCTION (G.GLOBAL, G.VOID, fname_cleanup, params_cleanup,
                  G.BLOCK stmts_cleanup)
   in

   let fname_match = "operand_match" in
   let params_match = [
      (G.INT, "lineno");
      (type'operand, "oper");
      (type'tokarray, "toks");
   ] in
   let read'lineno = G.READVAR (G.INT, "lineno") in
   let read'toks = G.READVAR (type'tokarray, "toks") in
   let onestmt_match (tagname, (_pos, _ty)) =
      G.voidcall ("opermatch_" ^ tagname) [
         read'lineno;
         read'oper;
         read'toks;
      ]
   in
   let stmts_match =
      let bindings = Types.StringMap.bindings spec.operandtags in
      List.map onestmt_match bindings
   in
   let func_match =      
      G.FUNCTION (G.GLOBAL, G.VOID, fname_match, params_match,
                  G.BLOCK stmts_match)
   in

   [ func_init; func_cleanup; func_match; ]


(**************************************************************)
(* targettoken.h *)

let generate_header langinfo =
   let checktarget _ (_, _, istarget) = istarget in
   let mdtokens = Types.StringMap.filter checktarget langinfo.tokens in

   let targettoktypes = generate_targettoktypes mdtokens in
   let isletter = generate_letterdecl "letter" in
   let issubletter = generate_letterdecl "subletter" in

   let stmts = [
      G.BLANKLINEDECL;
      G.BLANKLINEDECL;
      targettoktypes;
      G.BLANKLINEDECL;
      isletter;
      issubletter;
      G.BLANKLINEDECL;
      G.BLANKLINEDECL;
   ] in
   G.FILE (Some "TARGETTOKEN_H", [], stmts)


(**************************************************************)
(* targettoken.c *)

let generate_source langinfo =
   let allmatches = List.map (build_match langinfo.numtype) langinfo.matches in

   let checktarget _ (_, _, istarget) = istarget in
   let mdtokens = Types.StringMap.filter checktarget langinfo.tokens in

   let fileheader = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "string.h";
      G.SYSINCLUDE "assert.h";
      G.LOCALINCLUDE "common.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "utils.h";
      G.LOCALINCLUDE "token.h";
      G.BLANKLINEINCLUDE;
   ] in

   let letterfuncs = [
      generate_letterfunc langinfo.letters "letter";
      generate_letterfunc (langinfo.letters @ langinfo.subletters) "subletter";
   ] in

   let matchfuncs =
      List.map (generate_matchfunc mdtokens) (Util.number allmatches)
   in
   let substfuncs =
      List.map (generate_substfunc mdtokens) (Util.number allmatches)
   in

   let target_scantokens =
      generate_scantokens allmatches
   in

   let alldecls =
      letterfuncs @ matchfuncs @ substfuncs @ [target_scantokens]
   in
   G.FILE (None, fileheader, alldecls)


(**************************************************************)
(* targetoper.h *)

let generate_operheader spec =
   let prelimdecls = [
      G.STRUCTDECL' "tokenarray";
   ] in

   let compoundstructs = generate_compoundstructs spec in

   let operstruct = generate_operstruct spec in

   let stmts = [
      G.BLANKLINEDECL;
      G.BLANKLINEDECL;
   ] @ prelimdecls @ [
      G.BLANKLINEDECL;
   ] @ compoundstructs @ [
      G.BLANKLINEDECL;
      operstruct;
   ] @ generate_opermethoddecls spec @ [
(*
      G.BLANKLINEDECL;
   ] @ tagruledecls @ [
*)
      G.BLANKLINEDECL;
      G.BLANKLINEDECL;
   ] in
   G.FILE (Some "TARGETOPER_H", [], stmts)


(**************************************************************)
(* targetoper.c *)

let generate_opersource langinfo =

   let fileheader = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "stdlib.h";
      G.SYSINCLUDE "string.h";
      G.SYSINCLUDE "errno.h";
      G.SYSINCLUDE "assert.h";
      G.LOCALINCLUDE "common.h";
      G.BLANKLINEINCLUDE;
      (*G.LOCALINCLUDE "array.h";*)
      G.LOCALINCLUDE "expr.h";
      G.LOCALINCLUDE "eparse.h";
      G.LOCALINCLUDE "token.h";
      G.LOCALINCLUDE "targetoper.h";
      G.BLANKLINEINCLUDE;
   ] in

   let opertags = Types.StringMap.bindings langinfo.operandtags in
   let funcs0 = List.map (generate_tagrule' langinfo) (Util.number langinfo.tagrules) in
   let funcs1 = List.concat (List.map (generate_opermatch langinfo) opertags) in
   let funcs2 = generate_opermethods langinfo in

   G.FILE (None, fileheader, funcs0 @ funcs1 @ funcs2)
