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

module TI = Exprtypeinf

open Rep

(**************************************************************)
(* scopes *)

(* XXX should have a common scope implementation *)

type 't scope = {
   bindings: 't Types.StringMap.t ref;
   inner: 't scope option ref;
}

let newscope () = {
   bindings = ref Types.StringMap.empty;
   inner = ref None;
}

let stringmap_get name m =
   try
      Some (Types.StringMap.find name m)
   with Not_found -> None

let rec scope_get name { bindings; inner; } =
   match stringmap_get name !bindings, !inner with
        Some x, _ -> Some x
      | None, Some inner' -> scope_get name inner'
      | None, None -> None

let scope_gethere name { bindings; _ } =
   stringmap_get name !bindings

let scope_existshere name s =
   scope_gethere name s <> None

(* unused
let scope_filterkeys pred { bindings; _ } =
   let key (k, _v) = k in
   List.filter pred (List.map key (Types.StringMap.bindings !bindings))
*)

let scope_filtervals pred { bindings; _ } =
   let value (_k, v) = v in
   List.filter pred (List.map value (Types.StringMap.bindings !bindings))

let scope_add name v { bindings; _ } =
   bindings := Types.StringMap.add name v !bindings

(*
let scope_push scope =
   { bindings = ref Types.StringMap.empty; inner = Some scope; }

let scope_pop { inner; _ } = match inner with
     None -> Util.crash "typecheck: scope_pop: nothing to pop"
   | Some inner' -> inner'
*)

let scope_push scope =
   let inner = {
      bindings = ref !(scope.bindings);
      inner = ref !(scope.inner);
   } in
   scope.bindings := Types.StringMap.empty;
   scope.inner := Some inner

