open Util
open Ast
open Reps

module PA = Prettyast
module P  = Printf

let print_verbose: (string -> unit) ref = ref (fun s -> ())
let print_dump: (string -> unit) ref = ref (fun s -> ())

(* PASS 1 - collect declarations *)

(* Returns: a casp_collected containing all the decls.
   Duplicate declarations forbidden. *)
let collect (c : decl list) : casp_collected =
  let builtin_defs =
    ["true"; "false"; "bv_to_len"; "bv_to_uint"; "uint_to_bv_l"; "Mem"]
  in
  let check_id (cc : casp_collected) i =
    if SM.mem i cc.lets then
      failwith ("id "^i^" is already bound to a value")
    else if SM.mem i cc.letstates then
      failwith ("id "^i^" is already bound to a state")
    else if SM.mem i cc.defs then
      failwith ("id "^i^" is already bound to a function")
    else if SM.mem i cc.defss then
      failwith ("id "^i^" is already bound to a subroutine")
    else if List.mem i builtin_defs then
      failwith ("id "^i^" conflicts with a built-in")
    else ()
  in
  let collect_decl (cc : casp_collected) = function
  | DeclType (i, t) ->
    if SM.mem i cc.types then
      failwith ("type alias "^i^" already defined")
    else { cc with types = SM.add i t cc.types }
  | DeclLet (i, t, e) ->
    check_id cc i; { cc with lets = SM.add i (t, e) cc.lets }
  | DeclLetstate (i, t, b) ->
    check_id cc i; { cc with letstates = SM.add i (t, b) cc.letstates }
  | DeclDef (i, aa, t, e) ->
    check_id cc i; { cc with defs = SM.add i (aa, t, e) cc.defs }
  | DeclDefs (i, aa, s) ->
    check_id cc i; { cc with defss = SM.add i (aa, s) cc.defss }
  | DeclDefop (i, aa, _, s) ->
    if SM.mem i cc.defops then
      failwith ("operation "^i^" is already defined")
    else { cc with defops = SM.add i (aa, s) cc.defops }
  in
  let empty = { types = SM.empty;
                lets = SM.empty; letstates = SM.empty; defs = SM.empty;
                defss = SM.empty; defops = SM.empty } in
  List.fold_left collect_decl empty c

(* PASS 2 - substitute type aliases *)

(* Returns: a mapping from type aliases to types.
 * Resolve type aliases to concrete types.
 * No type will be either AliasType or AliasLocType. *)
