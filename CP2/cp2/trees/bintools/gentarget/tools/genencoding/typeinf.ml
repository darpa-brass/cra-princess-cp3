(*
 * Copyright (c) 2016
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

module TI = Exprtypeinf

open Rep

(**************************************************************)
(* scopes that nest *)

type 'a scope = {
   bindings: 'a Types.StringMap.t;
   parent: 'a scope option;
}

let newscope parent = {
   bindings = Types.StringMap.empty;
   parent = parent;
}

let scope_add name x { bindings; parent; } =
   let bindings' = Types.StringMap.add name x bindings in
   { bindings=bindings'; parent; }

let rec scope_get name { bindings; parent; } =
   try
      Some (Types.StringMap.find name bindings)
   with Not_found ->
      match parent with
           None -> None
         | Some scope -> scope_get name scope

let scope_existshere name { bindings; _ } =
   Types.StringMap.mem name bindings

(**************************************************************)
(* scopes that don't nest (wrapper around StringMap) *)

type 'a flatscope = {
   flatbindings: 'a Types.StringMap.t;
}

let newflatscope () = {
   flatbindings = Types.StringMap.empty;
}

let flatscope_add name x { flatbindings; } =
   let flatbindings' = Types.StringMap.add name x flatbindings in
   { flatbindings=flatbindings'; }

let flatscope_get name { flatbindings; } =
   try
      Some (Types.StringMap.find name flatbindings)
   with Not_found -> None

let flatscope_exists name { flatbindings; } =
   Types.StringMap.mem name flatbindings

let flatscope_map f { flatbindings; } =
   let flatbindings = Types.StringMap.map f flatbindings in
   { flatbindings; }

(**************************************************************)
(* context *)

(*
 * There are four real namespaces:
 *    - types
 *    - variables (includes field names and enum constants)
 *    - encodings/macros/instructions
 *    - MD "modifier" names
 * plus one more made up by buildrep:
 *    - forms
 * (this should probably be numberings, not namespaces)
 *
 * Enumerations used to have their own namespace made up by buildrep
 * too, but now they just have unique names (beginning with .E) in the
 * type namespace.
 *)

type signature = Pos.pos * string * typename list * typename list

type context = {
   tictx: TI.context;

   spec: spec;

   (* types *)

   (* the known PLAINTYPEs and WIDTHTYPEs [type namespace] *)
   plaintypes: Types.StringSet.t ref;
   argtypes: Types.StringSet.t ref;
   (* the known ENUMTYPEs [type namespace] (maps to the sequence number) *)
   enumtypes: int Types.StringMap.t ref;
   nextenumseq: int ref;
   (* compound types [type namespace] *)
   compoundtypes: (Pos.pos * typename) list flatscope ref;

   (* operand tags *)

   (* operand tags: name to basetype *)
   optags: (Pos.pos * typename) flatscope ref;
   (* the short names of operand tags; both mapping directions *)

   (* forms and fields *)

   (* the types of all fields *)
   fields: typename flatscope ref;
   (* the fields in all forms, by (made-up) name *)
   forms: string list flatscope ref;

   (* variables *)

   (* the types of all variables [variable namespace] - nesting scope *)
   vars: typename scope ref;

   (* encodings/macros/instructions *)

   (* the argtypes and optypes for all encodings/macros/instructions *)
   insns: signature list flatscope ref;

   (* modifiers *)
   (* use spec.modifiers *)
}

let newctx spec = {
   tictx = TI.newctx ();
   spec;

   plaintypes = ref builtin_plaintypes;
   argtypes = ref builtin_argtypes;
   enumtypes = ref Types.StringMap.empty;
   nextenumseq = ref 0;
   compoundtypes = ref (newflatscope ());

   optags = ref (newflatscope ());

   fields = ref (newflatscope ());
   forms = ref (newflatscope ());

   vars = ref (newscope None);

   insns = ref (newflatscope ());
}

(*
 * Context accessors: types
 *)

let ctx_isplaintype (ctx : context) name =
   Types.StringSet.mem name !(ctx.plaintypes)

let ctx_addplaintype (ctx : context) name =
   if Types.StringSet.mem name !(ctx.plaintypes) then
      (* should have been caught by basecheck *)
      Util.crash ("typeinf: PLAINTYPE " ^ name ^ " already exists")
   else
      ctx.plaintypes := Types.StringSet.add name !(ctx.plaintypes)

let ctx_isargtype (ctx : context) name =
   Types.StringSet.mem name !(ctx.argtypes)

(* ctx_addargtype is not needed *)

let ctx_isenumtype (ctx : context) name =
   Types.StringMap.mem name !(ctx.enumtypes)

let ctx_addenumtype (ctx : context) name seq =
   if Types.StringMap.mem name !(ctx.enumtypes) then
      (* must have been emitted wrong by Buildrep *)
      Util.crash ("typeinf: enum " ^ name ^ " already exists")
   else
      ctx.enumtypes := Types.StringMap.add name seq !(ctx.enumtypes)

let ctx_addcompoundtype (ctx : context) name args =
   if flatscope_exists name !(ctx.compoundtypes) then
      (* should have been caught by basecheck *)
      Util.crash ("typeinf: compound type " ^ name ^ " already exists")
   else
      ctx.compoundtypes := flatscope_add name args !(ctx.compoundtypes)

let ctx_isoptag (ctx : context) name =
   flatscope_exists name !(ctx.optags)

let ctx_addoptag (ctx : context) name otherty =
   if flatscope_exists name !(ctx.optags) then
      (* checked before adding *)
      Util.crash ("typeinf: operand tag " ^ name ^ " already exists")
   else
      ctx.optags := flatscope_add name otherty !(ctx.optags)

let ctx_isanytype ctx name =
   ctx_isplaintype ctx name ||
     ctx_isargtype ctx name

(*
 * Context accessors: fields and forms
 *)

let ctx_getfield (ctx : context) name =
   flatscope_get name !(ctx.fields)

let ctx_addfield (ctx : context) name ty =
   if name = "_" then ()
   else if flatscope_exists name !(ctx.fields) then
      (* should have been caught by Encodingcheck *)
      Util.crash ("typeinf: field " ^ name ^ " already exists")
   else
      ctx.fields := flatscope_add name ty !(ctx.fields)

let ctx_getform (ctx : context) name =
   flatscope_get name !(ctx.forms)

let ctx_addform (ctx : context) name fields =
   if name = "_" then ()
   else if flatscope_exists name !(ctx.forms) then
      (* must have been emitted wrong by Buildrep *)
      Util.crash ("typeinf: form " ^ name ^ " already exists")
   else
      ctx.forms := flatscope_add name fields !(ctx.forms)

(*
 * Context accessors: variables
 *)

let ctx_getvar ctx name =
   scope_get name !(ctx.vars)

let ctx_addvar ctx name ty =
   if name = "_" then ()
   else if scope_existshere name !(ctx.vars) then
      (* should have been caught by Encodingcheck *)
      Util.crash ("typeinf: var " ^ name ^ " already exists")
   else
      ctx.vars := scope_add name ty !(ctx.vars)

let ctx_pushscope ctx =
   ctx.vars := newscope (Some !(ctx.vars))

let ctx_popscope ctx =
   match (!(ctx.vars)).parent with
        None -> Util.crash "typeinf: unbalanced popscope"
      | Some scope -> ctx.vars := scope

(*
 * Context accessors: encodings/macros/instructions
 *
 * Note that because these are polymorphic over argument and operand
 * types, each entry is a list and we only have duplicates if all the
 * types are the same. We do *not* check for duplicates -- that is
 * done downstream.
 *)

let ctx_getinsn (ctx : context) name =
   flatscope_get name !(ctx.insns)

let ctx_addinsn (ctx : context) name entry =
   let prior = match flatscope_get name !(ctx.insns) with
        None -> []
      | Some stuff -> stuff
   in
   ctx.insns := flatscope_add name (entry :: prior) !(ctx.insns)

(**************************************************************)
(* signatures of encodings/macros/instructions *)

(*
 * The full function name for an instruction is "mangled": it has the
 * types of operands in it. This allows having multiple variants of an
 * instruction with different signatures to coexist in the output code.
 *
 * Note: this mangling is used only for internal names and internal
 * signatures (within the encodings output) -- the externally visible
 * mangled names of external encoding entry points are generated using
 * different logic, and in general different names for the types, in
 * buildrep.ml. The names generated by this mangling aren't exposed
 * outside the file.
 *
 * Thus, it doesn't have to match anything anyone else does anywhere.
 *)
let mangle ctx (pos, name, _args, operands) =
   let bailwith tyname =
      Pos.sayat pos ("typeinf: mangle: invalid type for operand: " ^ tyname);
      Util.fail ();
      "xx"
   in
   let rec getshortname optype =
      match optype with
           PLAINTYPE "bool" ->
              "b0"
         | PLAINTYPE name -> begin
              try
                 let seq = Types.StringMap.find name !(ctx.enumtypes) in
                 "e" ^ string_of_int seq
              with Not_found ->
                 name
           end
         | WIDTHTYPE ("uint", width) ->
              (* XXX *)
              "u" ^ string_of_int width
         | WIDTHTYPE ("int", width) ->
              (* XXX *)
              "i" ^ string_of_int width
         | WIDTHTYPE (name, width) ->
              bailwith (name ^ "(" ^ string_of_int width ^ ")")
         | EXPRTYPE optype' ->
              "x" ^ getshortname optype'
         | LISTTYPE _ ->
              bailwith ("list type")
         | TMPTYPE _ ->
              bailwith ("scratch type")
   in
   (* remove characters that can't be in C identifiers *)
   (* XXX do we need to distinguish upstream foo_bar and foo.bar? *)
   (* XXX why do we need this here when it's already in buildrep? *)
   let fixchar c = match c with
        '.' -> '_'
      | ',' -> '_'
      | _ -> c
   in
   let fixstring s =
      String.map fixchar s
   in
   (fixstring name) ^ "_" ^ String.concat "" (List.map getshortname operands)

(**************************************************************)
(* hooks to type inference machinery in exprtypeinf *)

let unify' ctx pos ty ty2 =
   TI.unify' ctx.tictx pos ty ty2

let improvetype ctx ty =
   TI.improvetype ctx.tictx ty

let inf'expr ctx e =
   TI.inf'expr ctx.tictx e

let res'type ctx t =
   TI.res'type ctx.tictx t

let res'expr ctx e =
   TI.res'expr ctx.tictx e


(**************************************************************)
(* types *)

(*
 * This is responsible for building the symtovalue and valuetosym
 * mappings.
 *)

let inf'enum ctx { name; definedat; width; syms; _ } =
   (* symtovalue *)
   let addsym tbl (_pos, name, value) =
      if name <> "_" then Types.StringMap.add name value tbl
      else tbl
   in
   let symtovalue = List.fold_left addsym Types.StringMap.empty syms in

   (* valuetosym *)
   let largest = List.fold_left (fun x (_, _, value) -> max value x) 0 syms in
   let valuetosym = Array.make (largest + 1) "" in
   let setsym (_pos, name, value) = Array.set valuetosym value name in
   List.iter setsym syms;

   let seq = !(ctx.nextenumseq) in
   ctx.nextenumseq := seq + 1;

   (* remember the enum name and sequence number *)
   ctx_addenumtype ctx name seq;

   (* add the names to the typing context as variables *)
   let addenumerator (_pos, sym, _value) =
      ctx_addvar ctx sym (PLAINTYPE name)
   in
   List.iter addenumerator syms;

   {
      name;
      definedat;
      width;
      seq;
      syms;
      symtovalue;
      valuetosym;
   }

let inf'compoundtype ctx { name; definedat; members; } =
   if ctx_isanytype ctx name then begin
      Pos.sayat definedat ("Duplicate type name " ^ name);
      Util.fail ();
   end else begin
      ctx_addplaintype ctx name;
      ctx_addcompoundtype ctx name members
   end;
   { name; definedat; members; }

let inf'operandtag ctx { name; definedat; basetype; } =
   (* add the name to the typing context *)
   if ctx_isoptag ctx name then begin
      Pos.sayat definedat ("Duplicate operand tag " ^ name);
      Util.fail ();
   end else begin
      (* XXX check if basetype is legal here? *)
      ctx_addoptag ctx name (definedat, basetype)
   end;
   { name; definedat; basetype; }

let inf'subenum ctx { name; definedat; values; _ } =
   (*
    * Encodingcheck has already validated that all the values are from
    * one enum, and that it's not empty. So just look up the value.
    *)
   let enumname = match ctx_getvar ctx (Types.StringSet.choose values) with
        Some (PLAINTYPE name) -> name
      | _ -> Pos.crashat definedat ("typeinf: broken subenum " ^ name)
   in
   let ty = LISTTYPE (PLAINTYPE enumname) in
   ctx_addvar ctx name ty;
   { name; definedat; enumname; values; }

(**************************************************************)
(* modifiers *)

let inf'modifier _ctx (m: modifier) =
   (* XXX should probably check m.name for uniqueness *)
   m

(**************************************************************)
(* fields and forms *)

let inf'field ctx (f : field) =
   let ty = f.ty in
   (* XXX check here if ty is a legal type for a field *)
   (* also if it's an enum check if it's in ctx.enumtypes *)
   ctx_addfield ctx f.name ty;
   ctx_addvar ctx f.name ty;
   { f with ty; }

let inf'form ctx { name; definedat; fields; _ } =
   let dofield f =
      match ctx_getfield ctx f with
           Some ty -> ty
         | None ->
              (* should have been caught by Encodingcheck *)
              Pos.crashat definedat ("typeinf: no such field " ^ name)
   in
   ctx_addform ctx name fields;
   let types = List.map dofield fields in

   {
      name;
      definedat;
      fields;
      types;
   }

(**************************************************************)
(* statements *)

let rec inf'pat ctx ty pat = match pat with
     SETVAR (pos, name) -> begin
        match ctx_getvar ctx name with
             Some ty2 -> ignore (unify' ctx pos ty ty2)
           | None -> ctx_addvar ctx name ty
     end
   | UNPACK (pos, "modimm", [arg0; arg1]) ->
        (* XXX this should not exist *)
        ignore (unify' ctx pos ty (WIDTHTYPE ("uint", 32)));
	inf'pat ctx (WIDTHTYPE ("uint", 4)) arg0;
	inf'pat ctx (WIDTHTYPE ("uint", 8)) arg1
   | UNPACK (pos, ctor, args) ->
        ignore (unify' ctx pos ty (PLAINTYPE ctor));
        match flatscope_get ctor !(ctx.compoundtypes) with
             None ->
                Pos.sayat pos ("Cannot unpack non-compound type " ^ ctor);
                Util.fail ()
           | Some argtys ->
	       let numargtys = List.length argtys in
	       let numargs = List.length args in
	       if numargtys <> numargs then begin
		  Pos.sayat pos ("Wrong number of elements for " ^ ctor ^
                                 "; " ^ "expected " ^ string_of_int numargtys ^
				 " but found " ^ string_of_int numargs);
		  Util.fail ()
	       end;
	       let pairs = Util.zip' argtys args in
	       let dopair ((_pos2, argty), arg) =
		  inf'pat ctx argty arg
	       in
	       List.iter dopair pairs

let inf'assignment ctx (pos, pat, e) =
   let e' = inf'expr ctx e in
   let t' = exprtype e' in
   inf'pat ctx t' pat;
   (pos, pat, e')

let rec inf'statement ctx s = match s with
     ASSIGN (pos, pat, e) ->
       let (pos', pat', e') = inf'assignment ctx (pos, pat, e) in
       ASSIGN (pos', pat', e')
   | USE (pos, name, es, ops, unset_resolvedname) ->
       let es' = List.map (inf'expr ctx) es in
       let ops' = List.map (inf'expr ctx) ops in
       USE (pos, name, es', ops', unset_resolvedname)
   | IF (pos, c, t, f) ->
       let c' = inf'expr ctx c in
       ignore (unify' ctx pos booltype (exprtype c'));
       let t' = List.map (inf'statement ctx) t in
       let f' = List.map (inf'statement ctx) f in
       IF (pos, c', t', f')
   | EMIT (pos, _e) ->
(* the following is correct, but unneeded *)
(*
       let pcunittype = WIDTHTYPE ("uint", ctx.spec.pcunitwidth) in
       let e' = inf'expr ctx e in
       ignore (unify' ctx pos pcunittype (exprtype c'));
*)
       (* EMIT is only added downstream *)
       Pos.crashat pos "typeinf: invalid EMIT"
   | HOOK (pos, _name, _args) ->
       (* HOOK is only added downstream *)
       Pos.crashat pos "typeinf: invalid HOOK"
   | WARN (pos, text) ->
       (* nothing to do *)
       WARN (pos, text)

(**************************************************************)
(* encodings/macros/instructions *)

(*
 * encodings
 *)

let inf'alternative ctx (pos, e, stmts) =
   let e' = inf'expr ctx e in
   ignore (unify' ctx pos booltype (exprtype e'));
   let stmts' = List.map (inf'statement ctx) stmts in
   (pos, e', stmts')

let inf'arg ctx (pos, name, ty_already) =
   let ty = match ctx_getvar ctx name with
        Some ty -> ty
      | None ->
           let ty = TI.ctx_newtmptype ctx.tictx pos in
           ctx_addvar ctx name ty;
           ty
   in
   (* if it's not PLAINTYPE _, it was a type annotation *)
   if ty_already <> PLAINTYPE "_" then begin
      ignore (unify' ctx pos ty_already ty)
   end;
   (pos, name, ty)

let inf'encoding ctx { name; mangledname; definedat; specargs; opargs;
		       formname; alternatives } =
   ctx_pushscope ctx;
   let specargs' = List.map (inf'arg ctx) specargs in
   let opargs' = List.map (inf'arg ctx) opargs in
   let alternatives' = List.map (inf'alternative ctx) alternatives in
   ctx_popscope ctx;

   let gettype (_pos, _name, ty) = ty in
   let specargtypes = List.map gettype specargs' in
   let opargtypes = List.map gettype opargs' in
   let signature = (definedat, name, specargtypes, opargtypes) in
   ctx_addinsn ctx name signature;

   {
      name;
      mangledname;
      definedat;
      specargs = specargs';
      opargs = opargs';
      formname;
      alternatives = alternatives';
   }

(*
 * macros
 *)

let inf'expansion ctx (pos, e, stmts) =
   let e' = inf'expr ctx e in
   ignore (unify' ctx pos booltype (exprtype e'));
   let stmts' = List.map (inf'statement ctx) stmts in
   (pos, e', stmts')

