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

module TB = Typebuild
module EB = Exprbuild

module TT = Typetree
module BT = Basetree
module ET = Encodingtree
module MT = Modifiertree
module RT = Relocstree

open Rep


(**************************************************************)
(* baseinfo *)


let build'basedecl compoundtypes d =
   match d with
        BT.COMPOUNDTYPE (_pos, name, members) ->
           let build'member (pos, ty) =
              (pos, TB.build'type ty)
           in
           let members' = List.map build'member members in
           Types.StringMap.add name members' compoundtypes
      | _ -> compoundtypes

let build'basedecls ds =
   List.fold_left build'basedecl Types.StringMap.empty ds

(**************************************************************)
(* encodinginfo *)

let build'encfield fieldposmap name definedat ty relinfo =
   let offset =
      match relinfo with
           None -> 0
         | Some offset -> offset
   in
   let canuse, ty =
      match ty with
            None -> false, PLAINTYPE "<enumerated type>"
          | Some ty' -> true (* set by typeinf *), TB.build'type ty'
   in
   let bitpos =
       try
          Types.StringMap.find name fieldposmap
       with Not_found ->
          Pos.sayat definedat ("Found no bit position for field " ^ name);
          Pos.sayat definedat ("Probably this means the field is unused.");
          Util.fail ();
          0
   in
   { name; definedat; canuse; ty; bitpos; offset; }

let build'encodingdecl fieldposmap d = match d with
     ET.FIELD (definedat, name, ty, relinfo) ->
        [build'encfield fieldposmap name definedat (Some ty) relinfo]
   | ET.ENUMFIELD (definedat, name, _ty, relinfo) ->
        [build'encfield fieldposmap name definedat None relinfo]
   | ET.SUBENUM _ -> []
   | ET.SUBENUMEXPR _ -> []
   | ET.FORM _ -> []

let buildencodings fieldposmap decls =
   List.concat (List.map (build'encodingdecl fieldposmap) decls)

(**************************************************************)
(* modifierinfo *)

let rec build_modifier_type mt = match mt with
     MT.INT width -> WIDTHTYPE ("int", width)
   | MT.UINT width -> WIDTHTYPE ("uint", width)
   | MT.EXPRTYPE mt' -> EXPRTYPE (build_modifier_type mt')

let build_modifier1 { MT.name; MT.definedat; MT.argtype; MT.resulttype; } =
   let argtype' = build_modifier_type argtype in
   let resulttype' = build_modifier_type resulttype in
   (name, definedat, argtype', resulttype')

let build_modifiers1 decls =
   List.map build_modifier1 decls

let merge_modifiers m1s m2s =
   if List.length m1s <> List.length m2s then begin
      Util.say "genrelocs: merge_modifiers: mismatched counts";
      Util.fail ()
   end;
   (* note: upstream should have already checked that each list is unique *)
   let m2tab = Types.stringmap_of_list m2s in
   let merge (name, definedat, argtype, resulttype) =
      let (_m2pos, argname, block) =
         try
            Types.StringMap.find name m2tab
         with Not_found -> begin
            Util.say ("genrelocs: no expansion for modifier " ^ name);
            Util.fail();
            (definedat, "_", [])
         end
      in
      let symname = "RELOC_MOD_" ^ Upcase.upcase name in
      {
	 name; definedat;
	 argname; argtype; symname; resulttype;
	 semantics = block;
      }
   in
   List.map merge m1s

(**************************************************************)
(* relocinfo *)

(*
 * Convert a pattern to an equivalent expression, used inside
 * structure field references. The structure value should just be an
 * expression, but doing that upstream that causes complications in
 * the parser. XXX: sort that out later. In the meantime, just do
 * this conversion.
 *)
let rec pat_to_expr pat = match pat with
     RT.WRITEVAR (pos, name) ->
        USEVAR (pos, TB.notype, name)
   | RT.WRITEFIELD (pos, pat1, name) ->
        USEFIELD (pos, TB.notype, pat_to_expr pat1, name)
   | RT.UNPACK (pos, _, _) ->
        (* XXX? *)
        Pos.crashat pos "buildrep: cannot unpack here"

let rec build'pattern pat = match pat with
     RT.WRITEVAR (pos, name) ->
        SETVAR (pos, name)
   | RT.WRITEFIELD (pos, pat, name) ->
        SETFIELD (pos, pat_to_expr pat, name)
   | RT.UNPACK (pos, name, pats) ->
        UNPACK (pos, name, List.map build'pattern pats)

let rec build'statement s = match s with
     RT.ASSIGN (pos, pat, e) ->
       ASSIGN (pos, build'pattern pat, EB.build'expr e)
   | RT.IF (pos, cond, ts, fs) ->
       let ts' = build'statements ts in
       let fs' = build'statements fs in
       IF (pos, EB.build'expr cond, BLOCK ts', BLOCK fs')
   | RT.WARN (pos, msg) ->
       WARN (pos, msg)
   | RT.REQUIRE (pos, e) ->
       REQUIRE (pos, EB.build'expr e)
   | RT.BLOCK ss -> BLOCK (build'statements ss)
and build'statements ss = List.map build'statement ss

let build'rf {
		RT.name; RT.extname; RT.definedat;
		RT.frominstruction;
		RT.readop; RT.writeop;
		RT.typename;
	     } =
   let symname = Upcase.upcase name in
   let ty = match typename with
        Some ty -> TB.build'type ty
      | None -> PLAINTYPE "_"
   in
   {
      fieldname = name;
      extfieldname = extname;
      definedat;
      symname;
      input = (build'statements readop);
      output = (build'statements writeop);
      ty;
      frominstruction;
   }

let build_modifier2 { RT.name; RT.definedat; RT.arg; RT.block; } =
   (name, (definedat, arg, build'statements block))

let build'oper { RT.name; RT.definedat; RT.computation; } =
   { opername = name; definedat; actions = (build'statements computation); }

let build'code { RT.name; RT.definedat; RT.value; RT.semantics; } =
   let num = match value with
        Some n -> n
      | None ->
           (* XXX this is probably not going to do *)
           Pos.sayat definedat ("No value for relocation " ^ name);
           Util.fail ();
           0
   in
   let build'semantics sem = match sem with
        RT.NOP -> NOP
      | RT.UNSUPPORTED -> UNSUPPORTED
      | RT.APPLYIN (opname, rfnames, dogen) -> APPLYIN (opname, rfnames, dogen)
   in
   let behavior = build'semantics semantics in
   { symname = name; definedat; num; behavior; }

let build'relocdecl d = match d with
     RT.D_FIELD rf ->
        let rf' = build'rf rf in
        ([rf'], [], [], [])
   | RT.D_MODIFIER md ->
        let md' = build_modifier2 md in
        ([], [md'], [], [])
   | RT.D_OP oper ->
        let oper' = build'oper oper in
        ([], [], [oper'], [])
   | RT.D_CODES (_pos, binfmt, codes) ->
        let codes' = List.map build'code codes in
        ([], [], [], [(binfmt, codes')])
   | RT.D_SUBST _
   | RT.D_GROUP _ ->
        (* XXX notyet *)
        ([], [], [], [])

let buildrelocs decls =
   let decls' = List.map build'relocdecl decls in
   let combine (a1s, a2s, a3s, a4s) (b1s, b2s, b3s, b4s) =
      (a1s @ b1s, a2s @ b2s, a3s @ b3s, a4s @ b4s)
   in
   List.fold_right combine decls' ([], [], [], []) 

(**************************************************************)
(* builtins *)

let builtin_operations addrtype =
   let builtinpos = Pos.builtin in

   let absname = "univ_absolute" in
   let relname = "univ_relative" in

   let add =
      OP (builtinpos, addrtype, ADD, [
             USEVAR (builtinpos, addrtype, "symbol");
             USEVAR (builtinpos, addrtype, "addend");
         ])
   in
   let sub =
      OP (builtinpos, addrtype, SUB, [
             add;
             USEVAR (builtinpos, addrtype, "location");
         ])
   in

   let univ_absolute = {
      opername = absname;
      definedat = builtinpos;
      actions = [
         ASSIGN (builtinpos, SETVAR (builtinpos, absname), add);
      ];
   } in
   let univ_relative = {
      opername = relname;
      definedat = builtinpos;
      actions = [
         ASSIGN (builtinpos, SETVAR (builtinpos, relname), sub);
      ];
   } in

   (univ_absolute, univ_relative)


(**************************************************************)
(* field positions *)

(*
 * XXX this duplicates logic in genencoding; it should be made to
 * be shared. (But since it requires type info from base.def, it
 * can't just go in encodingtree...)
 * (it's check_field_positions in genencoding/typecheck.ml)
 * (except this one doesn't do a consistency checks so it's simpler)
 *)

let count'basedecl tys d =
   match d with
        BT.ENUMTYPE (_pos, name, w, _members) ->
           tys := Types.StringMap.add name w !tys
      | BT.WRAPTYPE _ ->
           Util.crash "buildrep: WRAPTYPE not expanded by basecheck"
      | _ -> ()

let typewidth tys pos name ty =
   let bad msg =
      Pos.crashat pos ("genrelocs: count_field_positions: field " ^
                       name ^ ": " ^ msg)
   in
   match ty with
        TT.PLAINTYPE (_pos, name) -> begin
            try
               Types.StringMap.find name tys
            with Not_found -> bad "invalid type"
        end
      | TT.WIDTHTYPE (_pos, _name, w) -> w
      | TT.EXPRTYPE _ -> bad "expression in field"

let fieldwidth fws pos name ty =
   try
      Types.StringMap.find name !fws
   with Not_found ->
      (* only anonymous fields should reach here *)
      match ty with
           Some (TT.WIDTHTYPE (_pos, _name, w)) -> w
         | _ -> Pos.crashat pos ("genrelocs: count_field_positions: field " ^
                                 name ^ ": cannot find width")

let count'fieldref (fws, bps) (ET.FIELDREF_ (pos, name, ty, _val)) bitpos =
   bps := Types.StringMap.add name bitpos !bps;
   bitpos + fieldwidth fws pos name ty

let count'encodingdecl (tys, fws, bps) d =
   match d with
        ET.FIELD (pos, name, ty, _encinfo) ->
           let w = typewidth tys pos name ty in
           fws := Types.StringMap.add name w !fws
      | ET.ENUMFIELD (_pos, name, ET.ENUMTYPE (_pos2, w, _mems), _encinfo) ->
           fws := Types.StringMap.add name w !fws
      | ET.FORM (_pos, fieldrefs, _statements) ->
           ignore (List.fold_right (count'fieldref (fws, bps)) fieldrefs 0)
      | _ -> ()

let count_field_positions baseinfo encodinginfo =
   let tys = ref Types.StringMap.empty in
   List.iter (count'basedecl tys) baseinfo;

   let fws = ref Types.StringMap.empty in
   let bps = ref Types.StringMap.empty in
   let ctx = (!tys, fws, bps) in
   List.iter (count'encodingdecl ctx) encodinginfo;
   !bps


(**************************************************************)
(* main *)

let build baseinfo miscinfo encodinginfo modifierinfo relocinfo =
   let addresswidth = miscinfo.Misctree.addresswidth in
   let pcunitwidth = miscinfo.Misctree.pcunitwidth in
   let addrtype = (WIDTHTYPE ("uint", addresswidth)) in

   (*
    * From baseinfo (and a separate pass through encodinginfo)
    * build the table of field positions.
    *)
   let fieldposmap = count_field_positions baseinfo encodinginfo in

   (*
    * From baseinfo get the compound types.
    *)
   let compoundtypes = build'basedecls baseinfo in

   (*
    * From encodinginfo we need the fields (and forms?)
    *)
   let (encfields(*, forms*)) = buildencodings fieldposmap encodinginfo in
   let encfieldname (ef: encfield) = ef.name in
   let encfields = Types.stringmap_of_list_by_key encfieldname encfields in

   (*
    * From modifierinfo we need the modifier list.
    *)
   let modifiers1 = build_modifiers1 modifierinfo in

   (*
    * From relocinfo we need
    *    relocfields
    *    modifier expansions (should be in modifierinfo, XXX)
    *    operations
    *    codes
    * and later on, substitutions and groupings but we don't
    * actually handle those yet (XXX)
    *)
   let (relocfields, modifiers2, operations, codes) = buildrelocs relocinfo in

   (* add the built-in operations *)
   let (univ_absolute, univ_relative) = builtin_operations addrtype in
   let operations =
      univ_absolute :: univ_relative :: operations
   in

   let modifiers = merge_modifiers modifiers1 modifiers2 in

   {
      addresswidth;
      pcunitwidth;
      compoundtypes;
      encfields;
      modifiers;
      relocfields;
      allcodes = (Types.stringmap_of_list codes);
      operations;
   }
