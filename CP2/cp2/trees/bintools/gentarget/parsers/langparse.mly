%{
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

open Pos
module T = Langtree
module TY = Typetree
module E = Exprtree

let pos () = Pos.fromparser ()

(*
 * for internal use (and should go away)
 *)

type pos = Pos.pos

(*
 * Intermediate results.
 *)

let linecomments = ref []
let blockcomments = ref []
let charset = ref ""
let letters = ref []
let subletters = ref []
let tokens = ref Types.StringMap.empty
let keywords = ref []
let matches = ref []
let separators = ref []
let tagrules = ref []

(**************************************************************)
(* Updaters for the results *)

let addlinecomment pos s =
   linecomments := (!linecomments) @ [(pos, s)]

let addblockcomment pos nest s1 s2 =
   blockcomments := (!blockcomments) @ [(pos, nest, s1, s2)]

let setcharset pos s =
   match s with
        "ascii" -> charset := s
      | _ -> Pos.crashat pos ("Unsupported character set " ^ s) (* XXX *)

let addletter v =
   letters := !letters @ [v]

let addsubletter v =
   subletters := !subletters @ [v]

let addtoken (pos, name, ty) =
   tokens := Types.StringMap.add name (pos, ty, true) !tokens

let addkeyword pos str result =
   keywords := !keywords @ [T.KWDECL (pos, str, result)]

let addmatch pos tokpats result =
   matches := !matches @ [T.MATCHDECL (pos, tokpats, result)]

let addseparator pos s =
   separators := (!separators) @ [(pos, s)]

let etrue () = E.BOOLCONSTANT (pos (), true)
let addtagrule tokpats guard (rpos, optag, e) =
   let pos = pos () in
   let r = T.TAGRULE (pos, List.rev tokpats, guard, rpos, optag, e) in
   tagrules := !tagrules @ [r]


(**************************************************************)
(* other support logic  *)

let notype = TY.PLAINTYPE (pos (), "_")

let produce () =
   {
	T.linecomments = !linecomments;
	T.blockcomments = !blockcomments;
	T.separators = !separators;
        T.letters = !letters;
	T.subletters = !subletters;
	T.tokens = !tokens;
	T.keywords = !keywords;
	T.matches = !matches;
        T.tagrules = !tagrules;
   }

(**************************************************************)
(* Grammar *)

%}

%token EOF
%token <int> NUMBER
%token <string> QSTRING IDENT
%token COMMENTS LINE NEST FLAT
%token CHARACTERS CHARSET LETTER SUBLETTER
%token TOKENS KEYWORDS MATCH
%token SYNTAX SEPARATOR
%token TAGRULES
%token CAST CONSTANTP EVAL EXPRESSION FITS ORD FALSE TRUE
%token LBRACE RBRACE LBRACK RBRACK LPAREN RPAREN
%token AMP AMPAMP BANG BANGEQ BAR BARBAR CARET CARETCARET COLONCOLON COMMA
%token DOTDOT EQ
%token EQEQ EQGT GT GTEQ GTGT LT LTEQ LTLT MINUS PCT PLUS PLUSPLUS
%token SEMIC
%token SLASH STAR

%type <Langtree.properties> file

%start file

%%

file:
   decls EOF					{ produce () }
;

decls:
     /* nil */					{ () }
   | decls decl					{ () }
;

decl:
     comments_section				{ () }
   | characters_section				{ () }
   | tokens_section				{ () }
   | keywords_section				{ () }
   | match_section				{ () }
   | syntax_section				{ () }
   | tag_section				{ () }
;

/*
 * Stuff related to comments
 */

comments_section:
   COMMENTS LBRACE comment_decls RBRACE		{ () }
;

comment_decls: /* built in reverse order */
     /* nil */					{ () }
   | comment_decls comment_decl			{ () }
;

comment_decl:
     LINE QSTRING SEMIC		{ addlinecomment (pos ()) $2 }
   | NEST QSTRING QSTRING SEMIC	{ addblockcomment (pos ()) true $2 $3 }
   | FLAT QSTRING QSTRING SEMIC	{ addblockcomment (pos ()) false $2 $3 }
;

/*
 * Stuff related to characters and character sets
 */

characters_section:
   CHARACTERS LBRACE character_decls RBRACE	{ () }
;

character_decls: /* built in reverse order */
     /* nil */					{ () }
   | character_decls character_decl		{ () }
;

character_decl:
     CHARSET QSTRING SEMIC	{ setcharset (pos ()) $2 }
   | LETTER QSTRING SEMIC	{ addletter (*(pos ())*) $2 }
   | SUBLETTER QSTRING SEMIC	{ addsubletter (*(pos ())*) $2 }
;

/*
 * Stuff related to tokenization: token declarations
 */

tokens_section:
   TOKENS LBRACE token_decls RBRACE		{ List.rev $3 }
