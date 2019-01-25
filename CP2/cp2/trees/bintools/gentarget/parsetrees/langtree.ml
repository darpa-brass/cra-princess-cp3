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

(*
 * The language.def file defines, besides some simple properties,
 * three kinds of things:
 *    keywords (literal, symbolic name, type)
 *    matches (list of subtokens, symbolic name, type)
 *    operands (expression pattern, name)
 *
 * It also produces a map from tokens to their token types; this is
 * the type of the value carried with the token, if any.
 *)

(* source position *)
type pos = Pos.pos

(* types *)
type typename = Typetree.typename

(* expressions *)
type expr = Exprtree.expr

(* patterns for token values *)
type tokvalpattern =
     P_BINDER of (pos * typename * string)
   | P_CONSTANT_S of (pos * string)
   | P_CONSTANT_N of (pos * int)

type tokenpattern = TOKENPAT of pos * string * tokvalpattern option
type tokenexpr = TOKENEXPR of pos * string * expr option

type kwdecl = KWDECL of pos * string * tokenexpr
type matchdecl = MATCHDECL of pos * tokenpattern list * tokenexpr

type exprpattern = 
     XP_TOKEN of pos * tokenpattern
   | XP_EXPR of pos * tokenpattern list * tokvalpattern option
   | XP_EXPRANY of pos * tokvalpattern option

                             (* patterns          guard       tagname tagval *)
type tagrule = TAGRULE of pos * exprpattern list * expr * pos * string * expr

type properties = {
   linecomments: (pos * string) list;
   blockcomments: (pos * bool(*nest*) * string * string) list;
   letters: string list;
   subletters: string list;
   tokens: (pos * typename * bool (*istarget*) ) Types.StringMap.t;
   keywords: kwdecl list;
   matches: matchdecl list;
   separators: (pos * string) list;
   tagrules: tagrule list;
}


(* The builtin token names. This should match token.h in the assembler. *)
let stdtokens = Types.stringmap_of_list [
	("IDENT",    Typetree.PLAINTYPE (Pos.builtin, "string"));
	("NUMBER",   Typetree.PLAINTYPE (Pos.builtin, "number"));
	("STRING",   Typetree.PLAINTYPE (Pos.builtin, "string"));
	("MODIFIER", Typetree.PLAINTYPE (Pos.builtin, "string"));
	("LPAREN",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("RPAREN",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("LBRACK",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("RBRACK",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("LBRACE",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("RBRACE",   Typetree.PLAINTYPE (Pos.builtin, "_"));
	("BANG",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("HASH",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("DOL",      Typetree.PLAINTYPE (Pos.builtin, "_"));
	("PCT",      Typetree.PLAINTYPE (Pos.builtin, "_"));
	("AMP",      Typetree.PLAINTYPE (Pos.builtin, "_"));
	("STAR",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("PLUS",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("COMMA",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("MINUS",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("SLASH",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("COLON",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("SEMIC",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("LT",       Typetree.PLAINTYPE (Pos.builtin, "_"));
	("LTLT",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("EQ",       Typetree.PLAINTYPE (Pos.builtin, "_"));
	("GT",       Typetree.PLAINTYPE (Pos.builtin, "_"));
	("GTGT",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("QUES",     Typetree.PLAINTYPE (Pos.builtin, "_"));
	("AT",       Typetree.PLAINTYPE (Pos.builtin, "_"));
	("CARET",    Typetree.PLAINTYPE (Pos.builtin, "_"));
	("BAR",      Typetree.PLAINTYPE (Pos.builtin, "_"));
	("TILDE",    Typetree.PLAINTYPE (Pos.builtin, "_"));
]
