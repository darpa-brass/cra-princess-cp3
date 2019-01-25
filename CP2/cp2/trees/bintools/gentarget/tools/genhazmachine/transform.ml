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

open Rep
module ET = Exprtransform

(*
 * Miscellaneous transforms.
 *)

(**************************************************************)
(* number_matchers *)

(*
 * Give each matcher an ID number. This will be used in the state
 * management machinery.
 *)
let number_matchers spec =
   let nextid = ref 0 in
   let number_matcher m =
      let id = !nextid in
      nextid := id + 1;
      { m with id; }
   in
   let number_hazard (h: hazard) =
      let m = number_matcher h.m in
      { h with m; }
   in
   let number_transfer (t: transfer) =
      let m = number_matcher t.m in
      { t with m; }
   in
   let hazards = List.map number_hazard spec.hazards in
   let transfers = List.map number_transfer spec.transfers in
   { spec with hazards; transfers; }

(**************************************************************)
(* collect_fields *)

(*
 * This is like Hazresolve.collect_fields but it works on
 * Exprrep and the Hazresolve one works on Exprtree. Sigh.
 * See structural notes in hazresolve.ml.
 *
 * Adds any field variables seen in e to fields and returns a
 * new set. Variables are checked by whether they're present in
 * fmap. What fmap maps to is irrelevant.
 *)

let rec collect_fields gettype fmap fields e =
   let one e1 =
      collect_fields gettype fmap fields e1
   in
   let many es =
      List.fold_left (collect_fields gettype fmap) fields es
   in
   match e with
     CONST _ -> fields
   | STRCONST _ -> fields
   | USEVAR (_pos, _ty, name) -> begin
        try
           let f = Types.StringMap.find name fmap in
           Types.StringMap.add name (gettype f) fields
        with Not_found -> fields
     end
   | USEFIELD (_pos, _ty, e1, _name) -> one e1
   | OP (_pos, _ty, _op, es) -> many es
   | FITS (_pos, _ty, e1, _argty) -> one e1
   | MODE _ -> fields
   | LIST (_pos, _ty, es) -> many es
   | MODIFIER (_pos, _ty, _name, es) -> many es
   | PACK (_pos, _ty, _name, es) -> many es
   | CAST (_pos, _nty, _oty, e1) -> one e1
   | EVAL (_pos, _, _, _, _, e1) -> one e1
   | UNEVAL (_pos, _, e1) -> one e1
   | ANNOTATE (_pos, _ty, e1) -> one e1
   | COMMENTED (_ty, e1) -> one e1

(**************************************************************)
(* numerate: remove enum types and values *)

(*
 * XXX we should probably set up to run this downstream of emitting
 * Gcode, given that Gcode is typed and that some of the Gcode
 * emit logic is nontrivial.
 *)

(*
 * The bulk of the pass is in Exprtransform
 *)
let numeratectx_new = ET.numeratectx_new
let numeratectx_checkclean = ET.numeratectx_checkclean
let numerate'typename = ET.numerate'typename
let numerate'expr = ET.numerate'expr

(*
 * field
 *)
let numerate'field ctx { name; definedat; ty; junk; } =
   let ty = numerate'typename ctx ty in
   { name; definedat; ty; junk; }

(*
 * subenum
 *
 * Builds an assignment for a scratch variable that replaces the
 * subenum value, and stores it in ctx.rangebindings.
 *)
