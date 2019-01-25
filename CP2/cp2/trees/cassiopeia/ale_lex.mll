{
open Lexing
open Ale_parse

module Bat = Batteries

let (++) = (^)

let get_pos lexbuf = Ale_pos.mk
    lexbuf.lex_curr_p.pos_fname 
    lexbuf.lex_start_p.pos_lnum 
    lexbuf.lex_curr_p.pos_lnum 
    (lexbuf.lex_start_p.pos_cnum - lexbuf.lex_start_p.pos_bol)
    (lexbuf.lex_curr_p.pos_cnum - lexbuf.lex_curr_p.pos_bol)

let get_lex lb =
  Lexing.lexeme lb

let get_tok = get_lex

}

let cr='\013'
let nl='\010'
let eol=(cr nl|nl|cr)
let ws=('\012'|'\t'|' ')*
let digit=['0'-'9']
let hex=['0'-'9''A'-'F''a'-'f']
let bit=['0'-'1']
let id = ['A'-'Z''a'-'z''_''.']['\'''a'-'z''A'-'Z''0'-'9''_']*


rule main = parse
  | eol       { new_line lexbuf; main lexbuf }
  | ws+       { main lexbuf }
  | '('       { LPAREN }
  | ')'       { RPAREN }
  | '{'       { LBRACE }
  | '}'       { RBRACE }
  | '['       { LBRACKET }
  | ']'       { RBRACKET }
  | ':'       { COLON }
  | '.'       { DOT }
  | ','       { COMMA }
  | '/'       { FSLASH }
  | '='       { EQ }
  | "&&"      { CONJUNCT }
  | "||"      { DISJUNCT }
  | '~'       { NEG }
  | "->"      { RIGHTARROW }
  | "<-"      { LEFTARROW }
  | "bind"    { BIND }
  | "abstract"{ ABSTRACT }
  | "type"    { TYPE }
  | "bool"    { BOOL }
  | "boolean" { BOOL }
  | "fun"     { FUNCTION }
  | "pred"    { PREDICATE }
  | "axiom"   { AXIOM }
  | "block"   { BLOCK }
  | "pre"    { PRE }
  | "post"   { POST }
  | "forall"  { FORALL }
  | "exists"  { EXISTS }
  | "true"    { TRUE }
  | "false"   { FALSE }
  | "bit"     { BIT }
  | "loc"     { LOC }
  | "ghost"   { GHOST }
  | "machinetype" { MACHTYPE }
  | digit+    { CONST (int_of_string (get_tok lexbuf)) } 
  | id        { ID (get_tok lexbuf) }
  | eof       { EOF }
  | "(*"      { comment 1 lexbuf }
  | _         {
    let tok = get_tok lexbuf in
    let pos = get_pos lexbuf |> Ale_pos.string_of in
    let msg = "invalid token: " ++ tok ++ "@" ++ pos in
    failwith msg
  } 

and comment lvl = parse
| "(*"  { comment (lvl + 1) lexbuf }
| eol   { new_line lexbuf; comment lvl lexbuf }
| "*)"  { if lvl == 1 then main lexbuf else comment lvl lexbuf }
| _     { comment lvl lexbuf }

{

let read file =
  let ch = open_in file in
  let lexbuf = Lexing.from_channel ch in
  let pos = { lexbuf.lex_curr_p with pos_fname = file; } in
  let lexbuf = { lexbuf with lex_curr_p = pos; } in
  try
     Ale_parse.file main lexbuf
  with Ale_parse.Error ->
    let msg = get_pos lexbuf |> Ale_pos.string_of in
     failwith (msg ++ ": Parse error");

}
