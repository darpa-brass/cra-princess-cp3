%{
open Util
open Ast

open Lexing

module Bat = Batteries
module P   = Printf
module A   = Ast
module BI  = BatBig_int
module B   = Bits
module U   = Util

let pos_of startp endp =
  Pos.mk startp.pos_fname
    startp.pos_lnum endp.pos_lnum
    (startp.pos_cnum - startp.pos_bol)
    (endp.pos_cnum - endp.pos_bol)

let cnt  = ref 0
let next () = incr cnt; !cnt

let fresh_id () =
  "tmp" ++. (next ())

%}

%token <Util.bint> DECNUM
%token <Bits.t> HEXNUM
%token <Bits.t> BITNUM
%token <string> ID 
%token <string> STRINGLIT
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token AMPAMP PIPEPIPE CARETCARET LTMINUS MINUSGT LTLT GTGT EQEQ BANGEQ STARSTAR DOTDOTDOT
%token SEMIC QUES COLON COMMA PLUS MINUS STAR SLASH EQ BLT LT GT AMP PIPE CARET BANG TILDE
%token BIT LOC BOOL INT DOT PLUSPLUS ARMCC
%token IF THEN ELSE FOR LET IN DO ASSERT ERR SKIP TYPE LETSTATE DEF DEFS DEFOP TXT SEM
%token TRUE FALSE MEM GHOST
%token MACHINE BLOCK PRE POST
%token EOF

%nonassoc THEN IN DO
%nonassoc ELSE
%right SEMIC
%right PLUSPLUS

%type <Ast.t> file
%type <(Pos.t * Ast.decl) list> casp_file
%type <(Pos.t * Ast.inst) list> prog_file
%type <(string list * Ast.expr * Ast.expr)> spec_file

%start file casp_file prog_file spec_file

%%

file :
    MACHINE i=ID ds=casp_file EOF { Casp ds }
  | BLOCK   i=ID is=prog_file EOF { Prog is }
;

casp_file :
  ds=decls EOF { ds }
;

decls :
    /* nil */       { [] }
  | ds=decls d=decl { ds @ [d] }
;

decl :
    TYPE i=ID EQ t=typ {
      let p = pos_of $startpos $endpos in
      (p, DeclType (i, t))
    }
  | LETSTATE LPAREN i=ID COLON t=typ RPAREN EQ h=HEXNUM
  | LETSTATE i=ID COLON t=typ EQ h=HEXNUM {
      let p = pos_of $startpos $endpos in
      (p, DeclLetstate (i, t, h))
    }
  | LETSTATE LPAREN i=ID COLON t=typ RPAREN EQ b=BITNUM
  | LETSTATE i=ID COLON t=typ EQ b=BITNUM {
      let p = pos_of $startpos $endpos in
      (p, DeclLetstate (i, t, b))
    }
  | LET LPAREN i=ID COLON t=typ RPAREN EQ e=expr
  | LET i=ID COLON t=typ EQ e=expr {
      let p = pos_of $startpos $endpos in
      (p, DeclLet (i, t, e))
    }
  | DEF i=ID ps=params MINUSGT t=typ EQ e=expr {
      let p = pos_of $startpos $endpos in
      (p, DeclDef (i, ps, t, e))
    }
  | DEFS i=ID ps=params EQ s=stmt {
      let p = pos_of $startpos $endpos in
      (p, DeclDefs (i, ps, s))
    }
  | DEFOP i=ID ps=params LBRACE b=body RBRACE {
      let p = pos_of $startpos $endpos in
      let (txt, sem) = b in
      (p, DeclDefop (i, ps, txt, sem))
    }
;

params :
    /* nil */ { [] }
  | ps=params p=param { ps @ [p] }
;

param :
    LPAREN i=ID COLON t=typ RPAREN 
  | i=ID COLON t=typ {
      (i, t)
    }
;

body :
    TXT EQ se=string_expr COMMA SEM EQ LBRACKET s=stmt RBRACKET
     { (se, s) }
  | SEM EQ LBRACKET s=stmt RBRACKET
     { ([], s) }
  /* MK: what is this rule for? ghost ops? */
;

string_expr :
    s=STRINGLIT                           
      { [SLiteral(s)] }
  | s=STRINGLIT DOT ARMCC LPAREN i=ID RPAREN
      { [SArmCond(s,i)] }
  | i=ID DOT TXT
      { [SField(i)] }
  | a=atomic
      { [SAtomic(a)] }
  | s1=string_expr PLUSPLUS s2=string_expr
      { s1 @ s2 }
;

