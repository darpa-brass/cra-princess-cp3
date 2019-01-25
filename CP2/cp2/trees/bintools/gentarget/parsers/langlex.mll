(*
 * Copyright (c) 2016, 2018
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

(* prologue code *)
{
open Pos
open Lextools
open Langparse

let keywords = Types.stringmap_of_list [
   ("cast", CAST);
   ("constantp", CONSTANTP);
   ("eval", EVAL);
   ("expression", EXPRESSION);
   ("fits", FITS);
   ("ord", ORD);
   ("false", FALSE);
   ("true", TRUE);

   ("comments", COMMENTS);
   ("line", LINE);
   ("nest", NEST);
   ("flat", FLAT);

   ("characters", CHARACTERS);
   ("charset", CHARSET);
   ("letter", LETTER);
   ("subletter", SUBLETTER);

   ("tokens", TOKENS);
   ("keywords", KEYWORDS);
   ("match", MATCH);

   ("syntax", SYNTAX);
   ("separator", SEPARATOR);

   ("tagrules", TAGRULES);
]
let doident = doident' keywords (fun x -> IDENT x)

(* end of prologue code *)
}

(* common patterns *)

let ws = [' ' '\t']
let digit = ['0'-'9']
let letter = ['a'-'z' 'A'-'Z' '_']
let alnum = ['0'-'9' 'a'-'z' 'A'-'Z' '_']

(* states *)
rule base = parse
     ws+		{ advance lexbuf; base lexbuf }
   | '\n'		{ nl lexbuf; base lexbuf }
   | '#' 		{ comment lexbuf; base lexbuf }
   | digit alnum*	{ NUMBER (tval' lexbuf int_of_string) }
   | '"' 		{ startstring lexbuf; strconst lexbuf }
   | letter alnum*	{ doident (tval lexbuf) }
   | '<' '='		{ advance lexbuf; LTEQ }
   | '<' '<'		{ advance lexbuf; LTLT }
   | '>' '='		{ advance lexbuf; GTEQ }
   | '>' '>'		{ advance lexbuf; GTGT }
   | '.' '.'		{ advance lexbuf; DOTDOT }
   | '&' '&'		{ advance lexbuf; AMPAMP }
   | '|' '|'		{ advance lexbuf; BARBAR }
   | '^' '^'		{ advance lexbuf; CARETCARET }
   | ':' ':'		{ advance lexbuf; COLONCOLON }
   | '=' '='		{ advance lexbuf; EQEQ }
   | '=' '>'		{ advance lexbuf; EQGT }
   | '!' '='		{ advance lexbuf; BANGEQ }
   | '+' '+'		{ advance lexbuf; PLUSPLUS }
   | '&'		{ advance lexbuf; AMP }
   | '!'		{ advance lexbuf; BANG }
   | '|'		{ advance lexbuf; BAR }
   | '^'		{ advance lexbuf; CARET }
   | ','		{ advance lexbuf; COMMA }
   | '='		{ advance lexbuf; EQ }
   | '>'		{ advance lexbuf; GT }
   | '<'		{ advance lexbuf; LT }
   | '-'		{ advance lexbuf; MINUS }
   | '%'		{ advance lexbuf; PCT }
   | '+'		{ advance lexbuf; PLUS }
   | '/'		{ advance lexbuf; SLASH }
   | '*'		{ advance lexbuf; STAR }
   | ';'		{ advance lexbuf; SEMIC }
   | '('		{ advance lexbuf; LPAREN }
   | ')'		{ advance lexbuf; RPAREN }
   | '{'		{ advance lexbuf; LBRACE }
   | '}'		{ advance lexbuf; RBRACE }
   | '['		{ advance lexbuf; LBRACK }
   | ']'		{ advance lexbuf; RBRACK }
   | _			{ badchar (posval lexbuf); base lexbuf }
   | eof		{ EOF }

and strconst = parse
     [ ^ '"' '\n' ]+	{ addstring (tval lexbuf); strconst lexbuf }
   | '\\' '"'		{ addchar '"'; advance lexbuf; strconst lexbuf }
   | '"'		{ advance lexbuf; QSTRING (getstring ()) }  (* done *)
   | '\n'		{ badstring (pos lexbuf); QSTRING (getstring ())}

(* this needs to be its own state to defeat the longest-match rule *)
and comment = parse
     [ ^ '\n' ]* '\n'	{ nl lexbuf; }

(* trailer code *)
{

let dumpone t =
   match t with
        EOF ->             "EOF"
      | NUMBER n ->        ("NUMBER " ^ string_of_int n)
      | QSTRING s ->       ("QSTRING " ^ s)
      | IDENT x ->         ("IDENT " ^ x)
      | CAST ->            "CAST"
      | EXPRESSION ->      "EXPRESSION"
      | FALSE ->           "FALSE"
      | TRUE ->            "TRUE"
      | COMMENTS ->        "COMMENTS"
      | CONSTANTP ->       "CONSTANTP"
      | EVAL ->            "EVAL"
      | FITS ->            "FITS"
      | ORD ->             "ORD"
      | LINE ->            "LINE"
      | FLAT ->            "FLAT"
      | NEST ->            "NEST"
      | CHARACTERS ->      "CHARACTERS"
      | CHARSET ->         "CHARSET"
      | LETTER ->          "LETTER"
      | SUBLETTER ->       "SUBLETTER"
      | TOKENS ->          "TOKENS"
      | KEYWORDS ->        "KEYWORDS"
      | MATCH ->           "MATCH"
      | SYNTAX ->          "SYNTAX"
      | SEPARATOR ->       "SEPARATOR"
      | TAGRULES ->        "TAGRULES"
      | LBRACK ->          "LBRACK"
      | RBRACK ->          "RBRACK"
      | LBRACE ->          "LBRACE"
      | RBRACE ->          "RBRACE"
      | LPAREN ->          "LPAREN"
      | RPAREN ->          "RPAREN"
      | AMP ->             "AMP"
      | AMPAMP ->          "AMPAMP"
      | BANG ->            "BANG"
      | BANGEQ ->          "BANGEQ"
      | BAR ->             "BAR"
      | BARBAR ->          "BARBAR"
      | CARET ->           "CARET"
      | CARETCARET ->      "CARETCARET"
      | COLONCOLON ->      "COLONCOLON"
      | COMMA ->           "COMMA"
      | DOTDOT ->          "DOTDOT"
      | EQ ->              "EQ"
      | EQEQ ->            "EQEQ"
      | EQGT ->            "EQGT"
      | GT ->              "GT"
      | GTEQ ->            "GTEQ"
      | GTGT ->            "GTGT"
      | LT ->              "LT"
      | LTEQ ->            "LTEQ"
      | LTLT ->            "LTLT"
      | MINUS ->           "MINUS"
      | PCT ->             "PCT"
      | PLUS ->            "PLUS"
      | PLUSPLUS ->        "PLUSPLUS"
      | SEMIC ->           "SEMIC"
      | SLASH ->           "SLASH"
      | STAR ->            "STAR"

let iseof t =
   match t with
        EOF -> true
      | _ -> false

let read = read' base Langparse.file iseof dumpone Langcheck.check
}
