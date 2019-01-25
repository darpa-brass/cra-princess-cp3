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

open Pos


(* positioning and text/value extraction *)

let curfile = ref ""
let curline = ref 0
let curcol = ref 0

let nl lexbuf =
   Lexing.new_line lexbuf;
   curline := !curline + 1;
   curcol := 1

let advance lexbuf =
   let len = Lexing.lexeme_end lexbuf - Lexing.lexeme_start lexbuf in
   curcol := !curcol + len

let getpos () =
   let l = !curline in
   let c = !curcol in
   { file = !curfile; startline=l; startcolumn=c; endline=l; endcolumn=c; }

let pos lexbuf =
   let ret = getpos () in
   advance lexbuf;
   ret

let posval lexbuf =
   let ret = getpos () in
   advance lexbuf;
   (ret, Lexing.lexeme lexbuf)

let tval' lexbuf f =
   advance lexbuf;
   f (Lexing.lexeme lexbuf)

let tval lexbuf =
   advance lexbuf;
   Lexing.lexeme lexbuf

let setpathname lexbuf pathname =
   let lp = { lexbuf.Lexing.lex_curr_p with Lexing.pos_fname = pathname; } in
   lexbuf.Lexing.lex_curr_p <- lp;
   lexbuf


(* string accumulation buffer *)

let stringdata = ref (Buffer.create 64)
let stringstart = ref Pos.nowhere
let startstring lexbuf =
   Buffer.clear !stringdata;
   stringstart := pos lexbuf
let addstring s =
   Buffer.add_string !stringdata s
let addchar c =
   addstring (String.make 1 c)
let getstring () =
   let s = Buffer.contents !stringdata in
(*
   let p0 = !stringstart in 
   { pos = p0; x = s; }
*)
   s


(* identifiers and keywords *)

let doident' keywords mkident tval =
   try
      (Types.StringMap.find tval keywords)
   with Not_found ->
      mkident tval

(* for invalid input *)

let commentstart = ref Pos.nowhere

let badchar (pos, tval) =
   let postxt = Pos.string_of_pos pos in
   Util.say (postxt ^ ": Invalid input character " ^ tval);
   Util.fail ()

let badstring pos =
   let postxt = Pos.string_of_pos pos in
   let postxt2 = Pos.string_of_pos !stringstart in
   Util.say (postxt ^ ": Unterminated quoted constant");
   Util.say (postxt2 ^ ": Constant began here");
   Util.fail ()

let startcomment lexbuf =
   commentstart := pos lexbuf

let badcomment pos =
   let postxt = Pos.string_of_pos pos in
   let postxt2 = Pos.string_of_pos !commentstart in
   Util.say (postxt ^ ": Unterminated comment");
   Util.say (postxt2 ^ ": Comment began here");
   Util.fail ()

(* dump support *)

let rec dump' iseof dumpone f b =
   let t = f b in
   if iseof t then ()
   else begin
(*
      let (pos, txt) = dumpone t in
      print_string (Pos.string_of_pos pos ^ " " ^ txt);
*)
      let txt = dumpone t in
      print_string txt;
      print_newline ();
      dump' iseof dumpone f b
   end

(* toplevel *)

let read' base mkparser iseof dumpone check pathname =
   let dump f b = dump' iseof dumpone f b in
   let _ = dump in (* silence unused warning *)

   curfile := pathname;
   curline := 1;
   curcol := 1;
   let channel = open_in pathname in
   let lexbuf = setpathname (Lexing.from_channel channel) pathname in
   let lexer = base in
   let parser = mkparser lexer in
   try
      (*dump lexer lexbuf;*)
      let decls = parser lexbuf in
      check decls
   with Parsing.Parse_error ->
      let strings = [!curfile; string_of_int !curline; string_of_int !curcol]
      in
      let postxt = String.concat ":" strings in
      let msg = postxt ^ ": Parse error" in
      Util.say msg;
      Util.die ()
