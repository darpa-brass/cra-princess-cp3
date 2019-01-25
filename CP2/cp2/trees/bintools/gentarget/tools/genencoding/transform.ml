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

open Rep
module ET = Exprtransform

(**************************************************************)
(* misc support code *)

(*
let rec exprpos e = match e with
     CONST (pos, _, _) -> pos
   | USEVAR (pos, _, _) -> pos
   | OP (pos, _, _, _) -> pos
   | FITS (pos, _, _, _) -> pos
   | MODE (pos, _) -> pos
   | LIST (pos, _, _) -> pos
   | MODIFIER (pos, _, _, _) -> pos
   | PACK (pos, _, _, _) -> pos
   | CAST (pos, _, _, _) -> pos
   | EVAL (pos, _, _, _, _, _) -> pos
   | UNEVAL (pos, _, _) -> pos
   | ANNOTATE (pos, _, _) -> pos
   | COMMENTED (_, e1) -> exprpos e1
*)

(**************************************************************)
(* numerate: remove enum types and values *)

(*
 * The bulk of the pass is in Exprtransform
 *)
let numeratectx_new = ET.numeratectx_new
let numeratectx_push = ET.numeratectx_push
let numeratectx_checkclean = ET.numeratectx_checkclean
let numerate'typename = ET.numerate'typename
let numerate'expr = ET.numerate'expr

(*
 * compoundtype
 *)
