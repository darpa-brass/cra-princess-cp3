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

module G = Gcode
module TE = Typeemit
module EE = Expremit
open Rep

(**************************************************************)
(* code generation bits *)

let mk_type pos ty = TE.emit'type pos ty

(*
 * Expressions for the elements of enum labelstateresult
 *)
let type'labelstateresult = G.ENUMTYPE "labelstateresult"
let eLS_SAFE    = G.READVAR (type'labelstateresult, "LS_SAFE")
let eLS_UNSAFE  = G.READVAR (type'labelstateresult, "LS_UNSAFE")
let eLS_PENDING = G.READVAR (type'labelstateresult, "LS_PENDING")
let eLS_SPLICE  = G.READVAR (type'labelstateresult, "LS_SPLICE")
let eLS_FORK    = G.READVAR (type'labelstateresult, "LS_FORK")
let eLS_DECIDE p =
   G.READVAR (type'labelstateresult, "LS_DECIDE_" ^ Upcase.upcase p)

(*
 * Other types in the Gcode
 *)
let type'label = G.STRUCTTYPE "label"
let type'labelptr = G.POINTER type'label
let type'labelstate = G.STRUCTTYPE "labelstate"
let type'decide p = G.STRUCTTYPE (p ^ "_decide")
let type'fork = G.STRUCTTYPE "fork"
let type'labelhazinfo = G.STRUCTTYPE "labelhazinfo"
let type'specstate = G.STRUCTTYPE "specstate"
let type'concstate = G.STRUCTTYPE "concstate"
let type'specstatearray = G.STRUCTTYPE "specstatearray"
let type'concstatearray = G.STRUCTTYPE "concstatearray"

let type'labelstateptr =   G.POINTER type'labelstate
let type'decideptr p =     G.POINTER (type'decide p)
let type'forkptr =         G.POINTER type'fork
let type'labelhazinfoptr = G.POINTER type'labelhazinfo
let type'specstateptr =    G.POINTER type'specstate
let type'concstateptr =    G.POINTER type'concstate
let type'specstatearrayptr = G.POINTER type'specstatearray
let type'concstatearrayptr = G.POINTER type'concstatearray

(*
 * Accessors for fields of types in the Gcode
 *)

(* labelstate *)

let labelstate'read'result from =
   G.READFIELD (type'labelstateresult, from, "result")
let labelstate'read'u from =
   G.READFIELD (G.UNIONTYPE "", from, "u")
let labelstate'read'u_unsafe from =
   G.READFIELD (G.STRUCTTYPE "", labelstate'read'u from, "unsafe")
let labelstate'read'u_unsafe_failurelinenum from =
   G.READFIELD (G.INT, labelstate'read'u_unsafe from, "failure_linenum")
let labelstate'read'u_pending from =
   G.READFIELD (G.STRUCTTYPE "", labelstate'read'u from, "pending")
let labelstate'read'u_pending_curstate from =
   G.READFIELD (G.UINT, labelstate'read'u_pending from, "curstate")
let labelstate'read'u_splice from =
   G.READFIELD (type'labelstateptr, labelstate'read'u from, "splice")
let labelstate'read'u_fork from =
   G.READFIELD (type'forkptr, labelstate'read'u from, "fork")
let labelstate'read'u_decide from p =
   G.READFIELD (type'decideptr p, labelstate'read'u from, "decide_" ^ p)

let labelstate'write'result from =
   G.WRITEFIELD (type'labelstateresult, from, "result")
let labelstate'write'u_unsafe_failurelinenum from =
   G.WRITEFIELD (G.INT, labelstate'read'u_unsafe from, "failure_linenum")
let labelstate'write'u_pending_curstate from =
   G.WRITEFIELD (G.UINT, labelstate'read'u_pending from, "curstate")
let labelstate'write'u_splice from =
   G.WRITEFIELD (type'labelstateptr, labelstate'read'u from, "splice")
let labelstate'write'u_fork from =
   G.WRITEFIELD (type'forkptr, labelstate'read'u from, "fork")
(*let labelstate'write'u_decide from p =
   G.WRITEFIELD (type'decideptr p, labelstate'read'u from, "decide_" ^ p) *)

(* *_decide *)
let decide'read'iftrue from =
   G.READFIELD (type'labelstate, from, "iftrue")
let decide'read'iffalse from =
   G.READFIELD (type'labelstate, from, "iffalse")
let decide'read'data from p =
   G.READFIELD (G.STRUCTTYPE (p ^ "_cstash"), from, "data")
let decide'read'iftrueptr from =
   G.addrof type'labelstateptr (decide'read'iftrue from)
let decide'read'iffalseptr from =
   G.addrof type'labelstateptr (decide'read'iffalse from)
let decide'read'dataptr from p =
   G.addrof (G.POINTER (G.STRUCTTYPE (p ^ "_cstash")))
            (decide'read'data from p)

(* fork *)
let fork'read'basecase from = G.READFIELD (type'labelstate, from, "basecase")
let fork'read'altcase from =  G.READFIELD (type'labelstate, from, "altcase")
let fork'read'basecaseptr from =
   G.addrof type'labelstateptr (fork'read'basecase from)
let fork'read'altcaseptr from =
   G.addrof type'labelstateptr (fork'read'altcase from)
(*let fork'write'jumpid from = G.WRITEFIELD (G.UINT, from, "jumpid")*)

(* labelhazinfo *)
let labelhazinfo'read'states from id =
   let name = "m" ^ string_of_int id ^ "_states" in
   G.READFIELD (G.ARRAY (type'labelstate, ""), from, name)
let labelhazinfo'read'states_i from id ix =
   G.READARRAY (type'labelstate, labelhazinfo'read'states from id, ix)

(* specstate *)
let specstate'read'matcherid from = G.READFIELD (G.UINT, from, "matcherid")
let specstate'read'ptr from = G.READFIELD (type'labelstateptr, from, "ptr")
let specstate'write'matcherid from = G.WRITEFIELD (G.UINT, from, "matcherid")
let specstate'write'ptr from = G.WRITEFIELD (type'labelstateptr, from, "ptr")

(* concstate *)
let concstate'read'startline from = G.READFIELD (G.INT, from, "startline")
let concstate'read'matcherid from = G.READFIELD (G.UINT, from, "matcherid")
let concstate'read'state from     = G.READFIELD (G.UINT, from, "state")
let concstate'read'deferline from = G.READFIELD (G.UINT, from, "deferline")
let concstate'read'deferinfo from =
   G.READFIELD (type'labelhazinfoptr, from, "deferinfo")
let concstate'write'startline from = G.WRITEFIELD (G.INT, from, "startline")
let concstate'write'matcherid from = G.WRITEFIELD (G.UINT, from, "matcherid")
let concstate'write'state from     = G.WRITEFIELD (G.UINT, from, "state")
let concstate'write'deferline from = G.WRITEFIELD (G.UINT, from, "deferline")
let concstate'write'deferinfo from =
   G.WRITEFIELD (type'labelhazinfoptr, from, "deferinfo")

(*
 * Wrappers for the array operations from array.h
 *)

type ainfo = { aname: string; aty: G.gtype; ety: G.gtype; }
let array_add info arr x = G.voidcall (info.aname ^ "_add") [arr; x]
let array_get info arr ix = G.call info.ety (info.aname ^ "_get") [arr; ix]
let array_num info arr = G.call G.UINT (info.aname ^ "_num") [arr]
let array_setsize info arr n = G.voidcall (info.aname ^ "_setsize") [arr; n]
let array_remunsorted info arr ix =
   G.voidcall (info.aname ^ "_remunsorted") [arr; ix]

let specstatearray_info = {
   aname="specstatearray"; aty=type'specstatearray; ety=type'specstate;
}
(*let specstatearray_add = array_add specstatearray_info*)
let specstatearray_get = array_get specstatearray_info
let specstatearray_num = array_num specstatearray_info
let specstatearray_setsize = array_setsize specstatearray_info
let specstatearray_remunsorted = array_remunsorted specstatearray_info

let concstatearray_info = {
   aname="concstatearray"; aty=type'concstatearray; ety=type'concstate;
}
let concstatearray_add = array_add concstatearray_info
let concstatearray_get = array_get concstatearray_info
let concstatearray_num = array_num concstatearray_info
let concstatearray_setsize = array_setsize concstatearray_info
let concstatearray_remunsorted = array_remunsorted concstatearray_info

(*
 * The (file-static) state in the Gcode.
 * Or at least, that of it worth abbreviating.
 *)

let active_specstates =
   let arr = G.READVAR (type'specstatearray, "active_specstates") in
   G.addrof type'specstatearrayptr arr

let active_concstates =
   let arr = G.READVAR (type'concstatearray, "active_concstates") in
   G.addrof type'concstatearrayptr arr

let deferred_concstates =
   let arr = G.READVAR (type'concstatearray, "deferred_concstates") in
   G.addrof type'concstatearrayptr arr


(*
 * Generate a loop over all the states in a matcher.
 * (This generates the loop head.)
 *)
let mk_states_loop m varname body =
   let mname = "M" ^ string_of_int m.id in

   let i'read = G.READVAR (G.UINT, varname) in
   let i'write = G.WRITEVAR (G.UINT, varname) in

   let numstates = G.READVAR (G.UINT, mname ^ "_NUMSTATES") in
   let i0 = G.ASSIGN (i'write, G.zero G.UINT) in
   let ilt = G.lt i'read numstates in
   let iinc = G.ASSIGN (i'write, G.add G.UINT i'read (G.one G.UINT)) in
   G.LOOP (i0, G.skip, ilt, body, iinc)

(*
 * Generate a loop over a resizeable array.
 *)
let mk_array_loop donum arr varname body =
   let read'i = G.READVAR (G.UINT, varname) in
   let write'i = G.WRITEVAR (G.UINT, varname) in

   let i0 = G.ASSIGN (write'i, G.zero G.UINT) in
   let ilt = G.lt read'i (donum arr) in
   let iinc = G.incr G.UINT varname in
   G.LOOP (i0, G.skip, ilt, body, iinc)

let mk_specstates_loop = mk_array_loop specstatearray_num active_specstates
let mk_concstates_loop = mk_array_loop concstatearray_num active_concstates
let mk_deferred_loop = mk_array_loop concstatearray_num deferred_concstates
   

(**************************************************************)
(* spec handling bits *)

(*
 * Get the list of all matchers in the form (ishaz, m, dfa).
 *
 * Since for ML declaration reasons the dfas can't be stored in Rep
 * this hides a bunch of annoyances.
 *
 * Most or all of the matcher-based code generation functions in
 * here use the results from this function.
 *)
let getmatchers spec haz_dfas xfer_dfas =
   let hms = List.map (fun (h: hazard) -> h.m) spec.hazards in
   let tms = List.map (fun (t: transfer) -> t.m) spec.transfers in 
   let hinfo = Util.zip hms haz_dfas in
   let tinfo = Util.zip tms xfer_dfas in
   let hinfo = List.map (fun (m, dfa) -> (true, m, dfa)) hinfo in
   let tinfo = List.map (fun (m, dfa) -> (false, m, dfa)) tinfo in
   hinfo @ tinfo

(*
 * Map over all predicates, as a list, in order.
 *)
let map_predicates f spec =
   List.map f (Types.stringmap_bindings_inorder spec.predicates spec.predorder)

(*
 * Map over all predicates where args is nonempty, as a list, in order.
 *)
let map_arg_predicates f spec =
   let f' pred =
      let (_, { args; }) = pred in
      if Types.StringMap.is_empty args then []
      else [f pred]
   in
   List.concat (map_predicates f' spec)


(**************************************************************)
(* defines/enums *)

(*
 * For each matcher, #define its number of states in the form
 * #define M0_NUMSTATES 3
 *)
let mknumstates matchers =
   let mkone (_ishaz, m, dfa) =
      let numstates = Rx.dfa_numstates dfa in
      let sym = "M" ^ string_of_int m.id ^ "_NUMSTATES" in
      G.DEFINE (sym, Some (G.INTCONSTANT (G.UINT, string_of_int numstates)))
   in
   List.map mkone matchers


(**************************************************************)
(* types *)

(*
 * For each predicate, define its "tstash", "astash", and "cstash"
 * structs.
 *
 * There are three sets of instruction field values that we need:
 *    - values computed from the trigger instruction and assigned to
 *      temporary variables (assignedvars) for later reference;
 *    - values from the current instruction needed to produce the
 *      assignedvars;
 *    - values from the current instruction to evaluate a predicate.
 *
 * These are the tstash, astash, and cstash values respectively and
 * the corresponding structs are set up with fields to match.
 *
 * Ideally values that appear in both astash and cstash would not
 * be produced or stored twice, but at the moment this optimization
 * is not made. (XXX)
 *)

let mkstashes spec =
   let mkone (name, { definedat; args; afields; cfields; (*es;*) }) =
      let get_t (argname, (_argpos, argty)) =
            (mk_type definedat argty, "t_" ^ argname)
      in
      let get_ac ac (argname, argty) =
            (mk_type definedat argty, ac ^ "_" ^ argname)
      in
      let get_a = get_ac "a" in
      let get_c = get_ac "c" in

      let members_t = List.map get_t (Types.StringMap.bindings args) in
      let members_a = List.map get_a (Types.StringMap.bindings afields) in
      let members_c = List.map get_c (Types.StringMap.bindings cfields) in

      let mkstruct tac members =
         if members = [] then []
         else [G.STRUCTDECL (name ^ "_" ^ tac ^ "stash", members)]
      in
      let tstash = mkstruct "t" members_t in
      let astash = mkstruct "a" members_a in
      let cstash = mkstruct "c" members_c in

      List.concat [tstash; astash; cstash]
   in
   List.concat (map_predicates mkone spec)

(*
 * The labelstate structure used for speculatively checking forward
 * from a label. Each labelstate instance represents the safety of
 * one start state at the label, or one derived case of possibly
 * many arising from the same start state.
 *)

let mklabelstate spec =
   let mkenumentry (name, _) =
      ("LS_DECIDE_" ^ Upcase.upcase name, None, None)
   in
   let enummembers = [
      ("LS_SAFE", None, None);
      ("LS_UNSAFE", None, None);
      ("LS_PENDING", None, None);
      ("LS_SPLICE", None, None);
      ("LS_FORK", None, None);
   ] @ map_predicates mkenumentry spec
   in
   let enum = G.ENUMDECL ("labelstateresult", enummembers) in

   let mkunionentry (name, _) =
      (G.POINTER (G.STRUCTTYPE (name ^ "_decide")), "decide_" ^ name)
   in
   let unionmembers = [
      (G.ANONSTRUCT [(G.INT, "failure_linenum")], "unsafe");
      (G.ANONSTRUCT [(G.UINT, "curstate")], "pending");
      (type'labelstateptr, "splice");
      (type'forkptr, "fork");
   ] @ map_predicates mkunionentry spec
   in
   let structmembers = [
      (G.ENUMTYPE "labelstateresult", "result");
      (G.ANONUNION unionmembers, "u");
   ] in
   [enum; G.STRUCTDECL ("labelstate", structmembers)]
      
(*
 * The decide structures are used to make up the decision tree used
 * when testing an instruction predicate speculatively returns an
 * indeterminate result.
 *
 * There is one for each predicate. This is not strictly necessary;
 * but because it's in generated code, the cost is minimal, and it
 * avoids using C memory placement tricks that our output
 * representation doesn't really cater to.
 *)

let mkdecides spec =
   let mkone (name, { cfields; }) =
      let members = [
         (G.STRUCTTYPE "labelstate", "iftrue");
         (G.STRUCTTYPE "labelstate", "iffalse");
      ] in
      (* add the cstash only if it exists *)
      let members =
         if Types.StringMap.is_empty cfields then members
         else members @ [G.STRUCTTYPE (name ^ "_cstash"), "data"]
      in
      G.STRUCTDECL (name ^ "_decide", members)
   in
   map_predicates mkone spec

(*
 * The fork structure is used for dealing with when branch or jump
 * handling requires multiple simultaneous cases.
 *)
let mkfork () =
   let members = [
      (*(G.UINT, "jumpid");*)
      (G.STRUCTTYPE "labelstate", "basecase");
      (G.STRUCTTYPE "labelstate", "altcase");
   ] in
   G.STRUCTDECL ("fork", members)

(*
 * The labelhazinfo struct is attached to each (assembler) label.
 *)
let mklabelhazinfo matchers =
   let mkentry (_ishaz, (m: matcher), _dfa) =
      let mname = "m" ^ string_of_int m.id in
      let mNAME = "M" ^ string_of_int m.id in
      (*let numstates = G.READVAR (G.UINT, mname ^ "_NUMSTATES") in*)
      let numstates = mNAME ^ "_NUMSTATES" in
      (G.ARRAY (G.STRUCTTYPE "labelstate", numstates), mname ^ "_states")
   in
   (* for now at least we don't speculate about branches *)
   let trymkentry (ishaz, m, dfa) =
      if ishaz then [mkentry (ishaz, m, dfa)]
      else []
   in
   let members = List.concat (List.map trymkentry matchers) in
   G.STRUCTDECL ("labelhazinfo", members)

(*
 * The specstate struct represents one current speculative state.
 *)

let mkspecstate () =
   let members = [
      (G.UINT, "matcherid");
      (type'labelstateptr, "ptr");
      (*(G.BOOL, "nullifying");*)
   ] in
   G.STRUCTDECL ("specstate", members)

(*
 * The concstate struct represents one current concrete state.
 *)

let mkconcstate () =
   let members = [
      (G.INT, "startline");
      (G.UINT, "matcherid");
      (G.UINT, "state");
      (*(G.BOOL, "nullifying");*)
      (* the jump (in the input) associated with this state *)
      (* XXX is one sufficient? *)
      (*(G.UINT, "jumpid");*)
      (G.UINT, "deferline");
      (type'labelhazinfoptr, "deferinfo");
   ] in
   G.STRUCTDECL ("concstate", members)

(*
 * Array types.
 *)

let mkarrays () = [
   G.VARARRAYDECL (type'specstateptr, "specstatearray", true);
   G.VARARRAYDECL (type'concstateptr, "concstatearray", true);
]

(**************************************************************)
(* static state *)

(*
 * Static stashes (of each kind) for each argument. These are
 * filled in when instructions are matched and predicates are
 * marked true, then consulted when an instruction is issued.
 *)
let mkstashvars spec =
   let mkone (name, { args; afields; cfields; }) =
      let tname = name ^ "_tstash" in
      let aname = name ^ "_astash" in
      let cname = name ^ "_cstash" in

      let mkdecl name isempty =
         if isempty then []
         else [G.VARDECL (G.STATIC, G.STRUCTTYPE name, name)]
      in
      let tdecl = mkdecl tname (Types.StringMap.is_empty args) in
      let adecl = mkdecl aname (Types.StringMap.is_empty afields) in
      let cdecl = mkdecl cname (Types.StringMap.is_empty cfields) in
      List.concat [tdecl; adecl; cdecl]
   in
   List.concat (map_predicates mkone spec)

(*
 * Flags for remembering predicates that match in the encoding code.
 * For predicates that require further evaluation (testing against
 * assignvars), the flag is called "maybetrue" instead of "istrue".
 * This can be determined by whether the predicate's args list is
 * empty.
 *
 * These flags are set when instructions are matched, then
 * consulted by the state machines when an instruction is issued.
 *)
let mkpredflags spec =
   let mkone (name, { args; }) =
      let flagname =
         if Types.StringMap.is_empty args then name ^ "_istrue"
         else name ^ "_maybetrue"
      in
      let init = G.INITSCALAR (G.boolconst false) in
      G.VARDECL' (G.STATIC, G.BOOL, flagname, init)
   in
   map_predicates mkone spec

(*
 * The current destination label for a branch or jump.
 *)
let mkcurlabel () =
   G.VARDECL (G.STATIC, type'labelptr, "curlabel")

(*
 * The tables of active states, and also the deferred table.
 *)
let mkactive () = [
   G.VARDECL (G.STATIC, G.STRUCTTYPE "specstatearray", "active_specstates");
   G.VARDECL (G.STATIC, G.STRUCTTYPE "concstatearray", "active_concstates");
   G.VARDECL (G.STATIC, G.STRUCTTYPE "concstatearray", "deferred_concstates");
]

(*
 * The jump id counter.
 * XXX notyet
 *)
(*
let mkjump () =
   G.VARDECL (G.STATIC, G.UINT, "nextjumpid")
*)


(**************************************************************)
(* diagnostics *)

let mkreport hazards =
   let funcname = "report_unsafe" in

   let params = [
      (G.INT, "triggered_linenum");
      (G.INT, "failed_linenum");
      (G.UINT, "matcherid");
   ] in
   let read'triggered_linenum = G.READVAR (G.INT, "triggered_linenum") in
   let read'failed_linenum = G.READVAR (G.INT, "failed_linenum") in
   let read'matcherid = G.READVAR (G.UINT, "matcherid") in

   let locals = [
      G.LOCAL (G.constcharptr, "mmsg");
   ] in
   let read'mmsg = G.READVAR (G.constcharptr, "mmsg") in
   let write'mmsg = G.WRITEVAR (G.constcharptr, "mmsg") in

   let mk_case (h: hazard) =
      (G.INTCONSTANT (G.UINT, string_of_int h.m.id), G.BLOCK [
         G.ASSIGN (write'mmsg, G.STRINGCONSTANT h.desc);
         G.BREAK;
      ])
   in
   let defcase =
      G.ASSERT (G.boolconst false)
   in
   let mmsg_cases = List.map mk_case hazards in
   let assignmmsg = G.SWITCH (read'matcherid, mmsg_cases, Some defcase) in

   let fmsg = G.STRINGCONSTANT "This instruction is unsafe:" in
   let mmsgfmt = G.STRINGCONSTANT "%s" in
   let tmsg = G.STRINGCONSTANT "Triggering instruction" in
   let msgs = [
      G.voidcall "file_warn" [read'failed_linenum; fmsg];
      G.voidcall "file_warn" [read'failed_linenum; mmsgfmt; read'mmsg];
      G.voidcall "file_warn" [read'triggered_linenum; tmsg];
   ] in

   let body = locals @ [assignmmsg] @ msgs in
   [
      G.DECLCOMMENT "Failure reporting";
      G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK body);
   ]

(**************************************************************)
(* ops on hazinfo *)

let mkhazinfo_create matchers =
   let funcname = "labelhazinfo_create" in

   let lstype = type'labelstateresult in
   let ls_pending = eLS_PENDING in

   let labelstate'ty = G.STRUCTTYPE "labelstate" in

   let hazinfo'ty = G.POINTER (G.STRUCTTYPE "labelhazinfo") in
   let locals = [
      G.LOCAL (hazinfo'ty, "info");
      G.LOCAL (G.UINT, "i");
   ] in
   let info'read = G.READVAR (hazinfo'ty, "info") in
   let info'write = G.WRITEVAR (hazinfo'ty, "info") in
   let info'readfield ty name = G.READFIELD (ty, info'read, name) in
(*
   let info'writefield ty name = G.WRITEFIELD (ty, info'read, name) in
*)
   let i'read = G.READVAR (G.UINT, "i") in
(*
   let i'write = G.WRITEVAR (G.UINT, "i") in
*)

   let info'size = G.SIZEOF(hazinfo'ty) in

   let call_malloc sz = G.call (G.POINTER G.VOID) "domalloc" [sz] in

   let stmts = [
      (*
       * info = domalloc(sizeof( *info ));
       * for m# in matchers (that are hazards) {
       *    for (i=0; i<M#_NUMSTATES; i++) {
       *       info->m#_states[i].result = LS_PENDING;
       *       info->m#_states[i].u.pending.curstate = i;
       *    }
       * }
       *)
      G.ASSIGN (info'write, call_malloc info'size);
      begin
        let loopbody (m: matcher) =
           let mname = "m" ^ string_of_int m.id in
           let fname = mname ^ "_states" in
           let array'ty = G.ARRAY (labelstate'ty, "") in
           let states = info'readfield array'ty fname in
           let state = G.READARRAY (labelstate'ty, states, i'read) in
           let result'write = G.WRITEFIELD (lstype, state, "result") in
	   let u'type = G.UNIONTYPE "" in
           let u'read = G.READFIELD (u'type, state, "u") in
	   let s'type = G.STRUCTTYPE "" in
           let pending'read = G.READFIELD (s'type, u'read, "pending") in
           let cs'write = G.WRITEFIELD (G.UINT, pending'read, "curstate") in
           G.BLOCK [
              G.ASSIGN (result'write, ls_pending);
              G.ASSIGN (cs'write, i'read);
           ]
        in
        let tryoneloop (ishaz, m, _dfa) =
           if ishaz then [mk_states_loop m "i" (loopbody m)] else []
        in
        let loops = List.concat (List.map tryoneloop matchers) in
        G.BLOCK loops
      end;
      G.retval info'read;
   ] in
      
   let body = G.BLOCK (locals @ stmts) in
   G.FUNCTION (G.STATIC, hazinfo'ty, funcname, [], body)

let mkhazinfo_lookup matchers =
   let ty'info = type'labelhazinfoptr in
   let ty'ls = type'labelstateptr in

   let params = [
      (ty'info, "info");
      (G.UINT, "matcherid");
      (G.UINT, "state");
   ] in
   let read'info = G.READVAR (ty'info, "info") in
   let read'matcherid = G.READVAR (G.UINT, "matcherid") in
   let read'state = G.READVAR (G.UINT, "state") in

   let read'info_mstates_array id ix =
      labelhazinfo'read'states_i read'info id ix
   in

   let locals = [
      G.LOCAL (ty'ls, "ls");
   ] in
   let read'ls = G.READVAR (ty'ls, "ls") in
   let write'ls = G.WRITEVAR (ty'ls, "ls") in

   let mkswitchcase (ishaz, (m: matcher), _) =
      if ishaz then begin
         let sym = "M" ^ string_of_int m.id ^ "_NUMSTATES" in
         let nstates = G.READVAR (G.UINT, sym) in
         let e = read'info_mstates_array m.id read'state in
         [(G.INTCONSTANT (G.UINT, string_of_int m.id), G.BLOCK [
            G.ASSERT (G.lt read'state nstates);
            G.ASSIGN (write'ls, G.addrof ty'ls e);
            G.BREAK;
         ])]
      end else []
   in
   let doswitch =
      let cases = List.concat (List.map mkswitchcase matchers) in
      G.SWITCH (read'matcherid, cases, Some (G.ASSERT (G.boolconst false)))
   in
   let ret = G.retval read'ls in

   let body = locals @ [doswitch; ret] in
   G.FUNCTION (G.STATIC, ty'ls, "labelhazinfo_lookup", params, G.BLOCK body)

let mk_hazinfo_funcs matchers = [
   G.DECLCOMMENT "hazinfo ops";
   mkhazinfo_create matchers;
   mkhazinfo_lookup matchers;
]

(**************************************************************)
(* ops on specstate *)

let mkspecstate_create () =
   let ty's = type'specstateptr in
   let ty'ls = type'labelstateptr in

   let params = [
      (G.UINT, "matcherid");
      (ty'ls, "ls");
   ] in
   let read'matcherid = G.READVAR (G.UINT, "matcherid") in
   let read'ls = G.READVAR (ty'ls, "ls") in

   let locals = [
      G.LOCAL (ty's, "s");
   ] in
   let read's = G.READVAR (ty's, "s") in
   let write's = G.WRITEVAR (ty's, "s") in
   let write's_matcherid = specstate'write'matcherid read's in
   let write's_ptr = specstate'write'ptr read's in

   (* XXX *)
(*
   let write's_nullifying = G.WRITEFIELD (G.BOOL, read's, "nullifying") in
*)

   let sz = G.SIZEOF (type'specstate) in
   let stmts = [
      G.ASSIGN (write's, G.call (G.POINTER G.VOID) "domalloc" [sz]);
      G.ASSIGN (write's_matcherid, read'matcherid);
      G.ASSIGN (write's_ptr, read'ls);
      (*G.ASSIGN (write's_nullifying, G.boolconst false);*)
      G.retval read's;
   ] in

   let body = locals @ stmts in
   G.FUNCTION (G.STATIC, ty's, "specstate_create", params, G.BLOCK body)

let mkspecstate_destroy () =
   let ty's = type'specstateptr in

   let params = [
      (ty's, "s0");
   ] in
   let read's0 = G.READVAR (ty's, "s0") in

   (*
    * note that ptr points into the speculative results tree and isn't
    * ours; we shouldn't destroy it.
    *)

   let sz = G.SIZEOF (type'specstate) in
   let body = [
      G.voidcall "dofree" [read's0; sz];
   ] in
      
   G.FUNCTION (G.STATIC, G.VOID, "specstate_destroy", params, G.BLOCK body)

let mk_specstate_funcs () = [
   G.DECLCOMMENT "specstate ops";
   mkspecstate_create ();
   mkspecstate_destroy ();
]

(**************************************************************)
(* ops on concstate *)

let mkconcstate_create () =
   let ty's = type'concstateptr in

   let params = [
      (G.INT, "linenum");
      (G.UINT, "matcherid");
      (G.UINT, "state");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read'matcherid = G.READVAR (G.UINT, "matcherid") in
   let read'state = G.READVAR (G.UINT, "state") in

   let locals = [
      G.LOCAL (ty's, "s");
   ] in
   let read's = G.READVAR (ty's, "s") in
   let write's = G.WRITEVAR (ty's, "s") in
   let write's_startline = concstate'write'startline read's in
   let write's_matcherid = concstate'write'matcherid read's in
   let write's_state = concstate'write'state read's in
   let write's_deferline = concstate'write'deferline read's in
   let write's_deferinfo = concstate'write'deferinfo read's in

   (* XXX *)
(*
   let write's_nullifying = G.WRITEFIELD (G.BOOL, read's, "nullifying") in
   let write's_jumpid = G.WRITEFIELD (G.UINT, read's, "jumpid") in
*)

   let sz = G.SIZEOF (type'concstate) in
   let stmts = [
      G.ASSIGN (write's, G.call (G.POINTER G.VOID) "domalloc" [sz]);
      G.ASSIGN (write's_startline, read'linenum);
      G.ASSIGN (write's_matcherid, read'matcherid);
      G.ASSIGN (write's_state, read'state);
(*
      G.ASSIGN (write's_nullifying, G.boolconst false);
      G.ASSIGN (write's_jumpid, G.zero G.UINT);
*)
      G.ASSIGN (write's_deferline, G.zero G.UINT);
      G.ASSIGN (write's_deferinfo, G.null);
      G.retval read's;
   ] in

   let body = locals @ stmts in
   G.FUNCTION (G.STATIC, ty's, "concstate_create", params, G.BLOCK body)

let mkconcstate_clone () =
   let ty's = type'concstateptr in

   let params = [
      (ty's, "s0");
   ] in
   let read's0 = G.READVAR (ty's, "s0") in
   let read's0_startline = concstate'read'startline read's0 in
   let read's0_matcherid = concstate'read'matcherid read's0 in
   let read's0_state = concstate'read'state read's0 in

   let locals = [
      G.LOCAL (ty's, "s");
   ] in
   let read's = G.READVAR (ty's, "s") in
   let write's = G.WRITEVAR (ty's, "s") in

   let stmts = [
      G.ASSIGN (write's, G.call ty's "concstate_create" [
         read's0_startline;
         read's0_matcherid;
         read's0_state;
      ]);
      (* XXX: nullifying/jumpid? *)
      G.retval read's;
   ] in

   let body = locals @ stmts in
   G.FUNCTION (G.STATIC, ty's, "concstate_clone", params, G.BLOCK body)

let mkconcstate_destroy () =
   let ty's = type'concstateptr in

   let params = [
      (ty's, "s0");
   ] in
   let read's0 = G.READVAR (ty's, "s0") in

   let sz = G.SIZEOF (type'concstate) in
   let body = [
      G.voidcall "dofree" [read's0; sz];
   ] in
      
   G.FUNCTION (G.STATIC, G.VOID, "concstate_destroy", params, G.BLOCK body)

let mk_concstate_funcs () = [
   G.DECLCOMMENT "concstate ops";
   mkconcstate_create ();
   mkconcstate_clone ();
   mkconcstate_destroy ();
]

(**************************************************************)
(* ops on fork *)

let mkfork_create () =
   let type'f = type'forkptr in

   let params = [
      (G.UINT, "s");
   ] in
   let read's = G.READVAR (G.UINT, "s") in

   let locals = [
      G.LOCAL (type'f, "f");
   ] in
   let read'f = G.READVAR (type'f, "f") in
   let write'f = G.WRITEVAR (type'f, "f") in

   (*let write'f'jumpid = fork'write'jumpid read'f in*)
   let read'f'basecase = fork'read'basecase read'f in
   let read'f'altcase = fork'read'altcase read'f in
   let write'f'basecase_result = labelstate'write'result read'f'basecase in
   let write'f'basecase_u_pending_curstate =
      labelstate'write'u_pending_curstate read'f'basecase
   in
   let write'f'altcase_result = labelstate'write'result read'f'altcase in
   let write'f'altcase_u_pending_curstate =
      labelstate'write'u_pending_curstate read'f'altcase
   in

   let sz = G.SIZEOF (type'fork) in
   let assigns = [
      G.ASSIGN (write'f, G.call (G.POINTER G.VOID) "domalloc" [sz]);
      (*G.ASSIGN (write'f'jumpid, G.zero G.UINT);*)
      G.ASSIGN (write'f'basecase_result, eLS_PENDING);
      G.ASSIGN (write'f'basecase_u_pending_curstate, read's);
      G.ASSIGN (write'f'altcase_result, eLS_PENDING);
      G.ASSIGN (write'f'altcase_u_pending_curstate, read's);
   ] in
   let ret = G.retval read'f in

   let body = locals @ assigns @ [ret] in
   G.FUNCTION (G.STATIC, type'f, "fork_create", params, G.BLOCK body)

let mk_fork_funcs () = [
   G.DECLCOMMENT "fork ops";
   mkfork_create ();
]

(**************************************************************)
(* predicate triggering functions *)

(*
 * For each predicate, there's a function that's called when an
 * instruction matches, or might match. We implement these;
 * targetencoding calls them.
 *
 * Each one needs to:
 *    - set the flag that says "I've been called"
 *    - stash the arguments
 *
 * The arguments are:
 *    - the tstash elements
 *    - the astash elements
 *    - the cstash elements
 *
 * XXX: the astash and cstash lists are not currently available from the
 * representation. Need to compute it upstream and store it properly,
 * then fill in the missing places (all marked XXX).
 *
 * Note that the static stashes are not strictly necessary, arguably,
 * and one might also do without the explicit struct types. But some
 * of the stashes need to be copied for later (hence the name) so it's
 * better to have it all wrapped up.
 *
 * The argument ordering relies on Map.bindings returning its results
 * in key order, and that this order will be the same here as in
 * genencoding.
 *)

(*
 * Return the names (with types) of the tstash, astash, and cstash
 * elements. These names are ordered by Types.StringMap.bindings,
 * which is (fortunately) both meaningful and deterministic.
 *)
let pred_tnames (_name, { args; }) =
   let mkone (argname, (_argpos, argty)) = (argty, argname) in
   List.map mkone (Types.StringMap.bindings args)

let pred_anames (_name, { afields; }) =
   (* grr *)
   let mkone (name, ty) = (ty, name) in
   List.map mkone (Types.StringMap.bindings afields)

let pred_cnames (_name, { cfields; }) =
   (* grr *)
   let mkone (name, ty) = (ty, name) in
   List.map mkone (Types.StringMap.bindings cfields)

(*
 * Compute the parameter list for a predfunc. Shared between the
 * function declaration and definition.
 *)
let mk_predfuncparams pos pred =
   let mk_tparam (argty, argname) =
      (mk_type pos argty, "t_" ^ argname)
   in
   let mk_aparam (argty, argname) =
      (mk_type pos argty, "a_" ^ argname)
   in
   let mk_cparam (argty, argname) =
      (mk_type pos argty, "c_" ^ argname)
   in
   let tparams = List.map mk_tparam (pred_tnames pred) in
   let aparams = List.map mk_aparam (pred_anames pred) in
   let cparams = List.map mk_cparam (pred_cnames pred) in
   tparams @ aparams @ cparams

let mk_predfuncdecls spec =
   let mk_one pred =
      let (name, { definedat; args; })  = pred in
      ignore (args);
      let funcname = "haz_seen_" ^ name in
      let params = mk_predfuncparams definedat pred in
      G.FUNCDECL (G.GLOBAL, G.VOID, funcname, params)
   in
   map_predicates mk_one spec

let mk_predfuncs spec =
   let mkone pred =
      let (pname, { definedat; args; (*es;*) }) = pred in
      ignore (args);
      let funcname = "haz_seen_" ^ pname in
      let params = mk_predfuncparams definedat pred in

      let mkassign tac (argty, argname) =
         let argty = mk_type definedat argty in
         let stashname = pname ^ "_" ^ tac ^ "stash" in
         let membername = tac ^ "_" ^ argname in
         let paramname = tac ^ "_" ^ argname in
         let structexpr = G.READVAR (G.STRUCTTYPE stashname, stashname) in
         let lhs = G.WRITEFIELD (argty, structexpr, membername) in
         G.ASSIGN (lhs, G.READVAR (argty, paramname))
      in
      let tassigns = List.map (mkassign "t") (pred_tnames pred) in
      let aassigns = List.map (mkassign "a") (pred_anames pred) in
      let cassigns = List.map (mkassign "c") (pred_cnames pred) in

      let flagname =
         if Types.StringMap.is_empty args then pname ^ "_istrue"
         else pname ^ "_maybetrue"
      in
      let istrueassign =
         G.ASSIGN (G.WRITEVAR (G.BOOL, flagname), G.boolconst true)
      in

      let body = G.BLOCK (tassigns @ aassigns @ cassigns @ [istrueassign]) in
      G.FUNCTION (G.GLOBAL, G.VOID, funcname, params, body)
   in
   G.DECLCOMMENT "Predicate triggering functions; called when predicates are or might be true" ::
   map_predicates mkone spec

let mk_curlabeldecl () =
   let type'l = type'labelptr in

   let params = [
      (type'l, "l");
   ] in

   G.FUNCDECL(G.GLOBAL, G.VOID, "haz_label", params)   

let mk_curlabelfunc () =
   let type'l = type'labelptr in

   let params = [
      (type'l, "l");
   ] in
   let read'l = G.READVAR (type'l, "l") in

   let write'curlabel = G.WRITEVAR (type'l, "curlabel") in

   let assign =
      G.ASSIGN (write'curlabel, read'l);
   in

   G.FUNCTION (G.GLOBAL, G.VOID, "haz_label", params, G.BLOCK [assign])


(**************************************************************)
(* predicate evaluation functions *)

(*
 * For each predicate that needs one (args/assignedvars is nonempty)
 * provide a function that evaluates the predicate fully, given a
 * tstash and a cstash. This is used when the tstash is on file and
 * the cstash is the static cstash for the current instruction,
 * when checking a concrete state; it is also used when the cstash
 * is on file and the tstash is from the current instruction, when
 * checking a speculative state that we've now reached.
 *)

let mkevalfuncs spec =
   let mkone pred =
      let (pname, { definedat; (*args;*) es; }) = pred in
      let funcname = pname ^ "_eval" in
      let params = [
         (G.POINTER (G.STRUCTTYPE (pname ^ "_tstash")), "t");
         (G.POINTER (G.STRUCTTYPE (pname ^ "_cstash")), "c");
      ] in

      (*
       * The expremit code assumes every variable is available
       * without prefix or qualification, and doesn't have a way
       * to parameterize. So make locals for all the elements.
       *)
      let tnames = pred_tnames pred in
      let cnames = pred_cnames pred in

      (* convert all the types first *)
      let domktype (argty, argname) =
         (mk_type definedat argty, argname)
      in
      let tnames = List.map domktype tnames in
      let cnames = List.map domktype cnames in

      let mklocal (argty, argname) =
         G.LOCAL (argty, argname)
      in
      let mkassign tc (argty, argname) =
         let ptrty = G.POINTER (G.STRUCTTYPE (pname ^ "_" ^ tc ^ "stash")) in
         let ptr = G.READVAR (ptrty, tc) in
         let read = G.READFIELD (argty, ptr, tc ^ "_" ^ argname) in
         G.ASSIGN (G.WRITEVAR (argty, argname), read)
      in
      let locals = List.map mklocal (tnames @ cnames) in
      let tassigns = List.map (mkassign "t") tnames in
      let cassigns = List.map (mkassign "c") cnames in

      let evalexprs =  List.map EE.emit'expr es in
      let evalall = List.fold_left G.logand (G.boolconst true) evalexprs in
      let ret = G.retval evalall in

      let body = G.BLOCK (locals @ tassigns @ cassigns @ [ret]) in
      G.FUNCTION (G.STATIC, G.BOOL, funcname, params, body)
   in
   G.DECLCOMMENT "Predicate evaluation functions; used when applying a concrete context to a speculative result" ::
   map_arg_predicates mkone spec


(**************************************************************)
(* assignvars evaluation functions *)

(*
 * Fill in the (static) tstash using the (static) astash.
 *
 * This is per-matcher because more than one matcher might use
 * the same trigger with different assignvar expressions.
 *
 * Only defined when the matcher actually has assignvars.
 *
 * XXX: it is theoretically possible for the cstash to be empty,
 * in which case its struct won't exist and this code won't compile.
 *)

let mk_assignfuncs spec matchers =
   let getpred pname =
      Types.StringMap.find pname spec.predicates
   in
   let mkone (m: matcher) =
      let mname = "m" ^ string_of_int m.id in
      let funcname = mname ^ "_assignvars" in
      let pname = m.trigger in
      let pred = (m.trigger, getpred m.trigger) in
      let (_, { definedat; args; }) = pred in
      ignore args;
      
      (*
       * The expremit code assumes every variable is available
       * without prefix or qualification, and doesn't have a way
       * to parameterize. So make locals for all the elements of
       * the anames stash.
       *)
      let anames = pred_anames pred in

      (* convert all the types first *)
      let domktype (argty, argname) =
         (mk_type definedat argty, argname)
      in
      let anames = List.map domktype anames in

      let mklocal (argty, argname) =
         G.LOCAL (argty, argname)
      in
      let mkassign_a (argty, argname) =
         let aty = G.STRUCTTYPE (pname ^ "_astash") in
         let a = G.READVAR (aty, pname ^ "_astash") in
         let read = G.READFIELD (argty, a, "a_" ^ argname) in
         G.ASSIGN (G.WRITEVAR (argty, argname), read)
      in
      let locals = List.map mklocal anames in
      let assigns_a = List.map mkassign_a anames in

      (*
       * Now the actual assignments from the matcher.
       *)
      let mk_assignment (pos, tname, ty, e) =
         let ty = mk_type pos ty in
         let stash = m.trigger ^ "_tstash" in
         let tstash = G.READVAR (G.STRUCTTYPE stash, stash) in
         let write = G.WRITEFIELD (ty, tstash, "t_" ^ tname) in
         G.ASSIGN (write, EE.emit'expr e)
      in
      let assignments = List.map mk_assignment m.assignments in

      let body = G.BLOCK (locals @ assigns_a @ assignments) in
      G.FUNCTION (G.STATIC, G.VOID, funcname, [], body)
   in
   let trymkone (_, (m: matcher), _) =
      if m.assignments = [] then []
      else [mkone m]
   in
   G.DECLCOMMENT "Predicate argument assigment functions; used to prepare the tstash when a trigger matches" ::
   List.concat (List.map trymkone matchers)


(**************************************************************)
(* branch/jump update *)

(*
 * When we reach a jump, all the states we have (speculative or
 * concrete) are equivalent to the same states on entry to the label.
 * For jumps backward, these states should already exist:
 *    - for speculative states, find them and link them up.
 *    - for concrete states, find them and resolve the decision tree.
 *      If what results is unsafe, complain. If what results is safe,
 *      discard. If what results is not yet known (from some other
 *      branch forward) link it up, then add an entry on the to-be-
 *      resolved-later list.
 * For jumps forward, these states don't already exist.
 *    - for speculative states, link them up.
 *    - for concrete states, add an entry on the to-be-resolved
 *      table.
 *
 * For jumps, clear the current state; for branches, don't.
 *
 * For branch-likely instructions, where instructions after the
 * branch are nullified if the branch is taken, we actually end
 * up with two sets of states, and one set should be processed as
 * above and the other kept. See below.
 *)

(*
 * merge_speculation takes a current speculative state that's
 * jumping somewhere and merges in the destination info.
 *
 * "here" is what we currently have; "targ" describes the jump target.
 *)
let mkmergespec () =
   let type'lsr = G.ENUMTYPE "labelstateresult" in
   let type'ls = type'labelstateptr in

   let params = [
      (type'ls, "here");
      (type'ls, "targ");
   ] in

   (* read accessors *)
   let read'here = G.READVAR (type'ls, "here") in
   let read'targ = G.READVAR (type'ls, "targ") in
   let read'targ_result = G.READFIELD (type'lsr, read'targ, "result") in
   let read'targ_u_unsafe_failurelinenum =
      labelstate'read'u_unsafe_failurelinenum read'targ
   in
   let read'targ_u_splice = labelstate'read'u_splice read'targ in

   (* write accessors *)
   let write'here_result = G.WRITEFIELD (type'lsr, read'here, "result") in
   let write'here_u_unsafe_failurelinenum =
      labelstate'write'u_unsafe_failurelinenum read'here
   in
   let write'here_u_splice = labelstate'write'u_splice read'here in

   let mainswitch =
      (*
       * switch (targ->result) {
       *    case LS_SAFE:
       *       here->result = LS_SAFE;
       *       break;
       *    case LS_UNSAFE:
       *       here->result = LS_UNSAFE;
       *       here->u.unsafe.failure_linenum =
       *          targ->u.unsafe.failure_linenum;
       *       break;
       *    case LS_SPLICE:
       *       merge_speculation(sp, &targ->u.splice);
       *       break;
       *    default:
       *       here->result = LS_SPLICE;
       *       here->u.splice = targ;
       *       break;
       *)
      let safecase =
         (eLS_SAFE, G.BLOCK [
            G.ASSIGN (write'here_result, eLS_SAFE);
            G.BREAK;
         ])
      in
      let unsafecase =
         (eLS_UNSAFE, G.BLOCK [
            G.ASSIGN (write'here_result, eLS_UNSAFE);
            G.ASSIGN (write'here_u_unsafe_failurelinenum,
                      read'targ_u_unsafe_failurelinenum);
            G.BREAK;
         ])
      in
      let splicecase =
         (eLS_SPLICE, G.BLOCK [
            G.voidcall "merge_speculation" [read'here; read'targ_u_splice];
            G.BREAK;
         ])
      in
      let defaultcase =
         G.BLOCK [
            G.ASSIGN (write'here_result, eLS_SPLICE);
            G.ASSIGN (write'here_u_splice, read'targ);
            G.BREAK;
         ]
      in
         G.SWITCH (read'targ_result,
                   [safecase; unsafecase; splicecase], Some defaultcase)
   in

   let body = G.BLOCK [mainswitch] in [
      G.DECLCOMMENT "Branch resolution for speculative states";
      G.FUNCTION (G.STATIC, G.VOID, "merge_speculation", params, body);
   ]
   

(*
 * merge_concrete takes a current concrete state that's jumping
 * somewhere and pulls in the destination info.
 *
 * conc is what we have; ls describes the jump target.
 *)
let mkmergeconc predicates =
   let funcname = "merge_concrete" in

   let type'info = type'labelhazinfoptr in
   let type'conc = type'concstateptr in
   let type'ls = type'labelstateptr in
   let params = [
      (G.INT, "linenum");
      (type'info, "info");
      (type'conc, "conc");
      (G.BOOL, "consume");
      (type'ls, "ls");
   ] in

   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read'info = G.READVAR (type'info, "info") in
   let read'conc = G.READVAR (type'conc, "conc") in
   let read'consume = G.READVAR (G.BOOL, "consume") in
   let read'ls = G.READVAR (type'ls, "ls") in

   let read'conc_startline = concstate'read'startline read'conc in
   let read'conc_matcherid = concstate'read'matcherid read'conc in
   let read'ls_u_unsafe_failurelinenum =
      labelstate'read'u_unsafe_failurelinenum read'ls
   in
   let read'ls_result = labelstate'read'result read'ls in
   let read'ls_u_splice = labelstate'read'u_splice read'ls in
   let read'ls_u_fork = labelstate'read'u_fork read'ls in
   let read'ls_u_fork_basecaseptr = fork'read'basecaseptr read'ls_u_fork in
   let read'ls_u_fork_altcaseptr = fork'read'altcaseptr read'ls_u_fork in
   let read'ls_u_decide p = labelstate'read'u_decide read'ls p in
   let read'ls_u_decide_iftrueptr p =
      decide'read'iftrueptr (read'ls_u_decide p)
   in
   let read'ls_u_decide_iffalseptr p =
      decide'read'iffalseptr (read'ls_u_decide p)
   in
   let read'ls_u_decide_dataptr p =
      decide'read'dataptr (read'ls_u_decide p) p
   in

   let locals = [
      G.LOCAL (type'conc, "conc2");
      G.ULOCAL (type'ls, "nextls");
   ] in

   let read'conc2 = G.READVAR (type'conc, "conc2") in
   let write'conc2 = G.WRITEVAR (type'conc, "conc2") in
   let read'nextls = G.READVAR (type'ls, "nextls") in
   let write'nextls = G.WRITEVAR (type'ls, "nextls") in

   let write'conc_deferline = concstate'write'deferline read'conc in
   let write'conc_deferinfo = concstate'write'deferinfo read'conc in
   let write'conc2_deferline = concstate'write'deferline read'conc2 in
   let write'conc2_deferinfo = concstate'write'deferinfo read'conc2 in

   let mainswitch =
      (*
       * switch (ls->result) {
       *    case LS_SAFE:
       *       if (consume) {
       *          concstate_destroy(conc);
       *       }
       *       break;
       *    case LS_UNSAFE:
       *       report_unsafe(conc->startline, ls->u.unsafe.failure_linenum,
       *                     conc->matcherid);
       *       if (consume) {
       *          concstate_destroy(conc);
       *       }
       *       break;
       *    case LS_PENDING:
       *       if (consume) {
       *          conc->deferline = linenum;
       *          conc->deferinfo = info;
       *          concstatearray_add(&deferred_concstates, conc);
       *       }
       *       else {
       *          conc2 = concstate_clone(conc);
       *          conc2->deferline = linenum;
       *          conc2->deferinfo = info;
       *          concstatearray_add(&deferred_concstates, conc2);
       *       }
       *       break;
       *    case LS_SPLICE:
       *       merge_concrete(linenum, info, conc, consume, &ls->u.splice);
       *       break;
       *    case LS_FORK:
       *       merge_concrete(linenum, info, conc, false, &ls->u.fork->basecase);
       *       merge_concrete(linenum, info, conc, consume, &ls->u.fork->altcase);
       *       break;
       *    case LS_DECIDE_<PRED>:
       *       /* ->data doesn't exist if the predicate has no cfields */
       *       if (eval_pred(&pred_tstash, &ls->u.decide_pred->data)) {
       *          nextls = &ls->u.decide_pred->iftrue;
       *       }
       *       else {
       *          nextls = &ls->u.decide_pred->iffalse;
       *       }
       *       merge_concrete(linenum, info, conc, consume, nextls);
       *       break;
       * }
       *)
      let recurse arg'consume arg'ls =
         G.voidcall funcname [read'linenum; read'info; read'conc; arg'consume; arg'ls]
      in
      let safecase =
         (eLS_SAFE, G.BLOCK [
            G.IF (read'consume, G.BLOCK [
               G.voidcall "concstate_destroy" [read'conc];
            ], G.skip);
            G.BREAK;
         ])
      in
      let unsafecase =
         (eLS_UNSAFE, G.BLOCK [
            G.voidcall "report_unsafe" [
               read'conc_startline;
               read'ls_u_unsafe_failurelinenum;
               read'conc_matcherid;
            ];
            G.IF (read'consume, G.BLOCK [
               G.voidcall "concstate_destroy" [read'conc];
            ], G.skip);
            G.BREAK;
         ])
      in
      let pendingcase =
         (eLS_PENDING, G.BLOCK [
            G.IF (read'consume, G.BLOCK [
               G.ASSIGN (write'conc_deferline, read'linenum);
               G.ASSIGN (write'conc_deferinfo, read'info);
               concstatearray_add deferred_concstates read'conc;
            ], G.BLOCK [
               G.ASSIGN (write'conc2,
                         G.call type'conc "concstate_clone" [read'conc]);
               G.ASSIGN (write'conc2_deferline, read'linenum);
               G.ASSIGN (write'conc2_deferinfo, read'info);
               concstatearray_add deferred_concstates read'conc2;
            ]);
            G.BREAK;
         ])
      in
      let splicecase =
         (eLS_SPLICE, G.BLOCK [
            recurse read'consume read'ls_u_splice;
            G.BREAK;
         ])
      in
      let forkcase =
         (eLS_FORK, G.BLOCK [
            recurse (G.boolconst false) read'ls_u_fork_basecaseptr;
            recurse read'consume read'ls_u_fork_altcaseptr;
            G.BREAK;
         ])
      in
      let mkdecidecase (pname, { args; cfields; }) =
         let tstash =
            if Types.StringMap.is_empty args then []
            else
               let tname = pname ^ "_tstash" in
               let ty = G.STRUCTTYPE tname in
               let read = G.READVAR (ty, tname) in
               [G.addrof (G.POINTER ty) read]
         in
         let cstash =
            if Types.StringMap.is_empty cfields then []
            else [read'ls_u_decide_dataptr pname]
         in
         let mystmts = match tstash @ cstash with
              [] -> [
                  G.STMTCOMMENT "impossible (predicate has no args)";
                  G.ASSERT (G.boolconst false);
              ]
            | callargs ->
                 let call = G.call G.BOOL (pname ^ "_eval") callargs in [
                    G.IF (call, G.BLOCK [
                       G.ASSIGN (write'nextls,
                                 read'ls_u_decide_iftrueptr pname);
                    ], G.BLOCK [
                       G.ASSIGN (write'nextls,
                                 read'ls_u_decide_iffalseptr pname);
                    ]);
                    recurse read'consume read'nextls;
                 ]
         in
         (eLS_DECIDE pname, G.BLOCK (mystmts @ [G.BREAK]))
      in
      let decidecases =
         List.map mkdecidecase (Types.StringMap.bindings predicates)
      in
         let cases =
            [safecase; unsafecase; pendingcase; splicecase; forkcase] @
            decidecases
         in
         G.SWITCH (read'ls_result, cases, None)
   in

   let body = G.BLOCK (locals @ [mainswitch]) in [
      G.DECLCOMMENT "Branch resolution for concrete states";
      G.FUNCTION (G.STATIC, G.VOID, funcname, params, body);
   ]

let mktakejumpto () =
   let funcname = "takejumpto" in

   let type'l = type'labelptr in
   let params = [
      (G.INT, "linenum");
      (type'l, "l");
      (G.BOOL, "isbranch");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read'l = G.READVAR (type'l, "l") in
   let read'isbranch = G.READVAR (G.BOOL, "isbranch") in

   let type'info = type'labelhazinfoptr in
   let type'sp = type'specstateptr in
   let type'conc = type'concstateptr in
   let type'ls = type'labelstateptr in
   let locals = [
      G.LOCAL (type'info, "info");
      G.LOCAL (G.UINT, "i");
      G.LOCAL (type'sp, "sp");
      G.LOCAL (type'conc, "conc");
      G.LOCAL (type'ls, "ls");
      G.LOCAL (G.UINT, "state");
   ] in
   let read'info = G.READVAR (type'info, "info") in
   let write'info = G.WRITEVAR (type'info, "info") in
   let read'i = G.READVAR (G.UINT, "i") in
   let read'sp = G.READVAR (type'sp, "sp") in
   let write'sp = G.WRITEVAR (type'sp, "sp") in
   let read'conc = G.READVAR (type'conc, "conc") in
   let write'conc = G.WRITEVAR (type'conc, "conc") in
   let read'ls = G.READVAR (type'ls, "ls") in
   let write'ls = G.WRITEVAR (type'ls, "ls") in
   let read'state = G.READVAR (G.UINT, "state") in
   let write'state = G.WRITEVAR (G.UINT, "state") in

   let read'sp_matcherid = specstate'read'matcherid read'sp in
   let read'sp_ptr = specstate'read'ptr read'sp in
   let write'sp_ptr = specstate'write'ptr read'sp in
   let write'sp_ptr_result =
      labelstate'write'result read'sp_ptr
   in
   let read'sp_ptr_u_pending_curstate =
      labelstate'read'u_pending_curstate read'sp_ptr
   in
   let read'sp_ptr_u_fork =
      labelstate'read'u_fork read'sp_ptr
   in
   let write'sp_ptr_u_fork =
      labelstate'write'u_fork read'sp_ptr
   in
   let read'sp_ptr_u_fork_basecaseptr =
      fork'read'basecaseptr read'sp_ptr_u_fork
   in
   let read'sp_ptr_u_fork_altcaseptr =
      fork'read'altcaseptr read'sp_ptr_u_fork
   in
   let read'conc_matcherid = concstate'read'matcherid read'conc in
   let read'conc_state = concstate'read'state read'conc in
   let read'ls_result = labelstate'read'result read'ls in

   let setup = [
      (*
       * info = label_gethazinfo(l);
       * if (info == NULL) {
       *    info = labelhazinfo_create();
       *    label_sethazinfo(l, info);
       * }
       *)
      G.ASSIGN (write'info, G.call type'info "label_gethazinfo" [read'l]);
      G.IF (G.eq read'info G.null, G.BLOCK [
         G.ASSIGN (write'info, G.call type'info "labelhazinfo_create" []);
         G.voidcall "label_sethazinfo" [read'l; read'info];
      ], G.skip);
   ] in

   let spec_loopbody =
      (*
       * sp = specstatearray_get(&active_specstates, i);
       * assert(sp->ptr->result == LS_PENDING);
       * state = sp->ptr->u.pending.curstate;
       * ls = labelhazinfo_lookup(info, sp->matcherid, state);
       * if (isbranch) {
       *    sp->ptr->result = LS_FORK;
       *    sp->ptr->u.fork = fork_create(state);
       *    /* alt case is to take the branch */
       *    merge_speculation(&sp->ptr.u.fork->altcase, ls);
       *    sp->ptr = &sp->ptr.u.fork->basecase;
       * }
       * else {
       *    merge_speculation(sp->ptr, ls);
       *    specstatearray_remove_unordered(&active_specstates);
       *    specstate_destroy(sp);
       *    i--;
       * }
       *)
      [
         G.ASSIGN (write'sp, G.call type'sp "specstatearray_get" [
                                active_specstates;
                                read'i;
                             ]);
         G.ASSERT (G.eq read'ls_result eLS_PENDING);
         G.ASSIGN (write'state, read'sp_ptr_u_pending_curstate);
         G.ASSIGN (write'ls,
                   G.call type'ls "labelhazinfo_lookup" [
                      read'info;
                      read'sp_matcherid;
                      read'state;
                  ]);
         G.IF (read'isbranch, G.BLOCK [
            G.ASSIGN (write'sp_ptr_result, eLS_FORK);
            G.ASSIGN (write'sp_ptr_u_fork,
                      G.call type'forkptr "fork_create" [read'state]);
            G.voidcall "merge_speculation" [
                          read'sp_ptr_u_fork_altcaseptr;
                          read'ls;
                       ];
            G.ASSIGN (write'sp_ptr, read'sp_ptr_u_fork_basecaseptr);
         ], G.BLOCK [
            G.voidcall "merge_speculation" [read'sp_ptr; read'ls];
            specstatearray_remunsorted active_specstates read'i;
            G.voidcall "specstate_destroy" [read'sp];
            G.decr G.UINT "i";
         ]);
      ]
   in
   let conc_loopbody =
      (*
       * conc = concstatearray_get(&active_concstates, i);
       * state = conc->state;
       * ls = labelhazinfo_lookup(info, conc->matcherid, state);
       * if (isbranch) {
       *    merge_concrete(linenum, info, conc, false/*consume*/, ls);
       * }
       * else {
       *    merge_concrete(linenum, info, conc, true/*consume*/, ls);
       *    concstatearray_remove_unordered(&active_concstates, i);
       *    i--;
       * }
       *)
      [
         G.ASSIGN (write'conc, concstatearray_get active_concstates read'i);
         G.ASSIGN (write'state, read'conc_state);
         G.ASSIGN (write'ls, G.call type'ls "labelhazinfo_lookup" [
                                      read'info;
                                      read'conc_matcherid;
                                      read'state;
                             ]);
         G.IF (read'isbranch, G.BLOCK [
            G.voidcall "merge_concrete" [
                          read'linenum;
                          read'info;
                          read'conc;
                          G.boolconst false; (* consume *)
                          read'ls;
                       ];
         ], G.BLOCK [
            G.voidcall "merge_concrete" [
                          read'linenum;
                          read'info;
                          read'conc;
                          G.boolconst true; (* consume *)
                          read'ls;
                       ];
            concstatearray_remunsorted active_concstates read'i;
            G.decr G.UINT "i";
         ]);
      ]
   in

   let specloop = mk_specstates_loop "i" (G.BLOCK spec_loopbody) in  
   let concloop = mk_concstates_loop "i" (G.BLOCK conc_loopbody) in

   let body = locals @ setup @ [specloop; concloop] in
   [
      G.DECLCOMMENT "Called when a branch to a specific location is taken";
      G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK body);
   ]

let mktakejumpaway () =
   let funcname = "takejumpaway" in

   let params = [
      (G.INT, "linenum");
      (*(G.BOOL, "isbranch");*)
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   (*let read'isbranch = G.READVAR (G.BOOL, "isbranch") in*)

   let type'sp = type'specstateptr in
   let type'conc = type'concstateptr in
   let locals = [
      G.LOCAL (G.UINT, "i");
      G.LOCAL (type'sp, "sp");
      G.LOCAL (type'conc, "conc");
   ] in
   let read'i = G.READVAR (G.UINT, "i") in
   let read'sp = G.READVAR (type'sp, "sp") in
   let write'sp = G.WRITEVAR (type'sp, "sp") in
   let read'conc = G.READVAR (type'conc, "conc") in
   let write'conc = G.WRITEVAR (type'conc, "conc") in

   let read'sp_ptr = specstate'read'ptr read'sp in
   let read'sp_ptr_result =
      labelstate'read'result read'sp_ptr
   in
   let write'sp_ptr_result =
      labelstate'write'result read'sp_ptr
   in
   let write'sp_ptr_u_unsafe_failurelinenum =
      labelstate'write'u_unsafe_failurelinenum read'sp_ptr
   in
   let read'conc_startline = concstate'read'startline read'conc in
   let read'conc_matcherid = concstate'read'matcherid read'conc in

   (*
    * Note that for branches, theoretically we could/should fork and
    * continue to work on the STAY case as it might produce a
    * different result. However, this is moot because the code is
    * unsafe if either fork is unsafe; therefore, just mark the whole
    * thing unsafe up front, or complain up front, and stop working on
    * it.
    *
    * This means we discard all current states regardless of whether
    * the instruction is a branch, so we don't need the isbranch param.
    *)

   let spec_loopbody =
      (*
       * sp = specstatearray_get(&active_specstates, i);
       * assert(sp->ptr->result == LS_PENDING);
       * sp->ptr->result = LS_UNSAFE;
       * sp->ptr->u.unsafe.failure_linenum = linenum;
       * specstate_destroy(sp);
       *)
      [
         G.ASSIGN (write'sp, G.call type'sp "specstatearray_get" [
                                active_specstates;
                                read'i;
                             ]);
         G.ASSERT (G.eq read'sp_ptr_result eLS_PENDING);
         G.ASSIGN (write'sp_ptr_result, eLS_UNSAFE);
         G.ASSIGN (write'sp_ptr_u_unsafe_failurelinenum, read'linenum);
         G.voidcall "specstate_destroy" [read'sp];
      ]
   in
   let specstmts = [
      mk_specstates_loop "i" (G.BLOCK spec_loopbody);
      specstatearray_setsize active_specstates (G.zero G.UINT);
   ] in

   let conc_loopbody =
      (*
       * conc = concstatearray_get(&active_concstates, i);
       * report_unsafe(read'conc_startline, linenum, conc->matcherid);
       * concstate_destroy(conc);
       *)
      [
         G.ASSIGN (write'conc, concstatearray_get active_concstates read'i);
         G.voidcall "report_unsafe" [
                       read'conc_startline;
                       read'linenum;
                       read'conc_matcherid;
                    ];
         G.voidcall "concstate_destroy" [read'conc];
      ]
   in
   let concstmts = [
      mk_concstates_loop "i" (G.BLOCK conc_loopbody);
      concstatearray_setsize active_concstates (G.zero G.UINT);
   ] in

   let body = locals @ specstmts @ concstmts in
   [
      G.DECLCOMMENT "Called when a branch to an unknown location is taken";
      G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK body);
   ]

(**************************************************************)
(* speculative state update *)

(*
 * At any time we have some number of active speculative states.
 * Each one is associated with some matcher in some state.
 * Examine the predicate states of the current instruction:
 * some are definitely false, some are definitely true, some
 * might be true depending on assignedargs that we don't know
 * when speculating. This gives us zero or more possible next
 * states.
 *
 * If there's no next states, the automaton has rejected, so
 * mark this case unsafe and take it off the active table.
 *
 * If there's one next state, update to it and move on.
 *
 * If there's more than one, construct a decision tree based
 * on the to-be-checked predicates: each entry saves a copy of
 * the current instruction field stash for that predicate and
 * encodes a yes/no decision. The leaves of this tree get added
 * to the active speculative state table. (And the top gets
 * removed.)
 *
 * XXX: we should probably think about how to construct an
 * optimal or advantageous decision tree, but I'm not sure what
 * that is. (Fewest nodes? Most balanced tree? Or what?)
 *)

let mkspecupdate alltentatives (m: matcher) dfa =
   let mname = "m" ^ string_of_int m.id in
   let funcname = mname ^ "_specupdate" in

   (*
    * statement helpers (move to Gcode?)
    *)

   let retfalse = G.retval (G.boolconst false) in
   let rettrue = G.retval (G.boolconst true) in

   (*
    * accessors for globals
    *)

   (* XXX remove these *)
   let lstype = type'labelstateresult in
   let ls_safe = eLS_SAFE in
   let ls_unsafe = eLS_UNSAFE in
   let ls_pending = eLS_PENDING in

   let specstate'ty = G.STRUCTTYPE "specstate" in

   let active_specstates =
      let ty = G.STRUCTTYPE "specstatearray" in
      G.addrof (G.POINTER ty) (G.READVAR (ty, "active_specstates"))
   in

   (*
    * params and accessors
    *    unsigned linenum
    *    struct specstate *s
    *)

   let s'ty = G.POINTER (G.STRUCTTYPE "specstate") in
   let params = [
      (G.INT, "linenum");
      (s'ty, "s");
   ] in
   let s'read = G.READVAR (s'ty, "s") in
   let s'readfield ty name = G.READFIELD (ty, s'read, name) in
(*
   let s'writefield ty name = G.WRITEFIELD (ty, s'read, name) in
*)

   let ptr'ty = G.POINTER (G.STRUCTTYPE "labelstate") in
   let ptr'read = s'readfield ptr'ty "ptr" in
   let ptr'readfield ty name = G.READFIELD (ty, ptr'read, name) in
(*
   let ptr'writefield ty name = G.WRITEFIELD (ty, ptr'read, name) in
*)

   let u'ty = G.UNIONTYPE "" in
   let u'read = ptr'readfield u'ty "u" in
   let u'readfield ty name = G.READFIELD (ty, u'read, name) in
(*
   let u'writefield ty name = G.WRITEFIELD (ty, u'read, name) in
*)

   let uf'readfield ty ufield subfield =
      G.READFIELD (ty, u'readfield (G.STRUCTTYPE "") ufield, subfield)
   in
(*
   let uf'writefield ty ufield subfield =
      G.WRITEFIELD (ty, u'readfield (G.STRUCTTYPE "") ufield, subfield)
   in
*)

   (*
    * locals and accesors
    *    struct m#_decide *decide
    *)

   let decide'ty = G.POINTER (G.STRUCTTYPE (mname ^ "_decide")) in
   let locals = [
      G.ULOCAL (decide'ty, "decide");
   ] in
   let decide'read = G.READVAR (decide'ty, "decide") in
   let decide'write = G.WRITEVAR (decide'ty, "decide") in

   (*
    * entry assertions
    *)

   let assertions = [
      G.ASSERT (G.eq (s'readfield G.UINT "matcherid") (G.zero G.UINT));
      G.ASSERT (G.eq (ptr'readfield G.UINT "result") ls_pending);
   ] in

   (*
    * Hooks to use to resolve state machine transitions
    *)

   let fetchstate =
      (* s->ptr->u.pending.curstate *)
      uf'readfield G.UINT "pending" "curstate"
   in
   let tonextstate newstate ptr = [
      (*
       * (ptr is s->ptr by default)
       * ptr->u.pending.curstate = newstate;
       * return false; /* keep original entry */
       *)
      begin
         let u = G.READFIELD (u'ty, ptr, "u") in
         let pending = G.READFIELD (G.STRUCTTYPE "", u, "pending") in
         let curstate = G.WRITEFIELD (G.UINT, pending, "curstate") in
         G.ASSIGN (curstate, G.INTCONSTANT (G.UINT, string_of_int newstate))
      end;
      retfalse;
   ] in
   let doaccept ptr = [
      (*
       * (ptr is s->ptr by default)
       * ptr->result = LS_SAFE;
       * return true; /* remove original entry */
       *)
      begin
         let result = G.WRITEFIELD (lstype, ptr, "result") in
         G.ASSIGN (result, ls_safe)
      end;
      rettrue;
   ] in
   let doreject ptr = [
      (*
       * (ptr is s->ptr by default)
       * s->ptr->result = LS_UNSAFE;
       * s->ptr->u.unsafe.failure_linenum = linenum;
       * return true; /* remove original entry */
       *)
      begin
         let result = G.WRITEFIELD (lstype, ptr, "result") in
         G.ASSIGN (result, ls_unsafe)
      end;
      begin
         let u = G.READFIELD (u'ty, ptr, "u") in
         let unsafe = G.READFIELD (G.STRUCTTYPE "", u, "unsafe") in
         let fl = G.WRITEFIELD (G.INT, unsafe, "failure_linenum") in
         G.ASSIGN (fl, G.READVAR (G.INT, "linenum"))
      end;
      rettrue;
   ] in
   let dodecide pred next1 next2 ptr =
      (*
       * (ptr is s->ptr by default)
       *)
      let write'ptr_result = labelstate'write'result ptr in
   ([
      (*
       * decide = pred_decide_create();
       * ptr->result = LS_DECIDE;
       * ptr->u.decide = decide;
       * next1(&ptr->u.decide->iftrue);
       * next2(&ptr->u.decide->iffalse);
       * specstatearray_add(&active_specstates, &ptr->u.decide->iftrue);
       * specstatearray_add(&active_specstates, &ptr->u.decide->iffalse);
       * return true; /* remove original entry */
       *)
      G.ASSIGN (decide'write,
                G.call decide'ty (pred ^ "_decide_create") []);
      G.ASSIGN (write'ptr_result, eLS_DECIDE pred);
      begin
         let u = G.READFIELD (u'ty, ptr, "u") in
         let udecide_w = G.WRITEFIELD (G.STRUCTTYPE "", u, "decide") in
         G.ASSIGN (udecide_w, decide'read);
      end;

      (* don't use the original decide past here in case it changes *)
   ] @
      let u = G.READFIELD (u'ty, ptr, "u") in
      let udecide = G.READFIELD (G.STRUCTTYPE "", u, "decide") in
      let ptrty = G.POINTER specstate'ty in
      let iftrue =
         G.addrof ptrty (G.READFIELD (specstate'ty, udecide, "iftrue"))
      in
      let iffalse = 
         G.addrof ptrty (G.READFIELD (specstate'ty, udecide, "iffalse"))
      in
   [
      G.BLOCK (next1 iftrue);
      G.BLOCK (next2 iffalse);

      G.voidcall "specstatearray_add" [
         active_specstates;
         iftrue;
      ];
      G.voidcall "specstatearray_add" [
         active_specstates;
         iffalse;
      ];
      rettrue;
   ]) in

   (*
    * call the dfa codegen
    *)
   let grind =
      Rx.advance_dfa_spec dfa
		fetchstate
		tonextstate doaccept doreject
		dodecide alltentatives ptr'read
   in

   let body = G.BLOCK (locals @ assertions @ [grind]) in
   G.FUNCTION (G.STATIC, G.BOOL, funcname, params, body)

(* XXX this and mkallconcupdate are too much cutpaste *)
let mkallspecupdate matchers =
   let ty's = type'specstateptr in

   let params = [
      (G.INT, "linenum");
      (ty's, "s");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read's = G.READVAR (ty's, "s") in
   let read's_matcherid = specstate'read'matcherid read's in

   let cases =
      let mkcase (_, m, _) =
         let idstr = string_of_int m.id in
         let updatename = "m" ^ idstr ^ "_specupdate" in
         (G.INTCONSTANT (G.UINT, idstr),
          G.retval (G.call G.BOOL updatename [read'linenum; read's]))
      in
      let mkcase' (ishaz, m, dfa) =
         if ishaz then [mkcase (ishaz, m, dfa)] else []
      in
      List.concat (List.map mkcase' matchers)
   in
   let doswitch = G.SWITCH (read's_matcherid, cases,
                            Some (G.ASSERT (G.boolconst false)))
   in

   let body = [doswitch] in
   G.FUNCTION (G.STATIC, G.BOOL, "all_specupdate", params, G.BLOCK body)

let mkspecupdates alltentatives matchers =
   (*
    * For now at least we don't speculate about branching.
    * XXX this is probably inadequate for some sparc cases
    *)
   let tryone (ishaz, m, dfa) =
      if ishaz then [mkspecupdate alltentatives m dfa]
      else []
   in
   G.DECLCOMMENT "Speculative state machine update functions" ::
   List.concat (List.map tryone matchers) @ [mkallspecupdate matchers]

(**************************************************************)
(* concrete state update *)

(*
 * At any time we also have some set of active concrete states,
 * associated with hazards and/or branches. For each one, check
 * the predicates and find the next state. Since we have the
 * assignedargs values for each one, every predicate resolves
 * definitely to either true or false, so we get either one
 * next state, or none. If none, the automaton rejects; for
 * hazards complain about it, and for transfers just discard
 * the entry. If we get one, and it's an accepting state, for
 * hazards discard the entry and for transfers process the
 * transfer. If it's not an accepting state, update the entry
 * and continue.
 *)

let mktransfer { definedat; m; effects; } =
   let mname = "m" ^ string_of_int m.id in
   let funcname = mname ^ "_transfer" in

   let params = [
      (G.INT, "linenum");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in

   let read'curlabel = G.READVAR (type'labelptr, "curlabel") in

   let takejump isbranch =
      G.IF (G.eq read'curlabel G.null, G.BLOCK [
         G.voidcall "takejumpaway" [
            read'linenum;
            (*G.boolconst isbranch;*)
         ]
      ], G.BLOCK [
         G.voidcall "takejumpto" [
            read'linenum;
            read'curlabel;
            G.boolconst isbranch;
         ]
      ])
   in
   let comment msg =
      G.STMTCOMMENT msg
   in

   (*
    * This is what happens when we reach the transfer part, so
    * NULLIFY vs. EXECUTE is no longer relevant.
    *)
   let stmts = match effects with
        [_, STAY] -> [comment "jump that doesn't jump"]
      | [_, GO] -> [takejump false]
      | [_, STAY; _, GO] -> [takejump true]
      | [_, GO; _, STAY] -> [takejump true]
      | [_, GO; _, GO] ->
           Pos.sayat definedat "Cannot branch both ways"; Util.fail (); []
      | [_, STAY; _, STAY] -> [comment "branch that doesn't branch"]
      | _ -> Util.crash "mkhazmachine: mktransfer: Invalid effects list"
   in

   G.FUNCTION (G.STATIC, G.VOID, funcname, params, G.BLOCK stmts)


let mkconcupdate (ishaz, m, dfa) =
   let mname = "m" ^ string_of_int m.id in
   let funcname = mname ^ "_concupdate" in

   let retfalse = G.retval (G.boolconst false) in
   let rettrue = G.retval (G.boolconst true) in

   let intconst ty k =
      G.INTCONSTANT (ty, string_of_int k)
   in
   let id = intconst G.UINT m.id in

(*
   let ty'tstash = G.STRUCTTYPE (m.trigger ^ "_tstash") in
   let read'tstash = G.READVAR (ty'tstash, m.trigger ^ "_tstash") in

   let ty'cstash pred = G.STRUCTTYPE (pred ^ "_cstash") in
   let read'cstash pred = G.READVAR (ty'cstash pred, pred ^ "_cstash") in
*)

   let ty's = type'concstateptr in

   let params = [
      (G.INT, "linenum");
      (ty's, "s");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read's = G.READVAR (ty's, "s") in

   let read's_startline = concstate'read'startline read's in
   let read's_matcherid = concstate'read'matcherid read's in
   let read's_state = concstate'read'state read's in
   let write's_state = concstate'write'state read's in


   let assertions = [
      G.ASSERT (G.eq read's_matcherid id);
   ] in

   (*
    * Hooks for the state machine transitions
    *)
   let fetchstate = read's_state in
   let tonextstate newstate () = [
      (*
       * s->state = newstate;
       * return false; /* keep entry */
       *)
      G.ASSIGN (write's_state, intconst G.UINT newstate);
      retfalse;
   ] in
   let doaccept () = (if ishaz then [] else [
      (*
       * m#_transfer(linenum);
       *)
      G.voidcall (mname ^ "_transfer") [read'linenum];
   ]) @ [
      (*
       * return true; /* remove entry */
       *)
      rettrue;
   ] in
   let doreject () = [
      (*
       * report_unsafe(s->startline, linenumm, matcherid);
       * return true; /* remove entry */
       *)
      G.voidcall "report_unsafe" [read's_startline; read'linenum; id];
      rettrue;
   ] in
(*
   let dodecide pred next1 next2 () =
      (*
       * if (pred_eval(...)) {
       *    return next1();
       * }
       * else {
       *    return next2();
       * }
       *)
      let eval =
         G.call G.BOOL (pred ^ "_eval") [read'tstash; read'cstash pred]
      in
      [
         G.IF (eval, G.BLOCK (next1 ()), G.BLOCK (next2 ()));
         retfalse; (* XXX wrong *)
      ]
   in
*)
   let grind =
(*
      Rx.advance_dfa_spec dfa
                fetchstate
                tonextstate doaccept doreject
                dodecide Types.StringSet.empty ()
*)
      Rx.advance_dfa dfa
                fetchstate
                tonextstate doaccept doreject ()
   in

   let body = (*locals @*) assertions @ [grind] in
   G.FUNCTION (G.STATIC, G.BOOL, funcname, params, G.BLOCK body)

(* XXX this and mkallspecupdate are too much cutpaste *)
let mkallconcupdate matchers =
   let ty's = type'concstateptr in

   let params = [
      (G.INT, "linenum");
      (ty's, "s");
   ] in
   let read'linenum = G.READVAR (G.INT, "linenum") in
   let read's = G.READVAR (ty's, "s") in
   let read's_matcherid = concstate'read'matcherid read's in

   let cases =
      let mkcase (_, m, _) =
         let idstr = string_of_int m.id in
         let updatename = "m" ^ idstr ^ "_concupdate" in
         (G.INTCONSTANT (G.UINT, idstr),
          G.retval (G.call G.BOOL updatename [read'linenum; read's]))
      in
      List.map mkcase matchers
   in
   let doswitch = G.SWITCH (read's_matcherid, cases,
                            Some (G.ASSERT (G.boolconst false)))
   in

   let body = [doswitch] in
   G.FUNCTION (G.STATIC, G.BOOL, "all_concupdate", params, G.BLOCK body)

let mkconcupdates spec matchers =
   G.DECLCOMMENT "Concrete state machine update functions" ::
   List.map mktransfer spec.transfers @
   List.map mkconcupdate matchers @
   [mkallconcupdate matchers]


(**************************************************************)
(* label update *)

(*
 * When we reach a new label, we need to start speculating about
 * every state of every hazard. Create a new hazard entry for the
 * new label. Initialize it with every state of every hazard. Add
 * these to the active table.
 *
 * XXX what about transfers? On MIPS it's illegal to put branches in
 * branch delay slots, so you can't have a branch pending when you
 * arrive at a label. But this apparently isn't true on sparc. I guess
 * what we should do is speculate from every hazard state and every
 * transfer state, and then if the transfer matcher accepts record the
 * safety as equivalent to the (unknown) destination associated with
 * the pending transfer. We can do this; however, I think for now
 * we'll just prohibit it. Update: sparc allows branches in jump
 * delay slots, but apparently not in the delay slots of conditional
 * branches. See pg. 56 of the sparcv8 manual. So unless other
 * examples surface this gets (somewhat) simpler.
 *)

let mkhazlabel matchers =
   let funcname = "haz_addlabel" in

   let labelstate'ty = G.STRUCTTYPE "labelstate" in
   let specstate'ty = G.POINTER (G.STRUCTTYPE "specstate") in

   let active_specstates =
      let ty = G.STRUCTTYPE "specstatearray" in
      G.addrof (G.POINTER ty) (G.READVAR (ty, "active_specstates"))
   in

   let l'ty = G.POINTER (G.STRUCTTYPE ("label")) in
   let params = [
      (l'ty, "l");
   ] in
   let l'read = G.READVAR (l'ty, "l") in

   let hazinfo'ty = G.POINTER (G.STRUCTTYPE "labelhazinfo") in
   let locals = [
      G.LOCAL (hazinfo'ty, "info");
      G.LOCAL (G.UINT, "i");
      G.LOCAL (specstate'ty, "sp");
   ] in
   let info'read = G.READVAR (hazinfo'ty, "info") in
   let info'write = G.WRITEVAR (hazinfo'ty, "info") in
   let info'readfield ty name = G.READFIELD (ty, info'read, name) in
(*
   let info'writefield ty name = G.WRITEFIELD (ty, info'read, name) in
*)
   let i'read = G.READVAR (G.UINT, "i") in
(*
   let i'write = G.WRITEVAR (G.UINT, "i") in
*)
   let sp'read = G.READVAR (specstate'ty, "sp") in
   let sp'write = G.WRITEVAR (specstate'ty, "sp") in
(*
   let sp'readfield ty name = G.READFIELD (ty, sp'read, name) in
   let sp'writefield ty name = G.WRITEFIELD (ty, sp'read, name) in
*)

   let label_gethazinfo =
      G.call hazinfo'ty "label_gethazinfo" [l'read]
   in
   let label_sethazinfo e =
      G.voidcall "label_sethazinfo" [l'read; e]
   in

   let labelhazinfo_create =
      G.call hazinfo'ty "labelhazinfo_create" []
   in

   let stmts = [
      (*
       * info = label_gethazinfo(l);
       * if (info == NULL) {
       *    info = labelhazinfo_create();
       *    label_sethazinfo(l, info);
       * }
       *)
      G.ASSIGN (info'write, label_gethazinfo);
      G.IF (G.eq info'read (G.READVAR (G.POINTER G.VOID, "NULL")), G.BLOCK [
                G.ASSIGN (info'write, labelhazinfo_create);
                label_sethazinfo info'read;
           ], G.skip);
      (*
       * for m# in matchers (that are hazards) {
       *    for (i=0; i<M#_NUMSTATES; i++) {
       *       sp = specstate_create(&info->m#_states[i]);
       *       specstatearray_add(&active_specstates, sp);
       *    }
       * }
       *)
      begin
        let loopbody (m: matcher) =
           let mname = "m" ^ string_of_int m.id in
           let fname = mname ^ "_states" in

           let array'ty = G.ARRAY (labelstate'ty, "") in
           let states = info'readfield array'ty fname in
           let state = G.READARRAY (labelstate'ty, states, i'read) in
           let astate = G.addrof (G.POINTER labelstate'ty) state in

           let id = G.INTCONSTANT (G.UINT, string_of_int m.id) in
           let create = G.call specstate'ty "specstate_create" [id; astate] in
           G.BLOCK [
              G.ASSIGN (sp'write, create);
              G.voidcall "specstatearray_add" [active_specstates; sp'read];
           ]
        in
        let tryoneloop (ishaz, m, _dfa) =
           if ishaz then [mk_states_loop m "i" (loopbody m)] else []
        in
        let loops = List.concat (List.map tryoneloop matchers) in
        G.BLOCK loops
      end;
   ] in

   let body = G.BLOCK (locals @ stmts) in [
      G.DECLCOMMENT "External hook called when a label is defined";
      G.FUNCTION (G.GLOBAL, G.VOID, funcname, params, body);
   ]

(**************************************************************)
(* trigger update *)

(*
 * After updating all the existing states we then need to see if
 * we triggered anything. Test all the predicates that are used
 * as triggers (for either branch or jump state machines). If a
 * hazard trigger matches, create a concrete state entry for it,
 * then update the state once. (The state machines begin on the
 * trigger instruction, not after, to allow writing restrictions
 * on single instructions; so this update might reject.)
 *
 * If a branch matches, also create a concrete state entry for it.
 * But also, if instruction nullification is involved, duplicate
 * all the states (both speculative and concrete) tagging each
 * with the branch involved and the nullification state.
 *
 * Note: it is not clear if nullified instructions should be
 * applied to hazard state machines as NOPs or not. This is not
 * specified in any of the architecture manuals I've seen for
 * any of the architectures that have these misbegotten branches.
 * I'm going to assume not until proven otherwise as this is the
 * conservative choice.
 *
 * XXX: since the state machines include the current instruction,
 * we should test the trigger and generate new current states
 * *before* updating the state machines, then just let them rip.
 * However, I laid it out the way it is originally and I don't
 * want to try changing it until I have it running enough to
 * test.
 *)

let mktrigger matchers =
   let ty's = type'concstateptr in

   let params = [
      (G.UINT, "linenum");
   ] in
   let read'linenum = G.READVAR (G.UINT, "linenum") in

   let locals = [
      G.LOCAL (ty's, "s");
   ] in
   let read's = G.READVAR (ty's, "s") in
   let write's = G.WRITEVAR (ty's, "s") in

   let read'tstash p =
      let tname = p ^ "_tstash" in
      let ty = G.STRUCTTYPE tname in
      G.addrof (G.POINTER ty) (G.READVAR (ty, tname))
   in
   let read'cstash p =
      let cname = p ^ "_cstash" in
      let ty = G.STRUCTTYPE cname in
      G.addrof (G.POINTER ty) (G.READVAR (ty, cname))
   in

   let once (_ishaz, m, dfa) =
      let mname = "m" ^ string_of_int m.id in

      let mkcheck_plain m blk =
         (* if (trigger_istrue) { ... } *)
         let read = G.READVAR (G.BOOL, m.trigger ^ "_istrue") in
         G.IF (read, blk, G.skip)
      in
      let mkcheck_complex m blk =
         (*
          * if (trigger_maybetrue) {
          *    m#_assignvars();
          *    if (trigger_eval(trigger_tstash, trigger_cstash)) { ... }
          * }
          *)
         let read'flag = G.READVAR (G.BOOL, m.trigger ^ "_maybetrue") in
         let eval =
            G.call G.BOOL (m.trigger ^ "_eval") [
               read'tstash m.trigger;
               read'cstash m.trigger;
            ]
         in
         G.IF (read'flag, G.BLOCK [
            (* first load the tstash *)
            G.voidcall (mname ^ "_assignvars") [];
            G.IF (eval, blk, G.skip)
         ], G.skip)
      in
      let mkcheck m blk =
         if m.assignments = [] then mkcheck_plain m blk
         else mkcheck_complex m blk
      in

      (* XXX if not a hazard, should check for nullification *)

      let state = Rx.dfa_startstate dfa in
      let block = [
         (*
          * s = concstate_create(linenum, m#, dfa_startstate);
          * concstatearray_add(&active_concstates, s);
          *)
         G.ASSIGN (write's, G.call ty's "concstate_create" [
                               read'linenum;
                               G.INTCONSTANT (G.UINT, string_of_int m.id);
                               G.INTCONSTANT (G.UINT, string_of_int state);
                            ]);
         concstatearray_add active_concstates read's;
      ] in
      mkcheck m (G.BLOCK block)
   in
   let tests = List.map once matchers in

   let body = locals @ tests in
   [
      G.DECLCOMMENT "Check for triggering";
      G.FUNCTION (G.STATIC, G.VOID, "trigger", params, G.BLOCK body);
   ]


(**************************************************************)
(* per-instruction hook *)

(*
 * On each instruction, after the predicate functions are (maybe)
 * called, there's a master function called that examines the
 * current instruction and updates everything.
 *
 * Call the speculative state and concrete state updaters, then the
 * trigger hook.
 *
 * Then, reset all the istrue/maybetrue flags for the next go.
 *)

let mkhazinsn_decl () =
   let params = [
      (G.UINT, "linenum");
   ] in
   G.FUNCDECL (G.GLOBAL, G.VOID, "haz_instruction", params)

let mkhazinsn preds =
   let ty'ss = type'specstateptr in
   let ty'cs = type'concstateptr in

   let params = [
      (G.UINT, "linenum");
   ] in
   let read'linenum = G.READVAR (G.UINT, "linenum") in

   let locals = [
      G.LOCAL (G.UINT, "i");
      G.LOCAL (ty'ss, "ss");
      G.LOCAL (ty'cs, "cs");
   ] in
   let read'i = G.READVAR (G.UINT, "i") in
   let read'ss = G.READVAR (ty'ss, "ss") in
   let read'cs = G.READVAR (ty'cs, "cs") in
   let write'ss = G.WRITEVAR (ty'ss, "ss") in
   let write'cs = G.WRITEVAR (ty'cs, "cs") in

   let specbody =
      let update = G.call G.BOOL "all_specupdate" [read'linenum; read'ss] in
      G.BLOCK [
         G.ASSIGN (write'ss, specstatearray_get active_specstates read'i);
         G.IF (update, G.BLOCK [
            specstatearray_remunsorted active_specstates read'i;
            G.decr G.UINT "i";
         ], G.skip)
      ]
   in
   let specloop = mk_specstates_loop "i" specbody in

   let concbody =
      let update = G.call G.BOOL "all_concupdate" [read'linenum; read'cs] in
      G.BLOCK [
         G.ASSIGN (write'cs, concstatearray_get active_concstates read'i);
         G.IF (update, G.BLOCK [
            concstatearray_remunsorted active_concstates read'i;
            G.decr G.UINT "i";
         ], G.skip)
      ]
   in
   let concloop = mk_concstates_loop "i" concbody in

   let dotrigger = G.voidcall "trigger" [read'linenum] in

   let doreset =
      let reset_one (pname, { args; }) =
         let flagname =
            pname ^ "_" ^
            if Types.StringMap.is_empty args then "istrue" else "maybetrue"
         in
         G.ASSIGN (G.WRITEVAR (G.BOOL, flagname), G.boolconst false)
      in
      List.map reset_one (Types.StringMap.bindings preds) @
      [ G.ASSIGN (G.WRITEVAR (type'labelptr, "curlabel"), G.null) ]
   in

   let body = locals @ [specloop; concloop; dotrigger] @ doreset in
   [
      G.DECLCOMMENT "Overall trigger point called for each instruction";
      G.FUNCTION (G.GLOBAL, G.VOID, "haz_instruction", params, G.BLOCK body);
   ]

(**************************************************************)
(* end-of-file update *)

(*
 * When we reach the end of file, check all the postponed states
 * and complain about any that have turned out to be unsafe.
 *
 * Any state still pending at EOF is a reference to an external symbol
 * and thus unsafe.
 *)

let mkateof () =
   let ty's = type'concstateptr in
   let ty'info = type'labelhazinfoptr in
   let ty'ls = type'labelstateptr in

   let params = [
      (G.UINT, "linenum");
   ] in
   let read'linenum = G.READVAR (G.UINT, "linenum") in

   let locals = [
      G.LOCAL (G.UINT, "i");
      G.LOCAL (ty's, "s");
      G.LOCAL (ty'info, "info");
      G.LOCAL (ty'ls, "ls");
   ] in
   let read'i = G.READVAR (G.UINT, "i") in
   let read's = G.READVAR (ty's, "s") in
   let read'info = G.READVAR (ty'info, "info") in
   let read'ls = G.READVAR (ty'ls, "ls") in
   let write's = G.WRITEVAR (ty's, "s") in
   let write'info = G.WRITEVAR (ty'info, "info") in
   let write'ls = G.WRITEVAR (ty'ls, "ls") in

   let read's_startline = concstate'read'startline read's in
   let read's_matcherid = concstate'read'matcherid read's in
   let read's_state = concstate'read'state read's in
   let read's_deferline = concstate'read'deferline read's in
   let read's_deferinfo = concstate'read'deferinfo read's in

   (*
    * If anything's left in active_concstates, warn. Delete what's
    * there.
    *
    * FUTURE: if we have fatal hazards we should check if any of the
    * pending states are from fatal hazards and if so error out.
    *)
   let checkactive =
      (*
       * if (concstatearray_num(&active_concstates) > 0) {
       *    file_warn(linenum, ...);
       *    for (i=0; i<concstatearray_num(&active_concstates); i++) {
       *       s = concstatearray_get(&active_concstates, i);
       *       concstate_destroy(s);
       *    }
       *    concstatearray_setsize(&active_concstates, 0);
       * }
       *)
      let msg = "Warning: Execution runs off end of file" in
      let getnum = concstatearray_num active_concstates in

      G.IF (G.gt getnum (G.zero G.UINT), G.BLOCK [
         G.voidcall "file_warn" [read'linenum; G.STRINGCONSTANT msg];
         mk_concstates_loop "i" (G.BLOCK [
            G.ASSIGN (write's, concstatearray_get active_concstates read'i);
            G.voidcall "concstate_destroy" [read's];
         ]);
	 concstatearray_setsize active_concstates (G.zero G.UINT);
      ], G.skip)
   in

   (*
    * Now shift all the deferred concstates back to active.
    *)
   let shift = [
      (*
       * for (i=0; i<concstatearray_num(&deferred_concstates); i++) {
       *    s = concstatearray_get(&deferred_concstates, i);
       *    concstatearray_add(&active_concstates, s);
       * }
       * concstatearray_setsize(&deferred_concstates, 0);
       *)
      mk_deferred_loop "i" (G.BLOCK [
         G.ASSIGN (write's, concstatearray_get deferred_concstates read'i);
         concstatearray_add active_concstates read's;
      ]);
      concstatearray_setsize deferred_concstates (G.zero G.UINT);
   ] in

   (*
    * Now call merge_concrete on each one remaining state.
    * XXX: this loop is the same as the one in takejump and should
    * probably be shared.
    *
    * for (i=0; i<concstatearray_num(&active_concstates); i++) {
    *    s = concstatearray_get(&active_concstates, i);
    *    info = s->deferredinfo;
    *    ls = labelhazinfo_lookup(info, s->matcherid, s->state);
    *    merge_concrete(s->deferline, info, s, true/*consume*/, ls);
    * }
    * concstatearray_setsize(&active_concstates, 0);
    *)
   let merge = [
      mk_concstates_loop "i" (G.BLOCK [
         G.ASSIGN (write's, concstatearray_get active_concstates read'i);
         G.ASSIGN (write'info, read's_deferinfo);
         G.ASSIGN (write'ls, G.call ty'ls "labelhazinfo_lookup" [
                                read'info;
                                read's_matcherid;
                                read's_state;
                             ]);
         G.voidcall "merge_concrete" [
                                read's_deferline;
                                read'info;
                                read's;
                                G.boolconst true;
                                read'ls;
         ];
     ]);
     concstatearray_setsize active_concstates (G.zero G.UINT);
   ] in

   (*
    * Now, anything that's reappeared in deferred is unsafe.
    *
    * for (i=0; i<concstatearray_num(&deferred_concstates); i++) {
    *    s = concstatearray_get(&deferred_concstates, i);
    *    report_unsafe(s->startline, s->deferline, s->matcherid);
    *    concstate_destroy(s);
    * }
    * concstatearray_setsize(&deferred_concstates, 0);
    *)
   let finalize = [
      mk_deferred_loop "i" (G.BLOCK [
         G.ASSIGN (write's, concstatearray_get deferred_concstates read'i);
         G.voidcall "report_unsafe" [
             read's_startline;
             read's_deferline;
             read's_matcherid;
         ];
         G.voidcall "concstate_destroy" [read's];
      ]);
     concstatearray_setsize deferred_concstates (G.zero G.UINT);
   ] in
   
   let body = locals @ [checkactive] @ shift @ merge @ finalize in
   [
      G.DECLCOMMENT "End-of-file hook";
      G.FUNCTION (G.GLOBAL, G.VOID, "haz_eof", params, G.BLOCK body);
   ]

(**************************************************************)
(* interface *)

let mkheader hsym spec =
   let decls =
      mk_predfuncdecls spec @
      [mk_curlabeldecl ()] @
      [mkhazinsn_decl ()]
   in
   G.FILE (Some hsym, [], decls)

let mksource hname spec haz_dfas xfer_dfas =
   (* XXX *)
   let headers = [
      G.SYSINCLUDE "stdbool.h";
      G.SYSINCLUDE "stdint.h";
      G.SYSINCLUDE "stddef.h";
      G.SYSINCLUDE "assert.h";
      G.LOCALINCLUDE "common.h";
      G.LOCALINCLUDE "array.h";
      G.LOCALINCLUDE "label.h";
      G.BLANKLINEINCLUDE;
      G.LOCALINCLUDE hname;
      G.BLANKLINEINCLUDE;
   ] in

   (*
    * alltentatives is a StringSet of the predicate names that
    * are not definitely true without further evaluation. That
    * is, the ones with args.
    *)
   let alltentatives =
      let addone pname { args; } s =
         if Types.StringMap.is_empty args then s
         else Types.StringSet.add pname s
      in
      Types.StringMap.fold addone spec.predicates Types.StringSet.empty
   in

   let matchers = getmatchers spec haz_dfas xfer_dfas in
   let predicates = spec.predicates in

   let decls =
      mknumstates matchers @
      mkstashes spec @
      mklabelstate spec @
      mkdecides spec @
      [mkfork ();
       mklabelhazinfo matchers;
       mkspecstate ();
       mkconcstate ()] @
      mkarrays () @
      mkstashvars spec @
      mkpredflags spec @
      [mkcurlabel () ] @
      mkactive ()
      (*[mkjump ()]*)
   in
   let funcs =
      mkreport spec.hazards @
      mk_hazinfo_funcs matchers @
      mk_specstate_funcs () @
      mk_concstate_funcs () @
      mk_fork_funcs () @
      mk_predfuncs spec @
      [mk_curlabelfunc ()] @
      mkevalfuncs spec @
      mk_assignfuncs spec matchers @
      mkmergespec () @
      mkmergeconc predicates @
      mktakejumpto () @
      mktakejumpaway () @
      mkspecupdates alltentatives matchers @
      mkconcupdates spec matchers @
      mkhazlabel matchers @
      mktrigger matchers @
      mkhazinsn spec.predicates @
      mkateof ()
   in
   G.FILE (None, headers, decls @ funcs)
