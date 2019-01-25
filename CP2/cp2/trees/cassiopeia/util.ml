module Bat = Batteries
module S   = BatSys
module P   = BatPrintf
module BI  = BatBig_int
module R   = BatText

open BatPervasives
open BatFormat

module IntMap = Map.Make(struct type t=int let compare=compare end)
module StringMap  = Map.Make(String)
module Big_intMap = Map.Make(BI)
module BitsMap    = Map.Make(Bits)

module IM  = IntMap
module SM  = StringMap
module BIM = Big_intMap
module BM  = BitsMap

module StringSet  = Set.Make(String)
module SS  = StringSet

type rope = R.t
type bint = BI.t

let ( ++ )  = (^)
let ( +++ ) = R.(^^^)
let ( ++. ) s =
  string_of_int %> (++) s

let rla rl a = rl := a :: !rl 
let arl rl a = rl := !rl @ [a]

let flap f l =
  l |> List.map f |> List.flatten

let string_of_list d f l =
  l |> List.map f |> String.concat d

let is_uniform_list = function
  | [] | [_] -> true
  | x :: t   -> List.for_all (fun y -> y = x) t

let maybe_filter = BatList.filter_map

let zip   = List.combine
let unzip = List.split

let string_of_bint = BI.to_string
let bitstring_of_bint b = "0b" ++ BI.to_string_in_binary b
let hexstring_of_bint b = "0x" ++ BI.to_string_in_hexa b
let bint_of_string = BI.of_string

let bint_clamp w n =
  BI.mod_big_int n (BI.power_int_positive_big_int 2 w)

type wrapper =
  | PAREN
  | BRACKET
  | BRACE
  | COLON

let ch_wrap s = function
  | PAREN   -> "(" ++ s ++ ")"
  | BRACKET -> "[" ++ s ++ "]"
  | BRACE   -> "{" ++ s ++ "}"
  | COLON   -> ":" ++ s ++ ":"

