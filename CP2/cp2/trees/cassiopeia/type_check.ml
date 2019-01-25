open Util
open Ast
open Reps

module PA = Prettyast
module P  = Printf

let print_verbose: (string -> unit) ref = ref (fun s -> ())
let print_dump: (string -> unit) ref = ref (fun s -> ())

(* TODO add error locations back *)

(* very simple type inference logic *)
(* easier since users cannot yet construct polymorphic terms *)
(* alternative: just pass the return type into each expr check *)

(* metatypes used internally by the checker *)
(* actually IntTerm is a term *)
(* free variables are implicitly quantified *)
type metatyp =
  | UnitType
  | ConcreteType of typ
  | VariableType of id
  (* index argument for types varying with length *)
  | IntIndex of id
  | IntTerm of BI.t
  (* variable-length bitvecs and locations *)
  | BitvecFamily of id
  | BitvecLocFamily of id
  (* function is recursively defined but
     we currently avoid higher-order functions *)
  | FunctionType of metatyp list * metatyp

let rec string_of_metatyp = function
  | UnitType -> "()"
  | ConcreteType t -> PA.string_of_typ t
  | VariableType s -> "weak("^s^")"
  | IntIndex s -> "("^s^" : int)"
  | IntTerm i -> BI.string_of_big_int i
  | BitvecFamily s -> s^" bit"
  | BitvecLocFamily s -> s^" bit loc"
  | FunctionType (tt, t) ->
    let s = tt @ [t]
      |> List.map string_of_metatyp
      |> String.concat "->"
    in
    "function "^s

(* lift concrete typ to metatyp: convenient shorthands *)
let lift t = ConcreteType t

(* try to turn metatyp back into concrete typ *)
let lower t =
  match t with
  | ConcreteType t' -> t'
  | IntTerm _ -> IntType
  | _ -> failwith ("could not lower metatype "^(string_of_metatyp t))

(* get the set of free variables appearing in t *)
let rec free t =
  match t with
  | VariableType s -> SS.singleton s
  | IntIndex i -> SS.singleton i
  | BitvecFamily s -> SS.singleton s
  | BitvecLocFamily s -> SS.singleton s
  | FunctionType (tt, t) -> tt
    |> List.map free
    |> List.fold_left SS.union SS.empty
    |> SS.union (free t)
  | _ -> SS.empty

(* get a variable name not appearing in a set of free variables *)
let rec fresh f n =
  let next = "id"^(string_of_int n) in
  if SS.mem next f then
    fresh f (n + 1)
  else next

(* type variable environment *)
type subst = {
  typs : metatyp StringMap.t;
  lens : BI.t StringMap.t
}

let sub_empty = { typs = SM.empty; lens = SM.empty }