;

token_decls: /* built in reverse order */
     /* nil */					{ [] }
   | token_decls token_decl			{ $2 :: $1 }
;

token_decl:
     toktype SEMIC				{ addtoken $1 }
;

/*
 * Stuff related to tokenization: keywords
 */

keywords_section:
   KEYWORDS LBRACE keywords RBRACE		{ () }
;

keywords: /* built in reverse order */
     /* nil */					{ () }
   | keywords keyword				{ () }
;

keyword:
   QSTRING EQGT tokval SEMIC	{ addkeyword (pos ()) $1 $3 }
;

/*
 * Stuff related to tokenization: compound token matching rules
 */

match_section:
   MATCH LBRACE matches RBRACE			{ () }
;

matches: /* built in reverse order */
     /* nil */					{ () }
   | matches match_				{ () }
;

match_:
     tokpats EQGT tokval SEMIC	{ addmatch (pos ()) (List.rev $1) $3 }
/* XXX this was intended but isn't implemented yet
     QSTRING EQGT tokval SEMIC	{ addmatch (pos ()) (... $1) $3 }
*/
;

/*
 * stuff related to assembly syntax
 */

syntax_section:
   SYNTAX LBRACE syntax_decls RBRACE		{ () }
;

syntax_decls: /* built in reverse order */
     /* nil */					{ () }
   | syntax_decls syntax_decl			{ () }
;

syntax_decl:
   SEPARATOR QSTRING SEMIC	{ addseparator (pos ()) $2 }
;

/*
 * operand tag matching rules
 */

tag_section:
   TAGRULES LBRACE tag_decls RBRACE		{ () }
;

tag_decls:
     /* nil */					{ () }
   | tag_decls tag_decl				{ () }
;

/* XXX: need expression stuff on the left */
tag_decl:
     exprpats EQGT tagval SEMIC			{ addtagrule $1 (etrue ()) $3 }
   | exprpats BAR expr EQGT tagval SEMIC	{ addtagrule $1 $3 $5 }
;

exprpats: /* built in reverse order */
     /* nil */					{ [] }
   | exprpats exprpat				{ $2 :: $1 }
;

exprpat:
     tokpat					{ T.XP_TOKEN (pos (), $1) }
   | LBRACK tokpats RBRACK			{ T.XP_EXPR (pos (), $2, None) }
   | LBRACK tokpats RBRACK LPAREN pattern RPAREN { T.XP_EXPR (pos (), $2, Some $5) }
   | LBRACK STAR RBRACK				{ T.XP_EXPRANY (pos (), None) }
   | LBRACK STAR RBRACK LPAREN pattern RPAREN { T.XP_EXPRANY (pos (), Some $5) }
;

tagval:
   IDENT LPAREN expr RPAREN	{ (pos (), $1, $3) }
;


/*
 * tokens
 */

/* token type: type form -- the arg is a type name */
toktype:
     IDENT			{ (pos (), $1, TY.PLAINTYPE (pos (), "_")) }
   | IDENT LPAREN typename RPAREN { (pos (), $1, $3) }
;

/* token pattern: binder form -- the arg is a pattern */
tokpat:
     IDENT			{ T.TOKENPAT (pos (), $1, None) }
   | IDENT LPAREN pattern RPAREN { T.TOKENPAT (pos (), $1, Some $3) }
;

/* token value: expression form -- the arg is an expression */
tokval:
     IDENT			{ T.TOKENEXPR (pos (), $1, None) }
   | IDENT LPAREN expr RPAREN	{ T.TOKENEXPR (pos (), $1, Some $3) }
;

tokpats: /* built in reverse order */
     tokpat			{ [$1] }
   | tokpats tokpat		{ $2 :: $1 }
;

typename:
     IDENT			{ TY.PLAINTYPE (pos (), $1) }
   | IDENT LPAREN NUMBER RPAREN	{ TY.WIDTHTYPE (pos (), $1, $3) }
   | EXPRESSION typename	{ TY.EXPRTYPE (pos (), $2) }
;

/*
 * Patterns for token values
 *
 * Since we don't support compound types for tokens, there are
 * only two cases: a constant and a binder.
 * XXX: should come up with a common notion of "constant", but not yet
 */

pattern:
     IDENT			{ T.P_BINDER (pos (), notype, $1) }
   | QSTRING			{ T.P_CONSTANT_S (pos (), $1) }
   | NUMBER			{ T.P_CONSTANT_N (pos (), $1) }
;

/*
 * Description-level expressions. These include the operators used in
 * guard expressions, including logical operators and comparisons, but
 * not e.g. bit operations. Juxtaposition is not allowed here.
 */

expr:
   or_expr			{ $1 }
;

or_expr:
     xor_expr			{ $1 }
   | or_expr BARBAR xor_expr	{ E.BOP (pos (), $1, E.LOGOR, $3) }
