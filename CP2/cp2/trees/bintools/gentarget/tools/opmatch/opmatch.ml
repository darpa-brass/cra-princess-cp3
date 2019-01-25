(*
 * Copyright (c) 2002, 2016, 2017
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
 * 
 * Script that generates targetmatch.{h,cc} from target's opmatch.def.
 * Usage:
 *    opmatch opmatch.def base.def targetmatch.h targetmatch.c
 *
 * Note: this file is structured more like a script than a real program
 * because that's how it started out.
 *)

open Opmatchtree
module T = Typetree
module B = Basetree


(**************************************************************)
(* Support code *)

let pad_right width str =
   let len = String.length str in
   if len < width then
      str ^ String.make (width - len) ' '
   else str

let pad_left width str =
   let len = String.length str in
   if len < width then
      String.make (width - len) ' ' ^ str
   else str

(**************************************************************)
(* Context *)

type matchctx = {
   (* typename -> width, for enumerated types *)
   width_bytypename: int Types.StringMap.t;

   (* longname -> shortname *)
   shortname_bylongname: string Types.StringMap.t;

   (* longname -> type *)
   type_bylongname: T.typename Types.StringMap.t;

   (* typenames that are compound types *)
   compound_typenames: (Pos.pos * T.typename) list Types.StringMap.t;
}

let ctx_shortname_of_longname ctx longname =
   try
      Types.StringMap.find longname ctx.shortname_bylongname
   with Not_found -> longname

let ctx_type_of_longname ctx longname =
   try
      Some (Types.StringMap.find longname ctx.type_bylongname)
   with Not_found -> None

let ctx_enumwidth_of_typename ctx tyname =
   try
      Some (Types.StringMap.find tyname ctx.width_bytypename)
   with Not_found -> None

let ctx_compoundmembers_of_typename ctx tyname =
   try
      Some (Types.StringMap.find tyname ctx.compound_typenames)
   with Not_found -> None

let ctx_iscompound_of_typename ctx tyname =
   match ctx_compoundmembers_of_typename ctx tyname with
        None -> false
      | Some _ -> true

let newctx basedecls =
   let width_bytypename =
      let doadd_rt map d =
         match d with
              B.ENUMTYPE (_definedat, name, width, _members) ->
                 Types.StringMap.add name width map
            | _ -> map
      in
      List.fold_left doadd_rt Types.StringMap.empty basedecls
   in
   let shortname_bylongname =
      let doadd map d =
         match d with
              B.SHORTNAME (_, shortname, longname) ->
                 Types.StringMap.add longname shortname map
            | _ -> map
      in
      List.fold_left doadd Types.StringMap.empty basedecls
   in
   let type_bylongname =
      let doadd map d =
         match d with
              B.OPERANDTAG (_pos, longname, ty) ->
                 Types.StringMap.add longname ty map
            | _ -> map
      in
      List.fold_left doadd Types.StringMap.empty basedecls
   in

   let compound_typenames =
      let doadd map d =
         match d with
              B.COMPOUNDTYPE (_, name, members) ->
                 Types.StringMap.add name members map
            | _ -> map
      in
      List.fold_left doadd Types.StringMap.empty basedecls
   in

   {
      width_bytypename;
      shortname_bylongname;
      type_bylongname;
      compound_typenames;
   }

(**************************************************************)
(* Augmented insn *)

type myinsn = {
   name: string;
   number: int;
   definedat: Pos.pos;

   ident: string;
   prefix: string;

             (* definedat number tag *)
   operands: (Pos.pos * int * string) list;
   multi: bool;

   mangled: string;
}

let build ctx (number, { name; definedat; operandtags; multi; }) =
   (*
    * some arches have instructions with "." in the name
    * some arches even have instructions with "," in the name
    *
    * XXX: Do we need to make this more elaborate to make sure that if we
    * XXX: have instructions named both foo.x and foo_x that it doesn't
    * XXX: choke?
    *)
   let fixchar c = match c with
        '.' -> '_'
      | ',' -> '_'
      | _ -> c
   in
   let isdirective = (String.get name 0 = '.') in
   let ident = String.map fixchar (
      if isdirective then
         String.sub name 1 (String.length name - 1)
      else name
   ) in
   let prefix = if isdirective then "directive" else "insn" in

   let mkoperand (i, (pos, tag)) = (pos, i, tag) in
   let operands = List.map mkoperand (Util.number operandtags) in

   if multi && operands = [] then begin
      Pos.sayat definedat ("Repeated operand list is empty");
      Util.fail ()
   end;

   let operandtags = List.map (fun (_pos, _i, op) -> op) operands in
   let shortnames = List.map (ctx_shortname_of_longname ctx) operandtags in

   (*
    * Generate a string that encodes the operand signature.
    *)
   let mangled =
      if isdirective then String.concat "_" shortnames
      else String.concat "_" operandtags
   in

   {
      name; number; definedat;
      ident; prefix;
      operands; multi;
      mangled;
   }

