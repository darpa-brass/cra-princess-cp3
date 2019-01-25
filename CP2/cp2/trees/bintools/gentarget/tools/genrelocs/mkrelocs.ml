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

module TE = Typeemit
module EE = Expremit
module G = Gcode

open Rep

type file = G.file

(**************************************************************)
(* lookups *)

let getencfield spec name =
   try
      Types.StringMap.find name spec.encfields
   with Not_found ->
      Util.crash ("mkrelocs: getencfield: " ^ name ^ " not found")

(**************************************************************)
(* searches *)

(*
 * Find all the relocation codes for a given modifier and given
 * field.
 *
 * Note: owing to infrastructure inadequacies, all the assembler can
 * currently represent as MI relocs is a modifier applied to a symbol,
 * or a symbol minus the current location, stuck in a field. This is a
 * decided subset of the relocations we have, and have to be able to
 * generate, especially once we start trying to handle PIC. But for
 * now, suck it up. Convert the modifier to an operation (in the sense
 * of relocs.def operations) and then look that up in the list of
 * codes.
 *
 * The right way to fix this in the future is to upgrad the MI reloc
 * structure to hold an operation instead of a modifier, and do the
 * matching of expressions and modifiers to operations in compile_expr,
 * part of which will have to become MD.
 *
 * XXX fix this.
 *
 * Ignoring the prior issue, for each operation and field there should
 * be exactly one (or maybe zero, but not > 1) code, and this function
 * is supposed to dig it out. Ideally checkrelocs should enforce this,
 * but for now it doesn't (XXX), so we just return all the ones we
 * find and the caller will barf if multiples appear.
 *
 * Note: operations are "oper", operators in expressions (which are
 * unrelated) are "op". Blah. Maybe we should call operations something
 * else, like actions? XXX.
 *)

