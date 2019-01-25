%{
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

open Pos
module TT = Typetree
module T = Exprtree
module H = Hazardtree
open H (* blah *)

let pos () = Pos.fromparser ()

(* temporary type used for parsing the decls *)
type decl =
     INSNPRED of string * T.expr
   | HAZARD of string * string * T.expr * H.assignment list * T.expr * H.cond
   | TRANSFER of H.assignment list * T.expr * H.cond * H.transfertype

let assemble decls =
   let preds = ref Types.StringMap.empty in
   let predorder = ref [] in
   let hazards = ref [] in
   let transfers = ref [] in

   let add_decl ((definedat: Pos.pos), d) = match d with
        INSNPRED (name, pred) ->
           let pdecl = {
              definedat;
              args = Types.StringMap.empty;
              afields = Types.StringSet.empty;
              e = pred;
           } in
           preds := Types.StringMap.add name pdecl (!preds);
           predorder := name :: !predorder
      | HAZARD (name, desc, guard, assignments, trigger, condition) ->
           let trigger = P_BYEXPR trigger in
           let m = { guard; assignments; trigger; condition; } in
           let haz = { name; definedat; desc; m; } in
           hazards := haz :: !hazards
      | TRANSFER (assignments, trigger, condition, result) ->
           let trigger = P_BYEXPR trigger in
           let guard = T.BOOLCONSTANT (definedat, true) in
           let m = { guard; assignments; trigger; condition; } in
           let xfer = { definedat; m; result; } in
           transfers := xfer :: !transfers
   in
   List.iter add_decl decls;

   {
      predicates = !preds;
      predorder = List.rev !predorder;
      hazards = (*List.rev*) !hazards;
      transfers = (*List.rev*) !transfers;
   }

let etrue pos = T.BOOLCONSTANT (pos, true)

%}

%token EOF
%token <int> NUMBER
%token <string> QSTRING IDENT
/* reserved words */
/* XXX true and false don't need to be reserved, just predefined */
%token CAST GO FALSE FIELD FITS HAZARD
%token IN INSNP MODE MODIFIER NOTIN NULLIFY STAY TRANSFER TRUE
/* grouping punctuation */
%token LBRACE RBRACE LBRACK RBRACK LPAREN RPAREN
/* multicharacter punctuation */
%token AMPAMP BANGEQ BARBAR CARETCARET COLONCOLON
%token EQEQ GTEQ GTGT LTEQ LTLT RARROW
/* single-character punctuation */
%token AMP BANG BAR CARET COLON COMMA DOT EQ GT LT MINUS
%token PCT PLUS QUES SEMIC SLASH STAR TILDE

%type <Hazardtree.decls> file
%start file

%%

/* **************************************** */

file:
   decls EOF			{ assemble (List.rev $1) }
;

decls: /* built in reverse order */
     /* nil */			{ [] }
   | decls decl			{ $2 :: $1 }
;

decl:
     INSNP insnp_decl SEMIC		{ (pos (), $2) }
   | HAZARD hazard_decl SEMIC		{ (pos (), $2) }
   | TRANSFER transfer_decl SEMIC	{ (pos (), $2) }
;

insnp_decl:
   IDENT COLON expr			{ INSNPRED ($1, $3) }
;

hazard_decl:
   hazard_head assignments expr RARROW cond {
	let (name, desc, guard) = $1 in
	HAZARD (name, desc, guard, $2, $3, $5)
   }
;

hazard_head:
     IDENT QSTRING COLON		{ ($1, $2, etrue (pos ())) }
   | IDENT QSTRING BAR expr COLON	{ ($1, $2, $4) }
;

transfer_decl:
   assignments expr RARROW cond GTGT transference { TRANSFER ($1, $2, $4, $6) }
;

transference:
     jump_transference			{ H.JUMP $1 }
   | branch_transference		{ $1 }
;

branch_transference:
   jump_transference BARBAR jump_transference	{ H.BRANCH ($1, $3) }
