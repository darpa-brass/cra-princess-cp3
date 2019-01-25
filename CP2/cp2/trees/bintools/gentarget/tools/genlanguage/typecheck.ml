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

(*
 * Typecheck the representation.
 *
 * This must perform the following checks that cannot be in langcheck.ml:
 *    - all TY_ENUM must refer to enumerations that exist
 *    - all E_READENUM must refer to enumeration constants that exist
 * and it also fills in the proper type in E_READENUM since we won't
 * previously know that.
 *
 * This also returns two maps with the enum type info: one that maps
 * enum type names to (pos, bitwidth, members) and one that maps
 * member names to (pos, typename, value).
 *
 * XXX: we also need to check that types appearing in tokens are ok
 * to be in tokens; enums are ok but some types aren't (and, can we
 * please get a clear concept of which aren't?)
 *)

open Typerep
open Exprrep
open Rep

open Exprutil
module TC = Exprtypecheck

(**************************************************************)
(* context *)

type context = {
   tcctx: TC.context;

   spec: spec;

   alltokens: (Pos.pos * typename) Types.StringMap.t ref;
   allvars: (Pos.pos * typename) Types.scope ref;
   beforenumerate: bool;
}

let ctx_addtoken ctx name pos ty =
   ctx.alltokens := Types.StringMap.add name (pos, ty) !(ctx.alltokens)

let ctx_addvar ctx name pos ty =
   ctx.allvars := Types.scope_add name (pos, ty) !(ctx.allvars)

let lookup_type ctx name =
   try
      let (pos, _width, _members) =
         Types.StringMap.find name ctx.spec.enumtypes
      in
      (* definedat, takeswidth, components/args if a compound type *)
      (* note: takeswidth should be true if a width must be supplied *)
      (* enums already have a width baked into them *)
      Some (pos, false, [])
   with Not_found ->
   try
      let (pos, elements) = Types.StringMap.find name ctx.spec.compoundtypes in
      Some (pos, false, elements)
   with Not_found ->
      (* XXX we should have a list of builtins *)
      (* also we should just suck it up and use "void", not "_" *)
      match name with
           "string" | "bool" -> Some (Pos.builtin, false, [])
         | "int" | "uint" -> Some (Pos.builtin, true, [])
         | "_" -> Some (Pos.builtin, false, [])
         | _ -> None

let lookup_var ctx name =
   match Types.scope_find name !(ctx.allvars) with
        Some ret -> Some ret
      | None ->
           (* also look for enumeration constants *)
           try
              let (pos, enumname, _val) =
                 Types.StringMap.find name ctx.spec.enumvals
              in
              Some (pos, PLAINTYPE enumname)
           with Not_found ->
              match name with
                   "true" | "false" -> Some (Pos.builtin, PLAINTYPE "bool")
                  | _ ->  None

let newctx spec beforenumerate =
   let ctx = {
      tcctx = TC.newctx ();
      spec;
      alltokens = ref Types.StringMap.empty;
      allvars = ref Types.emptyscope;
      beforenumerate;
   } in
   let callbacks = {
      TC.lookup_aliastype = (fun _ -> None); (* no type aliases *)
      TC.lookup_type = lookup_type ctx;
      TC.lookup_var = lookup_var ctx;
      TC.lookup_modifier = (fun _ -> None) (* no modifiers *)
   } in
   TC.setcallbacks ctx.tcctx callbacks;
   ctx

let ctx_pushscope ctx =
   ctx.allvars := Types.scope_push !(ctx.allvars)

let ctx_popscope ctx =
   ctx.allvars := Types.scope_pop !(ctx.allvars)


(**************************************************************)
(* main pass *)

let badtype = PLAINTYPE "bool" (* XXX: what to use? *)

let typemismatch = TC.typemismatch
let check'typename ctx pos ty = TC.check'typename ctx.tcctx pos ty
let check'expr ctx e = TC.check'expr ctx.tcctx e

let check'tokenexists ctx pos name =
   try
      let (_defpos, ty) = Types.StringMap.find name !(ctx.alltokens) in
      ty
   with Not_found ->
      Pos.sayat pos ("No such token " ^ name);
      Util.fail ();
      badtype

