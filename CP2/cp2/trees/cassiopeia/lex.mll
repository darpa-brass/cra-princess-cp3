{
open Util
open Lexing
open Parse

module Bat = Batteries

exception SyntaxError of string

let get_pos lexbuf = Pos.mk
    lexbuf.lex_curr_p.pos_fname 
    lexbuf.lex_start_p.pos_lnum 
    lexbuf.lex_curr_p.pos_lnum 
    (lexbuf.lex_start_p.pos_cnum - lexbuf.lex_start_p.pos_bol)
    (lexbuf.lex_curr_p.pos_cnum - lexbuf.lex_curr_p.pos_bol)

let get_lex lb =
  Lexing.lexeme lb

let get_tok = get_lex

let bint_of_token lb =
  get_lex lb |>
  BI.of_string

let failwith msg = raise (SyntaxError (msg))

}

let cr='\013'
let nl='\010'
let eol=(cr nl|nl|cr)
let ws=('\012'|'\t'|' ')*
let digit=['0'-'9']
let hex=['0'-'9''A'-'F''a'-'f']
let bit=['0'-'1']
let id = ['A'-'Z''a'-'z''_']['\'''a'-'z''A'-'Z''0'-'9''_']*

rule main = parse
  | eol       { new_line lexbuf; main lexbuf }
  | ws+       { main lexbuf }
  | '('       { LPAREN }
  | ')'       { RPAREN }
  | '['       { LBRACKET }
  | ']'       { RBRACKET }
  | '{'       { LBRACE }
  | '}'       { RBRACE }
  | "&&"      { AMPAMP }
  | "||"      { PIPEPIPE }
  | "^^"      { CARETCARET }
  | "<-"      { LTMINUS }
  | "->"      { MINUSGT }
  | "<<"      { LTLT }
  | ">>"      { GTGT }
  | "=="      { EQEQ }
  | "!="      { BANGEQ }
  | "**"      { STARSTAR }
  | "..."     { DOTDOTDOT }
  | '.'       { DOT }
  | "^"       { CARET }
  | ';'       { SEMIC }
  | '?'       { QUES }
  | ':'       { COLON }
  | ','       { COMMA }
  | '+'       { PLUS }
  | '-'       { MINUS }
  | '*'       { STAR }
  | '/'       { SLASH }
  | '='       { EQ }
  | '<'       { LT }
  | "b<"      { BLT }
  | '>'       { GT }
  | '&'       { AMP }
  | '|'       { PIPE }
  | '!'       { BANG }
  | '~'       { TILDE }
  | "++"      { PLUSPLUS }
  | "armcc"   { ARMCC }
  | "bit"     { BIT }
  | "loc"     { LOC }
  | "bool"    { BOOL }
  | "int"     { INT }
  | "if"      { IF }
  | "then"    { THEN }
  | "else"    { ELSE }
  | "for"     { FOR }
  | "let"     { LET }
  | "in"      { IN }
  | "do"      { DO }
  | "err"     { ERR }
  | "assert"  { ASSERT }
  | "skip"    { SKIP }
  | "type"    { TYPE }
  | "letstate" { LETSTATE }
  | "def"     { DEF }
  | "defop"   { DEFOP }
  | "txt"     { TXT }
  | "sem"     { SEM }
  | "true"    { TRUE }
  | "false"   { FALSE }
  | "Mem"     { MEM
    (* Mem is capitalized to match ARM DDI arch manual *)
  }
  | "ghost"     { GHOST }
  | "machine" { MACHINE }
  | "block"   { BLOCK }
  | "pre"     { PRE }
  | "post"    { POST }
  | digit+    {
      DECNUM (bint_of_token lexbuf) }
  | '-'digit+ {
      let b = bint_of_token lexbuf |> BI.neg in
      DECNUM (b) }
  | "0x"hex+  {
      let tok = get_tok lexbuf in
      HEXNUM (Bits.of_string tok) }
  | "0b"bit+  {
      let tok = get_tok lexbuf in
      BITNUM (Bits.of_string tok) }
  (* TODO some IDs may be dangerous in translation to rosette, e.g. define *)
  | id        { ID (get_lex lexbuf) }
  | "(*"      { comment 1 lexbuf }
  | '"'       {
    let fresh = Buffer.create 10 in
    lexbuf |>
    read_string fresh }
  | _         {
    let tok = get_tok lexbuf in
    let pos = get_pos lexbuf |> Pos.string_of in
    let msg = "invalid token: " ++ tok ++ "@" ++ pos in
    failwith msg }
  | eof       { EOF }

and comment lvl = parse
| "(*"  { comment (lvl + 1) lexbuf }
| eol   { new_line lexbuf; comment lvl lexbuf }
| "*)"  { if lvl == 1 then main lexbuf else comment (lvl-1) lexbuf }
| eof   { failwith "unterminated comment." }
| _     { comment lvl lexbuf }

(* proudly copy and pasted from Real World OCaml 1st ed 
 * THANKS YARON. *)
and read_string buf = parse
  | '"'       { STRINGLIT (Buffer.contents buf) }
  | '\\' '/'  { Buffer.add_char buf '/'; read_string buf lexbuf }
  | '\\' '\\' { Buffer.add_char buf '\\'; read_string buf lexbuf }
  | '\\' 'b'  { Buffer.add_char buf '\b'; read_string buf lexbuf }
  | '\\' 'f'  { Buffer.add_char buf '\012'; read_string buf lexbuf }
  | '\\' 'n'  { Buffer.add_char buf '\n'; read_string buf lexbuf }
  | '\\' 'r'  { Buffer.add_char buf '\r'; read_string buf lexbuf }
  | '\\' 't'  { Buffer.add_char buf '\t'; read_string buf lexbuf }
  | [^ '"' '\\']+
    { Buffer.add_string buf (Lexing.lexeme lexbuf);
      read_string buf lexbuf
    }
  | _ { failwith ("Illegal string character: " ^ Lexing.lexeme lexbuf) }
  | eof { failwith "String is not terminated" }

{

let parse_with parse file =
  let ch = open_in file in
  let lexbuf = Lexing.from_channel ch in
  let pos = { lexbuf.lex_curr_p with pos_fname = file; } in
  let lexbuf = { lexbuf with lex_curr_p = pos; } in
  try
     parse main lexbuf
  with Parse.Error ->
    let msg = get_pos lexbuf |> Pos.string_of in
      failwith (msg ++ ": Parse error")

let read file =
  parse_with Parse.file file;

}
