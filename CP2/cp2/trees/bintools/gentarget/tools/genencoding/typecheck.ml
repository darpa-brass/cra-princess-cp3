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

module TC = Exprtypecheck

open Rep

(**************************************************************)
(* signatures *)

type insnsig = {
   name: string;
   mangledname: string;
   defpos: Pos.pos; (* not "definedat" or the compiler horks *)
   tyargs: typename list;
   tyops: typename list;
}

(**************************************************************)
(* scopes *)

type 't scope = {
   bindings: 't Types.StringMap.t ref;
   inner: 't scope option ref;
}

let newscope () = {
   bindings = ref Types.StringMap.empty;
   inner = ref None;
}

let stringmap_get name m =
   try
      Some (Types.StringMap.find name m)
   with Not_found -> None

let rec scope_get name { bindings; inner; } =
   match stringmap_get name !bindings, !inner with
        Some x, _ -> Some x
      | None, Some inner' -> scope_get name inner'
      | None, None -> None

let scope_gethere name { bindings; _ } =
   stringmap_get name !bindings

(* unused
let scope_filterkeys pred { bindings; _ } =
   let key (k, _v) = k in
   List.filter pred (List.map key (Types.StringMap.bindings !bindings))
*)

let scope_filtervals pred { bindings; _ } =
   let value (_k, v) = v in
   List.filter pred (List.map value (Types.StringMap.bindings !bindings))

let scope_add name v { bindings; _ } =
   bindings := Types.StringMap.add name v !bindings

(*
let scope_push scope =
   { bindings = ref Types.StringMap.empty; inner = Some scope; }

let scope_pop { inner; _ } = match inner with
     None -> Util.crash "typecheck: scope_pop: nothing to pop"
   | Some inner' -> inner'
*)

let scope_push scope =
   let inner = {
      bindings = ref !(scope.bindings);
      inner = ref !(scope.inner);
   } in
   scope.bindings := Types.StringMap.empty;
   scope.inner := Some inner

