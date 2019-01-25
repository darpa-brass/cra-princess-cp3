(*
 * Copyright (c) 2016, 2017, 2018
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
 * XXX: note that this file is almost a carbon copy of deflex.mll. It
 * differs only in the list of reserved words and in which two-character
 * punctuation it recognizes. Ideally one would be able to share most of
 * it, if deflex.mll continues to exist; but that seems hard if more than
 * the keyword list is different.
 *)

(* prologue code *)
{
open Pos
open Lextools
open Hazardparse

let keywords = Types.stringmap_of_list [
   ("cast", CAST);
   ("go", GO);
   ("false", FALSE);
   ("field", FIELD);
   ("fits", FITS);
   ("hazard", HAZARD);
   ("in", IN);
   ("insnp", INSNP);
   ("mode", MODE);
   ("modifier", MODIFIER);
   ("notin", NOTIN);
   ("nullify", NULLIFY);
   ("stay", STAY);
   ("transfer", TRANSFER);
   ("true", TRUE);
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
   | '&' '&'		{ advance lexbuf; AMPAMP }
   | '!' '='		{ advance lexbuf; BANGEQ }
   | '|' '|'		{ advance lexbuf; BARBAR }
   | '^' '^'		{ advance lexbuf; CARETCARET }
   | ':' ':'		{ advance lexbuf; COLONCOLON }
   | '=' '='		{ advance lexbuf; EQEQ }
   | '>' '='		{ advance lexbuf; GTEQ }
   | '<' '='		{ advance lexbuf; LTEQ }
   | '<' '<'		{ advance lexbuf; LTLT }
   | '>' '>'		{ advance lexbuf; GTGT }
   | '-' '>'		{ advance lexbuf; RARROW }
   | '&'		{ advance lexbuf; AMP }
   | '!'		{ advance lexbuf; BANG }
   | '|'		{ advance lexbuf; BAR }
   | '^'		{ advance lexbuf; CARET }
   | ':'		{ advance lexbuf; COLON }
   | ','		{ advance lexbuf; COMMA }
   | '.'		{ advance lexbuf; DOT }
   | '='		{ advance lexbuf; EQ }
   | '>'		{ advance lexbuf; GT }
   | '<'		{ advance lexbuf; LT }
   | '-'		{ advance lexbuf; MINUS }
   | '%'		{ advance lexbuf; PCT }
   | '+'		{ advance lexbuf; PLUS }
   | '?'		{ advance lexbuf; QUES }
   | ';'		{ advance lexbuf; SEMIC }
   | '/'		{ advance lexbuf; SLASH }
   | '*'		{ advance lexbuf; STAR }
   | '~'		{ advance lexbuf; TILDE }
   | '('		{ advance lexbuf; LPAREN }
   | ')'		{ advance lexbuf; RPAREN }
   | '['		{ advance lexbuf; LBRACK }
   | ']'		{ advance lexbuf; RBRACK }
   | '{'		{ advance lexbuf; LBRACE }
   | '}'		{ advance lexbuf; RBRACE }
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
      | GO ->              "GO"
      | FALSE ->           "FALSE"
      | FIELD ->           "FIELD"
      | FITS ->            "FITS"
      | HAZARD ->          "HAZARD"
      | IN ->              "IN"
      | INSNP ->           "INSNP"
      | MODE ->            "MODE"
      | MODIFIER ->        "MODIFIER"
      | NOTIN ->           "NOTIN"
      | NULLIFY ->         "NULLIFY"
      | STAY ->            "STAY"
      | TRANSFER ->        "TRANSFER"
      | TRUE ->            "TRUE"
      | LBRACE ->          "LBRACE"
      | RBRACE ->          "RBRACE"
      | LBRACK ->          "LBRACK"
      | RBRACK ->          "RBRACK"
      | LPAREN ->          "LPAREN"
      | RPAREN ->          "RPAREN"
      | AMPAMP ->          "AMPAMP"
      | BANGEQ ->          "BANGEQ"
      | BARBAR ->          "BARBAR"
      | CARETCARET ->      "CARETCARET"
      | COLONCOLON ->      "COLONCOLON"
      | EQEQ ->            "EQEQ"
      | GTEQ ->            "GTEQ"
      | GTGT ->            "GTGT"
      | LTEQ ->            "LTEQ"
      | LTLT ->            "LTLT"
      | RARROW ->          "RARROW"
      | AMP ->             "AMP"
      | BANG ->            "BANG"
      | BAR ->             "BAR"
      | CARET ->           "CARET"
      | COLON ->           "COLON"
      | COMMA ->           "COMMA"
      | DOT ->             "DOT"
      | EQ ->              "EQ"
      | GT ->              "GT"
      | LT ->              "LT"
      | MINUS ->           "MINUS"
      | PCT ->             "PCT"
      | PLUS ->            "PLUS"
      | QUES ->            "QUES"
      | SEMIC ->           "SEMIC"
      | SLASH ->           "SLASH"
      | STAR ->            "STAR"
      | TILDE ->           "TILDE"

let iseof t =
   match t with
        EOF -> true
      | _ -> false

let read = read' base Hazardparse.file iseof dumpone Hazardcheck.check
}
