open Util
open Ast

module PA = Prettyast
module P  = Printf

type casp = Reps.casp_resolved
type prog = Ast.inst list

let preamble = Rosette_preamble.preamble ;;

let convert_bits b =
  let v = BI.to_string_in_hexa (Bits.to_big_int b) in
  let l = string_of_int (Bits.width b) in
  "(bv #x"^v^" "^l^")"

let convert_atomic = function
  | Id i -> i
  | Int i -> "#x"^(BI.to_string_in_hexa i)
  | Bit b -> convert_bits b
  | True -> "#t"
  | False -> "#f"

(* generate toplevel-env let bindings *)
let convert_lets (c : casp) =
  let convert_let (i, a) = "(define "^i^" "^(convert_atomic a)^")" in
  ["; BEGIN LETS"] @
  (SM.bindings c.lets
  |> List.map convert_let) @
  ["; END LETS"]
  |> String.concat "\n"

(* encode register information *)
let convert_letstates (c : casp) =
  (* toplevel register name bindings *)
  let reg_binding (i, b) = "(define "^i^" '"^i^")" in
  let reg_bindings = SM.bindings c.letstates
    |> List.map reg_binding
  in
  (* encode register info *)
  let reg_names =
    "(define REGISTERS '("^
    (SM.bindings c.letstates
    |> List.map fst
    |> String.concat " ")^"))"
  in
  let reg_lens =
    "(define REGLENGTHS (list "^
    (SM.bindings c.letstates
    |> List.map snd
    |> List.map Bits.width
    |> List.map string_of_int
    |> String.concat " ")^"))"
  in
  let reg_inits =
    "(define REGINITS (list "^
    (SM.bindings c.letstates
    |> List.map snd
    |> List.map (fun b ->
      let w = Bits.width b in
      let s = Bits.to_bitstring b in
      let s = String.sub s 2 (String.length s - 2) in
      "(bv #b"^s^" "^(string_of_int w)^")")
    |> String.concat " ")^"))"
  in
  ["; BEGIN LETSTATES"] @
  reg_bindings @
  [reg_names;
  reg_lens;
  reg_inits;
  "; END LETSTATES"]
  |> String.concat "\n"

let convert_args = String.concat " "

let convert_unop u a =
  let a = convert_atomic a in
  match u with
  | Neg -> "(- "^a^")"
  | LogNot -> "(! "^a^")"
  | BitNot -> "(bvnot "^a^")"

let convert_binop a1 b a2 =
  let a1 = convert_atomic a1 in
  let a2 = convert_atomic a2 in
  match b with
  | Add -> "(+ "^a1^" "^a2^")"
  | Sub -> "(- "^a1^" "^a2^")"
  | Mul -> "(* "^a1^" "^a2^")"
  | Div -> "(/ "^a1^" "^a2^")"
  | Pow -> "(expt "^a1^" "^a2^")"
  | Eq -> "(eq? "^a1^" "^a2^")"
  | Neq -> "(not (eq? "^a1^" "^a2^"))"
  | BLt -> "(bvult "^a1^" "^a2^")"
  | Lt -> "(< "^a1^" "^a2^")"
  | Gt -> "(> "^a1^" "^a2^")"
  | LShift -> "(bvshl "^a1^" "^a2^")"
  | RShift -> "(bvlshr "^a1^" "^a2^")"
  | LogAnd -> "(&& "^a1^" "^a2^")"
  | LogOr -> "(|| "^a1^" "^a2^")"
  | LogXor -> "(not (<=> "^a1^" "^a2^"))"
  | BitAnd -> "(bvand "^a1^" "^a2^")"
  | BitOr -> "(bvor "^a1^" "^a2^")"
  | BitXor -> "(bvxor "^a1^" "^a2^")"

let rec convert_expr = function
  | Atomic a -> convert_atomic a
  | Deref i -> "((state-reg st) "^i^")"
  | Load (a1, a2) ->
    "(load-mem st "^(convert_atomic a1)^" "^(convert_atomic a2)^")"
  | Index (i, a) ->
    "(eq? (extract "^(convert_atomic a)^" "^(convert_atomic a)^" "^i^") (bv 1 1))"
  | Slice (i, a1, a2) ->
    "(extract (- "^(convert_atomic a2)^" 1) "^(convert_atomic a1)^" "^i^")"
  | Unop (u, a) -> convert_unop u a
  | Binop (a1, b, a2) -> convert_binop a1 b a2
  | App (i, aa) ->
    "("^i^" st "^(convert_args (List.map convert_atomic aa))^")"
  | LetE (i, t, e1, e2) ->
    "(let (["^i^" "^(convert_expr e1)^"]) "^(convert_expr e2)^")"
  | IfE (i, e1, e2) ->
    "(if "^i^" "^
      (convert_expr e1)^" "^
      (convert_expr e2)^")"

