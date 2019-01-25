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

(*
 * structured text representation
 *)

open Textrep

(*let indentsize = 3*)
let indentstring = "   "

(*
let isspaces s =
   let l = String.length s in
   s = String.make l ' '
*)

let rec addspace texts = match texts with
     NL :: OPERATOR b :: more ->
        NL :: SPACE :: addspace (OPERATOR b :: more)
   | WORD "" :: more ->
        addspace more
   | WORD a :: WORD b :: more ->
        WORD a :: SPACE :: addspace (WORD b :: more)
   | WORD a :: OPERATOR b :: more ->
        WORD a :: SPACE :: addspace (OPERATOR b :: more)
   | WORD a :: PREFIX b :: more ->
        WORD a :: SPACE :: addspace (PREFIX b :: more)
   | OPERATOR a :: WORD b :: more -> 
        OPERATOR a :: SPACE :: addspace (WORD b :: more)
   | OPERATOR a :: OPERATOR b :: more -> 
        OPERATOR a :: SPACE :: addspace (OPERATOR b :: more)
   | OPERATOR a :: PREFIX b :: more -> 
        OPERATOR a :: SPACE :: addspace (PREFIX b :: more)
   | SUFFIX a :: WORD b :: more -> 
        SUFFIX a :: SPACE :: addspace (WORD b :: more)
   | SUFFIX a :: OPERATOR b :: more -> 
        SUFFIX a :: SPACE :: addspace (OPERATOR b :: more)
   | SUFFIX a :: PREFIX b :: more -> 
        SUFFIX a :: SPACE :: addspace (PREFIX b :: more)
   | PARENS a :: BRACES b :: more ->
        addspace (PARENS a :: SPACE :: BRACES b :: more)
   | text :: more ->
        let text' = match text with
             NL | SPACE | WORD _ | OPERATOR _ | PREFIX _ | SUFFIX _ -> text
           | BRACES subtexts -> BRACES (addspace subtexts)
           | PARENS subtexts -> PARENS (addspace subtexts)
           | INDENT subtexts -> INDENT (addspace subtexts)
        in
        text' :: addspace more
   | [] -> []

let indent texts =
   (*
    * If INDENT starts after the beginning of a line, push it forward
    * to the beginning of the next line. Also make sure we end with a
    * newline overall.
    *)
