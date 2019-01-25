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

(*
 * The hazard.def file defines:
 *    - instruction predicates (expressions over instruction fields)
 *    - hazard conditions
 *    - jump instruction conditions
 *)

(*
 * A cond is a regular expression over instructions, written in
 * terms of instruction predicates.
 *)
type cond =
     COND_ANY
   | COND_PREDNAME of string
   | COND_PREDEXPR of Exprtree.expr
   | COND_SEQ of cond * cond
   | COND_ALT of cond * cond
   | COND_OPT of cond
   | COND_PLUS of cond

(*
 * Because of the way the internals are structured, predicates can
 * be declared by name in advance; those that don't come that way
 * are factored out and assigned a scratch name.
 *)
type predicate_name_or_expr =
     P_BYNAME of string
   | P_BYEXPR of Exprtree.expr

(*
 * An assignment is a binding of a value to a (fresh) name. These
 * appear in hazards to allow remembering properties of the trigger
 * instruction for subsequent matching.
 *)
type assignment =
   ASSIGN of Pos.pos * string * Exprtree.expr

(*
 * A matcher is a full specification of an instruction sequence match
 * automaton: it has
 *    - a guard expression (the matcher is only "live" when this is true;
 *      it is a predicate on the assembler state, not on instructions)
 *    - a list of assignments for variables to bind values from the
 *      trigger expression for use in the condition;
 *    - a trigger predicate (when this matches, the hazard is triggered);
 *    - a condition (this is what describes what must follow the trigger);
 *
 * This is shared between hazards and transfer specs.
 *)
type matcher = {
   guard: Exprtree.expr;
   assignments: assignment list;
   trigger: predicate_name_or_expr;
   condition: cond;
}

(*
 * A hazard is a full specification of a single hazard; it has a name
 * (this may ultimately be of little value and might go away) and a
 * description (this is user-facing), plus a matcher spec.
 *
 * The hazard is triggered when the matcher triggers; it is discharged
 * when the matcher condition accepts.
 *)
type hazard = {
   name: string;
   definedat: Pos.pos;
   desc: string;

   m: matcher;
}

(*
 * A transfer is a specification of a jump or branch instruction.
 * It has:
 *    - a matcher specification;
 *    - a result, which describes what happens when the transfer
 *      takes effect:
 *          * EITHER marks a branch, that can go two ways and is
 *            modeled as nondeterministically taking both;
 *          * NULLIFY_AND specifies that the instructions between
 *            the control transfer instruction and the actual
 *            control transfer are not executed;
 *          * GO means the control transfer goes somewhere else
 *            (exactly where is deduced/specified in the encodings);
 *          * STAY means the control transfer doesn't go anywhere
 *            else.
 *
 * The matcher's trigger should match the actual jump instruction.
 * When the matcher's condition accepts is when the actual jump
 * happens. (This may not be immediate, e.g. in the presence of
 * delay slots.)
 *
 * A vanilla branch instruction is written EITHER (GO, STAY) or
 * EITHER (STAY, GO). A jump is written GO. A branch-never (these
 * exist due to instruction set symmetries on some architectures)
 * is written STAY.
 *
 * EITHER is not allowed to appear except at the top level, and
 * NULLIFY_AND appears only once. This is enforced by a combination
 * of the parser and the hazardcheck pass.
 *)

type destination =
     GO				(* go elsewhere *)
   | STAY			(* stay here *)

type transference =
     EXECUTE_AND of destination
   | NULLIFY_AND of destination	(* do not execute intervening instructions *)

type transfertype =
     JUMP of transference
   | BRANCH of transference * transference

let jump = JUMP (EXECUTE_AND GO)
let branch = BRANCH (EXECUTE_AND GO, EXECUTE_AND STAY)
let branch_likely = BRANCH (EXECUTE_AND GO, NULLIFY_AND STAY)

type transfer = {
   definedat: Pos.pos;

   m: matcher;
   result: transfertype;
}

type predicatedecl = {
   definedat: Pos.pos;
   args: Pos.pos Types.StringMap.t;
   afields: Types.StringSet.t;  (* fields needed to evaluate args *)
   e: Exprtree.expr;
}

(*
 * The full set of decls coming from hazard.def.
 *)
type decls = {
   predicates: predicatedecl Types.StringMap.t;
   predorder: string list;
   hazards: hazard list;
   transfers: transfer list;
}
