(* bit vector interface to Big_int *)

type t

val bits_compare : t -> t -> int
val compare : t -> t -> int

val zero: int(*width*) -> t

val width: t -> int

val get: t -> Big_int.big_int -> bool
val not: t -> t
val and_: t -> t -> t
val or_: t -> t -> t
val xor: t -> t -> t
val lshift: t -> Big_int.big_int -> t
val rshift: t -> Big_int.big_int -> t
val concat: t -> t -> t

val of_big_int : int(*width*) -> Big_int.big_int -> t
val to_big_int : t -> Big_int.big_int

val of_string : string -> t
val to_string : t -> string
val to_hexstring: t -> string
val to_bitstring: t -> string
