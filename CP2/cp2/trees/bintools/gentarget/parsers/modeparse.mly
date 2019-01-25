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
module T = Modetree

let pos () = Pos.fromparser ()

let mkmode name modetype =
   let definedat = pos () in
   { T.definedat; T.name; T.modetype; }

%}

%token EOF
%token <string> IDENT
/* reserved words */
%token MODE OFF ON UNSUPPORTED
/* grouping punctuation (none) */
/* multicharacter punctuation (none) */
/* single-character punctuation */
%token COLON SEMIC

%type <Modetree.mode list> file
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
     MODE IDENT COLON modetype SEMIC	{ mkmode $2 $4 }
;

modetype:
     ON				{ T.DEFAULT_ON }
   | OFF			{ T.DEFAULT_OFF }
   | UNSUPPORTED		{ T.UNSUPPORTED }
;
