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
module T = Modifiertree

let pos () = Pos.fromparser ()

%}

%token EOF
%token <int> NUMBER
%token <string> IDENT
/* reserved words */
%token EXPRESSION INT MODIFIER UINT
/* grouping punctuation */
%token LPAREN RPAREN
/* multicharacter punctuation */
%token COLONCOLON MINUSGT
/* single-character punctuation */
%token SEMIC

%type <Modifiertree.decl list> file

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
     MODIFIER IDENT COLONCOLON typespec MINUSGT typespec SEMIC {
	{ T.name=$2; T.definedat=pos (); T.argtype=$4; T.resulttype=$6; }
     }
;

typespec:
   basetype			{ $1 }
;

basetype:
     INT LPAREN NUMBER RPAREN	{ T.INT $3 }
   | UINT LPAREN NUMBER RPAREN	{ T.UINT $3 }
   | EXPRESSION basetype	{ T.EXPRTYPE $2 }
;

%%