(**************************************************************)
(* operand matching *)

(*
 * Make a table that maps signatures (myinsn.mangled) to the
 * corresponding list of operand tags.
 *
 * By using a StringMap this implicitly folds duplicates.
 *
 * Note: insn.mangled is "" if the operand list is empty, and we
 * want to skip that case.
 *)
let makematchsigs insns =
   let doadd tbl insn =
      let names = List.map (fun (_pos, _n, name) -> name) insn.operands in
      if insn.mangled <> "" then
         Types.StringMap.add insn.mangled names tbl
      else
         tbl
   in
   List.fold_left doadd Types.StringMap.empty insns

(*
 * Emit the matching function array for a signature.
 * (we use .mangled for the signature since .signature has spaces in it)
 * (of course, that value is not actually used any more so it should change)
 * (XXX)
 *)
let domatchlist cfile mangled names =
   output_string cfile ("static const opmatchfn matches_" ^ mangled);
   output_string cfile ("[" ^ string_of_int (List.length names) ^ "]");
   output_string cfile (" = {\n");
   List.iter (fun n -> output_string cfile ("   check_" ^ n ^ ",\n")) names;
   output_string cfile ("};\n\n")

(*
 * Emit all the matching function arrays.
 *)
let domatchlists cfile insns =
   let tbl = makematchsigs insns in
   Types.StringMap.iter (domatchlist cfile) tbl

(*
 * Check if an operand matches an operand tag.
 *)
let domatch' _ctx cfile otname _ty =
   output_string cfile ("static UNUSED bool check_" ^ otname);
   output_string cfile ("(struct operand *oper) {\n");
   output_string cfile ("   return oper->is_" ^ otname ^ ";\n");
   output_string cfile ("}\n")

let domatch ctx cfile d =
   match d with
        B.OPERANDTAG (_pos, name, ty) ->
           domatch' ctx cfile name ty
      | _ -> ()

(**************************************************************)
(* operand tags *)

(*
 * These functions encode the C manifestation of operand values as
 * passed from the opcode dispatcher to the encoding procedures.
 *)

let declare_operand ctx hfile pos op ix =
   match ctx_type_of_longname ctx op with
        None ->
           Pos.sayat pos ("Invalid operand tag " ^ op ^ " in signature");
           Util.fail ()
      | Some ty ->
           let cty = match ty with
	   (* XXX this is still not what we want in the long term *)
		T.PLAINTYPE (_pos, "string") -> "const char *"
	      | T.PLAINTYPE (_pos, name) -> begin
		   match ctx_enumwidth_of_typename ctx name with
			Some n -> Typerep.uinttype n
		      | None -> match ctx_iscompound_of_typename ctx name with
			     true -> "struct compound_" ^ name ^ " *"
			   | false -> "struct expr *"
		end
	      | T.WIDTHTYPE (_pos, "int", w) -> Typerep.inttype w
	      | T.WIDTHTYPE (_pos, "uint", w) -> Typerep.uinttype w
	      | T.WIDTHTYPE (pos, name, _w) ->
		   Pos.crashat pos ("opmatch: declare_operand: bad widthtype "^
					   name)
	      | T.EXPRTYPE (_pos, _t) -> "struct expr *"
           in
           let decl = cty ^ " val" ^ string_of_int ix in
           output_string hfile decl

let extract_operand_value ctx cfile pos op oper =
   match ctx_type_of_longname ctx op with
        None ->
           Pos.sayat pos ("Invalid operand tag " ^ op ^ " in signature");
           Util.fail ()
      | Some ty ->
           let ordinary = oper ^ "->val_" ^ op in
           let e = match ty with
	        T.PLAINTYPE (_pos, name) -> begin
		   match ctx_iscompound_of_typename ctx name with
		        false -> ordinary
		      | true -> 
                           (*
                            * XXX: should pass the unpacked arguments of
                            * the compound type out of the operand; but
                            * can't do that yet; they aren't there and
                            * also the call won't work.
                            *)
                           "&" ^ ordinary
		end
              | _ -> ordinary
           in
           output_string cfile e

