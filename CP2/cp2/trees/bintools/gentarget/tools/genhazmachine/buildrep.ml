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

module B = Basetree
module E = Encodingtree
module H = Hazardtree
open Rep

module TB = Typebuild
module EB = Exprbuild

(*************************************************************)
(* support *)

let nextid = ref 0

let getname prefix =
   let id = !nextid in
   nextid := id + 1;
   prefix ^ string_of_int id

let notype = Typerep.PLAINTYPE "_"

(*************************************************************)
(* from modes.def *)

(*
 * All we care about is which modes exist, so just take name and
 * location.
 *)
let build'mode (m: Modetree.mode) =
   let name = m.Modetree.name in
   let pos = m.Modetree.definedat in
   (name, pos)

(*************************************************************)
(* from registers.def *)

let build'regdecls decls =
   (* these are just more enum types... should share the rep and code *)
   let enumtypes = ref Types.StringMap.empty in

   let build'decl d = match d with
        B.ENUMTYPE (definedat, name, width, members) ->
           let mkelement (pos, ename, optval) =
              match optval with
                   None -> Util.crash "buildrep: register enumerator without value"
                 | Some n -> (pos, ename, n)
           in
           let elements = List.map mkelement members in
           let et = { name; definedat; width; elements; } in
           enumtypes := Types.StringMap.add name et !enumtypes;
      | _ -> ()
   in
   List.iter build'decl decls;
   !enumtypes


(*************************************************************)
(* from encoding.def *)

let build'encodingdecls decls =
   let enumtypes = ref Types.StringMap.empty in
   let subenums = ref Types.StringMap.empty in
   let fields = ref Types.StringMap.empty in
   
   let build'decl d = match d with
        E.FIELD (definedat, name, ty, _relinfo) ->
           let ty = TB.build'type ty in
           let f = { name; definedat; ty; junk=false; } in
           fields := Types.StringMap.add name f !fields
      | E.ENUMFIELD (_definedat, name, ty, _relinfo) ->
           let E.ENUMTYPE (definedat, width, elems) = ty in
           let mkelement (pos, ename, optval) =
              match optval with
                   None -> Util.crash "buildrep: enumerator without value"
                 | Some n -> (pos, ename, n)
           in
           let elements = List.map mkelement elems in
           let tyname = getname ".E" in
           let et = { name=tyname; definedat; width; elements; } in
           enumtypes := Types.StringMap.add tyname et !enumtypes;
           let ty' = Typerep.PLAINTYPE tyname in
           let f = { name; definedat; ty=ty'; junk=false; } in
           fields := Types.StringMap.add name f !fields
      | E.SUBENUM (definedat, name, names) ->
           let add z name = Types.StringMap.add name true z in
           let selected = List.fold_left add Types.StringMap.empty names in
           let se = { name; definedat; ty=notype; selected; } in
           subenums := Types.StringMap.add name se !subenums
      | E.SUBENUMEXPR _ ->
           (* removed by Encodingcheck *)
           Util.crash "buildrep: leftover SUBENUMEXPR"
      | E.FORM _ -> ()
   in
   List.iter build'decl decls;
   (!enumtypes, !subenums, !fields)

(*************************************************************)
(* from hazard.def *)

(*
 * Build a regexp.
 *)
let rec build'rx cond = match cond with
     H.COND_ANY -> ANY
   | H.COND_PREDNAME p -> SOME p
   | H.COND_PREDEXPR _e ->
        Util.crash "buildrep: build'rx: leftover PREDEXPR"
   | H.COND_SEQ (r1, r2) -> SEQ (build'rx r1, build'rx r2)
   | H.COND_ALT (r1, r2) -> ALT (build'rx r1, build'rx r2)
   | H.COND_OPT r1 -> OPT (build'rx r1)
   | H.COND_PLUS r1 -> PLUS (build'rx r1)

(*
 * Build an (instruction) predicate, that is, an expression.
 *)
let build'predicatedecl { H.definedat; H.args; H.afields; H.e; } =
   let e' = EB.build'expr e in
   let build'arg pos = (pos, notype) in
   let args = Types.StringMap.map build'arg args in

   let afields =
      let mkone f map = Types.StringMap.add f notype map in
      Types.StringSet.fold mkone afields Types.StringMap.empty
   in

   (* cfields needs to be computed after predicate splitting *)
   let cfields = Types.StringMap.empty in

   { definedat; args; afields; cfields; es=[e']; }

(*
 * Build an assignment.
 *)
let build'assignment (H.ASSIGN (pos, name, e)) =
   (pos, name, notype, EB.build'expr e)

(*
 * Create the rep version of an instruction match.
 *)
let build'matcher { H.guard; H.assignments; H.trigger; H.condition; } =
   let id = 0 in
   let guard = EB.build'expr guard in
   let assignments = List.map build'assignment assignments in
   let trigger = match trigger with
        H.P_BYEXPR _ -> Util.crash "buildrep: expr predicate left in matcher"
      | H.P_BYNAME name -> name
   in
   let cond = build'rx condition in
   { id; guard; assignments; trigger; cond; }

(*
 * Create the rep version of a hazard.
 *)
let build'hazard { H.name; H.definedat; H.desc; H.m; } =
   let m = build'matcher m in
   { name; definedat; desc; m; }

(*
 * Create the rep version of a transfer (jump/branch instruction spec)
 *)
let build'transfer { H.definedat; H.m; H.result; } =

   let m = build'matcher m in

   (* convert the representation of what happens *)
   let build'dest d = match d with
        H.GO -> GO
      | H.STAY -> STAY
   in
   let build'effect tf = match tf with
        H.EXECUTE_AND d -> (EXECUTE, build'dest d)
      | H.NULLIFY_AND d -> (NULLIFY, build'dest d)
   in
   let build'effects tt = match tt with
        H.JUMP tf1 -> [build'effect tf1]
      | H.BRANCH (tf1, tf2) -> [build'effect tf1; build'effect tf2]
   in
   let effects = build'effects result in

   { definedat; m; effects; }

(*************************************************************)
(* toplevel *)

let build baseinfo modeinfo encinfo hazinfo =

   let modes = Types.stringmap_of_list (List.map build'mode modeinfo) in

   let enumtypes1 = build'regdecls baseinfo in

   let enumtypes2, subenums, fields = build'encodingdecls encinfo in

   let unionfunc name _ _ =
      (* The enumtype names from encinfo are autogenerated, can't conflict *)
      Util.crash ("buildrep: enum type name collision on " ^ name)
   in
   let enumtypes = Types.stringmap_union unionfunc enumtypes1 enumtypes2 in

   let { H.predicates; H.predorder; H.hazards; H.transfers; } = hazinfo in
   let predicates = Types.StringMap.map build'predicatedecl predicates in
   let hazards = List.map build'hazard hazards in
   let transfers = List.map build'transfer transfers in

   {
      modes;
      enumtypes; subenums; fields;
      predicates; predorder; hazards; transfers;
   }
