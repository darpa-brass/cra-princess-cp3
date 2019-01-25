(*
 * Copyright (c) 2017, 2018
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
 * Internal representation for the hazard machine.
 *)

include Typerep
include Exprrep

(*
 * Encoding items
 *)

type enumtype = {
   name: string;
   definedat: Pos.pos;
   width: int;
   elements: (Pos.pos * string * int) list;
}

type subenum = {
   name: string;
   definedat: Pos.pos;
   ty: typename;
   selected: bool Types.StringMap.t;
}

type field = {
   name: string;
   definedat: Pos.pos;
   ty: typename;
   junk: bool;   (* needed to disambiguate the record element names *)
}

(*
 * Hazard items
 *)

type rx =
     ANY
   | SOME of string
   | SEQ of rx * rx
   | ALT of rx * rx
   | OPT of rx
   | PLUS of rx

type arg = (Pos.pos * typename)
type argmap = arg Types.StringMap.t
type predicatedecl = {
   definedat: Pos.pos;
   args: argmap;
   afields: typename Types.StringMap.t;
   cfields: typename Types.StringMap.t;
   es: expr list;
}

type matcher = {
   id: int;
   guard: expr;
   assignments: (Pos.pos * string * typename * expr) list;
   trigger: string;
   cond: rx;
}

type hazard = {
   name: string;
   definedat: Pos.pos;
   desc: string;
   m: matcher;
}

type nullification = NULLIFY | EXECUTE
type where = STAY | GO

type transfer = {
   definedat: Pos.pos;
   m: matcher;
   effects: (nullification * where) list;
}

type spec = {
   (* which modes exist (and where they were defined) from modes.def *)
   modes: Pos.pos Types.StringMap.t;

   (* from encodings.def *)
   enumtypes: enumtype Types.StringMap.t;
   subenums: subenum Types.StringMap.t;
   fields: field Types.StringMap.t;

   (* from hazards.def *)
   predicates: predicatedecl Types.StringMap.t;
   predorder: string list;
   hazards: hazard list;
   transfers: transfer list;
}
