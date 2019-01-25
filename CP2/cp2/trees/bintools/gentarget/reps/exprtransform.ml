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

open Typerep
open Exprrep


(**************************************************************)
(* misc support code *)

(* This chains better than plain compare. *)
let compare'' f a b =
   match f a b with
        0 -> None
      | x -> Some x

(* Can't have just one of these, because ML types suck. *)
let compare'1 = compare'' Pervasives.compare
let compare'2 = compare'' Pervasives.compare
let compare'3 = compare'' Pervasives.compare
let compare'4 = compare'' Pervasives.compare
let compare'5 = compare'' Pervasives.compare

let compare'lists f a b =
   let rec digest xs = match xs with
        (Some x) :: _ -> Some x
      | None :: more -> digest more
      | [] -> None
   in
   digest (List.map2 f a b)

(**************************************************************)
(* numerate: remove enum types and values *)

(* begin mandatory cutpaste *)
type enumdata = {
   name: string;
   width: int;
   symtovalue: int Types.StringMap.t;
}
(* end mandatory cutpaste *)

type numeratectx = {
   enuminfo: enumdata Types.StringMap.t;
   subenumbindings: (Pos.pos * expr) Types.StringMap.t ref;
   needed: string list ref;
   canbind: bool;
}

let numeratectx_new enums = {
   enuminfo = enums;
   subenumbindings = ref Types.StringMap.empty;
   needed = ref [];
   canbind = false;
}

let numeratectx_push ctx = {
   ctx with canbind = true;
} 

let numeratectx_addbinding ctx name e =
   ctx.subenumbindings := Types.StringMap.add name e !(ctx.subenumbindings)

let numeratectx_needsubenum ctx sym =
   ctx.needed := sym :: !(ctx.needed)

let numeratectx_getneeded ctx =
   let ret = !(ctx.needed) in
   ctx.needed := [];
   ret

let numeratectx_checkclean ctx =
   assert(!(ctx.needed) = [])

(*
 * typename
 *)
let rec numerate'typename ctx ty = match ty with
     PLAINTYPE name -> begin
        try
           let e = Types.StringMap.find name ctx.enuminfo in
           WIDTHTYPE ("uint", e.width)
        with Not_found ->
           (* not an enum *)
           ty
     end
   | EXPRTYPE t1 -> EXPRTYPE (numerate'typename ctx t1)
   | LISTTYPE t1 -> LISTTYPE (numerate'typename ctx t1)
   | TMPTYPE _ -> Util.crash "transform: leftover temporary type"
   | _ -> ty

(*
 * expr
 *)
let rec numerate'expr ctx e = match e with
     CONST (pos, ty, k) -> CONST (pos, numerate'typename ctx ty, k)
   | STRCONST (pos, ty, s) -> STRCONST (pos, numerate'typename ctx ty, s)
   | USEVAR (pos, ty, sym) -> begin
        let ty' = numerate'typename ctx ty in
        match ty (* ty, not ty' *) with
             PLAINTYPE enumname -> begin
                try begin
                   let e = Types.StringMap.find enumname ctx.enuminfo
                   in
                   try
                      (* it is an enumerator of this enum *)
                      let v = Types.StringMap.find sym e.symtovalue in
                      COMMENTED (sym, CONST (pos, ty', SMALL v))
                   with Not_found ->
                      (* it is just a variable of this type *)
                      USEVAR (pos, ty', sym)
                end
                with Not_found ->
                   (* not an enum *)
                   USEVAR (pos, ty', sym)
             end
           | LISTTYPE _ -> begin
                try
                   (* if it's a subenum value... *)
                   let ee = Types.StringMap.find sym !(ctx.subenumbindings) in
                   if ctx.canbind then begin
                      numeratectx_needsubenum ctx sym;
                      USEVAR (pos, ty', sym)
                   end else begin
                      let (_pos, ee) = ee in
                      COMMENTED (sym, ee)
                   end
                with Not_found ->
                   USEVAR (pos, ty', sym)
             end
           | _ ->
                USEVAR (pos, ty', sym)
     end
   | USEFIELD (pos, ty, e1, name) ->
        let ty = numerate'typename ctx ty in
        let e1 = numerate'expr ctx e1 in
        USEFIELD (pos, ty, e1, name)
   | OP (pos, ty, op, args) ->
        let ty = numerate'typename ctx ty in
        let args = List.map (numerate'expr ctx) args in
        OP (pos, ty, op, args)
   | FITS (pos, ty, e1, argty) ->
        let ty = numerate'typename ctx ty in
        let e1 = numerate'expr ctx e1 in
        let argty = numerate'typename ctx argty in
        FITS (pos, ty, e1, argty)
   | MODE (pos, modename) ->
        MODE (pos, modename)
   | LIST (pos, ty, elems) ->
        let ty = numerate'typename ctx ty in
        let elems = List.map (numerate'expr ctx) elems in
        LIST (pos, ty, elems)
   | MODIFIER (pos, ty, modname, args) ->
        let ty = numerate'typename ctx ty in
        let args = List.map (numerate'expr ctx) args in
        MODIFIER (pos, ty, modname, args)
   | PACK (pos, ty, ctor, args) ->
        (* ty should be PLAINTYPE (ctor) and thus shouldn't change *)
        let ty' = numerate'typename ctx ty in
        if ty' <> ty then
           Util.crash "transform: numerating PACK: type changed"
        ;
        let args = List.map (numerate'expr ctx) args in
        PACK (pos, ty, ctor, args)
   | CAST (pos, nty, oty, e1) ->
        let oty = numerate'typename ctx oty in
        let nty = numerate'typename ctx nty in
        let e1 = numerate'expr ctx e1 in
	CAST (pos, nty, oty, e1)
   | EVAL (pos, nty, relname, reloffset, oty, e1) ->
        let oty = numerate'typename ctx oty in
        let nty = numerate'typename ctx nty in
        let e1 = numerate'expr ctx e1 in
	EVAL (pos, nty, relname, reloffset, oty, e1)
   | UNEVAL (pos, ty, e1) ->
        let ty = numerate'typename ctx ty in
        let e1 = numerate'expr ctx e1 in
	UNEVAL (pos, ty, e1)
   | ANNOTATE (pos, ty, e1) ->
        let ty = numerate'typename ctx ty in
        let e1 = numerate'expr ctx e1 in
	ANNOTATE (pos, ty, e1)
   | COMMENTED (text, e1) ->
        let e1 = numerate'expr ctx e1 in
        COMMENTED (text, e1)

(*
 * subenum
 *
 * Builds an assignment for a scratch variable that replaces the
 * subenum value, and stores it in ctx.subenumbindings.
 *)
let numerate'subenum ctx name definedat enumname values =
   let e =
      try
         Types.StringMap.find enumname ctx.enuminfo
      with Not_found -> Util.crash ("numerate: missing enum " ^ enumname ^
				    " in subenum " ^ name)
   in
   let ty = numerate'typename ctx (PLAINTYPE enumname) in
   let uselarge = match ty with
        WIDTHTYPE ("uint", n) -> n > 20
      | _ -> false
   in
   let getval sym =
      try
         Types.StringMap.find sym e.symtovalue
      with Not_found -> Util.crash ("numerate: missing enumerator " ^ sym ^
				    "in subenum " ^ name ^ " of enum " ^
				    enumname)
   in
   let getvalexpr v =
         if uselarge then
            CONST (definedat, ty, LARGE (Types.Wide.of_int v))
         else
            CONST (definedat, ty, SMALL v)
   in
   let values = List.map getval (Types.StringSet.elements values) in 
   let valexprs = List.map getvalexpr (List.sort Pervasives.compare values) in
   let expr = LIST (definedat, LISTTYPE ty, valexprs) in
   numeratectx_addbinding ctx name (definedat, expr)

(*
 * extract
 *
 * gets the bindings currently needed
 * 
 * returns a list of assignment tuples in the form (pos, sym, e)
 * (caller must turn those into its own assignment statements)
 *)
let numerate_extract ctx =
   let enumsyms = numeratectx_getneeded ctx in
   let mkassignment sym =
      let (pos, expr) = Types.StringMap.find sym !(ctx.subenumbindings) in
      (pos, sym, expr)
   in
   List.map mkassignment enumsyms 


(**************************************************************)
(* delist: kill off list expressions *)

type delistctx = {
   (*spec: spec;*)
   listvars: expr Types.StringMap.t ref;
}

let delistctx_new () = { listvars = ref Types.StringMap.empty; }

let delistctx_addlistvar ctx name e =
   ctx.listvars := Types.StringMap.add name e !(ctx.listvars)

let nolist pos ty what =
   match ty with
        LISTTYPE _ ->
           Pos.crashat pos ("Illegal list type in " ^ what)
      | _ -> ()

let leftover pos ty what =
   match ty with
        LISTTYPE _ ->
           Pos.crashat pos ("Leftover list value in " ^ what)
      | _ -> ()

(*
 * expressions
 *)

(*
 * handle "E0 in ES"
 *)
let delist'in'list _ctx pos _ty e0 es =
   (*
    * Because this is a set op, we can uniq es.
    * Ignore positions (otherwise we could just use Pervasives.compare)
    * and types (because the list typechecked and must have uniform type)
    *
    * XXX probably the sorter should get moved to Rep
    *)
   let rec sorter' e1 e2 =
      let sorter'lists es1 es2 =
         match compare'1 (List.length es1) (List.length es2) with
              Some x -> Some x
            | None -> compare'lists sorter' es1 es2
      in
      match e1, e2 with
           CONST (_pos1, _ty1, SMALL k1), CONST (_pos2, _ty2, SMALL k2) ->
              compare'1 k1 k2
         | CONST (_pos1, _ty1, LARGE k1), CONST (_pos2, _ty2, LARGE k2) ->
              compare'' Types.Wide.compare k1 k2
         | CONST (_pos1, _ty1, SMALL k1), CONST (_pos2, _ty2, LARGE k2) ->
              compare'' Types.Wide.compare (Types.Wide.of_int k1) k2
         | CONST (_pos1, _ty1, LARGE k1), CONST (_pos2, _ty2, SMALL k2) ->
              compare'' Types.Wide.compare k1 (Types.Wide.of_int k2)
         | USEVAR (_pos1, _ty1, name1), USEVAR (_pos2, _ty2, name2) ->
              compare'2 name1 name2
         | OP (_pos1, _ty1, op1, args1), OP (_pos2, _ty2, op2, args2) -> begin
              match compare'3 op1 op2 with
                   Some x -> Some x
                 | None -> sorter'lists args1 args2
           end
         | LIST (_pos1, _ty1, elems1), LIST (_pos2, _ty2, elems2) ->
              sorter'lists elems1 elems2
         | MODIFIER (_, _, name1, args1), MODIFIER (_, _, name2, args2) ->begin
              match compare'2 name1 name2 with
                   Some x -> Some x
                 | None -> sorter'lists args1 args2
           end
         | PACK (_, _, name1, args1), PACK (_, _, name2, args2) -> begin
              match compare'2 name1 name2 with
                   Some x -> Some x
                 | None -> sorter'lists args1 args2
           end
         | CAST (_, _, oty1, e1), CAST (_, _, oty2, e2) -> begin
              (* plain compare is ok for typename *)
              match compare'4 oty1 oty2 with
                   Some x -> Some x
                 | None -> sorter' e1 e2
           end
         | COMMENTED (_, e1), COMMENTED (_, e2) ->
              (* ignore the text *)
              sorter' e1 e2
         | _, _ ->
              (* Pervasives.compare is ok if they aren't matching cases *)
              compare'5 e1 e2
   in
   let sorter e1 e2 = match sorter' e1 e2 with
        Some x -> x
      | None -> 0
   in
   let es = List.sort_uniq sorter es in

   (* Collect the integer constants from ES *)
   let pred e = match e with
        CONST _ -> true
      | _ -> false
   in
   let (es'int, es'other) = List.partition pred es in

   (* strip off the expression tag from the integer constants *)
   let e2k e = match e with
        CONST (pos, ty, k) -> (pos, ty, k)
      | _ -> Util.crash "transform: dolist'in: e2k: flatly impossible"
   in
   let ks = List.map e2k es'int in

   (* convert to a list of ranges *)
   let rec next_after k1 k2 = match k1, k2 with
        SMALL k1', SMALL k2' -> k1'+1 = k2'
      | LARGE k1', LARGE k2' -> Types.Wide.eq (Types.Wide.inc k1') k2'
      | _, SMALL k2' -> next_after k1 (LARGE (Types.Wide.of_int k2'))
      | SMALL k1', _ -> next_after (LARGE (Types.Wide.of_int k1')) k2
   in
   let folder ranges (pos, ty, k) =
      match ranges with
           [] -> (pos, ty, k, k) :: []
         | (pos', ty', k0, k1) :: more ->
              assert(ty = ty');
              if next_after k1 k then
                 (pos', ty', k0, k) :: more
              else
                 (pos, ty, k, k) :: (pos', ty', k0, k1) :: more
   in
   let kranges = List.fold_left folder [] ks in

   (* Convert each case of the list to a test expression *)
   let mkexpr'k (pos, ty, k1, k2) =
      if k1 = k2 then
         OP (pos, booltype, EQ, [e0; CONST (pos, ty, k1)])
      else
         let e1' = OP (pos, booltype, LT, [e0; CONST (pos, ty, k1)]) in
         let e2' = OP (pos, booltype, LT, [CONST (pos, ty, k2); e0]) in
         let e3' = OP (pos, booltype, LOGOR, [e1'; e2']) in
         OP (pos, booltype, LOGNOT, [e3'])
   in
   let mkexpr'e e =
      let pos = exprpos e in
      OP (pos, booltype, EQ, [e0; e])
   in

   (* The ultimate expression is a big LOGOR over everything *)
   let kexprs = List.map mkexpr'k kranges in
   let eexprs = List.map mkexpr'e es'other in
   match kexprs @ eexprs with
        [] -> USEVAR (pos, booltype, "false")
      | [e] -> e
      | e :: more ->
           let mkor e1 e2 = OP (pos, booltype, LOGOR, [e1; e2]) in
           List.fold_left mkor e more

let rec delist'in ctx pos ty x xs =
   match xs with
      CONST _ -> Pos.crashat pos "'in' operator on integer constant"
    | STRCONST _ -> Pos.crashat pos "'in' operator on string constant"
    | USEVAR (pos, ty, name) ->
         (* xs has list type so look in ctx.listvars *)
         let e = Types.StringMap.find name !(ctx.listvars) in
         delist'in ctx pos ty x e
    | USEFIELD (pos, _ty, _e1, _name) ->
         Pos.crashat pos ("Invalid list operator .")
    | OP (pos, _ty, BITNOT, _) ->
         Pos.crashat pos "Illegal set-complement operator"
    | OP (pos, ty, BITAND, [x1; x2]) ->
         let x1' = delist'in ctx pos ty x x1 in
         let x2' = delist'in ctx pos ty x x2 in
         OP (pos, booltype, LOGAND, [x1'; x2'])
    | OP (pos, ty, BITOR, [x1; x2]) ->
         let x1' = delist'in ctx pos ty x x1 in
         let x2' = delist'in ctx pos ty x x2 in
         OP (pos, booltype, LOGOR, [x1'; x2'])
    | OP (pos, ty, SUB, [x1; x2]) ->
         let x1' = delist'in ctx pos ty x x1 in
         let x2' = delist'in ctx pos ty x x2 in
         let x2'' = OP (pos, booltype, LOGNOT, [x2']) in
         OP (pos, booltype, LOGOR, [x1'; x2''])
    | OP (pos, _ty, op, _) ->
         Pos.crashat pos ("Invalid list operator " ^ dump'op op)
    | FITS (pos, _ty, _e1, _) ->
         Pos.crashat pos ("Invalid list operator fits")
    | MODE (pos, _modename) ->
         Pos.crashat pos ("Invalid list operator mode")
    | LIST (pos, _ty, elems) ->
         delist'in'list ctx pos ty x elems
    | MODIFIER (pos, _ty, modname, _args) ->
         Pos.crashat pos ("Invalid modifier " ^ modname ^ " producing list")
    | PACK (pos, _ty, ctor, _args) ->
         Pos.crashat pos ("Invalid compound " ^ ctor ^ " producing list")
    | CAST (pos, _nty, oty, e1) ->
         delist'in ctx pos oty x e1
    | EVAL (pos, _nty, _relname, _reloffset, oty, e1) ->
         delist'in ctx pos oty x e1
    | UNEVAL (pos, ty, e1) ->
         delist'in ctx pos ty x e1
    | ANNOTATE (pos, ty, e1) ->
         delist'in ctx pos ty x e1
    | COMMENTED (text, e1) ->
         let e1' = delist'in ctx pos ty x e1 in
         COMMENTED (text, e1')

let rec delist'expr ctx e = match e with
     CONST (pos, ty, k) ->
        nolist pos ty "integer constant";
        CONST (pos, ty, k)
   | STRCONST (pos, ty, s) ->
        nolist pos ty "string constant";
        STRCONST (pos, ty, s)
   | USEVAR (pos, ty, name) ->
        leftover pos ty ("variable/identifier " ^ name);
        USEVAR (pos, ty, name)
   | USEFIELD (pos, ty, e1, name) ->
        let e1 = delist'expr ctx e1 in
        USEFIELD (pos, ty, e1, name)
   | OP (pos, ty, IN, [x; xs]) ->
        delist'in ctx pos ty x xs
   | OP (pos, _ty, IN, _) ->
        Pos.crashat pos "'in' operator on wrong number of args"
   | OP (pos, ty, op, args) ->
        let args = List.map (delist'expr ctx) args in
        OP (pos, ty, op, args)
   | FITS (pos, ty, e1, argty) ->
        nolist pos argty "fits expression";
        let e1 = delist'expr ctx e1 in
        FITS (pos, ty, e1, argty)
   | MODE (pos, modename) ->
        MODE (pos, modename)
   | LIST (pos, ty, elems) ->
        let elems = List.map (delist'expr ctx) elems in
        (* Should always fail... *)
        leftover pos ty ("list literal");
        LIST (pos, ty, elems);
   | MODIFIER (pos, ty, modname, args) ->
        let args = List.map (delist'expr ctx) args in
        MODIFIER (pos, ty, modname, args)
   | PACK (pos, ty, ctor, args) ->
        let args = List.map (delist'expr ctx) args in
        PACK (pos, ty, ctor, args)
   | CAST (pos, nty, oty, e1) ->
        nolist pos oty "cast input";
        nolist pos nty "cast output";
        let e1 = delist'expr ctx e1 in
        CAST (pos, nty, oty, e1)
   | EVAL (pos, nty, relname, reloffset, oty, e1) ->
        nolist pos oty "eval input";
        nolist pos nty "eval output";
        let e1 = delist'expr ctx e1 in
        EVAL (pos, nty, relname, reloffset, oty, e1)
   | UNEVAL (pos, ty, e1) ->
        nolist pos ty "uneval result type";
        let e1 = delist'expr ctx e1 in
        UNEVAL (pos, ty, e1)
   | ANNOTATE (pos, ty, e1) ->
        nolist pos ty "type annotation";
        let e1 = delist'expr ctx e1 in
        ANNOTATE (pos, ty, e1)
   | COMMENTED (text, e1) ->
        let e1 = delist'expr ctx e1 in
        COMMENTED (text, e1)
