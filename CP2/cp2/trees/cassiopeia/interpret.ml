open Util
open Ast

module PA = Prettyast
module P  = Printf
module Opt = Options

type casp = Reps.casp_resolved
type prog = inst list

let print_verbose: (string -> unit) ref = ref (fun s -> ())
let print_dump: (string -> unit) ref = ref (fun s -> ())

(* TODO mark unexpected error messages with "BUG:" *)

type value =
  | ValInt    of bint
  | ValBit    of bits
  | ValBool   of bool
  | ValState  of id

let string_of_value = function
  | ValInt i    -> "int:"^(string_of_bint i)
  | ValBit h    -> "bv:"^(Bits.to_hexstring h)
  | ValBool b   -> if b then "true" else "false"
  | ValState s  -> "&"^s

type world = {
  mem : bits BIM.t;
  reg : bits SM.t;
  env : value SM.t;
}

let world_empty = { mem = BIM.empty; reg = SM.empty; env = SM.empty }

(* get list with numbers [a; a + 1; ...; b - 1] *)
let range a b =
  let rec range_ a b l =
    if a >= b then l
    else range_ (a + 1) b (a :: l)
  in
  List.rev (range_ a b [])

(* memory fetch with zero-initialized memory *)
(* TODO endianness: this is big-endian as default *)
let mem_get mem addr len =
  range 0 (BI.int_of_big_int len) |>
  (* get byte at each address *)
  List.map (fun i ->
    let a =
      BI.big_int_of_int i |>
      BI.add_big_int addr
    in
    match BIM.find_opt a mem with
    | None -> Bits.zero 8
    | Some h ->
      if Bits.width h <> 8 then
        failwith ("bug: non-byte stored in memory at addr "^
                  (hexstring_of_bint a))
      else h) |>
  (* combine bytes *)
  List.fold_left Bits.concat (Bits.zero 0)

(* memory store *)
(* TODO endianness: this is big-endian as default *)
let mem_put mem addr v =
  (* get number of bytes as ceil(bits / 8) *)
  let bytelen = (Bits.width v + 7) / 8 in
  range 0 bytelen |>
  List.map (fun i ->
    (* calculate addr to store to: run backwards from end *)
    let addr =
      BI.big_int_of_int (bytelen - 1 - i) |>
      BI.add_big_int addr
    in
    (* get bytes from word *)
    let b = Bits.rshift v (BI.big_int_of_int (i * 8)) in
    (addr, Bits.of_big_int 8 (Bits.to_big_int b))) |>
  (* write bytes into memory *)
  List.fold_left (fun m (a, b) -> BIM.add a b m) mem

let string_of_mem (mem : Bits.t BIM.t) =
  let collapse32 addr _ out =
    let four = BI.big_int_of_int 4 in
    let diff = BI.mod_big_int addr four in
    let base = BI.sub_big_int addr diff in
    let word = mem_get mem base four in
    BIM.add base word out
  in
  let pair_to_string (k, v) =
    (hexstring_of_bint k)^" : "^(Bits.to_hexstring v)
  in
  (BIM.fold collapse32 mem BIM.empty
    |> BIM.bindings
    |> List.map pair_to_string
    |> String.concat "\n")^"\n"

let string_of_reg (reg : Bits.t SM.t) =
  let pair_to_string (k, v) =
    k^" : "^(Bits.to_string v)^", len "^(string_of_int (Bits.width v))
  in
  (reg
    |> StringMap.bindings
    |> List.map pair_to_string
    |> String.concat "\n")^"\n"

let exp2 = BI.power_int_positive_big_int 2

let eval_atomic state a =
  match a with
  | Id s ->
    (match SM.find_opt s state.env with
    | None -> failwith ("type error: variable " ++ s ++ " undefined")
    | Some v -> v)
  | Int d -> ValInt d
  | Bit v -> ValBit v
  | True -> ValBool true
  | False -> ValBool false

let collect_args env args vv =
  (* add the next arg to an environment *)
  let add_arg env (i, v) = SM.add i v env in
  try
    List.combine args vv
    |> List.fold_left add_arg env
  with Invalid_argument s ->
    failwith ("type error: wrong number of arguments: got "^
              (string_of_int (List.length vv))^", expected "^
              (string_of_int (List.length args)))