atomic :
    c=DECNUM {
      Int (c)
    }
  | h=HEXNUM {
      Bit (h)
    }
  | b=BITNUM {
      Bit (b)
    }
  | TRUE {
      True
    }
  | FALSE {
      False
    }
  | i=ID {
      Id (i)
    }
;

stmt :
  | SKIP {
      Skip
    }
  | ERR {
      Err
    }
  | ASSERT e=expr {
      Assert (e)
    }
  | s1=stmt SEMIC s2=stmt {
      Seq (s1, s2)
    }
  | MEM LBRACKET a1=atomic COMMA a2=atomic RBRACKET LTMINUS e=expr {
      Store (a1, a2, e)
    }
  | STAR i=ID LTMINUS e=expr {
      Assign (i, e)
    }
  | FOR i=ID IN LBRACKET a1=atomic DOTDOTDOT a2=atomic RBRACKET DO s=stmt {
      For (i, a1, a2, s)
    }
  | i=ID LPAREN aa=atomic_args RPAREN {
      Call (i, aa)
    }
  | LET LPAREN i=ID COLON t=typ RPAREN EQ e=expr IN s=stmt
  | LET i=ID COLON t=typ EQ e=expr IN s=stmt {
      LetS (i, t, e, s)
    }
  | IF i=ID THEN s=stmt {
      IfS (i, s, Skip)
    }
  | IF i=ID THEN s1=stmt ELSE s2=stmt {
      IfS (i, s1, s2)
    }
  | LPAREN s=stmt RPAREN { s }
;

expr :
  | a=atomic {
      Atomic (a)
    }
  | STAR i=ID {
      Deref (i)
    }
  | MEM LBRACKET a1=atomic COMMA a2=atomic RBRACKET {
      Load (a1, a2)
    }
  | i=ID LBRACKET a=atomic RBRACKET {
      Index (i, a)
    }
  | i=ID LBRACKET a1=atomic COLON a2=atomic RBRACKET {
      Slice (i, a1, a2)
    }
  | op=unop a=atomic {
      Unop (op, a)
    }
  | a1=atomic b=binop a2=atomic {
      Binop (a1, b, a2)
    }
  | i=ID QUES a1=atomic COLON a2=atomic {
      IfE (i, Atomic a1, Atomic a2)
    }
  | i=ID LPAREN aa=atomic_args RPAREN {
      (*let _ = if aa = [] then
        failwith ("Application of " ++ i ++ " without args") in*)
      App (i, aa)
    }
  | LET i=ID COLON t=typ EQ e1=expr IN e2=expr {
      LetE (i, t, e1, e2)
    }
  | IF i=ID THEN e1=expr ELSE e2=expr {
      IfE (i, e1, e2)
    }
  | LPAREN e=expr RPAREN { e }
;

atomic_args :
    /* nil */                     { [] }
  | a=atomic                      { [a] }
  | aa=atomic_args COMMA a=atomic { aa @ [a] }
;

unop :
    MINUS { Neg }
  | BANG  { LogNot }
  | TILDE { BitNot }
;

binop :
    PLUS       { Add }
  | MINUS      { Sub }
  | STAR       { Mul }
  | SLASH      { Div }
  | STARSTAR   { Pow }
  | EQEQ       { Eq }
  | BANGEQ     { Neq }
  | BLT        { BLt }
  | LT         { Lt }
  | GT         { Gt }
  | LTLT       { LShift }
  | GTGT       { RShift }
  | AMPAMP     { LogAnd }
  | PIPEPIPE   { LogOr }
  | CARETCARET { LogXor }
  | AMP        { BitAnd }
  | PIPE       { BitOr }
  | CARET      { BitXor }
;

typ :
    n=DECNUM BIT { BitvecType (BI.to_int n) }
  | s=ID { AliasType (s) }
  | n=DECNUM BIT LOC { BitvecLocType (BI.to_int n) }
  | i=ID LOC { AliasLocType (i) }
  | BOOL { BoolType }
  | INT  { IntType }
;

prog_file :
    is=insts EOF { is }
;

insts :
    /* nil */                     { [] }
  | is=insts LPAREN i=inst RPAREN { is @ [i] }
;

inst :
    i=ID aa=inst_args {
      let p = pos_of $startpos $endpos in
      (p, (i, aa)) }
;

inst_args :
    /* nil */             { [] }
  | aa=inst_args a=atomic { aa @ [a] }
;

spec_file :
    gg=spec_ghosts PRE COLON e1=expr POST COLON e2=expr EOF { (gg, e1, e2) }
;

spec_ghosts :
    /* nil */             { [] }
  | gg=spec_ghosts GHOST i=ID { gg @ [i] }
;
