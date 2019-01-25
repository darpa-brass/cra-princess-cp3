(*
 * Copyright (c) 2016, 2017
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

type callbacks = {
   (* resolve type alias names (provded by client) *)
   unalias_type: (Typerep.typename -> Typerep.typename);

   (* look up a compound type (provided by client) *)
   lookup_compoundtype: (string ->
	(Pos.pos * Typerep.typename) list option);
		(* definedat, argtys *)

   (* look up a variable (provided by client) *)
   lookup_variable: (string -> Typerep.typename option);

   (* look up a modifier (provided by client) *)
   lookup_modifier: (string ->
	(Pos.pos * Typerep.typename * Typerep.typename) option);
		(* definedat, argtype, resulttype *)

}

type context

val failuretype: Typerep.typename

val newctx: unit -> context
val setcallbacks: context -> callbacks -> unit

val improvetype: context -> Typerep.typename -> Typerep.typename

val ctx_newtmptype: context -> Pos.pos -> Typerep.typename
val unify': context -> Pos.pos -> Typerep.typename -> Typerep.typename ->
		Typerep.typename

val inf'expr: context -> Exprrep.expr -> Exprrep.expr
val res'type: context -> Typerep.typename -> Typerep.typename
val res'expr: context -> Exprrep.expr -> Exprrep.expr
val done'typename: Pos.pos -> string -> Typerep.typename -> unit
val done'typename'fatal: Pos.pos -> string -> Typerep.typename -> unit
val done'expr: Exprrep.expr -> unit
