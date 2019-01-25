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

open Rep
module G = Gcode
module DT = Dumptools

(*
 * Regular expression compiler.
 *
 * For each regexp, create
 *   - an enumeration of input codes (possible instruction types)
 *     based on the predicates that appear in the regexp;
 *   - logic to choose an input code by testing the current instruction;
 *   - a table of state * input code -> new state.
 *
 * Because the regexps are defined in terms of more or less arbitrary
 * predicates, any place two (or more) can appear at once we need to
 * assume these can be individually true or both true at once, which
 * are separate cases of "input codes" as a regexp engine understands
 * them. For the time being, I'm going to use only a very simple
 * analysis to identify pairs of predicates that cannot be true at
 * once (or that are always true at once) and otherwise generate all
 * the cases. (This analysis is in predpair.ml.) This might lead to an
 * exponential blowup of impossible cases; if so we need an analysis
 * with more precision, which can be gotten by using a solver. (For
 * the time being we have no solver infrastructure, and while it's
 * intended elsewhere that hasn't happened yet, and I don't want to
 * spend time on it right now.)
 *
 * Because of the things we do with states to avoid scanning the
 * assembler input more than once, we need to enumerate the possible
 * states; therefore executing directly from an NDFA to avoid
 * materializing the exponential blowup doesn't work. It might be
 * possible to reframe the scanning/speculation logic to work with
 * nondeterministic states directly, but I'd need to think about it at
 * length. Should try sometime; but it's not that likely to be able to
 * avoid size problems.
 *)

(*************************************************************)
(* annoying goop *)

let stringmap_keys map =
   List.map (fun (k, _) -> k) (Types.StringMap.bindings map)

let intmap_keys map =
   List.map (fun (k, _) -> k) (Types.IntMap.bindings map)

(*************************************************************)
(* basic regexp bits *)

(*
 * Return whether a regexp can be empty.
 *)
(* unused
let rec rx_can_be_empty (r: rx) =
   match r with
        ANY -> false
      | SOME _ -> false
      | SEQ (r1, r2) ->
           if rx_can_be_empty r1 then rx_can_be_empty r2 else false
      | ALT (r1, r2) ->
           if rx_can_be_empty r1 then true else rx_can_be_empty r2
      | OPT _ -> true
      | PLUS _ -> false
*)

(*
 * Simplify regexps (particularly, stupid regexps, though we shouldn't
 * ever see genuinely stupid ones) to avoid generating garbage that
 * then needs to be optimized afterwards.
 *
 * Although currently this bubbles OPT up at the cost of duplicating
 * some subexpressions, and maybe that's not desirable.
 *)

let rec rx_baseopt_once (r: rx) =
   match r with
        ANY -> ANY
      | SOME p -> SOME p
      | SEQ (OPT r1, OPT r2) -> OPT (ALT (ALT (r1, r2), SEQ (r1, r2)))
      | SEQ (OPT r1, r2) -> ALT (r2, SEQ (r1, r2))
      | SEQ (r1, OPT r2) -> ALT (r1, SEQ (r1, r2))
      | ALT (ALT (r1a, r1b), r2) ->
           ALT (r1a, rx_baseopt_once (ALT (r1b, r2)))
      | ALT (OPT r1, OPT r2) -> OPT (ALT (r1, r2))
      | ALT (OPT r1, r2) -> OPT (ALT (r1, r2))
      | ALT (r1, OPT r2) -> OPT (ALT (r1, r2))
      | ALT (r1, r2) ->
           if r1 = r2 then r1
           else ALT (r1, r2)
      | OPT (OPT r1) -> OPT r1
      | PLUS (OPT r1) -> OPT (PLUS r1)
      | PLUS (PLUS r1) -> PLUS r1
      | _ -> r

let rec rx_baseopt (r: rx) =
   let r' = match r with
        ANY -> ANY
      | SOME p -> SOME p
      | SEQ (r1, r2) -> SEQ (rx_baseopt r1, rx_baseopt r2)
      | ALT (r1, r2) -> ALT (rx_baseopt r1, rx_baseopt r2)
      | OPT r1 -> OPT (rx_baseopt r1)
      | PLUS r1 -> PLUS (rx_baseopt r1)
   in
   rx_baseopt_once r'

(*************************************************************)
(* types *)

(*
 * We have the following kinds of automata in here:
 *   pndfa - nondeterministic finite automaton over predicates
 *   tlndfa - nondeterministic finite automaton over predicate sets
 *   tldfa - deterministic finite automaton over predicate sets
 *   adfa - deterministic finite automaton over numbered alphabet
 *
 * Since instruction predicates are in general not disjoint, and we
 * want a deterministic automaton as the result, we need to recover
 * an input alphabet from the predicates.
 *
 * The full alphabet set appears only after determinization (going
 * through the pndfa and finding which predicates are tested together
 * in single states doesn't necessarily uncover everything that
 * happens when you can be in multiple states at once) so to begin
 * with we use "temporary letters", which are sets of predicate names.
 *
 * In order to be able to minimize the output DFA, which requires
 * reversing it, which makes an NDFA, we convert the pndfa to an
 * tlndfa (NDFA over tletters/predicate sets) first, and then we can
 * go back and forth between tlndfa and tldfa until we're done
 * optimizing. It is obviously possible to determinize directly from a
 * pndfa, but then you need another copy of the determinize logic for
 * use in minimization.
 *
 * At the end we can number the alphabet, although I'm starting to
 * wonder if that's worthwhile.
 *)

module TLetter = Types.StringSet
type tletter = TLetter.t

module TLetterSet = Set.Make(TLetter)
module TLetterMap = Map.Make(TLetter)

type pndfa_state =
   (* predicate name to next state set *)
   Types.IntSet.t Types.StringMap.t

type tlndfa_state =
   (* temporary-letter to next state set *)
   Types.IntSet.t TLetterMap.t

type tldfa_state =
   (* temporary-letter to single next state *)
   int TLetterMap.t

type dfa_state =
   (* predicate name to one next state *)
   int Types.IntMap.t

(* predicate NDFA (edges labeled with predicates) *)
type pndfa =
   (* startstates, transition map, accepting states, next unused state *)
   Types.IntSet.t * pndfa_state Types.IntMap.t * Types.IntSet.t * int

(* temporary letter NDFA (edges labeled with temporary input alphabet) *)
type tlndfa =
   (* startstates, transition map, accepting states, next unused state *)
   Types.IntSet.t * tlndfa_state Types.IntMap.t * Types.IntSet.t * int

