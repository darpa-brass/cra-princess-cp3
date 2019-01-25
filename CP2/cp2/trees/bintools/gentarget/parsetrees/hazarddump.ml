(*
 * Copyright (c) 2017
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

(* dump for Hazardtree *)

open Dumptools
open Hazardtree

(**************************************************************)
(* main recursion *)

let dump'expr e =
   Exprdump.dump'expr e

let rec dump'cond' count c = match c with
     COND_ANY -> (".", [])
   | COND_PREDNAME p -> ("[" ^ p ^ "]", [])
   | COND_PREDEXPR p ->
        let n = !count in
        count := !count + 1;
        ("{" ^ string_of_int n ^ "}", [(n, p)])
   | COND_SEQ (c1, c2) ->
        let (s1, e1) = dump'cond' count c1 in
        let (s2, e2) = dump'cond' count c2 in
        (s1 ^ s2, e1 @ e2)
   | COND_ALT (c1, c2) ->
        let (s1, e1) = dump'cond' count c1 in
        let (s2, e2) = dump'cond' count c2 in
        (s1 ^ " | " ^ s2, e1 @ e2)
   | COND_OPT c1 ->
        let (s, e) = dump'cond' count c1 in
        ("(" ^ s ^ ")?", e)
   | COND_PLUS c1 ->
        let (s, e) = dump'cond' count c1 in
        ("(" ^ s ^ ")+", e)

let dump'cond c =
   let dump'p (n, e) =
      field (string_of_int n ^ " = ") (dump'expr e)
   in
   let (s, es) = dump'cond' (ref 0) c in
   shortfield "regex" s @
   list dump'p es

let dump'predref p = match p with
     P_BYEXPR e -> dump'expr e
   | P_BYNAME name -> [name]

let dump'assignment (ASSIGN (pos, name, e)) =
   heading' "ASSIGN" name pos @
   field "value" (dump'expr e)

let dump'matcher { guard; assignments; trigger; condition; } =
   field "guard" (dump'expr guard) @
   field "assignments" (list dump'assignment assignments) @
   field "trigger" (dump'predref trigger) @
   field "condition" (dump'cond condition)

let dump'hazard { name; definedat; desc; m; } =
   heading' "HAZARD" name definedat @
   shortfield "desc" desc @
   dump'matcher m

let dump'destination d = match d with
     GO -> "go"
   | STAY -> "stay"

let dump'transference t = match t with
     EXECUTE_AND d -> dump'destination d
   | NULLIFY_AND d -> "nullify and " ^ (dump'destination d)

let dump'transfertype tt = match tt with
     JUMP tf -> "JUMP " ^ dump'transference tf
   | BRANCH (tf1, tf2) ->
        "BRANCH " ^ dump'transference tf1 ^ " OR " ^ dump'transference tf2

let dump'transfer { definedat; m; result; } =
   heading "TRANSFER" definedat @
   dump'matcher m @
   shortfield "result" (dump'transfertype result)

let dump'predicatedecl (name, { definedat; args; e; }) =
   heading' "PREDICATE" name definedat @
   begin
      if args = Types.StringMap.empty then []
      else
         let arglist =
            List.map (fun (k, _) -> k) (Types.StringMap.bindings args)
         in
         shortfield "args" (String.concat " " arglist)
   end @
   indent (dump'expr e)

let dump'decls decls =
   Types.stringmap_assert_okorder decls.predicates decls.predorder;
   let predlist =
      Types.stringmap_bindings_inorder decls.predicates decls.predorder
   in
   (list dump'predicatedecl predlist) @
   (list dump'hazard decls.hazards) @
   (list dump'transfer decls.transfers)

(**************************************************************)
(* top level *)

let dump decls =
   String.concat "\n" (dump'decls decls)
