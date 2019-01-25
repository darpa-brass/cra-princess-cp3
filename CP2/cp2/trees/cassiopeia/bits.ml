open Batteries

module BI = BatBig_int

(* bit vector interface to Big_int *)

let big_pow = BI.power_int_positive_int

(* width, value *)
type t = Bits of int * BI.big_int

let zero w = Bits (w, BI.zero_big_int)

let width (Bits (w, _)) = w

(*
 * private operations
 *)

let clamp w n =
  BI.mod_big_int n (big_pow 2 w)

(*
 * comparison
 *)

let bits_compare (Bits (w1, n1)) (Bits (w2, n2)) =
  if w1 <> w2 then w1 - w2
  else BI.sign_big_int (BI.sub_big_int n1 n2)

let compare = bits_compare

(*
 * operations
 *)

let get (Bits (w, n)) d = 
  (* assert (d < w); *)
  let mask = BI.power_int_positive_big_int 2 d in
  not (BI.eq_big_int (BI.and_big_int n mask) (BI.zero_big_int))

let not (Bits (w, n)) =
  let limit = big_pow 2 w in
  let one = BI.unit_big_int in
  let n' =
     BI.sub_big_int (BI.sub_big_int limit n) one
  in
  Bits (w, n')

let and_ (Bits (w1, n1)) (Bits (w2, n2)) =
  assert (w1 = w2);
  Bits (w1, BI.and_big_int n1 n2)

let or_ (Bits (w1, n1)) (Bits (w2, n2)) =
  assert (w1 = w2);
  Bits (w1, BI.or_big_int n1 n2)

let xor (Bits (w1, n1)) (Bits (w2, n2)) =
  assert (w1 = w2);
  Bits (w1, BI.xor_big_int n1 n2)

let lshift (Bits (w, n)) d =
  let n' = clamp w (BI.shift_left_big_int n (BI.int_of_big_int d)) in
  Bits (w, n')

let rshift (Bits (w, n)) d =
  let n' = clamp w (BI.shift_right_big_int n (BI.int_of_big_int d)) in
  Bits (w, n')

let concat (Bits (w1, n1)) (Bits (w2, n2)) =
  let rhs = lshift (Bits (w1 + w2, n1)) (BI.big_int_of_int w2) in
  or_ rhs (Bits (w1 + w2, n2))

(*
 * conversions
 *)

let of_big_int w n = Bits (w, clamp w n)

let to_big_int (Bits (_, n)) = n

let of_string s =
  assert (String.get s 0 = '0');
  let bitsper =
    match (String.get s 1) with
      'x' | 'X' -> 4
    | 'b' -> 1
    | _ -> assert false
  in
  (* in the following, -2 because of 0x/0b prefix *)
  let width = (String.length s - 2) * bitsper in
  Bits (width, BI.big_int_of_string s)


let to_string (Bits (width, n)) =
  let (base, prefix) =
    if width mod 4 = 0 then (16, "0x")
    else (2, "0b")
  in
  let base = BI.big_int_of_int base in
  let todigit x =
    if x < 10 then string_of_int x
    else String.make 1 (String.get "abcdef" (x - 10))
  in
  let rec todigits x =
     if BI.eq_big_int x BI.zero_big_int then []
     else begin
        let (q, r) = BI.quomod_big_int x base in
        todigit (BI.int_of_big_int r) :: todigits q
     end
  in
  let digits = todigits n in
  match digits with
    [] -> "0"
  | _ -> String.concat "" (List.rev digits)

let to_bitstring (Bits (width, n)) =
  let s = BI.to_string_in_binary n in
  let z = BatString.repeat "0" (width - BatString.length s) in
  "0b" ^ z ^ s

let to_hexstring (Bits (width, n)) =
  let s = BI.to_string_in_hexa n in
  let z = BatString.repeat "0" ((width+3)/4 - BatString.length s) in
  "0x" ^ z ^ s
