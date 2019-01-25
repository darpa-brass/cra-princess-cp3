open Batteries
open Util

module A   = Ast
module P   = Printf
module Pr  = Prettyast
module Opt = Options

(* this is a hack to enable arm conditional execution extraction possible.
 * conditional execution was removed from our initial arm models because
 * conditional execution itself is a dirty microarchitectural hack *cough* STDM.
 * however, due to scaling issues with our Rosette + Boolector decision procedure,
 * we are forced to synthesize code using conditional execution.
 *   however, note that we model arm conditional execution perfectly. this is
 *   simply to print out the right conditional flag on the assembly opcode;
 *   we have to either hardcode the flags or make our string expressions
 *   turing complete. hardcoding is the preferable hack. *)

(* here is the wonderful table that we have to hardcode. ARM IS SO RISC! *)
(*def arm32_checkcond cpsr: 32 bit op: 4 bit -> bool = 
	let is_eq: bool = op == 0b0000 in
	let is_ne: bool = op == 0b0001 in
	let is_hs: bool = op == 0b0010 in
	let is_lo: bool = op == 0b0011 in
	let is_mi: bool = op == 0b0100 in
	let is_pl: bool = op == 0b0101 in
	let is_vs: bool = op == 0b0110 in
	let is_vc: bool = op == 0b0111 in
	let is_hi: bool = op == 0b1000 in
	let is_ls: bool = op == 0b1001 in
	let is_ge: bool = op == 0b1010 in
	let is_lt: bool = op == 0b1011 in
	let is_gt: bool = op == 0b1100 in
	let is_le: bool = op == 0b1101 in
	let is_al: bool = op == 0b1110 in *)
type arm_cond =
  Eq | Ne | Hs | Lo | Mi | Pl | Vs | Vc | Hi | Ls | Ge | Lt | Gt | Le | Al

let string_of_arm_cond = function
  | Eq -> "eq"
  | Ne -> "ne"
  | Hs -> "hs"
  | Lo -> "lo"
  | Mi -> "mi"
  | Pl -> "pl"
  | Vs -> "vs"
  | Vc -> "vc"
  | Hi -> "hi"
  | Ls -> "ls"
  | Ge -> "ge"
  | Lt -> "lt"
  | Gt -> "gt"
  | Le -> "le"
  | Al -> "al"

let arm_cond =
  [Eq; Ne; Hs; Lo; Mi; Pl; Vs; Vc; Hi; Ls; Ge; Lt; Gt; Le; Al]

let get_arm_cond_code i =
  try
    List.at arm_cond i |> string_of_arm_cond
  with Invalid_argument s ->
    failwith "Invalid arm condition code " ++ s

let string_of_param ps = function
  | A.SLiteral s -> s
  | A.SAtomic a -> Pr.string_of_atomic a
  | A.SField i -> Pr.string_of_atomic (List.assoc i ps)
  | A.SArmCond (s,i) ->
      let cc = List.assoc i ps |>
        Pr.string_of_atomic |>
        int_of_string in
      s ++ get_arm_cond_code cc

      
let get_asm (i, ps, se) =
  try
   let f = string_of_param ps in
   let s = List.map f se in
     String.concat " " s
  with Not_found ->
    let se = Pr.string_of_string_expr se in
    failwith i ++ " not found while resolving " ++ se

let get_pre_asm ops (i, args) =
  let (formals, se) = List.assoc i ops in
  let  formals      = List.map fst formals in
  (i, zip formals args, se)

let defop_filter = function
  | A.DeclDefop (i, ff, se, _) -> Some (i, (ff, se))
  | _ -> None
    
(* proc_prog is typechecked derivative of prog_ast *)
(* casp_decls is the defop list used to typecheck proc_prog *)
let to_asm casp prog =
  let ops  = maybe_filter defop_filter casp in
  let pasm = List.map (get_pre_asm ops) prog in
  let asm  = List.map get_asm pasm in
    String.concat "\n" asm
