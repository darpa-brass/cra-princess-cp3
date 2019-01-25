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
module T = Encodingtree

let pos () = Pos.fromparser ()

let subenum es =
   let truncate (_pos, name, optval) =
      begin
         match optval with
             None -> ()
           | Some _ ->
                Util.say "Unexpected explicit value in subenum declaration";
                Util.fail ()
      end;
      name
   in
   List.map truncate es

(*
let strippos x = x.x
*)

%}

%token EOF
%token <int> NUMBER
%token <string> QSTRING IDENT
/* reserved words */
/* XXX true and false don't need to be reserved, just predefined */
%token CAST DEFINEDP ELSE ENCODE ENUM EVAL FALSE FIELD FITS FORM IF IN
%token MACRO MODE MODIFIER NOTIN ORD RELOCATE SUBENUM TRUE USE WARN
/* grouping punctuation */
%token LBRACE RBRACE LBRACK RBRACK LPAREN RPAREN
/* multicharacter punctuation */
%token AMPAMP BANGEQ BARBAR CARETCARET COLONCOLON EQEQ GTEQ GTGT
%token LTEQ LTLT
/* single-character punctuation */
%token AMP AT BANG BAR CARET COLON COMMA DOT EQ GT LT
%token MINUS PCT PLUS SEMIC SLASH
%token STAR TILDE

%type <Encodingtree.decl list> file

%start file

%%

file:
   decls EOF			{ List.rev $1 }
;

/*
 * Declarations
 */

decls: /* built in reverse order */
     /* nil */			{ [] }
   | decls decl			{ $2 :: $1 }
;

decl:
     FIELD field_decl SEMIC	{ $2 }
   | SUBENUM IDENT EQ enumeration SEMIC { T.SUBENUM (pos (), $2, subenum $4) }
   | SUBENUM IDENT EQ expr SEMIC { T.SUBENUMEXPR (pos (), $2, $4) }
   | FORM formhead formbody	{ T.FORM (pos (), $2, $3) }
;

field_decl:
     IDENT COLONCOLON typename		{ T.FIELD (pos (), $1, $3, None) }
   | IDENT COLONCOLON typename relinfo	{ T.FIELD (pos (), $1, $3, Some $4) }
   | IDENT COLONCOLON enumtype		{ T.ENUMFIELD (pos (), $1, $3, None) }
   | IDENT COLONCOLON enumtype relinfo { T.ENUMFIELD (pos (), $1, $3, Some $4)}
;

/*
 * Fields and types
 */

typename:
     IDENT				     { T.PLAINTYPE (pos (), $1) }
   | IDENT LPAREN NUMBER RPAREN		     { T.WIDTHTYPE (pos (), $1, $3) }
   | IDENT LPAREN typename RPAREN	     {
        if $1 = "expr" then T.EXPRTYPE (pos (), $3)
        else begin
           Pos.sayat (pos ()) "Invalid type argument";
           Util.fail ();
           T.PLAINTYPE (pos (), $1)
        end
     }
;

enumtype:
     ENUM LPAREN NUMBER RPAREN enumeration   { T.ENUMTYPE (pos (), $3, $5) }
;

relinfo:
   RELOCATE NUMBER		{ ($2) }
;

enumeration:
     LBRACE enum_items RBRACE	{ List.rev $2 }
   | LBRACE enum_items COMMA RBRACE { List.rev $2 }
;

enum_items: /* built in reverse order */
     enum_item			{ [$1] }
   | enum_items COMMA enum_item	{ $3 :: $1 }
;

enum_item:
     IDENT			{ (pos (), $1, None) }
   | IDENT EQ NUMBER		{ (pos (), $1, Some $3) }
;

/*
 * Forms and encodings
 */

formhead:
     LBRACK fieldnamelist RBRACK { List.rev $2 }
   | IDENT {
        if $1 = "_" then []
        else begin
           Util.say "Expected _ or field list after 'form'";
           Util.fail ();
           []
        end
     }
;

fieldnamelist: /* built in reverse order */
     fieldname			{ [$1] }
   | fieldnamelist COMMA fieldname { $3 :: $1 }
;

fieldname:
     IDENT			{ T.FIELDREF_(pos (), $1, None, None) }
   | IDENT EQ NUMBER {
        T.FIELDREF_(pos (), $1, None, Some $3)
     }
   | IDENT COLONCOLON typename	{
        T.FIELDREF_(pos (), $1, Some $3, None)
     }
   | IDENT COLONCOLON typename EQ NUMBER {
        T.FIELDREF_(pos (), $1, Some $3, Some $5)
     }
