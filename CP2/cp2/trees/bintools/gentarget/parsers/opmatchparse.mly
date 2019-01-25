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
module T = Opmatchtree

let pos () = Pos.fromparser ()

let insn name (operandtags, multi) encodinginfo =
   let definedat = pos () in
   { T.name; T.definedat; T.operandtags; T.multi; T.encodinginfo; }

%}

%token EOF
%token WS
%token <int> NUMBER
%token <string> IDENT QSTRING
/* reserved words */
/* none */
/* grouping punctuation */
%token LPAREN RPAREN LBRACE RBRACE
/* multicharacter punctuation */
/* none */
/* single-character punctuation */
%token COMMA EQ PLUS
%token NL

%type <Opmatchtree.insn list> file

%start file

%%

file:
   optws optnewlines insns optnewlines EOF		{ List.rev $3 }
;

insns: /* built in reverse order */
     insn			{ [$1] }
   | insns newlines insn	{ $3 :: $1 }
;

insn:
     opcode					{ insn $1 ([], false) None }
   | opcode optws EQ optws encoding	{ insn $1 ([], false) (Some $5) }
   | opcode WS operands				{ insn $1 $3 None }
   | opcode WS operands EQ optws encoding	{ insn $1 $3 (Some $6) }
;

/* sparc64 has commas in opcode names... blargh */
/* thus opcode has to be a lexeme */
opcode:
     IDENT				{ $1 }
   | QSTRING				{ $1 }
   | opcode COMMA			{ $1 ^ "," }
   | opcode COMMA IDENT			{ $1 ^ "," ^ $3 }
;

encoding:
     IDENT optws					{ ($1, []) }
   | IDENT optws LPAREN optws RPAREN optws		{ ($1, []) }
   | IDENT optws LPAREN optws identlist RPAREN optws	{ ($1, List.rev $5) }
;

operands:
     operandlist					{ (List.rev $1, false)}
   | LBRACE optws operandlist RBRACE optws PLUS optws	{ (List.rev $3, true) }
;

operandlist: /* built in reverse order */
     operand				{ [$1] }
   | operandlist COMMA optws operand	{ $4 :: $1 }
;

operand:
   IDENT optws				{ (pos (), $1) }
;

/* XXX these pos () are suboptimal */
identlist: /* built in reverse order, with commas */
     IDENT optws				{ [(pos (), $1)] }
   | identlist COMMA optws IDENT optws		{ (pos (), $4) :: $1 }
;

optnewlines:
     /* nil */			{ () }
   | newlines			{ () }
;

newlines:
     NL optws			{ () }
   | newlines NL optws		{ () }
;

optws:
     /* nil */			{ () }
   | WS				{ () }

%%
