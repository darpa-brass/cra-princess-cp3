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
module T = Relocstree

let pos () = Pos.fromparser ()

let exprblock x e = [T.ASSIGN (pos (), T.WRITEVAR (pos (), x), e)]

let mkmod name arg block =
   { T.name; T.definedat=pos (); T.arg; T.block; }

let mkop name block =
   { T.name; T.definedat=pos (); T.computation=block; }

let mkcode value name semantics =
   { T.name; T.definedat=pos (); T.value; T.semantics; }

%}

%token EOF
%token <int> NUMBER
%token <string> IDENT QSTRING
/* reserved words */
%token AS CAST CODES DATA ELSE EVAL EXPRESSION
%token FALSE FIELDS FITS GROUP
%token IF IN INPUT INSTRUCTION MANY MANYATONCE
%token MATCH MODE MODIFIER NOGENERATE NOTIN NULL ONE OPS ORDER OUTPUT
%token REQUIRE RESOLVE SUBSTITUTE
%token TRUE UNSUPPORTED WARN WHEN
/* grouping punctuation */
%token LBRACE RBRACE LBRACK RBRACK LPAREN RPAREN
/* multicharacter punctuation */
%token AMPAMP BANGEQ BARBAR CARETCARET COLONCOLON EQEQ GTEQ GTGT
%token LTEQ LTLT LTMINUSGT
/* single-character punctuation */
%token AMP AT BANG BAR CARET COLON COMMA DOT EQ GT LT
%token MINUS PCT PLUS SEMIC SLASH
%token STAR TILDE

%type <Relocstree.decl list> file
%start file

%%

file:
   decls EOF			{ List.concat (List.rev $1) }
;

/*
 * Declarations
 */

decls: /* built in reverse order */
     /* nil */			{ [] }
   | decls decl			{ $2 :: $1 }
;

decl:
     FIELDS LBRACE fields RBRACE	{ List.rev $3 } 
   | MODIFIER LBRACE modifierdecls RBRACE	{ List.rev $3 } 
   | OPS LBRACE ops RBRACE		{ List.rev $3 }
   | CODES IDENT LBRACE codes RBRACE	{[T.D_CODES (pos (), $2, List.rev $4)]}
   | substitute				{ [$1] }
   | group				{ [$1] }
/* XXX
   | MACHINE IDENT SEMIC	{ [T.D_MACHINE (pos (), $2)] }
   | RELOCSTYLE IDENT SEMIC	{
	let s =
	   if $2 = "rel" then T.REL
	   else if $2 = "rela" then T.RELA
	   else begin
		Pos.sayat (pos ()) ("Invalid relocstyle " ^ $2);
		Util.fail ();
                T.RELA
	   end
	in
	[T.D_RELOCSTYLE (pos (), s)]
     }
*/
;

fields: /* built in reverse order */
     /* nil */				{ [] }
   | fields field			{ (T.D_FIELD $2) :: $1 }
;

field:
     INSTRUCTION IDENT methods {
	let name = $2 in
        let extname = name in
        let definedat = pos () in
	let (readop, writeop) = $3 in
	let typename = None in
	{ T.name; T.extname; T.definedat; T.frominstruction = true;
	  T.readop; T.writeop; T.typename; }
     }
   | INSTRUCTION IDENT EQ IDENT methods {
	let name = $2 in
	let extname = $4 in
        let definedat = pos () in
	let (readop, writeop) = $5 in
	let typename = None in
	{ T.name; T.extname; T.definedat; T.frominstruction = true;
	  T.readop; T.writeop; T.typename; }
     }
   | DATA IDENT COLONCOLON typename SEMIC {
	let name = $2 in
        let extname = name in
        let definedat = pos () in
	let (readop, writeop) = ([], []) in
	let typename = Some $4 in
	{ T.name; T.extname; T.definedat; T.frominstruction = false;
	  T.readop; T.writeop; T.typename; }
     }
;