let numerate'compoundtype ctx { name; definedat; members; } =
   let num'arg (pos, ty) =
      (pos, numerate'typename ctx ty)
   in
   let members = List.map num'arg members in
   { name; definedat; members; }

(*
 * operandtag
 *)
let numerate'operandtag ctx { name; definedat; basetype; } =
   let basetype = numerate'typename ctx basetype in
   { name; definedat; basetype; }

(*
 * modifier
 *)
let numerate'modifier _ctx m = m

(*
 * field
 *)
let numerate'field ctx { name; definedat; relocatable; offset; ty; } =
   let ty = numerate'typename ctx ty in
   { name; definedat; relocatable; offset; ty; }

(*
 * form
 *)
let numerate'form ctx { name; definedat; fields; types; } =
   let types = List.map (numerate'typename ctx) types in
   { name; definedat; fields; types; }

(*
 * subenum
 *)
let numerate'subenum ctx _ { name; definedat; enumname; values; } =
   ET.numerate'subenum ctx name definedat enumname values

(* patterns don't have types in them and thus don't change *)

(*
 * statement
 *)
let numerate'assignment ctx (pos, pat, e) =
   let e = numerate'expr ctx e in
   (pos, pat, e)

let rec numerate'statement ctx stmt = match stmt with
     ASSIGN a -> ASSIGN (numerate'assignment ctx a)
   | IF (pos, cond, ts, fs) ->
        let cond = numerate'expr ctx cond in
        let ts = List.map (numerate'statement ctx) ts in
        let fs = List.map (numerate'statement ctx) fs in
        IF (pos, cond, ts, fs)
   | USE (pos, name, args, ops, resolvedname) ->
        let args = List.map (numerate'expr ctx) args in
        let ops = List.map (numerate'expr ctx) ops in
        USE (pos, name, args, ops, resolvedname)
   | EMIT (pos, _e) ->
        (* these only appear downstream *)
        Pos.crashat pos "transform: numerate: invalid EMIT"
   | HOOK (pos, _name, _args) ->
        (* these only appear downstream *)
        Pos.crashat pos "transform: numerate: invalid HOOK"
   | WARN (pos, text) ->
        WARN (pos, text)

(*
 * encodings and macros
 *)
let numerate'arg ctx (pos, name, ty) =
   (pos, name, numerate'typename ctx ty)

let numerate'encoding ctx { name; mangledname; definedat; specargs; opargs;
                            formname; alternatives; } =
   let specargs = List.map (numerate'arg ctx) specargs in
   let opargs = List.map (numerate'arg ctx) opargs in
   let numerate'alt (pos, e, block) =
      let e = numerate'expr ctx e in
      let ctx' = numeratectx_push ctx in
      let block = List.map (numerate'statement ctx) block in
      let encode (pos, sym, expr) =
         ASSIGN (pos, SETVAR (pos, sym), expr)
      in
      let enumassignments = List.map encode (ET.numerate_extract ctx') in
      numeratectx_checkclean ctx';
      (pos, e, enumassignments @ block)
   in
   let alternatives = List.map numerate'alt alternatives in

   { name; mangledname; definedat; specargs; opargs; formname; alternatives; }

let numerate'macro ctx { name; mangledname; definedat; specargs; opargs;
			 expansions; } =
   let specargs = List.map (numerate'arg ctx) specargs in
   let opargs = List.map (numerate'arg ctx) opargs in
   let numerate'exp (pos, e, block) =
      let e = numerate'expr ctx e in
      let ctx' = numeratectx_push ctx in
      let block = List.map (numerate'statement ctx') block in
      let encode (pos, sym, expr) =
         ASSIGN (pos, SETVAR (pos, sym), expr)
      in
      let enumassignments = List.map encode (ET.numerate_extract ctx') in
      numeratectx_checkclean ctx';
      (pos, e, enumassignments @ block)
   in
   let expansions = List.map numerate'exp expansions in

   { name; mangledname; definedat; specargs; opargs; expansions; }

(*
 * instruction
 *)
let numerate'instruction ctx insn =
   let operands_int = List.map (numerate'typename ctx) insn.operands_int in
   { insn with operands_int; }

(*
 * toplevel
 *)
let numerate {
	pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
 } =
   let smap = Types.StringMap.map in
   let siter = Types.StringMap.iter in
   let lmap = List.map in

   let loadenum { name; width; symtovalue; } =
      { ET.name; ET.width; ET.symtovalue; }
   in
   let ctx = numeratectx_new (Types.StringMap.map loadenum enums) in

   let compoundtypes = smap (numerate'compoundtype ctx) compoundtypes in
   let operandtags =  smap (numerate'operandtag ctx)  operandtags in
   let modifiers =    smap (numerate'modifier ctx)    modifiers in
   let fields =       smap (numerate'field ctx)       fields in
   let forms =        smap (numerate'form ctx)        forms in
                      siter (numerate'subenum ctx)    subenums;
   let encodings =    lmap (numerate'encoding ctx)    encodings in
   let macros =       lmap (numerate'macro ctx)       macros in
   let instructions = lmap (numerate'instruction ctx) instructions in

   numeratectx_checkclean ctx;

   let enums = Types.StringMap.empty in
   let subenums = Types.StringMap.empty in
   {
	pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
   }

(**************************************************************)
(* delist: kill off list expressions *)

let delist'expr = ET.delist'expr
let nolist = ET.nolist

(*
 * statements
 *)
let delist'assignment ctx (pos, pat, e) =
   (pos, pat, delist'expr ctx e)

let rec delist'statement ctx stmt = match stmt with
     (* XXX this should probably pick up any expression of list type *)
     ASSIGN (_pos1, SETVAR (_pos2, name), LIST (pos, ty, elems)) ->
        let e = LIST (pos, ty, elems) in
        ET.delistctx_addlistvar ctx name e;
        []
   | ASSIGN a ->
        [ASSIGN (delist'assignment ctx a)]
   | IF (pos, cond, ts, fs) ->
        let cond = delist'expr ctx cond in
        let ts = delist'statements ctx ts in
        let fs = delist'statements ctx fs in
        [IF (pos, cond, ts, fs)]
   | USE (pos, name, args, ops, resolvedname) ->
        let args = List.map (delist'expr ctx) args in
        let ops = List.map (delist'expr ctx) ops in
        [USE (pos, name, args, ops, resolvedname)]
   | EMIT (pos, _e) ->
        (* these only appear downstream *)
        Pos.crashat pos "transform: delist: invalid EMIT"
   | HOOK (pos, _name, _args) ->
        (* these only appear downstream *)
        Pos.crashat pos "transform: delist: invalid HOOK"
   | WARN (pos, text) ->
        [WARN (pos, text)]
and delist'statements ctx stmts =
   List.concat (List.map (delist'statement ctx) stmts)

(*
 * encodings/macros
 *)
let delist'arg _ctx (pos, name, ty) =
   nolist pos ty ("argument/operand " ^ name)

let delist'encoding ctx { name; mangledname; definedat; specargs; opargs;
                          formname; alternatives; } =
   List.iter (delist'arg ctx) specargs;
   List.iter (delist'arg ctx) opargs;
   let delist'alt (pos, e, block) =
      let e = delist'expr ctx e in
      let block = delist'statements ctx block in
      (pos, e, block)
   in
   let alternatives = List.map delist'alt alternatives in
   { name; mangledname; definedat; specargs; opargs; formname; alternatives; }

let delist'macro ctx { name; mangledname; definedat; specargs; opargs;
		       expansions; } =
   List.iter (delist'arg ctx) specargs;
   List.iter (delist'arg ctx) opargs;
   let delist'exp (pos, e, block) =
      let e = delist'expr ctx e in
      let block = delist'statements ctx block in
      (pos, e, block)
   in
   let expansions = List.map delist'exp expansions in
   { name; mangledname; definedat; specargs; opargs; expansions; }

(*
 * instructions
 *)
let delist'instruction _ctx (insn : instruction) =
  let name = insn.name in
  let definedat = insn.definedat in
  let operands_int = insn.operands_int in

  let delist'op (n, ty) =
     nolist definedat ty ("operand " ^ string_of_int n ^ " of " ^ name)
  in
  List.iter delist'op (Util.number operands_int);

  insn

(*
 * toplevel
 *)
let delist spec =
   let ctx = ET.delistctx_new () in

   let encodings =    List.map (delist'encoding ctx)    spec.encodings in
   let macros =       List.map (delist'macro ctx)       spec.macros in
   let instructions = List.map (delist'instruction ctx) spec.instructions in

   { spec with encodings; macros; instructions; }

(**************************************************************)
(* registrate: emit reginfo hooks *)

(*
 * This whole pass is a hack. If "reginfo" is turned on in the misc
 * settings file, it's called (otherwise it's skipped) and emits a
 * HOOK for each register used in each instruction that uses
 * registers. These are found based on the presence of register fields
 * in the form, which is an imprecise overapproximation. (In general
 * some instructions that use any given form will not use one or more
 * of the registers and set the field to zero or some other magic
 * value instead.) The right way to do this is check which of the
 * register fields are specified as args (either encoding arguments or
 * operands; the latter come from the user but the former in general
 * come from macro expansions rather than hardwiring) but for the time
 * being I can't be bothered as the whole concept is stupid and this
 * method is a hack anyhow.
 *
 * Also for now we hardwire in the names of the register fields that
 * exist in the mips machine description, because this thing is
 * actually a mips-only notion, and at the time I'm writing this we
 * don't yet have register-typed fields and for various reasons I
 * don't want to go implement those first. (XXX: this is now in
 * place and can be done properly)
 *
 * The C functions the HOOKs call are provided by a similarly hacky
 * chunk of code that's baked into mkencoding.ml.
 *)

type registratectx = {
   (* form name -> hook list *)
   formhooks: statement list Types.StringMap.t ref;
}

let new_registratectx _spec = { formhooks = ref Types.StringMap.empty; }

let registrate'form ctx _ { name; definedat; fields; types; } =
   let addhook name ty fn =
      [HOOK (definedat, name, [USEVAR (definedat, ty, fn)])]
   in
   let dofield (fn, ty) = match fn with
        (* XXX hardwired mips names *)
        "rs" | "rt" | "rd" -> addhook "reginfo_use_gp_reg" ty fn
      | "fs" | "ft" | "fd" -> addhook "reginfo_use_fp_reg" ty fn
      | "rt_cop0" | "rd_cop0" -> addhook "reginfo_use_cop0_reg" ty fn
      | "rt_cop2" | "rd_cop2" -> addhook "reginfo_use_cop2_reg" ty fn
      | "rt_cop3" | "rd_cop3" -> addhook "reginfo_use_cop3_reg" ty fn
      | _ -> []
   in
   let hooks = List.concat (List.map dofield (Util.zip fields types)) in
   ctx.formhooks := Types.StringMap.add name hooks !(ctx.formhooks)

let registrate'alternative hooks (pos, e, block) =
   (pos, e, block @ hooks)

let registrate'encoding ctx enc =
   let hooks = match enc.formname with
        "_" -> []  (* should not happen, but be safe... *)
      | _ ->
           try Types.StringMap.find enc.formname !(ctx.formhooks)
           with Not_found -> [] (* shouldn't happen either, but... *)
   in
   let alternatives =
      List.map (registrate'alternative hooks) enc.alternatives
   in
   { enc with alternatives; }

let registrate spec =
   let ctx = new_registratectx spec in
   Types.StringMap.iter (registrate'form ctx) spec.forms;
   let encodings = List.map (registrate'encoding ctx) spec.encodings in
   { spec with encodings; }

(**************************************************************)
(* inform: build values of pcunit type *)

let checktybits pos ty bits =
   let notlarger width tyname =
      if bits > width then
         Pos.crashat pos ("transform: inform: overflow: " ^
			  string_of_int bits ^ " > " ^
			  string_of_int width ^ " (type " ^ tyname ^ ")")
   in
   let notsmaller width tyname =
      if bits < width then
         Pos.crashat pos ("transform: inform: underflow: " ^
			  string_of_int bits ^ " > " ^
			  string_of_int width ^ " (type " ^ tyname ^ ")")
   in
   let same width tyname =
      notlarger width tyname;
      notsmaller width tyname
   in
   match ty with
        WIDTHTYPE ("uint", width) -> notlarger width "uint"
      | WIDTHTYPE ("zeros", width) -> notlarger width "zeros"
      | WIDTHTYPE ("ones", width) -> same width "ones"
      | _ -> Pos.crashat pos "transform: inform: invalid value type"

let maxval pos ty bits =
   checktybits pos ty bits;
   let k = if bits > 20 then
      LARGE (Types.Wide.ones bits)
   else
      SMALL (Util.ones bits)
   in
   CONST (pos, ty, k)

let zeroval pos ty bits =
   checktybits pos ty bits;
   let k = if bits > 20 then
      LARGE Types.Wide.zero
   else
      SMALL 0
   in
   CONST (pos, ty, k)

type informctx = spec

let inform'form ctx encpos formname =
   let pcunitwidth = ctx.pcunitwidth in
   let pcunittype = WIDTHTYPE ("uint", pcunitwidth) in
   let shifttype = WIDTHTYPE ("uint", 8) (* XXX: ? *) in

   let form = Types.StringMap.find formname ctx.forms in

   (* Get what we need for each field *)
   let getfieldinfo fieldname =
      let f = Types.StringMap.find fieldname ctx.fields in
      let width = match f.ty with
           WIDTHTYPE ("int", w) -> w
         | WIDTHTYPE ("uint", w) -> w
         | WIDTHTYPE ("zeros", w) -> w
         | WIDTHTYPE ("ones", w) -> w
         |  _ -> Pos.crashat encpos "Illegal field type"
      in
      let uty = WIDTHTYPE ("uint", width) in
      (* name, position, width, type, equivalent unsigned type *)
      (fieldname, f.definedat, width, f.ty, uty)
   in
   let fieldinfo = List.map getfieldinfo form.fields in

   (* For constant fields we need to bind the value *)
   let bindfield (fieldname, pos, width, ty, _uty) =
      let dobind k =
         let a = ASSIGN (pos, SETVAR (encpos, fieldname), k) in
	 [a]
      in
      match ty with
           WIDTHTYPE ("zeros", _) -> dobind (zeroval encpos ty width)
         | WIDTHTYPE ("ones", _) -> dobind (maxval encpos ty width)
         | _ -> []
   in
   let bindings = List.concat (List.map bindfield fieldinfo) in

   (* Now peel off PCUNITWIDTH bits at a time *)
   let bitpos = ref pcunitwidth in
   let wordnum = ref 0 in
   let fetchfield (fieldname, pos, width, ty, uty) =

      (* read the value out *)
      let expr = USEVAR (encpos, ty, fieldname) in

      (* cast to unsigned to prevent signed shift lossage *)
      let expr = CAST (encpos, uty, ty, expr) in

      (* mask it *)
      let expr = OP (pos, uty, BITAND, [expr; maxval pos uty width]) in

      (* this might be either widen or narrow *)
      let topcunit e =
         CAST (encpos, pcunittype, uty, e)
      in
      let nop e = e
      in

      (* widen it if needed *)
      let widetype, expr, narrow =
         if width > pcunitwidth then
            uty, expr, topcunit
         else
            pcunittype, topcunit expr, nop
      in

      (* place some; REMAINING is the number of bits left to place *)
      let rec place remaining =
         assert(remaining > 0);

         (* if we have only part of the field, truncate *)
         let myexpr = if remaining < width then
            let mymaskval = maxval pos widetype remaining in
            OP (pos, widetype, BITAND, [expr; mymaskval])
         else expr
         in
         if remaining <= !bitpos then
            (* what's left fits entirely into this unit *)
            let basepos = !bitpos - remaining in
            (* shift left into position *)
            let myexpr = if basepos > 0 then
                let shiftval = CONST (encpos, shifttype, SMALL basepos) in
                OP (pos, widetype, SHL, [myexpr; shiftval])
            else myexpr
            in
            let ret = (!wordnum, narrow myexpr) in
            (* update where we are *)
            bitpos := !bitpos - remaining;
            if !bitpos = 0 then begin
               (* to the next word *)
               wordnum := !wordnum + 1;
               bitpos := ctx.pcunitwidth;
            end else ();
            (* produce the result *)
            ret :: []
         else
            (* will need another unit for the rest of this field *)
            let leftover = remaining - !bitpos in
            (* now shift right *)
            let myexpr =
                let shiftval = CONST (encpos, shifttype, SMALL leftover) in
                OP (pos, widetype, SHR, [myexpr; shiftval])
            in
            let ret = (!wordnum, narrow myexpr) in
            (* update where we are *)
            bitpos := 0;
            (* go to the next word *)
            wordnum := !wordnum + 1;
            bitpos := ctx.pcunitwidth;
            (* produce the result and recursively do the rest *)
            ret :: place leftover
      in (* end of place *)
      place width
   in (* end of fetchfield *)

   let fieldexprs = List.concat (List.map fetchfield fieldinfo) in

   (*
    * Now we have a list of (wordnumber, expr) pairs. Fuse all the
    * exprs belonging to the same wordnumber; glue them together
    * with bitor. Entries with the same wordnumber are adjacent.
    *)
   let glue e1 e2 =
      OP (encpos, pcunittype, BITOR, [e1; e2])
   in
   let folder z (wn, e) = match z with
        [] -> [(wn, e)]
      | (wn', e') :: more ->
           if wn = wn' then
              (wn', glue e' e) :: more
           else
              (wn, e) :: (wn', e') :: more
   in
   let fieldexprs = List.fold_left folder [] fieldexprs in
   let mkstmt (_wn, e) =
      EMIT (encpos, e)
   in
   let fieldstmts = List.map mkstmt fieldexprs in

   (*
    * Important ordering considerations:
    *    - fetchfield traverses the form from left to right
    *      (high bit number to low bit number);
    *    - thus it processes most significant fields first;
    *    - even though it conses, it produces its result in order, not
    *      reversed;
    *    - the fold preserves this ordering;
    *    - thus we here have most significant output words/bytes first.
    *    - That is big-endian order.
    *
    * Currently we assume that forms are single (possibly very wide)
    * values that have bits 0 to n right to left, and that these values
    * should be emptied into memory in chunks based on the machine
    * endianness. In the long run we probably want to be more flexible
    * such that we can have forms that consist of muliple values
    * specified in fetch order and thus memory order. But this will need
    * to wait until we have an example, and probably should be codesigned
    * with subforms.
    *)
   let fieldstmts = match ctx.endian with
        LITTLE_ENDIAN -> List.rev fieldstmts
      | BIG_ENDIAN -> fieldstmts
(* XXX notyet: modes *)
(*
      | DYNAMIC_ENDIAN mode ->
           let littlecond = MODE mode in
           [IF (encpos, littlecond, List.rev fieldstmts, fieldstmts)]
*)
   in
   bindings @ fieldstmts

let inform'alt ctx formname (definedat, guard, block) =
   let stmts = inform'form ctx definedat formname in
   (definedat, guard, block @ stmts)

let inform'encoding ctx enc =
   let alts = List.map (inform'alt ctx enc.formname) enc.alternatives in
   { enc with alternatives = alts; }

let inform spec =
   let ctx = spec in
   let encodings = List.map (inform'encoding ctx) spec.encodings in
   { spec with encodings; }
