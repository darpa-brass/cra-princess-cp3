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

module ETI = Exprtypeinf
open Rep

(*************************************************************)
(* context *)

(*
 * See scoping notes in typecheck.ml.
 *
 * "globals" holds everything available in the global scope; this
 * includes enumerator and subenum names. Field names go in "fields",
 * and predicate names go in "preds".
 *
 * The encodinginfo material is loaded up front. (Since there's only
 * one set of fields, they're the same everywhere, just inaccessible
 * where there isn't an instruction in context.)
 *
 * Assigned variables from matcher contexts go in "assignedvars" while
 * working in a matcher context. So do args of predicates when
 * checking predicates.
 *
 * Note that we must handle scoping by updating the context somehow
 * (not passing around a different context) because of the way the
 * contexts in the shared Exprtypeinf work. That setup is maybe not
 * optimal but it's annoyingly circular in ways that are hard to get
 * to work at all, so don't change it without planning out and testing
 * a better model beforehand.
 *)

(* where we are (basically, which scope we're in *)
type scope = IN_NOWHERE | IN_INSN | IN_PRED

type ctx = {
   ectx: ETI.context;

   enums: (Pos.pos * string * int) list Types.StringMap.t ref;

   globals: (Pos.pos * typename) Types.StringMap.t ref;
   fields: (Pos.pos * typename) Types.StringMap.t ref;
   preds: (Pos.pos * typename) Types.StringMap.t ref;
   assignedvars: (Pos.pos * typename) Types.StringMap.t ref;

   curscope: scope ref;
}

let ctx_getvar ctx name =
   let getglobal () = Types.StringMap.find name !(ctx.globals) in
   let getfield () = Types.StringMap.find name !(ctx.fields) in
   let getpred () = Types.StringMap.find name !(ctx.preds) in
   let getassignedvar () = Types.StringMap.find name !(ctx.assignedvars) in

   let get_in_nowhere () = getglobal () in
   let get_in_insn () =
      try getpred ()
      with Not_found ->
      try getfield ()
      with Not_found ->
      get_in_nowhere ()
   in
   let get_in_pred () =
      try getassignedvar ()
      with Not_found ->
      get_in_insn ()
   in

   match !(ctx.curscope) with
        IN_NOWHERE -> (try Some (get_in_nowhere ()) with Not_found -> None)
      | IN_INSN ->    (try Some (get_in_insn ())    with Not_found -> None)
      | IN_PRED ->    (try Some (get_in_pred ())    with Not_found -> None)

let lookup_variable ctx name =
   match ctx_getvar ctx name with
        Some (_pos, ty) -> Some ty
      | None -> None

let newctx () =

   (* we don't have aliased type names in here *)
   let unalias_type t = t in
   (* nor do we have compound types *)
   let lookup_compoundtype _ = None in
   (* and modifiers aren't allowed *)
   let lookup_modifier _ = None in

   let ectx = ETI.newctx () in
   let ctx = {
      ectx;
      enums = (ref Types.StringMap.empty);
      globals = (ref Types.StringMap.empty);
      fields = (ref Types.StringMap.empty);
      preds = (ref Types.StringMap.empty);
      assignedvars = (ref Types.StringMap.empty);
      curscope = (ref IN_NOWHERE);
   } in

   let callbacks = {
      ETI.unalias_type;
      ETI.lookup_compoundtype;
      ETI.lookup_variable = (lookup_variable ctx);
      ETI.lookup_modifier;
   } in
   ETI.setcallbacks ctx.ectx callbacks;
   ctx

let addvar map name pos ty =
   try
      let (oldpos, _) = Types.StringMap.find name !map in
      Pos.sayat pos ("Duplicate definition of " ^ name);
      Pos.sayat oldpos ("Previous definition");
      Util.fail ()
   with Not_found ->
      map := Types.StringMap.add name (pos, ty) !map
      
let ctx_addglobal (ctx: ctx) (* name pos ty *) =
   addvar ctx.globals (* name pos ty *)

let ctx_addfield (ctx: ctx) (* name pos ty *) =
   addvar ctx.fields (* name pos ty *)

let ctx_addpred (ctx: ctx) (* name pos ty *) =
   addvar ctx.preds (* name pos ty *)

let ctx_addassignedvar (ctx: ctx) (* name pos ty *) =
   addvar ctx.assignedvars (* name pos ty *)

let ctx_addenum ctx name elements =
   ctx.enums := Types.StringMap.add name elements !(ctx.enums)

let ctx_getenum ctx name =
   (* will crash if you ask for a nonexistent one *)
   Types.StringMap.find name !(ctx.enums)

let ctx_pushscope ctx scope =
   let ret = !(ctx.curscope) in
   ctx.curscope := scope;
   ret

let ctx_popscope ctx scope =
   ctx.curscope := scope

(*************************************************************)
(* types, expressions, and unification *)

let res'typename ctx ty =
   ETI.res'type ctx.ectx ty

let done'typename pos what ty =
   ETI.done'typename pos what ty

let unify ctx pos ty1 ty2 =
   ignore (ETI.unify' ctx.ectx pos ty1 ty2)

let inf'expr ctx e =
   ETI.inf'expr ctx.ectx e

let res'expr ctx e =
   ETI.res'expr ctx.ectx e

let done'expr e =
   ETI.done'expr e

(*************************************************************)
(* encoding elements *)

let inf'enumtype ctx _name { name; (*definedat; width;*) elements; } =
   let inf'element (pos, elname, _k) =
      if String.get elname 0 = '_' then ()
      else ctx_addglobal ctx elname pos (PLAINTYPE name)
   in
   List.iter inf'element elements;
   ctx_addenum ctx name elements;
   ()

(* nothing in here can get a scratch type *)
let res'enumtype _ctx _name _et = ()
let done'enumtype _name _et = ()

let inf'subenum ctx { name; definedat; (*ty;*) selected; } =
   (*
    * Get the type by looking up one of the enumerators; note that
    * Encodingcheck has already confirmed that all the values are
    * from one enum, and that there is at least one value.
    *)
  let (ename, _) = Types.StringMap.choose selected in
  let (_, ty) = Types.StringMap.find ename !(ctx.globals) in

  let enumname = match ty with
       PLAINTYPE n -> n
     | _ -> Util.crash "typeinf: inf'subenum: weird enum type"
  in

  (* fill in selected[] *)
  let elements = ctx_getenum ctx enumname in
  let tryinsert nsel (_pos, ename, _k) =
     try
        ignore (Types.StringMap.find ename selected); nsel
     with Not_found ->
        Types.StringMap.add ename false nsel
  in
  let selected = List.fold_left tryinsert selected elements in

  (* ty is the element type; the type of the subenum is a list of them *)
  let ty = LISTTYPE ty in

  (* remember the var *)
  ctx_addglobal ctx name definedat ty;

  { name; definedat; ty; selected; }

(* nothing in here can get a scratch type *)
let res'subenum _ctx se = se
let done'subenum _name _se = ()

let inf'field ctx _name { name; definedat; ty; junk; } =
   ignore (junk);
   (* we don't have to inf ty; it comes predefined; just add the symbol *)
   ctx_addfield ctx name definedat ty

(* nothing in here can get a scratch type *)
let res'field _ctx _name _f = ()
let done'field _name _f = ()

(*************************************************************)
(* hazard elements *)

(*
 * regexp
 *
 * Since the only thing inside regexps are the names of predicates,
 * they don't need type inference. If they aren't boolean, we'll
 * catch that later in typecheck.
 *)

let inf'rx _ctx r = r
let res'rx _ctx r = r
let done'rx _r = ()

(*
 * predicate
 *
 * note that because predicate declarations are moved out from inside
 * matchers, this does not intersect the matcher use of
 * ctx.assignedvars.
 *)

let inf'predicatedecl ctx name { definedat; args; afields; cfields; es; } =
   (* predicate splitting is run downstream of typeinf *)
   let e = match es with
        [e] -> e
      | _ -> Util.crash "typeinf: inf'predicatedecl: multiple expressions"
   in

   let scope = ctx_pushscope ctx IN_PRED in
   ctx.assignedvars := Types.StringMap.empty;

   let addone name (pos, _) =
      let ty = ETI.ctx_newtmptype ctx.ectx pos in
      ctx_addassignedvar ctx name pos ty;
      (pos, ty)
   in
   let args = Types.StringMap.mapi addone args in

   let e' = inf'expr ctx e in
   let ty = exprtype e' in
   unify ctx definedat booltype ty;

   let inf'field fname _ map =
      let (_pos, ty) = Types.StringMap.find fname !(ctx.fields) in
      Types.StringMap.add fname ty map
   in
   let afields =
      Types.StringMap.fold inf'field afields Types.StringMap.empty
   in
   (* cfields should be empty; but go ahead just in case *)
   let cfields =
      Types.StringMap.fold inf'field cfields Types.StringMap.empty
   in

   ctx_popscope ctx scope;
   ctx_addpred ctx name definedat ty;

   ctx.assignedvars := Types.StringMap.empty;

   { definedat; args; afields; cfields; es=[e']; }

let res'predicatedecl ctx _name { definedat; args; afields; cfields; es; } =
   (* predicate splitting is run downstream of typeinf *)
   let e = match es with
        [e] -> e
      | _ -> Util.crash "typeinf: inf'predicatedecl: multiple expressions"
   in

   let scope = ctx_pushscope ctx IN_PRED in
   ctx.assignedvars := Types.StringMap.empty;

   let e' = res'expr ctx e in

   let res'arg (pos, ty) =
      let ty' = res'typename ctx ty in
      (pos, ty')
   in
   let args = Types.StringMap.map res'arg args in

   (*
    * Don't need to update afields/cfields; they have types from fields,
    * which start out typed so don't need to be resolved.
    *)

   ctx_popscope ctx scope;

   { definedat; args; afields; cfields; es=[e']; }

let done'predicatedecl _name { definedat; args; afields; cfields; es; } =
   let done'freevar name (pos, ty) =
      done'typename pos ("Free var " ^ name ^ " in predicate ") ty
   in
   Types.StringMap.iter done'freevar args;

   let done'field tbl fname fty =
      done'typename definedat(*ugh*) ("field " ^ fname ^ " in " ^ tbl) fty
   in
   Types.StringMap.iter (done'field "afields") afields;
   Types.StringMap.iter (done'field "cfields") cfields;

   List.iter done'expr es

(*
 * assignment
 *)

let inf'assignment ctx (pos, name, _ty, e) =
   let e' = inf'expr ctx e in
   let ty' = exprtype e' in
   ctx_addassignedvar ctx name pos ty';
   (pos, name, ty', e')

let res'assignment ctx (pos, name, ty, e) =
   (pos, name, res'typename ctx ty, res'expr ctx e)

let done'assignment (pos, name, ty, e) =
   done'typename pos ("assigned variable " ^ name) ty;
   done'expr e

(*
 * matcher
 *)

let inf'matcher ctx _definedat { id; guard; assignments; trigger; cond; } =
   let guard = inf'expr ctx guard in
   let scope = ctx_pushscope ctx IN_INSN in
   ctx.assignedvars := Types.StringMap.empty;
   let assignments = List.map (inf'assignment ctx) assignments in
   (* trigger is a string *)
   let cond = inf'rx ctx cond in
   ctx.assignedvars := Types.StringMap.empty;
   ctx_popscope ctx scope;
   { id; guard; assignments; trigger; cond; }

let res'matcher ctx _definedat { id; guard; assignments; trigger; cond; } =
   let guard = res'expr ctx guard in
   let scope = ctx_pushscope ctx IN_INSN in

   (* need to populate ctx.assignedvars *)
   ctx.assignedvars := Types.StringMap.empty;
   let insert (pos, name, ty, _e) =
      ctx.assignedvars :=
         Types.StringMap.add name (pos, ty) !(ctx.assignedvars)
   in
   List.iter insert assignments;

   let assignments = List.map (res'assignment ctx) assignments in
   let cond = res'rx ctx cond in
   ctx.assignedvars := Types.StringMap.empty;
   ctx_popscope ctx scope;
   { id; guard; assignments; trigger; cond; }

let done'matcher { guard; assignments; (*trigger;*) cond; } =
   done'expr guard;
   List.iter done'assignment assignments;
   done'rx cond

(*
 * hazard
 *)

let inf'hazard ctx { name; definedat; desc; m; } =
   let m = inf'matcher ctx definedat m in
   { name; definedat; desc; m; }

let res'hazard ctx { name; definedat; desc; m; } =
   let m = res'matcher ctx definedat m in
   { name; definedat; desc; m; }

let done'hazard { name; definedat; desc; m; } =
   ignore (name); ignore (definedat); ignore (desc);
   done'matcher m

(*
 * transfer
 *)

let inf'transfer ctx { definedat; m; effects; } =
   let m = inf'matcher ctx definedat m in
   { definedat; m; effects; }

let res'transfer ctx { definedat; m; effects; } =
   let m = res'matcher ctx definedat m in
   { definedat; m; effects; }

let done'transfer { definedat; m; effects; } =
   ignore (definedat); ignore (effects);
   done'matcher m

(*************************************************************)
(* interface *)

let typeinf (spec: spec) =
   let ctx = newctx () in

   (* nothing needs to be (or can be) done with spec.modes *)

   (* XXX these should be listed in Exprrep or some such place *)
   ctx_addglobal ctx "true" Pos.builtin booltype;
   ctx_addglobal ctx "false" Pos.builtin booltype;

   (*
    * inference pass
    *)

   let enumtypes = spec.enumtypes in
   let fields = spec.fields in

   Types.StringMap.iter (inf'enumtype ctx) enumtypes;
   let subenums = Types.StringMap.map (inf'subenum ctx) spec.subenums in
   Types.StringMap.iter (inf'field ctx) fields;

   let predorder = spec.predorder in
   let predicates =
      Types.stringmap_mapi_inorder (inf'predicatedecl ctx)
         spec.predicates predorder
   in
   let hazards = List.map (inf'hazard ctx) spec.hazards in
   let transfers = List.map (inf'transfer ctx) spec.transfers in

   (*
    * resolution pass
    *)

   Types.StringMap.iter (res'enumtype ctx) enumtypes;
   let subenums = Types.StringMap.map (res'subenum ctx) subenums in
   Types.StringMap.iter (res'field ctx) fields;

   let predicates =
      Types.stringmap_mapi_inorder (res'predicatedecl ctx) predicates predorder
   in
   let hazards = List.map (res'hazard ctx) hazards in
   let transfers = List.map (res'transfer ctx) transfers in

   (*
    * check pass
    *)

   Types.StringMap.iter done'enumtype enumtypes;
   Types.StringMap.iter done'subenum subenums;
   Types.StringMap.iter done'field fields;

   Types.StringMap.iter done'predicatedecl predicates;
   List.iter done'hazard hazards;
   List.iter done'transfer transfers;

   (*
    * Done
    *)

   { spec with enumtypes; subenums; fields; predicates; hazards; transfers; }