let numerate'subenum ctx _ { name; definedat; ty; selected; } =
   let enumname = match ty with
        LISTTYPE (PLAINTYPE n) -> n
      | _ -> Util.crash ("numerate: subenum " ^ name ^ " has odd type " ^
                         dump'typename ty)
   in
   let values =
      let doadd set (sym, sel) =
         if sel then Types.StringSet.add sym set else set
      in
      List.fold_left doadd Types.StringSet.empty (Types.StringMap.bindings selected)
   in
   ET.numerate'subenum ctx name definedat enumname values

(*
 * predicate
 *)

let numerate'predicatedecl ctx { definedat; args; afields; cfields; es; } =
   let numerate'arg (argpos, argty) =
      (argpos, numerate'typename ctx argty)
   in
   let args = Types.StringMap.map numerate'arg args in

   let numerate'field fty = numerate'typename ctx fty in
   let afields = Types.StringMap.map numerate'field afields in
   let cfields = Types.StringMap.map numerate'field cfields in

   let es = List.map (numerate'expr ctx) es in
   { definedat; args; afields; cfields; es; }

(*
 * matcher
 *)

let numerate'assignment ctx (pos, name, ty, e) =
   let ty = numerate'typename ctx ty in
   let e = numerate'expr ctx e in
   (pos, name, ty, e)

let numerate'matcher ctx { id; guard; assignments; trigger; cond; } =
   let guard = numerate'expr ctx guard in
   let assignments = List.map (numerate'assignment ctx) assignments in
   (* trigger and cond have only strings and don't need direct attention *)
   { id; guard; assignments; trigger; cond; }

(*
 * hazard, transfer
 *)

let numerate'hazard ctx (h: hazard) =
   let m = numerate'matcher ctx h.m in
   { h with m; }

let numerate'transfer ctx (t: transfer) =
   let m = numerate'matcher ctx t.m in
   { t with m; }

(*
 * toplevel
 *)
let numerate {
	modes;
	enumtypes; subenums; fields;
	predicates; predorder; hazards; transfers;
 } =
   let smap = Types.StringMap.map in
   let siter = Types.StringMap.iter in
   let lmap = List.map in

   let loadenum { name; width; elements; } =
      let doadd map (_pos, sym, value) =
         Types.StringMap.add sym value map
      in
      let symtovalue = List.fold_left doadd Types.StringMap.empty elements in
      { ET.name; ET.width; ET.symtovalue; }
   in
   let ctx = numeratectx_new (Types.StringMap.map loadenum enumtypes) in

   let fields =       smap (numerate'field ctx)         fields in
                      siter (numerate'subenum ctx)      subenums;
   let predicates =   smap (numerate'predicatedecl ctx) predicates in
   let hazards =      lmap (numerate'hazard ctx)        hazards in
   let transfers =    lmap (numerate'transfer ctx)      transfers in

   numeratectx_checkclean ctx;

   let enumtypes = Types.StringMap.empty in
   let subenums = Types.StringMap.empty in
   {
	modes;
	enumtypes; subenums; fields;
	predicates; predorder; hazards; transfers;
   }

(**************************************************************)
(* delist: kill off list expressions *)

let delist'expr = ET.delist'expr
let nolist = ET.nolist

(*
 * predicates
 *)

let delist'predicatedecl ctx name { definedat; args; afields; cfields; es; } =
   let delist'arg argname (argpos, argty) =
      nolist argpos argty ("argument " ^ argname ^ " of predicate " ^ name)
   in
   Types.StringMap.iter delist'arg args;

   let delist'field tbl fname fty =
      nolist definedat fty ("field " ^ fname ^ " in " ^ tbl)
   in
   Types.StringMap.iter (delist'field "afields") afields;
   Types.StringMap.iter (delist'field "cfields") cfields;

   let es = List.map (delist'expr ctx) es in
   { definedat; args; afields; cfields; es; }

(*
 * matchers, hazards, transfers
 *)

let delist'assignment ctx (pos, name, ty, e) =
   nolist pos ty "assigned var";
   (pos, name, ty, delist'expr ctx e)

let delist'matcher ctx { id; guard; assignments; trigger; cond; } =
   let guard = delist'expr ctx guard in
   let assignments = List.map (delist'assignment ctx) assignments in
   { id; guard; assignments; trigger; cond; }

let delist'hazard ctx (h: hazard) =
   let m = delist'matcher ctx h.m in
   { h with m; }

let delist'transfer ctx (t: transfer) =
   let m = delist'matcher ctx t.m in
   { t with m; }

(*
 * toplevel
 *)
let delist spec =
   let ctx = ET.delistctx_new () in

   let predicates =
      Types.StringMap.mapi (delist'predicatedecl ctx) spec.predicates
   in
   let hazards =   List.map (delist'hazard ctx)   spec.hazards in
   let transfers = List.map (delist'transfer ctx) spec.transfers in

   { spec with predicates; hazards; transfers; }


(**************************************************************)
(* widen: use type widths that exist *)

(*
 * XXX: we should probably arrange to have one such pass, at least for
 * expressions, and share it among everything that needs it. Catch is
 * that it's somewhat more complicated for genencoding than anywhere
 * else...
 *
 * (Also, is this code adequate? assigning e.g. uint(5) to int(5)
 * requires sign-extension in a wider type, and we don't seem to be
 * doing that here. XXX)
 *)

(*
 * Figure out the real width to use.
 *
 * XXX: this should produce "int", "uint", "long", "ulong", etc.
 * for types that fit into the sizes guaranteed for those C types,
 * and/or maybe check the host's machine word properties, and only
 * fall back to {u,}intNN_t when those aren't good enough. But
 * currently buildtype.ml doesn't allow these types through. It
 * should; *users* shouldn't be allowed to use those types but we
 * should be able to compile down to them. (and I guess typecheck
 * will need a setting to enable them, so they aren't allowed in 
 * the initial typecheck...)
 *
 * For what we're doing in this code there's nothing to be gained
 * by using less than word-sized types, so use either 32 or 64.
 *)
let widen'width w =
   if w <= 32 then 32
   else if w <= 64 then 64
   else w

let rec widen'typename ty = match ty with
     PLAINTYPE name -> PLAINTYPE name
   | WIDTHTYPE (name, width) -> WIDTHTYPE (name, widen'width width)
   | EXPRTYPE ty -> EXPRTYPE (widen'typename ty)
   | LISTTYPE ty -> LISTTYPE (widen'typename ty)
   | TMPTYPE q -> TMPTYPE q

let rec widen'expr e = match e with
     CONST (pos, ty, k) ->
        let ty' = widen'typename ty in
        (* widening to 32 means all constants must be LARGE *)
        let k' = match k with
             SMALL n -> LARGE (Types.Wide.of_int n)
           | LARGE n -> LARGE n
        in
        CONST (pos, ty', k')
   | STRCONST (pos, ty, s) ->
        let ty' = widen'typename ty in
        STRCONST (pos, ty', s)
   | USEVAR (pos, ty, name) ->
        let ty' = widen'typename ty in
        USEVAR (pos, ty', name)
   | USEFIELD (pos, ty, e1, name) ->
        let ty' = widen'typename ty in
        let e1' = widen'expr e1 in
        USEFIELD (pos, ty', e1', name)
   | OP (pos, ty, op, args) ->
        let ty' = widen'typename ty in
        let args' = List.map widen'expr args in
        OP (pos, ty', op, args')
   | FITS (pos, ty, e1, argty) ->
        let ty' = widen'typename ty in
        let e1' = widen'expr e1 in
        let argty' = widen'typename argty in
        FITS (pos, ty', e1', argty')
   | MODE (pos, name) ->
        MODE (pos, name)
   | LIST (pos, ty, args) ->
        let ty' = widen'typename ty in
        let args' = List.map widen'expr args in
        LIST (pos, ty', args')
   | MODIFIER (pos, ty, name, args) ->
        let ty' = widen'typename ty in
        let args' = List.map widen'expr args in
        MODIFIER (pos, ty', name, args')
   | PACK (pos, ty, name, args) ->
        let ty' = widen'typename ty in
        let args' = List.map widen'expr args in
        PACK (pos, ty', name, args')
   | CAST (pos, nty, oty, e1) ->
        let nty' = widen'typename nty in
        let oty' = widen'typename oty in
        let e1' = widen'expr e1 in
        CAST (pos, nty', oty', e1')
   | EVAL (pos, nty, relf, relo, oty, e1) ->
        let nty' = widen'typename nty in
        let oty' = widen'typename oty in
        let e1' = widen'expr e1 in
        EVAL (pos, nty', relf, relo, oty', e1')
   | UNEVAL (pos, ty, e1) ->
        let ty' = widen'typename ty in
        let e1' = widen'expr e1 in
        UNEVAL (pos, ty', e1')
   | ANNOTATE (pos, ty, e1) ->
        let ty' = widen'typename ty in
        let e1' = widen'expr e1 in
        ANNOTATE (pos, ty', e1')
   | COMMENTED (txt, e1) ->
        let e1' = widen'expr e1 in
        COMMENTED (txt, e1')


(*
 * Note that since we aren't ourselves touching encodings and don't
 * see the raw fields, we can widen these arbitrarily. We don't even
 * have to worry about agreeing with genencodings: as long as the
 * argument type we put in targethaz.h is wide enough to hold the
 * values, the magic of integer type promotions in C means it'll work.
 *)
let widen'field (f: field) =
   let ty = widen'typename f.ty in
   { f with ty; }

let widen'predicatedecl { definedat; args; afields; cfields; es; } =
   let widen'arg (pos, ty) = (pos, widen'typename ty) in
   let args = Types.StringMap.map widen'arg args in

   let afields = Types.StringMap.map widen'typename afields in
   let cfields = Types.StringMap.map widen'typename cfields in

   let es = List.map widen'expr es in
   { definedat; args; afields; cfields; es; }

let widen'assignment (pos, name, ty, e) =
   let ty' = widen'typename ty in
   let e' = widen'expr e in
   (pos, name, ty', e')

let widen'matcher m =
   let guard = widen'expr m.guard in
   let assignments = List.map widen'assignment m.assignments in
   { m with guard; assignments; }

let widen'hazard (h: hazard) =
   let m = widen'matcher h.m in
   { h with m; }

let widen'transfer (t: transfer) =
   let m = widen'matcher t.m in
   { t with m; }

(* top level *)
let widen (spec: spec) =

   (* after numerate, enumtypes/subenums are irrelevant *)
   assert (Types.StringMap.cardinal spec.enumtypes = 0);
   assert (Types.StringMap.cardinal spec.subenums = 0);
   let fields = Types.StringMap.map widen'field spec.fields in

   let predicates = Types.StringMap.map widen'predicatedecl spec.predicates in
   let hazards = List.map widen'hazard spec.hazards in
   let transfers = List.map widen'transfer spec.transfers in

   { spec with fields; predicates; hazards; transfers; }
