%{
open Lexing 

module Bat = Batteries
module A   = Ale_ast


let mk_bit = A.Bit
let mk_loc = A.Loc
let mk_ghost = A.Ghost
let mk_true  = A.True
let mk_false = A.False
let mk_bool  = A.Bool

let mk_term t = A.Term (t)

let mk_macht = function
  | A.Bit -> A.MachType (A.Bit)
  | A.Loc -> A.MachType (A.Loc)

let mk_abst i = A.AbsType (i)
let mk_aliast _ i2 = A.AbsType (i2)
(* let mk_funt = .. *)

let mk_bind_term i    = A.Name (i)
let mk_fapp_term i tt = A.FApp (i, tt)

let mk_bit_binder i = (i, mk_bit)
let mk_loc_binder i = (i, mk_loc)
let mk_ghost_binder i = (i, mk_ghost)
 
let mk_neg      p        = A.Neg p
let mk_conjunct p1 p2    = A.Conjunct (p1, p2)
let mk_disjunct p1 p2    = A.Disjunct (p1, p2)
let mk_eq       p1 p2    = A.Compare (A.Eq, p1, p2)
let mk_implication p1 p2 = A.Implies (p1, p2)
let mk_papp p tt         = A.PApp (p, tt)

let mk_block i p1 p2 = (i, p1, p2)
let mk_block_pr i (s1, s2) = mk_block i s1 s2
let mk_spec s1 s2 = (s1, s2)

let mk_subst a1 a2 p = A.Subst ((a1, a2), p)

let mk_axiom ids p = A.Forall (ids, p)

let mk_arg i t =
  (i, t)

let mk_pred i ta =
  (i, ta)

let mk_fun i ta rt =
  (i, ta, rt)

let mk_ale ts bs ps fs xs bls =
  (ts, bs, ps, fs, xs, bls)

%}

%token <string> ID
%token <int> CONST
%token TRUE FALSE EOF LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA DOT COLON FSLASH
%token FORALL EXISTS AXIOM PREDICATE FUNCTION
%token BLOCK PRE POST MACHTYPE TYPE ABSTRACT BIT LOC BOOL GHOST LEFTARROW
%token CONJUNCT DISJUNCT NEG EQ RIGHTARROW BIND

%left RIGHTARROW
%left DISJUNCT
%left CONJUNCT
%nonassoc NEG

%start <Ale_ast.t> file

%%

file :
    /* nil */   EOF
    { mk_ale [] [] [] [] [] [] }
  | ts=types bs=binders ps=preds fs=funs xs=axioms bls=blocks EOF
    { mk_ale ts bs ps fs xs bls }

ids :
    /* nil */         { [] }
  | i=ID              { [i] }
  | ii=ids COMMA i=ID { ii @ [i] }

term : 
    TRUE                        { mk_true }
  | FALSE                       { mk_false }
  | i=ID                        { mk_bind_term i }
  | i=ID LPAREN tt=terms RPAREN { mk_fapp_term i tt }

terms :
    /* nil */             { [] }
  | t=term                { [t] }
  | t=term COMMA tt=terms { t :: tt }

binders :
    /* nil */ { [] }
  | BIND i=ID COLON BIT bb=binders
      { mk_bit_binder i :: bb }
  | BIND i=ID COLON LOC bb=binders
      { mk_loc_binder i :: bb  }
  | BIND i=ID COLON GHOST bb=binders
      { mk_ghost_binder i :: bb }

phi :
    TRUE                        { mk_term mk_true }
  | FALSE                       { mk_term mk_false }
  | i=ID                        { A.Term (A.Name i) }
  | p1=phi CONJUNCT p2=phi      { mk_conjunct p1 p2 }
  | p1=phi DISJUNCT p2=phi      { mk_disjunct p1 p2 }
  | NEG p=phi                   { mk_neg p }
  | p1=phi RIGHTARROW p2=phi    { mk_implication p1 p2 }
  | LPAREN p=phi RPAREN         { p }
  | t1=term EQ t2=term          { mk_eq t1 t2 }
  | LBRACKET i1=ID FSLASH i2=ID RBRACKET p=phi
                                { mk_subst i1 i2 p }
  | i=ID LPAREN tt=terms RPAREN { mk_papp i tt }


prenex_quantified :
    /* nil */ { [] }
  | FORALL i1=ids DOT EXISTS i2=ids DOT
     { (i1, i2) }

types :
    /* nil */ { [] }
  | t=type_decl ts=types { t :: ts }

type_decl :
    ABSTRACT TYPE i=ID       { (i, mk_abst i) }
  | TYPE i=ID EQ t=type_lit  { (i, t) }

type_lit :
    BIT   { mk_macht mk_bit }
  | LOC   { mk_macht mk_loc }
  | i=ID  { mk_abst i }
  | BOOL  { mk_bool }

  /* do we need literal function types yet? we're not higher order */
  /* once we have typing, we will have to resolve aliases */

preds :
    /* nil */ { [] }
  | p=pred_decl ps=preds { p :: ps }

pred_decl:
    PREDICATE i=ID xs=args { mk_pred i xs }

args :
    /* nil */ { [] }
  | xs=args x=arg { xs @ [x] } 

arg :
    LPAREN a=arg RPAREN { a }
  | i=ID COLON BIT
      { mk_bit |> mk_macht |> mk_arg i }
  | i=ID COLON LOC
      { mk_loc |> mk_macht |> mk_arg i }
  | i1=ID COLON i2=ID
      { mk_abst i2 |> mk_arg i1 }
  | i=ID COLON BOOL
      { mk_bool |> mk_arg i }

funs :
    /* nil */              { [] }
  | f=fun_decl ff=funs     { f :: ff }

fun_decl :
    FUNCTION i=ID xs=args COLON t=type_lit
      { mk_fun i xs t }

axioms :
    /* nil */              { [] }
  | a=axiom_decl aa=axioms { a :: aa }

axiom_decl :  
  AXIOM FORALL ii=ids DOT p=phi
    { mk_axiom ii p }

blocks:
    /* nil */              { [] }
  | b=block_decl bb=blocks { b :: bb }

block_decl:
  BLOCK i=ID LBRACE sp=blockspec RBRACE
    { mk_block_pr i sp }

blockspec:
  PRE COLON pre=phi POST COLON post=phi
    { mk_spec pre post }

;