let scope_pop scope = match !(scope.inner) with
     None -> Util.crash "typecheck: scope_pop: nothing to pop"
   | Some inner' ->
        scope.bindings := !(inner'.bindings);
        scope.inner := !(inner'.inner)

(**************************************************************)
(* context *)

type context = {
   tictx: TI.context;

   spec: spec;
   addrtype: typename;

   (* types *)
   plaintypes: Types.StringSet.t ref;
   argtypes: Types.StringSet.t ref;

   (* variables *)
   vars: typename scope;
}

let newctx spec addrtype = {
   tictx = TI.newctx ();
   spec;
   addrtype;

   plaintypes = ref builtin_plaintypes;
   argtypes = ref builtin_argtypes;

   vars = newscope ();
}

let ctx_pushscope ctx =
   scope_push ctx.vars

let ctx_popscope ctx =
   scope_pop ctx.vars

let ctx_isplaintype (ctx : context) name =
   Types.StringSet.mem name !(ctx.plaintypes)

let ctx_isargtype (ctx : context) name =
   Types.StringSet.mem name !(ctx.argtypes)

let ctx_getcompoundtype ctx ctor =
   try
      Some (Types.StringMap.find ctor ctx.spec.compoundtypes)
   with Not_found ->
      None

let ctx_getvar ctx name =
   scope_get name ctx.vars

let ctx_addvar ctx name ty =
   if name = "_" then ()
   else if scope_existshere name ctx.vars then
      (* should have been caught by Relocscheck *)
      Util.crash ("typeinf: var " ^ name ^ " already exists")
   else
      scope_add name ty ctx.vars

let ctx_getencfield ctx pos name =
   try
      Types.StringMap.find name ctx.spec.encfields
   with Not_found ->
      Pos.sayat pos ("No encoding field named " ^ name);
      Util.fail ();
      (* make one up *)
      let ty = TI.failuretype in {
         name;
         definedat=pos;
         canuse=true;
         ty;
         bitpos=0;
         offset=0;
      }

(**************************************************************)
(* hooks to type inference machinery in exprtypeinf *)

let unify' ctx pos ty ty2 =
   TI.unify' ctx.tictx pos ty ty2

let improvetype ctx ty =
   TI.improvetype ctx.tictx ty

let inf'expr ctx e =
   TI.inf'expr ctx.tictx e

let res'type ctx t =
   TI.res'type ctx.tictx t

let res'expr ctx e =
   TI.res'expr ctx.tictx e


(**************************************************************)
(* statements *)

let rec inf'pat ctx ty pat = match pat with
     SETVAR (pos, name) -> begin
        match ctx_getvar ctx name with
             Some ty2 -> ignore (unify' ctx pos ty ty2); pat
           | None -> ctx_addvar ctx name ty; pat
     end
   | SETFIELD (pos, e, name) -> begin
        let e' = inf'expr ctx e in
        (* don't try to infer based on the field name; it doesn't work well *)
        SETFIELD (pos, e', name)
     end
   | UNPACK (pos, "modimm", [arg0; arg1]) ->
        (* XXX this should not exist *)
        ignore (unify' ctx pos ty (WIDTHTYPE ("uint", 32)));
	let arg0' = inf'pat ctx (WIDTHTYPE ("uint", 4)) arg0 in
	let arg1' = inf'pat ctx (WIDTHTYPE ("uint", 8)) arg1 in
        UNPACK (pos, "modimm", [arg0'; arg1'])
   | UNPACK (pos, ctor, args) ->
        ignore (unify' ctx pos ty (PLAINTYPE ctor));
        match ctx_getcompoundtype ctx ctor with
             None ->
                Pos.sayat pos ("Cannot unpack non-compound type " ^ ctor);
                Util.fail ();
                pat
           | Some argtys ->
	       let numargtys = List.length argtys in
	       let numargs = List.length args in
	       if numargtys <> numargs then begin
		  Pos.sayat pos ("Wrong number of elements for " ^ ctor ^
                                 "; " ^ "expected " ^ string_of_int numargtys ^
				 " but found " ^ string_of_int numargs);
		  Util.fail ()
	       end;
	       let pairs = Util.zip' argtys args in
	       let dopair ((_pos, argty), arg) =
		  inf'pat ctx argty arg
	       in
	       let args' = List.map dopair pairs in
               UNPACK (pos, ctor, args')

let inf'assignment ctx (pos, pat, e) =
   let e' = inf'expr ctx e in
   let t' = exprtype e' in
   let pat' = inf'pat ctx t' pat in
   (pos, pat', e')

let rec inf'statement ctx s = match s with
     ASSIGN (pos, pat, e) ->
       let (pos', pat', e') = inf'assignment ctx (pos, pat, e) in
       ASSIGN (pos', pat', e')
(*
   | USE (pos, name, es, ops, unset_resolvedname) ->
       let es' = List.map (inf'expr ctx) es in
       let ops' = List.map (inf'expr ctx) ops in
       USE (pos, name, es', ops', unset_resolvedname)
*)
   | IF (pos, c, t, f) ->
       let c' = inf'expr ctx c in
       ignore (unify' ctx pos booltype (exprtype c'));
       let t' = inf'statement ctx t in
       let f' = inf'statement ctx f in
       IF (pos, c', t', f')
(*
   | EMIT (pos, _e) ->
(* the following is correct, but unneeded *)
(*
       let pcunittype = WIDTHTYPE ("uint", ctx.spec.pcunitwidth) in
       let e' = inf'expr ctx e in
       ignore (unify' ctx pos pcunittype (exprtype e'));
*)
       (* EMIT is only added downstream *)
       Pos.crashat pos "typeinf: invalid EMIT"
   | HOOK (pos, _name, _args) ->
       (* HOOK is only added downstream *)
       Pos.crashat pos "typeinf: invalid HOOK"
*)
   | WARN (pos, text) ->
       (* nothing to do *)
       WARN (pos, text)
   | REQUIRE (pos, e) ->
       let e' = inf'expr ctx e in
       ignore (unify' ctx pos booltype (exprtype e'));
       REQUIRE (pos, e')
   | BLOCK ss ->
       let ss' = List.map (inf'statement ctx) ss in
       BLOCK ss'

(**************************************************************)
(* declarations *)

let inf'encfield _ctx { name; definedat; canuse; ty; bitpos; offset; } =
   (* only fields of integer type can be relocated *)
   (*
    * XXX: this will probably not be adequate in general, since someone
    * will want relocations that do code relaxations or the like, but the
    * the framework we have so far only works for integer computations.
    * To do code relaxations we'll need things like the ability to match
    * in fields, and it'll want to be integrated a lot more closely with
    * encodings as well. FUTURE, when/if it comes up.
    *)
   let canuse = match canuse, ty with
        true, WIDTHTYPE ("int", _) -> true
      | true, WIDTHTYPE ("uint", _) -> true
      | _, _ -> false
   in
   { name; definedat; canuse; ty; bitpos; offset; }

(* strip off "expression" from the modifier signature *)
(* XXX modifiers should be polymorphic over this but typeinf
   can't handle it yet *)
let modifierfix at rt =
   match at, rt with
        EXPRTYPE at', EXPRTYPE rt' -> (at', rt')
      | _, _ -> (at, rt)

let inf'modifier ctx { name; definedat;
		       argname; argtype; symname; resulttype;
		       semantics; } =
   (* XXX this shouldn't be necessary *)
   let (argtype, resulttype) = modifierfix argtype resulttype in

   ctx_pushscope ctx;
   ctx_addvar ctx symname resulttype;
   ctx_addvar ctx argname argtype;
   let semantics = List.map (inf'statement ctx) semantics in
   ctx_popscope ctx;
   { name; definedat; argname; argtype; symname; resulttype; semantics; }

let inf'relocfield ctx { fieldname; extfieldname; definedat;
			 symname; input; output;
                         ty; frominstruction; } =
   let ty =
      if frominstruction then
         let encfield = ctx_getencfield ctx definedat extfieldname in
         encfield.ty   
      else ty
   in

   ctx_pushscope ctx;
   ctx_addvar ctx fieldname ty;
   ctx_addvar ctx "input" ctx.addrtype;
   ctx_addvar ctx "location" ctx.addrtype;
   let input = List.map (inf'statement ctx) input in
   ctx_popscope ctx;

   ctx_pushscope ctx;
   ctx_addvar ctx "output" ctx.addrtype;
   ctx_addvar ctx fieldname ty;
   ctx_addvar ctx "location" ctx.addrtype;
   let output = List.map (inf'statement ctx) output in
   ctx_popscope ctx;

   { fieldname; extfieldname; definedat;
     symname; input; output;
     ty; frominstruction; }

let inf'operation ctx { opername; definedat; actions; } =
   ctx_pushscope ctx;
   ctx_addvar ctx "symbol" ctx.addrtype;
   ctx_addvar ctx "addend" ctx.addrtype;
   ctx_addvar ctx "location" ctx.addrtype;
   let actions = List.map (inf'statement ctx) actions in
   ctx_popscope ctx;

   { opername; definedat; actions; }

let inf'code _ctx c =
   (* nothing to do *)
   c

let inf'codes ctx cs =
   List.map (inf'code ctx) cs

(**************************************************************)
(* spec *)

let inf'spec ctx spec =
   let map = Types.StringMap.map in

   let {
        addresswidth;
        pcunitwidth;
        compoundtypes;
        encfields;
        modifiers;
        relocfields;
        operations;
        allcodes;
   } = spec in

   let encfields =    map (inf'encfield ctx)         encfields       in
   let modifiers =    List.map (inf'modifier ctx)    modifiers       in
   let relocfields =  List.map (inf'relocfield ctx)  relocfields     in
   let operations  =  List.map (inf'operation ctx)   operations      in
   let allcodes =     map (inf'codes ctx)            allcodes        in

   {
        addresswidth;
        pcunitwidth;
        compoundtypes;
        encfields;
	modifiers;
	relocfields;
	operations;
	allcodes;
   }

(**************************************************************)
(* resolve inferred types *)

let res'assignment ctx (pos, name, e) =
   (pos, name, res'expr ctx e)

let rec res'statement ctx r = match r with
     ASSIGN (pos, name, e) ->
        let e' = res'expr ctx e in
        ASSIGN (pos, name, e')
(*
   | USE (pos, name, es, ops, resolvedname_unset) ->
        let es' = List.map (res'expr ctx) es in
        let ops' = List.map (res'expr ctx) ops in
        USE (pos, name, es', ops', resolvedname_unset)
*)
   | IF (pos, c, t, f) ->
        let c' = res'expr ctx c in
        let t' = res'statement ctx t in
        let f' = res'statement ctx f in
        IF (pos, c', t', f')
(*
   | EMIT (pos, e) ->
        let e' = res'expr ctx e in
        EMIT (pos, e')
   | HOOK (pos, name, args) ->
        let args' = List.map (res'expr ctx) args in
        HOOK (pos, name, args')
*)
   | WARN (pos, text) ->
        WARN (pos, text)
   | REQUIRE (pos, e) ->
        let e' = res'expr ctx e in
        REQUIRE (pos, e')
   | BLOCK ss ->
        let ss' = List.map (res'statement ctx) ss in
        BLOCK ss'

let res'modifier ctx { name; definedat;
		       argname; argtype; symname; resulttype;
		       semantics; } =
   let semantics = List.map (res'statement ctx) semantics in
   { name; definedat; argname; argtype; symname; resulttype; semantics; }


let res'relocfield ctx { fieldname; extfieldname; definedat;
			 symname; input; output;
                         ty; frominstruction; } =
   let input = List.map (res'statement ctx) input in
   let output = List.map (res'statement ctx) output in

   { fieldname; extfieldname; definedat;
     symname; input; output;
     ty; frominstruction; }

let res'operation ctx { opername; definedat; actions; } =
   let actions = List.map (res'statement ctx) actions in

   { opername; definedat; actions; }

let res'code _ctx c =
   (* nothing to do *)
   c

let res'codes ctx cs =
   List.map (res'code ctx) cs

let res'spec ctx spec =
   let map = Types.StringMap.map in

   let {
        addresswidth;
        pcunitwidth;
        compoundtypes;
        encfields;
        modifiers;
        relocfields;
        operations;
        allcodes;
   } = spec in

(* nothing to do for encfields
   let encfields =    map (res'encfield ctx)         encfields       in
*)
   let modifiers =    List.map (res'modifier ctx)    modifiers       in
   let relocfields =  List.map (res'relocfield ctx)  relocfields     in
   let operations  =  List.map (res'operation ctx)   operations      in
   let allcodes =     map (res'codes ctx)            allcodes        in

   {
        addresswidth;
        pcunitwidth;
        compoundtypes;
        encfields;
	modifiers;
	relocfields;
	operations;
	allcodes;
   }

(**************************************************************)
(* make sure we're done (no temporary types left) *)

(* patterns don't actually have types in them *)
let done'pattern _pat = ()

let done'assignment (_pos, pat, e) =
   done'pattern pat;
   TI.done'expr e

let rec done'statement r = match r with
     ASSIGN a -> done'assignment a
   | IF (_pos, c, t, f) ->
        TI.done'expr c;
        done'statement t;
        done'statement f
(*
   | USE (_pos, _name, es, ops, _resolvedname_unset) ->
        List.iter TI.done'expr es;
        List.iter TI.done'expr ops
   | EMIT (_pos, e) ->
        TI.done'expr e
   | HOOK (_pos, _name, args) ->
        List.iter TI.done'expr args
*)
   | WARN (_pos, _text) ->
        ()
   | REQUIRE (_pos, e) ->
        TI.done'expr e
   | BLOCK ss ->
        List.iter done'statement ss

let done'modifier (mod_: modifier) =
   List.iter done'statement mod_.semantics

let done'relocfield (rf: relocfield) =
   List.iter done'statement rf.input;
   List.iter done'statement rf.output

let done'operation (oper: operation) =
   List.iter done'statement oper.actions

let done'code (_c: code) =
   (* nothing to do *)
   ()

let done'codes _ cs =
   List.iter done'code cs

let done'spec spec =
   let iter = Types.StringMap.iter in

   let {
        (*encfields;*)
        modifiers;
        relocfields;
        operations;
        allcodes;
        _
   } = spec in

(* nothing to do for encfields
   iter done'encfield           encfields;
*)
   List.iter done'modifier      modifiers;
   List.iter done'relocfield    relocfields;
   List.iter done'operation     operations;
   iter done'codes              allcodes

(**************************************************************)
(* callback hooks *)

(*
 * Callback hooks for the common typeinf code
 *)

let unalias_type _ ty = ty

let lookup_compoundtype (_ctx: context) _ctor =
(*
   scope_get ctor ctx.compoundtypes
*)
   None

let lookup_variable ctx name =
   ctx_getvar ctx name

let lookup_modifier ctx modname =
(*
   try
      let mi = Types.StringMap.find modname ctx.spec.modifiers in
      Some (mi.definedat, mi.argtype, mi.resulttype)
   with Not_found -> None
*)
   let findit res (mi: modifier) =
      if mi.name = modname then 
         let (argtype, resulttype) = modifierfix mi.argtype mi.resulttype in
         Some (mi.definedat, argtype, resulttype)
      else res
   in
   List.fold_left findit None ctx.spec.modifiers

(**************************************************************)
(* top level *)

let typeinf spec =
   let addrtype = (WIDTHTYPE ("uint", spec.addresswidth)) in
   let ctx = newctx spec addrtype in

   (* this must be built after the initial context construction *)
   let callbacks = {
      TI.unalias_type = unalias_type ctx;
      TI.lookup_compoundtype = lookup_compoundtype ctx;
      TI.lookup_variable = lookup_variable ctx;
      TI.lookup_modifier = lookup_modifier ctx;
   } in
   TI.setcallbacks ctx.tictx callbacks;

(*
   let builtinpos = { Pos.file = "<builtin>"; Pos.line=0; Pos.column=0; } in
*)
   ctx_addvar ctx "true" booltype;
   ctx_addvar ctx "false" booltype;
   ctx_addvar ctx "." ctx.addrtype;

   (* First, run inference on the whole thing. *)
   let spec = inf'spec ctx spec in

   (* Resolve all the types we can. *)
   let spec = res'spec ctx spec in

   (* Now we'd better be done resolving. *)
   done'spec spec;

   Util.checkfail ();

   spec
