open Util
open Ale_ast

let rec free_of_term = function
  | Name i -> SS.singleton i
  | FApp (i, tt) ->
    List.fold_left (fun s t -> SS.union s (free_of_term t))
      (SS.singleton i) tt
  | _ -> SS.empty

let rec free_of_phi = function
  | Term t -> free_of_term t
  | Forall (ii, p) | Exists (ii, p) ->
    List.fold_left (fun s i -> SS.remove i s) (free_of_phi p) ii
  | Conjunct (p1, p2) | Disjunct (p1, p2) | Implies (p1, p2) ->
    SS.union (free_of_phi p1) (free_of_phi p2)
  | PApp (i, tt) ->
    List.fold_left (fun s t -> SS.union s (free_of_term t))
      (SS.singleton i) tt
  | Neg p -> free_of_phi p
  | Compare (c, t1, t2) ->
    SS.union (free_of_term t1) (free_of_term t2)
  | Subst ((i1, i2), p) -> (* XXX variable capture *)
    SS.add i1 (SS.remove i2 (free_of_phi p))

let fresh = ref 0
let fresh_id free =
  let rec fresh_next () =
    let next = "v"^(string_of_int !fresh) in
    if SS.mem next free then
      let _ = fresh := (!fresh + 1) in
      fresh_next ()
    else next
  in
  fresh_next ()

(* all variables free *)
let rec expr_of_term = function
  | True -> "true"
  | False -> "false"
  | Name i -> i
  | FApp (i, tt) -> (* XXX need to recursively let bind *)
    let aa = tt
      |> List.map expr_of_term
      |> String.concat ","
    in
    i^"("^aa^")"

let expr_of_cmp = function
  | Eq -> "=="
  | Neq -> "!="
  | Lt -> "<"
  | Gt -> ">"
  | Le -> "<="
  | Ge -> ">="

let rec expr_of_phi = function
  | Term t -> expr_of_term t
  | Forall (ii, p) -> failwith "forall NYI"
  | Exists (ii, p) -> failwith "exists NYI"
  | Conjunct (p1, p2) ->
    let v' = fresh_id (free_of_phi p2) in
    "let "^v'^": bool = "^(expr_of_phi p1)^" in\n"^
    "let v: bool = "^(expr_of_phi p2)^" in\n"^
    v'^" && v"
  | Disjunct (p1, p2) ->
    let v' = fresh_id (free_of_phi p2) in
    "let "^v'^": bool = "^(expr_of_phi p1)^" in\n"^
    "let v: bool = "^(expr_of_phi p2)^" in\n"^
    v'^" || v"
  | PApp (i, tt) -> (* XXX need to recursively let bind *)
    i^"("^(tt
    |> List.map expr_of_term
    |> String.concat ",")^")"
    (*let tt = List.map expr_of_term tt in
    let lets = tt
      |> List.map (fun t ->
        let v = fresh_id SS.empty in
        "let "^v^": = t")
    in*)
  | Neg p ->
    "let v: bool = "^(expr_of_phi p)^" in !v"
  | Implies (p1, p2) ->
    let v' = fresh_id (free_of_phi p2) in
    "let "^v'^": bool = "^(expr_of_phi p1)^" in\n"^
    "let v: bool = "^(expr_of_phi p2)^" in\n"^
    "let nv': bool = !"^v'^" in\n"^
    "nv' || v"
  | Compare (c, t1, t2) ->
    let v' = fresh_id (free_of_term t2) in
    "let "^v'^": bool = "^(expr_of_term t1)^" in\n"^
    "let v: bool = "^(expr_of_term t2)^" in\n"^
    v'^" "^(expr_of_cmp c)^" v"
  | Subst ((i1, i2), p) -> "subst NYI"

let spec_of_binding (i, g) =
  match g with
  | Bit -> failwith "bit binding NYI"
  | Loc -> failwith "loc binding NYI"
  | Ghost -> "ghost "^i

let spec_of_block (i, pre, post) =
  "(* block "^i^"*)\n"^
  "pre: "^(expr_of_phi pre)^"\n"^
  "post: "^(expr_of_phi post)^"\n"

let spec_of_ast (tds, bds, pds, fds, axs, bs) =
  (* skip: typedecls, binds, preds, funs, axioms *)
  (* XXX just emitting ghost variable declarations for cassiopeia spec *)
  (List.map spec_of_binding bds @
  (* XXX no multiblock now: invoke only on singleton lists *)
  List.map spec_of_block bs)
  |> String.concat "\n"
