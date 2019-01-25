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

module B = Basetree
module E = Exprtree
module N = Encodingtree
module H = Hazardtree

(*
 * Fill in stuff in the hazardinfo tree based on information from the
 * encodings tree.
 *
 * Specifically this figures out which identifiers in the hazardinfo
 * tree are field names and which aren't, as that information is
 * critical to the analysis of instruction predicates that needs to be
 * shared between genhazmachine and genencoding.
 *
 * It also rejects undefined identifiers, prohibits the use of field
 * names in guard expressions, and figures out the arguments of
 * predicates.
 *)

(**************************************************************)
(* context *)

type wheretype = IN_GUARD | IN_MATCHER | IN_PRED

type context = {
   globals: Pos.pos Types.StringMap.t ref;
   fields: Pos.pos Types.StringMap.t ref;
   preds: Pos.pos Types.StringMap.t ref;
   assignedvars: Pos.pos Types.StringMap.t ref;
   args: Pos.pos Types.StringMap.t ref;
   predargs: (Pos.pos Types.StringMap.t) Types.StringMap.t ref;
}

let newctx () = {
   globals = ref Types.StringMap.empty;
   fields = ref Types.StringMap.empty;
   preds = ref Types.StringMap.empty;
   assignedvars = ref Types.StringMap.empty;
   args = ref Types.StringMap.empty;
   predargs = ref Types.StringMap.empty;
}

let ctx_clearassignedvars ctx =
   ctx.assignedvars := Types.StringMap.empty

let ctx_clearargs ctx =
   ctx.args := Types.StringMap.empty

let ctx_addglobal ctx name pos =
   ctx.globals := Types.StringMap.add name pos !(ctx.globals)

let ctx_addfield ctx name pos =
   ctx.fields := Types.StringMap.add name pos !(ctx.fields)

let ctx_addpred ctx name pos =
   ctx.preds := Types.StringMap.add name pos !(ctx.preds)

let ctx_addassignedvar ctx name pos =
   ctx.assignedvars := Types.StringMap.add name pos !(ctx.assignedvars)

let ctx_addarg ctx name pos =
   ctx.args := Types.StringMap.add name pos !(ctx.args)

let ctx_findname ctx name =
   try
      Some (Types.StringMap.find name !(ctx.assignedvars))
   with Not_found -> try
      Some (Types.StringMap.find name !(ctx.preds))
   with Not_found -> try
      Some (Types.StringMap.find name !(ctx.fields))
   with Not_found -> try
      Some (Types.StringMap.find name !(ctx.globals))
   with Not_found ->
      None


(**************************************************************)
(* registers materials *)

let base'decl ctx d =
   match d with
        B.ENUMTYPE (_pos, _name, _width, members) ->
           (* add the enum constants *)
           let addmember (mpos, mname, _optval) =
              if String.get mname 0 = '_' then ()
              else ctx_addglobal ctx mname mpos
           in
           List.iter addmember members
      | _ -> ()


(**************************************************************)
(* encoding materials *)

let enc'decl ctx d = match d with
     N.FIELD (pos, name, _ty, _relinfo) ->
        ctx_addfield ctx name pos
   | N.ENUMFIELD (pos, name, N.ENUMTYPE (_tpos, _width, members), _relinfo) ->
        ctx_addfield ctx name pos;
        let addmember (mpos, name, _optval) =
           if String.get name 0 = '_' then ()
           else ctx_addglobal ctx name mpos
        in
        List.iter addmember members
   | N.SUBENUM (pos, name, _selected) ->
        ctx_addglobal ctx name pos
   | N.SUBENUMEXPR _ ->
        (* removed by encodingcheck *)
        Util.crash "hazresolve: enc'decl: leftover SUBENUMEXPR"
   | N.FORM _ -> ()

(**************************************************************)
(* variable references (the real work for expressions) *)

let is_global ctx name =
   Types.StringMap.mem name !(ctx.globals)

