(*
 * Copyright (c) 2016, 2017, 2018
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
 * Intermediate representation for genlanguage
 *
 * This is largely the same as langtree, but (for now at least) leaves
 * some of the bits out (the bits that are handled by genlangdefs) and
 * also trying to make langtree polymorphic over the types for types
 * and expressions make a mess and did not really accomplish a great
 * deal vs. having two separate sets of types.
 *)

open Typerep
open Exprrep

type pos = Pos.pos

type pattern =
     BIND of pos * typename * string
   | MATCHSTR of pos * string
   | MATCHINT of pos * int

type enumerator = pos * string * int

type token = pos * typename * bool (*istarget*)

type tokenexpr = pos * string * expr option
type tagexpr = pos * string * expr

type tokenpattern = pos * string * pattern option

type exprpattern =
     TOKEN of tokenpattern
   | EXPR of pos * tokenpattern list * pattern option
   | EXPRANY of pos * pattern option

type spec = {
   addrtype: typename;
   numtype: typename;

   letters: string list;
   subletters: string list;

   enumtypes: (Pos.pos * int * enumerator list) Types.StringMap.t;
   enumvals: enumerator Types.StringMap.t;
   compoundtypes: (Pos.pos * (Pos.pos * typename) list) Types.StringMap.t;
   operandtags: (Pos.pos * typename) Types.StringMap.t;

   tokens: (pos * typename * bool (*istarget*) ) Types.StringMap.t;
   matches: (pos * tokenpattern list * tokenexpr) list;
   tagrules: (pos * exprpattern list * expr * tagexpr) list;
}
