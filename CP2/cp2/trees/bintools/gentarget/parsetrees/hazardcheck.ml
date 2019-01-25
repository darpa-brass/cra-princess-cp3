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

open Hazardtree

(*************************************************************)
(* context *)

type context = {
   pos: Pos.pos ref;
   preds: bool Types.StringMap.t ref;
   nexttmp: int ref;
   newpreds: predicatedecl Types.StringMap.t ref;
   newpredorder: string list ref;
}

let newctx () = {
   pos = ref Pos.builtin;
   preds = ref Types.StringMap.empty;
   nexttmp = ref 0;
   newpreds = ref Types.StringMap.empty;
   newpredorder = ref []; (* built in reverse order *)
}

let ctx_findpred ctx name =
   try
      Some (Types.StringMap.find name !(ctx.preds))
   with Not_found -> None

let ctx_addpred ctx name =
   ctx.preds := Types.StringMap.add name true !(ctx.preds)

(* get a fresh name for a predicate *)
let ctx_getname ctx =
   let n = !(ctx.nexttmp) in
   ctx.nexttmp := n + 1;
   "HAZP_" ^ string_of_int n

let ctx_addnewpred ctx name e =
   let newpred = {
      definedat = !(ctx.pos);
      args = Types.StringMap.empty;
      afields = Types.StringSet.empty;
      e;
   } in
   ctx.newpreds := Types.StringMap.add name newpred !(ctx.newpreds);
   ctx.newpredorder := name :: !(ctx.newpredorder)

(*************************************************************)
(* main pass *)

(*
 * Give a predicate (that doesn't already have one) a name.
 *)
let bind_predicate ctx e =
   let name = ctx_getname ctx in
   ctx_addpred ctx name;
   ctx_addnewpred ctx name e;
   name

(*
 * We can't check this for real yet because we don't have the names of
 * instruction fields here. So do... what? nothing I guess...
 *
 * Note that we can get a READVAR with a named predicate name, and
 * that should be interpreted as testing that predicate.
 *)
let check_expr _ctx _e = ()

(*
 * Check a predicate declaration (a named predicate)
 *)
let check_predicatedecl ctx name { definedat; args; e; } =
   ignore (args);
   ctx.pos := definedat;
   check_expr ctx e;
   match ctx_findpred ctx name with
        Some _ -> Pos.sayat !(ctx.pos) ("Duplicate definition of " ^ name);
                  Util.fail ()
      | None -> ctx_addpred ctx name

(*
 * Check an assignment.
 *)
let check_assignment ctx (ASSIGN (_pos, _name, e)) =
   check_expr ctx e

(*
 * Check a condition. Move any inline predicate expressions to
 * new named predicates.
 *)
let rec check_cond ctx c = match c with
     COND_ANY -> COND_ANY
   | COND_PREDNAME name ->
        begin
        match ctx_findpred ctx name with 
             Some _ -> ()
           | None ->
                Pos.sayat !(ctx.pos) ("No such named predicate " ^ name);
                Util.fail ()
        end;
        COND_PREDNAME name
   | COND_PREDEXPR e ->
        check_expr ctx e;
        let name = bind_predicate ctx e in
        COND_PREDNAME name
   | COND_SEQ (c1, c2) ->
        let c1' = check_cond ctx c1 in
        let c2' = check_cond ctx c2 in
        COND_SEQ (c1', c2')
   | COND_ALT (c1, c2) ->
        let c1' = check_cond ctx c1 in
        let c2' = check_cond ctx c2 in
        COND_ALT (c1', c2')
   | COND_OPT (c1) ->
        let c1' = check_cond ctx c1 in
        COND_OPT (c1')
   | COND_PLUS (c1) ->
        let c1' = check_cond ctx c1 in
        COND_PLUS (c1')

(*
 * Check a matcher specification.
 *)
let check_matcher ctx { guard; assignments; trigger; condition; } =
   check_expr ctx guard;
   List.iter (check_assignment ctx) assignments;
   let trigger = match trigger with
        P_BYNAME _ ->
           (* the parser doens't allow this; could support it easily enough *)
           Util.crash "hazardcheck: named trigger in matcher"
      | P_BYEXPR e ->
           check_expr ctx e;
           P_BYNAME (bind_predicate ctx e)
   in
   let condition = check_cond ctx condition in
   { guard; assignments; trigger; condition; }

(*
 * Check a full hazard.
 *)
let check_hazard ctx { name; definedat; desc; m; } =
   ctx.pos := definedat;
   let m = check_matcher ctx m in
   { name; definedat; desc; m; }

(*
 * Check the transfertype of a transfer.
 *)
let check_transfertype ctx t =
   let dowarn msg =
      Pos.sayat !(ctx.pos) ("Warning: " ^ msg)
   in
   let getdest tf = match tf with
       EXECUTE_AND d -> d
     | NULLIFY_AND d -> d
   in
   let nullifies tf = match tf with
       EXECUTE_AND _ -> false
     | NULLIFY_AND _ -> true
   in
   match t with
        JUMP (EXECUTE_AND _) -> ()
      | JUMP (NULLIFY_AND _) ->
           (* not necessarily wrong but doesn't make much sense *)
           dowarn "This jump nullifies"
      | BRANCH (tf1, tf2) ->
           begin
           if nullifies tf1 && nullifies tf2 then
              dowarn "Both cases of this branch nullify"
           end;
           match getdest tf1, getdest tf2 with
                GO, GO -> dowarn "Both cases of this branch jump"
              | STAY, STAY -> dowarn "Neither case of this branch jumps"
              | _, _ -> ()
             
(*
 * Check a transfer specification.
 *)
let check_transfer ctx { definedat; m; result; } =
   ctx.pos := definedat;
   let m = check_matcher ctx m in
   check_transfertype ctx result;
   { definedat; m; result; }

(*************************************************************)
(* interface *)

let check { predicates; predorder; hazards; transfers; } =
   let ctx = newctx () in

   Types.stringmap_assert_okorder predicates predorder;

   (* do the checks *)
   Types.stringmap_iter_inorder
      (check_predicatedecl ctx) predicates predorder;
   let hazards = List.map (check_hazard ctx) hazards in
   let transfers = List.map (check_transfer ctx) transfers in

   (* glue together the predicate tables *)
   let unionfunc name _p1 _p2 =
      Util.crash ("hazardcheck: name collision on " ^ name)
   in
   let predicates =
      Types.stringmap_union unionfunc predicates !(ctx.newpreds)
   in
   let predorder =
      predorder @ (List.rev !(ctx.newpredorder))
   in
   { predicates; predorder; hazards; transfers; }