;

formbody:
   block SEMIC			{ $1 }
;

block:
     LBRACE RBRACE		{ [] }
   | LBRACE statementlist RBRACE { List.rev $2 }
;

statementlist: /* built in reverse order */
     statement			{ [$1] }
   | statementlist statement	{ $2 :: $1 }
;

statement:
     pattern EQ expr SEMIC		{ T.ASSIGN (pos (), $1, $3) }
   | ENCODE insn guard EQ block SEMIC	{ T.ENCODE (pos (), $2, $3, $5) }
   | ENCODE insn guard SEMIC		{ T.ENCODE (pos (), $2, $3, []) }
   | MACRO insn guard EQ block SEMIC	{ T.MACRO (pos (), $2, $3, $5) }
   | if_statement			{ $1 }
   | USE IDENT SEMIC	{ T.USE (pos (), $2, [], []) }
   | USE IDENT operands SEMIC	{ T.USE (pos (), $2, [], $3) }
   | USE IDENT LPAREN arglist RPAREN SEMIC { T.USE (pos (), $2, $4, []) }
   | USE IDENT LPAREN arglist RPAREN operands SEMIC {T.USE(pos (), $2, $4, $6)}
   | WARN QSTRING SEMIC { T.WARN (pos (), $2) }
;

if_statement:
     IF pexpr block			{ T.IF (pos (), $2, $3, []) }
   | IF pexpr block ELSE block		{ T.IF (pos (), $2, $3, $5) }
   | IF pexpr block ELSE if_statement	{ T.IF (pos (), $2, $3, [$5]) }
;

insn:
   IDENT specparams opparams	{ T.INSN(pos (), $1, $2, $3) }
;

specparams:
     /* nil */			{ [] }
   | LPAREN paramlist RPAREN	{ List.rev $2 }
;

opparams:
     /* nil */			{ [] }
   | paramlist			{ List.rev $1 }
;

paramlist: /* built in reverse order */
     param			{ [$1] }
   | paramlist COMMA param	{ $3 :: $1 }
;

param:
     IDENT			{ (pos (), $1, None) }
   | IDENT COLONCOLON typename	{ (pos (), $1, Some $3) }
;

arglist:
   exprlist			{ List.rev $1 }
;

operands:
   operlist			{ List.rev $1 }
;

operlist: /* built in reverse order */
     operand			{ [$1] }
   | operlist COMMA operand	{ $3 :: $1 }
;

operand:
/* XXX */
/* can't do this; it's ambiguous: foo(arg) op, op vs. foo (op), op, op */
/* expr				{ $1 } */
   operand_expr			{ $1 }
;

guard:
     /* nil */			{ None }
   | COLON expr			{ Some $2 }
;

/*
 * Patterns
 *
 * Left-hand side of assignments.
 */
pattern:
     IDENT			{ T.SETVAR (pos (), $1) }
   | IDENT LPAREN patternlist RPAREN { T.UNPACK (pos (), $1, List.rev $3) }
;

patternlist: /* built in reverse order */
     pattern			{ [$1] }
   | patternlist COMMA pattern	{ $3 :: $1 }
;

/*
 * Expressions
 *
 * These are description-level expressions, not assembly language
 * expressions.
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
   | DEFINEDP LPAREN expr RPAREN { T.UOP (pos (), T.DEFINEDP, $3) }
   | ORD LPAREN expr RPAREN	{ T.UOP (pos (), T.ORD, $3) }
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

castsequence:
     typename LTEQ typename	{ [($1, $3)] }
   | typename LTEQ castsequence {
	match $3 with
	     [] -> Util.crash "encodingparse: empty cast sequence"
	   | (nt, ot) :: more -> ($1, nt) :: (nt, ot) :: more
     }
;

primary_expr:
     basic_expr			{ $1 }
   | LPAREN expr RPAREN		{ $2 }
   | LPAREN expr RPAREN COLONCOLON typename { T.ANNOTATE (pos (), $5, $2) } 
;

operand_expr:
     basic_expr			{ $1 }
   | MINUS, NUMBER		{ T.NUMCONSTANT (pos (), -$2) }
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

%%
