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

open Typerep
open Exprrep

(*
 * generic visit/treewalk
 *)

let rec visit f e =
   begin
   match e with
        CONST (_, _, _) -> ()
      | STRCONST (_, _, _) -> ()
      | USEVAR (_, _, _) -> ()
      | USEFIELD (_, _, e1, _) -> visit f e1
      | OP (_, _, _, es) -> List.iter (visit f) es
      | FITS (_, _, e1, _) -> visit f e1
      | MODE (_, _) -> ()
      | LIST (_, _, es) -> List.iter (visit f) es
      | MODIFIER (_, _, _, es) -> List.iter (visit f) es
      | PACK (_, _, _, es) -> List.iter (visit f) es
      | CAST (_, _, _, e1) -> visit f e1
      | EVAL (_, _, _, _, _, e1) -> visit f e1
      | UNEVAL (_, _, e1) -> visit f e1
      | ANNOTATE (_, _, e1) -> visit f e1
      | COMMENTED (_, e1) -> visit f e1
   end;
   f e

(*
 * generic transform
 *)

let rec xform f e =
   let e' = match e with
        CONST (_, _, _) -> e
      | STRCONST (_, _, _) -> e
      | USEVAR (_, _, _) -> e
      | USEFIELD (pos, ty, e1, name) ->
           let e1' = xform f e1 in
           USEFIELD (pos, ty, e1', name)
      | OP (pos, ty, op, es) ->
           let es' = List.map (xform f) es in
           OP (pos, ty, op, es')
      | FITS (pos, ty, e1, argty) ->
           let e1' = xform f e1 in
           FITS (pos, ty, e1', argty)
      | MODE (_, _) -> e
      | LIST (pos, ty, es) ->
           let es' = List.map (xform f) es in
           LIST (pos, ty, es')
      | MODIFIER (pos, ty, name, es) ->
           let es' = List.map (xform f) es in
           MODIFIER (pos, ty, name, es')
      | PACK (pos, ty, name, es) ->
           let es' = List.map (xform f) es in
           PACK (pos, ty, name, es')
      | CAST (pos, nty, oty, e1) ->
           let e1' = xform f e1 in
           CAST (pos, nty, oty, e1')
      | EVAL (pos, ty, field, reloffset, ty2, e1) ->
           let e1' = xform f e1 in
           EVAL (pos, ty, field, reloffset, ty2, e1')
      | UNEVAL (pos, ty, e1) ->
           let e1' = xform f e1 in
           UNEVAL (pos, ty, e1')
      | ANNOTATE (pos, ty, e1) ->
           let e1' = xform f e1 in
           ANNOTATE (pos, ty, e1')
      | COMMENTED (txt, e1) ->
           let e1' = xform f e1 in
           COMMENTED (txt, e1')
   in f e'

(*
 * alpha equivalence
 *)

let alphachange f e =
   let f' e = match e with
        USEVAR (pos, ty, name) -> USEVAR (pos, ty, f name)
      | _ -> e
   in
   xform f' e

let alphachange_opt f oe =
   match oe with
        None -> None
      | Some e -> Some (alphachange f e)

(*
 * very simple optimizer
 *)

(*
 * XXX we need to be more consistent about the way we represent boolconstants
 *)
let bconst e =
   match e with
        CONST (_pos, PLAINTYPE "bool", SMALL 1) -> Some true
      | CONST (_pos, PLAINTYPE "bool", SMALL 0) -> Some false
      | CONST (_pos, PLAINTYPE "bool", LARGE k) ->
           if k = Types.Wide.one then Some true
           else if k = Types.Wide.zero then Some false
           else None
      | USEVAR (_pos, PLAINTYPE "bool", "true") -> Some true
      | USEVAR (_pos, PLAINTYPE "bool", "false") -> Some false
      | _ -> None

let baseoptfunc e =
   match e with
        OP (_pos, PLAINTYPE "bool", op, [e1; e2]) -> begin
           match op, bconst e1, bconst e2 with
		(* x && true => x *)
                LOGAND, _, Some true -> e1
		(* true && x => x *)
              | LOGAND, Some true, _ -> e2
		(* x && false => false (assuming x has no other effects) *)
              | LOGAND, _, Some false -> e2
		(* false && x => false *)
              | LOGAND, Some false, _ -> e1
		(* x || false => x *)
              | LOGOR, _, Some false -> e1
		(* false || x => x *)
              | LOGOR, Some false, _ -> e2
		(* x || true => true (assuming x has no other effects) *)
              | LOGOR, _, Some true -> e2
		(* true || x => true *)
              | LOGOR, Some true, _ -> e1
              | _ -> e
        end
      | _ -> e

let baseopt e = xform baseoptfunc e