methods:
     SEMIC				{ ([], []) }
   | LBRACE RBRACE			{ ([], []) }
   | LBRACE INPUT block OUTPUT block RBRACE { ($3, $5) }
   | LBRACE INPUT block RBRACE		{ ($3, []) }
   | LBRACE OUTPUT block RBRACE		{ ([], $3) }
   | LBRACE OUTPUT block INPUT block RBRACE { ($5, $3) }
;

modifierdecls: /* built in reverse order */
     /* nil */				{ [] }
   | modifierdecls modifierdecl		{ (T.D_MODIFIER $2) :: $1 }
;

modifierdecl:
     IDENT LPAREN IDENT RPAREN block	{ mkmod $1 $3 $5 }
   | IDENT LPAREN IDENT RPAREN EQ expr SEMIC { mkmod $1 $3 (exprblock $1 $6) }
;

ops: /* built in reverse order */
     /* nil */				{ [] }
   | ops op				{ (T.D_OP $2) :: $1 }
;

op:
     IDENT block			{ mkop $1 $2 }
   | IDENT EQ expr SEMIC		{ mkop $1 (exprblock $1 $3) }
;

codes: /* built in reverse order */
     /* nil */				{ [] }
   | codes code				{ $2 :: $1 }
;

code:
     STAR IDENT codeimpl SEMIC		{ mkcode None $2 $3 }
   | NUMBER IDENT codeimpl SEMIC	{ mkcode (Some $1) $2 $3 }
;

codeimpl:
     NULL				{ T.NOP }
   | UNSUPPORTED			{ T.UNSUPPORTED }
   | IDENT IN identlist			{ T.APPLYIN ($1, List.rev $3, true) }
   | IDENT IN identlist NOGENERATE	{ T.APPLYIN ($1, List.rev $3, false) }
;

substitute:
     SUBSTITUTE IDENT LBRACE substitutions RBRACE {
	let body = List.rev $4 in
	let guard = T.BOOLCONSTANT (pos (), true) in
	T.D_SUBST { T.definedat=pos (); T.binfmt=$2; T.guard; T.body; }
     }
   | SUBSTITUTE IDENT BAR expr LBRACE substitutions RBRACE {
	let body = List.rev $6 in
	T.D_SUBST { T.definedat=pos (); T.binfmt=$2; T.guard=$4; T.body; }
     }
;

substitutions: /* built in reverse order */
     substitution			{ [$1] }
   | substitutions substitution		{ $2 :: $1 }
;

substitution:
   IDENT COLON expr LTMINUSGT expr SEMIC { (pos (), $1, $3, $5) }
;

group:
     GROUP IDENT LBRACE groupdecls RBRACE	{
	T.D_GROUP {
	   T.definedat = pos (); T.binfmt = $2;
	   T.groupdecls = List.rev $4;
	}
     }
;

groupdecls: /* built in reverse order */
     /* nil */			{ [] }
   | groupdecls groupdecl	{ $2 @ $1 }
;

groupdecl: /* in reverse order */
     MATCH matchbody SEMIC	{ $2 }
   | ORDER identlist SEMIC	{ [T.GD_ORDER (pos (), List.rev $2)] }
   | INPUT block		{ [T.GD_INPUT (pos (), $2)] }
   | OUTPUT block		{ [T.GD_OUTPUT (pos (), $2)] }
   | RESOLVE block		{ [T.GD_RESOLVE (pos (), $2)] }
;

matchbody: /* in reverse order */
     matchdecls			{ $1 }
   | matchbody WHEN INPUT expr	{ T.GD_WHENINPUT (pos (), $4) :: $1 }
   | matchbody WHEN OUTPUT expr	{ T.GD_WHENOUTPUT (pos (), $4) :: $1 }

matchdecls: /* built in reverse order */
     matchdecl			{ [$1] }
   | matchdecls COMMA matchdecl	{ $3 :: $1 }
;

matchdecl:
   howmany expr AS IDENT	{ T.GD_MATCH (pos (), $1, $2, $4) }
;

howmany:
     ONE 			{ T.ONE }
   | MANY 			{ T.MANY }
   | MANYATONCE 		{ T.MANYATONCE }
