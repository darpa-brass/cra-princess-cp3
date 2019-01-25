# Dependencies

OCaml >= 4.06.0

{macos}
brew install ocaml
brew install opam
opam init
opam config env

{ubuntu 17.10}
apt-get install ocaml
apt-get install opam
apt-get install m4
opam init
opam config env
opam switch 4.06.0
#just start a new shell at this point

{both}
opam install ocamlbuild
opam install ocamlfind
opam install num
opam install menhir

{pkgsrc on netbsd, solaris, etc.}
pkgin install ocaml ocaml-findlib ocamlbuild ocaml-num menhir

# Building

* `make` to build
* `make clean` to clean the ./_build directory created by ocamlbuild

# Running

`./cassiopeia examples/[desired example].casp`

# Installing

(no install procedure yet)