let inf'macro ctx { name; mangledname; definedat;
                    specargs; opargs;
		    expansions; } =
   ctx_pushscope ctx;
   let specargs' = List.map (inf'arg ctx) specargs in
   let opargs' = List.map (inf'arg ctx) opargs in
   let expansions' = List.map (inf'expansion ctx) expansions in
   ctx_popscope ctx;

   let gettype (_pos, _name, ty) = ty in
   let specargtypes = List.map gettype specargs' in
   let opargtypes = List.map gettype opargs' in
   let signature = (definedat, name, specargtypes, opargtypes) in
   ctx_addinsn ctx name signature;

   {
      name;
      mangledname;
      definedat;
      specargs = specargs';
      opargs = opargs';
      expansions = expansions';
   }

(*
 * instruction
 *)

let inf'instruction _ctx { name; definedat;
                          operands_ext; operands_int;
                          mangledname_ext; mangledname_int;
			  encoder; encoder_mangled; } =

(*
   let signature = (definedat, name, [], operands_int) in
   ctx_addinsn ctx name signature;
*)
   {
      name;
      definedat;
      operands_ext;
      operands_int;
      mangledname_ext;
      mangledname_int;
      encoder;
      encoder_mangled;
   }

(**************************************************************)
(* spec *)

let inf'spec ctx spec =
   let map = Types.StringMap.map in

   let {
        pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
   } = spec in

   let enums =        map (inf'enum ctx)        enums           in
   let compoundtypes = map (inf'compoundtype ctx) compoundtypes    in
   let operandtags =  map (inf'operandtag ctx)  operandtags     in
   let modifiers =    map (inf'modifier ctx)    modifiers       in
   let fields =       map (inf'field ctx)       fields          in
   let forms =        map (inf'form ctx)        forms           in
   let subenums =     map (inf'subenum ctx)     subenums        in
   let encodings =    List.map (inf'encoding ctx) encodings     in
   let macros =       List.map (inf'macro ctx)  macros          in
   let instructions = List.map (inf'instruction ctx) instructions in

   {
	pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
   }

(**************************************************************)
(* pass 2 *)

(*
 * Second pass on macros
 *
 * This must be done after all encodings and macros are processed the
 * first time so all the argument lists have been typeinf'd first. We
 * don't require encodings to be defined before used; because they're
 * syntactically tied to their forms, that governs where they appear
 * in encoding.def, so it doesn't always make sense for macros that
 * use them to come after them.
 *)

let printinsn (_pos, name, defargs, defops) =
   let defargs' = String.concat ", " (List.map dump'typename defargs) in
   let defops' = String.concat ", " (List.map dump'typename defops) in
   let defargs'' = if defargs' = "" then "" else "(" ^ defargs' ^ ")" in
   let defops'' = if defops' = "" then "" else " " ^ defops' in
   name ^ defargs'' ^ defops''

let sayinsn (pos, name, defargs, defops) =
   Pos.sayat pos ("   " ^ printinsn (pos, name, defargs, defops))

let nomatchinsns callinsn insns =
   let (pos, name, _, _) = callinsn in
   Pos.sayat pos ("No match for encoding or macro " ^ name);
   Pos.sayat pos ("Signature is: " ^ printinsn callinsn);
   Pos.sayat pos ("Candidates are:");
   List.iter sayinsn insns;
   Util.fail ()

let ambigmatchinsns callinsn insns =
   let (pos, name, _, _) = callinsn in
   Pos.sayat pos ("Ambiguous match for encoding or macro " ^ name);
   Pos.sayat pos ("Signature is: " ^ printinsn callinsn);
   Pos.sayat pos ("Matching candidates are:");
   List.iter sayinsn insns;
   Util.fail ()

(*
 * Unify a USE caller/callee.
 * The argument lengths have been checked to match.
 *)
let unifyinsn ctx callinsn insn =
   let (pos, _, callargs, callops) = callinsn in
   let (_, _, defargs, defops) = insn in
   let dopair (ty, def) =
      ignore (unify' ctx pos ty def)
   in
   List.iter dopair (Util.zip (callargs @ callops) (defargs @ defops))

(*
 * Pick a possibly matching USE caller/callee.
 * The argument lengths have been checked to match.
 *)
let matchinsns ctx callinsn insns =
   let matchonetype (ty, def) =
      if ty = def then true
      else match ty, def with
           TMPTYPE _, _ -> true
         | _, TMPTYPE _ -> true
         | _, _ -> false
   in
   let matchalltypes (_, _, callargs, callops) (_, _, defargs, defops) =
      List.map matchonetype (Util.zip (callargs @ callops) (defargs @ defops))
   in
   let matchoneinsn definsn =
      List.for_all (fun x -> x) (matchalltypes callinsn definsn)
   in
   let oks = List.map matchoneinsn insns in
   (*
    * If there is exactly one true in oks, take it and feed it to
    * unifyinsn. If there are none, use nomatchinsns; otherwise,
    * ambigmatchinsns.
    *
    * However, uniq the list first (ignoring position) because we also
    * haven't unified candidates with the same signature yet. Probably
    * we should be doing that on the fly as we resolve types, instead
    * of afterwards, but the code for that would be horrifying...
    * XXX though -- the results are not always good this way.
    *
    * XXX also we should probably fetch the best available resolution
    * of any scratch types in the argument/operand lists.
    *)
   let sortsig (_, (_pos1, n1, a1, o1)) (_, (_pos2, n2, a2, o2)) =
      let a1' = List.map (improvetype ctx) a1 in
      let o1' = List.map (improvetype ctx) o1 in
      let a2' = List.map (improvetype ctx) a2 in
      let o2' = List.map (improvetype ctx) o2 in
      compare (n1, a1', o1') (n2, a2', o2')
   in
   let matches = List.filter (fun (x, _) -> x) (Util.zip oks insns) in
   let matches = List.sort_uniq sortsig matches in
   match matches with
        [] -> nomatchinsns callinsn insns
      | [(_, insn)] -> unifyinsn ctx callinsn insn
      | _ ->
        let (_, matchinsns) = Util.unzip matches in
        ambigmatchinsns callinsn matchinsns

(*
 * Given a USE, try to identify the callee and unify the types.
 *
 * (This is also used for instructions, which are implicitly simple
 * cases of USEs.)
 *
 * The macro/instruction named in EXCLUDE (currently identified by
 * name and definedat position, which is gross) is not considered
 * because recursive invocations aren't allowed.
 *)
let inf2'use ctx exclude callinsn =
   let (pos, name, callargs, callops) = callinsn in
   match ctx_getinsn ctx name with
        None ->
           (*
            * Encodingcheck should have caught any of these within
            * encodings.def, but not ones referred to by opmatch.def.
            *)
           Pos.sayat pos ("No such encoding or macro " ^ name);
           Util.fail ()
      | Some [] ->
           Util.crash "typeinf: inf2'use: empty insn"
      | Some insns ->
           (* Drop the macro/instruction we're calling from. *)
           let excludepred (calleepos, calleename, _, _) =
              match exclude with
                   None -> true
                 | Some excl -> (calleepos, calleename) <> excl
           in
           let insns = List.filter excludepred insns in

           (* Drop any that don't have the right number of args/operands. *)
           let numargs = List.length callargs in
           let numops = List.length callops in
           let pred (_, _, defargs, defops) =
              List.length defargs = numargs && List.length defops = numops
           in
           let candidates = List.filter pred insns in

           (* Match against those. *)
           match candidates with
                [] -> nomatchinsns callinsn insns
              | [insn] -> unifyinsn ctx callinsn insn
              | _ -> matchinsns ctx callinsn candidates

let rec inf2'macrostmt ctx exclude r = match r with
     USE (pos, name, args, ops, _resolvedname_unset) ->
       let ty'args = List.map exprtype args in
       let ty'ops = List.map exprtype ops in
       inf2'use ctx exclude (pos, name, ty'args, ty'ops)
   | IF (_pos, _cond, t, f) ->
       List.iter (inf2'macrostmt ctx exclude) t;
       List.iter (inf2'macrostmt ctx exclude) f;
   | _ -> ()

let inf2'expansion ctx exclude (_pos, _e, stmts) =
   List.iter (inf2'macrostmt ctx exclude) stmts

let inf2'macro ctx { name; definedat; expansions; _ } =
   let exclude = Some (definedat, name) in
   List.iter (inf2'expansion ctx exclude) expansions

let inf2'instruction ctx { definedat; operands_int; encoder; } =
   inf2'use ctx None (definedat, encoder, [], operands_int)

let inf2'spec ctx spec =
   List.iter (inf2'macro ctx) spec.macros;
   List.iter (inf2'instruction ctx) spec.instructions

(**************************************************************)
(* resolve inferred types *)

let res'enum _ e = e
let res'subenum _ r = r

(* forms and fields can't have temporary unification types *)
let res'field _ f = f
let res'form _ f = f

let res'compoundtype _ ct = ct
let res'operandtag _ ot = ot

(* the types in modifiers are declared up front; nothing to do *)
let res'modifier _ m = m

let res'assignment ctx (pos, name, e) =
   (pos, name, res'expr ctx e)

let rec res'statement ctx r = match r with
     ASSIGN (pos, name, e) ->
        let e' = res'expr ctx e in
        ASSIGN (pos, name, e')
   | USE (pos, name, es, ops, resolvedname_unset) ->
        let es' = List.map (res'expr ctx) es in
        let ops' = List.map (res'expr ctx) ops in
        USE (pos, name, es', ops', resolvedname_unset)
   | IF (pos, c, t, f) ->
        let c' = res'expr ctx c in
        let t' = List.map (res'statement ctx) t in
        let f' = List.map (res'statement ctx) f in
        IF (pos, c', t', f')
   | EMIT (pos, e) ->
        let e' = res'expr ctx e in
        EMIT (pos, e')
   | HOOK (pos, name, args) ->
        let args' = List.map (res'expr ctx) args in
        HOOK (pos, name, args')
   | WARN (pos, text) ->
        WARN (pos, text)

let res'alternative ctx (pos, e, stmts) =
   let e' = res'expr ctx e in
   let results' = List.map (res'statement ctx) stmts in
   (pos, e', results')

let res'encoding ctx { name; mangledname; definedat; specargs; opargs;
		       formname; alternatives; } =
   let res'arg (pos, n, t) =
      (pos, n, res'type ctx t)
   in
   let specargs' = List.map res'arg specargs in
   let opargs' = List.map res'arg opargs in
   let alternatives' = List.map (res'alternative ctx) alternatives in
   {
      name;
      mangledname;
      definedat;
      specargs = specargs';
      opargs = opargs';
      formname;
      alternatives = alternatives';
   }

let res'expansion ctx (pos, e, stmts) =
   let e' = res'expr ctx e in
   let stmts' = List.map (res'statement ctx) stmts in
   (pos, e', stmts')

let res'macro ctx { name; mangledname; definedat; specargs; opargs;
		    expansions; } =
   let res'arg (pos, n, t) =
      (pos, n, res'type ctx t)
   in
   let specargs' = List.map res'arg specargs in
   let opargs' = List.map res'arg opargs in
   let expansions' = List.map (res'expansion ctx) expansions in
   {
      name;
      mangledname;
      definedat;
      specargs = specargs';
      opargs = opargs';
      expansions = expansions';
   }

let res'insns ctx =
   let res'sig (pos, name, argtys, optys) =
      let argtys = List.map (res'type ctx) argtys in
      let optys = List.map (res'type ctx) optys in
      (pos, name, argtys, optys)
   in
   let res'sigs sigs = List.map res'sig sigs in
   ctx.insns := flatscope_map res'sigs !(ctx.insns)

let res'spec ctx spec =
   let map = Types.StringMap.map in

   let {
	pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
   } = spec in

   let enums =        map (res'enum ctx)        enums in
   let compoundtypes = map (res'compoundtype ctx) compoundtypes in
   let operandtags =  map (res'operandtag ctx)  operandtags in
   let modifiers =    map (res'modifier ctx)    modifiers in
   let fields =       map (res'field ctx)       fields in
   let forms =        map (res'form ctx)        forms in
   let subenums =     map (res'subenum ctx)     subenums in
   let encodings =    List.map (res'encoding ctx)    encodings in
   let macros =       List.map (res'macro ctx)       macros in

   (* XXX: should we also resolve ctx.vars? *)
   res'insns ctx;

   {
	pcunitwidth; addresswidth; endian; do_reginfo;
	enums; compoundtypes; operandtags;
	modifiers;
	fields; forms;
	subenums;
	encodings; macros; instructions;
   }

(**************************************************************)
(* make sure we're done (no temporary types left) *)

let done'compoundtype _ { name; members; _ } =
   let done'mem (pos, ty) =
      TI.done'typename'fatal pos ("member of compound type " ^ name) ty
   in
   List.iter done'mem members

let done'operandtag _ { name; definedat; basetype; } =
   TI.done'typename'fatal definedat ("type for operand tag " ^ name) basetype

let done'field _ { name; definedat; ty; } =
   TI.done'typename'fatal definedat ("field " ^ name) ty

let done'form _ { name; definedat; types; _ } =
   List.iter (TI.done'typename'fatal definedat ("form " ^ name)) types

(* patterns don't actually have types in them *)
let done'pattern _pat = ()

let done'assignment (_pos, pat, e) =
   done'pattern pat;
   TI.done'expr e

let rec done'statement r = match r with
     ASSIGN a -> done'assignment a
   | IF (_pos, c, t, f) ->
        TI.done'expr c;
        List.iter done'statement t;
        List.iter done'statement f
   | USE (_pos, _name, es, ops, _resolvedname_unset) ->
        List.iter TI.done'expr es;
        List.iter TI.done'expr ops
   | EMIT (_pos, e) ->
        TI.done'expr e
   | HOOK (_pos, _name, args) ->
        List.iter TI.done'expr args
   | WARN (_pos, _text) ->
        ()

let done'alternative (_pos, e, stmts) =
   TI.done'expr e;
   List.iter done'statement stmts

let done'encoding { name; specargs; opargs; alternatives; _ } =
   let done'arg (pos, n, t) =
      TI.done'typename pos ("argument " ^ n ^ " of " ^ name) t
   in
   List.iter done'arg specargs;
   List.iter done'arg opargs;
   List.iter done'alternative alternatives

let done'expansion (_pos, e, stmts) =
   TI.done'expr e;
   List.iter done'statement stmts

let done'macro { name; specargs; opargs; expansions; _ } =
   let done'arg (pos, n, t) =
      TI.done'typename pos ("argument " ^ n ^ " of " ^ name) t
   in
   List.iter done'arg specargs;
   List.iter done'arg opargs;
   List.iter done'expansion expansions

let done'instruction { name; definedat; operands_int; _ } =
   List.iter (TI.done'typename'fatal definedat ("operand of " ^ name))
								operands_int

let done'spec spec =
   let iter = Types.StringMap.iter in

   let {
	(*enums;*) compoundtypes; operandtags;
	fields; forms;
	(*subenums;*)
	encodings; macros; instructions;
        _
   } = spec in

   (*iter (done'enum)      enums;*)
   iter (done'compoundtype) compoundtypes;
   iter (done'operandtag)  operandtags;
   iter (done'field)       fields;
   iter (done'form)        forms;
   (*iter (done'subenum) subenums;*)
   List.iter (done'encoding)    encodings;
   List.iter (done'macro)       macros;
   List.iter (done'instruction) instructions

(**************************************************************)
(* compute encoding/macro/instruction signatures *)

(*
 * Note that while some of the code above deals in signatures, we
 * can't assign signatures for real until after we've finished
 * resolving scratch types.
 *)

let argtype (_pos, _name, ty) = ty

let rec sign'statement ctx stmt = match stmt with
     USE (pos, name, args, ops, _) ->
        let ty'args = List.map exprtype args in
        let ty'ops = List.map exprtype ops in
        let sigg = (pos, name, ty'args, ty'ops) in
        let resolvedname = mangle ctx sigg in
        USE (pos, name, args, ops, resolvedname)
   | IF (pos, cond, t, f) ->
        let t' = List.map (sign'statement ctx) t in
        let f' = List.map (sign'statement ctx) f in
        IF (pos, cond, t', f')
   | _ -> stmt

let sign'encoding ctx (enc : encoding) =
   let specargtypes = List.map argtype enc.specargs in
   let opargtypes = List.map argtype enc.opargs in

   let signature = (enc.definedat, enc.name, specargtypes, opargtypes) in
   let mangledname = mangle ctx signature in

   { enc with mangledname; }

let sign'expansion ctx (pos, guard, block) =
   (pos, guard, List.map (sign'statement ctx) block)

let sign'macro ctx (mac : macro) =
   let specargtypes = List.map argtype mac.specargs in
   let opargtypes = List.map argtype mac.opargs in

   let signature = (mac.definedat, mac.name, specargtypes, opargtypes) in
   let mangledname = mangle ctx signature in

   let expansions = List.map (sign'expansion ctx) mac.expansions in

   { mac with mangledname; expansions; }

let sign'instruction ctx (insn : instruction) =
   let signature = (insn.definedat, insn.name, [], insn.operands_int) in
   let mangledname_int = mangle ctx signature in

   let callsig = (insn.definedat, insn.encoder, [], insn.operands_int) in
   let encoder_mangled = mangle ctx callsig in

   { insn with mangledname_int; encoder_mangled; }

let sign'spec ctx spec =
   let encodings = List.map (sign'encoding ctx) spec.encodings in
   let macros = List.map (sign'macro ctx) spec.macros in
   let instructions = List.map (sign'instruction ctx) spec.instructions in
   { spec with encodings; macros; instructions; }

(**************************************************************)
(* Merge matching signatures *)

(*
 * Note that for now at least (XXX?) we can't merge encodings and
 * macros that have the same signature, even if the guard expressions
 * are disjoint, because the representation can't store one thing that
 * has some cases that are encodings and others that are macros.
 *
 * Therefore, for now at least it is wrong for encodings and macros
 * (and instructions) to have overlapping signatures.
 *
 * And therefore, for now at least, all we do is one merging pass over
 * the encodings and another merging pass over the macros. Any
 * overlaps will be detected and rejected later on.
 *)

(*
 * Check if two arglists (really parameter lists) are the same,
 * ignoring the input file position.
 *)
let args_eq args1 args2 =
   let arg_eq ((_pos1, name1, ty1), (_pos2, name2, ty2)) =
      name1 = name2 && ty1 = ty2
   in
   if List.length args1 <> List.length args2 then
      false
   else
      List.for_all arg_eq (Util.zip' args1 args2)

let merge'encodings _ctx encs =
   let tbl : (int * encoding) Types.StringMap.t ref =
      ref Types.StringMap.empty
   in
   let addenc (n, (enc : encoding)) =
      try
         let (prevn, prev) = Types.StringMap.find enc.mangledname !tbl in
         if enc.name <> prev.name then
            Pos.crashat enc.definedat ("typeinf: merge: encoding names " ^
				       enc.name ^ " and " ^ prev.name ^
				       " both have signature " ^
				       enc.mangledname)
         ;
         if not (args_eq enc.specargs prev.specargs)
            || not (args_eq enc.opargs prev.opargs) then begin
            (* XXX it would be better if this weren't true *)
            Pos.sayat enc.definedat ("Encodings with same signature must" ^
				     " have the same argument and operand" ^
				     " names");
            Pos.sayat prev.definedat "Other encoding";
            Util.fail ()
         end;
         if enc.formname <> prev.formname then begin
            (* XXX this is pretty much wrong, have to change the rep *)
            Pos.sayat enc.definedat ("Encodings with same signature must " ^
				     "use the same form");
            Pos.sayat prev.definedat "Other encoding";
            Util.fail ()
         end;
         let newalts = prev.alternatives @ enc.alternatives in
         let newenc = { prev with alternatives = newalts; } in
         tbl := Types.StringMap.add newenc.mangledname (prevn, newenc) !tbl
      with Not_found ->
         tbl := Types.StringMap.add enc.mangledname (n, enc) !tbl
   in
   (* Number the encodings to (mostly) preserve the input ordering *)
   List.iter addenc (Util.number encs);
   let sort (_, (n1, _)) (_, (n2, _)) = compare n1 n2 in
   let encs = List.sort sort (Types.StringMap.bindings !tbl) in
   List.map (fun (_, (_, enc)) -> enc) encs

(*
 * XXX this has too much cutpaste code, but it's not obvious how to
 * share it without doing a lot of work.
 *)
let merge'macros _ctx macs =
   let tbl : (int * macro) Types.StringMap.t ref =
      ref Types.StringMap.empty
   in
   let addmac (n, (mac : macro)) =
      try
         let (prevn, prev) = Types.StringMap.find mac.mangledname !tbl in
         if mac.name <> prev.name then
            Pos.crashat mac.definedat ("typeinf: merge: macro names " ^
				       mac.name ^ " and " ^ prev.name ^
				       " both have signature " ^
				       mac.mangledname)
         ;
         if not (args_eq mac.specargs prev.specargs)
            || not (args_eq mac.opargs prev.opargs) then begin
            (* XXX it would be better if this weren't true *)
            Pos.sayat mac.definedat ("Macros with same signature must have " ^
			             " the same argument and operand names");
            Pos.sayat prev.definedat "Other macro";
            Util.fail ()
         end;
         let newexps = prev.expansions @ mac.expansions in
         let newmac = { prev with expansions = newexps; } in
         tbl := Types.StringMap.add newmac.mangledname (prevn, newmac) !tbl
      with Not_found ->
         tbl := Types.StringMap.add mac.mangledname (n, mac) !tbl
   in
   (* Number the macros to (mostly) preserve the input ordering *)
   List.iter addmac (Util.number macs);
   let sort (_, (n1, _)) (_, (n2, _)) = compare n1 n2 in
   let macs = List.sort sort (Types.StringMap.bindings !tbl) in
   List.map (fun (_, (_, mac)) -> mac) macs

let merge'spec ctx spec =
   let encodings = merge'encodings ctx spec.encodings in
   let macros = merge'macros ctx spec.macros in
   { spec with encodings; macros; }

(**************************************************************)
(* tsort the macros *)

let rec getuses'stmt allmacros s = match s with
     ASSIGN _ -> []
   | IF (_pos, _cond, t, f) ->
        let uses't = List.map (getuses'stmt allmacros) t in
        let uses'f = List.map (getuses'stmt allmacros) f in
        List.concat (uses't @ uses'f)
   | USE (_pos, _name, _specargs, _opargs, mangledname) ->
        if Types.StringSet.mem mangledname allmacros then
           [mangledname]
        else
           []
   | EMIT _ -> []
   | HOOK _ -> []
   | WARN _ -> []

let getuses'expansion allmacros (_pos, _guard, block) =
   List.concat (List.map (getuses'stmt allmacros) block)

let getuses'macro allmacros m =
   List.concat (List.map (getuses'expansion allmacros) m.expansions)

let tsort'spec spec =
   let getkey (m : macro) = m.mangledname in

   (* Blah: want only USE calls that refer to macros, not encodings *)
   let allmacros =
      let doadd set (m : macro) = Types.StringSet.add m.mangledname set in
      List.fold_left doadd Types.StringSet.empty spec.macros
   in

   let macros = Tsort.tsort getkey (getuses'macro allmacros) spec.macros in

   { spec with macros; }

(**************************************************************)
(* propagate relocation info to EVAL *)

(*
 * Each EVAL node needs to know the relocation field it's evaluating
 * for, because that's what ultimately generates the correct
 * relocation code in the assembler output.
 *
 * This info is not available at the EVAL node, but we can propagate
 * it up from the field assignments.
 *)

(*
 * context
 *)

type relctx = {
   (* this holds the relfield and offset from each field declaration *)
   fieldinfo: (string option * int) Types.StringMap.t;

   (* this holds the name of the field, if any, for bound variables *)
   varinfo: string option scope ref;

   (* this holds the name of the field, if any, for specargs and opargs *)
   callinfo: (string option list * string option list) Types.StringMap.t ref;
}

let newrelctx (spec : spec) =
   let fieldinfo =
      let addfield _name (f : field) map =
         (* XXX simplify this later *)
         let foo = if f.relocatable then Some (Upcase.upcase f.name) else None in
         Types.StringMap.add f.name (foo, f.offset) map
      in
      Types.StringMap.fold addfield spec.fields Types.StringMap.empty
   in
   let varinfo =
      let addfield name _ scope =
         scope_add name (Some name) scope
      in
      Types.StringMap.fold addfield spec.fields (newscope None)
   in
   let callinfo = ref Types.StringMap.empty in
   { fieldinfo; varinfo = ref varinfo; callinfo; }

(*
 * context ops
 *)

let relctx_pushscope ctx =
   ctx.varinfo := newscope (Some !(ctx.varinfo))

let relctx_popscope ctx =
   match (!(ctx.varinfo)).parent with
        None -> Util.crash "typeinf: relinf: unbalanced popscope"
      | Some scope -> ctx.varinfo := scope

let relctx_setvar ctx name info =
   ctx.varinfo := scope_add name info !(ctx.varinfo)

let relctx_setcall ctx sig_ info =
   ctx.callinfo := Types.StringMap.add sig_ info !(ctx.callinfo)

let relctx_getfield ctx name =
   Types.StringMap.find name ctx.fieldinfo

let relctx_getvar ctx name =
   match scope_get name !(ctx.varinfo) with
        None -> None
      | Some x -> x

let relctx_getcall ctx sig_ =
   (* crash if the call target isn't there; that's been checked *)
   Types.StringMap.find sig_ !(ctx.callinfo)

let relctx_getarg ctx (_pos, name, _ty) =
   relctx_getvar ctx name

let relctx_makecallinfo ctx specargs opargs =
   let specinfo = List.map (relctx_getarg ctx) specargs in
   let opinfo = List.map (relctx_getarg ctx) opargs in
   (specinfo, opinfo)

(*
 * recursive pass
 *
 * note that this propagates information *backwards* through expressions
 *)

let relinf'op _ctx op info = match op with
     EQ | IN | LT -> None
   | STRCAT -> info
   | ADD | SUB | MUL | DIV | MOD | NEG -> info
   | SHL | SHR -> info
   | BITAND | BITOR | BITXOR | BITNOT -> info
   | LOGAND | LOGOR | LOGXOR | LOGNOT -> None
   | CONSTP | DEFINEDP -> None
   | ORD -> info

let rec relinf'expr_noeval ctx where e = match e with
     CONST _ -> ()
   | STRCONST _ -> ()
   | USEVAR (_pos, _ty, name) -> relctx_setvar ctx name None
   | USEFIELD (_pos, _ty, e1, _name) ->
        relinf'expr_noeval ctx where e1
   | OP (_pos, _ty, _op, args) ->
        List.iter (relinf'expr_noeval ctx where) args
   | FITS (_pos, _ty, e1, _argty) ->
        relinf'expr_noeval ctx where e1
   | MODE _ -> ()
   | LIST (_pos, _ty, args) ->
        List.iter (relinf'expr_noeval ctx where) args
   | MODIFIER (_pos, _ty, _modname, args) ->
        List.iter (relinf'expr_noeval ctx where) args
   | PACK (_pos, _ty, _ctor, args) ->
        List.iter (relinf'expr_noeval ctx where) args
   | CAST (_pos, _nty, _oty, e1) ->
        relinf'expr_noeval ctx where e1
   | EVAL (pos, _nty, _relfield, _reloffset, _oty, e1) ->
        relinf'expr_noeval ctx where e1;
        Pos.sayat pos ("Misplaced eval in " ^ where);
        Util.fail ()
   | UNEVAL (pos, _ty, e1) ->
        relinf'expr_noeval ctx where e1;
        Pos.sayat pos ("Misplaced @ in " ^ where);
        Util.fail ()
   | ANNOTATE (_pos, _ty, e1) ->
        relinf'expr_noeval ctx where e1
   | COMMENTED (_txt, e1) ->
        relinf'expr_noeval ctx where e1

let rec relinf'expr ctx (e, info) = match e with
     CONST _ -> e
   | STRCONST _ -> e
   | USEVAR (_pos, _ty, name) -> relctx_setvar ctx name info; e
   | USEFIELD (pos, ty, e1, name) ->
        let e1 = relinf'expr ctx (e1, info) in
        USEFIELD (pos, ty, e1, name)
   | OP (pos, ty, op, args) ->
        let info = relinf'op ctx op info in
        let info = List.map (fun arg -> (arg, info)) args in
        let args = List.map (relinf'expr ctx) info in
        OP (pos, ty, op, args)
   | FITS (pos, ty, e1, argty) ->
        let e1 = relinf'expr ctx (e1, info) in
        FITS (pos, ty, e1, argty)
   | MODE (pos, modename) ->
        MODE (pos, modename)
   | LIST (_pos, _ty, args) ->
        List.iter (relinf'expr_noeval ctx "list expression") args; e
   | MODIFIER (_pos, _ty, _modname, args) ->
        List.iter (relinf'expr_noeval ctx "modifier arguments") args; e
   | PACK (pos, ty, ctor, args) ->
        (*List.iter (relinf'expr_noeval ctx "constructor arguments") args; e*)
        let args' = List.map (fun arg -> relinf'expr ctx (arg, info)) args in
        PACK (pos, ty, ctor, args')
   | CAST (pos, nty, oty, e1) ->
        let e1 = relinf'expr ctx (e1, info) in
        CAST (pos, nty, oty, e1)
   | EVAL (pos, nty, _relfield, _reloffset, oty, e1) -> begin
        relinf'expr_noeval ctx "unevaluated operand expression" e1;
        match info with
             None ->
                Pos.sayat pos ("Unexpected eval; result of expression " ^
			       "does not reach an instruction field");
                Util.fail ();
                e1
           | Some fname -> begin
                let (relfield, reloffset) = relctx_getfield ctx fname in
                match relfield with
                     None ->
                        Pos.sayat pos ("Unexpected eval; result of " ^
                                       "expression reaches non-relocatable " ^
                                       "field " ^ fname);
                        Util.fail ();
                        e1
                   | Some rf ->
                        EVAL (pos, nty, rf, reloffset, oty, e1)
             end
     end
   | UNEVAL (pos, ty, e1) ->
        let e1 = relinf'expr ctx (e1, info) in
        UNEVAL (pos, ty, e1)
   | ANNOTATE (pos, ty, e1) ->
        let e1 = relinf'expr ctx (e1, info) in
        ANNOTATE (pos, ty, e1)
   | COMMENTED (txt, e1) ->
        let e1 = relinf'expr ctx (e1, info) in
        COMMENTED (txt, e1)

let rec relinf'pattern ctx pat = match pat with
     SETVAR (_pos, name) -> relctx_getvar ctx name
   | UNPACK (_pos, _ctor, pats) ->
        (*
         * XXX: This is too approximate. We ought to carry around an
         * info type that can record the relocation field separately
         * for each of the members of a value of compound type. This
         * treats the compound type's field as the field of any of
         * its members, provided there's exactly one. Fortunately it's
         * rare to have more than one relocatable item in a single
         * instruction so this is unlikely to be limiting; however it
         * allows various messy mistakes tha tit shouldn't.
         *)
        let infos = List.map (relinf'pattern ctx) pats in
        let merge z info =
           match z, info with
                Some r, None -> Some r
              | None, Some r -> Some r
              | _, _ -> None
        in
        List.fold_left merge None infos

let rec relinf'stmt ctx stmt = match stmt with
     ASSIGN (pos, pat, e) ->
        let info = relinf'pattern ctx pat in
        let e = relinf'expr ctx (e, info) in
        ASSIGN (pos, pat, e)
   | IF (pos, cond, t, f) ->
        relinf'expr_noeval ctx "if condition" cond;
        (*
         * XXX this is not really good enough either: we should check
         * that anything updated is the same on both sides, and currently
         * it'll just take the version from the false branch.
         *)
        let t = List.rev (List.map (relinf'stmt ctx) (List.rev t)) in
        let f = List.rev (List.map (relinf'stmt ctx) (List.rev f)) in
        IF (pos, cond, t, f)
   | USE (pos, name, args, ops, sig_) ->
        let (arginfo, opinfo) = relctx_getcall ctx sig_ in
        let arginfo = Util.zip args arginfo in
        let opinfo = Util.zip ops opinfo in
        let args = List.map (relinf'expr ctx) arginfo in
        let ops = List.map (relinf'expr ctx) opinfo in
        USE (pos, name, args, ops, sig_)
   | EMIT (pos, _e) ->
        (* EMIT is only added downstream *)
        Pos.crashat pos "typeinf: relinf'stmt: unexpected EMIT"
   | HOOK (pos, _name, _args) ->
        (* HOOK is only added downstream *)
        Pos.crashat pos "typeinf: relinf'stmt: unexpected HOOK"
   | WARN (pos, text) ->
        WARN (pos, text)

let relinf'alternative ctx (pos, guard, block) =
   relinf'expr_noeval ctx "encoding guard" guard;
   let block = List.rev (List.map (relinf'stmt ctx) (List.rev block)) in
   (pos, guard, block)

let relinf'encoding ctx enc =
   let alternatives = List.map (relinf'alternative ctx) enc.alternatives in
   let callinfo = relctx_makecallinfo ctx enc.specargs enc.opargs in
   relctx_setcall ctx enc.mangledname callinfo;
   { enc with alternatives; }

let relinf'expansion ctx (pos, guard, block) =
   relinf'expr_noeval ctx "macro guard" guard;
   let block = List.rev (List.map (relinf'stmt ctx) (List.rev block)) in
   (pos, guard, block)

let relinf'macro ctx mac =
   let expansions = List.map (relinf'expansion ctx) mac.expansions in
   let callinfo = relctx_makecallinfo ctx mac.specargs mac.opargs in
   relctx_setcall ctx mac.mangledname callinfo;
   { mac with expansions; }

let relinf spec =
   let ctx = newrelctx spec in

   let encodings = List.map (relinf'encoding ctx) spec.encodings in
   let macros = List.map (relinf'macro ctx) spec.macros in

   { spec with encodings; macros; }

(**************************************************************)
(* callback hooks *)

(*
 * Callback hooks for the common typeinf code
 *)
let lookup_compoundtype (ctx: context) ctor =
   flatscope_get ctor !(ctx.compoundtypes)

let lookup_variable ctx name =
   ctx_getvar ctx name

let lookup_modifier ctx modname =
   try
      let mi = Types.StringMap.find modname ctx.spec.modifiers in
      Some (mi.definedat, mi.argtype, mi.resulttype)
   with Not_found -> None

(**************************************************************)
(* top level *)

let typeinf spec =
   let ctx = newctx spec in

   (* this must be built after the initial context construction *)
   let callbacks = {
      TI.unalias_type = (fun ty -> ty);
      TI.lookup_compoundtype = lookup_compoundtype ctx;
      TI.lookup_variable = lookup_variable ctx;
      TI.lookup_modifier = lookup_modifier ctx;
   } in
   TI.setcallbacks ctx.tictx callbacks;

(*
   let builtinpos = { Pos.file = "<builtin>"; Pos.line=0; Pos.column=0; } in
*)
   ctx_addvar ctx "true" booltype;
   ctx_addvar ctx "false" booltype;
   ctx_addvar ctx "." (EXPRTYPE (WIDTHTYPE ("uint", spec.addresswidth)));

   (* First, run inference on the whole thing. *)
   let spec = inf'spec ctx spec in

   (* Resolve all the types we can. *)
   let spec = res'spec ctx spec in

   (* Now run the instruction matching pass. *)
   inf2'spec ctx spec;

   (* Resolve again. *)
   let spec = res'spec ctx spec in

   (* Now we'd better be done resolving. *)
   done'spec spec;

   (* Assign signatures to encodings, macros, and instructions. *)
   let spec = sign'spec ctx spec in

   (* Merge encodings/macros/instructions with the same signatures. *)
   let spec = merge'spec ctx spec in

   Util.checkfail ();

   (* tsort the macro list *)
   let spec = tsort'spec spec in

   (* Propagate relocation info *)
   let spec = relinf spec in

   spec
