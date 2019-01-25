open Batteries
open Util

module BI = BatBig_int

type id   = string
type dec  = BI.t
type bits = Bits.t

type typ =
  (* basic types *)
  | BitvecType of int
  | BitvecLocType of int
  | BoolType
  | IntType
  (* parser placeholders *)
  | AliasType of id
  | AliasLocType of id

type unop =
  | Neg
  | LogNot
  | BitNot

type binop =
  | Add
  | Sub
  | Mul
  | Div
  | Pow
  | Eq
  | Neq
  | BLt
  | Lt
  | Gt
  | LShift
  | RShift
  | LogAnd
  | LogOr
  | LogXor
  | BitAnd
  | BitOr
  | BitXor

type atomic =
  | Id of id
  | Int of dec
  | Bit of bits
  | True
  | False

type str  = 
  | SLiteral of string
  | SArmCond of string * id
  | SField of id
  | SAtomic of atomic

type string_expr = str list

type arg = id * typ

type expr =
  | Atomic of atomic
  | Deref of id
  | Load of atomic * atomic
  | Index of id * atomic
  | Slice of id * atomic * atomic
  | Unop of unop * atomic 
  | Binop of atomic * binop * atomic
  | App of id * atomic list
  | LetE of id * typ * expr * expr
  | IfE of id * expr * expr

type stmt =
  | Skip
  | Err
  | Assert of expr
  | Seq of stmt * stmt
  | Store of atomic * atomic * expr
  | Assign of id * expr
  | For of id * atomic * atomic * stmt
  | Call of id * atomic list
  | LetS of id * typ * expr * stmt
  | IfS of id * stmt * stmt


type decl =
  | DeclType of id * typ
  | DeclLet of id * typ * expr
  | DeclLetstate of id * typ * bits
  | DeclDef of id * arg list * typ * expr
  | DeclDefs of id * arg list * stmt
  | DeclDefop of id * arg list * string_expr * stmt

type inst = id * atomic list

type t =
  | Casp of (Pos.t * decl) list
  | Prog of (Pos.t * inst) list
