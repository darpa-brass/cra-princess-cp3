open Batteries
open Util
open Ast

module A = Ast
module Opt = Options
module P = Printf
module F = Format


let string_of_unop = function
  | Neg -> "(-)"
  | LogNot -> "not"
  | BitNot -> "!"

let string_of_binop = function
  | Add -> "+"
  | Sub -> "-"
  | Mul -> "*"
  | Div -> "/"
  | Pow -> "**"
  | Eq  -> "=="
  | Neq -> "!="
  | BLt -> "b<"
  | Lt  -> "<"
  | Gt  -> ">"
  | LShift -> "<<"
  | RShift -> ">>"
  | LogAnd -> "&&"
  | LogOr  -> "||"
  | LogXor -> "^^"
  | BitAnd -> "&"
  | BitOr  -> "|"
  | BitXor -> "^"

let string_of_hex h =
  (Bits.to_string h) ++
  " len:" ++ (string_of_int (Bits.width h))

let string_of_id i = i

let pos_of_ty = function
  | None -> Pos.builtin
  | Some (pos,_) -> pos

let rec string_of_function_typ (arg_typs, return_typ) =
  let arg_typs = arg_typs
                 |> (List.map string_of_typ) in
  let return_typ = string_of_typ return_typ in
  String.concat "->" (arg_typs @ [return_typ])

and string_of_typ = function
  | BitvecType i -> (string_of_int i)^" bit"
  | BitvecLocType i -> (string_of_int i)^" bit loc"
  | AliasType i -> i
  | AliasLocType i -> i^" loc"
  (*| FunType (xs, rt) ->
      let s = string_of_function_typ (xs,rt) in
      "fun " ^ s*)
  | BoolType -> "bool"
  | IntType -> "int"

let string_of_atomic = function
  | Id i -> string_of_id i
  | Int i -> string_of_bint i
  | Bit v -> Bits.to_hexstring v
  | True -> "true"
  | False -> "false"

let rec string_of_expr = function
  | Atomic a -> string_of_atomic a
  | Deref i -> "*" ^ string_of_id i
  | Load (a1, a2) ->
      "Mem[" ^
      (string_of_atomic a1) ^ "," ^
      (string_of_atomic a2) ^ "]"
  | Index (i, a) ->
      (string_of_id i) ^ "[" ^ (string_of_atomic a) ^ "]"
  | Slice (i, a1, a2) -> 
      (string_of_id i) ^ "[" ^
      (string_of_atomic a1) ^ ", " ^
      (string_of_atomic a2) ^ "]"
  | Unop (op, a) ->
      (string_of_unop op) ^ " " ^ string_of_atomic a
  | Binop (a1, op, a2) ->
      string_of_atomic a1 ^ " " ^  
      string_of_binop  op ^ " " ^
      string_of_atomic a2
  | App (i, args) ->
      i :: (args |> List.map string_of_atomic) |>
      String.concat " "
  | LetE (i, ty, e1, e2) ->
      "let " ^ (string_of_id i) ^
      " : " ^ (string_of_typ ty) ^
      " = " ^ (string_of_expr e1) ^
      " in " ^ (string_of_expr e2)
  | IfE (i, e1, e2) ->
      "if " ^ (string_of_id i) ^
      " then " ^ (string_of_expr e1) ^
      " else " ^ (string_of_expr e2)

let rec string_of_stmt = function
  | Skip -> "skip"
  | Err -> "err"
  | Assert e ->
      let e = string_of_expr e in
      "assert " ^ e
  | Seq (s1, s2) ->
      let s1 = string_of_stmt s1 in
      let s2 = string_of_stmt s2 in
      s1 ++ "; " ++ s2
  | Store (a1, a2, e) ->
      let a1 = string_of_atomic a1 in
      let a2 = string_of_atomic a2 in
      let e = string_of_expr e in
      "Mem[" ^ a1 ^ "," ^ a2 ^ "] <- "^ e
  | Assign (i, e) ->
      let i = string_of_id i in
      let e = string_of_expr e in
      "*" ^ i ^ " <- " ^ e
  | For (i, a1, a2, s) -> 
      "for " ++ i ++ " in " ++
      (string_of_atomic a1) ++ ", ..., " ++
      (string_of_atomic a2) ++ "\ndo\n\t" ++
      (string_of_stmt s) ++ "\ndone"
  | Call (i, args) ->
      i :: (args |> List.map string_of_atomic) |>
      String.concat " "
  | LetS (i, t, e, s) -> 
      "let " ++ i ++ ":" ++
      (string_of_typ t) ++ " = " ++
      (string_of_expr e) ++ " in\n" ++
      (string_of_stmt s)
  | IfS (i, s1, s2) ->
      "if " ++ i ++ " then " ++
      (string_of_stmt s1) ++ " else " ++
      (string_of_stmt s2)

let string_of_typed_id i t = 
	string_of_id i ++ " : " ++ string_of_typ t

let string_of_typed_arg (i, t) =
  ch_wrap (string_of_typed_id i t) PAREN

let string_of_typed_args xs = xs
  |> (List.map string_of_typed_arg)
  |> String.concat " "

let rec string_of_string_expr = function
  | SLiteral s :: ss -> s ++ " " ++ string_of_string_expr ss
  | SAtomic a :: ss  ->
      string_of_atomic a ++ " " ++ string_of_string_expr ss
  | SField i :: ss -> i ++ ".txt" ++ " " ++ string_of_string_expr ss 
  | [] -> ""

let string_of_decl = function
	  DeclType (i, t) ->
      let i, t = string_of_id i, string_of_typ t in
      "type " ++ i ++ " = " ++ t
  | DeclLet (i, t, e) ->
      let it = string_of_typed_id i t in
      let e  = string_of_expr e in
      "let " ++ it ++ " = " ++ e
	| DeclLetstate (i, t, h) ->
      let it = string_of_typed_id i t in
      let h = Bits.to_hexstring h in
      "letstate " ++ it ++ " = " ++ h
  | DeclDef (i, xs, t, e) ->
      let i   = string_of_id i in
      let xs  = string_of_typed_args xs in
      let t,e = string_of_typ t, string_of_expr e in
      "def " ++ i ++ " " ++ xs ++ " -> " ++ t ++ " " ++ e
  | DeclDefs (i, xs, s) ->
      let i   = string_of_id i in
      let xs  = string_of_typed_args xs in
      let s   = string_of_stmt s in
      "defs " ++ i ++ " " ++ xs ++ " -> () " ++ s
  | DeclDefop (i, xs, txt, s) ->
      let i   = string_of_id i in
      let xs  = string_of_typed_args xs in
      let s   = string_of_stmt s in
      let txt = string_of_string_expr txt in
      let txt = "txt = " ++ txt in
      let sem = "sem = " ++ s in
        "defop " ++ i ++ " " ++ xs ++ " " ++
        (ch_wrap ("\n" ++ txt ++ "\n" ++ sem ++ "\n") BRACE)

let string_of_decl (pos, decl) =
      (Pos.string_of pos) ++ ": " ++
      (string_of_decl decl)

let string_of_casp m = m
  |> (List.map string_of_decl)
  |> String.concat "\n"

let string_of_inst (i, args) =
  (string_of_id i) ++ " " ++
  (args |> (List.map string_of_atomic) |> String.concat " ")

let string_of_inst (pos, inst) =
  ch_wrap (string_of_inst inst) PAREN

let string_of_prog p = p
  |> List.map string_of_inst
  |> String.concat "\n"

let string_of_t = function
  | Casp m -> string_of_casp m
  | Prog p -> string_of_prog p

