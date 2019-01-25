(*
 * Copyright (c) 2018
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
 * numerate
 *)

type enumdata = {
   name: string;
   width: int;
   symtovalue: int Types.StringMap.t;
}

type numeratectx

val numeratectx_new: enumdata Types.StringMap.t -> numeratectx
val numeratectx_push: numeratectx -> numeratectx
val numeratectx_checkclean: numeratectx -> unit

val numerate'typename: numeratectx -> Typerep.typename -> Typerep.typename
val numerate'expr: numeratectx -> Exprrep.expr -> Exprrep.expr
val numerate'subenum: numeratectx ->
				string (*name of subenum*) ->
				Pos.pos (* definedat of subenum *) ->
				string (* name of enum referenced *) ->
				Types.StringSet.t (* values in subenum *) ->
			unit

                                     (* assignment: pos, name, expr *)
val numerate_extract: numeratectx -> (Pos.pos * string * Exprrep.expr) list


(*
 * delist
 *)

type delistctx

val delistctx_new: unit -> delistctx
val delistctx_addlistvar: delistctx -> string -> Exprrep.expr -> unit

val nolist: Pos.pos -> Typerep.typename -> string -> unit

val delist'expr: delistctx -> Exprrep.expr -> Exprrep.expr