let rec eval_expr (c : casp) state e =
  let _ =
    (!print_verbose) (P.sprintf "eval_expr: %s\n" (PA.string_of_expr e))
  in
  let result = match e with
    | Atomic a -> eval_atomic state a
    | Deref i -> eval_deref c state i
    | Load (a1, a2) -> eval_load c state a1 a2
    | Index (i, a) -> eval_index c state i a
    | Slice (i, a1, a2) -> eval_slice c state i a1 a2
    | Unop (u, a) -> eval_unop c state u a
    | Binop (a1, b, a2) -> eval_binop c state a1 b a2
    | App (i, args) -> eval_app c state i args
    | LetE (i, _, e1, e2) -> eval_lete c state i e1 e2
    | IfE (i, e1, e2) -> eval_ife c state i e1 e2
  in
  (* print_string ("\t\t: " ^ (dump_value (result)) ^ "\n"); *)
  result

and eval_deref c state i =
  match SM.find_opt i state.env with
  | None -> failwith ("type error: no variable "^i)
  | Some (ValState s) ->
    (match SM.find_opt s state.reg with
    | None -> failwith ("bug: deref of nonexistent state "^s)
    | Some h -> ValBit h)
  | _ -> failwith "type error: attempted deref of non-ref"

and eval_load c state a1 a2 =
  match (eval_atomic state a1, eval_atomic state a2) with
  | (ValInt d1, ValInt d2) -> ValBit (mem_get state.mem d1 d2)
  | (_, _) ->
    failwith ("type error: mem load expected int addr and int len")

and eval_index c state i a =
  match SM.find_opt i state.env with
  | None -> failwith ("type error: no variable "^i)
  | Some (ValBit h) ->
    let l = Bits.width h in
    (match eval_atomic state a with
    | ValInt d ->
        let dl = BI.big_int_of_int l in
        if BI.sign_big_int d = -1 then
          failwith "index value is negative"
        else if BI.ge_big_int d dl then
          failwith ("index value is out of range, got "^
                    (BI.string_of_big_int d)^" out of "^
                    (string_of_int l)^" bit")
        else
          ValBool (Bits.get h d)
    | _ -> failwith "type error: index value not an int")
  | _ -> failwith ("type error: variable "^i^" not a bitvector")

and eval_slice c state i a1 a2 =
  match SM.find_opt i state.env with
  | None -> failwith ("type error: no variable "^i)
  | Some (ValBit h) ->
  let l = Bits.width h in
    (match (eval_atomic state a1, eval_atomic state a2) with
    | (ValInt d1, ValInt d2) ->
      let dl = BI.big_int_of_int l in
        if BI.sign_big_int d1 = -1 then
          failwith "slice start is negative"
        else if BI.sign_big_int d2 = -1 then
          failwith "slice end is negative"
        else if BI.gt_big_int d1 dl then
          failwith "slice start is out of range"
        else if BI.gt_big_int d2 dl then
          failwith "slice end is out of range"
        else if BI.gt_big_int d1 d2 then
          failwith "slice starts after end"
        else
          let w = BI.int_of_big_int (BI.sub_big_int d2 d1) in
          ValBit (Bits.of_big_int w (Bits.to_big_int (Bits.rshift h d1)))
    | _ -> failwith "slice range not a pair of ints")
  | _ -> failwith ("type error: variable "^i^" not a bitvector")

and eval_unop c state u a =
  let a = eval_atomic state a in
  match (u, a) with
  | (Neg, ValInt d) -> ValInt (BI.minus_big_int d)
  | (Neg, _) -> failwith "not negating an integer"
  | (LogNot, ValBool b) -> ValBool (not b)
  | (LogNot, _) -> failwith "not negating a boolean"
  | (BitNot, ValBit h) -> ValBit (Bits.not h)
  | (BitNot, _) -> failwith "not negating a bitvector"