;

jump_transference:
     destination				{ H.EXECUTE_AND $1 }
   | LPAREN NULLIFY AMPAMP destination RPAREN	{ H.NULLIFY_AND $4 }
;

destination:
     GO					{ H.GO }
   | STAY				{ H.STAY }
;

assignments:
     /* nil */				{ [] }
   | LBRACE assignments_body RBRACE	{ List.rev $2 }
;

assignments_body: /* built in reverse order */
     assignment				{ [$1] }
   | assignments_body assignment	{ $2 :: $1 }
;

assignment:
   IDENT EQ expr SEMIC			{ H.ASSIGN (pos (), $1, $3) }
;

/* **************************************** */

cond:
   alt_cond				{ $1 }
;

alt_cond:
     seq_cond				{ $1 }
   | alt_cond BAR seq_cond		{ H.COND_ALT ($1, $3) }
;

seq_cond:
     suffix_cond			{ $1 }
   | seq_cond suffix_cond		{ H.COND_SEQ ($1, $2) }
;

suffix_cond:
     base_cond				{ $1 }
   | suffix_cond QUES			{ H.COND_OPT $1 }
   | suffix_cond PLUS			{ H.COND_PLUS $1 }
   | suffix_cond STAR			{ H.COND_OPT (H.COND_PLUS $1) }
;

base_cond:
     DOT				{ H.COND_ANY }
   | LBRACK IDENT RBRACK		{ H.COND_PREDNAME $2 }
   | LBRACK caretident RBRACK		{ H.COND_PREDEXPR $2 }
   | LBRACE expr RBRACE			{ H.COND_PREDEXPR $2 }
   | LPAREN cond RPAREN			{ $2 }
;

/* these two are here to make the positions nice */
caretident:
   CARET caretident_ident		{ T.UOP (pos (), T.LOGNOT, $2) }
;
caretident_ident:
   IDENT				{ T.READVAR (pos (), $1) }
;

/* **************************************** */

/*
 * expressions
 *
 * (caution: mostly cutpasted from encodingparse.mly; should figure
 * out a way to share)
 */

expr:
   or_expr			{ $1 }
;

or_expr:
     xor_expr			{ $1 }
   | or_expr BARBAR xor_expr	{ T.BOP (pos (), $1, T.LOGOR, $3) }
;

xor_expr:
     and_expr			{ $1 }
   | xor_expr CARETCARET and_expr { T.BOP (pos (), $1, T.LOGXOR, $3) }
;

and_expr:
     bitor_expr			{ $1 }
   | and_expr AMPAMP bitor_expr { T.BOP (pos (), $1, T.LOGAND, $3) }
;

bitor_expr:
     bitxor_expr		{ $1 }
   | bitor_expr BAR bitxor_expr	{ T.BOP (pos (), $1, T.BITOR, $3) }
;

bitxor_expr:
     bitand_expr		{ $1 }
   | bitxor_expr CARET bitand_expr { T.BOP (pos (), $1, T.BITXOR, $3) }
;

bitand_expr:
     compare_expr		{ $1 }
   | bitand_expr AMP compare_expr { T.BOP (pos (), $1, T.BITAND, $3) }
;

compare_expr:
     shift_expr				{ $1 }
   | compare_expr EQEQ shift_expr	{ T.BOP (pos (), $1, T.EQ, $3) }
   | compare_expr BANGEQ shift_expr	{ T.BOP (pos (), $1, T.NEQ, $3) }
   | compare_expr LT shift_expr		{ T.BOP (pos (), $1, T.LT, $3) }
   | compare_expr GT shift_expr		{ T.BOP (pos (), $3, T.LT, $1) }
   | compare_expr LTEQ shift_expr	{ T.BOP (pos (), $1, T.LTEQ, $3) }
   | compare_expr GTEQ shift_expr	{ T.BOP (pos (), $3, T.LTEQ, $1) }
   | compare_expr IN shift_expr		{ T.BOP (pos (), $1, T.IN, $3) }
   | compare_expr NOTIN shift_expr	{ T.BOP (pos (), $1, T.NOTIN, $3) }
   | compare_expr FITS typename		{ T.FITS (pos (), $1, $3) }