(**************************************************************)
(* output *)

(*
 * Write header file prologue.
 *)
let initheader ctx hfile =
   output_string hfile "/* Automatically generated; do not edit */\n";

   output_string hfile "#include \"targetdefs.h\"\n";
   output_string hfile "struct label; /* from label.h */\n";
   let one_struct name _members =
      output_string hfile ("struct compound_" ^ name ^ ";\n")
   in
   Types.StringMap.iter one_struct ctx.compound_typenames

(*
 * Write source file prologue.
 *)
let initsource cfile =
   output_string cfile "/* Automatically generated; do not edit */\n";

   output_string cfile "#include <stdbool.h>\n";
   output_string cfile "#include <stdint.h>\n";
   output_string cfile "#include <stdlib.h>\n";
   output_string cfile "#include <assert.h>\n";
   output_string cfile "#include \"common.h\"\n\n";
   output_string cfile "#include \"expr.h\"\n";
   output_string cfile "#include \"backend.h\"\n"; (* current loc of operandarray (XXX) *)
   output_string cfile "#include \"targetoper.h\"\n";
   output_string cfile "#include \"match.h\"\n";
   output_string cfile "#include \"targetmatch.h\"\n";
   output_string cfile "\n\n"

(*
 * Emit encoding function declaration into header.
 *)
let dodecl ctx hfile {
		definedat;
		ident; prefix;
		operands;
		mangled;
           } =

   output_string hfile "void ";
   output_string hfile (prefix ^ "_" ^ ident ^ "_" ^ mangled);
   output_string hfile "(int line";
   let outputone (_pos, i, op) =
      output_string hfile ", ";
      declare_operand ctx hfile definedat op (i+1)
   in
   List.iter outputone operands;
   output_string hfile ");\n"

(*
 * Emit call thunk into source file.
 *)
let dothunk ctx cfile {
		number; definedat;
		ident; prefix;
		operands; multi;
		mangled;
           } =

   let out s =
      output_string cfile s
   in

   let docall ind adj =
      out ind;
      out (prefix ^ "_" ^ ident ^ "_" ^ mangled);
      out "(line";
      let outone (_pos, i, op) =
	 out ", ";
         let str = "operandarray_get(ops, " ^ adj ^ string_of_int i ^ ")" in
	 extract_operand_value ctx cfile definedat op str
      in
      List.iter outone operands;
      out ");\n"
   in

   out ("static void call_" ^ string_of_int number);
   out "(int line, struct operandarray *ops) {\n";

   let noperands = List.length operands in
   if multi then begin
      out "   const unsigned n=";
      out        (string_of_int noperands);
      out        ";\n";
      out "   unsigned i, num;\n";
      out "   num = operandarray_num(ops);\n";
      (* XXX it should either use num/n or i+=n but not both... *)
      out "   for (i=0; i<num/n; i+=n) {\n";
      docall     "      " "i+";
      out "   }\n"
   end else begin
      if noperands = 0 then begin
	 out "   (void)ops;\n"
      end;
      docall "   " "";
   end;
   out "}\n\n"

(*
 * Emit a signature table row.
 *)
let dosigrow cfile {
		(*name;*) number; definedat;
		operands; multi;
		(*signature;*) mangled;
           } =
   let out s =
      output_string cfile s
   in
   let line = string_of_int definedat.Pos.startline in

   let noperands = List.length operands in

   (*let signaturetmp = "\"" ^ signature ^ "\"," in*)

   let matchtbl = if mangled <> "" then "matches_" ^ mangled else "NULL" in
   let matchtbl = matchtbl ^ ", " in

   out "   { ";
   (*out (pad_right 6 signaturetmp);*)
   out (pad_right 15 matchtbl);
   out " ";
   out (string_of_int noperands);
   out ", ";
   out (string_of_int (if multi then 1 else 0));
   out (", call_" ^ string_of_int number);
   out " }";
   out (" /* line " ^ pad_left 3 line ^ " */,\n")

(*
 * Emit a signature table for a particular opcode name.
 *)