and eval_binop c state a1 b a2 =
  let _ =
    (!print_verbose) (P.sprintf "eval_binop: %s\n" (PA.string_of_binop b))
  in
  let (a1, a2) = (eval_atomic state a1, eval_atomic state a2) in
  match (b, a1, a2) with
  | (Add, ValInt d1, ValInt d2) -> ValInt (BI.add_big_int d1 d2)
  | (Add, _, _) -> failwith "not adding two integers"
  | (Sub, ValInt d1, ValInt d2) -> ValInt (BI.sub_big_int d1 d2)
  | (Sub, _, _) -> failwith "not subtracting two integers"
  | (Mul, ValInt d1, ValInt d2) -> ValInt (BI.mult_big_int d1 d2)
  | (Mul, _, _) -> failwith "not multiplying two integers"
  | (Div, ValInt d1, ValInt d2) -> ValInt (BI.div_big_int d1 d2)
  | (Div, _, _) -> failwith "not dividing two integers"
  | (Pow, ValInt d1, ValInt d2) ->
    ValInt (BI.power_big_int_positive_big_int d1 d2)
  | (Pow, _, _) -> failwith "not exponentiating two integers"
  | (Eq, ValInt d1, ValInt d2) -> ValBool (BI.eq_big_int d1 d2)
  | (Eq, ValBit b1, ValBit b2) -> ValBool ((Bits.bits_compare b1 b2) = 0)
  | (Eq, ValBool b1, ValBool b2) -> ValBool (b1 = b2)
  | (Eq, ValState s1, ValState s2) -> ValBool (s1 = s2)
  | (Eq, _, _) -> failwith "comparison of two different types"
  | (Neq, ValInt d1, ValInt d2) -> ValBool (not (BI.eq_big_int d1 d2))
  | (Neq, ValBit b1, ValBit b2) -> ValBool ((Bits.bits_compare b1 b2) <> 0)
  | (Neq, ValBool b1, ValBool b2) -> ValBool (b1 <> b2)
  | (Neq, ValState s1, ValState s2) -> ValBool (s1 <> s2)
  | (Neq, _, _) -> failwith "comparison of two different types"
  | (Lt, ValInt d1, ValInt d2) -> ValBool (BI.lt_big_int d1 d2)
  | (Lt, _, _) -> failwith "not comparing two integers"
  | (Gt, ValInt d1, ValInt d2) -> ValBool (BI.gt_big_int d1 d2)
  | (Gt, _, _) -> failwith "not comparing two integers"
  | (LShift, ValBit h, ValInt d) -> ValBit (Bits.lshift h d)
  | (LShift, _, _) -> failwith "not shifting a hex with an int"
  | (RShift, ValBit h, ValInt d) -> ValBit (Bits.rshift h d)
  | (RShift, _, _) -> failwith "not shifting a hex with an int"
  | (LogAnd, ValBool b1, ValBool b2) -> ValBool (b1 && b2)
  | (LogAnd, _, _) -> failwith "not &&ing two booleans"
  | (LogOr, ValBool b1, ValBool b2) -> ValBool (b1 || b2)
  | (LogOr, _, _) -> failwith "not ||ing two booleans"
  | (LogXor, ValBool b1, ValBool b2) -> ValBool (b1 <> b2)
  | (LogXor, _, _) -> failwith "not ^^ing two booleans"
  | (BitAnd, ValBit h1, ValBit h2) ->
      if Bits.width h1 <> Bits.width h2 then
        failwith "& of different lengths"
      else ValBit (Bits.and_ h1 h2)
  | (BitAnd, _, _) -> failwith "attempting bitwise and on non-bvs"
  | (BitOr, ValBit h1, ValBit h2) ->
      if Bits.width h1 <> Bits.width h2 then
        failwith "| of different lengths"
      else ValBit (Bits.or_ h1 h2)
  | (BitOr, _, _) -> failwith "attempting bitwise or on non-bvs"
  | (BitXor, ValBit h1, ValBit h2) ->
      if Bits.width h1 <> Bits.width h2 then
        failwith "^ of different lengths"
      else ValBit (Bits.xor h1 h2)
  | (BitXor, _, _) -> failwith "attempting bitwise xor on non-bvs"
  | _ -> failwith "probably BLt: NYI!" (* XXX *)