(* temporary letter DFA (edges labeled with temporary input alphabet) *)
type tldfa =
   (* startstate, transition map, accepting states, next unused state *)
   int * tldfa_state Types.IntMap.t * Types.IntSet.t * int

(* (numbered alphabet) DFA *)
type dfa =
   (* startstate, transition map, accepting states, next unused state *)
   int * dfa_state Types.IntMap.t * Types.IntSet.t * int


(*************************************************************)
(* simple lookups *)

let dfa_numstates (dfa: tldfa) =
   let (_, _, _, nextstate) = dfa in
   nextstate

let dfa_startstate (dfa: tldfa) =
   let (startstate, _, _, _) = dfa in
   startstate


(*************************************************************)
(* dump for automata *)

let string_of_tletter tl =
   "{ " ^ String.concat " " (TLetter.elements tl) ^ " }"

let dump_rx r =
   let pos = Pos.builtin (* XXX *) in
   String.concat "\n" (Dump.dump'rx pos r)

let dump_ndfa_state startstates accepts (s, _tmap) =
   let ifstart =
      if Types.IntSet.mem s startstates then " (starts)" else ""
   in
   let ifaccept =
      if Types.IntSet.mem s accepts then " (accepts)" else ""
   in
   ["state " ^ string_of_int s ^ ifstart ^ ifaccept]

let dump_ndfa_transition string_of_key s (k, dests) =
   let destlist = Types.IntSet.elements dests in
   let deststr = String.concat " " (List.map string_of_int destlist) in
   string_of_int s ^ " " ^ string_of_key k ^ " -> " ^ deststr

let dump_ndfa_transitions string_of_key bindings (s, tmap) =
   let bs = bindings tmap in
   if bs = [] then [string_of_int s ^ " [empty]"]
   else List.map (dump_ndfa_transition string_of_key s) bs

let dump_dfa_state startstate accepts (s, _tmap) =
   let ifstart =
      if s = startstate then " (starts)" else ""
   in
   let ifaccept =
      if Types.IntSet.mem s accepts then " (accepts)" else ""
   in
   ["state " ^ string_of_int s ^ ifstart ^ ifaccept]

let dump_dfa_transition string_of_key s (k, dest) =
   string_of_int s ^ " " ^ string_of_key k ^ " -> " ^ string_of_int dest

let dump_dfa_transitions string_of_key bindings (s, tmap) =
   let bs = bindings tmap in
   if bs = [] then [string_of_int s ^ " [empty]"]
   else List.map (dump_dfa_transition string_of_key s) bs

let dump_pndfa (ndfa: pndfa) =
   let (startstates, transitions, accepts, nextstate) = ndfa in

   let dump_state = dump_ndfa_state startstates accepts in
   let dump_transitions =
      dump_ndfa_transitions (fun p -> p) Types.StringMap.bindings
   in

   let tlist = Types.IntMap.bindings transitions in

   let strings =
      DT.heading "PNDFA" Pos.builtin (* XXX *) @
      DT.shortfield "nextstate" (string_of_int nextstate) @
      DT.field "states" (DT.list dump_state tlist) @
      DT.field "transitions" (DT.list dump_transitions tlist)
   in
   String.concat "\n" strings

let dump_tlndfa (ndfa: tlndfa) =
   let (startstates, transitions, accepts, nextstate) = ndfa in

   let dump_state = dump_ndfa_state startstates accepts in
   let dump_transitions =
      dump_ndfa_transitions string_of_tletter TLetterMap.bindings
   in

   let tlist = Types.IntMap.bindings transitions in

   let strings =
      DT.heading "TLNDFA" Pos.builtin (* XXX *) @
      DT.shortfield "nextstate" (string_of_int nextstate) @
      DT.field "states" (DT.list dump_state tlist) @
      DT.field "transitions" (DT.list dump_transitions tlist)
   in
   String.concat "\n" strings

let dump_tldfa (dfa: tldfa) =
   let (startstate, transitions, accepts, nextstate) = dfa in

   let dump_state = dump_dfa_state startstate accepts in
   let dump_transitions =
      dump_dfa_transitions string_of_tletter TLetterMap.bindings
   in

   let tlist = Types.IntMap.bindings transitions in

   let strings =
      DT.heading "TLDFA" Pos.builtin (* XXX *) @
      DT.shortfield "nextstate" (string_of_int nextstate) @
      DT.field "states" (DT.list dump_state tlist) @
      DT.field "transitions" (DT.list dump_transitions tlist)
   in
   String.concat "\n" strings


(*************************************************************)
(* checks for automata *)

let commonfail pass msg dump =
   Util.say ("rx: " ^ pass ^ ": " ^ msg);
   Util.say ("rx: Offending automaton:\n" ^ dump);
   Util.fail ()

let check_pndfa pass (ndfa: pndfa) =
   let (startstates, transitions, accepts, nextstate) = ndfa in

   let fail msg = commonfail pass msg (dump_pndfa ndfa) in

   (* A valid state must be less than nextstate and in transitions *)
   let checkstate where s =
      let sfail msg =
         fail ("State " ^ string_of_int s ^ " from " ^ where ^ msg)
      in
      try
         ignore (Types.IntMap.find s transitions);
         if s >= nextstate then
            sfail "is out of range"
      with Not_found -> sfail " is not in the transition table"
   in

   (* all start states must exist *)
   Types.IntSet.iter (checkstate "startstates") startstates;
   (* must be at least one *)
   if Types.IntSet.is_empty startstates then
     fail "No start states"
   else ();

   (* all accept states must exist *)
   Types.IntSet.iter (checkstate "acceptstates") accepts;
   (* must be at least one *)
   if Types.IntSet.is_empty accepts then
     fail "No accepting states"
   else ();

   (* transition table must be valid *)
   let checktransition s tmap =
      (* must be for a valid state *)
      checkstate "key of transitions" s;
      (* must lead only to valid states *)
      let msg0 = "transitions for state " ^ string_of_int s in
      let checkedge p dests =
         let msg = msg0 ^ ": destinations of " ^ p in
         Types.IntSet.iter (checkstate msg) dests
      in
      Types.StringMap.iter checkedge tmap
   in
   Types.IntMap.iter checktransition transitions

(* XXX too much cutpaste *)
let check_tlndfa pass (ndfa: tlndfa) =
   let (startstates, transitions, accepts, nextstate) = ndfa in

   let fail msg = commonfail pass msg (dump_tlndfa ndfa) in

   (* A valid state must be less than nextstate and in transitions *)
   let checkstate where s =
      let sfail msg =
         fail ("State " ^ string_of_int s ^ " from " ^ where ^ msg)
      in
      try
         ignore (Types.IntMap.find s transitions);
         if s >= nextstate then
            sfail "is out of range"
      with Not_found -> sfail " is not in the transition table"
   in

   (* all start states must exist *)
   Types.IntSet.iter (checkstate "startstates") startstates;
   (* must be at least one *)
   if Types.IntSet.is_empty startstates then
     fail "No start states"
   else ();

   (* all accept states must exist *)
   Types.IntSet.iter (checkstate "acceptstates") accepts;
   (* must be at least one *)
   if Types.IntSet.is_empty accepts then
     fail "No accepting states"
   else ();

   (* transition table must be valid *)
   let checktransition s tmap =
      (* must be for a valid state *)
      checkstate "key of transitions" s;
      (* must lead only to valid states *)
      let msg0 = " in state " ^ string_of_int s in
      let checkedge tl dests =
         let msg = "destinations of " ^ (string_of_tletter tl) ^ msg0 in
         Types.IntSet.iter (checkstate msg) dests;
         if Types.IntSet.is_empty dests then
            fail (msg ^ ": empty set")
      in
      TLetterMap.iter checkedge tmap
   in
   Types.IntMap.iter checktransition transitions

(* XXX too much cutpaste *)
let check_tldfa pass (dfa: tldfa) =
   let (startstate, transitions, accepts, nextstate) = dfa in

   let fail msg = commonfail pass msg (dump_tldfa dfa) in

   (* A valid state must be less than nextstate and in transitions *)
   let checkstate where s =
      let sfail msg =
         fail ("State " ^ string_of_int s ^ " from " ^ where ^ msg)
      in
      try
         ignore (Types.IntMap.find s transitions);
         if s >= nextstate then
            sfail "is out of range"
      with Not_found -> sfail " is not in the transition table"
   in

   (* the start state must exist *)
   checkstate "startstate" startstate;

   (* all accept states must exist *)
   Types.IntSet.iter (checkstate "acceptstates") accepts;
   (* must be at least one *)
   if Types.IntSet.is_empty accepts then
     fail "No accepting states"
   else ();

   (* transition table must be valid *)
   let checktransition s tmap =
      (* must be for a valid state *)
      checkstate "key of transitions" s;
      (* must lead only to a valid state *)
      let msg0 = " in state " ^ string_of_int s in
      let checkedge tl dest =
         let msg = "destination of " ^ (string_of_tletter tl) ^ msg0 in
         checkstate msg dest
      in
      TLetterMap.iter checkedge tmap
   in
   Types.IntMap.iter checktransition transitions


(*************************************************************)
(* first compile stage *)

(*
 * Compile the regexp to a predicate NDFA, that is, an NDFA with edges
 * labeled by instruction predicate names. Epsilon edges are allowed
 * (and used).
 *
 * Epsilon edges are labeled with "", which isn't a legal predicate
 * name. This avoids having to go make a Types.StringOptionMap or
 * similar.
 *
 * Edges that match any instruction are labeled with ".", which isn't
 * a legal predicate name and also matches the POLA.
 *)

let pndfa_of_rx (rtop: rx) : pndfa =
   let nextstate = ref 0 in
   let transitions = ref Types.IntMap.empty in

   let getstate () =
      let s = !nextstate in
      nextstate := s + 1;
      s
   in

   let simpletransition (label: string) (endstate: int) =
      let startstate = getstate () in
      (* new state: don't have to get the old transition map *)
      let transition =
         let endstates = Types.IntSet.singleton endstate in
         Types.StringMap.add label endstates Types.StringMap.empty
      in
      transitions := Types.IntMap.add startstate transition !transitions;
      startstate
   in

   let addtransition (fromstate: int) (label: string) (tostate: int) =
      let transition =
         try Types.IntMap.find fromstate !transitions
         with Not_found -> Types.StringMap.empty
      in
      let tostates =
         try Types.StringMap.find label transition
         with Not_found -> Types.IntSet.empty
      in
      let tostates' = Types.IntSet.add tostate tostates in
      let transition' = Types.StringMap.add label tostates' transition in
      transitions := Types.IntMap.add fromstate transition' !transitions
   in

   let rec build (r: rx) (endstate: int) =
      match r with
           ANY -> simpletransition "." endstate
         | SOME p -> simpletransition p endstate
         | SEQ (r1, r2) ->
              let r2start = build r2 endstate in
              build r1 r2start
         | ALT (r1, r2) ->
              let r1start = build r1 endstate in
              let r2start = build r2 endstate in
              let mystart = getstate () in
              addtransition mystart "" r1start;
              addtransition mystart "" r2start;
              mystart
         | OPT r1 ->
              let r1start = build r1 endstate in
              let mystart = getstate () in
              addtransition mystart "" r1start;
              addtransition mystart "" endstate;
              mystart
         | PLUS r1 ->
              let myend = getstate () in
              let r1start = build r1 myend in
              addtransition myend "" r1start;
              addtransition myend "" endstate;
              r1start
   in

   let endstate = getstate () in
   let startstate = build rtop endstate in
   let startstates = Types.IntSet.add startstate Types.IntSet.empty in
   let accepts = Types.IntSet.add endstate Types.IntSet.empty in

   (*
    * Note that because build never adds anything to its argument state,
    * endstate will not have any transitions, which means it won't be
    * in transitions[] at all, which makes it not valid. Create an
    * empty entry for it.
    *)
   assert (not (Types.IntMap.mem endstate !transitions));
   transitions := Types.IntMap.add endstate Types.StringMap.empty !transitions;

   (startstates, !transitions, accepts, !nextstate)

(*
 * Union a list of pndfa transition maps, specifying an extra
 * one to start with.
 *)
let pred_tmap_unionall_with tmap0 tmaps =
   let unionfunc _pred dests1 dests2 =
      Some (Types.IntSet.union dests1 dests2)
   in
   List.fold_left (Types.stringmap_union unionfunc) tmap0 tmaps

let pred_tmap_unionall =
   pred_tmap_unionall_with Types.StringMap.empty

(*
 * Remove epsilon edges. This is a separate pass (rather than just
 * part of determinize) because we want to do it before doing the
 * subsequent steps, which are hard enough without having to also
 * deal with potentially cyclic epsilons.
 *
 * (Also at some point I want to try generating code that just
 * executes the ndfa and that too is much easier without epsilons.)
 *
 * Removing epsilons works as follows: an epsilon edge from s1 to s2
 * is equivalent to including the transitions for s2 in s1. This is
 * as simple as unioning the destination sets.
 *
 * The current version first computes the transitive closure of all
 * the epsilon edges from a given state, and merges them in all at
 * once. This allows dealing with cyclic epsilons (which can happen,
 * e.g. from PLUS (OPT ANY)) in a robust way, and also allows
 * iterating over the states unioning exactly once.
 *)
let pndfa_unepsilon (ndfa: pndfa) : pndfa =
   let (startstates0, transitions0, accepts0, nextstatenum) = ndfa in

   let startstates = ref startstates0 in
   let transitions = ref transitions0 in
   let accepts = ref accepts0 in

   (* compute the transitive epsilon closure of a set of states *)
   let trans_epsilon_closure initstates =
      let ret = ref initstates in
      let grind todo =
         let statelist = Types.IntSet.elements todo in
         let getnewdestset s =
            let tmap = Types.IntMap.find s !transitions in
            try
               let dests = Types.StringMap.find "" tmap in
               Types.IntSet.diff dests !ret
            with Not_found -> Types.IntSet.empty
         in
         let newdestsets = List.map getnewdestset statelist in
         let newdests = Types.intset_unionall newdestsets in
         ret := Types.IntSet.union !ret newdests;
         newdests
      in

      let todo = ref initstates in
      while not (Types.IntSet.is_empty !todo) do
         todo := grind !todo
      done;

      !ret
   in      

   (* include state's epsilon edges into it, updating the ndfa *)
   let include_epsilons state =

      (* get this state's transition map *)
      let tmap = Types.IntMap.find state !transitions in

      (* get the epsilon edge for this state; then remove it *)
      let destset = Types.StringMap.find "" tmap in
      let tmap' = Types.StringMap.remove "" tmap in

      (* take the transitive epsilon closure of the states in destset *)
      let alldestset = trans_epsilon_closure destset in

      (* if we get a circular edge, drop it  *)
      let alldestset = Types.IntSet.remove state alldestset in

      (* get the list of destinations *)
      let alldests = Types.IntSet.elements alldestset in

      (* get all the transition maps, dropping epsilon edges *)
      let desttmaps =
         let getone s =
            let tmap = Types.IntMap.find s !transitions in
            Types.StringMap.remove "" tmap
         in
         List.map getone alldests
      in

      (* union them all *)
      let tmap'' = pred_tmap_unionall_with tmap' desttmaps in

      (* now update this state *)
      transitions := Types.IntMap.add state tmap'' !transitions;

      (* update the accepts set too *)
      let checkaccepting sofar dest =
         if sofar then true else Types.IntSet.mem dest !accepts
      in
      let accepting = List.fold_left checkaccepting false alldests in
      if accepting then
         accepts := Types.IntSet.add state !accepts
      else ();

      (* and the startstates set *)
      if Types.IntSet.mem state !startstates then begin
         (* already a start state; anything we included doesn't need to be *)
         let checkstart dest =
            startstates := Types.IntSet.remove dest !startstates
         in
         List.iter checkstart alldests
      end else begin
         let checkstart sofar dest =
            if sofar then true else Types.IntSet.mem dest !startstates
         in
         let starting = List.fold_left checkstart false alldests in
         if starting then
            startstates := Types.IntSet.add state !startstates
      end
   in

   (* find the states that have epsilon edges *)
   let epsilonstates =
      let scanstate state tmap sofar =
         if Types.StringMap.mem "" tmap then 
            Types.IntSet.add state sofar
         else sofar
      in
      Types.IntMap.fold scanstate !transitions Types.IntSet.empty
   in
   Types.IntSet.iter include_epsilons epsilonstates;

   (* return the new ndfa *)
   (!startstates, !transitions, !accepts, nextstatenum)

(*
 * Prune unreferenced states
 *)
let pndfa_unref (ndfa: pndfa) : pndfa =
   let (startstates0, transitions0, accepts0, nextstatenum) = ndfa in

   let startstates = ref startstates0 in
   let transitions = ref transitions0 in
   let accepts = ref accepts0 in

   (* delete a state *)
   let delete state =
      startstates := Types.IntSet.remove state !startstates;
      transitions := Types.IntMap.remove state !transitions;
      accepts := Types.IntSet.remove state !accepts;
      if Types.IntSet.is_empty !startstates then begin
         Util.crash "rx: pndfa_unref: no start states left"
      end
   in

   (* scan for state references and make list of unreferenced states *)
   let scan () =
      let scanstate _state tmap seen =
         let scanedge _p nextstates seen' =
            Types.IntSet.union nextstates seen'
         in
         Types.StringMap.fold scanedge tmap seen
      in
      let seen = Types.IntMap.fold scanstate !transitions !startstates in
      let filt k =
         not (Types.IntSet.mem k seen)
      in
      List.filter filt (intmap_keys !transitions)
   in

   (* work until convergence *)
   let dels = ref (scan ()) in
   while !dels <> [] do
      List.iter delete !dels;
      dels := scan ()
   done;

   (* return the new ndfa *)
   (!startstates, !transitions, !accepts, nextstatenum)

(* unused (for now?)
(*
 * Generate code that executes the (predicate) ndfa directly.
 *
 * First argument is the name for this state machine, as there may be
 * several in the full output file.
 *)
let ndfa_codegen (mname: string) (ndfa: pndfa) : G.decl list =
   let (startstates, transitions, accepts, nextstate) = ndfa in
   let states = intmap_keys transitions in


   (* The name of the are-we-in-this-state variable for a state. *)
   let inname state =
      mname ^ "_instate_" ^ string_of_int state
   in

   (* Helper for assigning booleans *)
   let assignbool name x =
      let str = if x then "true" else "false" in
      G.ASSIGN (G.WRITEVAR (G.BOOL, name), G.READVAR (G.BOOL, str))
   in

   (*
    * We need a boolean var for each state.
    *)
   let vardecls =
      let mkdecl state =
         G.VARDECL (G.STATIC, G.BOOL, inname state)
      in
      List.map mkdecl states
   in

   (*
    * We need a function to initialize the state variables.
    *)
   let initfunc =
      let mkinit state =
         assignbool (inname state) (Types.IntSet.mem state startstates)
      in
      let stmts = List.map mkinit states in
      G.FUNCTION (G.STATIC, G.VOID, mname ^ "_init", [], G.BLOCK stmts)
   in

   (*
    * And we need a function to update the state. Or actually the
    * states.
    *)
   let updatefunc =
      let uvardecls =
         let mkdecl state =
            G.LOCAL (G.BOOL, "next_" ^ inname state)
         in
         List.map mkdecl states
      in
      let uvarinits =
         let mkinit state =
            assignbool ("next_" ^ inname state) false
         in
         List.map mkinit states
      in
      let updates =
         let scanstate state tmap updates =
            let scanedge pred nextstates updates' =
               let readpred = G.READVAR (G.BOOL, pred) in
               let mkassign nextstate =
                  assignbool ("next_" ^ inname nextstate) true
               in
               let assigns =
                  List.map mkassign (Types.IntSet.elements nextstates)
               in
               G.IF (readpred, G.BLOCK assigns, G.skip) :: updates'
            in
            let readstate = G.READVAR (G.BOOL, inname state) in
            let updates' = Types.StringMap.fold scanedge tmap [] in
            G.IF (readstate, G.BLOCK updates', G.skip) :: updates
         in
         Types.IntMap.fold scanstate transitions []
      in
      let stmts = uvardecls @ [G.BLANKLINESTMT] @ uvarinits @ updates in
      G.FUNCTION (G.STATIC, G.VOID, mname ^ "_update", [], G.BLOCK stmts)
   in

   (*
    * And we need functions to test if we accepted or rejected.
    * Accept: any accepting state is marked true
    * Reject: all states are false
    *)
   let acceptfunc =
      let mkcheck state oe =
         let readstate = G.READVAR (G.BOOL, inname state) in
         match oe with
              None -> Some readstate
            | Some e -> Some (G.logor e readstate)
      in
      let e = match Types.IntSet.fold mkcheck accepts None with
           None -> Util.crash "rx: ndfa_codegen: no accepting states"
         | Some e -> e
      in
      let stmt = G.retval e in
      G.FUNCTION (G.STATIC, G.BOOL, mname ^ "_accept", [], stmt)
   in

   let rejectfunc =
      let mkcheck oe state =
         let readstate = G.lognot (G.READVAR (G.BOOL, inname state)) in
         match oe with
              None -> Some readstate
            | Some e -> Some (G.logand e readstate)
      in
      let e = match List.fold_left mkcheck None states with
           None -> Util.crash "rx: ndfa_codegen: no states!?"
         | Some e -> e
      in
      let stmt = G.retval e in
      G.FUNCTION (G.STATIC, G.BOOL, mname ^ "_reject", [], stmt)
   in

   vardecls @ [initfunc; updatefunc; acceptfunc; rejectfunc]
*)


(*************************************************************)
(* second compile stage *)

(*
 * Convert the predicate-based NDFA to an alphabet-based NDFA.
 *
 * We can't generate a final alphabet set until we determinize
 * (because until then we can't readily know which predicates overlap
 * as a result of being in multiple states at once) so at this
 * point the alphabet entries are sets of predicate names.
 *
 * Note: in the input, "." means "any instruction" and "" means
 * "epsilon", which shouldn't appear.
 *
 * In the output the empty set of predicate names means "any
 * instruction". Note that this is not the same as its default
 * interpretation of "none of the predicates are true". XXX: this
 * might end up being a problem. Extending the letter set space
 * we're using would be a gigantic nuisance, but we can make the
 * tlndfa's transition map map to both the letter -> destination
 * map and an additional destination set for "anything".
 *)

let possible (p: string) (tl: tletter) =
   let check l sofar =
      if not sofar then false
      else Predpair.possible p l
   in
   Types.StringSet.fold check tl true

(*
 * Generate the powerset of a list of predicates. But only
 * return those where all the elements can be true at once,
 * which is hopefully a small minority.
 *)
let pred_powerset (preds: string list) =
   let rec powerset ks =
      match ks with
           [] ->
              TLetterSet.add (Types.StringSet.empty) TLetterSet.empty
         | (k :: more) ->
              let r = powerset more in
              let addk tletter sofar =
                 if possible k tletter then begin
                    let tletter' = Types.StringSet.add k tletter in
                    TLetterSet.add tletter' sofar
                 end
                 else sofar
              in
              TLetterSet.union r (TLetterSet.fold addk r TLetterSet.empty)
   in
   let ret = powerset preds in
   (* don't want [] as it's used as a special case *)
   TLetterSet.remove Types.StringSet.empty ret

(*
 * convert one state transition map
 *
 * (this is shared with determinize)
 *)
let conv_one_pndfa_tmap ptmap =
   let atmap = ref TLetterMap.empty in

   (* if the "any" edge is present handle it up front *)
   let ptmap =
      try
         let dests = Types.StringMap.find "." ptmap in
         atmap := TLetterMap.add TLetter.empty dests !atmap;
         Types.StringMap.remove "." ptmap
      with Not_found -> ptmap
   in

   (*
    * Now we need to generate the powerset of all the keys...
    * though we only need the ones that Predpair tells us can
    * happen together.
    *)
   let keys = stringmap_keys ptmap in
   let letters = pred_powerset keys in

   (*
    * Now build atmap.
    *)
   let doadd l =
      (* collect all the destination states for the predicates *)
      let addsome p sofar =
         let mydests = Types.StringMap.find p ptmap in
         Types.IntSet.union sofar mydests
      in
      let dests = Types.StringSet.fold addsome l Types.IntSet.empty in

      (* add to atmap *)
      atmap := TLetterMap.add l dests !atmap
   in
   TLetterSet.iter doadd letters;
   !atmap

let tlndfa_of_pndfa (pndfa: pndfa) =
   let (startstates, ptransitions, accepts, nextstate) = pndfa in

   (* convert ptransitions *)
   let atransitions = Types.IntMap.map conv_one_pndfa_tmap ptransitions in

   (startstates, atransitions, accepts, nextstate)
   

(*************************************************************)
(* third compile stage *)

(*
 * Determinize an alphabet NDFA to make a(n alphabet) DFA.
 *
 * When this is done we can make a final alphabet for this
 * automaton. However, for various reasons we'd like to share
 * one alphabet among all the automata we build.
 * ... what are those reasons? XXX
 *)

(*
 * Module rubbish so we can have a map from IntSets to things.
 *)

module IntSetMap = Map.Make(Types.IntSet)


let tldfa_of_tlndfa (ndfa: tlndfa) : tldfa =
   let (n_startstates, n_transitions, n_accepts, _nextstatenum) = ndfa in

   let d_nextstatenum = ref 0 in

   let newstate () =
      let s = !d_nextstatenum in
      d_nextstatenum := s + 1;
      s
   in

   let nstates_to_dstate = ref IntSetMap.empty in
   let dstate_to_nstates = ref Types.IntMap.empty in
   let undone_dstates = ref [] in

   let getdfastate ndestset =
      try
         IntSetMap.find ndestset !nstates_to_dstate
      with Not_found ->
         let dstate = newstate () in
         nstates_to_dstate := IntSetMap.add ndestset dstate !nstates_to_dstate;
         dstate_to_nstates :=
            Types.IntMap.add dstate ndestset !dstate_to_nstates;
         undone_dstates := dstate :: !undone_dstates;
         dstate
   in

   (*
    * Check that all predicates found in any of the input states
    * appear in ptmap.
    *)
   let check_for_missing_predicates ptmap nstates =
      let scan_state s =
         let scan_tl tl _ =
            let scan_pred p =
               try
                  ignore (Types.StringMap.find p ptmap)
               with Not_found ->
                  Util.crash ("rx: missing predicate " ^ p ^ "!")
            in
            TLetter.iter scan_pred tl
         in
         let tmap = Types.IntMap.find s n_transitions in
         TLetterMap.iter scan_tl tmap
      in
      Types.IntSet.iter scan_state nstates
   in

   (*
    * Make a union transition map over all the NDFA states passed in.
    *)
   let all_ndfa_transitions (nstates: Types.IntSet.t) =
      (*
       * To combine two states (which is what we need to do when we're
       * in multiple states at once), we need to prune back to just the
       * predicate -> dest subset of each state; then union those; then
       * regenerate the tletters.
       *
       * XXX: we know by construction that in the original tlndfa every
       * predicate mentioned anywhere in a transition table exists in it
       * as a singleton. However, are we sure that this will still be
       * true after reversing (or reversing twice)? It doesn't seem
       * obvious. This is the kind of thing that should be checked in
       * the Coq model, but that's not happening this week. For now,
       * we'll specifically check for this case and crash if we hit it.
       * (The check is immediately above.)
       *)
      let ptmaps =
         let addone s sofar =
            let getone tl dests sofar' =
               if TLetter.cardinal tl = 1 then
                  let p = match TLetter.elements tl with
                       [p] -> p
                     | _ -> assert (false)
                  in
                  Types.StringMap.add p dests sofar'
               else sofar'
            in
            let ntmap = Types.IntMap.find s n_transitions in
            (* don't want the empty tletter, it's a special case *)
            let ntmap = TLetterMap.remove TLetter.empty ntmap in
            let ptmap = TLetterMap.fold getone ntmap Types.StringMap.empty in
            ptmap :: sofar
         in
         Types.IntSet.fold addone nstates []
      in

      let anydests =
         let addone s sofar =
            let ntmap = Types.IntMap.find s n_transitions in
            try
               let dests = TLetterMap.find TLetter.empty ntmap in
               Types.IntSet.union sofar dests
            with Not_found -> sofar
         in
         Types.IntSet.fold addone nstates Types.IntSet.empty
      in

      let ptmap = pred_tmap_unionall ptmaps in
      let ptmap =
         if Types.IntSet.is_empty anydests then ptmap
         else Types.StringMap.add "." anydests ptmap
      in

      check_for_missing_predicates ptmap nstates;

      conv_one_pndfa_tmap ptmap
   in

   (*
    * Make a DFA transition map from a single NDFA transition map.
    *)
   let dfa_transitions ntmap =
      (* get the dfa state for each one *)
      let lookup destset =
            getdfastate destset
      in
      TLetterMap.map lookup ntmap
   in

   (* Get the DFA's start state *)
   let d_startstate =
      getdfastate n_startstates
   in

   (* accumulate the DFA's transition table *)
   let d_transitions = ref Types.IntMap.empty in

   (* build a dstate *)
   let build dstate =
      let nstates = Types.IntMap.find dstate !dstate_to_nstates in
      let combined_ntmap = all_ndfa_transitions nstates in
      let transitions = dfa_transitions combined_ntmap in
      d_transitions := Types.IntMap.add dstate transitions !d_transitions
   in

   (* build all the dstates *)
   while !undone_dstates <> [] do
      let dstates = !undone_dstates in
      undone_dstates := [];
      List.iter build dstates
   done;

   (* make the set of accepting states *)
   let d_accepts =
      let checknstate nstate =
         Types.IntSet.mem nstate n_accepts
      in
      let trydstate set dstate =
         let nstates = Types.IntMap.find dstate !dstate_to_nstates in
         (* dstate is accepting if *any* of the nstates are *)
         if Types.IntSet.exists checknstate nstates then
            Types.IntSet.add dstate set
         else set
      in
      let alldstates = intmap_keys !d_transitions in
      List.fold_left trydstate Types.IntSet.empty alldstates
   in

   (* return the DFA *)
   (d_startstate, !d_transitions, d_accepts, !d_nextstatenum)


(*
 * Reverse a DFA. (produces an NDFA, but an NDFA on inputs)
 *)

let tldfa_reverse (dfa: tldfa) : tlndfa =
   let (d_startstate, d_transitions, d_accepts, d_nextstatenum) = dfa in

   (*
    * Convert the transition tables to a list of triples.
    *)
   let triples =
      let convstate (dstate: int) inputmap z =
         let convedge (input: TLetter.t) (nextdstate: int) z' =
            (dstate, input, nextdstate) :: z'
         in
         TLetterMap.fold convedge inputmap z
      in
      Types.IntMap.fold convstate d_transitions []
   in

   (*
    * Make the reverse transition table.
    *)
   let n_transitions =
      let addedge map (lstate, edge, rstate) =
         let tbl =
            try
               Types.IntMap.find rstate map
            with Not_found -> TLetterMap.empty
         in
         let dests =
            try
               TLetterMap.find edge tbl
            with Not_found -> Types.IntSet.empty
         in
         let dests' = Types.IntSet.add lstate dests in
         let tbl = TLetterMap.add edge dests' tbl in
         Types.IntMap.add rstate tbl map
      in
      List.fold_left addedge Types.IntMap.empty triples
   in

   (*
    * Make sure every state appears in n_transitions. A state with no
    * outgoing edges (a legitimate thing) won't otherwise.
    *
    * XXX: does this impair the minimization property of reversing twice?
    *)
   let checkone s _ nt =
      try
         ignore (Types.IntMap.find s nt); nt
      with Not_found -> Types.IntMap.add s TLetterMap.empty nt
   in
   let n_transitions =
      (* fold over d_transitions and add to n_transitions. *)
      Types.IntMap.fold checkone d_transitions n_transitions
   in 

   (*
    * The (one) accepting state is the old startstate.
    *)
   let n_accepts =
      Types.IntSet.add d_startstate Types.IntSet.empty
   in

   (*
    * The start states are the old accepting states.
    *)
   let n_startstates = d_accepts in

   (* return the NDFA *)
   (n_startstates, n_transitions, n_accepts, d_nextstatenum)

(*
 * Minimize a DFA: reverse it twice
 *)
let tldfa_minimize (dfa: tldfa) : tldfa =
   (* this is too easy... *)
   (* tldfa_of_tlndfa (tldfa_reverse (tldfa_of_tlndfa (tldfa_reverse dfa))) *)

   let r1 = tldfa_reverse dfa in
   check_tlndfa "minimize reverse 1" r1;
   let d1 = tldfa_of_tlndfa r1 in
   check_tldfa "minimize determinize 1" d1;
   let r2 = tldfa_reverse d1 in
   check_tlndfa "minimize reverse 2" r2;
   let d2 = tldfa_of_tlndfa r2 in
   check_tldfa "minimize determinize 2" d2;
   d2


(*************************************************************)
(* codegen *)

(*
 * sort for tmap binding lists, by decreasing set size
 *)
let sort_size (tls: (TLetter.t * 'a) list) =
   let cmp (tl1, _) (tl2, _) =
      -(compare (TLetter.cardinal tl1) (TLetter.cardinal tl2))
   in
   List.sort cmp tls

(*
 * A simple way to represent predicate tests as code.
 *)
type xexpr =
     Xconst of int option
   | Xif of string * xexpr * xexpr

(*
 * eval xexpr given a set of preds that are true
 * (aka a tletter)
 *)
let rec xexpr_eval tl xe =
   match xe with
        Xconst oi -> oi
      | Xif (p, xe1, xe2) ->
           xexpr_eval tl (if TLetter.mem p tl then xe1 else xe2)

(*
 * simple optimizations on xexpr
 *)
let rec xexpropt xe0 =
   let rec top xe =
      match xe with
           Xif (_p0, Xconst oi1, Xconst oi2) ->
              if oi1 = oi2 then Xconst oi1
              else xe
         | Xif (p0, Xif (p1, xe1a, _xe1b), xe2) ->
              if p0 = p1 then top (Xif (p0, xe1a, xe2))
              else xe
         | Xif (p0, xe1, Xif (p2, _xe2a, xe2b)) ->
              if p0 = p2 then top (Xif (p0, xe1, xe2b))
              else xe
         | _ -> xe
   in
   match xe0 with
        Xconst oi -> Xconst oi
      | Xif (pred, xe1, xe2) ->
           let xe1' = xexpropt xe1 in
           let xe2' = xexpropt xe2 in
           top (Xif (pred, xe1', xe2'))
   
(*
 * Make a (fully determined) xexpr from a transitionlist and a default
 * destination. The transitionlist should already be sorted.
 *
 * This does not probably produce a good expression tree. In fact, it
 * almost certainly produces a terrible one. XXX.
 *)
let xexpr_of_transitionlist (tlist: (TLetter.t * int) list) (def: int option) =
   let add (tl, s) x0 =
      (* if tl then s else x0... except need to test tl one piece at a time *)
      let tryone pred x =
         Xif (pred, x, x0)
      in
      TLetter.fold tryone tl (Xconst (Some s))
   in
   xexpropt (List.fold_right add tlist (Xconst def))

(*
 * Make an xexpr directly from a transition table.
 *)
let xexpr_of_tmap tmap =
   (* deal with TLetter.empty being special *)
   let defaultdest, tmap =
      try
         let defaultdest = TLetterMap.find TLetter.empty tmap in
         (Some defaultdest, TLetterMap.remove TLetter.empty tmap)
      with Not_found -> None, tmap
   in

   (*
    * sort by decreasing number of elements in the TLetter, as those
    * are more specific and need to be tested first.
    *)
   let transitionlist = sort_size (TLetterMap.bindings tmap) in

   xexpr_of_transitionlist transitionlist defaultdest

(*
 * Similar in concept to Xexpr, but allows for tentative predicates,
 * and allows multiple things to be tested at once.
 *
 * In Yif, the first list of predicates is definite and the second
 * tentative. In Ydecision, the predicate is always tentative.
 *)

type yleaf =
     Yconst of int option
   | Ydecide of string * yleaf * yleaf
type yexpr =
     Yleaf of yleaf
   | Yif of string list * string list * yexpr * yexpr

(*
 * Make a yexpr from a transition list and a default destination,
 * using an xexpr to construct decision trees for the tentative
 * predicates, and a set that tells us which predicates are tentative.
 *)
let yexpr_of_transitionlist tlist def xe alltentatives =
   (* First, divide each predicate set into nontentative and tentative. *)
   let divide (tl, dest) =
      let tentative = TLetter.inter tl alltentatives in
      (TLetter.diff tl tentative, tentative, dest)
   in
   let tlist = List.map divide tlist in

   (* make a decision tree from a set of tentative predicates *)
   let rec mktree (fixed, tentative, dest) =
      if TLetter.is_empty tentative then Yconst (Some dest)
      else if TLetter.cardinal tentative = 1 then begin
         (* get the one predicate *)
         let pred = TLetter.choose tentative in
         let s1 = xexpr_eval (TLetter.add pred fixed) xe in
         let s2 = xexpr_eval fixed xe in
         Ydecide (pred, Yconst s1, Yconst s2)
      end else begin
         let pred = TLetter.choose tentative in
         let tentative' = TLetter.remove pred tentative in
         let t1 = mktree (TLetter.add pred fixed, tentative', dest) in
         let t2 = mktree (fixed, tentative', dest) in
         Ydecide (pred, t1, t2)
      end
   in

   (* Make a yexpr from a tlist *)
   let mkyexpr (fixed, tentative, dest) ye =
      let tree = mktree (fixed, tentative, dest) in
      Yif (TLetter.elements fixed, TLetter.elements tentative,
           Yleaf tree, ye)
   in
   List.fold_right mkyexpr tlist (Yleaf (Yconst def))

(*
 * Make a yexpr directly from a transition table.
 *)
let yexpr_of_tmap tmap xe alltentatives =
   (* deal with TLetter.empty being special *)
   let defaultdest, tmap =
      try
         let defaultdest = TLetterMap.find TLetter.empty tmap in
         (Some defaultdest, TLetterMap.remove TLetter.empty tmap)
      with Not_found -> None, tmap
   in

   (*
    * sort by decreasing number of elements in the TLetter, as those
    * are more specific and need to be tested first.
    *)
   let transitionlist = sort_size (TLetterMap.bindings tmap) in

   yexpr_of_transitionlist transitionlist defaultdest xe alltentatives

(*
 * Given:
 *    tonextstate s ptr: statement to go to another state
 *    doreject ptr: statement to reject
 *    dodecide pred xx xx ptr: statement to make a decisiontree for later
 *    and a ptr,
 * where xx is ptr -> statement,
 * generate Gcode from a yexpr.
 *)
let gcode_of_yexpr tonextstate doreject dodecide ye0 =
   let rec gcode_of_yleaf yl =
      match yl with
           Yconst None -> doreject
         | Yconst (Some s) -> tonextstate s
         | Ydecide (pred, yl1, yl2) ->
              let yl1' = gcode_of_yleaf yl1 in
              let yl2' = gcode_of_yleaf yl2 in
              dodecide pred yl1' yl2'
   in
   let rec doit ye =
      match ye with
           Yleaf yl -> gcode_of_yleaf yl
         | Yif (fixed, tentative, ye1, ye2) ->
              let mktest qual pred =
                 G.READVAR (G.BOOL, pred ^ "_" ^ qual ^ "true")
              in
              let tests =
                 List.map (mktest "is") fixed @
                 List.map (mktest "maybe") tentative
              in
              let test = List.fold_right G.logand tests (G.boolconst true) in
              let ye1' = doit ye1 in
              let ye2' = doit ye2 in
              fun p -> [G.IF (test, G.BLOCK (ye1' p), G.BLOCK (ye2' p))]
   in
   doit ye0
      

(*
 * Given:
 *    fetchstate: expression to read the current state
 *    tonextstate (s: int): statement to update the state
 *    doaccept: statement to accept
 *    doreject: statement to reject
 *    dodecide: statement to make decision tree
 *    alltentatives: predicate set of not-yet-decided predicates
 *
 * generate code to test the predicates and figure out what happens.
 * Speculating version where some predicates may not yet have a fixed
 * value.
 *)
let advance_dfa_spec (dfa: tldfa)
			fetchstate tonextstate doaccept doreject dodecide
			alltentatives ptr =
   let (_startstate, transitions, accepts, _nextstatenum) = dfa in

   let tonextstate' s =
      if Types.IntSet.mem s accepts then doaccept
      else tonextstate s
   in

   let mkcase (s, tmap) =
      let stmts =
         let xe = xexpr_of_tmap tmap in
         let ye = yexpr_of_tmap tmap xe alltentatives in
         gcode_of_yexpr tonextstate' doreject dodecide ye ptr
      in
      (G.INTCONSTANT (G.UINT, string_of_int s), G.BLOCK stmts)
   in
   let cases =
      List.map mkcase (Types.IntMap.bindings transitions)
   in
   let defcase =
      G.ASSERT (G.boolconst false)
   in
   G.SWITCH (fetchstate, cases, Some defcase)

(*
 * Similarly but for nonspeculating execution.
 *
 * Pass dummy stuff to the speculating version, even though that's
 * overkill.
 *)
let advance_dfa (dfa: tldfa) fetchstate tonextstate doaccept doreject ptr =
   (* these should be obvious if they appear in the output *)
   let dodecide _ _ _ _ =
      [G.ASSIGN (G.WRITEVAR (G.VOID, "wrong"), G.boolconst false)]
   in
   let xe = Xconst (Some (-1)) in
   let alltentatives = TLetter.empty in

   let (_startstate, transitions, accepts, _nextstatenum) = dfa in

   let tonextstate' s =
      if Types.IntSet.mem s accepts then doaccept
      else tonextstate s
   in

   let mkcase (s, tmap) =
      let stmts =
         let ye = yexpr_of_tmap tmap xe alltentatives in
         gcode_of_yexpr tonextstate' doreject dodecide ye ptr
      in
      (G.INTCONSTANT (G.UINT, string_of_int s), G.BLOCK stmts)
   in
   let cases =
      List.map mkcase (Types.IntMap.bindings transitions)
   in
   let defcase =
      G.ASSERT (G.boolconst false)
   in
   G.SWITCH (fetchstate, cases, Some defcase) 

(*************************************************************)
(* interface *)

let compile_rx (dumpinfo: Dumpinfo.t) (r: rx) =
   let dodump headertext f code =
      Dumpinfo.trysubdump ("*** " ^ headertext ^ " ***") dumpinfo f code
   in

   let d_r = dodump "input regexp" dump_rx r in

   let r' = rx_baseopt r in
   let d_r' = dodump "rx_baseopt" dump_rx r' in

   let pndfa = pndfa_of_rx r' in
   let d_pndfa = dodump "pndfa_of_rx" dump_pndfa pndfa in
   check_pndfa "compile" pndfa;

   let pndfa' = pndfa_unepsilon pndfa in
   let d_pndfa' = dodump "pndfa_unepsilon" dump_pndfa pndfa' in
   check_pndfa "unepsilon" pndfa';

   let pndfa'' = pndfa_unref pndfa in
   let d_pndfa'' = dodump "pndfa_unref" dump_pndfa pndfa'' in
   check_pndfa "unref" pndfa'';

   let tlndfa = tlndfa_of_pndfa pndfa'' in
   let d_tlndfa = dodump "tlndfa_of_pndfa" dump_tlndfa tlndfa in
   check_tlndfa "alphabetize" tlndfa;

   let tldfa = tldfa_of_tlndfa tlndfa in
   let d_tldfa = dodump "tldfa_of_tlndfa" dump_tldfa tldfa in
   check_tldfa "determinize" tldfa;

   let tldfa' = tldfa_minimize tldfa in
   let d_tldfa' = dodump "tldfa_minimize" dump_tldfa tldfa' in
   check_tldfa "minimize" tldfa;

   let dump = String.concat "\n" [
      d_r; d_r';
      d_pndfa; d_pndfa'; d_pndfa'';
      d_tlndfa;
      d_tldfa; d_tldfa';
   ] in
   (tldfa', dump)