let dosigtable cfile name indexnum insns =
   let tblname = "sigtbl" ^ string_of_int indexnum in
   let arrayname = tblname ^ "[" ^ string_of_int (List.length insns) ^ "]" in

   output_string cfile ("/* " ^ name ^ " */\n");
   output_string cfile "static const struct insnsig ";
   output_string cfile (arrayname ^ " = {\n");
   List.iter (dosigrow cfile) insns;
   output_string cfile "};\n\n"


(*
 * Emit entry for main opcode table.
 *)
let dotablerow cfile name indexnum insns =
   let out s =
      output_string cfile s
   in

   let nametmp = "\"" ^ name ^ "\"," in

   out "   { ";
   out (pad_right 16 nametmp);
   out " ";
   out ("sigtbl" ^ string_of_int indexnum);
   out ", ";
   out (string_of_int (List.length insns));
   out " },\n"

(*
 * Emit the operand matching table.
 *)
let writetable cfile insns =

   (*
    * Collect all the operand lists for each opcode name.
    *
    * Note that the result list accumulates in reverse order, and
    * needs to be flipped back in order to preserve the input order in
    * opmatch.def.
    *)
   let addone tbl (insn: myinsn) =
      let prev =
         try
            Types.StringMap.find insn.name tbl
         with Not_found -> []
      in
      Types.StringMap.add insn.name (insn :: prev) tbl
   in
   let tbl = List.fold_left addone Types.StringMap.empty insns in

   (*
    * Get all the unique instruction names
    * (grr, why doesn't Map have a keys operation?)
    *)
   let keys = List.map (fun (k, _) -> k) (Types.StringMap.bindings tbl) in

   (*
    * Sort the list so we can index it with bsearch; then number them
    *)
   let keys = Util.number (List.sort Pervasives.compare keys) in

   (*
    * Write out a sig table for each one
    *)
   let dosig (i, k) =
      dosigtable cfile k i (List.rev (Types.StringMap.find k tbl))
   in
   List.iter dosig keys;

   (*
    * Write out the instruction table
    *)

   output_string cfile "const struct insnmatch opcodes[] = {\n";
   let dorow (i, k) =
      dotablerow cfile k i (List.rev (Types.StringMap.find k tbl))
   in
   List.iter dorow keys;

   output_string cfile "};\n\n";
   output_string cfile "const unsigned numopcodes = ";
   output_string cfile "sizeof(opcodes)/sizeof(opcodes[0]);\n\n"

(**************************************************************)
(* validation *)

(*
 * Check that every operand tag used by the instruction exists.
 * This takes the raw instruction, not the augmented one.
 *)
let validate'insn ctx (insn: insn) =
   let validate'one (n, (pos, tagname)) =
      match ctx_type_of_longname ctx tagname with
           Some _ -> ()
         | None ->
              Pos.sayat pos ("No such operand tag " ^ tagname ^
        	             " for operand " ^ string_of_int n);
              Util.fail ()
   in
   List.iter validate'one (Util.number insn.operandtags)

(**************************************************************)
(* main *)

let opmatch matchname basename hname cname =

   (* Read the spec (opmatch.def) *)
   let rawinsns = Opmatchlex.read matchname in
   Util.checkfail ();

   (* Read the base declarations *)
   let basedecls = Baselex.read basename in
   Util.checkfail();

   let ctx = newctx basedecls in

   (* Validate the insns against the operand tags and their types. *)
   List.iter (validate'insn ctx) rawinsns;

   (* Build the augmented instruction list. *)
   let insns = List.map (build ctx) (Util.number rawinsns) in

   Util.checkfail ();

   (* Open the output files *)
   let hfile = open_out hname in
   let cfile = open_out cname in

   (* away we go *)
   initheader ctx hfile;
   initsource cfile;
   List.iter (domatch ctx cfile) basedecls;
   output_string cfile "\n";
   List.iter (dodecl ctx hfile) insns;
   List.iter (dothunk ctx cfile) insns;
   domatchlists cfile insns;
   writetable cfile insns;

   (* done *)
   close_out cfile;
   close_out hfile;
   Util.checkfail ()

let main argv =
   match argv with
        [_argv0; matchname; basename; hname; cname] ->
           opmatch matchname basename hname cname
      | _ ->
           Util.say ("opmatch: usage: opmatch " ^
                     "opmatch.def base.def " ^
                     "match.h match.c\n");
           Util.die ()
let _ = main (Array.to_list Sys.argv)
