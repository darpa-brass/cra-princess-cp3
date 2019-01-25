%{
(*
 * Copyright (c) 2017, 2018
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
module T = Basetree

let pos () = Pos.fromparser ()

let mkenum name (width, body) = T.ENUMTYPE (pos (), name, width, body)
let mkwrap name (ty, fmt)     = T.WRAPTYPE (pos (), name, ty, fmt)
let mkcompound name members   =
   T.COMPOUNDTYPE (pos (), name, members)

%}

%token EOF
%token <int> NUMBER
%token <string> IDENT QSTRING
/* reserved words */
%token ENUM EXPRESSION OPERANDTAG REGCLASS SHORTNAME TYPE WITH WRAP
/* grouping punctuation */
%token LBRACE RBRACE /*LBRACK RBRACK*/ LPAREN RPAREN
/* multicharacter punctuation */
%token COLONCOLON
/* single-character punctuation */
%token COMMA EQ SEMIC

%type <Basetree.decl list> file

%start file

%%

file:
   decls EOF			{ List.rev $1 }
;

decls: /* built in reverse order */
     /* nil */			{ [] }
   | decls decl			{ $2 :: $1 }
;

decl:
     TYPE IDENT EQ enumspec SEMIC	{ mkenum $2 $4 }
   | TYPE IDENT EQ wrapspec SEMIC	{ mkwrap $2 $4 }
   | TYPE IDENT EQ compoundspec SEMIC	{ mkcompound $2 $4 }
   | OPERANDTAG IDENT COLONCOLON typename SEMIC	{ T.OPERANDTAG (pos (), $2, $4) }
   | SHORTNAME IDENT EQ IDENT SEMIC	{ T.SHORTNAME (pos (), $2, $4) }
;

enumspec:
   ENUM LPAREN NUMBER RPAREN LBRACE enumbody RBRACE { ($3, $6) }
;

enumbody:
     enumerators			{ List.rev $1 }
   | enumerators COMMA			{ List.rev $1 }
;

enumerators: /* built in reverse order */ 
     enumerator				{ [$1] } 
   | enumerators COMMA enumerator	{ $3 :: $1 } 
;

enumerator:
     IDENT				{ (pos (), $1, None) }
   | IDENT EQ NUMBER			{ (pos (), $1, Some $3) }
;

wrapspec:
   WRAP typename WITH QSTRING		{ ($2, $4) }
;

compoundspec:
   LPAREN compoundbody RPAREN		{ List.rev $2 }
;

compoundbody: /* built in reverse order */
     typename				{ [(pos (), $1)] }
   | compoundbody COMMA typename	{ (pos (), $3) :: $1 }
;

typename:
     IDENT				{ TT.PLAINTYPE (pos (), $1) }
   | IDENT LPAREN NUMBER RPAREN		{ TT.WIDTHTYPE (pos (), $1, $3) }
   | EXPRESSION typename		{ TT.EXPRTYPE (pos (), $2) }
;

%%