let convert_defs (c : casp) =
  let convert_def (i, (aa, e)) =
    "(define ("^i^" st "^(convert_args aa)^") "^(convert_expr e)^")"
  in
  ["; BEGIN DEFS"] @
  (SM.bindings c.defs
  |> List.map convert_def) @
  ["; END DEFS"]
  |> String.concat "\n"

(* produce a function state -> state *)
let rec convert_stmt s =
  let body = match s with
  | Skip -> "st"
  | Err -> "(assert #f)"
  | Assert e -> "(assert "^(convert_expr e)^")"
  | Seq (s1, s2) -> (* compose *)
    "("^(convert_stmt s2)^" ("^(convert_stmt s1)^" st))"
  | Store (a1, a2, e) ->
    "(store-mem st "^
    (convert_atomic a1)^" "^
    (convert_atomic a2)^" "^
    (convert_expr e)^")"
  | Assign (i, e) ->
    "(store-reg st "^i^" "^(convert_expr e)^")"
  | For (i, a1, a2, s) ->
    "(for/fold ([st st]) (["^i^" (in-range "^
    (convert_atomic a1)^" "^(convert_atomic a2)^")]) ("^
    (convert_stmt s)^"st))"
  | Call (i, aa) ->
    "("^i^" st "^(String.concat " " (List.map convert_atomic aa))^")"
  | LetS (i, t, e, s) -> (* XXX env doesn't carry into call *)
    "(let (["^i^" "^(convert_expr e)^"]) ("^(convert_stmt s)^" st))"
  | IfS (i, s1, s2) ->
    "(if "^i^" ("^
    (convert_stmt s1)^" st) ("^
    (convert_stmt s2)^" st))"
  in "(lambda (st) "^body^")"

let convert_defss (c : casp) =
  let convert_defs (i, (aa, s)) =
    "(define ("^i^" st "^(convert_args aa)^") "^(convert_stmt s)^")"
  in
  ["; BEGIN DEFSS"] @
  (SM.bindings c.defss
  |> List.map convert_defs) @
  ["; END DEFSS"]
  |> String.concat "\n"

let convert_defops (c : casp) =
  let convert_defop_struct (i, (aa, s)) =
    "(struct "^i^" ("^(convert_args (List.map fst aa))^") #:transparent)"
  in
  let convert_defop_string (i, (aa, s)) =
    let arg_string (a, t) =
      match t with
      | BitvecType l ->
        "(string-append \"0b\" (~r (bitvector->natural "^a^
        ") #:base 2 #:min-width "^(string_of_int l)^
        " #:pad-string \"0\"))"
      | BitvecLocType l ->
        "(symbol->string "^a^")"
      | BoolType ->
        "(if "^a^" \"true\" \"false\")"
      | IntType ->
        "(number->string "^a^")"
      | AliasType _ | AliasLocType _ ->
        failwith "bug: aliases should have been substituted"
    in
    let defop_args = aa
      |> List.map arg_string
      |> String.concat " \" \" "
    in
    "[("^i^" "^(convert_args (List.map fst aa))^") "^
    "(string-append \"("^i^" \" "^defop_args^" \")\")]"
  in
  let convert_defop_execute (i, (aa, s)) =
    "[("^i^" "^(convert_args (List.map fst aa))^") "^
    "("^(convert_stmt s)^" st)]"
  in
  ["; BEGIN DEFOPS"] @
  (SM.bindings c.defops
  |> List.map convert_defop_struct) @
  ["(define (inst->string insn)";
  "(match insn"] @
  (SM.bindings c.defops
  |> List.map convert_defop_string) @
  ["))";
  "(define (execute prog st)";
  "(for/fold ([st st]) ([insn prog])";
  "(match insn"] @
  (SM.bindings c.defops
  |> List.map convert_defop_execute) @
  ["['() st]";
  ")))";
  "; END DEFOPS"]
  |> String.concat "\n"

(* generate type-respecting synthax macro for use in sketches
   that demand instruction synthesis *)
let convert_synthax (c : casp) =
  (* build lists of registers of given size *)
  let reg_list rls (i, b) =
    let w = Bits.width b in
    match IM.find_opt w rls with
    | None -> IM.add w [i] rls
    | Some l -> IM.add w (i :: l) rls
  in
  let reg_lists = c.letstates
    |> SM.bindings
    |> List.fold_left reg_list IM.empty
  in
  (* define-synthax for registers *)
  let choose_reg (w, l) =
    "(define-synthax reg/"^(string_of_int w)^"*\n"^
    "  ([(_) (choose* "^(String.concat " " l)^")]))" (* TODO ' regs *)
  in
  let choose_regs = reg_lists
    |> IM.bindings
    |> List.map choose_reg
    |> String.concat "\n"
  in
  (* define-synthax for instructions *)
  (* TODO opt: list and collect needed subterms to predefine
     before inst emission *)
  let choose_inst (i, (aa, s)) =
    let choose_arg (_, t) =
      match t with
      | BitvecType l -> "(imm* "^(string_of_int l)^")"
      | BitvecLocType l -> "(reg/"^(string_of_int l)^"*)"
      | BoolType -> "(?? boolean?)"
      | IntType -> "(?? integer?)"
      | AliasType _ | AliasLocType _ ->
        failwith "bug: aliases should have been substituted"
    in
    let choose_args = aa
      |> List.map choose_arg
      |> String.concat " "
    in
    "("^i^" "^choose_args^")"
  in
  let choose_insts = c.defops
    |> SM.bindings
    |> List.map choose_inst
    |> List.append ["'()"]
    |> String.concat "\n"
  in
  ["; BEGIN SYNTHAX";
  choose_regs;
  "(define-synthax inst*";
  "  ([(_) (choose* "^choose_insts^")]))";
  "; END SYNTHAX"]
  |> String.concat "\n"

(* given cassiopeia as casp_resolved,
   emit rosette implementing inst sequence language
   for this architecture *)
let convert_casp (c : casp) =
  let letstates = convert_letstates c in
  let lets = convert_lets c in
  let defs = convert_defs c in
  let defss = convert_defss c in
  let defops = convert_defops c in
  let synthax = convert_synthax c in
  [preamble;
  "; BEGIN GENERATED MACHINE DESCRIPTION";
  letstates;
  lets;
  defs;
  defss;
  defops;
  synthax;
  "; END GENERATED MACHINE DESCRIPTION"]
  |> String.concat "\n"

(* given a series of ops as a .prog,
   emit rosette executing the inst sequence *)
let convert_prog (p : prog) name =
  let convert_inst (i, aa) =
    "("^i^" "^(convert_args (List.map convert_atomic aa))^")"
  in
  let insts = match p with
    | [] -> "'()" (* racket balks at empty procedure defines *)
    | _ -> String.concat " " (List.map convert_inst p)
  in
  ["; BEGIN GENERATED PROG";
  "(define "^name^" (list "^insts^"))";
  "; END GENERATED PROG"]
  |> String.concat "\n"

(* assign a new symbolic value of appropriate size to each register *)
let convert_inits (c : casp) =
  let orig_state = "(define orig-state (fresh-state))" in
  let convert_init (i, b) =
    "(define "^i^"_orig ((state-reg orig-state) '"^i^"))"
  in
  [orig_state] @
  (SM.bindings c.letstates
  |> List.map convert_init)
  |> String.concat "\n"

let convert_ghosts gg =
  let convert_ghost g =
    "(define-symbolic* "^g^" boolean?)" 
  in
  let ghosts = "(define GHOSTVARS (list "^(String.concat " " gg)^"))" in
  (gg
  |> List.map convert_ghost
  |> String.concat "\n")^
  ghosts

let convert_pre pre =
  "(assert "^(convert_expr pre)^")"

let convert_post post =
  "(assert "^(convert_expr post)^")"

(* given pre- and post-condition,
   emit rosette implementing verification *)
let convert_verify (c: casp) progname gg pre post =
  let inits = convert_inits c in
  let ghosts = convert_ghosts gg in
  let precond = convert_pre pre in
  let postcond = convert_post post in
  ["; BEGIN GENERATED VERIFY";
  inits;
  ghosts;
  "(define model";
  "  (verify";
  "   #:assume (let ([st orig-state]) "^precond^")";
  "   #:guarantee (begin";
  "                 (let ([st (execute "^progname^" orig-state)])";
  "                 "^postcond^"))))";
  ";(pretty-print (evaluate orig-state model))";
  ";(define orig (evaluate orig-state model))";
  ";(define after (execute prog orig))";
  "(if (sat? model) (begin (display \"Failed:\\n\")";
  "(pretty-print (evaluate orig-state model)))";
  "(display \"Succeeded\\n\"))";
  "; END GENERATED VERIFY"]
  |> String.concat "\n"

let convert_synth (c : casp) gg pre post =
  let inits = convert_inits c in
  let ghosts = convert_ghosts gg in
  let precond = convert_pre pre in
  let postcond = convert_post post in
  ["; BEGIN GENERATED SYNTH";
  inits;
  ghosts;
  "(define sketch (for/list ([_ 2]) (inst*)))";
  "(define model";
  "  (time (synthesize";
  "   #:forall (append (symbolics orig-state) GHOSTVARS)";
  "   #:assume (let ([st orig-state]) "^precond^")";
  "   #:guarantee (begin";
  "                 (let ([st (execute sketch orig-state)])";
  "                 "^postcond^")))))";
  "(if (sat? model) (begin (display \"Succeeded:\\n\")";
  "(display (prog->string (evaluate sketch model))))";
  "(display \"Failed\\n\"))";
  "; END GENERATED SYNTH"]
  |> String.concat "\n"