let is_field ctx name =
   Types.StringMap.mem name !(ctx.fields)

let is_pred ctx name =
   Types.StringMap.mem name !(ctx.preds)

let is_assignedvar ctx name =
   Types.StringMap.mem name !(ctx.assignedvars)

let badvar pos name =
   Pos.sayat pos ("Undefined symbol " ^ name);
   Util.fail ()

(*
 * Check that a reference to a predicate occurs in a context where the
 * args it expects are bound. (They are passed implicitly by name. And
 * since globals, fields, and predicates are resolved already, these
 * references must be satisfied by assignedvars.)
 *)
let check_predicate_use ctx pos name =
   (* should always exist; let it crash if missing *)
   let args = Types.StringMap.find name !(ctx.predargs) in
   let check_one_var var varusepos =
      if is_assignedvar ctx var then ()
      else if is_pred ctx var then begin
         Pos.sayat pos ("Cannot use predicate " ^ var ^
                        " in predicate " ^ name);
         Pos.sayat pos ("Fix by adjusting declaration order of predicates");
         Util.fail ()
      end else begin
         Pos.sayat pos ("Cannot use predicate " ^ name ^ " in this context");
         Pos.sayat varusepos ("It uses the variable " ^ var ^
                              " which is not bound.");
         Util.fail ()
      end
   in
   Types.StringMap.iter check_one_var args

let do'readvar ctx where pos name =
   match where with
        IN_GUARD ->
           (* guard expression: globals only *)
           if is_global ctx name then ()
           else badvar pos name
      | IN_MATCHER ->
           (* matcher context: globals, fields, predicates, assignedvars *)
           if is_assignedvar ctx name then ()
           else if is_pred ctx name then
              check_predicate_use ctx pos name
           else if is_field ctx name then ()
           else if is_global ctx name then ()
           else badvar pos name
      | IN_PRED ->
           (* predicate: globals, fields, other predicates *)
           (* also collect instead of rejecting unbound vars *)
           if is_pred ctx name then ()
           else if is_field ctx name then ()
           else if is_global ctx name then ()
           else ctx_addarg ctx name pos


(**************************************************************)
(* main recursive pass on hazard elements *)

