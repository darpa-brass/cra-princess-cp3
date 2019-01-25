(*
 * Copyright (c) 2016, 2017
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

(* XXX rearrange these to match better *)
module B = Basetree
module M = Modifiertree
module T = Encodingtree
module O = Opmatchtree

module TB = Typebuild
module EB = Exprbuild

(**************************************************************)
(* unique names *)

let nexttemp = ref 0
let getname prefix =
   let x = prefix ^ string_of_int !nexttemp in
   nexttemp := !nexttemp + 1;
   x

(**************************************************************)
(* the representation under construction *)

(* these lists accumulate backwards *)
let allenums = ref []
let allsubenums = ref []
let allfields = ref []
let allforms = ref []
let allcompoundtypes = ref []
let alloperandtags = ref []
let allmodifiers = ref []
let allencodings = ref []
let allmacros = ref []
let allinstructions = ref []

let doadd slot x = slot := x :: !slot

let addenum e = doadd allenums e
let addsubenum s = doadd allsubenums s
let addfield f = doadd allfields f
let addform f = doadd allforms f
let addcompoundtype ot = doadd allcompoundtypes ot
let addoperandtag ot = doadd alloperandtags ot
let addmodifier m = doadd allmodifiers m
let addencoding e = doadd allencodings e
let addmacro m = doadd allmacros m
let addinstruction i = doadd allinstructions i

(**************************************************************)
(* encodinginfo types *)

(* moved to typebuild.ml *)

(**************************************************************)
(* encodinginfo expressions *)

(* moved to exprbuild.ml *)

let concretize pos oe = match oe with
     Some e -> e
   | None -> EB.mkbool pos true

(**************************************************************)
(* encodinginfo patterns *)

let rec conv'pattern pat = match pat with
     T.SETVAR (pos, name) -> Rep.SETVAR (pos, name)
   | T.UNPACK (pos, ctor, args) ->
        let args' = List.map conv'pattern args in
        Rep.UNPACK (pos, ctor, args')

(**************************************************************)
(* encodinginfo statements *)

type formctx = {
   formname: string;
   assignments: (Pos.pos * Rep.pattern * Rep.expr) list ref;
}
let newformctx formname = {
   formname;
   assignments = ref [];
}

(*
 * Statement in an encoding. Only assignments are allowed.
 * (and, now, warnings)
 *)
let conv'encstmt s = match s with
     T.ASSIGN (pos, pat, e) ->
        let e' = EB.build'expr e in
        let pat' = conv'pattern pat in
        Rep.ASSIGN (pos, pat', e')
   | T.ENCODE _ ->
        Util.crash "buildrep: ENCODE inside encoding not trapped upstream"
   | T.MACRO _ ->
        Util.crash "buildrep: MACRO inside encoding not trapped upstream"
   | T.IF (_pos, _e, _tblock, _fblock) ->
        (*
         * This maybe should be legal, but it gets aggravatingly
         * complicated and provides very little bang for the buck.
         *)
        Util.crash "buildrep: IF inside encoding not trapped upstream"
   | T.USE _ ->
        Util.crash "buildrep: USE inside encoding not trapped upstream"
   | T.WARN (pos, text) ->
        Rep.WARN (pos, text)

(*
 * Whole encoding
 *)
let build'encoding formname pos insn guard assignments block =
   let block' = List.map conv'encstmt block in
   let stmts' = assignments @ block' in
   let T.INSN (_pos'name, name, specargnames, opargnames) = insn in

   let addtype defty (pos'arg, argname, optty) =
      let ty = match optty with
           None -> defty
         | Some ty -> TB.build'type ty
      in
      (pos'arg, argname, ty)
   in
   let specargs = List.map (addtype TB.notype) specargnames in
   let opargs = List.map (addtype TB.notype) opargnames in

   let guard' = concretize pos guard in

   addencoding {
      Rep.name;
      Rep.mangledname = "";
      Rep.definedat = pos;
      Rep.specargs;
      Rep.opargs;
      Rep.formname;
      Rep.alternatives = [(pos, guard', stmts')];
   }

(*
 * Statement in a macro
 *)
let rec conv'macrostmt s = match s with
     T.ASSIGN (pos, pat, e) ->
        let e' = EB.build'expr e in
        let pat' = conv'pattern pat in
        Rep.ASSIGN (pos, pat', e')
   | T.ENCODE _ ->
        Util.crash "buildrep: ENCODE inside macro not trapped upstream"
   | T.MACRO _ ->
        Util.crash "buildrep: MACRO inside macro not trapped upstream"
   | T.IF (pos, e, tblock, fblock) ->
        let e' = EB.build'expr e in
        let tblock' = List.map conv'macrostmt tblock in
        let fblock' = List.map conv'macrostmt fblock in
        Rep.IF (pos, e', tblock', fblock')
   | T.USE (pos, name, specargs, opargs) ->
        let specargs' = List.map EB.build'expr specargs in
        let opargs' = List.map EB.build'expr opargs in
        let resolvedname = "??" in
        Rep.USE (pos, name, specargs', opargs', resolvedname)
   | T.WARN (pos, text) ->
        Rep.WARN (pos, text)

(*
 * Whole macro
 *)
let build'macro pos insn guard assignments block =
   let doassign (pos2, name, e) =
      Rep.ASSIGN (pos2, name, e)
   in
   let assignments' = List.map doassign assignments in
   let block' = List.map conv'macrostmt block in
   let stmts' = assignments' @ block' in
   let T.INSN (_pos'name, name, specargnames, opargnames) = insn in

   let addtype defty (pos'arg, argname, optty) =
      let ty = match optty with
           None -> defty
         | Some ty -> TB.build'type ty
      in
      (pos'arg, argname, ty)
   in
   let specargs = List.map (addtype TB.notype) specargnames in
   let opargs = List.map (addtype TB.notype) opargnames in

   let guard' = concretize pos guard in

   addmacro {
      Rep.name;
      Rep.mangledname = "";
      Rep.definedat = pos;
      Rep.specargs;
      Rep.opargs;
      Rep.expansions = [(pos, guard', stmts')];
   }

(*
 * Statement not in an encoding or macro
 *)
let build'outerstmt (ctx : formctx) s = match s with
     T.ASSIGN (pos, pat, e) ->
        let e' = EB.build'expr e in
        let pat' = conv'pattern pat in
        ctx.assignments := (pos, pat', e') :: !(ctx.assignments)
   | T.ENCODE (pos, insn, optguard, block) ->
        let guard = EB.build'optexpr optguard in
        let assignments = List.map (fun x -> Rep.ASSIGN x) !(ctx.assignments) in
        build'encoding ctx.formname pos insn guard assignments block
   | T.MACRO (pos, insn, optguard, block) ->
        let guard = EB.build'optexpr optguard in
        build'macro pos insn guard !(ctx.assignments) block
   | T.IF _ ->
        Util.crash "buildrep: IF outside macro not trapped upstream"
   | T.USE _ ->
        Util.crash "buildrep: USE outside macro not trapped upstream"
   | T.WARN _ ->
        Util.crash "buildrep: WARN outside macro/encoding not trapped upstream"

(**************************************************************)
(* encodinginfo decls *)

(* shared utility function for enums *)
let conv'enum (pos, name, optval) = match optval with
     Some v -> (pos, name, v)
   | None ->
        (* Encodingcheck (or Registercheck) should have filled this in *)
        Util.crash ("buildrep: no value for enumerator " ^ name)

(* field decl *)
let build'field pos name ty relinfo =
   let ty' = match ty with
        T.PLAINTYPE (_pos, name) -> Rep.PLAINTYPE name
      | T.WIDTHTYPE (_pos, name, width) -> Rep.WIDTHTYPE (name, width)
      | T.EXPRTYPE (pos, _ty') ->
           Pos.sayat pos "Field types must be evaluated, not expressions";
           Util.fail ();
           TB.notype  (* XXX should just process the rest of the type *)
   in
   let (relocatable, offset) = match relinfo with
        None -> (false, 0)
      | Some offset -> (true, offset)
   in
   addfield {
      Rep.name;
      Rep.definedat = pos;
      Rep.ty = ty';
      Rep.relocatable;
      Rep.offset;
   }

(* field decl with private enumeration *)
(* XXX: fix this to cutpaste less code *)
let build'enumfield pos name ty relinfo =
   let ty' = match ty with
        T.ENUMTYPE (pos, width, values) ->
           let name = getname ".E" in
           let e = {
              Rep.name;
              Rep.definedat = pos;
              Rep.width;
              Rep.seq = 0; (* assigned later *)
              Rep.syms = List.map conv'enum values;
              Rep.symtovalue = Types.StringMap.empty; (* built later *)
              Rep.valuetosym = Array.make 0 ""; (* built later *)
           } in
           addenum e;
           Rep.PLAINTYPE name
   in
   let (relocatable, offset) = match relinfo with
        None -> (false, 0)
      | Some offset -> (true, offset)
   in
   addfield {
      Rep.name;
      Rep.definedat = pos;
      Rep.ty = ty';
      Rep.relocatable;
      Rep.offset;
   }

(* form decl *)
let build'form pos fields block =

   (*
    * Give each anonymous field a name and add it to the field pool.
    * Note that anonymous fields are not allowed to be enums so we
    * can use conv'type for the type.
    *)
   let namefield fr = match fr with
        T.FIELDREF_ (pos, "_", Some ty, optval) ->
           let xname = getname ".Z" in
	   addfield {
	      Rep.name = xname;
	      Rep.definedat = pos;
	      Rep.ty = TB.build'type ty;
	      Rep.relocatable = false;
	      Rep.offset = 0;
	   };
           T.FIELDREF_ (pos, xname, None, optval)
      | T.FIELDREF_ (pos, "_", None, _) ->
           (* should be caught by Encodingcheck *)
           Pos.crashat pos "Anonymous field with no type"
      | _ -> fr
   in
   let fields = List.map namefield fields in

   (*
    * Extract initializations for anonymous (or non-anonymous) fields.
    * Stick them onto the front of the block.
    *)
   let getinit fr = match fr with
        T.FIELDREF_ (pos, fname, _, Some v) ->
           [T.ASSIGN (pos, T.SETVAR (pos, fname), T.NUMCONSTANT (pos, v))]
      | _ -> []
   in
   let initstmts = List.concat (List.map getinit fields) in
   let block = initstmts @ block in

   (*
    * Downstream the list of fields is just their names. We've offloaded
    * all the type and initialization info.
    *)
   let getfname fr = match fr with
      T.FIELDREF_ (_, name, _, _) -> name
   in
   let fields' = List.map getfname fields in

   (*
    * Produce the output form.
    *)
   let formname = getname ".F" in
   addform {
      Rep.name = formname;
      Rep.definedat = pos;
      Rep.fields = fields';
      Rep.types = []
   };

   (*
    * Now go through the block and produce the encodings and macros
    * defined in this form.
    *)
   let ctx = newformctx formname in
   List.iter (build'outerstmt ctx) block

(* subenum decl *)
let build'subenum pos name syms =
   let syms' = Types.stringset_of_list syms in
   addsubenum {
      Rep.name;
      Rep.definedat = pos;
      Rep.enumname = ""; (* filled in later *)
      Rep.values = syms';
   }

(* whole encodings.def file *)
let build'encs decls =
   let build d = match d with
        T.FIELD (pos, name, ty, relinfo) -> build'field pos name ty relinfo
      | T.ENUMFIELD (pos, name, ty, relinfo) -> build'enumfield pos name ty relinfo
      | T.FORM (pos, name, fnames) -> build'form pos name fnames
      | T.SUBENUM (pos, name, syms) -> build'subenum pos name syms
      | T.SUBENUMEXPR _ -> Util.crash "buildrep: leftover SUBENUMEXPR"
   in
   List.iter build decls

(**************************************************************)
(* base decls *)

let build'basedecl d = match d with
     B.ENUMTYPE (definedat, name, width, members) ->
	let e = {
	   Rep.name;
	   Rep.definedat;
	   Rep.width;
           Rep.seq = 0; (* assigned later *)
	   Rep.syms = List.map conv'enum members;
	   Rep.symtovalue = Types.StringMap.empty; (* built later *)
	   Rep.valuetosym = Array.make 0 ""; (* built later *)
	} in
	addenum e
      | B.WRAPTYPE _ ->
           (* these are converted to ENUMTYPE by basecheck *)
           Util.crash "buildrep: leftover WRAPTYPE"
      | B.COMPOUNDTYPE (definedat, name, members) ->
           let conv'member (pos, ty) = (pos, TB.build'type ty) in
           let members' = List.map conv'member members in
           let ct = { Rep.name; Rep.definedat; Rep.members=members'; } in
           addcompoundtype ct;
      | B.OPERANDTAG (definedat, name, ty) ->
           let basetype = TB.build'type ty in
	   let opt = {
	      Rep.name;
	      Rep.definedat;
	      Rep.basetype;
	   } in
	   addoperandtag opt
      | B.SHORTNAME _ -> ()


(* longname -> type *)
let type_by_longname = ref Types.StringMap.empty

let gettype_by_longname longname =
   try
      Types.StringMap.find longname !type_by_longname
   with Not_found ->
      Util.crash ("buildrep: gettype_by_longname: " ^
		  longname ^ ": not found")

let build'bylongname d = match d with
     B.OPERANDTAG (_pos, name, ty) ->
        type_by_longname :=
            Types.StringMap.add name (TB.build'type ty) !type_by_longname
   | _ -> ()


let build'basedecls decls = 
   List.iter build'basedecl decls;
   List.iter build'bylongname decls


(**************************************************************)
(* modifiers *)

let rec mconv'typename ty = match ty with
     M.INT n -> Rep.WIDTHTYPE ("int", n)
   | M.UINT n -> Rep.WIDTHTYPE ("uint", n)
   | M.EXPRTYPE ty' -> Rep.EXPRTYPE (mconv'typename ty')

let build'modifier { M.name; M.definedat; M.argtype; M.resulttype; } =
   let argtype = mconv'typename argtype in
   let resulttype = mconv'typename resulttype in
   addmodifier {
      Rep.name;
      Rep.definedat;
      Rep.argtype;
      Rep.resulttype;
   }

let build'mods decls =
   List.iter build'modifier decls


(**************************************************************)
(* insns *)

let build'insn { O.name; O.definedat; O.operandtags; O.multi;
		 O.encodinginfo; } =
   if multi then begin
      (* (note: repeated operand sets are used by some MI directives) *)
      Pos.sayat definedat "Repeated operand sets not supported (yet?)";
      Util.fail ()
   end;

   (* XXX is this sufficient or do we need e.g. _ -> __ and . -> _o? *)
   let fixchar c = match c with
        '.' -> '_'
      | ',' -> '_'
      | _ -> c
   in
   let fixstring s =
      String.map fixchar s
   in

   (*
    * If there is an explicit encoding specified, generate a macro.
    *)
   begin
   match encodinginfo with
        None -> ()
      | Some (encoding, encargs) ->
           (* the macro specargs (params really) are always [] *)
           let specargs = [] in
           (* the macro opargs are the types from the operand list *)
           let mkoparg (n, (pos, longname)) =
              let ty = gettype_by_longname longname in
	      (*
               * XXX this identifier currently has to be private because
               * macro arg names matching field names are presumed to
               * refer to those fields and shouldn't (should be only in
               * encodings) so when there's a field named op1 or op2
               * like sparc64 has, its type leaks in and bizarro things
               * happen.
               *)
              (pos, "_op" ^ string_of_int n, ty)
           in
           let opargs = List.map mkoparg (Util.number operandtags) in

           (* the guard expression for the expansion is "true" *)
           let guard = Rep.USEVAR (definedat, TB.notype, "true") in

           (* the block for the expansion is the call *)

           (* make expressions for the operand args *)
           let mkopcallarg (n, (pos, _longname)) =
              Rep.USEVAR (pos, TB.notype, "_op" ^ string_of_int n)
           in
           let opcallargs = List.map mkopcallarg (Util.number operandtags) in

           (* make the encoding.def args (identifiers) into expressions *)
           let mkarg (pos, arg) =
              Rep.USEVAR (pos, TB.notype, arg)
           in
           let encargs = List.map mkarg encargs in

           let call = Rep.USE (definedat, encoding, encargs, opcallargs, "") in
           let block = [call] in

           addmacro {
              Rep.name;
              Rep.mangledname = "";
              Rep.definedat;
              Rep.specargs;
              Rep.opargs;
              Rep.expansions = [(definedat, guard, block)];
           }
   end;

   (*
    * Now for the instruction entry point itself...
    *)

   (* Externally operands are referred to by the operand tag name. *)
   let operands_ext =
      List.map (fun (_pos, op) -> op) operandtags
   in

   (* And internally, they're referred to just by type. *)
   let operands_int =
      List.map (fun (_pos, op) -> gettype_by_longname op) operandtags
   in

   (*
    * This mangling has to match what genencoding does to call the
    * external names of the encoding entry points. It isn't used for
    * naming within the encoding logic itself; the mangling used there
    * is the "mangle" function in typeinf.ml.
    *)
   let mangledname_ext =
      fixstring name ^ "_" ^ String.concat "_" operands_ext
   in

   addinstruction {
	Rep.name;
	Rep.definedat;
        Rep.mangledname_ext;
        Rep.mangledname_int = "";
	Rep.operands_ext;
	Rep.operands_int;
	Rep.encoder = name;
	Rep.encoder_mangled = "??";
   }

let build'insns insninfo =
   let notdirective (insn: O.insn) =
      String.get insn.O.name 0 <> '.'
   in
   List.iter build'insn (List.filter notdirective insninfo)

(**************************************************************)
(* name extraction *)

module type Named = sig
   type t
   val whatis : string
   val getname : t -> string
   val getpos : t -> Pos.pos
end

module Buildmap(T : Named) = struct
   let build ts =
      let doadd m t =
         let name = T.getname t in
         try
            let t0 = Types.StringMap.find name m in
            let pos = T.getpos t in
            let pos0 = T.getpos t0 in
            Pos.sayat pos ("Duplicate " ^ T.whatis ^ " " ^ name);
            Pos.sayat pos0 ("Previous definition");
            Util.fail ();
            m
          with Not_found ->
            Types.StringMap.add name t m
      in
      List.fold_left doadd Types.StringMap.empty ts
end

module NamedEnum = struct
   type t = Rep.enum
   let whatis = "enum"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedCompoundType = struct
   type t = Rep.compoundtype
   let whatis = "compound type"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedOperandTag = struct
   type t = Rep.operandtag
   let whatis = "operand tag"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedModifier = struct
   type t = Rep.modifier
   let whatis = "modifier"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedField = struct
   type t = Rep.field
   let whatis = "field"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedForm = struct
   type t = Rep.form
   let whatis = "form"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module NamedSubenum = struct
   type t = Rep.subenum
   let whatis = "subenum"
   let getname (t : t) = t.Rep.name
   let getpos (t : t) = t.Rep.definedat
end

module BuildEnum = Buildmap(NamedEnum)
module BuildCompoundType = Buildmap(NamedCompoundType)
module BuildOperandTag = Buildmap(NamedOperandTag)
module BuildModifier = Buildmap(NamedModifier)
module BuildField = Buildmap(NamedField)
module BuildForm = Buildmap(NamedForm)
module BuildSubenum = Buildmap(NamedSubenum)

(**************************************************************)
(* toplevel *)

let build
		baseinfo
		miscinfo
		encodinginfo
		modinfo
		insninfo
          =
   (* miscinfo (misc.def) gives us the PC unit type *)
   let pcunitwidth = miscinfo.Misctree.pcunitwidth in
   let addresswidth = miscinfo.Misctree.addresswidth in
   let endian = match miscinfo.Misctree.endianness with
        Misctree.BIG -> Rep.BIG_ENDIAN
      | Misctree.LITTLE -> Rep.LITTLE_ENDIAN
   in
   let do_reginfo = miscinfo.Misctree.do_reginfo in

   (* encodinginfo (encodings.def) produces most of the material *)
   build'encs encodinginfo; 

   (* modinfo (modifiers.def) produces modifiers *)
   build'mods modinfo;

   (* baseinfo (base.def) gives register classes and operand types *)
   build'basedecls baseinfo;

   (* insninfo (opmatch.def) produces instructions *)
   build'insns insninfo;

   (* convert from lists to maps *)

   {
      Rep.pcunitwidth =  pcunitwidth;
      Rep.addresswidth = addresswidth;
      Rep.endian =       endian;
      Rep.do_reginfo =   do_reginfo;
      Rep.enums =        BuildEnum.build        !allenums;
      Rep.compoundtypes = BuildCompoundType.build !allcompoundtypes;
      Rep.operandtags =  BuildOperandTag.build  !alloperandtags;
      Rep.modifiers =    BuildModifier.build    !allmodifiers;
      Rep.fields =       BuildField.build       !allfields;
      Rep.forms =        BuildForm.build        !allforms;
      Rep.subenums =     BuildSubenum.build     !allsubenums;
      Rep.encodings =    List.rev !allencodings;
      Rep.macros =       List.rev !allmacros;
      Rep.instructions = List.rev !allinstructions;
   }
