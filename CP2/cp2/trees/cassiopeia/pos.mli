type t
type pos = t

val none : t

val mk : string -> int -> int -> int -> int -> t

val builtin : t

val string_of : t -> string

val print : t -> unit

val file_of : t -> string

val lines_of : t -> int * int

val cols_of : t -> int * int

