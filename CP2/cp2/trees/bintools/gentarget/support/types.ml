(*
 * Copyright (c) 2016
 *	The President and Fellows of Harvard College.
 *
 * Written by David A. Holland.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *)

(*
 * Does ocaml have something native of this form? I haven't been able to
 * find one.
 *)
type ('a, 'b) emulsion = OIL of 'a | WATER of 'b

(*
 * There are no unsigned integer types in ocaml, I guess because
 * upstream thinks they're inelegant or something. This means that the
 * largest integer type we have is signed 64-bit... which is no good
 * if you have an unsigned 64-bit value.
 *
 * Furthermore, because there's a 128-bit version of riscv and several
 * GPUs/DSPs are 128-bit, we really need to handle unsigned 128-bit
 * values.
 *
 * The path of least resistance is to use the ocaml bignum library.
 * We aren't doing a lot of computations with wide values, so there
 * isn't really any reason to be concerned about inefficiency.
 *
 * (The situation is different in the actual assembler and linker but
 * that's a different problem.)
 *)

(*
 * This is the maximum field or integer type width we let a machine
 * description create.
 *)
let maxintwidth = 128

(*
 * This holds integer values that might overflow "int".
 *)
module Wide = struct
   type t = Big_int.big_int

   (*
    * For some reason everything in Big_int has "big_int" in its
    * name in addition to the module name qualification. Sigh.
    *)

   let zero = Big_int.zero_big_int
   let one = Big_int.unit_big_int

   let of_int (x: int)          = Big_int.big_int_of_int x

   let eq    (x: t) (y: t)      = Big_int.eq_big_int x y
   let eqint (x: t) (y: int)    = eq x (of_int y)
   let iszero (x: t)            = eq x zero

   let lt    (x: t) (y: t)      = Big_int.lt_big_int x y
   let gt    (x: t) (y: t)      = Big_int.gt_big_int x y
   let le    (x: t) (y: t)      = Big_int.le_big_int x y
   let ge    (x: t) (y: t)      = Big_int.ge_big_int x y
   let compare (x: t) (y: t)    = Big_int.compare_big_int x y
   let isneg (x: t)             = lt x zero

   let inc   (x: t)             = Big_int.succ_big_int x
   let dec   (x: t)             = Big_int.pred_big_int x

   let add   (x: t) (y: t)      = Big_int.add_big_int x y
   let sub   (x: t) (y: t)      = Big_int.sub_big_int x y
   let mul   (x: t) (y: t)      = Big_int.mult_big_int x y
   let div   (x: t) (y: t)      = Big_int.div_big_int x y
   let mod_  (x: t) (y: t)      = Big_int.mod_big_int x y

   let neg   (x: t)             = sub zero x
   let to_string (x: t)         = Big_int.string_of_big_int x

   let twoN x = Big_int.power_int_positive_int 2 x

   let rec ilog2 x =
      let k = of_int 0x40000000 in
      if ge x k then 30 + (ilog2 (div x k))
      else Util.ilog2 (Big_int.int_of_big_int x)

   let ones k = dec (twoN k)

end

module StringMap = Map.Make(String)
module StringSet = Set.Make(String)

(* Why doesn't this come with Map? *)
let stringmap_of_list kvs =
   let doadd z (k, v) = StringMap.add k v z in
   List.fold_left doadd StringMap.empty kvs

(* Especially since this *does* come with Set? *)
let stringset_of_list strs =
   StringSet.of_list strs
(*
   let doadd z str = StringSet.add str z in
   List.fold_left doadd StringSet.empty strs
*)

(* stringmap_of_list but with key extraction function instead of pairs *)
let stringmap_of_list_by_key getkey vs =
   let doadd z v = StringMap.add (getkey v) v z in
   List.fold_left doadd StringMap.empty vs

(* Why doesn't this come with Map either? *)
let stringmap_keys m =
   List.map (fun (k, _v) -> k) (StringMap.bindings m)

(* Map.union isn't in the ocaml on debian stale *)
let stringmap_union (f: string -> 'a -> 'a -> 'a option) m1 m2 =
   (* this equivalence is from the docs *)
   let f' k v1 v2 = match v1, v2 with
        None, None -> None
      | Some v, None -> Some v
      | None, Some v -> Some v
      | Some v1', Some v2' -> f k v1' v2'
   in
   StringMap.merge f' m1 m2

(* union over a list of sets *)
let stringset_unionall sets =
   List.fold_left StringSet.union StringSet.empty sets

(* StringMap.mapi in a specific external order *)
(* (caller is responsible for making sure keys has all keys exactly once) *)
let stringmap_mapi_inorder f map keys =
   let once newmap k =
      let v = StringMap.find k map in
      StringMap.add k (f k v) newmap
   in
   List.fold_left once StringMap.empty keys

(* Same, but iter *)
let stringmap_iter_inorder f map keys =
   let once k =
      let v = StringMap.find k map in
      f k v
   in
   List.iter once keys

(* Same, but bindings *)
let stringmap_bindings_inorder map keys =
   let once k bs =
      let v = StringMap.find k map in
      (k, v) :: bs
   in
   List.fold_right once keys []

(* Check that an order (for *_inorder) is well formed *)
let stringmap_assert_okorder map keys =
   let once_keys mseen k =
      try
         ignore (StringMap.find k map);
         StringSet.add k mseen
      with Not_found ->
         Util.crash ("stringmap_assert_inorder: key " ^ k ^ " not in map")
   in
   let mseen = List.fold_left once_keys StringSet.empty keys in
   let once_map k _ =
      if StringSet.mem k mseen then ()
      else Util.crash ("stringmap_assert_inorder: key " ^ k ^ " not in keys")
   in
   StringMap.iter once_map map

module IntMap = Map.Make(struct type t = int let compare = compare end)
module IntSet = Set.Make(struct type t = int let compare = compare end)

(* union over a list of sets *)
let intset_unionall sets =
   List.fold_left IntSet.union IntSet.empty sets

(*
 * Scope (nesting stringmap)
 *)

type 'a scope = {
   bindings: 'a StringMap.t;
   parent: 'a scope option;
}

let newscope parent = {
   bindings = StringMap.empty;
   parent = parent;
}

let emptyscope = newscope None

let scope_add k v s =
   let bindings = StringMap.add k v s.bindings in
   { s with bindings; }

let rec scope_find k s =
   try
      Some (StringMap.find k s.bindings)
   with Not_found ->
      match s.parent with
           None -> None
         | Some p -> scope_find k p

let scope_mem k s =
   scope_find k s <> None

let scope_mem_here k s =
   StringMap.mem k s.bindings

let scope_push s = newscope (Some s)
let scope_pop s =
   match s.parent with
        None -> Util.crash "scope_pop: unmatched"
      | Some p -> p