(* this itself is purely a recursive boilerplate *)
let rec do'expr ctx where e = match e with
     E.UOP (pos, op, e1) ->
        let e1 = do'expr ctx where e1 in
        E.UOP (pos, op, e1)
   | E.BOP (pos, e1, op, e2) ->
        let e1 = do'expr ctx where e1 in
        let e2 = do'expr ctx where e2 in
        E.BOP (pos, e1, op, e2)
   | E.FITS (pos, e1, argty) ->
        let e1 = do'expr ctx where e1 in
        E.FITS (pos, e1, argty)
   | E.MODE (pos, modename) ->
        E.MODE (pos, modename)
   | E.READVAR (pos, name) ->
        do'readvar ctx where pos name;
        E.READVAR (pos, name)
   | E.READMEMBER (pos, e1, name) ->
        let e1 = do'expr ctx where e1 in
        E.READMEMBER (pos, e1, name)
   | E.BOOLCONSTANT (pos, x) ->
        E.BOOLCONSTANT (pos, x)
   | E.NUMCONSTANT (pos, x) ->
        E.NUMCONSTANT (pos, x)
   | E.STRCONSTANT (pos, x) ->
        E.STRCONSTANT (pos, x)
   | E.HERE pos ->
        E.HERE pos
   | E.LIST (pos, es) ->
        let es = List.map (do'expr ctx where) es in
        E.LIST (pos, es)
   | E.MODIFIER (pos, name, es) ->
        let es = List.map (do'expr ctx where) es in
        E.MODIFIER (pos, name, es)
   | E.PACK (pos, name, es) ->
        let es = List.map (do'expr ctx where) es in
        E.PACK (pos, name, es)
   | E.CAST (pos, newty, oldty, e1) ->
        let e1 = do'expr ctx where e1 in
        E.CAST (pos, newty, oldty, e1)
   | E.ANNOTATE (pos, ty, e1) ->
        let e1 = do'expr ctx where e1 in
        E.ANNOTATE (pos, ty, e1)

let do'predicatedecl ctx name { H.definedat; H.args; (*H.afields;*) H.e; } =
   ignore (args);
   ctx_clearargs ctx;
   let e = do'expr ctx IN_PRED e in
   let args = !(ctx.args) in
   ctx_clearargs ctx;
   ctx_addpred ctx name definedat;
   ctx.predargs := Types.StringMap.add name args !(ctx.predargs);
   { H.definedat; H.args; H.afields = Types.StringSet.empty; H.e; }

let do'trigger ctx definedat trigger = match trigger with
     H.P_BYEXPR _ ->
        (* hazardcheck removes these *)
        Pos.crashat definedat "hazresolve: do'trigger: leftover expr"
   | H.P_BYNAME name ->
        do'readvar ctx IN_MATCHER definedat name;
        H.P_BYNAME name

let rec do'condition ctx definedat cond = match cond with
     H.COND_ANY -> ()
   | H.COND_PREDNAME name ->
        do'readvar ctx IN_MATCHER definedat name
   | H.COND_PREDEXPR _ ->
        (* hazardcheck removes these *)
        Pos.crashat definedat "hazresolve: do'condition: leftover expr"
   | H.COND_SEQ (c1, c2) ->
        do'condition ctx definedat c1;
        do'condition ctx definedat c2
   | H.COND_ALT (c1, c2) ->
        do'condition ctx definedat c1;
        do'condition ctx definedat c2
   | H.COND_OPT c1 ->
        do'condition ctx definedat c1
   | H.COND_PLUS c1 ->
        do'condition ctx definedat c1

let do'assignment ctx (H.ASSIGN (pos, name, e)) =
   let e = do'expr ctx IN_MATCHER e in
   begin
   match ctx_findname ctx name with
        None -> ()
      | Some prevpos ->
           Pos.sayat pos ("Warning: declaration of " ^ name ^
                          " shadows a previous binding");
           Pos.sayat prevpos ("Previous binding is here")
   end;      
   ctx_addassignedvar ctx name pos;
   H.ASSIGN (pos, name, e)

let do'matcher ctx definedat m =
   let { H.guard; H.assignments; H.trigger; H.condition; } = m in
   ctx_clearassignedvars ctx;
   let guard = do'expr ctx IN_GUARD guard in
   let assignments = List.map (do'assignment ctx) assignments in
   let trigger = do'trigger ctx definedat trigger in
   do'condition ctx definedat condition;
   ctx_clearassignedvars ctx;
   { H.guard; H.assignments; H.trigger; H.condition; }

let do'hazard ctx { H.name; H.definedat; H.desc; H.m; } =
   let m = do'matcher ctx definedat m in
   { H.name; H.definedat; H.desc; H.m; }

let do'transfer ctx { H.definedat; H.m; H.result; } =
   let m = do'matcher ctx definedat m in
   { H.definedat; H.m; H.result; }

(**************************************************************)
(* afields *)

(*
 * standalone function to extract the fields used by an expression,
 * given a map that defines which symbols are fields. (what the map
 * maps to is irrelevant)
 *
 * XXX it would be nice to use this to populate cfields as well as
 * afields, but cfields needs to be populated after predicate
 * splitting and thus happens on Exprrep instead of Exprtree.
 *
 * This pass could be done on Exprrep but then we don't have a
 * common representation for either the assignments or the predicate
 * declarations, and the logic needs to be shared between genencoding
 * and genhazmachine.
 *
 * (The same is true when populating cfields, but all that requires
 * is a fold over the split predicate's expression list; it doesn't
 * need to touch matchers.)
 *
 * Blah, this is unsatisfactory; maybe it will become clearer how to
 * do things cleanly in the future when the common representation stuff
 * is structured better, and we can, say, make a common representation
 * of the hazard material that uses Exprrep and is still shared between
 * genhazmachine and genencoding. FUTURE...
 *
 * Adds the fields to the set passed in and returns a new set. This
 * avoids needing to union the sets all over everywhere.
 *)

let rec collect_fields fmap fields e =
   let one e1 =
      collect_fields fmap fields e1
   in
   let two e1 e2 =
      let fields' = collect_fields fmap fields e1 in
      collect_fields fmap fields' e2
   in
   let many es =
      List.fold_left (collect_fields fmap) fields es
   in
   match e with
     E.UOP (_pos, _op, e1) -> one e1
   | E.BOP (_pos, e1, _op, e2) -> two e1 e2
   | E.FITS (_pos, e1, _argty) -> one e1
   | E.MODE _ -> fields
   | E.READVAR (_pos, name) -> begin
        try
           ignore (Types.StringMap.find name fmap);
           Types.StringSet.add name fields
        with Not_found -> fields
     end
   | E.READMEMBER (_pos, e1, _name) -> one e1
   | E.BOOLCONSTANT _ -> fields
   | E.NUMCONSTANT _ -> fields
   | E.STRCONSTANT _ -> fields
   | E.HERE _ -> fields
   | E.LIST (_pos, es) -> many es
   | E.MODIFIER (_pos, _name, es) -> many es
   | E.PACK (_pos, _name, es) -> many es
   | E.CAST (_pos, _nty, _oty, e1) -> one e1
   | E.ANNOTATE (_pos, _ty, e1) -> one e1

(*
 * Find the instruction fields needed to evaluate a matcher's
 * assignments. Return an updated afieldmap.
 * (afieldmap is predicate name -> identifier set)
 *)

let find_afields ctx afieldmap (m: H.matcher) =
   let trigger = match m.H.trigger with
        H.P_BYNAME n -> n
      | H.P_BYEXPR _ -> Util.crash "hazresolve: find_afields: P_BYEXPR"
   in
   let afields =
      try
          Types.StringMap.find trigger afieldmap
      with Not_found -> Types.StringSet.empty
   in

   let scan_assignment afields' (H.ASSIGN (_pos, _var, e)) =
      collect_fields !(ctx.fields) afields' e
   in
   let afields = List.fold_left scan_assignment afields m.H.assignments in
   Types.StringMap.add trigger afields afieldmap

(*
 * Update the afields of a predicate declaration.
 *)
let place_afields afieldmap name pred =
   let afields =
      (* will be nothing on file if not used as a trigger *)
      try
         Types.StringMap.find name afieldmap
      with Not_found -> Types.StringSet.empty
   in
   { pred with H.afields; }

(**************************************************************)
(* interface *)

let hazresolve hazinfo baseinfo encinfo =
   let ctx = newctx () in
   List.iter (base'decl ctx) baseinfo;
   List.iter (enc'decl ctx) encinfo;

   let { H.predicates; H.predorder; H.hazards; H.transfers; } = hazinfo in

   let predicates =
      Types.stringmap_mapi_inorder
         (do'predicatedecl ctx) predicates predorder
   in
   let hazards = List.map (do'hazard ctx) hazards in
   let transfers = List.map (do'transfer ctx) transfers in

   let predicates =
      let matchers =
         (List.map (fun (h: H.hazard) -> h.H.m) hazards) @
         (List.map (fun (t: H.transfer) -> t.H.m) transfers)
      in
      let afieldmap =
         List.fold_left (find_afields ctx) Types.StringMap.empty matchers
      in
      Types.StringMap.mapi (place_afields afieldmap) predicates
   in

   { H.predicates; H.predorder; H.hazards; H.transfers; }
