open Util
open Ast

module PA = Prettyast
module P  = Printf

type casp_collected = {
  types : typ StringMap.t;                    (* type aliases *)
  lets : (typ * expr) StringMap.t;            (* pure let bindings *)
  letstates : (typ * bits) StringMap.t;       (* state definitions *)
  defs : (arg list * typ * expr) StringMap.t; (* pure function defs *)
  defss : (arg list * stmt) StringMap.t;      (* subroutine defs *)
  defops : (arg list * stmt) StringMap.t;     (* operation defs *)
}

type casp_subbed = {
  lets : (typ * expr) SM.t;
  letstates : (typ * bits) SM.t;
  defs : (arg list * typ * expr) SM.t;
  defss : (arg list * stmt) SM.t;
  defops : (arg list * stmt) SM.t;
}

type casp_type_checked = {
  lets : expr SM.t;
  letstates : bits SM.t;
  defs : (id list * expr) SM.t;
  defss : (id list * stmt) SM.t;
  defops : (arg list * stmt) SM.t;
}

type casp_resolved = {
  lets : atomic SM.t;
  letstates : bits SM.t;
  defs : (id list * expr) SM.t;
  defss : (id list * stmt) SM.t;
  defops : (arg list * stmt) SM.t;
}