;

identlist: /* built in reverse order */
    IDENT				{ [$1] }
  | identlist COMMA IDENT		{ $3 :: $1 }
;

/*
 * Statements
 */

block:
   LBRACE stmts RBRACE			{ List.rev $2 }
;

stmts: /* built in reverse order */
     stmt				{ [$1] }
   | stmts stmt				{ $2 :: $1 }
;

stmt:
     block				{ T.BLOCK $1 }
   | pattern EQ expr SEMIC		{ T.ASSIGN (pos (), $1, $3) }
   | if_statement			{ $1 }
   | REQUIRE expr SEMIC			{ T.REQUIRE (pos (), $2) }
   | WARN QSTRING SEMIC { T.WARN (pos (), $2) }
;

if_statement:
     IF pexpr block			{ T.IF (pos (), $2, $3, []) }
   | IF pexpr block ELSE block		{ T.IF (pos (), $2, $3, $5) }
   | IF pexpr block ELSE if_statement	{ T.IF (pos (), $2, $3, [$5]) }
;

/*
 * patterns
 */

pattern:
     IDENT				{ T.WRITEVAR (pos (), $1) }
     /* allow "input" and "output" as vars in patterns */
   | INPUT				{ T.WRITEVAR (pos (), "input") }
   | OUTPUT				{ T.WRITEVAR (pos (), "output") }
   | pattern DOT IDENT			{ T.WRITEFIELD (pos (), $1, $3) }
   | IDENT LPAREN patternlist RPAREN { T.UNPACK (pos (), $1, List.rev $3) }
;

patternlist: /* built in reverse order */
     pattern			{ [$1] }
   | patternlist COMMA pattern	{ $3 :: $1 }
;

/*
 * expressions
 *
 * (caution: mostly cutpasted from encodingparse.mly; should figure
 * out a way to share)
 */

pexpr:
   LPAREN expr RPAREN		{ $2 }
;

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
   | EVAL prefix_expr		{ T.UOP (pos (), T.EVAL, $2) }
   | AT prefix_expr		{ T.UOP (pos (), T.UNEVAL, $2) }
   | MODE IDENT			{ T.MODE (pos (), $2) }
;

/* XXX: this should be propagated back to encodingparse */
castsequence:
     typename LTEQ typename	{ [($1, $3)] }
   | typename LTEQ castsequence {
	match $3 with
	     [] -> Util.crash "relocsparse: empty cast sequence"
	   | (nt, ot) :: more -> ($1, nt) :: (nt, ot) :: more
     }

primary_expr:
     basic_expr			{ $1 }
   | LPAREN expr RPAREN		{ $2 }
   | LPAREN expr RPAREN COLONCOLON typename { T.ANNOTATE (pos (), $5, $2) } 
;

basic_expr:
     IDENT			{ T.READVAR (pos (), $1) }
     /* allow "input" and "output" as vars in exprs */
   | INPUT			{ T.READVAR (pos (), "input") }
   | OUTPUT			{ T.READVAR (pos (), "output") }
   | DOT			{ T.HERE (pos ()) }
   | TRUE			{ T.BOOLCONSTANT (pos (), true) }
   | FALSE			{ T.BOOLCONSTANT (pos (), false) }
   | NUMBER			{ T.NUMCONSTANT (pos (), $1) }
   | QSTRING			{ T.STRCONSTANT (pos (), $1) }
   | IDENT LPAREN arglist RPAREN { T.PACK (pos (), $1, $3) }
   | LBRACK exprlist RBRACK	{ T.LIST (pos (), $2) }
   | modifier			{ $1 }
   | basic_expr DOT IDENT	{ T.READMEMBER (pos (), $1, $3) } 
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
     IDENT			{ T.PLAINTYPE (pos (), $1) }
   | IDENT LPAREN NUMBER RPAREN	{ T.WIDTHTYPE (pos (), $1, $3) }
   | EXPRESSION typename	{ T.EXPRTYPE (pos (), $2) }
;

%%