and eval_app c state i aa =
  (* first, builtins *)
  if i = "bv_to_len" then
    match aa with
    | [a1; a2] -> (match (eval_atomic state a1, eval_atomic state a2) with
      | (ValInt len, ValBit h) ->
        let ilen = BI.int_of_big_int len in
        ValBit (Bits.of_big_int ilen (Bits.to_big_int h))
      | _ -> failwith "bv_to_len takes one int arg and one hex arg")
    | _ -> failwith "wrong number of args to bv_to_len"
  else if i = "bv_to_uint" then
    match aa with
    | [a] -> (match eval_atomic state a with
      | ValBit h -> ValInt (Bits.to_big_int h)
      | _ -> failwith "bv_to_uint takes one hex arg")
    | _ -> failwith "wrong number of args to bv_to_uint"
  else if i = "uint_to_bv_l" then
    match aa with
    | [a1; a2] -> (match (eval_atomic state a1, eval_atomic state a2) with
      | (ValInt len, ValInt i) ->
          ValBit (Bits.of_big_int (BI.int_of_big_int len) i)
      | _ -> failwith "uint_to_bv_l takes two int args")
    | _ -> failwith "wrong number of args to uint_to_bv_l"
  (* now the general case *)
  else
    let (args, body) = match SM.find_opt i c.defs with
      | None -> failwith ("type error: no such function "^i)
      | Some op -> op
    in
    let vv = List.map (eval_atomic state) aa in
    let env' = collect_args state.env args vv in (* XXX env carries into call *)
    eval_expr c { state with env = env' } body

and eval_lete c state i e1 e2 =
  let v = eval_expr c state e1 in
  eval_expr c { state with env = SM.add i v state.env } e2

and eval_ife c state i e1 e2 =
  match SM.find_opt i state.env with
  | None -> failwith ("no variable "^i)
  | Some (ValBool b) ->
    if b then
      eval_expr c state e1
    else
      eval_expr c state e2
  | _ -> failwith "type error: conditioning on non-boolean"

and eval_stmt (c : casp) state s =
  let _ =
    (!print_verbose) (P.sprintf "eval_stmt: %s\n" (PA.string_of_stmt s))
  in
  match s with
  | Skip -> state
  | Err -> failwith ("encountered error")
  | Assert e ->
    let v = eval_expr c state e in
    (match v with
    | ValBool b ->
      if not b then failwith ("assertion failed")
      else state
    | _ -> failwith ("type error: assert got non-boolean "^(string_of_value v)))
  | Seq (s1, s2) ->
    let state' = eval_stmt c state s1 in
    eval_stmt c state' s2
  | Assign (i, e) ->
    let v = eval_expr c state e in
    (match v with
    | ValBit b ->
      (match SM.find_opt i state.env with
      | None -> failwith ("no variable "^i)
      | Some (ValState s) ->
        { state with reg = SM.add s b state.reg }
      | _ -> failwith "type error: Assign to non-location")
    | _ -> failwith "type error: Assign got non-bitvector value")
  | Store (a1, a2, e) ->
    let a1 = eval_atomic state a1 in
    let a2 = eval_atomic state a2 in
    let v = eval_expr c state e in
    (match (a1, a2, v) with
    | (ValInt addr, ValInt len, ValBit b) ->
      let len = (BI.int_of_big_int len) * 8 in
      if len = Bits.width b then
        { state with mem = mem_put state.mem addr b }
      else
        failwith ("type error: length of value for Store does not match "^
                  "given length: given length "^(string_of_int len)^
                  ", got value of length "^(string_of_int (Bits.width b)))
    | (ValInt _, ValInt _, _) ->
      failwith "type error: Store got non-bitvector value to store"
    | (ValInt _, _, _) ->
      failwith "type error: Store got non-int length"
    | (_, _, _) ->
      failwith "type error: Store got non-int addr")
  | For (i, a1, a2, s) ->
    (match (eval_atomic state a1, eval_atomic state a2) with
    | (ValInt i1, ValInt i2) ->
      let rec step state idx =
        if BI.ge_big_int idx i2 then state
        else
          let state' = { state with env = SM.add i (ValInt idx) state.env } in
          step (eval_stmt c state' s) (BI.succ_big_int idx)
      in
      step state i1
    | _ -> failwith "type error: For loop with non-integer limits")
  | Call (i, aa) ->
    let (args, body) = match SM.find_opt i c.defss with
      | None -> failwith ("no such subroutine "^i)
      | Some op -> op
    in
    let vv = List.map (eval_atomic state) aa in
    let env' = collect_args state.env args vv in (* XXX env carries into call *)
    eval_stmt c { state with env = env' } body
  | LetS (i, _, e, s) ->
    let v = eval_expr c state e in
    eval_stmt c { state with env = SM.add i v state.env } s
  | IfS (i, s1, s2) ->
    (match SM.find_opt i state.env with
    | None -> failwith ("no variable "^i)
    | Some (ValBool b) ->
      if b then eval_stmt c state s1
      else eval_stmt c state s2
    | _ -> failwith "type error: IfS got non-boolean value in condition")

let eval_op (c : casp) state i aa =
  let _ =
    (!print_verbose) (P.sprintf "eval_op: %s\n" i)
  in
  let (args, body) = match SM.find_opt i c.defops with
    | None -> failwith ("no such op "^i)
    | Some op -> op
  in
  let vv = List.map (eval_atomic state) aa in
  let env' = collect_args state.env (List.map fst args) vv in
  eval_stmt c { state with env = env' } body

let eval_inst (c : casp) state (i, aa) = eval_op c state i aa

let eval_world (c : casp) =
  (* build starting state: this consists of
     - starting memory
     - starting register state
     - top level variable environment *)
  (* skipping checks: no ID atomics, no duplicates in env *)
  (* XXX shimming in an order inversion *)
  let env =
    SM.fold (fun i v env -> SM.add i (ValState i) env)
            c.letstates SM.empty
  in
  let w = { mem = BIM.empty; reg = c.letstates; env = env } in
  SM.fold (fun i v w ->
    { w with env = SM.add i (eval_atomic w v) w.env }) c.lets w

(* run a prog *)
let eval_prog (c : casp) (p : prog) =
  let start = eval_world c in
  (* run a single instruction at a time *)
  List.fold_left (eval_inst c) start p
