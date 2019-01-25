(* Module for positions in source *)
open Batteries

open BatTuple.Tuple5

module P = Printf

type t = string * int * int * int * int

type pos = t

let file_of  = first
let line_beg = second
let line_end = third
let col_beg  = fourth
let col_end  = fifth

let mk f lb le cb ce = make f lb le cb ce
let none = mk "<none>" 0 0 0 0
let builtin = none

let string_of pos =
  P.sprintf "%s:%d,%d-%d,%d"
    (file_of pos)
    (line_beg pos)
    (col_beg  pos)
    (line_end pos)
    (col_end  pos)

let print p =
  string_of p |>
  P.printf "%s"

let lines_of p =
  let b, e = line_beg p, line_end p in
  let _ = assert (e - b >= 0) in
  (b, e - b)

let cols_of p =
  let b, e = col_beg p, col_end p in
  let _ = assert (e - b >= 0) in
  (b, e - b)
