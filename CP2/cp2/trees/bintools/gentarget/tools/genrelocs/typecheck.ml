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

module TC = Exprtypecheck

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
   tcctx: TC.context;

   spec: spec;
   addrtype: typename;

   (* namespaces *)
   alltypes: (Pos.pos * bool * (Pos.pos * typename) list) scope;
   allvars: (Pos.pos * typename) scope;

   (* assigned variables tracking *)
   assignedvars: unit scope;
}

let newcontext s addrtype = {
   tcctx = TC.newctx ();
   spec = s;
   addrtype;
   alltypes = newscope ();
   allvars = newscope ();
   assignedvars = newscope ();
}

let pushscope ctx =
   scope_push ctx.allvars;
   scope_push ctx.assignedvars

let popscope ctx =
   scope_pop ctx.allvars;
   scope_pop ctx.assignedvars

let ctx_getencfield ctx pos name =
   try
      Types.StringMap.find name ctx.spec.encfields
   with Not_found ->
      Pos.sayat pos ("No encoding field named " ^ name);
      Util.fail ();
      (* make one up *)
      let ty=TC.failuretype in
      { name; definedat=pos; canuse=true; ty; bitpos=0; offset=0; }

(*
let ctx_getcompoundtype ctx ctor =
   try
      Some (Types.StringMap.find ctor ctx.spec.compoundtypes)
   with Not_found ->
      None
*)

(**************************************************************)
(* tools *)

let tystr ty = 
   dump'typename ty

(**************************************************************)
(* dispatches to common typecheck code *)

let typemismatch = TC.typemismatch

let check'typename ctx ty =
   TC.check'typename ctx.tcctx ty

let check'typename'aliasok ctx ty =
   TC.check'typename'aliasok ctx.tcctx ty

let check'expr ctx e =
   TC.check'expr ctx.tcctx e

(**************************************************************)
(* forms and fields *)

(*
 * encoding fields:
 *
 * 0. The name must not already exist. (Fields have their own
 *    namespace.) This is implied by fields being stored in a
 *    Types.StringMap.
 *
 * 1. The type must be valid.
 *
 * 2. The type must be allowable for fields: signed or unsigned
 *    integer, zeros, ones, or an enum. This is enforced in
 *    genencoding so we don't need to do it again here.
 *)