(* apply a substitution in a type *)
let rec subst_apply (sub : subst) (t : metatyp) =
  match t with
  | UnitType -> UnitType
  | ConcreteType t' -> t
  | VariableType i ->
    let found = SM.find_opt i sub.typs in
    (match found with
    | Some (IntIndex _ as t')
    | Some (IntTerm _ as t')
    | Some (FunctionType _ as t') ->
      failwith ("cannot substitute "^(string_of_metatyp t')^" for "^
                (string_of_metatyp t))
    | Some t' -> t'
    | _ -> t)
  | IntIndex i ->
    (match SM.find_opt i sub.lens with
    | Some l -> IntTerm l
    | _ -> t)
  | IntTerm l -> t
  | BitvecFamily i ->
    (match SM.find_opt i sub.lens with
    | Some l -> ConcreteType (BitvecType (BI.int_of_big_int l))
    | _ -> t)
  | BitvecLocFamily i ->
    (match SM.find_opt i sub.lens with
    | Some l -> ConcreteType (BitvecLocType (BI.int_of_big_int l))
    | _ -> t)
  | FunctionType (tt, t) ->
    FunctionType (List.map (subst_apply sub) tt, subst_apply sub t)

(* combine two substitutions *)
let subst_compose (sub1 : subst) (sub2 : subst) : subst =
  let disjoint_compose i v1 v2 =
    match (v1, v2) with
    | (Some v1, Some v2) ->
      if v1 <> v2 then
        failwith "subst_compose conflict on key t"
      else Some v1
    | (Some v, _) -> Some v
    | (_, Some v) -> Some v
    | (None, None) -> None
  in
  { typs = SM.merge disjoint_compose sub1.typs sub2.typs;
    lens = SM.merge disjoint_compose sub1.lens sub2.lens }

(* Returns: a substitution rendering the given types identical *)
let rec unify t1 t2 =
  let fail () = 
    failwith ("cannot unify "^(string_of_metatyp t1)^
              " and "^(string_of_metatyp t2))
  in
  match (t1, t2) with
  | (UnitType, UnitType) -> sub_empty

  (* dependent indices should be specialized by application *)
  | (IntIndex _, _)
  | (_, IntIndex _) ->
    failwith "caught dependent product in unify"
  | (IntTerm _, _)
  | (_, IntTerm _) ->
    failwith "caught term in unify"

  (* avoid higher order functions *)
  | (VariableType _, FunctionType _)
  | (FunctionType _, VariableType _) -> fail ()

  (* otherwise anything is more constraining; unify arbitrarily *)
  | (VariableType i, t)
  | (t, VariableType i) ->
    { sub_empty with typs = SM.singleton i t }

  (* bitvec and location types: unify only with concrete versions *)
  | (BitvecFamily i, ConcreteType (BitvecType l))
  | (ConcreteType (BitvecType l), BitvecFamily i) ->
    { sub_empty with lens = SM.singleton i (BI.big_int_of_int l) }
  | (BitvecLocFamily i, ConcreteType (BitvecLocType l))
  | (ConcreteType (BitvecLocType l), BitvecLocFamily i) ->
    { sub_empty with lens = SM.singleton i (BI.big_int_of_int l) }

  (* concrete types unify if identical *)
  | (ConcreteType t1', ConcreteType t2') ->
    if t1' = t2' then sub_empty
    else fail ()

  (* functions: args then return type *)
  | (FunctionType (tt1, rt1), FunctionType (tt2, rt2)) ->
    (* unify function args pairwise *)
    let unify_next sub (t1, t2) =
      let t1' = subst_apply sub t1 in
      let t2' = subst_apply sub t2 in
      subst_compose (unify t1' t2') sub
    in
    let s1 =
      try
        List.combine tt1 tt2
        |> List.fold_left unify_next sub_empty
      with Invalid_argument s ->
        failwith ("could not unify functions "^(string_of_metatyp t1)^
                  " and "^(string_of_metatyp t2)^": arg count differs")
    in
    (* unify function return type *)
    let s2 = unify (subst_apply s1 rt1) (subst_apply s1 rt2) in
    subst_compose s1 s2

  | _ -> fail ()

(* Typing context construction and lookup *)

(* Returns: mapping from IDs to the types they're declared as. *)
let type_check_tenv (c : casp_subbed) =
  let collect_let i (t, e) tenv = SM.add i (lift t) tenv in
  let collect_letstate i (t, b) tenv =
    match t with
    | BitvecLocType _ -> SM.add i (lift t) tenv
    | _ ->
      failwith ("letstate "^i^" expected a location "^
                " but got "^(PA.string_of_typ t))
  in
  let collect_def i (aa, t, e) tenv =
    let tt = List.map (fun a -> lift (snd a)) aa in
    SM.add i (FunctionType (tt, lift t)) tenv
  in
  let collect_defs i (aa, s) tenv =
    let tt = List.map (fun a -> lift (snd a)) aa in
    SM.add i (FunctionType (tt, UnitType)) tenv
  in
  (* construct builtin typing context *)
  let tenv = SM.empty
    |> SM.add "true" (lift BoolType)
    |> SM.add "false" (lift BoolType)
    |> SM.add "bv_to_len"
      (FunctionType ([IntIndex "i"; BitvecFamily "n"], BitvecFamily "i"))
    |> SM.add "bv_to_uint"
      (FunctionType ([BitvecFamily "n"], lift IntType))
    |> SM.add "uint_to_bv_l"
      (FunctionType ([IntIndex "i"; lift IntType], BitvecFamily "i"))
  in
  let tenv = SM.fold collect_let c.lets tenv in
  let tenv = SM.fold collect_letstate c.letstates tenv in
  let tenv = SM.fold collect_def c.defs tenv in
  let tenv = SM.fold collect_defs c.defss tenv in
  tenv

let tenv_find tenv i =
  match SM.find_opt i tenv with
  | None -> failwith ("while type checking: id "^i^" not defined")
  | Some t -> t

(* Returns: type of this atomic *)
let type_check_atomic tenv = function
  | Id i -> tenv_find tenv i
  | Int i -> IntTerm i
  | Bit b -> ConcreteType (BitvecType (Bits.width b))
  | True
  | False -> ConcreteType BoolType

(* Returns: type obtained from applying term of type t against
   atomic args aa *)
(* TODO error message catch and handle: esp. with List.combine *)
let check_app tenv ft aa =
  let tt = List.map (type_check_atomic tenv) aa in
  (* construct a specialized fxn type for unify *)
  let spec (at', tt', sub) (a, t) =
    match (a, t) with
    (* sanity-check argument types *)
    | (IntTerm _, _) ->
      failwith "encountered int term in applicative signature"
    | (_, IntIndex _) ->
      failwith "encountered index as type of atomic"
    (* specialize an index *)
    | (IntIndex i, IntTerm l) ->
      (at', tt', { sub with lens = SM.add i l sub.lens })
    | (IntIndex _, ConcreteType IntType) ->
      failwith "cannot specialize dependent index without value"
    | (IntIndex _, _) ->
      failwith "cannot specialize dependent index with non-int"
    (* replace int terms with int type *)
    | (_, IntTerm _) ->
      (a :: at', (ConcreteType IntType) :: tt', sub)
    (* pass other values through *)
    | _ -> (a :: at', t :: tt', sub)
  in
  match ft with
  | FunctionType (at, rt) ->
    (* first, specialize dependent indices *)
    let (at', tt', sub) =
      try
        List.combine at tt
        |> List.fold_left spec ([], [], sub_empty)
      with Invalid_argument s ->
        failwith ("wrong number of arguments to "^
                  (string_of_metatyp ft)^": got "^
                  (string_of_int (List.length tt))^", expected "^
                  (string_of_int (List.length at)))
    in
    let fresh_t = fresh (free ft) 0 in
    let spec_ft = subst_apply sub (FunctionType (at', rt)) in
    (* now, unify remaining free variables *)
    let free_ft = FunctionType (tt', VariableType fresh_t) in
    let sub = unify spec_ft free_ft in
    subst_apply sub (VariableType fresh_t)
  | _ ->
    let st = tt
      |> List.map string_of_metatyp
      |> String.concat ","
    in
    failwith ("cannot apply "^(string_of_metatyp ft)^" to ("^st^")")

(* name_of functions provide descriptive appellations for error messages. *)

let name_of_unop = function
  | Neg -> "Negation"
  | LogNot -> "Logical Not"
  | BitNot -> "Bitwise Not"

let name_of_binop = function
  | Add -> "Add"
  | Sub -> "Sub"
  | Mul -> "Mul"
  | Div -> "Div"
  | Pow -> "Pow"
  | Eq -> "Eq"
  | Neq -> "Neq"
  | BLt -> "Bitvec Lt"
  | Lt -> "Lt"
  | Gt -> "Gt"
  | LShift -> "LShift"
  | RShift -> "RShift"
  | LogAnd -> "Logical And"
  | LogOr -> "Logical Or"
  | LogXor -> "Logical Xor"
  | BitAnd -> "Bitwise And"
  | BitOr -> "Bitwise Or"
  | BitXor -> "Bitwise Xor"

let name_of_typ = function
  | BitvecType i -> "bitvector"
  | BitvecLocType i -> "location"
  | BoolType -> "boolean"
  | IntType -> "integer"
  | _ -> failwith "alias type in type check pass?"

(* Returns: type of this expr *)
let rec type_check_expr tenv = function
  | Atomic a -> lower (type_check_atomic tenv a)
  | Deref i -> type_check_expr_deref tenv i
  | Load (a1, a2) -> type_check_expr_load tenv a1 a2
  | Index (i, a) -> type_check_expr_index tenv i a
  | Slice (i, a1, a2) -> type_check_expr_slice tenv i a1 a2
  | Unop (u, a) -> type_check_expr_unop tenv u a
  | Binop (a1, b, a2) -> type_check_expr_binop tenv a1 b a2
  | App (i, aa) -> type_check_expr_app tenv i aa
  | LetE (i, t, e1, e2) -> type_check_expr_lete tenv i t e1 e2
  | IfE (i, e1, e2) -> type_check_expr_ife tenv i e1 e2

and type_check_expr_deref tenv i =
  let t = tenv_find tenv i in
  match t with
  | ConcreteType (BitvecLocType l) -> BitvecType l
  | _ ->
    failwith ("Deref expected location but "^i^" is of type "^
              (PA.string_of_typ (lower t)))

and type_check_expr_load tenv a1 a2 =
  let t1 = type_check_atomic tenv a1 in
  let t2 = type_check_atomic tenv a2 in
  match (lower t1, t2) with
  | (IntType, IntTerm i) -> BitvecType ((BI.int_of_big_int i) * 8)
  | (IntType, ConcreteType IntType) ->
    failwith "could not statically determine Load length: sorry!"
  | (_, _) ->
    failwith ("Load expected [int, int] but got ["^
              (PA.string_of_typ (lower t1))^","^
              (PA.string_of_typ (lower t2))^"]")

and type_check_expr_index tenv i a =
  let (t, t') = (tenv_find tenv i, type_check_atomic tenv a) in
  match (t, t') with
  | (ConcreteType (BitvecType l), IntTerm i) ->
    let i = BI.int_of_big_int i in
    if 0 <= i && i < l then BoolType
    else failwith ("Index by out-of-bounds constant: bit "^
                  (string_of_int i)^" of "^(string_of_int l)^" bits")
  (* index not always statically determined: slight danger *)
  | (ConcreteType (BitvecType l), ConcreteType IntType) ->
    BoolType
  | (ConcreteType (BitvecType _), _) ->
      failwith ("Index expected integer but got "^
                (PA.string_of_atomic a))
  | (_, _) ->
      failwith ("Index expected bitvector but "^i^
                " is of type "^(PA.string_of_typ (lower t)))

and type_check_expr_slice tenv i a1 a2 =
  let t = tenv_find tenv i in
  let t1 = type_check_atomic tenv a1 in
  let t2 = type_check_atomic tenv a2 in
  match (t, t1, t2) with
  | (ConcreteType (BitvecType l), IntTerm i1, IntTerm i2) ->
    (* type depends on length---we only handle constants *)
    let i1 = BI.int_of_big_int i1 in
    let i2 = BI.int_of_big_int i2 in
    if 0 <= i1 && i1 < i2 && i2 <= l then
      BitvecType (i2 - i1)
    else
      failwith ("Slice got invalid constant args: "^
                "["^(string_of_int i1)^":"^(string_of_int i2)^"]")
  | (ConcreteType (BitvecType l), IntTerm _, ConcreteType IntType)
  | (ConcreteType (BitvecType l), ConcreteType IntType, IntTerm _)
  | (ConcreteType (BitvecType l), ConcreteType IntType, ConcreteType IntType) ->
    failwith ("could not statically determine Slice length: sorry!")
  | (ConcreteType (BitvecType l), _, _) ->
    failwith ("Slice of "^i^" expected integer parameters but got "^
              "["^(PA.string_of_atomic a1)^":"^(PA.string_of_atomic a2)^"]")
  | (_, _, _) ->
    failwith ("Slice expected bitvector but "^i^
              " is of type "^(PA.string_of_typ (lower t)))

and type_check_expr_unop tenv u a =
  let check t' rt = lower (check_app tenv (FunctionType ([t'], rt)) [a]) in
  match u with
  | Neg -> check (lift IntType) (lift IntType)
  | LogNot -> check (lift BoolType) (lift BoolType)
  | BitNot -> check (BitvecFamily "n") (BitvecFamily "n")

and type_check_expr_binop tenv a1 b a2 =
  let check (t1', t2') rt =
    lower (check_app tenv (FunctionType ([t1'; t2'], rt)) [a1; a2])
  in
  match b with
  (* integer operations *)
  | Add
  | Sub
  | Mul
  | Div
  | Pow -> check (lift IntType, lift IntType) (lift IntType)
  (* equality comparisons need same type *)
  | Eq
  | Neq -> check (VariableType "t", VariableType "t") (lift BoolType)
  (* XXX bitwise ineq *)
  | BLt -> check (BitvecFamily "n", BitvecFamily "n") (lift BoolType)
  (* inequalities operate on integers *)
  | Lt
  | Gt -> check (lift IntType, lift IntType) (lift BoolType)
  (* shifts type as their left operand *)
  | LShift
  | RShift -> check (BitvecFamily "n", lift IntType) (BitvecFamily "n")
  (* logical boolean operations *)
  | LogAnd
  | LogOr
  | LogXor -> check (lift BoolType, lift BoolType) (lift BoolType)
  (* bitwise boolean operations need same length *)
  | BitAnd
  | BitOr
  | BitXor -> check (BitvecFamily "n", BitvecFamily "n") (BitvecFamily "n")

and type_check_expr_app tenv i aa =
  (* type the arguments *)
  let t = tenv_find tenv i in
  lower (check_app tenv t aa)

and type_check_expr_lete tenv i t e1 e2 =
  (* 1. type of e1 should match t *)
  (* 2. e2 should typecheck with extended typing context *)
  let t' = type_check_expr tenv e1 in
  if t = t' then
    type_check_expr (SM.add i (lift t') tenv) e2
  else
    failwith ("LetE declared with type "^(PA.string_of_typ t)^
              " but got "^(PA.string_of_typ t'))

and type_check_expr_ife tenv i e1 e2 =
  let t = lower (tenv_find tenv i) in
  let t1 = type_check_expr tenv e1 in
  let t2 = type_check_expr tenv e2 in
  match t with
  | BoolType ->
    if t1 = t2 then t1
    else failwith ("IfE requires same-type branches but got "^
                  (PA.string_of_typ t1)^" and "^(PA.string_of_typ t2))
  | _ -> failwith ("IfE expected boolean but "^i^
                  " is of type "^(PA.string_of_typ t))

(* Type check a stmt against a typing context. *)
let rec type_check_stmt tenv = function
    Skip -> ()
  | Err -> ()
  | Assert e -> ()
  | Seq (s1, s2) ->
    type_check_stmt tenv s1;
    type_check_stmt tenv s2; ()
  | Assign (i, e) -> type_check_stmt_assign tenv i e
  | Store (a1, a2, e) -> type_check_stmt_store tenv a1 a2 e
  | For (i, a1, a2, s) -> type_check_stmt_for tenv i a1 a2 s
  | Call (i, aa) -> type_check_stmt_call tenv i aa
  | LetS (i, t, e, s) -> type_check_stmt_lets tenv i t e s
  | IfS (i, s1, s2) -> type_check_stmt_ifs tenv i s1 s2

and type_check_stmt_assign tenv i e =
  let t = lower (tenv_find tenv i) in
  let t' = type_check_expr tenv e in
  match (t, t') with
  | (BitvecLocType l1, BitvecType l2) ->
    if l1 = l2 then ()
    else
      failwith ("len of state "^i^" does not match len of expr in assign: "^
                "state "^(string_of_int l1)^", "^
                "expr "^(string_of_int l2))
  | (BitvecLocType _, _) ->
    failwith ("type of state "^i^" does not match type of expr in assign: "^
              "state "^(PA.string_of_typ t)^", "^
              "expr "^(PA.string_of_typ t'))
  | _ ->
    failwith ("id "^i^" is not a location: got "^ (PA.string_of_typ t))

and type_check_stmt_store tenv a1 a2 e =
  let t1 = type_check_atomic tenv a1 in
  let t2 = type_check_atomic tenv a2 in
  let t' = type_check_expr tenv e in
  match (lower t1, t2, t') with
  | (IntType, IntTerm i, BitvecType l) ->
    let i = BI.int_of_big_int i in
    if i * 8 = l then ()
    else
      failwith ("len of store does not match len of bitvec: "^
                "expected "^(string_of_int (i * 8))^
                ", got "^(string_of_int l))
  | (IntType, IntTerm i, _) ->
    failwith ("Store expected bitvector, got "^(PA.string_of_typ (lower t2)))
  | (IntType, ConcreteType IntType, _) ->
    failwith "could not statically determine Store length: sorry!"
  | (_, _, _) ->
    failwith ("Store expected [int, int], got ["^
              (PA.string_of_typ (lower t1))^","^
              (PA.string_of_typ (lower t2))^"]")

and type_check_stmt_for tenv i a1 a2 s =
  let t1 = lower (type_check_atomic tenv a1) in
  let t2 = lower (type_check_atomic tenv a2) in
  match (t1, t2) with
  | (IntType, IntType) ->
    type_check_stmt (SM.add i (lift IntType) tenv) s
  | _ ->
    failwith ("for loop requires integer limits but got ["^
              (PA.string_of_atomic a1)^"..."^(PA.string_of_atomic a2))

and type_check_stmt_call tenv i aa =
  let t = tenv_find tenv i in
  if check_app tenv t aa = UnitType then ()
  else
    failwith ("called identifier "^i^" is not bound to a subroutine")

and type_check_stmt_lets tenv i t e s =
  let t' = type_check_expr tenv e in
  if t = t' then
    type_check_stmt (SM.add i (lift t) tenv) s
  else
    failwith ("LetS declared with type "^(PA.string_of_typ t)^
              " but got "^(PA.string_of_typ t'))

and type_check_stmt_ifs tenv i s1 s2 =
  let t = lower (tenv_find tenv i) in
  match t with
  | BoolType ->
    type_check_stmt tenv s1; type_check_stmt tenv s2
  | _ -> failwith ("IfS expected boolean but "^i^
                  " is of type "^(PA.string_of_typ t))

(* Type check lets against a typing context. *)
let type_check_lets tenv lets =
  let type_check_let i (t, e) =
    let expr_t = type_check_expr tenv e in
    if t <> expr_t then
      failwith ("type of let declaration "^i^" does not match type of expr\n"^
                "declared: "^(PA.string_of_typ t)^"\n"^
                "found: "^(PA.string_of_typ expr_t)^"\n")
    else ()
  in
  SM.iter type_check_let lets

let type_check_letstates tenv letstates =
  let type_check_letstate i (t, b) =
    let t' = lower (type_check_atomic tenv (Bit b)) in
    match (t, t') with
    | (BitvecLocType l1, BitvecType l2) ->
      if l1 = l2 then ()
      else
        failwith ("length of letstate declaration "^i^
                  "does not match length of initial state bitvector\n"^
                  "declared: "^(string_of_int l1)^"\n"^
                  "found: "^(string_of_int l2))
    | (BitvecLocType _, _) ->
      failwith ("letstate declaration "^i^" expected bitvector initial state,"^
                " got "^(PA.string_of_typ t'))
    | (_, _) ->
      failwith ("letstate declaration "^i^" expected location type, got "^
                (PA.string_of_typ t))
  in
  SM.iter type_check_letstate letstates

let type_check_defs tenv defs =
  let type_check_def i (aa, t, e) =
    let add tenv (i, t) = SM.add i (lift t) tenv in
    let tenv' = List.fold_left add tenv aa in
    let t' = type_check_expr tenv' e in
    if t <> t' then
      failwith ("type of def "^i^" does not match type of expr\n"^
                "declared return type: "^(PA.string_of_typ t)^
                "resolved return type: "^(PA.string_of_typ t'))
    else ()
  in
  SM.iter type_check_def defs

let type_check_defss tenv defss =
  let type_check_defs i (aa, s) =
    let add_arg tenv (i, t) = SM.add i (lift t) tenv in
    let tenv' = List.fold_left add_arg tenv aa in
    type_check_stmt tenv' s
  in
  SM.iter type_check_defs defss

let type_check_defops tenv defops =
  let type_check_defop i (aa, s) =
    let add_arg tenv (i, t) = SM.add i (lift t) tenv in
    let tenv' = List.fold_left add_arg tenv aa in
    type_check_stmt tenv' s
  in
  SM.iter type_check_defop defops

let type_check (c : casp_subbed) : casp_type_checked =
  (* get typing context by assuming declarations *)
  let tenv = type_check_tenv c in
  (* check types *)
  type_check_lets tenv c.lets;
  type_check_letstates tenv c.letstates;
  type_check_defs tenv c.defs;
  type_check_defss tenv c.defss;
  type_check_defops tenv c.defops;
  (* strip types off *)
  let strip_lets = SM.map snd c.lets in
  let strip_letstates = SM.map snd c.letstates in
  let strip_defs = SM.map (fun (aa, _, e) -> (List.map fst aa, e)) c.defs in
  let strip_defss = SM.map (fun (aa, s) -> (List.map fst aa, s)) c.defss in
  let strip_defops = (*SM.map (fun (aa, s) -> (List.map fst aa, s))*) c.defops in
  { lets = strip_lets; letstates = strip_letstates;
    defs = strip_defs; defss = strip_defss; defops = strip_defops }