let scope_pop scope = match !(scope.inner) with
     None -> Util.crash "typecheck: scope_pop: nothing to pop"
   | Some inner' ->
        scope.bindings := !(inner'.bindings);
        scope.inner := !(inner'.inner)

(**************************************************************)
(* context *)

type context = {
   tcctx: TC.context;

   spec: spec;

   (* namespaces *)
             (* definedat takeswidth members-of-compound *)
   alltypes: (Pos.pos * bool * (Pos.pos * typename) list) scope;
   alllongnames: (Pos.pos * typename) scope;
   allvars: (Pos.pos * typename) scope;
   allinsns: insnsig scope;

   (* assigned variables tracking *)
   assignedvars: unit scope;
}

let newcontext s = {
   tcctx = TC.newctx ();
   spec = s;
   alltypes = newscope ();
   alllongnames = newscope ();
   allvars = newscope ();
   allinsns = newscope ();
   assignedvars = newscope ();
}

(*
let pushscope ctx =
   let allvars' = scope_push ctx.allvars in
   let assignedvars' = scope_push ctx.assignedvars in
   { ctx with allvars=allvars'; assignedvars=assignedvars'; }

let popscope ctx =
   let allvars' = scope_pop ctx.allvars in
   let assignedvars' = scope_pop ctx.assignedvars in
   { ctx with allvars=allvars'; assignedvars=assignedvars'; }
*)

let pushscope ctx =
   scope_push ctx.allvars;
   scope_push ctx.assignedvars

let popscope ctx =
   scope_pop ctx.allvars;
   scope_pop ctx.assignedvars

(**************************************************************)
(* tools *)

(*
let lookupname ctx name =
   let rec lookscope scope name =
      try
         Some (Types.StringMap.find name !(scope.bindings))
      with Not_found ->
         match !(scope.inner) with
              Some scope' -> lookscope scope' name
            | None -> None
   in
   lookscope !(ctx.namebindings) name

let name_inuse ctx expected name what =
   match lookupname ctx name with
        Some b ->
	   if expected = true then ()
	   else begin
	      say ctx ("Identifier " ^ name ^ " rebound as " ^ what ^
		       " was already bound as " ^ b.what);
	      Pos.sayat b.where ("Previous binding");
	      fail ctx
	   end
      | None ->
	   if expected = false then ()
	   else begin
	      say ctx ("Identifier " ^ name ^ " used as " ^ what ^
		       " is not bound");
	      fail ctx
	   end

let bindname' ctx name what where =
   let b = { what = what; where = where; ty = None; }  in
   let scope = !(ctx.namebindings) in
   scope.bindings := Types.StringMap.add name b !(scope.bindings)

let bindname ctx name what where ty =
   let b = { what = what; where = where; ty = Some ty; }  in
   let scope = !(ctx.namebindings) in
   scope.bindings := Types.StringMap.add name b !(scope.bindings)
*)

let tystr ty = 
   dump'typename ty
(*
   match ty with
     FIELD (INT bits) -> "int(" ^ string_of_int bits ^ ")"
   | FIELD (UINT bits) -> "uint(" ^ string_of_int bits ^ ")"
   | FIELD (ENUM name) -> name
   | FIELD (ZEROS bits) -> "zeros(" ^ string_of_int bits ^ ")"
   | BOOL -> "bool"
   | SHIFTCOUNT -> "shiftcount" (* XXX? *)
   | LISTTYPE t -> "[" ^ tystr t ^ "]"
   | TMPTYPE n -> ".T" ^ string_of_int n
*)

let saysig pos name tyargs tyops mangledname =
   let argstr = match tyargs with
        [] -> ""
      | _ -> "(" ^ String.concat ", " (List.map tystr tyargs) ^ ")"
   in
   let opstr = match tyops with
        [] -> ""
      | _ -> " " ^ String.concat ", " (List.map tystr tyops)
   in
   Pos.sayat pos ("   " ^ name ^ argstr ^ opstr ^ " as " ^ mangledname)

let saysigs qs =
   let sayone q =
      saysig q.defpos q.name q.tyargs q.tyops q.mangledname
   in
   List.iter sayone qs

(**************************************************************)
(* dispatches to common typecheck code *)

let typemismatch = TC.typemismatch

let check'typename ctx ty =
   TC.check'typename ctx.tcctx ty

let check'expr ctx e =
   TC.check'expr ctx.tcctx e

(**************************************************************)
(* types *)

(*
 * typename
 *)

(*
 * Test if a typename (use of a type) is ok as the type of a field.
 * Returns (Some width) if so, and None if not.
 *
 * Assumes check'typename has already been used to make sure the
 * type exists at all.
 *)
let type_ok_for_field ctx _pos ty =
   match ty with
        PLAINTYPE name -> begin
           (* It's ok if its an enumeration *)
           match stringmap_get name ctx.spec.enums with
                None -> None
              | Some e -> Some (e.width)
        end
      | WIDTHTYPE (_name, width) -> Some width
      | EXPRTYPE _ -> None
      | LISTTYPE _ -> None
      | TMPTYPE _n -> None

(*
 * enums
 *)

(*
 * Check an enum:
 *
 * 0. The name must be unique. This is implicitly enforced by the
 *    names being in a Types.StringMap.
 *
 * 1. Enums have a sanity limit on size of 2^20 entries.
 *
 * 2. The number of symbols in the syms list must match the bit width.
 *
 * 3. The symbols (which go in the variable namespace) must not already
 *    exist. This should have already been enforced by Checkencoding,
 *    since the variable namespace consists only of things from
 *    encoding.def, so crash on error.
 *
 * 4. The syms list must be in order.
 *
 * 5. The symtovalue and valuetosym tables must match the syms list.
 *)
let check'enum ctx _ { name; definedat; width; syms; symtovalue; valuetosym;} =
   if width > 20 then begin
      Pos.sayat definedat ("Enumeration " ^ name ^ " is ridiculously large");
      Util.fail ()
   end;
   let numsyms = Util.power 2 width in
   if List.length syms <> numsyms then begin
      Pos.sayat definedat ("Enumeration has " ^
			   string_of_int (List.length syms) ^
			   " elements but should have 2^" ^
			   string_of_int width ^ " = " ^
			   string_of_int numsyms);
      Util.fail ()
   end;

   let checksym (n, (pos, sym, v)) =
      if n <> v then begin
         Pos.sayat pos ("Wrong value " ^ string_of_int v ^ " for enumerator " ^
			sym ^ "; should be " ^ string_of_int n);
         Util.fail ()
      end;
      if sym = "" then begin
         Pos.sayat pos ("Empty string as enumeration constant");
         Util.fail ()
      end
      else if sym = "_" then ()
      else match scope_get sym ctx.allvars with
           None ->
              scope_add sym (pos, PLAINTYPE name) ctx.allvars
         | Some _ ->
              Pos.sayat pos ("Duplicate symbol " ^ sym);
              Util.fail ()
   in
   List.iter checksym (Util.number syms);

   (* Enumeration entries called _ don't appear in symtovalue *)
   let count k (_pos, sym, _v) =
      if sym = "_" then k+1 else k
   in
   let numignored = List.fold_left count 0 syms in

   begin
   match stringmap_get "_" symtovalue with
        None -> ()
      | Some _ -> Pos.crashat definedat "typecheck: _ in enum symtovalue"
   end;

   let s2v_numsyms = numignored + Types.StringMap.cardinal symtovalue in
   let v2s_numsyms = Array.length valuetosym in
   if s2v_numsyms <> numsyms then begin
      Pos.sayat definedat ("Enumeration " ^ name ^
                           " string to value map corrupt; found " ^
                           string_of_int s2v_numsyms ^ " entries instead of " ^
                           string_of_int numsyms);
      Util.fail ()
   end;
   if v2s_numsyms <> numsyms then begin
      Pos.sayat definedat ("Enumeration " ^ name ^
                           " value to string table corrupt; found " ^
                           string_of_int v2s_numsyms ^ " entries instead of " ^
                           string_of_int numsyms);
      Util.fail ()
   end;

   let checkentry (pos, sym, v) =
      if v >= Array.length valuetosym then () (* already complained *)
      else begin
         let foundsym = Array.get valuetosym v in
         if foundsym <> sym then begin
            Pos.sayat pos ("Enumeration " ^ name ^
			   " value to string table corrupt; " ^
			   (string_of_int v) ^ " maps to " ^ foundsym ^
			   " instead of " ^ sym);
            Util.fail ()
         end
      end;
      if sym = "_" then ()
      else match stringmap_get sym symtovalue with
           None ->
              Pos.crashat pos ("Enumeration " ^ name ^
                               " string to value map corrupt; missing " ^ sym)
         | Some foundval ->
              if foundval <> v then begin
                 Pos.sayat pos ("Enumeration " ^ name ^
				" string to value map corrupt; " ^ sym ^
				" gives " ^ string_of_int foundval ^
				" instead of " ^ string_of_int v);
                 Util.fail ()
              end
   in
   List.iter checkentry syms;
   (*
    * The "takeswidth" here is whether you need to provide the
    * width as an arg (like "uint(32)", which is not the case for
    * enums as each one has its own specific width.
    *)
   scope_add name (definedat, false(*takeswidth*), []) ctx.alltypes

(*
 * compound types
 *)

let check'compoundtype ctx _ { name; definedat; members; } =
   let checkmem (pos, ty) =
      check'typename ctx pos ty
   in
   List.iter checkmem members;
   match scope_get name ctx.alltypes with
        None ->
           scope_add name (definedat, false, members) ctx.alltypes
      | Some (defpos, _, _) ->
           Pos.sayat definedat ("Duplicate type name " ^ name);
           Pos.sayat defpos ("Previous definition");
           Util.fail ()


(**************************************************************)
(* operand tags *)

(*
 * Check an operand tag. The name must not already exist
 * and its underlying type must be valid.
 *
 * Part 1 checks and updates ctx.alltypes; part 2 does the rest.
 * These need to be separate because we didn't preserve the ordering
 * of the input file and types may refer to one another. So we run
 * everything through part 1 first and then run everything through
 * part 2.
 *
 * XXX we need to either revert that separation and preserve the
 * input order, or write a check to prohibit infinite mutually
 * recursive types.
 *
 * Update: at least the types coming from base.def are already
 * protected against being recursive by Basecheck.
 *
 * Note: this currently involves both compoundtypes and operand tags,
 * but that's wrong. (XXX)
 *)

let check'operandtag ctx _ { name; definedat; basetype; } =
   check'typename ctx definedat basetype;
   match scope_get name ctx.alllongnames with
        None ->
           scope_add name (definedat, basetype) ctx.alllongnames;
      | Some (defpos, _) ->
           Pos.sayat definedat ("Duplicate operand tag " ^ name);
           Pos.sayat defpos ("Previous definition");
           Util.fail ()

let check'uselongname ctx pos longname =
   match scope_get longname ctx.alllongnames with
        Some _ -> ()
      | None ->
           Pos.sayat pos ("Undefined operand tag " ^ longname);
           Util.fail ()

(**************************************************************)
(* forms and fields *)

(*
 * fields:
 *
 * 0. The name must not already exist. (Fields have their own
 *    namespace.) This is implied by fields being stored in a
 *    Types.StringMap.
 *
 * 1. The type must be valid.
 *
 * 2. The type must be allowable for fields: signed or unsigned
 *    integer, zeros, ones, or an enum.
 *)
let check'field ctx _ { name; definedat; ty; } =
   check'typename ctx definedat ty;
   match type_ok_for_field ctx definedat ty with
        None ->
          Pos.sayat definedat ("Type " ^ name ^
	       		       " may not be used as the type of a field.");
          Util.fail ()
      | Some _ -> ()

(*
 * Forms:
 *
 * 0. The name must not already exist. (Forms also have their own
 * namespace, which is manufactured by buildrep.) This is implied
 * by fields being stored in a Types.StringMap.
 *
 * 1. All the fields must exist, and the type for each field
 * must be the type declared for that field.
 *
 * 2. The total length of the form must be a multiple of the PC
 * unit width.
 *)
let check'form ctx _ { name; definedat; fields; types } =
   (* XXX should have a list of pairs instead *)
   if List.length fields <> List.length types then
      Pos.crashat definedat ("Form " ^ name ^ " type and field lists " ^
			     "have different lengths")
   ;

   let checkfield (field, ty) =
      match stringmap_get field ctx.spec.fields with
           None ->
              Pos.sayat definedat ("Form " ^ name ^
				   " uses nonexistent field " ^ field);
              Util.fail ()
         | Some f ->
              check'typename ctx definedat ty;
              if ty <> f.ty then
                 typemismatch definedat ty f.ty ("field " ^ field)
   in
   List.iter checkfield (Util.zip' fields types);

   let fieldwidth field =
      match stringmap_get field ctx.spec.fields with
           None -> 0 (* already complained *)
         | Some f ->
              match type_ok_for_field ctx definedat f.ty with
                   None -> 0 (* already complained *)
                 | Some w -> w
   in
   let width = List.fold_left (fun sum fn -> sum + fieldwidth fn) 0 fields in
   if width mod ctx.spec.pcunitwidth <> 0 then begin
      Pos.sayat definedat ("Form " ^ name ^ " has total width " ^
			   string_of_int width ^ ", which is not " ^
			   "a multiple of the PC unit width " ^
			   string_of_int ctx.spec.pcunitwidth);
      Util.fail ()
   end

(**************************************************************)
(* variables/values *)

(*
 * subenums
 *
 * 1. The name must not already exist. Subenums appear in the
 * variable namespace.
 *
 * 2. The enum indicated in enumname must exist.
 *
 * 3. The values must come from (only) that enum.
 *)
let check'subenum ctx _ { name; definedat; enumname; values; } =
   begin
   match scope_get name ctx.allvars with
        None ->
           let ty = LISTTYPE (PLAINTYPE enumname) in
           scope_add name (definedat, ty) ctx.allvars
      | Some (pos, _ty) ->
           Pos.sayat definedat ("Duplicate symbol " ^ name);
           Pos.sayat pos ("Previous definition");
           Util.fail ()
   end;
   match stringmap_get enumname ctx.spec.enums with
        None ->
           Pos.crashat definedat ("Enum " ^ enumname ^ " does not exist")
      | Some e ->
           let checksym sym =
              match stringmap_get sym e.symtovalue with
                   None ->
                      (* checked upstream *)
                      Pos.crashat definedat ("Symbol " ^ sym ^ " is not from" ^
                                             " enumeration " ^ enumname)
                 | Some _ -> ()
           in
           Types.StringSet.iter checksym values

(**************************************************************)
(* statements *)

let rec check'pattern ctx pat ty = match pat with
     SETVAR (pos, name) -> begin
        scope_add name () ctx.assignedvars;
        match scope_get name ctx.allvars with
             None ->
                scope_add name (pos, ty) ctx.allvars;
           | Some (_defpos, ty'stored) ->
                if ty <> ty'stored then
                   typemismatch pos ty'stored ty ("Assignment of " ^ name)
     end
   | UNPACK (pos, "modimm", [arg0; arg1]) -> begin
        (* XXX this should not exist *)
        match ty with
            WIDTHTYPE ("uint", 32) ->
               check'pattern ctx arg0 (WIDTHTYPE ("uint", 4));
               check'pattern ctx arg1 (WIDTHTYPE ("uint", 8))
          | _ ->
               Pos.sayat pos "Cannot unpack modimm; expected uint(32)";
               Util.fail ()
     end
   | UNPACK (pos, ctor, pats) ->
        match scope_get ctor ctx.alltypes with
             None ->
                Pos.sayat pos ("No such compound type " ^ ctor);
                Util.fail ()
           | Some (_defpos, _takeswidth, []) ->
                Pos.sayat pos ("Type " ^ ctor ^ " is not unpackable");
                Util.fail ()
           | Some (defpos, _takeswidth, argtypes) ->
                (* XXX shouldn't this check ty against (PLAINTYPE ctor)? *)
                let n'expected = List.length argtypes in
                let n'found = List.length pats in
                if n'expected <> n'found then begin
                   Pos.sayat pos ("Wrong number of elements unpacking type " ^
                                  ctor ^ ": found " ^ string_of_int n'found ^
                                  " but expected " ^
			          string_of_int n'expected);
                   Pos.sayat defpos "Type declaration";
                   Util.fail ();
                end;
                let checkone (pat, (_defpos, ty)) =
                   check'pattern ctx pat ty
                in
                List.iter checkone (Util.zip' pats argtypes)

let check'assignment ctx (_pos, pat, e) =
   let ty'e = check'expr ctx e in
   check'pattern ctx pat ty'e

let rec check'statement ctx ismacro s =
   match s with
        ASSIGN (pos, pat, e) ->
           check'assignment ctx (pos, pat, e)
      | USE (pos, _insn, args, ops, _resolvedinsn) ->
           if not ismacro then begin
              Pos.sayat pos "Illegal 'use' in encoding";
	      Util.fail ()
           end;
           let _ty'args = List.map (check'expr ctx) args in
           let _ty'ops = List.map (check'expr ctx) ops in
           ()
      | IF (pos, c, t, f) -> begin
           let ty'c = check'expr ctx c in
           if ty'c <> booltype then
              typemismatch pos booltype ty'c "control of if-expression"
           ;
           List.iter (check'statement ctx ismacro) t;
           List.iter (check'statement ctx ismacro) f
        end
      | EMIT (pos, e) -> begin
           let pcunittype = WIDTHTYPE ("uint", ctx.spec.pcunitwidth) in
           let ty'e = check'expr ctx e in
           if ty'e <> pcunittype then
              typemismatch pos pcunittype ty'e "argument of EMIT"
        end
      | HOOK (_pos, _name, args) ->
           (* XXX: should we actually declare hooks and typecheck the args? *)
           let _ty'args = List.map (check'expr ctx) args in
           ()
      | WARN (_pos, _text) ->
           ()


(**************************************************************)
(* encodings/macros/instructions *)

(*
 * Arguments of encodings (and macros)
 * (both specargs and opargs/operands)
 *
 * It is ok for args to be bound but not in *this* scope
 *)
let check'arg ctx (n, (pos, argname, ty)) =
   scope_add argname () ctx.assignedvars;
   check'typename ctx pos ty;
   match scope_get argname ctx.allvars with
        None ->
           scope_add argname (pos, ty) ctx.allvars
      | Some (defpos, prevty) ->
           if ty <> prevty then begin
              typemismatch pos ty prevty ("spec argument " ^
					  string_of_int (n+1));
              Pos.sayat defpos "Previous binding"
           end;
           match scope_gethere argname ctx.allvars with
                None -> ()
              | Some _ ->
                   Pos.sayat pos ("Duplicate argument name " ^ argname);
                   Util.fail ()

(*
 * Handle the signature of an encoding (or macro, or instruction)
 * if it's a definition. (instructions aren't always)
 *)
let doinsnsig' ctx name mangledname definedat tyargs tyops =
   let myq = {
      name;
      mangledname;
      defpos = definedat;
      tyargs;
      tyops;
   } in

   begin
   match scope_get mangledname ctx.allinsns with
        None ->
           scope_add mangledname myq ctx.allinsns
      | Some q ->
	   Pos.sayat definedat ("Duplicate encoding " ^ name);
	   saysig definedat name tyargs tyops mangledname;
	   Pos.sayat q.defpos "Previous definition";
	   saysig q.defpos q.name q.tyargs q.tyops q.mangledname;
	   Util.fail ();
           if q.name <> name then
              Pos.crashat definedat ("typecheck: doinsnsig: looked up " ^
				     mangledname ^ " (" ^ name ^ "), got " ^
				     q.mangledname ^ " (" ^ q.name ^ ")")
   end

let doinsnsig ctx name mangledname definedat specargs opargs =
   (* Compute the signature *)
   let getargtype (_, _, ty) = ty in
   let tyargs = List.map getargtype specargs in
   let tyops = List.map getargtype opargs in
   doinsnsig' ctx name mangledname definedat tyargs tyops

(*
 * encodings
 *)
let check'encoding ctx { name; mangledname; definedat; specargs; opargs;
			 formname; alternatives; } =
   doinsnsig ctx name mangledname definedat specargs opargs;

   (* The encoding has a scope *)
   (*let ctx = pushscope ctx in*)
   pushscope ctx;

   List.iter (check'arg ctx) (Util.number specargs);
   List.iter (check'arg ctx) (Util.number opargs);

   (* Form name must exist *)
   let form = match stringmap_get formname ctx.spec.forms with
        None ->
           (* Buildrep makes these up, so crash if broken *)
           Pos.crashat definedat ("No such instruction form " ^ formname)
      | Some f -> f
   in

   (* Each alternative version must be valid *)
   let check'alt (pos, guard, stmts) =
      let ty'guard = check'expr ctx guard in
      if ty'guard <> booltype then
         typemismatch pos booltype ty'guard "guard expression"
      ;
      (*let ctx = pushscope ctx in*)
      pushscope ctx;
      List.iter (check'statement ctx false) stmts;

      (* Check that we've assigned the whole form *)
      let checkfield (field, ty) =
         match ty with
              WIDTHTYPE ("zeros", _) -> ()
            | WIDTHTYPE ("ones", _) -> ()
            | _ ->
                 match scope_get field ctx.assignedvars with
                      Some _ -> ()
                    | None ->
                         Pos.sayat pos ("No assignment to field " ^ field ^
                                        "in this encoding alternative");
                         Util.fail ()
      in
      List.iter checkfield (Util.zip' form.fields form.types);
      popscope ctx
   in
   List.iter check'alt alternatives;

   popscope ctx

(*
 * macros
 *)

let check'macro ctx { name; mangledname; definedat; specargs; opargs;
		      expansions; } =
   doinsnsig ctx name mangledname definedat specargs opargs;

   (* The macro has a scope *)
   (*let ctx = pushscope ctx in*)
   pushscope ctx;

   List.iter (check'arg ctx) (Util.number specargs);
   List.iter (check'arg ctx) (Util.number opargs);

   (* Each expansion must be valid *)
   let check'exp (pos, guard, stmts) =
      let ty'guard = check'expr ctx guard in
      if ty'guard <> booltype then
         typemismatch pos booltype ty'guard "guard expression"
      ;
      (*let ctx = pushscope ctx in*)
      pushscope ctx;
      List.iter (check'statement ctx true) stmts;
      popscope ctx
   in
   List.iter check'exp expansions;
   popscope ctx

(*
 * instructions
 *)

let check'instruction ctx { definedat; operands_ext; operands_int; } = 
   (* Technically the instruction declaration has a scope *)
   (*let ctx = pushscope ctx in*)

   List.iter (check'uselongname ctx definedat) operands_ext;
   List.iter (check'typename ctx definedat) operands_int;

   (*popscope ctx*)
   ()

(**************************************************************)
(* consistency check of USE *)

(*
 * Check that the types of a USE match its callee.
 *
 * TYARGS and TYOPS are the types of the arguments; Q is the
 * callee's signature object from ctx.allinsns.
 *)
let checkuse'usecall _ctx pos tyargs tyops q =
   if tyargs <> q.tyargs || tyops <> q.tyops then begin
      Pos.sayat pos ("Invalid call to " ^ q.name);
      Pos.sayat pos "Signature found:";
      saysig pos q.name tyargs tyops q.mangledname;
      Pos.sayat pos "Signature expected:";
      saysig q.defpos q.name q.tyargs q.tyops q.mangledname;
      Util.fail()
   end

(*
 * Check that a USE matches its callee. Also check that it isn't
 * recursive.
 *
 * CALLERNAME is the mangled name of the instruction containing this
 * USE, for purposes of checking the recursion.
 *
 * POS is the location of the USE. CALLEE, TYARGS, TYOPS, and
 * CALLEE_MANGLED are the data from the USE.
 *
 * XXX we don't actually check recursion yet.
 *)
let no'use ctx pos callee tyargs tyops callee_mangled =
   Pos.sayat pos ("No suitable instruction " ^ callee ^ " found:");
   saysig pos callee tyargs tyops callee_mangled;
   Util.fail ();
   let pred (q : insnsig) = q.name = callee in
   match scope_filtervals pred ctx.allinsns with
        [] ->
           Pos.sayat pos ("Nothing by that name.")
      | candidates ->
           Pos.sayat pos "Possible candidates:";
           saysigs candidates

let checkuse'use ctx _callername pos callee tyargs tyops callee_mangled =
   match scope_get callee_mangled ctx.allinsns with
        None ->
           no'use ctx pos callee tyargs tyops callee_mangled
      | Some q ->
           checkuse'usecall ctx pos tyargs tyops q;
           if callee <> q.name then
              Pos.crashat pos ("typecheck: checkuse'use: looked up " ^
			       callee_mangled ^ " (" ^ callee ^ "), got " ^
			       q.mangledname ^ " (" ^ q.name ^ ")")


let rec checkuse'statement ctx mangledname stmt = match stmt with
     ASSIGN _ -> ()
   | IF (_pos, _cond, t, f) ->
        List.iter (checkuse'statement ctx mangledname) t;
        List.iter (checkuse'statement ctx mangledname) f
   | USE (pos, insn, args, ops, resolvedinsn) ->
        let ty'args = List.map exprtype args in
        let ty'ops = List.map exprtype ops in
        checkuse'use ctx mangledname pos insn ty'args ty'ops resolvedinsn
   | EMIT _ -> ()
   | HOOK _ -> ()
   | WARN _ -> ()

let checkuse'expansion ctx mangledname (_pos, _guard, block) =
   List.iter (checkuse'statement ctx mangledname) block

let checkuse'macro ctx (mac : macro) =
   List.iter (checkuse'expansion ctx mac.mangledname) mac.expansions

(*
 * If secondary, the expansion in opmatch.def was implicit. In this
 * case nothing can refer to this object directly so it can't be a
 * recursive call. Otherwise, it might be recursive and we need to
 * check that.
 *
 * Either way the callee, whatever it is, must exist.
 *
 * See the comment in check'instruction (above) for further notes on
 * what secondary means. (and note, XXX, that specargs = [] isn't the
 * right test but it's what we have for now.)
 *)
let checkuse'instruction ctx (insn : instruction) =
   let pos = insn.definedat in
   let callee = insn.encoder in
   let tyargs = [] in
   let tyops = insn.operands_int in
   let callee_mangled = insn.encoder_mangled in

   match scope_get callee_mangled ctx.allinsns with
        None ->
           no'use ctx pos callee tyargs tyops callee_mangled
      | Some q ->
           checkuse'usecall ctx pos tyargs tyops q

let checkuse'spec ctx (spec : spec) =
   List.iter (checkuse'macro ctx) spec.macros;
   List.iter (checkuse'instruction ctx) spec.instructions


(**************************************************************)
(* consistency check on field positioning *)

(*
 * Each field must appear at the same bit position in each form it
 * appears in.
 *)

let typewidth spec ty =
   let fail () =
      Util.crash ("typecheck: Field has illegal type " ^
			 dump'typename ty)
   in
   match ty with
        WIDTHTYPE ("int", n) -> n
      | WIDTHTYPE ("uint", n) -> n
      | WIDTHTYPE ("zeros", n) -> n
      | WIDTHTYPE ("ones", n) -> n
      | PLAINTYPE ename -> begin
           try
              let { width; _ } = Types.StringMap.find ename spec.enums in
              width
           with Not_found ->
	      (* Not an enum *)
              fail ()
        end
      | _ -> fail ()

let fieldwidth (spec : spec) fieldname =
   try
      let {ty; _} : field = Types.StringMap.find fieldname spec.fields in
      typewidth spec ty
   with Not_found ->
      (* The basic checking pass is supposed to prevent this case *)
      Util.crash ("typecheck: Nonexistent field " ^ fieldname ^
                  " in check_field_positions")

let check_field_positions s =
   let dead = ref false in
   let seenpositions = ref Types.StringMap.empty in
   let visitfield formname formpos bitpos fieldname =
      try
         let info = Types.StringMap.find fieldname !seenpositions in
         let (lastform, lastformpos, lastbitpos) = info in
         if bitpos <> lastbitpos then begin
            Pos.sayat formpos ("Inconsistent field positioning: field " ^
                            fieldname ^ " appears at bit position " ^
                            string_of_int bitpos ^ " of form " ^ formname ^
                            " but also at bit position " ^
                            string_of_int lastbitpos ^ " of form " ^
                            lastform);
            Pos.sayat lastformpos ("Declaration of " ^ lastform ^ " is here");
            dead := true
         end
         else ()
      with Not_found ->
         let info = (formname, formpos, bitpos) in
         seenpositions := Types.StringMap.add fieldname info !seenpositions
   in
   let visitform _ { name; definedat; fields; } =
      let dovisitfield bitpos fieldname =
         visitfield name definedat bitpos fieldname;
         let width = fieldwidth s fieldname in
         bitpos + width
      in
      let _ = List.fold_left dovisitfield 0 fields in
      ()
   in
   Types.StringMap.iter visitform s.forms;
   if !dead then
      Util.die ()
   else ()

(**************************************************************)
(* callback hooks for common typechecker code *)

let lookup_aliastype _ctx _name =
   None

let lookup_type ctx name =
   scope_get name ctx.alltypes 

let lookup_var ctx name =
   scope_get name ctx.allvars

let lookup_modifier ctx name =
   try
      let m = Types.StringMap.find name ctx.spec.modifiers in
      Some (m.argtype, m.resulttype)
   with Not_found -> None

(**************************************************************)
(* top level *)

let typecheck spec =
   (* basic checks first *)
   let ctx = newcontext spec in
   let callbacks = {
      TC.lookup_aliastype = lookup_aliastype ctx;
      TC.lookup_type = lookup_type ctx;
      TC.lookup_var = lookup_var ctx;
      TC.lookup_modifier = lookup_modifier ctx;
   } in
   TC.setcallbacks ctx.tcctx callbacks;

   let builtinpos = Pos.builtin in
   let buildintype haswidth name =
      scope_add name (builtinpos, haswidth, []) ctx.alltypes
   in
   Types.StringSet.iter (buildintype false) builtin_plaintypes;
   Types.StringSet.iter (buildintype true) builtin_argtypes;

   scope_add "true" (builtinpos, booltype) ctx.allvars;
   scope_add "false" (builtinpos, booltype) ctx.allvars;
   let addrtype = EXPRTYPE (WIDTHTYPE ("uint", spec.addresswidth)) in
   scope_add "." (builtinpos, addrtype) ctx.allvars;

   let pcunittype = WIDTHTYPE ("uint", spec.pcunitwidth) in
   check'typename ctx builtinpos(*XXX*) pcunittype;

   Types.StringMap.iter (check'enum ctx) spec.enums;
   Types.StringMap.iter (check'compoundtype ctx) spec.compoundtypes;
   Types.StringMap.iter (check'operandtag ctx) spec.operandtags;

   Types.StringMap.iter (check'field ctx) spec.fields;
   Types.StringMap.iter (check'form ctx) spec.forms;

   Types.StringMap.iter (check'subenum ctx) spec.subenums;

   List.iter (check'encoding ctx) spec.encodings;
   List.iter (check'macro ctx) spec.macros;
   List.iter (check'instruction ctx) spec.instructions;

   (* allow consistency checks to rely on well-formedness *)
   Util.checkfail();

   (* consistency checks *)
   checkuse'spec ctx spec;
   check_field_positions spec

