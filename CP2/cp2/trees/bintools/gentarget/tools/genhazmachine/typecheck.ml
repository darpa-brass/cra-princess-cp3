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

module ETC = Exprtypecheck
open Rep

(*************************************************************)
(* context *)

(*
 * The scopes of variables are as follows:
 *    global (true, false, enumerators, subenums)
 *      instruction/matcher (fields, predicates, assignedvars)
 *        predicate (predicate args)
 *
 * When a predicate is used, its args are satisfied from the
 * assignedvars of the same name in the current matcher context. (If
 * one doesn't exist, it's an error. Here, we crash on that because
 * it's enforced in the input by Hazresolve upstream, so if it's
 * broke here it's because we broke it somewhere.)
 *
 * Note that the args of predicates are not declared but are deduced
 * by examining the free variables of the predicate expression. This
 * is maybe a questionable design decision, but so far it's working ok
 * and it allows moving all predicate declarations out of line prior
 * to doing such analysis, which has been convenient. (The analysis
 * is done in Hazresolve. The out-of-lining is done in Hazardcheck.)
 *
 * Note that we don't attempt to generalize the types of the predicate
 * args. Given that in the normal case they're compared to instruction
 * fields, which are monomorphic, it doesn't seem very useful.
 *)

type context = {
   ectx: ETC.context;

   (* types are global *)
   types: (Pos.pos * bool(*takeswidth*)) Types.StringMap.t ref;

   (* vars have different scopes though *)
   globalvars: (Pos.pos * typename) Types.StringMap.t ref;
   fieldvars: (Pos.pos * typename) Types.StringMap.t ref;
   predicatevars: (Pos.pos * typename * argmap) Types.StringMap.t ref;
   assignedvars: (Pos.pos * typename) Types.StringMap.t ref;

   allmodes: Types.StringSet.t ref;

   inguard: bool ref;
}

let ctx_getvar ctx name =
   let noargs (pos, ty) =
      Some (pos, ty, None)
   in
   let withargs (pos, ty, map) =
      Some (pos, ty, Some map)
   in
   try
      noargs (Types.StringMap.find name !(ctx.globalvars))
   with Not_found -> 
      if !(ctx.inguard) then None
      else try
         noargs (Types.StringMap.find name !(ctx.fieldvars))
      with Not_found -> try
         withargs (Types.StringMap.find name !(ctx.predicatevars))
      with Not_found -> try
         noargs (Types.StringMap.find name !(ctx.assignedvars))
      with Not_found -> None

let lookup_type ctx name =
   try
      let (definedat, takeswidth) = Types.StringMap.find name !(ctx.types)
      in Some (definedat, takeswidth, [])
   with Not_found -> None

let lookup_var ctx name =
   match ctx_getvar ctx name with
        None -> None
      | Some (pos, ty, _) -> Some (pos, ty)

let newctx () =
   (* we don't have aliased type names in here *)
   let lookup_aliastype _ = None in
   (* and modifiers aren't allowed *)
   let lookup_modifier _ = None in

   let ectx = ETC.newctx () in
   let ctx = {
      ectx;
      types = (ref Types.StringMap.empty);
      globalvars = (ref Types.StringMap.empty);
      fieldvars = (ref Types.StringMap.empty);
      predicatevars = (ref Types.StringMap.empty);
      assignedvars = (ref Types.StringMap.empty);
      allmodes = (ref Types.StringSet.empty);
      inguard = (ref false);
   } in

   let callbacks = {
      ETC.lookup_aliastype;
      ETC.lookup_type = (lookup_type ctx);
      ETC.lookup_var = (lookup_var ctx);
      ETC.lookup_modifier;
   } in
   ETC.setcallbacks ctx.ectx callbacks;
   ctx

let ctx_addtype ctx name definedat takeswidth =
   ctx.types := Types.StringMap.add name (definedat, takeswidth) !(ctx.types)

let ctx_addplaintype ctx name definedat = ctx_addtype ctx name definedat false
(*
let ctx_addargtype ctx name definedat = ctx_addtype ctx name definedat true
*)

let ctx_addglobalvar ctx name definedat ty =
   ctx.globalvars := Types.StringMap.add name (definedat, ty) !(ctx.globalvars)

let ctx_addfieldvar ctx name definedat ty =
   ctx.fieldvars := Types.StringMap.add name (definedat, ty) !(ctx.fieldvars)

let ctx_addpredicatevar ctx name definedat ty args =
   ctx.predicatevars :=
      Types.StringMap.add name (definedat, ty, args) !(ctx.predicatevars)

let ctx_addassignedvar ctx name definedat ty =
   ctx.assignedvars :=
      Types.StringMap.add name (definedat, ty) !(ctx.assignedvars)

let ctx_clearassignedvars ctx =
   ctx.assignedvars := Types.StringMap.empty

(*************************************************************)
(* expressions *)

let typemismatch = ETC.typemismatch
let check'typename ctx ty = ETC.check'typename ctx.ectx ty
let check'expr ctx e = ETC.check'expr ctx.ectx e

(*************************************************************)
(* modes *)

(*
 * XXX: currently check'expr doesn't enforce that you only use
 * existing modes, but hopefully that'll get fixed, so we'll want
 * to know what they are.
 *)

let check'mode ctx name _pos =
   ctx.allmodes := Types.StringSet.add name !(ctx.allmodes)

(*************************************************************)
(* encoding elements *)

let check'enumtype ctx _name { name; definedat; (*width;*) elements; } =
   ctx_addplaintype ctx name definedat;
   let ty = (PLAINTYPE name) in
   check'typename ctx definedat ty;

   let check'element (pos, ename, _k) =
      if String.get ename 0 = '_' then ()
      else ctx_addglobalvar ctx ename pos ty
   in
   List.iter check'element elements

let check'subenum ctx _name { name; definedat; ty; selected; } =
   ignore (selected);
   check'typename ctx definedat ty;
   ctx_addglobalvar ctx name definedat ty

let check'field ctx _name { name; definedat; ty; junk; } =
   ignore (junk);
   check'typename ctx definedat ty;
   ctx_addfieldvar ctx name definedat ty

(*************************************************************)
(* hazard elements *)

let check'predname ctx usepos p where =
   let checkbool pos ty'p =
      if ty'p <> booltype then begin
         let msg = "result of predicate expression in " ^ where in
         typemismatch pos booltype ty'p msg;
         if pos <> usepos then
            Pos.sayat usepos "arising from use here"
      end
   in
   match ctx_getvar ctx p with
        None ->
           Pos.sayat usepos ("Undefined predicate " ^ p);
           Util.fail ()
      | Some (pos, ty'p, None) ->
           checkbool pos ty'p
      | Some (pos, ty'p, Some argmap) ->
           checkbool pos ty'p;
           let checkone name (defpos, ty) =
              match ctx_getvar ctx name with
                   None ->
                      Pos.sayat usepos ("No binding for variable " ^ name ^
                                        " used by predicate " ^ p);
                      Pos.sayat defpos ("Used in predicate here");
                      Util.fail ()
                 | Some (_pos, foundty, _) ->
                      if ty <> foundty then begin
                         let msg =
                            "variable " ^ name ^ " used by predicate " ^ p
                         in
                         typemismatch usepos foundty ty msg
                      end
           in
           Types.StringMap.iter checkone argmap

let rec check'rx ctx definedat r = match r with
     ANY -> ()
   | SOME p -> check'predname ctx definedat p "regexp"
   | SEQ (r1, r2) -> check'rx ctx definedat r1; check'rx ctx definedat r2
   | ALT (r1, r2) -> check'rx ctx definedat r1; check'rx ctx definedat r2
   | OPT r1 -> check'rx ctx definedat r1
   | PLUS r1 -> check'rx ctx definedat r1

let check'predicatedecl ctx name { definedat; args; afields; cfields; es; } =
   ctx_clearassignedvars ctx;
   let addone name (pos, ty) =
      ctx_addassignedvar ctx name pos ty
   in
   Types.StringMap.iter addone args;

   let tys'es = List.map (check'expr ctx) es in
   let check'e n ty'e =
      if ty'e <> booltype then begin
         let msg =
            let portion =
               if List.length es = 1 then ""
               else " portion " ^ string_of_int n
            in
            "result of predicate " ^ name ^ portion
         in
         typemismatch definedat booltype ty'e msg
      end;
   in
   List.iteri check'e tys'es;

   let check'f field ty =
      try
         let (_, foundty) = Types.StringMap.find field !(ctx.fieldvars) in
         if ty <> foundty then begin
            typemismatch definedat ty foundty ("stored type of field " ^ field)
         end
      with Not_found ->
         Pos.sayat definedat ("Predicate " ^ name ^ " uses field " ^ field ^
                              ", but it does not exist or is not a field");
         Util.fail ()
   in
   Types.StringMap.iter check'f afields;
   Types.StringMap.iter check'f cfields;

   ctx_clearassignedvars ctx;
   ctx_addpredicatevar ctx name definedat booltype args

let check'assignment ctx (pos, name, ty, e) =
   let ty'e = check'expr ctx e in
   if ty'e <> ty then begin
      let msg = "assignment of " ^ name in
      typemismatch pos ty ty'e msg
   end;
   ctx_addassignedvar ctx name pos ty'e

let check'matcher ctx definedat { guard; assignments; trigger; cond; } =
   ctx_clearassignedvars ctx;

   (*
    * it is ugly to flip a switch in the context like this...
    * ... but we have to because the context is closed into the Exprtypecheck
    * context so passing a different one isn't an option.
    *)
   ctx.inguard := true;
   let ty'guard = check'expr ctx guard in
   if ty'guard <> booltype then begin
      typemismatch definedat booltype ty'guard "result of guard expression"
   end;
   ctx.inguard := false;

   List.iter (check'assignment ctx) assignments;
   check'predname ctx definedat trigger "trigger";

   check'rx ctx definedat cond;

   ctx_clearassignedvars ctx

let check'hazard ctx { name; definedat; desc; m; } =
   ignore (name); ignore (desc);
   check'matcher ctx definedat m

let check'transfer ctx { definedat; m; effects; } =
   ignore (effects);
   check'matcher ctx definedat m

(*************************************************************)
(* interface *)

let typecheck (spec: spec) =
   let ctx = newctx () in

   (* add the builtin types *)
   let buildintype takeswidth name =
      ctx_addtype ctx name Pos.builtin takeswidth
   in
   Types.StringSet.iter (buildintype false) builtin_plaintypes;
   Types.StringSet.iter (buildintype true) builtin_argtypes;

   (* add the builtin values *)
   (* XXX these should be listed in Exprrep or some such place *)
   ctx_addglobalvar ctx "true" Pos.builtin booltype;
   ctx_addglobalvar ctx "false" Pos.builtin booltype;


   Types.StringMap.iter (check'mode ctx) spec.modes;

   Types.StringMap.iter (check'enumtype ctx) spec.enumtypes;
   Types.StringMap.iter (check'subenum ctx) spec.subenums;
   Types.StringMap.iter (check'field ctx) spec.fields;

   Types.stringmap_iter_inorder (check'predicatedecl ctx)
      spec.predicates spec.predorder;
   List.iter (check'hazard ctx) spec.hazards;
   List.iter (check'transfer ctx) spec.transfers;

   ()