let findrelocs spec modname rfname ispcrel =
   let mod_to_opers () =
      (*
       * look for an oper that returns the application of the modifier
       * to "symbol + addend", or, if ISPCREL, "symbol + addend - .".
       * Also allow "modifier(symbol) + addend". XXX: those aren't matched right.
       * That's all we can do for now...
       *
       * Note: "returns" in relocs.def means "assigns to the operation
       * name".
       *)
      let checkop oper =
         let checkexpr e = match e with
              OP (_pos, _ty, ADD, [
                   USEVAR (_pos1, _ty1, nsym);
                   USEVAR (_pos2, _ty2, nadd);
               ]) ->
                (nsym = "symbol" && nadd = "addend") && ispcrel = false
            | OP (_pos, _ty, SUB, [
                   OP (_pos12, _ty12, ADD, [
                      USEVAR (_pos1, _ty1, nsym);
                      USEVAR (_pos2, _ty2, nadd);
                    ]);
                   USEVAR (_pos3, _ty3, nloc);
               ]) ->
                (nsym = "symbol" && nadd = "addend" && nloc = "location") && ispcrel = true
            | _ -> false
         in
         (* XXX factor this better *)
         let checkexpr' e = match e with
              USEVAR (_pos1, _ty1, nsym) ->
                 nsym = "symbol" && ispcrel = false
            | OP (_pos, _ty, SUB, [
                   USEVAR (_pos1, _ty1, nsym);
                   USEVAR (_pos3, _ty3, nloc);
               ]) ->
                (nsym = "symbol" && nloc = "location") && ispcrel = true
            | _ -> false
         in
         let checkmod e = match e, modname with
              _, "none" -> checkexpr e
            | MODIFIER (_pos, _ty, nmod, [arg]), _ ->
                 if nmod = modname then checkexpr arg
                 else false
            | OP (_pos, _ty, ADD, [
                 MODIFIER (_pos2, _ty2, nmod, [arg]);
                 USEVAR(_pos3, _ty3, nadd);
               ]), _ ->
                 if nmod = modname then (nadd = "addend") && checkexpr' arg
                 else false
            | OP (_pos, _ty, ADD, [
                 MODIFIER (_pos2, _ty2, nmod, [arg]);
                 CAST (_pos4, _ty4a, _ty4b, USEVAR(_pos3, _ty3, nadd));
               ]), _ ->
                 if nmod = modname then (nadd = "addend") && checkexpr' arg
                 else false
            | _ -> false
         in
         let checkactions actions = match actions with
              [ASSIGN (_pos1, SETVAR (_pos2, retname), e)] ->
                 if retname = oper.opername then checkmod e
                 else false
            | _ -> false
         in
         if checkactions oper.actions then [oper] else []
      in
      List.concat (List.map checkop spec.operations)
   in
   let oper_to_code oper =
      let checkcode code =
         match code.behavior with
              APPLYIN (nameop, namefields, true(*dogenerate*)) ->
                 if nameop = oper.opername && List.mem rfname namefields then
                    [code]
                 else []
            | _ -> []
      in
      (* XXX we need to know what binary format we're building for here... *)
      (* or something... we should probably generate code for all of them *)
      (* and then conditionalize in the output *)
      let codes = Types.StringMap.find "elf" spec.allcodes in
      List.concat (List.map checkcode codes)
   in
   let opers = mod_to_opers () in
   let codes = List.concat (List.map oper_to_code opers) in
   codes

(**************************************************************)
(* common output code *)

let u_machword = G.TYPEDEFNAME "u_machword" 

let emit_type ty = TE.emit'type ty
let emit_expr e = EE.emit'expr e

let callwarn msg =
   let msg = G.STRINGCONSTANT msg in
   G.voidcall "file_warn" [G.READVAR (G.INT, "linenum"); msg]

let callwarn1 msg arg =
   let msg = G.STRINGCONSTANT msg in
   G.voidcall "file_warn" [G.READVAR (G.INT, "linenum"); msg; arg]

let callerr msg =
   let msg = G.STRINGCONSTANT msg in
   G.voidcall "file_err" [G.READVAR (G.INT, "linenum"); msg]

(* XXX we don't have the type! *)
let rec emit_pattern pat e' = match pat with
     SETVAR (_pos, name) -> 
        [G.ASSIGN (G.WRITEVAR (G.VOID, name), e')]
   | SETFIELD (_pos, e, name) ->
        [G.ASSIGN (G.WRITEFIELD (G.VOID, emit_expr e, name), e')]
   | UNPACK (_pos, "modimm", [arg0; arg1]) ->
        (* XXX this should not exist *)
        let ln = G.READVAR (G.INT, "linenum") in
        emit_pattern arg0 (G.call G.UINT "modimm_hack_a" [ln; e']) @
        emit_pattern arg1 (G.call G.UINT "modimm_hack_b" [ln; e'])
   | UNPACK (_pos, name, _members) ->
        Util.crash ("mkrelocs: cannot unpack that yet (" ^ name ^ ")")

let rec emit_statement s = match s with
     ASSIGN (_pos, pat, e) ->
        emit_pattern pat (emit_expr e)
   | IF (_pos, cond, t, f) ->
        [G.IF (emit_expr cond, G.BLOCK (emit_statement t), G.BLOCK (emit_statement f))]
   | WARN (_pos, msg) ->
        [G.voidcall "file_warn" [
           G.READVAR (G.INT, "linenum");
           G.STRINGCONSTANT msg;
        ]]
   | REQUIRE (pos, e) ->
        (* XXX this is not really good enough *)
        let etxt = (*String.concat " "*) (dump'expr e) in

        let err = [
           callwarn ("Requirement not met: " ^ etxt);
           callerr ("Requirement at: " ^ Pos.string_of_pos pos);
        ] in
        [G.IF (emit_expr e, G.skip, G.BLOCK err)]
   | BLOCK ss ->
        [G.BLOCK (List.concat (List.map emit_statement ss))]

let emit_statements _spec ss =
   List.concat (List.map emit_statement ss)

let rec get_locals' excl z ss =
   let combine _name ty1 _ty2 = Some ty1 in
   let rec get_local z s = match s with
        ASSIGN (pos1, SETVAR (_pos2, name), e) ->
           if Types.StringMap.mem name z || Types.StringSet.mem name excl then
              z
           else 
              let ty = emit_type pos1 (exprtype e) in
              Types.StringMap.add name ty z
      | ASSIGN (_, _, _) -> z
      | IF (_pos, _cond, t, f) ->
           get_local (get_local z t) f
      | WARN _ -> z
      | REQUIRE _ -> z
      | BLOCK ss -> Types.stringmap_union combine z (get_locals' excl z ss)
   in
   List.fold_left get_local z ss

let get_locals exclude ss =
   let addexclude z x = Types.StringSet.add x z in
   let excludemap = List.fold_left addexclude Types.StringSet.empty exclude in
   let xform (name, ty) = G.LOCAL (ty, name) in
   let map = (get_locals' excludemap Types.StringMap.empty ss) in
   List.map xform (Types.StringMap.bindings map)

(*
 * XXX this shouldn't exist
 *)
(*
let fixupoddsizes odds =
   let fixup'width w =
      match w with
           8|16|32|64 -> w
         | _ -> begin
              let rec getwidth candidates = match candidates with
                   [] -> Util.crash "mkrelocs: fixupoddsizes: bad width"
                 | w' :: more -> if w' >= w then w' else getwidth more
              in
              getwidth [8;16;32;64]
           end
   in
   let rec fixup'type t = match t with
        G.INTBITS w -> G.INTBITS (fixup'width w)
      | G.UINTBITS w -> G.UINTBITS (fixup'width w)
      | G.POINTER t' -> G.POINTER (fixup'type t')
      | G.CONST t' -> G.CONST (fixup'type t')
      | _ -> t
   in
   let rec fixup'expr e = match e with
        G.INTCONSTANT (t, k) -> G.INTCONSTANT (fixup'type t, k)
      | G.READVAR (t, n) -> G.READVAR (fixup'type t, n)
      | G.READFIELD (t, e', n) -> G.READFIELD (fixup'type t, fixup'expr e', n)
      | G.READPOINTER (t, e) -> G.READPOINTER (fixup'type t, fixup'expr e)
      | G.CALL (t, f, a) -> G.CALL (fixup'type t, f, List.map fixup'expr a)
      | G.CAST (n, o, e) -> G.CAST (fixup'type n, fixup'type o, fixup'expr e)
      | G.EXPRCOMMENT (t, x, e) -> G.EXPRCOMMENT (fixup'type t, x, fixup'expr e)
      | _ -> e
   in
   let fixup'pat p = match p with
        G.WRITEVAR (t, n) -> G.WRITEVAR (fixup'type t, n)
      | G.WRITEFIELD (t, e, n) -> G.WRITEFIELD (fixup'type t, fixup'expr e, n)
      | G.WRITEPOINTER (t, e) -> G.WRITEPOINTER (fixup'type t, fixup'expr e)
   in
   let rec fixup'stmt s = match s with
        G.BLOCK ss -> G.BLOCK (List.map fixup'stmt ss)
      | G.ASSERT e -> G.ASSERT (fixup'expr e)
      | G.ASSIGN (p, e) -> G.ASSIGN (fixup'pat p, fixup'expr e)
      | G.IGNORE e -> G.IGNORE (fixup'expr e)
      | G.IF (c, t, f) -> G.IF (fixup'expr c, fixup'stmt t, fixup'stmt f)
      | G.SWITCH (c, ks, d) ->
           let fixup'case (e, s) = (fixup'expr e, fixup'stmt s) in
           let fixup'd d = match d with
                None -> None
              | Some s -> Some (fixup'stmt s)
           in
           G.SWITCH (fixup'expr c, List.map fixup'case ks, fixup'd d)
      | G.LOOP _ -> Util.crash "mkrelocs: fixupoddsizes: loop"  (* unused *)
      | G.RETURN (Some e) -> G.RETURN (Some (fixup'expr e))
      | G.LOCAL (t, n) -> G.LOCAL (fixup'type t, n)
      | G.PPSTMT _ -> Util.crash "mkrelocs: fixupoddsizes: ppstmt" (* unused *)
      | _ -> s
   in
   List.map fixup'stmt odds
*)

(*
 * Currently these are dumped out into both the linker and assembler.
 * It would be better to drop them once into binfmts/elf somewhere,
 * but currently we aren't set up for that. XXX.
 *
 * (Also we need to figure out what error reporting should look like
 * if they're going to be shared...)
 *)

(*
 * XXX: this is not good enough. Rather than fetching a value of the
 * indicated type from the indicated offset, what we need to do is:
 *    - For instruction fields, fetch the whole instruction, and
 *      mask off the field we want. This requires knowing the form
 *      the field appears in, or at least the bit offset of the
 *      field. I think we should by default fetch the *instruction*
 *      at the indicated offset and have an alternate mode where the
 *      offset is taken to include an offset into the instruction as
 *      well.
 *    - For data fields I think we can just fetch a value of the
 *      indicated type from the indicated offset, but I still need
 *      to figure out how this really works for mips.
 *
 * Apart from the issues with the jumptarget field (which I'm going
 * to hack around) what's here should work well enough for the time
 * being. But it's not right and we can't have the hack for the
 * jumptarget field in the long run.
 *)
 

let mk_relocinput spec isas (rf: relocfield) =
   let rfty' = emit_type rf.definedat rf.ty in
   let width = match rf.ty with
        WIDTHTYPE ("int", w) -> w
      | WIDTHTYPE ("uint", w) -> w
      | _ -> Pos.crashat rf.definedat
                 "mk_relocinput: invalid relocfield type"
   in
   let accesswidth = if rf.frominstruction then spec.pcunitwidth else width in
   let accesstype =
      emit_type rf.definedat (WIDTHTYPE ("uint", accesswidth))
   in
   let accesstype_signed =
      emit_type rf.definedat (WIDTHTYPE ("int", accesswidth))
   in
   let bitpos =
      if rf.frominstruction then
         let encfield = getencfield spec rf.extfieldname in
         encfield.bitpos
      else 0
   in

   (* XXX: we'll have to be able to handle this case sometime *)
   assert (width <= accesswidth);

   let params = [
      (G.INT, "linenum");
      (G.UINT, "snum");
      (u_machword, "offset");
   ] in
   let read'offset = G.READVAR (u_machword, "offset") in

   let decls = [
      G.LOCAL (u_machword, "input");
      G.LOCAL (accesstype, rf.fieldname);
      G.LOCAL (accesstype, "signbits");
      G.LOCAL (u_machword, "location");
   ] in
   let decls2 =
      get_locals ["input"; "location"; rf.fieldname] rf.input
   in
   let read'signbits = G.READVAR (accesstype, "signbits") in
   let write'signbits = G.WRITEVAR (accesstype, "signbits") in

   let inits = [
      G.IGNORE (G.READVAR (G.INT, "linenum"));
      G.IGNORE read'signbits;
      G.ASSIGN (G.WRITEVAR (u_machword, "location"),
                if isas then read'offset
                else (* XXX fetch section address *) read'offset);
      G.IGNORE (G.READVAR (u_machword, "location"));
   ] in

   (*
    * step 1: read a word out of the section
    *)
   let prep =
      let callee =
         let verb = (if isas then "get" else "fetch") in
         "section_" ^ verb ^ string_of_int accesswidth
      in
      let call = G.call accesstype callee [
                            G.READVAR (G.UINT, "snum");
			    G.READVAR (u_machword, "offset");
                ]
      in
(*
      let call = match rf.ty with
           WIDTHTYPE ("int", w) ->
              G.CAST (G.INTBITS w, G.UINTBITS w, call)
         | WIDTHTYPE ("uint", _) -> call
         | _ -> Pos.crashat rf.definedat
                 "mk_relocinput: invalid relocfield type"
      in
*)
      G.ASSIGN (G.WRITEVAR (accesstype, rf.fieldname), call)
   in

   (*
    * Step 2: mask it off
    *)
   let maskery =
      if width = accesswidth then []
      else begin
(*
         let rec getwidth candidates = match candidates with
              [] -> Util.crash "mkrelocs: mkreloc_input: bad width"
            | w :: more -> if w >= width then w else getwidth more
         in
         let w = getwidth [8;16;32;64] in
         let ty'w = (G.UINTBITS w) in
*)

         let read = G.READVAR (accesstype, rf.fieldname) in
         let write = G.WRITEVAR (accesstype, rf.fieldname) in

         (*
          * first, shift away the unwanted bottom bits.
          * the recorded bit position is the position of the bottom
          * of the field (rightmost field has position 0) so that's all
          * we need.
          *)
         let rshiftamt = (string_of_int bitpos) ^ "U" in
         let xrshiftamt = G.INTCONSTANT (G.UINT, rshiftamt) in
         let shift = G.rshift accesstype read xrshiftamt in

         (*
          * then truncate off the high bits.
          *)
         let ones = Types.Wide.to_string (Types.Wide.ones width) in
         let xones = G.INTCONSTANT (accesstype, ones ^ G.tysuffix accesstype) in
         let trunc = G.bitand accesstype shift xones in

         let mask = G.ASSIGN (write, trunc) in

         (*
          * then if the field is signed, sign-extend.
          *)
         let extend = match rf.ty with
              WIDTHTYPE ("int", _w) ->
                 let zero = G.zero accesstype in
                 let one = G.one accesstype in

                 let setone = G.ASSIGN (write'signbits, one) in
                 let shiftamt' = string_of_int (width - 1) in
                 let xlshiftamt' = G.INTCONSTANT (G.UINT, shiftamt') in
                 let testmask =
                    G.lshift accesstype read'signbits xlshiftamt'
                 in
                 let test = G.bitand accesstype read testmask in
                 let test = G.ne test zero in

                 let topwidth = accesswidth - width in
                 let ones = Types.Wide.to_string (Types.Wide.ones topwidth) in
                 let xones =
                    G.INTCONSTANT (accesstype, ones ^ G.tysuffix accesstype)
                 in
                 let setones = G.ASSIGN (write'signbits, xones) in

                 let shiftamt = string_of_int width in
                 let xlshiftamt = G.INTCONSTANT (G.UINT, shiftamt) in
                 let lshift = G.lshift accesstype read'signbits xlshiftamt in
                 let bitor = G.bitor accesstype read lshift in
                 let extassign = G.ASSIGN (write, bitor) in

                 [setone; G.IF (test, G.BLOCK [setones; extassign], G.skip)]
            | _ -> []
         in
         mask :: extend
        end
   in

   let doinput =
      if rf.input <> [] then
         emit_statements spec rf.input
      else begin
         let read = G.READVAR (accesstype, rf.fieldname) in
         let write = G.WRITEVAR (rfty', "input") in
         let cast =
            match rf.ty with
                 WIDTHTYPE ("uint", _w) ->
                    G.CAST (rfty', accesstype, read)
               | WIDTHTYPE ("int", _w) ->
                    let e = G.CAST (accesstype_signed, accesstype, read) in
                    G.CAST (rfty', accesstype_signed, e)
               | _ -> assert false
         in
         [G.ASSIGN (write, cast)]
      end
   in
   let ret =
      G.retval (G.READVAR (u_machword, "input"))
   in
   let body = decls @ decls2 @ [G.BLANKLINESTMT] @
              inits @ [prep] @ maskery @ doinput @ [ret] in

   let funcname = "reloc_input_" ^ rf.fieldname in
   G.FUNCTION (G.USTATIC, u_machword, funcname, params, G.BLOCK body)

let mk_relocinputs spec isas =
   List.map (mk_relocinput spec isas) spec.relocfields

let mk_relocoutput spec isas (rf: relocfield) =
   let rfty' = emit_type rf.definedat rf.ty in
   let width = match rf.ty with
        WIDTHTYPE ("int", w) -> w
      | WIDTHTYPE ("uint", w) -> w
      | _ -> Pos.crashat rf.definedat
                 "mk_relocoutput: invalid relocfield type"
   in
   let accesswidth = if rf.frominstruction then spec.pcunitwidth else width in
   let accesstype =
      emit_type rf.definedat (WIDTHTYPE ("uint", accesswidth))
   in
   let accesstype_signed =
      emit_type rf.definedat (WIDTHTYPE ("int", accesswidth))
   in
   let bitpos =
      if rf.frominstruction then
         let encfield = getencfield spec rf.extfieldname in
         encfield.bitpos
      else 0
   in

   (* XXX: we'll have to be able to handle this case sometime *)
   assert (width <= accesswidth);

   let params = [
      (G.INT, "linenum");
      (G.UINT, "snum");
      (u_machword, "offset");
      (u_machword, "output");
   ] in
   let read'offset = G.READVAR (u_machword, "offset") in
   let read'output = G.READVAR (u_machword, "output") in
   (*let write'output = G.WRITEVAR (u_machword, "output") in*)

   let decls = [
      G.LOCAL (accesstype, rf.fieldname);
      G.LOCAL (accesstype, "prev");
      G.LOCAL (accesstype, "ones");
      G.LOCAL (u_machword, "location");
   ] in
   let decls2 =
      get_locals [rf.fieldname; "location"] rf.output
   in
   let read'field = G.READVAR (accesstype, rf.fieldname) in
   let write'field = G.WRITEVAR (accesstype, rf.fieldname) in
   let read'prev = G.READVAR (accesstype, "prev") in
   let write'prev = G.WRITEVAR (accesstype, "prev") in
   let read'ones = G.READVAR (accesstype, "ones") in
   let write'ones = G.WRITEVAR (accesstype, "ones") in

   let inits = [
      G.IGNORE (G.READVAR (G.INT, "linenum"));
      G.IGNORE read'prev;
      G.IGNORE read'ones;
      G.ASSIGN (G.WRITEVAR (u_machword, "location"),
                if isas then read'offset
                else (* XXX fetch section address *) read'offset);
      G.IGNORE (G.READVAR (u_machword, "location"));
   ] in

   (*
    * step 1: prepare the output value
    *)
   let dooutput =
      if rf.output <> [] then
         emit_statements spec rf.output
      else begin
         let cast =
            match rf.ty with
                 WIDTHTYPE ("uint", _w) ->
                    G.CAST (accesstype, rfty', read'output)
               | WIDTHTYPE ("int", _w) ->
                    let e = G.CAST (accesstype_signed, rfty', read'output) in
                    G.CAST (accesstype, accesstype_signed, e)
               | _ -> assert false
         in
         [G.ASSIGN (write'field, cast)]
      end
   in

   (*
    * Step 2: make sure it fits
    *)
   let checkfit =
      if width = accesswidth then []
      else begin
         let pos = Pos.builtin in
         let ty = WIDTHTYPE ("uint", accesswidth) in
         let sty = WIDTHTYPE ("int", accesswidth) in
         let ty' = emit_type pos ty in
         let sty' = emit_type pos sty in
         let read = USEVAR(pos, ty, rf.fieldname) in
         let issigned = match rf.ty with
              WIDTHTYPE ("int", _) -> true
            | WIDTHTYPE ("uint", _) -> false
            | _ -> assert false
         in
         let read = if issigned then CAST (pos, sty, ty, read) else read in
         let fits =
            FITS (rf.definedat, PLAINTYPE "bool", read, rf.ty)
         in
         let fits' = emit_expr fits in
         let read' = emit_expr read in
         let fmt, readval =
            if issigned then
               "%jd", G.CAST (G.TYPEDEFNAME "intmax_t", sty', read')
            else
               "%ju", G.CAST (G.TYPEDEFNAME "uintmax_t", ty', read')
         in
         let rftystr = if issigned then "int" else "uint" in
         let err = [
            callwarn "Value does not fit relocation field";
            callwarn1 ("Value is: " ^ fmt) readval;
            callerr ("Field is: " ^ rf.fieldname ^ " :: " ^
                     rftystr ^ "(" ^ string_of_int width ^ ")");
         ] in
         [G.IF (G.lognot fits', G.BLOCK err, G.skip)]
      end
   in

   (*
    * Step 3: combine with the previous value
    *)
   let maskery =
      if width = accesswidth then []
      else begin
         (*
          * truncate off the high bits of the output value; for an
          * unsigned field this has no effect, but for a signed field
          * it gets rid of the sign extension, which would otherwise
          * overwrite the upper part of the word with 1s.
          *)
         let ones = Types.Wide.to_string (Types.Wide.ones width) in
         let xones = G.INTCONSTANT (accesstype, ones ^ G.tysuffix accesstype) in
         let setones = G.ASSIGN (write'ones, xones) in
         let trunc =
            G.ASSIGN (write'field, G.bitand accesstype read'field read'ones)
         in

         (*
          * read a word out of the section
          *)
         let prep =
            let callee =
               let verb = (if isas then "get" else "fetch") in
               "section_" ^ verb ^ string_of_int accesswidth
            in
            let call = G.call accesstype callee [
                             G.READVAR (G.UINT, "snum");
		             G.READVAR (u_machword, "offset");
                ]
            in
            G.ASSIGN (write'prev, call)
         in

         (*
          * now leftshift the output value into place
          *)
         let xlshiftamt = G.INTCONSTANT (G.UINT, string_of_int bitpos ^ "U") in
         let xlshift e = G.lshift accesstype e xlshiftamt in
         let shiftfield = G.ASSIGN (write'field, xlshift read'field) in

         (*
          * now clear the bits to be updated out of the previous value
          * shift the ones mask into place then flip it and and
          *)
         let shiftones = G.ASSIGN (write'ones, xlshift read'ones) in
         let flip = G.bitnot accesstype read'ones in
         let flipones = G.ASSIGN (write'ones, flip) in

         let clr =
            G.ASSIGN (write'prev, G.bitand accesstype read'prev read'ones)
         in

	 let join = G.bitor accesstype read'prev read'field in
	 let assign = G.ASSIGN (write'field, join) in

         [setones; trunc; prep; shiftfield; shiftones; flipones; clr; assign]
      end
   in

   let put =
      let callee =
         let verb = if isas then "put" else "store" in
         "section_" ^ verb ^ string_of_int accesswidth
      in
      G.voidcall callee [
              G.READVAR (G.UINT, "snum");
              G.READVAR (u_machword, "offset");
              read'field;
      ]
   in
   let body = decls @ decls2 @ [G.BLANKLINESTMT] @ inits @
              dooutput @ checkfit @ maskery @ [put] in
   let funcname = "reloc_output_" ^ rf.fieldname in
   G.FUNCTION (G.USTATIC, G.VOID, funcname, params, G.BLOCK body)

let mk_relocoutputs spec isas =
   List.map (mk_relocoutput spec isas) spec.relocfields

let mk_modifierfunc spec (mod_: modifier) =
   let params = [
      (G.INT, "linenum");
      (emit_type mod_.definedat mod_.argtype, mod_.argname)
   ] in
   let rettype = emit_type mod_.definedat mod_.resulttype in
   let name = "modifier_" ^ mod_.name in
   let decls = [
      G.LOCAL (rettype, mod_.name);
   ] in
   let decls2 =
      get_locals [mod_.name] mod_.semantics
   in
   let inits = [
      G.IGNORE (G.READVAR (G.INT, "linenum"));
   ] in
   
   let stmts = emit_statements spec mod_.semantics in
   let body =
      decls @ decls2 @ [G.BLANKLINESTMT] @ inits @
      stmts @ [G.retval (G.READVAR (rettype, mod_.name))]
   in
   (G.FUNCDECL (G.USTATIC, rettype, name, params),
    G.FUNCTION (G.USTATIC, rettype, name, params, G.BLOCK body))

let mk_modifierfuncs spec =
   let (decls, funcs) =
      Util.unzip (List.map (mk_modifierfunc spec) spec.modifiers)
   in
   decls @ funcs

(**************************************************************)
(* elfreloc.h: header file of relocation codes *)

let mk_elfreloc_h spec =
   let mkdefine code =
      let k = G.INTCONSTANT (G.UINT, string_of_int code.num) in
      let sym = "R_" ^ code.symname in
      G.DEFINE (sym, Some k)
   in

   let codes = Types.StringMap.find "elf" spec.allcodes in

   let guardsym = "ELF_TARGET_RELOC_H" in
   let defines = List.map mkdefine codes in
   G.FILE (Some guardsym, [], defines)

(**************************************************************)
(* targetreloc.h: modifier and field enums (for as) *)

let mk_modifier_enum spec =
   let mkenumerator (mod_: modifier) =
      (mod_.symname, None, None)
   in
   let none = ("RELOC_MOD_NONE", None, None) in
   let enumerators = none :: (List.map mkenumerator spec.modifiers) in
   G.ENUMDECL ("reloc_modifier", enumerators)

let mk_relocfield_enum spec =
   let enumeratorname (rf: relocfield) =
      "RELOC_FIELD_" ^ rf.symname
   in
   let mkenumerator (rf: relocfield) =
      (enumeratorname rf, None, None)
   in
   let enumerators = List.map mkenumerator spec.relocfields in
   (* doesn't matter which one this is *)
   let defaultfieldname = enumeratorname (List.hd spec.relocfields) in
   let defaultfield = G.READVAR (G.ENUMTYPE "reloc_field", defaultfieldname) in
   (G.ENUMDECL ("reloc_field", enumerators), defaultfield)

let mk_targetreloc_h spec =
   let guardsym = "TARGETRELOC_H" in
   let modifierenum = mk_modifier_enum spec in
   let (fieldenum, defaultfield) = mk_relocfield_enum spec in
   let defaultdefine =
      G.DEFINE ("RELOC_FIELD_DEFAULT", Some defaultfield)
   in
   let body = [
      modifierenum;
      G.BLANKLINEDECL;
      fieldenum;
      G.BLANKLINEDECL;
      defaultdefine;
   ] in
   G.FILE (Some guardsym, [], body)

(**************************************************************)
(* targetreloc.c: modifier and field code (for as) *)

let mk_getmodifier spec =
   let rmenum = G.ENUMTYPE "reloc_modifier" in
   let params = [
      (G.constcharptr, "name");
   ] in
   let mktest (mod_: modifier) tail =
      G.IF (G.streq (G.READVAR (G.constcharptr, "name"))
                    (G.STRINGCONSTANT mod_.name),
            G.retval (G.READVAR (rmenum, mod_.symname)),
            tail)
   in
   let end_ = [
      G.IGNORE (G.READVAR (G.constcharptr, "name")); (* in case none *)
      G.STMTCOMMENT "?";
      G.ASSERT (G.INTCONSTANT (G.INT, "0"));
      G.retval (G.READVAR (rmenum, "RELOC_MOD_NONE"));
   ] in
   let tests = List.fold_right mktest spec.modifiers (G.BLOCK end_) in
   let body = G.BLOCK [tests] in
      
   G.FUNCTION (G.GLOBAL, rmenum, "target_reloc_getmodifier", params, body)

let mk_modifiername spec =
   let rmenum = G.ENUMTYPE "reloc_modifier" in
   let null = G.READVAR (G.constcharptr, "NULL") in
   let params = [
      (rmenum, "mod");
   ] in
   let mkcase (mod_: modifier) =
      let block = G.retval (G.STRINGCONSTANT ("%" ^ mod_.name)) in
      (G.READVAR (rmenum, mod_.symname), block)
   in
   let nullcase =
      let block = G.retval null in
      (G.READVAR (rmenum, "RELOC_MOD_NONE"), block)
   in
   let cases = nullcase :: (List.map mkcase spec.modifiers) in
   let body = [
      G.SWITCH (G.READVAR (rmenum, "mod"), cases, None);
      G.ASSERT (G.INTCONSTANT (G.INT, "0"));
      G.retval null;
   ] in

   let funcname = "target_reloc_modifier_name" in
   G.FUNCTION (G.GLOBAL, G.constcharptr, funcname, params, G.BLOCK body)

let mk_fieldname spec =
   let rftype = G.ENUMTYPE "reloc_field" in
   let params = [
      (rftype, "rf");
   ] in
   let mkcase rf =
      let block = G.retval (G.STRINGCONSTANT rf.fieldname) in
      (G.READVAR (rftype, "RELOC_FIELD_" ^ rf.symname), block)
   in
   let cases = List.map mkcase spec.relocfields in
   let body = [
      G.SWITCH (G.READVAR (rftype, "rf"), cases, None);
      G.ASSERT (G.INTCONSTANT (G.INT, "0"));
      G.retval (G.READVAR (G.constcharptr, "NULL"));
   ] in

   let funcname = "target_reloc_field_name" in
   G.FUNCTION (G.GLOBAL, G.constcharptr, funcname, params, G.BLOCK body)

let mk_applydirectly spec =
   let rftype = G.ENUMTYPE "reloc_field" in
   let rt = G.POINTER (G.STRUCTTYPE "reloc") in
   let params = [
      (rt, "r");
      (u_machword, "value");
   ] in
   let decls = [
      G.LOCAL (G.INT, "linenum");
      G.LOCAL (G.UINT, "snum");
      G.LOCAL (u_machword, "orig");
   ] in 
   let inits = [
      G.ASSIGN (G.WRITEVAR (G.INT, "linenum"),
                G.READFIELD (G.INT, G.READVAR (rt, "r"), "r_linenum"));
      G.ASSIGN (G.WRITEVAR (G.UINT, "snum"),
                G.READFIELD (G.UINT, G.READVAR (rt, "r"), "r_sectnum"));
   ] in
   let mkcase rf =
      let block = [
         G.ASSIGN (G.WRITEVAR (u_machword, "orig"),
                   G.call u_machword ("reloc_input_" ^ rf.fieldname) [
		       G.READVAR (G.INT, "linenum");
                       G.READVAR (G.UINT, "snum");
                       G.READFIELD (u_machword, G.READVAR (rt, "r"),
                                    "r_offset");
                   ]);
         G.ASSERT (G.eq (G.READVAR (u_machword, "orig"))
                        (G.INTCONSTANT (u_machword, "0")));
         G.voidcall ("reloc_output_" ^ rf.fieldname) [
		        G.READVAR (G.INT, "linenum");
                        G.READVAR (G.UINT, "snum");
		        G.READFIELD (u_machword, G.READVAR (rt, "r"),
                                     "r_offset");
                        G.READVAR (u_machword, "value");
                     ];
         G.BREAK;
      ] in
      (G.READVAR (rftype, "RELOC_FIELD_" ^ rf.symname), G.BLOCK block)
   in
   let defaultcase =
      G.BLOCK [G.ASSERT (G.INTCONSTANT (G.INT, "0")); G.BREAK]
   in
   let cases = List.map mkcase spec.relocfields in
   let switch = G.SWITCH (G.READFIELD (rftype, G.READVAR (rt, "r"), "r_field"),
                          cases, Some defaultcase) in
   let body = decls @ inits @ [switch] in

   let funcname = "target_reloc_apply_directly" in
   G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK body)

let mk_modapply spec addrtype =
   let rmenum = G.ENUMTYPE "reloc_modifier" in
   let params = [
      (G.INT, "linenum");
      (rmenum, "m");
      (u_machword, "value");
   ] in
   let decls = [
   ] in
   let igns = [
      G.IGNORE (G.READVAR (G.INT, "linenum"));
   ] in

   let nonecase = (G.READVAR (rmenum, "RELOC_MOD_NONE"), G.BREAK) in
   let mkcase (mod_: modifier) =
      let rty' = emit_type mod_.definedat mod_.resulttype in
      let call =
         let name = ("modifier_" ^ mod_.name) in
         G.call rty' name [
            G.READVAR (G.INT, "linenum");
            G.READVAR (u_machword, "value");
         ]
      in
      let call =
         if mod_.resulttype <> addrtype then begin
            match mod_.resulttype, addrtype with
                 WIDTHTYPE ("int", _), WIDTHTYPE ("uint", w) ->
                    G.CAST (G.UINTBITS w, G.INTBITS w,
                            G.CAST (G.INTBITS w, rty', call))
               | WIDTHTYPE ("uint", _), WIDTHTYPE ("uint", w) ->
                    G.CAST (G.UINTBITS w, rty', call)
               | _ -> Pos.crashat mod_.definedat
                         "mkrelocs: mk_apply: invalid modifier types"
         end
         else call
      in
      (G.READVAR (rmenum, mod_.symname), G.BLOCK [
          G.ASSIGN (G.WRITEVAR (u_machword, "value"), call);
          G.BREAK;
      ])
   in
   let cases = nonecase :: List.map mkcase spec.modifiers in
   let switch =
      G.SWITCH (G.READVAR (rmenum, "m"), cases, None)
   in
   let ret = G.retval (G.READVAR(u_machword, "value")) in
   let body = decls @ [G.BLANKLINESTMT] @ igns @ [switch; ret] in

   let funcname = "target_modifier_apply" in
   G.FUNCTION (G.GLOBAL, u_machword, funcname, params, G.BLOCK body)

let mk_apply _spec _addrtype =
   let rmenum = G.ENUMTYPE "reloc_modifier" in
   let rt = G.POINTER (G.STRUCTTYPE "reloc") in
   let params = [
      (rt, "r");
      (u_machword, "value");
   ] in
   let decls = [
      G.LOCAL (G.INT, "linenum");
   ] in
   let inits = [
      G.ASSIGN (G.WRITEVAR (G.INT, "linenum"),
                G.READFIELD (G.INT, G.READVAR (rt, "r"), "r_linenum"));
   ] in

   let modify =
      G.ASSIGN (G.WRITEVAR (u_machword, "value"),
                G.call u_machword "target_modifier_apply" [
                   G.READVAR (G.INT, "linenum");
                   G.READFIELD (rmenum, G.READVAR (rt, "r"), "r_modifier");
                   G.READVAR (u_machword, "value");
                ])
   in
   let call =
       G.voidcall "target_reloc_apply_directly" [
             G.READVAR (rt, "r");
             G.READVAR (u_machword, "value")
       ]
   in
   let body = decls @ [G.BLANKLINESTMT] @ inits @ [modify; call] in

   let funcname = "target_reloc_apply" in
   G.FUNCTION (G.GLOBAL, G.VOID, funcname, params, G.BLOCK body)

let mk_rawcode spec =
   let ty'label = G.POINTER (G.STRUCTTYPE "label") in

   let rmenum = G.ENUMTYPE "reloc_modifier" in
   let rfenum = G.ENUMTYPE "reloc_field" in
   let rt = G.POINTER (G.STRUCTTYPE "reloc") in
   let params = [
      (rt, "r");
   ] in
   let decls = [
      G.LOCAL (rmenum, "mod");
      G.LOCAL (rfenum, "rf");
      G.LOCAL (G.BOOL, "isrel");
   ] in
   let inits = [
      G.ASSIGN (G.WRITEVAR (rmenum, "mod"),
                G.READFIELD (rmenum, G.READVAR (rt, "r"), "r_modifier"));
      G.ASSIGN (G.WRITEVAR (rfenum, "rf"),
                G.READFIELD (rfenum, G.READVAR (rt, "r"), "r_field"));
      G.ASSIGN (G.WRITEVAR (G.BOOL, "isrel"),
		G.ne (G.READFIELD (ty'label, G.READVAR (rt, "r"), "r_sym2"))
                     G.null);
   ] in

   (*
    * For each RELOC_MOD_* case and RELOC_FIELD_* case (and isrel case)
    * there should be no more than one raw relocation code to
    * represent the operation in the output. The checker is supposed
    * to ensure that this is so. (XXX: but it currently doesn't)
    *)

   let mkchoosereloc modname rf ispcrel =
      match findrelocs spec modname rf.fieldname ispcrel with
           [] -> [
              G.voidcall "file_err" [
                  G.READFIELD (G.INT, G.READVAR (rt, "r"), "r_linenum");
                  G.STRINGCONSTANT "Cannot encode relocation in output";
              ];
              G.BREAK;
           ]
         | code :: [] -> [
              G.retval (G.READVAR (G.INT, "R_" ^ code.symname));
           ]
         | codes ->
              let codenames = List.map (fun (c: code) -> c.symname) codes in
              let m = String.concat ", " codenames in
              Util.crash ("Multiple relocation encodings: mod=" ^
                            modname ^ ", rf=" ^ rf.fieldname ^
                            ", candidates: " ^ m)
   in

   (*
    * The inner switch: switch on the field.
    *)

   let mkinnercase modname (rf: relocfield) =
      (G.READVAR (rfenum, "RELOC_FIELD_" ^ rf.symname),
       G.IF (G.READVAR (G.BOOL, "isrel"),
             G.BLOCK (mkchoosereloc modname rf true),
	     G.BLOCK (mkchoosereloc modname rf false)))
   in
   let mkinnerswitch modname =
      G.SWITCH (G.READVAR (rfenum, "rf"),
		List.map (mkinnercase modname) spec.relocfields, None)
   in

   (*
    * The outer switch: switch on the modifier.
    *
    * FUTURE: should probably make each case its own function instead
    * of nesting the additional switchery.
    *)
   let mkoutercase modname modsymname =
      let block = [
         mkinnerswitch modname;
         G.BREAK;
      ] in
      (G.READVAR (rmenum, modsymname), G.BLOCK block)
   in
   let mkoutercase' (mod_: modifier) = mkoutercase mod_.name mod_.symname in
   let outercases =
      mkoutercase "none" "RELOC_MOD_NONE" ::
      List.map mkoutercase' spec.modifiers
   in
   let outerswitch = G.SWITCH (G.READVAR (rmenum, "mod"), outercases, None) in

   (* XXX handle binary formats properly *)
   let codes = Types.StringMap.find "elf" spec.allcodes in
   let codedefault = List.hd codes in
   let codedefaultname = "R_" ^ codedefault.symname in
   let body = decls @ inits @ [outerswitch] @ [
      G.ASSERT (G.INTCONSTANT (G.INT, "0"));
      G.retval (G.READVAR (G.INT, codedefaultname));
   ] in

   let funcname = "target_reloc_code_raw" in
   G.FUNCTION (G.STATIC, G.INT, funcname, params, G.BLOCK body)

let mk_code _spec =
   let rt = G.POINTER (G.STRUCTTYPE "reloc") in
   let params = [
      (rt, "r");
   ] in
   let call = G.call G.INT "target_reloc_code_raw" [G.READVAR (rt, "r")] in
   let body' =
      G.PPIF (G.PPDEFINED "TARGET_ELF_USE_REL", [
         G.retval (G.neg G.INT call);
      ], G.PPIF (G.PPDEFINED "TARGET_ELF_USE_RELA", [
         G.retval call;
      ], (G.PPELSE [
         (* should be impossible nowadays... *)
         G.PPERROR "TARGET_ELF_USE_REL/RELA not set";
      ])))
   in
   let body = G.PPSTMT body' in

   let funcname = "target_reloc_code" in
   G.FUNCTION (G.GLOBAL, G.INT, funcname, params, body)

let mk_preoutput _spec =
   let rt = G.POINTER (G.STRUCTTYPE "reloc") in
   let params = [
      (rt, "r");
   ] in
   let body' =
      G.PPIF (G.PPDEFINED "TARGET_ELF_USE_REL", [
         G.voidcall "target_reloc_apply_directly" [
                     G.READVAR (rt, "r");
                     G.READFIELD (u_machword, G.READVAR (rt, "r"), "r_addend");
         ];
         G.ASSIGN (G.WRITEFIELD (u_machword, (G.READVAR (rt, "r")), "r_addend"),
                   G.INTCONSTANT (u_machword, "0"));
      ], (G.PPELSE [
         G.IGNORE (G.READVAR (rt, "r"));
      ]));
   in
   let body = G.PPSTMT body' in

   let funcname = "target_reloc_preoutput" in
   G.FUNCTION (G.GLOBAL, G.VOID, funcname, params, body)

let mk_targetreloc_c spec addrtype =
   let headers = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "string.h";
      G.SYSINCLUDE "assert.h";
      G.LOCALINCLUDE "common.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "utils.h";
      G.LOCALINCLUDE "section.h";
      G.LOCALINCLUDE "reloc.h";
      G.LOCALINCLUDE "elfreloc.h";
      G.LOCALINCLUDE "targetreloc.h";
      G.LOCALINCLUDE "targetelfdefs.h";
      G.LOCALINCLUDE "as.h";  (* XXX for modimm hack *)
      G.BLANKLINEINCLUDE;
   ] in
   let funcs =
      mk_getmodifier spec ::
      mk_modifiername spec ::
      mk_fieldname spec ::
      mk_relocinputs spec true @
      mk_relocoutputs spec true @
      mk_modifierfuncs spec @
      [mk_applydirectly spec] @
      [mk_modapply spec addrtype] @
      [mk_apply spec addrtype] @
      [mk_rawcode spec] @
      [mk_code spec] @
      [mk_preoutput spec]
   in
   G.FILE (None, headers, funcs)

(**************************************************************)
(* treloc.c: resolve code (for ld) *)

let mk_operfunc spec addrtype (op: operation) =
   (* XXX op.definedat is the wrong position for this... *)
   let addrtype' = emit_type op.definedat addrtype in

   let params = [
      (G.INT, "linenum");
      (* XXX I had this as "symval" and maybe that's better *)
      (addrtype', "symbol");
      (addrtype', "addend");
      (addrtype', "offset");
      (addrtype', "location");
   ] in
   let decls =
      get_locals [] op.actions
   in
   let inits = [
      G.IGNORE (G.READVAR (G.INT, "linenum"));
      G.IGNORE (G.READVAR (G.INT, "addend"));
      G.IGNORE (G.READVAR (G.INT, "offset"));
      G.IGNORE (G.READVAR (G.INT, "location"));
   ] in

   let actions = emit_statements spec op.actions in
   let ret = G.retval (G.READVAR (addrtype', op.opername)) in
   let body = decls @ [G.BLANKLINESTMT] @ inits @ actions @ [ret] in

   let funcname = "reloc_compute_" ^ op.opername in
   G.FUNCTION (G.STATIC, addrtype', funcname, params, G.BLOCK body)

let mk_operfuncs spec addrtype =
   List.map (mk_operfunc spec addrtype) spec.operations

let mk_doreloc spec =
   let params = [
      (G.INT, "code");
      (G.UINT, "section");
      (u_machword, "offset");
      (u_machword, "symval");
      (u_machword, "addend");
   ] in
   let decls = [
      G.LOCAL (u_machword, "location");
      G.LOCAL (u_machword, "value");
      G.LOCAL (G.INT, "linenum");
   ] in

   (* XXX handle binary formats properly *)
   let codes = Types.StringMap.find "elf" spec.allcodes in

   let inits = [
      G.ASSIGN (G.WRITEVAR (u_machword, "location"),
                G.add u_machword (G.call u_machword "section_getbase" [
                                     G.READVAR (G.UINT, "section")
                                  ])
                                 (G.READVAR (u_machword, "offset")));
      G.ASSIGN (G.WRITEVAR (G.INT, "linenum"), G.zero G.INT);
   ] in

   let mkinputcase code =
      let s =
         match code.behavior with
              NOP -> [
                 G.STMTCOMMENT "nop";
                 G.retvoid;
              ]
            | UNSUPPORTED ->
                 (*
                  * XXX: should generate a diagnostic properly
                  * ...the handwritten code asserts and says
                  * "XXX how do we error in here?"...
                  *)
                 let msg =
                    "Unsupported relocation " ^ string_of_int code.num
                 in
              [
                 G.STMTCOMMENT "unsupported";
                 G.ASSERT (G.lognot (G.STRINGCONSTANT msg));
                 G.BREAK;
              ]
            | APPLYIN (_opername, rfnames, _dogenerate) ->
                 (*
                  * If this relocation can be done in multiple fields,
                  * the first one is the one the linker uses; this should
                  * ordinarily be the smallest one. See typecheck.
                  *)
                 let rfname = match rfnames with
                      [] -> assert false
                    | rfname :: _ -> rfname
                 in
                 let inputname = "reloc_input_" ^ rfname in
                 let call = G.call u_machword inputname [
                               G.READVAR (G.INT, "linenum");
                               G.READVAR (G.UINT, "section");
                               G.READVAR (u_machword, "offset");
                     ]
                 in
		 let add =
                     G.add u_machword (G.READVAR (u_machword, "addend")) call
                 in
                 [
                    G.ASSIGN (G.WRITEVAR (u_machword, "addend"), add);
                    G.BREAK;
                 ]
      in
      (G.READVAR (G.INT, "R_" ^ code.symname), G.BLOCK s)
   in
   let inputblock =
      let defaultcase = G.BLOCK [
         callwarn1 "Unknown relocation code %d" (G.READVAR (G.INT, "code"));
         callerr "Fatal error, sorry"
      ] in
      let cases = List.map mkinputcase codes in
      [
         G.ASSIGN (G.WRITEVAR (G.INT, "code"),
                   G.neg G.INT (G.READVAR (G.INT, "code")));
         G.SWITCH (G.READVAR (G.INT, "code"), cases, Some defaultcase);
      ]
   in
   let inputpart =
      G.IF (G.lt (G.READVAR (G.INT, "code")) (G.INTCONSTANT (G.INT, "0")),
            G.BLOCK inputblock,
            G.BLOCK [])
   in
   let mkcomputecase code =
      let s =
         match code.behavior with
              NOP -> [
                 G.STMTCOMMENT "nop";
                 G.retvoid;
              ]
            | UNSUPPORTED -> 
                 (*
                  * XXX: should generate a diagnostic properly
                  * ...the handwritten code asserts and says
                  * "XXX how do we error in here?"...
                  *)
                 let msg =
                    "Unsupported relocation " ^ string_of_int code.num
                 in
              [
                 G.STMTCOMMENT "unsupported";
                 G.ASSERT (G.lognot (G.STRINGCONSTANT msg));
                 G.BREAK;
              ]
            | APPLYIN (opername, _rfnames, _dogenerate) ->
                 let call = G.call u_machword ("reloc_compute_" ^ opername) [
                              G.READVAR (G.INT, "linenum");
                              G.READVAR (u_machword, "symval");
                              G.READVAR (u_machword, "addend");
                              G.READVAR (u_machword, "offset");
                              G.READVAR (u_machword, "location");
                            ]
                 in
                 [
                    G.ASSIGN (G.WRITEVAR (u_machword, "value"), call);
                    G.BREAK;
                 ]
      in
      (G.READVAR (G.INT, "R_" ^ code.symname), G.BLOCK s)
   in
   let computepart =
      let defaultcase = G.BLOCK [
         callwarn1 "Unknown relocation code %d" (G.READVAR (G.INT, "code"));
         callerr "Fatal error, sorry"
      ] in
      let cases = List.map mkcomputecase codes in
      G.SWITCH (G.READVAR (G.INT, "code"), cases, Some defaultcase)
   in

   let mkoutputcase code =
      let s =
         match code.behavior with
              NOP -> [
                 G.STMTCOMMENT "nop";
                 G.retvoid;
              ]
            | UNSUPPORTED ->
                 (*
                  * XXX: should generate a diagnostic properly
                  * ...the handwritten code asserts and says
                  * "XXX how do we error in here?"...
                  *)
                 let msg =
                    "Unsupported relocation " ^ string_of_int code.num
                 in
              [
                 G.STMTCOMMENT "unsupported";
                 G.ASSERT (G.lognot (G.STRINGCONSTANT msg));
                 G.BREAK;
              ]
            | APPLYIN (_opername, rfnames, _dogenerate) ->
                 (*
                  * If this relocation can be done in multiple fields,
                  * the first one is the one the linker uses; this should
                  * ordinarily be the smallest one. See typecheck.
                  *)
                 let rfname = match rfnames with
                      [] -> assert false
                    | rfname :: _ -> rfname
                 in
              [
                 G.voidcall ("reloc_output_" ^ rfname) [
                       G.READVAR (G.INT, "linenum");
                       G.READVAR (G.INT, "section");
                       G.READVAR (u_machword, "offset");
                       G.READVAR (u_machword, "value");
                 ];
                 G.BREAK;
              ]
      in
      (G.READVAR (G.INT, "R_" ^ code.symname), G.BLOCK s)
   in
   let outputpart =
      let defaultcase = G.BLOCK [
         callwarn1 "Unknown relocation code %d" (G.READVAR (G.INT, "code"));
         callerr "Fatal error, sorry"
      ] in
      let cases = List.map mkoutputcase codes in
      G.SWITCH (G.READVAR (G.INT, "code"), cases, Some defaultcase)
   in

   let body = decls @ inits @ [inputpart; computepart; outputpart] in

   let funcname = "machdep_do_reloc" in
   G.FUNCTION (G.GLOBAL, G.VOID, funcname, params, G.BLOCK body)

let mk_treloc_c spec addrtype =
   let headers = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "assert.h";
      G.LOCALINCLUDE "common.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "elfreloc.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE "section.h";
      G.LOCALINCLUDE "outputrel.h";
      G.BLANKLINEINCLUDE;
   ] in
   let funcs =
      mk_relocinputs spec false @
      mk_relocoutputs spec false @
      mk_modifierfuncs spec @
      mk_operfuncs spec addrtype @
      [mk_doreloc spec]
   in
   G.FILE (None, headers, funcs)

(**************************************************************)
(* toplevel *)

let mkrelocs spec =
   let addrtype = (WIDTHTYPE ("uint", spec.addresswidth)) in

   let elfreloc_h = mk_elfreloc_h spec in
   let targetreloc_h = mk_targetreloc_h spec in
   let targetreloc_c = mk_targetreloc_c spec addrtype in
   let treloc_c = mk_treloc_c spec addrtype in
   (elfreloc_h, targetreloc_h, targetreloc_c, treloc_c)