let alias_sub_resolve (types : typ SM.t) =
  (* Resolve an alias to a concrete type.
     Given: (resolved, a)
     - the set of so-far resolved aliases (an Ast.typ StringMap)
     - the alias to resolve (a string)
     Returns: (resolved, type)
     - the set of resolved aliases (a StringMap) after resolving this alias
     - the type that the given alias resolved to (Ast.typ) *)
  let rec resolve resolved a =
    match SM.find_opt a resolved with
    (* not yet resolved *)
    | None -> lookup resolved a
    (* circular dependency - we use presence in the map
       instead of a separate visited set *)
    | Some (AliasType _)
    | Some (AliasLocType _) ->
      failwith ("circular dependency on type alias "^a)
    (* already resolved *)
    | Some t -> (resolved, t)
  (* Look up an alias in the declarations.
     Returns: (resolved, type) as above. *)
  and lookup resolved a =
    match SM.find_opt a types with
    | None -> failwith ("unknown type alias "^a)
    | Some t ->
      (match t with
      | BitvecType _
      | BitvecLocType _
      | BoolType
      | IntType -> (SM.add a t resolved, t)
      | AliasType a' ->
        let (resolved', t') = resolve (SM.add a t resolved) a' in
        (SM.add a t' resolved', t')
      | AliasLocType a' ->
        let (resolved', t') = resolve (SM.add a t resolved) a' in
        (match t' with
        | BitvecType len -> let t'' = BitvecLocType len in
          (SM.add a t'' resolved', t'')
        | _ -> failwith ("location type expected bitvector but type alias "
                        ^a^" is of type "^(PA.string_of_typ t'))))
  in
  SM.fold (fun i t res -> fst (resolve res i)) types SM.empty

(* Concretize any types appearing in an expr or stmt. *)
let rec alias_sub_expr concrete e =
  match e with
  | Atomic _
  | Deref _
  | Load _
  | Index _
  | Slice _
  | Unop _
  | Binop _
  | App _ -> e
  | LetE (i, t, e1, e2) ->
    LetE (i, concrete t, alias_sub_expr concrete e1, alias_sub_expr concrete e2)
  | IfE (i, e1, e2) ->
    IfE (i, alias_sub_expr concrete e1, alias_sub_expr concrete e2)

let rec alias_sub_stmt concrete s =
  match s with
  | Skip
  | Err -> s
  | Assert e ->
    Assert (alias_sub_expr concrete e)
  | Seq (s1, s2) ->
    Seq (alias_sub_stmt concrete s1, alias_sub_stmt concrete s2)
  | Assign (i, e) ->
    Assign (i, alias_sub_expr concrete e)
  | Store (a1, a2, e) ->
    Store (a1, a2, alias_sub_expr concrete e)
  | For (i, a1, a2, s) ->
    For (i, a1, a2, alias_sub_stmt concrete s)
  | Call (i, aa) ->
    Call (i, aa)
  | IfS (i, s1, s2) ->
    IfS (i, alias_sub_stmt concrete s1, alias_sub_stmt concrete s2)
  | LetS (i, t, e, s) ->
    LetS (i, concrete t, alias_sub_expr concrete e, alias_sub_stmt concrete s)

(* Returns: a casp_subbed, where all alias types have been substituted
   with the corresponding concrete type. *)
let alias_sub (c : casp_collected) : casp_subbed =
  let aliases = alias_sub_resolve c.types in
  let concrete t =
    match t with
    | BitvecType _
    | BitvecLocType _
    | BoolType
    | IntType -> t
    | AliasType a ->
      (match SM.find_opt a aliases with
      | None -> failwith ("unknown type alias "^a)
      | Some t -> t)
    | AliasLocType a ->
      (match SM.find_opt a aliases with
      | None -> failwith ("unknown type alias "^a)
      | Some (BitvecType len) -> BitvecLocType len
      | Some t' -> failwith ("location type expected bitvector but type alias "
                            ^a^" is of type "^(PA.string_of_typ t')))
  in
  let concrete_let (t, e) = (concrete t, alias_sub_expr concrete e) in
  let concrete_letstate (t, b) = (concrete t, b) in
  let concrete_def (aa, t, e) =
    let concrete_aa = List.map (fun (i, t) -> (i, concrete t)) aa in
    (concrete_aa, concrete t, alias_sub_expr concrete e)
  in
  let concrete_defs (aa, s) =
    let concrete_aa = List.map (fun (i, t) -> (i, concrete t)) aa in
    (concrete_aa, alias_sub_stmt concrete s)
  in
  let concrete_defop (aa, s) =
    let concrete_aa = List.map (fun (i, t) -> (i, concrete t)) aa in
    (concrete_aa, alias_sub_stmt concrete s)
  in
  { lets = SM.map concrete_let c.lets;
    letstates = SM.map concrete_letstate c.letstates;
    defs = SM.map concrete_def c.defs;
    defss = SM.map concrete_defs c.defss;
    defops = SM.map concrete_defop c.defops }

(* PASS 3 - type-checking *)

let type_check = Type_check.type_check

(* PASS 4 - first-pass eval *)

let check_depends deps =
  let rec check visited i =
    if SS.mem i visited then
      failwith ("circular dependency at def/defs "^i)
    else
      if List.mem i ["bv_to_len"; "bv_to_uint"; "uint_to_bv_l"] then ()
      else
        match SM.find_opt i deps with
        | None ->
          failwith ("type check fail: dependency on undefined def/defs "^i)
        | Some d -> SS.iter (check (SS.add i visited)) d; ()
  in
  let checked = SS.empty in
  List.fold_left (fun checked (i, _) ->
    let _ = check SS.empty i in
    SS.add i checked) checked (SM.bindings deps)

let resolve_check_defs defs =
  let rec check_def_expr = function
    | App (i, aa) -> SS.singleton i
    | LetE (i, t, e1, e2) ->
      SS.union (check_def_expr e1) (check_def_expr e2)
    | IfE (i, e1, e2) ->
      SS.union (check_def_expr e1) (check_def_expr e2)
    | _ -> SS.empty
  in
  let check_def (ii, e) = check_def_expr e in
  SM.map check_def defs
  |> check_depends

let resolve_check_defss defss =
  let rec check_defs_stmt = function
    | Seq (s1, s2) ->
      SS.union (check_defs_stmt s1) (check_defs_stmt s2)
    | For (i, a1, a2, s) -> check_defs_stmt s
    | Call (i, aa) -> SS.singleton i
    | LetS (i, t, e, s) -> check_defs_stmt s
    | IfS (i, s1, s2) ->
      SS.union (check_defs_stmt s1) (check_defs_stmt s2)
    | _ -> SS.empty
  in
  let check_defs (ii, s) = check_defs_stmt s in
  SM.map check_defs defss
  |> check_depends

(* get free variables i.e. env dependencies *)
let free_atomic = function
  | Id i -> SS.singleton i
  | _ -> SS.empty

let rec free_expr defs = function
  | Atomic a -> free_atomic a
  | Deref i -> SS.singleton i
  | Load (a1, a2) ->
    free_atomic a1
    |> SS.union (free_atomic a2)
  | Index (i, a) ->
    free_atomic a
    |> SS.add i
  | Slice (i, a1, a2) ->
    free_atomic a1
    |> SS.union (free_atomic a2)
    |> SS.add i
  | Unop (u, a) -> free_atomic a
  | Binop (a1, b, a2) ->
    free_atomic a1
    |> SS.union (free_atomic a2)
  | App (i, aa) ->
    (* find free variables referred to in function body *)
    let (ii, e) = match SM.find_opt i defs with
      | None -> failwith ("type check fail: no such pure function "^i)
      | Some (ii, e) -> (ii, e)
    in
    (* note this is unsafe to use on mutually dependent defs *)
    (* get free variables from called function body and strip args *)
    let fxn_free = free_expr defs e in
    let fxn_free = List.fold_left (fun s i -> SS.remove i s) fxn_free ii in
    (* add free variables referred to in function call *)
    List.map free_atomic aa
    |> List.fold_left SS.union SS.empty
    |> SS.union fxn_free
  | LetE (i, t, e1, e2) ->
    (* remove bound i from frees in e2 *)
    let sub_free = SS.remove i (free_expr defs e2) in
    free_expr defs e1
    |> SS.union sub_free
  | IfE (i, e1, e2) ->
    free_expr defs e1
    |> SS.union (free_expr defs e2)
    |> SS.add i

let resolve (c : casp_type_checked) : casp_resolved =
  (* check def and defs circular dependencies *)
  let _ = resolve_check_defs c.defs in
  let _ = resolve_check_defss c.defss in

  (* determine let interdependencies *)
  let depends = SM.map (free_expr c.defs) c.lets in

  (* resolve lets, respecting dependencies *)
  (* c' is a casp_resolved where c'.lets is being built *)
  let rec resolve_let visited (c' : casp_resolved) i =
    let state = Interpret.eval_world c' in
    (* if it's already in the environment, move on *)
    if SM.mem i state.env then
      (visited, c')
    (* if we're trying to resolve it again, we're looping *)
    else if SS.mem i visited then
      failwith ("circular dependency on let bind "^i)
    else
      (* resolve this let *)
      let visited' = SS.add i visited in
      match (SM.find_opt i c.lets, SM.find_opt i depends) with
      | (Some e, Some s) ->
        (* first resolve dependencies *)
        let (visited', c') =
          SS.fold (fun i (v, r) -> resolve_let v r i) s (visited', c')
        in
        (* now resolve the let *)
        (* build stub interpreter state *)
        let state = Interpret.eval_world c' in
        (* evaluate expr and convert result back to atomic *)
        let res = (match Interpret.eval_expr c' state e with
          | Interpret.ValInt i -> Int i
          | Interpret.ValBit b -> Bit b
          | Interpret.ValBool true -> True
          | Interpret.ValBool false -> False
          | Interpret.ValState s -> Id s)
        in
        (visited', { c' with lets = SM.add i res c'.lets })
      | _ -> failwith ("type check fail: no let bind "^i)
  in
  let c' : casp_resolved =
    { lets = SM.empty; letstates = c.letstates;
      defs = c.defs; defss = c.defss; defops = c.defops }
  in
  snd (SM.fold (fun i _ (v, c') -> resolve_let v c' i) c.lets (SS.empty, c'))

let process_casp (c : Ast.decl list) =
  let c = collect c in    (* pass 1: collect declarations *)
  let c = alias_sub c in  (* pass 2: substitute type aliases *)
  let c = type_check c in (* pass 3: type-checking *)
  let c = resolve c in    (* pass 4: first-pass eval *)
  c

let process_prog (c : casp_resolved) (p : Ast.inst list) =
  let state = Interpret.eval_world c in
  (* evaluative check... should carry tenv down *)
  let check_arg_type op (a, t) =
    match (Interpret.eval_atomic state a, t) with
    | (_, AliasType i)
    | (_, AliasLocType i) ->
      failwith ("preprocessing bug: alias type "^i^
                " should have been resolved by now")
    | (ValInt _, IntType) -> ()
    | (ValBit b, BitvecType l) ->
      let w = Bits.width b in
      if w <> l then
        failwith ("in prog: bad type in argument to op "^op^": got "^
                  (string_of_int w)^" bit, expected "^
                  (string_of_int l)^" bit")
      else ()
    | (ValBool _, BoolType) -> ()
    | (ValState i, BitvecLocType l) ->
      (match SM.find_opt i state.reg with (* examine register initial values *)
      | Some b ->
        let w = Bits.width b in
        if w <> l then
          failwith ("in prog: bad type in argument to op "^op^": got "^
                    "register "^i^" of type "^
                    (string_of_int w)^" bit loc, expected "^
                    (string_of_int l)^" bit loc")
        else ()
      | None ->
        failwith ("in prog: bad argument to op "^op^": got non-register "^i))
    | (v, t) ->
      failwith ("in prog: bad type in argument to op "^op^": got "^
                (Interpret.string_of_value v)^", expected type "^
                (PA.string_of_typ t))
  in
  (* check every instruction has correct argument types *)
  let check_inst (i, aa) =
    match SM.find_opt i c.defops with
    | Some (aa', s) ->
      (try
        List.map snd aa' (* get arg types for defop *)
        |> List.combine aa
        |> List.iter (check_arg_type i);
        (i, aa)
      with Invalid_argument s ->
        failwith ("in prog: wrong number of arguments to op "^i^": got "^
                  (string_of_int (List.length aa))^", expected "^
                  (string_of_int (List.length aa'))))
    | None ->
      failwith ("in prog: unknown op "^i)
  in
  List.map check_inst p