let check'encfield ctx _ (ef: encfield) =
   if ef.canuse then begin
      check'typename ctx ef.definedat ef.ty
   end
   (* otherwise the type might be one we don't know *)

(**************************************************************)
(* statements *)

let rec check'pattern ctx pat ty = match pat with
     SETVAR (pos, name) -> begin
        scope_add name () ctx.assignedvars;
        match scope_get name ctx.allvars with
             None ->
                scope_add name (pos, ty) ctx.allvars;
           | Some (_defpos, ty'stored) ->
                if ty <> ty'stored then
                   typemismatch pos ty'stored ty ("assignment of " ^ name)
     end
   | SETFIELD (pos, e, name) ->
        let ty'e = check'expr ctx e in
        (*
         * XXX this should not be hardwired
         *)
        let ty'name = match ty'e with
             PLAINTYPE "relocation" -> begin
	        match name with
                     (* XXX should have a reloccodetype *)
                     (* (and it shoud be an enum...) *)
                     "code" -> WIDTHTYPE ("int", 32) 
                   | "symbol" -> stringtype
                   | "offset" -> ctx.addrtype
                   | "addend" -> ctx.addrtype
                   | _ ->
                        Pos.sayat pos ("No such field " ^ name ^ " in type " ^
                                       tystr ty'e);
                        Util.fail ();
                        TC.failuretype
             end
           | _ -> Pos.sayat pos ("Field reference in non-structure type " ^
                                 tystr ty'e);
                  Util.fail ();
                  TC.failuretype
        in
        if ty <> ty'name then
           typemismatch pos ty'name ty ("assignment of field " ^ name ^
                                        " in type " ^ tystr ty'e)
   | UNPACK (pos, "modimm", [arg0; arg1]) -> begin
        (* XXX this should not exist *)
        match ty with
            WIDTHTYPE ("uint", 32) ->
               check'pattern ctx arg0 (WIDTHTYPE ("uint", 4));
               check'pattern ctx arg1 (WIDTHTYPE ("uint", 8))
          | _ ->
               Pos.sayat pos "Cannot unpack modimm; expected uint(32)";
               Util.fail ()
     end
   | UNPACK (pos, ctor, pats) ->
        match scope_get ctor ctx.alltypes with
             None ->
                Pos.sayat pos ("No such compound type " ^ ctor);
                Util.fail ()
           | Some (_defpos, _haswidth, []) ->
                Pos.sayat pos ("Type " ^ ctor ^ " is not unpackable");
                Util.fail ()
           | Some (defpos, _haswidth, argtypes) ->
                let n'expected = List.length argtypes in
                let n'found = List.length pats in
                if n'expected <> n'found then begin
                   Pos.sayat pos ("Wrong number of elements unpacking type " ^
                                  ctor ^ ": found " ^ string_of_int n'found ^
                                  " but expected " ^
			          string_of_int n'expected);
                   Pos.sayat defpos "Type declaration";
                   Util.fail ();
                end;
                let checkone (pat, (_defpos, ty)) =
                   check'pattern ctx pat ty
                in
                List.iter checkone (Util.zip' pats argtypes)

let check'assignment ctx (_pos, pat, e) =
   let ty'e = check'expr ctx e in
   check'pattern ctx pat ty'e

let rec check'statement ctx s =
   match s with
        ASSIGN (pos, pat, e) ->
           check'assignment ctx (pos, pat, e)
      | IF (pos, c, t, f) -> begin
           let ty'c = check'expr ctx c in
           if ty'c <> booltype then
              typemismatch pos booltype ty'c "control of if-expression"
           ;
           check'statement ctx t;
           check'statement ctx f
        end
      | WARN (_pos, _text) ->
           ()
      | REQUIRE (pos, e) -> begin
           let ty'e = check'expr ctx e in
           if ty'e <> booltype then
              typemismatch pos booltype ty'e "argument of REQUIRE"
        end
      | BLOCK ss ->
           List.iter (check'statement ctx) ss


(**************************************************************)
(* declarations *)

(* strip off "expression" from the modifier signature *)
(* XXX modifiers should be polymorphic over this but typeinf
   can't handle it yet *)
let modifierfix at rt =
   match at, rt with
        EXPRTYPE at', EXPRTYPE rt' -> (at', rt')
      | _, _ -> (at, rt)

let check'modifier ctx { (*name;*) definedat;
                         argname; argtype; symname; resulttype;
                         semantics; } =
   (* XXX this shouldn't be needed *)
   let (argtype, resulttype) = modifierfix argtype resulttype in

   check'typename ctx definedat argtype;
   check'typename ctx definedat resulttype;

   pushscope ctx;
   scope_add argname (definedat, argtype) ctx.allvars;
   scope_add symname (definedat, resulttype) ctx.allvars;
   List.iter (check'statement ctx) semantics;
   popscope ctx   

let check'relocfield ctx { fieldname; extfieldname; definedat;
			   (*symname;*) input; output;
                           ty; frominstruction; } =
   check'typename ctx definedat ty;

   if frominstruction then begin
      let encfield = ctx_getencfield ctx definedat extfieldname in
      if encfield.canuse = false then begin
         let n =
            if fieldname <> extfieldname then
               extfieldname ^ " (" ^ fieldname ^ ")"
            else fieldname
         in
         Pos.sayat definedat ("Cannot relocate in instruction field " ^
                              n ^ " because it has non-integer type");
         Util.fail ()
      end
      else if ty <> encfield.ty then begin
         typemismatch definedat ty encfield.ty "Type of reloc field"
      end
   (* otherwise the type was declared explicitly so it's inherently ok *)
   end;

   pushscope ctx;
   scope_add fieldname (definedat, ty) ctx.allvars;
   scope_add "input" (definedat, ctx.addrtype) ctx.allvars;
   scope_add "location" (definedat, ctx.addrtype) ctx.allvars;
   List.iter (check'statement ctx) input;
   popscope ctx;

   pushscope ctx;
   scope_add "output" (definedat, ctx.addrtype) ctx.allvars;
   scope_add fieldname (definedat, ty) ctx.allvars;
   scope_add "location" (definedat, ctx.addrtype) ctx.allvars;
   List.iter (check'statement ctx) output;
   popscope ctx

let check'operation ctx { (*opername;*) definedat; actions; } =

   pushscope ctx;
   scope_add "symbol" (definedat, ctx.addrtype) ctx.allvars;
   scope_add "addend" (definedat, ctx.addrtype) ctx.allvars;
   scope_add "location" (definedat, ctx.addrtype) ctx.allvars;
   List.iter (check'statement ctx) actions;
   popscope ctx

let check'code opernames rfnames { symname; definedat; (*num;*) behavior; } =
   match behavior with
        NOP -> ()
      | UNSUPPORTED -> ()
      | APPLYIN (oper, rfs, _dogenerate) -> begin
           if not (Types.StringSet.mem oper opernames) then begin
              Pos.sayat definedat ("No such operation " ^ oper ^ " in code " ^
                                   symname);
              Util.fail ()
           end;
           (*
            * XXX: this should also check that the bit positions of the
            * fields are such that (a) the first listed field is the
            * smallest one (it is the one the linker will use for access)
            * and that (b) all the other ones are bit supersets of it,
            * and also (c) ideally the lowest-significant-bit of all the
            * fields is the same.
            *
            * I don't remember at the moment if the positions of the
            * fields are checked in encodingcheck or only downstream in
            * genencoding. Probably the latter since it requires knowing
            * widths and that requires base.def. That means we'll have to
            * replicate the logic here (ugh) or share it (also ugh).
            *
            * Note that it is in general ok to use a small relocation
            * in a larger field (e.g. something that produces a 10-bit
            * value in a 12-bit field) but not the other way around
            * (which would trash bits used by the target instruction for
            * other things) which is why the linker should use the
            * smallest field the relocation can be applied to.
            *
            * XXX: so should we as the typechecker... nothing seems to be
            * checking operation result types against field widths.
            *)
           let checkone rf =
              if not (Types.StringSet.mem rf rfnames) then begin
                 Pos.sayat definedat ("No such reloc field " ^ rf ^
                                      " in code " ^ symname);
                 Util.fail ()
              end
           in
           List.iter checkone rfs
        end

let check'codes ctx _ cs =
   (* XXX we should check the binary format names attached to the opers *)
   let opernames_list =
      List.map (fun o -> o.opername) ctx.spec.operations 
   in
   let opernames = Types.stringset_of_list opernames_list in

   let rfnames_list =
      List.map (fun rf -> rf.fieldname) ctx.spec.relocfields
   in
   let rfnames = Types.stringset_of_list rfnames_list in

   List.iter (check'code opernames rfnames) cs;

   let isdup tbl (c: code) =
      try
         let oldpos = Types.IntMap.find c.num tbl in
         Pos.sayat c.definedat ("Duplicate relocation code " ^
                                 string_of_int c.num);
         Pos.sayat oldpos ("Previous declaration");
         Util.fail ();
         tbl
      with Not_found ->
         Types.IntMap.add c.num c.definedat tbl
   in
   let _  = List.fold_left isdup Types.IntMap.empty cs in
   ()

(**************************************************************)
(* callback hooks for common typechecker code *)

let lookup_aliastype _ctx _name =
   None

let lookup_type ctx name =
   scope_get name ctx.alltypes 

let lookup_var ctx name =
   scope_get name ctx.allvars

let lookup_modifier ctx modname =
(*
   try
      let m = Types.StringMap.find name ctx.spec.modifiers in
      Some (m.argtype, m.resulttype)
   with Not_found -> None
*)
   let findit res (mi: modifier) =
      if mi.name = modname then Some (modifierfix mi.argtype mi.resulttype)
      else res
   in
   List.fold_left findit None ctx.spec.modifiers

(**************************************************************)
(* top level *)

let typecheck spec =
   let addrtype = (WIDTHTYPE ("uint", spec.addresswidth)) in

   (* basic checks first *)
   let ctx = newcontext spec addrtype in
   let callbacks = {
      TC.lookup_aliastype = lookup_aliastype ctx;
      TC.lookup_type = lookup_type ctx;
      TC.lookup_var = lookup_var ctx;
      TC.lookup_modifier = lookup_modifier ctx;
   } in
   TC.setcallbacks ctx.tcctx callbacks;

   let builtinpos = Pos.builtin in
   let buildintype haswidth name =
      scope_add name (builtinpos, haswidth, []) ctx.alltypes
   in
   Types.StringSet.iter (buildintype false) builtin_plaintypes;
   Types.StringSet.iter (buildintype true) builtin_argtypes;

   let addcompoundtype ctor members =
      scope_add ctor (builtinpos, false, members) ctx.alltypes
   in
   Types.StringMap.iter addcompoundtype spec.compoundtypes;

   scope_add "true" (builtinpos, booltype) ctx.allvars;
   scope_add "false" (builtinpos, booltype) ctx.allvars;
   (* XXX we shouldn't know the type of addresses here *)
   scope_add "." (builtinpos, addrtype) ctx.allvars;

   Types.StringMap.iter (check'encfield ctx) spec.encfields;
   List.iter (check'modifier ctx) spec.modifiers;
   List.iter (check'relocfield ctx) spec.relocfields;
   List.iter (check'operation ctx) spec.operations;
   Types.StringMap.iter (check'codes ctx) spec.allcodes;

   (* allow consistency checks to rely on well-formedness *)
   Util.checkfail();

   (* consistency checks (none yet) *)
   ()


