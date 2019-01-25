open Batteries

open BatTuple.Tuple5
open BatTuple.Tuple2

module BI = BatBig_int
module R  = BatText

let (++) = (^)

type cmp = Eq | Neq | Lt | Gt | Le | Ge

type id  = string

type subst = id * id

(* grounded machine types. alewife types are not dependent *)
type gndtyp = Bit | Loc | Ghost

type typ =
  | Bool
  | MachType of gndtyp
  | AbsType of  id     (* interpreted only by the machine model *)
  | FunType of  typ list * typ

    (* MK: at some point we need class types. maybe call them caps
     * they need to have an abstract notion of memory layout
     * (or just an abstract ordering relation between fields *)

type term =
  | True 
  | False
  | Name of id
  | FApp of id * term list

type phi =
  | Term of term
  | Forall of id list * phi
  | Exists of id list * phi
  | Conjunct of phi * phi
  | Disjunct of phi * phi
  | PApp of id * term list
  | Neg of phi
  | Implies of phi * phi
  | Compare of cmp * term * term
  | Subst of subst * phi

type type_decl = id * typ

type targ = id * typ 

type bind_decl = id * gndtyp

type pred_decl = id * targ list

type fun_decl = id * targ list * typ

type axiom = phi

type block = id * phi * phi

type ast = type_decl list *
           bind_decl list *
           pred_decl list *
           fun_decl  list *
           axiom     list *
           block     list

type t = ast

let string_of_cmp = function
  | Eq -> "="
  | Neq -> "!="
  | Lt -> "<"
  | Gt -> ">"
  | Le -> "<="
  | Ge -> ">="

let string_of_ids d ii =
  List.fold_left (fun s i -> i ++ d ++ s) "" ii

let string_of_gndtyp = function
  | Bit -> "bit"
  | Loc -> "loc"
  | Ghost -> "ghost"

let string_of_typ = function
  | Bool -> "bool"
  | MachType g ->
      g |> string_of_gndtyp |>
      (fun x -> "machtype " ++ x)
  | AbsType id -> "abs " ++ id

let rec string_of_term = function
  | True -> "true"
  | False -> "false"
  | Name id -> id
  | FApp (i, tt) ->
    let tt = tt
      |> List.map string_of_term
      |> String.concat ","
    in
    i ++ "(" ++ tt ++ ")"

let string_of_value = function
  | Term t -> string_of_term t
  | _ -> assert false

let rec string_of_phi = function
  | Term t ->
      string_of_term t
  | Forall (ids, phi) ->
      let ids = string_of_ids "," ids in
      let phi = string_of_phi phi in
      "forall " ++ ids ++ ". " ++ phi
  | Exists (ids, phi) ->
      let ids = string_of_ids "," ids in
      let phi = string_of_phi phi in
      let _   = failwith
        "Existentials not supported" in
      "exists " ++ ids ++ ". " ++ phi
  | Conjunct (p1, p2) ->
      let (p1, p2) = (string_of_phi p1, string_of_phi p2) in
      p1 ++ " && " ++ p2
  | Disjunct (p1, p2) ->
      let (p1, p2) = (string_of_phi p1, string_of_phi p2) in
      p1 ++ " || " ++ p2
  | PApp (i, tt) ->
      let tt = List.fold_left
        (fun s t -> s ++ "," ++ string_of_term t) "" tt in
      i ++ "(" ++ tt ++ ")"
  | Neg (p) ->
      "~ " ++ string_of_phi p
  | Implies (p1, p2) ->
      let (p1, p2) = (string_of_phi p1, string_of_phi p2) in
      p1 ++ " -> " ++ p2
  | Compare (c, t1, t2) ->
      let (c, t1, t2) =
        (string_of_cmp c,
         string_of_term t1,
         string_of_term t2) in
      t1 ++ " " ++ c ++ " " ++ t2
  | Subst ((i1, i2), p) ->
      let p = string_of_phi p in
      "[" ++ i1 ++ "/" ++ i2 ++ "]" ++ p
  | _ -> assert false

let string_of_typedecl (name, ty) =
  "type " ++ name ++ ": " ++ string_of_typ ty

let string_of_targ (name, ty) =
  "(" ++ name ++ ": " ++ string_of_typ ty ++ ")"

let string_of_bind (name, gty) =
  "bind " ++ name ++ " " ++ (string_of_gndtyp gty)

let string_of_pred (id, args) =
  "pred: " ++ id ++ " " ++
     String.concat " " (List.map string_of_targ args)

let string_of_fun (id, args, ty) =
  "fun: " ++ id ++ " " ++
     String.concat " " (List.map string_of_targ args) ++
  " : " ++ string_of_typ ty

let string_of_axiom axiom =
  "axiom:" ++ string_of_phi axiom

let string_of_block (x, pre, post) =
  let (pre, post) = (string_of_phi pre, string_of_phi post) in
  "block " ++ x ++ "{\n" ++
  "pre: " ++ pre ++ "\n" ++
  "post: " ++ post ++ "}\n"
  
let string_of_funct (x, pre, post) =
  let (pre, post) = (string_of_phi pre, string_of_phi post) in
  "funct: " ++ x ++ "{\n" ++
  "pre: " ++ pre ++ "\n"  ++
  "post: " ++ post ++ "}\n"

let string_of_ast (tds, bds, pds, fds, axs, bs) =
   let strings =
      List.map string_of_typedecl tds @
      List.map string_of_bind bds @ 
      List.map string_of_pred pds @
      List.map string_of_fun fds @
      List.map string_of_axiom axs @
      List.map string_of_block bs
   in
   String.concat "\n" strings

let to_string (i, pre, post) = string_of_block (i, pre, post)