let check'tagexists ctx pos name =
   try
      let (_defpos, ty) = Types.StringMap.find name ctx.spec.operandtags in
      ty
   with Not_found ->
      Pos.sayat pos ("No such operand tag " ^ name);
      Util.fail ();
      badtype

let check'pattern ctx ty'expected opat =
   let docheck pos ty =
      if ty <> ty'expected then
         typemismatch pos ty'expected ty ("value bound")
   in  
   match opat with
        None -> ()
      | Some (BIND (pos, ty, "_")) ->
           check'typename ctx pos ty;
           docheck pos ty
      | Some (BIND (pos, ty, name)) ->
           check'typename ctx pos ty;
           docheck pos ty;
           begin
           match lookup_var ctx name with
                None -> ()
              | Some (defpos, _ty) ->
                   Pos.sayat pos ("Duplicate binding of " ^ name);
                   Pos.sayat defpos ("Previous binding");
                   Util.fail ()
           end;
           ctx_addvar ctx name pos ty
      | Some (MATCHSTR (pos, _k)) ->
           docheck pos (PLAINTYPE "string")
      | Some (MATCHINT (pos, _k)) ->
           docheck pos ctx.spec.numtype

let check'tokenexpr ctx (pos, name, oe) =
   let ty = check'tokenexists ctx pos name in
   match oe with
        None -> ()
      | Some e ->
           let ty'e = check'expr ctx e in
           if ty'e <> ty then
              typemismatch pos ty ty'e ("value for token " ^ name)

let check'tagexpr ctx (pos, name, oe) =
   let ty = check'tagexists ctx pos name in
   match Some oe (* XXX *) with
        None -> ()
      | Some e ->
           let ty'e = check'expr ctx e in
           if ty'e <> ty then
              (* XXX numerate doesn't numerate the types of operandtags *)
              (* hack around it forcibly *)
              if ctx.beforenumerate then
                 typemismatch pos ty ty'e ("value for tag " ^ name)

let check'tokenpattern ctx (pos, name, pat) =
   let ty = check'tokenexists ctx pos name in
   check'pattern ctx ty pat

let check'exprpattern ctx epat =
   match epat with
        TOKEN tpat ->
           check'tokenpattern ctx tpat
      | EXPR (_pos, tpats, pat) ->
           List.iter (check'tokenpattern ctx) tpats;
           check'pattern ctx (EXPRTYPE ctx.spec.addrtype) pat
      | EXPRANY (_pos, pat) ->
           check'pattern ctx (EXPRTYPE ctx.spec.addrtype) pat

let check'token ctx name (pos, typename, _istarget) =
   check'typename ctx pos typename;
   begin
      try
         let (defpos, _ty) = Types.StringMap.find name !(ctx.alltokens) in
         Pos.sayat pos ("Duplicate token name " ^ name);
         Pos.sayat defpos ("Previous declaration");
         Util.fail ()
      with Not_found -> ()
   end;
   ctx_addtoken ctx name pos typename

let check'matchdecl ctx (_pos, pats, te) =
   ctx_pushscope ctx;
   List.iter (check'tokenpattern ctx) pats;
   check'tokenexpr ctx te;
   ctx_popscope ctx

let check'tagrule ctx (pos, pats, guard, te) =
   ctx_pushscope ctx;
   List.iter (check'exprpattern ctx) pats;
   let ty'guard = check'expr ctx guard in
   let ty = PLAINTYPE "bool" in
   if ty'guard <> ty then
      typemismatch pos ty ty'guard ("value for guard expression")
   ;
   check'tagexpr ctx te;
   ctx_popscope ctx

(**************************************************************)
(* toplevel *)

let typecheck spec beforenumerate =
   let ctx = newctx spec beforenumerate in

   Types.StringMap.iter (check'token ctx) spec.tokens; 
   List.iter (check'matchdecl ctx) spec.matches;
   List.iter (check'tagrule ctx) spec.tagrules