;

xor_expr:
     and_expr			{ $1 }
   | xor_expr CARETCARET and_expr { E.BOP (pos (), $1, E.LOGXOR, $3) }
;

and_expr:
     bitor_expr			{ $1 }
   | and_expr AMPAMP bitor_expr { E.BOP (pos (), $1, E.LOGAND, $3) }
;

bitor_expr:
     bitxor_expr		{ $1 }
   | bitor_expr BAR bitxor_expr	{ E.BOP (pos (), $1, E.BITOR, $3) }
;

bitxor_expr:
     bitand_expr		{ $1 }
   | bitxor_expr CARET bitand_expr { E.BOP (pos (), $1, E.BITXOR, $3) }
;

bitand_expr:
     compare_expr		{ $1 }
   | bitand_expr AMP compare_expr { E.BOP (pos (), $1, E.BITAND, $3) }
;

compare_expr:
     shift_expr				{ $1 }
   | compare_expr EQEQ shift_expr	{ E.BOP (pos (), $1, E.EQ, $3) }
   | compare_expr BANGEQ shift_expr	{ E.BOP (pos (), $1, E.NEQ, $3) }
   | compare_expr LT shift_expr		{ E.BOP (pos (), $1, E.LT, $3) }
   | compare_expr GT shift_expr		{ E.BOP (pos (), $3, E.LT, $1) }
   | compare_expr LTEQ shift_expr	{ E.BOP (pos (), $1, E.LTEQ, $3) }
   | compare_expr GTEQ shift_expr	{ E.BOP (pos (), $3, E.LTEQ, $1) }
   | compare_expr FITS typename		{ E.FITS (pos (), $1, $3) }
;

shift_expr:
     add_expr			{ $1 }
   | shift_expr LTLT add_expr	{ E.BOP (pos (), $1, E.SHL, $3) }
   | shift_expr GTGT add_expr	{ E.BOP (pos (), $1, E.SHR, $3) }
;

add_expr:
     mul_expr			{ $1 }
   | add_expr PLUS mul_expr	{ E.BOP (pos (), $1, E.ADD, $3) }
   | add_expr MINUS mul_expr	{ E.BOP (pos (), $1, E.SUB, $3) }
   | add_expr PLUSPLUS mul_expr	{ E.BOP (pos (), $1, E.STRCAT, $3) }
;

mul_expr:
     prefix_expr		{ $1 }
   | mul_expr STAR prefix_expr	{ E.BOP (pos (), $1, E.MUL, $3) }
   | mul_expr SLASH prefix_expr	{ E.BOP (pos (), $1, E.DIV, $3) }
   | mul_expr PCT prefix_expr	{ E.BOP (pos (), $1, E.MOD, $3) }
;

prefix_expr:
     primary_expr		{ $1 }
   | PLUS prefix_expr		{ E.UOP (pos (), E.PLUS, $2) }
   | MINUS prefix_expr		{ E.UOP (pos (), E.NEG, $2) }
   | BANG prefix_expr		{ E.UOP (pos (), E.LOGNOT, $2) }
   | ORD LPAREN expr RPAREN	{ E.UOP (pos (), E.ORD, $3) }
   | CAST LPAREN castsequence RPAREN prefix_expr {
        let wrap (nt, ot) e =
	   E.CAST (pos (), nt, ot, e)
        in
        List.fold_right wrap $3 $5
     }
   | EVAL prefix_expr		{ E.UOP (pos (), E.EVAL, $2) }
   | CONSTANTP prefix_expr	{ E.UOP (pos (), E.CONSTP, $2) }
;

castsequence:
     typename LTEQ typename	{ [($1, $3)] }
   | typename LTEQ castsequence {
	match $3 with
	     [] -> Util.crash "langparse: empty cast sequence"
	   | (nt, ot) :: more -> ($1, nt) :: (nt, ot) :: more
     }
;

primary_expr:
     value			{ $1 }
   | IDENT			{ E.READVAR (pos (), $1) }
   | IDENT LPAREN arglist RPAREN { E.PACK (pos (), $1, $3) }
   | LPAREN expr RPAREN		{ $2 }
   | primary_expr COLONCOLON typename { E.ANNOTATE (pos (), $3, $1) } 
;

value:
     TRUE			{ E.BOOLCONSTANT (pos (), true) }
   | FALSE			{ E.BOOLCONSTANT (pos (), false) }
   | QSTRING			{ E.STRCONSTANT (pos (), $1) }
   | NUMBER			{ E.NUMCONSTANT (pos (), $1) }
;

arglist:
   exprlist			{ List.rev $1 }
;

exprlist: /* built in reverse order */
     expr			{ [$1] }
   | exprlist COMMA expr	{ $3 :: $1 }
;

%%