(* after all that, don't actually need this I think
   let pushbeginning texts =
      let rec wrap depth ts =
         match depth with
              0 -> ts
            | n -> INDENT (wrap (n-1) ts)
      in
      let rec push results atbol depth ts =
         match ts with
              [] ->
                 (List.rev results, atbol, depth)
            | NL :: more ->
                 push (NL :: results) true 0 (wrap depth more)
            | (INDENT subtexts) :: more ->
                 assert(depth = 0);
                 if atbol then
                    let (subtexts, atbol, _) =
                       push [] true 0 subtexts
                    in
                    push ((INDENT subtexts) :: results) atbol 0 more
                 else
                    let (subtexts, atbol, depth') =
                       push [] false (depth+1) subtexts
                    in
                    if depth' == 0 then
                       (* crossed a newline *)
                       let more = wrap depth more in
                       push ((INDENT subtext) :: results) atbol 0 more
                    else
                       (* didn't; this indent had no newlines so drop it *)
                       let results = List.rev subtexts @ results in
                       push results atbol depth more
            | (BRACES subtexts) :: more ->
                 let (subtexts, _, _) = push [] false depth subtexts in
                 push ((BRACES subtexts) :: results) false depth more
            | (PARENS subtexts) :: more ->
                 let (subtexts, _, _) = push [] false depth subtexts in
                 push ((PARENS subtexts) :: results) false depth more
            | t :: more ->
                 push (t :: results) false depth more
      in
      let (texts, atbol, _depth) = push [] true 0 texts in
      if atbol = false then
         texts @ [NL]
      else texts
   in
*)
   (*
    * Insert spaces for indentation at the beginning of each line.
    * Because we laboriously did pushbeginning we know INDENT only
    * happens at beginnings of lines so we don't need to check that.
    *)
   let doindent texts =
      let rec go spaces ts results = match ts with
	   [] -> (List.rev results, [])
	 | NL :: [] -> (List.rev results, [NL])
         | NL :: (INDENT subtexts) :: more ->
              go spaces ((INDENT (NL :: subtexts)) :: more) results
         | NL :: more ->
              go spaces more ((WORD spaces) :: NL :: results)
         | (INDENT subtexts) :: more ->
              let (subtexts, nl) = go (spaces ^ indentstring) subtexts [] in
              go spaces (nl @ more) ((INDENT subtexts) :: results)
         | (BRACES subtexts) :: more ->
              let (subtexts, nl) = go spaces subtexts [] in
              let nl = match nl with
                   [] -> []
                 | _ -> nl @ [WORD spaces]
              in
              go spaces more ((BRACES (subtexts @ nl)) :: results)
         | (PARENS subtexts) :: more ->
              let (subtexts, nl) = go spaces subtexts [] in
              let nl = match nl with
                   [] -> []
                 | _ -> nl @ [WORD spaces]
              in
              go spaces more ((PARENS (subtexts @ nl)) :: results)
         | t :: more ->
              go spaces more (t :: results)
      in
      let (results, _nl) = go "" texts [] in
      results @ [NL]
   in
(* let texts = pushbeginning texts in *)
   doindent texts

type pick = (int * int * int * int) list

(* XXX doesn't work yet
let wordwrap texts =
   let rec lookahead results startcol curcol ts =
      let here = (curcol, startcol) in
      let results' = here :: results in
      let simple s more =
         lookahead results' startcol (curcol + String.length s) more
      in
      let pairing subtexts more = 
         let nextcol = curcol + 1 in
         let (results, curcol) = lookahead results' nextcol nextcol subtexts in
         lookahead results startcol (curcol + 1) more
      in
      match ts with
           [] -> (List.rev results, curcol)
         | NL :: _ -> (List.rev results, curcol)
         | SPACE :: more -> simple " " more
         | WORD s :: more -> simple s more
         | OPERATOR s :: more -> simple s more
         | PREFIX s :: more -> simple s more
         | SUFFIX s :: more -> simple s more
         | (BRACES subtexts) :: more -> pairing subtexts more
         | (PARENS subtexts) :: more -> pairing subtexts more
         | (INDENT subtexts) :: more ->
              lookahead results startcol curcol (subtexts @ more)
   in
   let plan startcol curcol ts =
      let width = 79 in
      let (results, lastcol) = lookahead [] startcol curcol ts in
      let fixcol (cc, sc) =
         (cc, if sc < startcol + 3 then startcol + 3 else sc)
      in
      let results = List.map fixcol results in
      let results = List.filter (fun (cc, sc) -> cc > sc) results in
      let results = List.sort_uniq (Pervasives.compare) results in

      (* a < b if a is better than b *)
      let sortpicks (a : pick) b =
         let sq x = x * x in
         let rec compute xs = match xs with
              [] -> (width, sq (lastcol - startcol))
            | (_cc, sc, len1, len2) :: [] ->
                 (sc, sq len1 + sq len2)
            | (_cc, sc, len1, _len2) :: more ->
                 let (tsc, tsq) = compute more in
                 (sc + tsc, sq len1 + tsq)
         in
         let (tsc_a, tsq_a) = compute a in
         let (tsc_b, tsq_b) = compute b in

         (*
          * less total indented space (tsc) is good
          * less squared displayed length (tsq) is good
          * (prefers breakdowns of relatively even length)
          *
          * not clear how to weight these... taking them
          * sequentially is probably worse
          *)
         if (tsq_a < tsq_b) then -1
         else if (tsq_a > tsq_b) then 1
         else if (tsc_a < tsc_b) then -1
         else if (tsc_a > tsc_b) then 1
         else 0
      in
      let mergepicks (pick : pick) (picks : pick list) =
         Util.take 5 (List.sort sortpicks (pick :: picks))
      in
      let rec dopick sc0 choices lc w =
         match choices with
              [] -> []
            | (cc, sc) :: more ->
                 if cc >= w then []
                 else begin
                    let len1 = cc - sc0 in
                    let len2 = lc - cc in
                    let picks = dopick sc more lc (w + sc0 - sc) in
                    let picks = mergepicks [(cc, sc, len1, len2)] picks in
                    if w - len1 > width then
                       let morepicks (pick : pick) : pick list =
                          let (_cc', sc', _len1', _len2') = List.hd pick in
                          let picks' = dopick sc' more lc (w - len1) in
                          List.map (fun p -> p @ pick) picks'
                       in
                       let picks' = List.concat (List.map morepicks picks) in
                       Util.take 5 (List.sort sortpicks picks')
                    else
                       picks
                 end
      in
      let picks = dopick startcol results lastcol width in
      match picks with
           [] -> []
         | pick :: _ -> List.map (fun (cc, _sc, _len1, _len2) -> cc) pick
   in

   let rec startline spaces col output ts = match ts with
        [] -> (col, List.rev output, [])
      | NL :: more ->
           startline "" 0 (NL :: output) more
      | SPACE :: more ->
           startline (spaces ^ " ") (col + 1) (SPACE :: output) more
      | (WORD s) :: more ->
           let output = (WORD s) :: output in
           if isspaces s then
              startline (spaces ^ s) (col + String.length s) output more
           else
              let col' = (col + String.length s) in
              scan (spaces ^ s) col' col' output more
      | t :: more ->
           scan spaces col col output (t :: more)
   and scan spaces startcol curcol output ts = match ts with
        [] -> (curcol, List.rev output, [])
      | NL :: more ->
          startline "" 0 (NL :: output) more
      | t :: more ->
          let pick = plan startcol curcol more in
          (* pick is a list of columns to split at *)
          dosplit spaces curcol output (t :: more) pick
   and dosplit spaces curcol output ts pick =
      let (splitit, pick') = match pick with
           [] -> (false, [])
         | cc :: more -> if cc <= curcol then (true, more) else (false, pick)
      in
      let output = if splitit then WORD spaces :: NL :: output else output in
      let simple t s more =
         dosplit spaces (curcol + String.length s) (t :: output) more pick'
      in
      let matching f k ts more =
         let (curcol, ts', pick) = dosplit spaces (curcol + k) [] ts pick in
         dosplit spaces (curcol + k) (f ts' :: output) more pick
      in
      match ts with
           [] -> (curcol, List.rev output, pick)
         | NL :: more -> startline "" 0 (NL :: output) more
         | SPACE :: more -> simple SPACE " " more
         | (WORD s) :: more -> simple (WORD s) s more
         | (OPERATOR s) :: more -> simple (OPERATOR s) s more
         | (PREFIX s) :: more -> simple (PREFIX s) s more
         | (SUFFIX s) :: more -> simple (SUFFIX s) s more
         | (BRACES ts) :: more -> matching (fun x -> BRACES x) 1 ts more
         | (PARENS ts) :: more -> matching (fun x -> PARENS x) 1 ts more
         | (INDENT ts) :: more -> matching (fun x -> INDENT x) 0 ts more
   in

(*
   let rec getwidth t = match t with
        NL -> 0
      | SPACE -> 1
      | WORD s -> String.length s
      | OPERATOR s -> String.length s
      | PREFIX s -> String.length s
      | SUFFIX s -> String.length s
      | BRACES ts -> 1 + List.fold_left (+) 0 (List.map getwidth ts) + 1
      | PARENS ts -> 1 + List.fold_left (+) 0 (List.map getwidth ts) + 1
      | INDENT ts -> List.fold_left (+) 0 (List.map getwidth ts)
   in
   let texts' = List.map (fun t -> (t, getwidth t)) texts in
*)
   let (_col, texts', _pick) = startline "" 0 [] texts in
   texts'
*)

let wordwrap texts = texts


let string_of_texts texts =
   let rec conv text = match text with
        NL -> "\n"
      | SPACE -> " "
      | WORD s -> s
      | OPERATOR s -> s
      | PREFIX s -> s
      | SUFFIX s -> s
      | BRACES stuff -> "{" ^ convmap stuff ^ "}"
      | PARENS stuff -> "(" ^ convmap stuff ^ ")"
      | INDENT stuff -> convmap stuff
   and convmap texts =
      String.concat "" (List.map conv texts)
   in
   convmap texts

let rec dump'text indent text =
   let d s =
      [indent ^ s]
   in
   let sub xs =
      List.concat (List.map (dump'text (indent ^ indentstring)) xs)
   in
   match text with
        NL -> d "NL"
      | SPACE -> d "SPACE"
      | WORD x -> d ("WORD \"" ^ x ^ "\"")
      | OPERATOR x -> d ("OPERATOR " ^ x)
      | PREFIX x -> d ("PREFIX " ^ x)
      | SUFFIX x -> d ("SUFFIX " ^ x)
      | BRACES xs -> d ("{") @ sub xs @ d ("}")
      | PARENS xs -> d ("(") @ sub xs @ d (")")
      | INDENT xs -> d ("INDENT") @ sub xs

let dump texts =
   String.concat "\n" (List.concat (List.map (dump'text "") texts))

let format dumpinfo text =
   let d what tx =
      Dumpinfo.trydump' what dumpinfo dump tx
   in

   d "text" text;

   let text = addspace text in
   d "spacing" text;

   let text = indent text in
   d "indented" text;

   let text = wordwrap text in
   d "wrapped" text;

   text