;

shift_expr:
     add_expr			{ $1 }
   | shift_expr LTLT add_expr	{ T.BOP (pos (), $1, T.SHL, $3) }
   | shift_expr GTGT add_expr	{ T.BOP (pos (), $1, T.SHR, $3) }
;

add_expr:
     mul_expr			{ $1 }
   | add_expr PLUS mul_expr	{ T.BOP (pos (), $1, T.ADD, $3) }
   | add_expr MINUS mul_expr	{ T.BOP (pos (), $1, T.SUB, $3) }
;

mul_expr:
     prefix_expr		{ $1 }
   | mul_expr STAR prefix_expr	{ T.BOP (pos (), $1, T.MUL, $3) }
   | mul_expr SLASH prefix_expr	{ T.BOP (pos (), $1, T.DIV, $3) }
   | mul_expr PCT prefix_expr	{ T.BOP (pos (), $1, T.MOD, $3) }
;

prefix_expr:
     primary_expr		{ $1 }
   | PLUS prefix_expr		{ T.UOP (pos (), T.PLUS, $2) }
   | MINUS prefix_expr		{ T.UOP (pos (), T.NEG, $2) }
   | BANG prefix_expr		{ T.UOP (pos (), T.LOGNOT, $2) }
   | TILDE prefix_expr		{ T.UOP (pos (), T.BITNOT, $2) }
   | CAST LPAREN castsequence RPAREN prefix_expr {
        let wrap (nt, ot) e =
	   T.CAST (pos (), nt, ot, e)
        in
        List.fold_right wrap $3 $5
     }
/*
   | EVAL prefix_expr		{ T.UOP (pos (), T.EVAL, $2) }
   | AT prefix_expr		{ T.UOP (pos (), T.UNEVAL, $2) }
*/
   | MODE IDENT			{ T.MODE (pos (), $2) }
;

castsequence:
     typename LTEQ typename	{ [($1, $3)] }
   | typename LTEQ castsequence {
	match $3 with
	     [] -> Util.crash "hazardparse: empty cast sequence"
	   | (nt, ot) :: more -> ($1, nt) :: (nt, ot) :: more
     }
;

primary_expr:
     basic_expr			{ $1 }
   | LPAREN expr RPAREN		{ $2 }
   | LPAREN expr RPAREN COLONCOLON typename { T.ANNOTATE (pos (), $5, $2) } 
;

basic_expr:
     IDENT			{ T.READVAR (pos (), $1) }
   | DOT			{ T.HERE (pos ()) }
   | TRUE			{ T.BOOLCONSTANT (pos (), true) }
   | FALSE			{ T.BOOLCONSTANT (pos (), false) }
   | NUMBER			{ T.NUMCONSTANT (pos (), $1) }
   | IDENT LPAREN arglist RPAREN { T.PACK (pos (), $1, $3) }
   | LBRACK exprlist RBRACK	{ T.LIST (pos (), $2) }
   | modifier			{ $1 }
   | basic_expr COLONCOLON typename { T.ANNOTATE (pos (), $3, $1) } 
;

modifier:
   MODIFIER IDENT LPAREN exprlist RPAREN { T.MODIFIER (pos (), $2, $4) }
;

exprlist: /* built in reverse order */
     expr			{ [$1] }
   | exprlist COMMA expr	{ $3 :: $1 }
;

arglist:
   exprlist			{ List.rev $1 }
;

typename:
     IDENT			{ TT.PLAINTYPE (pos (), $1) }
   | IDENT LPAREN NUMBER RPAREN	{ TT.WIDTHTYPE (pos (), $1, $3) }
;

%%

