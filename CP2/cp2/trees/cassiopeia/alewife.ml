open Batteries

module ALex = Ale_lex
module AAst = Ale_ast
module CLex = Lex
module CAst = Ast

module A   = Arg
module S   = Sys
module P   = Printf
module O   = Options

let (++) = (^)

let alewife_file = ref ""
let afile = alewife_file

let usage =
  "usage: " ++ exe ++ " [alewife_file] [cassiopeia_file] [-o output_file]"

let outfile:  string ref  = ref ""
let opts = [
  ("-o", A.Set_string outfile, "")]

let parse_args () =
  A.parse opts (fun f -> afile := f) usage

let main () =
  let _   = parse_args () in
  let _   = assert (!afile <> "") in
  let _   = P.printf "Parsing %s...\n" !afile in
  let ale = Ale_lex.read !afile in
  let ale = match ale with
    | ([], [], [], [], [], []) -> !afile ++ " is empty\n" |> failwith
    | _ -> ale in
  let _   = P.printf "parsed.\n" in
  let _   =
    ale |>
    Ale_ast.string_of_ast |>
    P.printf "Saw program: \n\t%s.\n" in
  let out_ch =
    if !outfile <> "" then open_out !outfile
    else stdout
  in
  let _   =
    ale |>
    Ale_spec.spec_of_ast |>
    P.fprintf out_ch "%s\n"
  in
  0

let _ = main ()
