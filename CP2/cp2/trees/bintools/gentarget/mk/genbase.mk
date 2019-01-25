REALTOP?=$(GENTOP)/..

# Defaults for things that defs.mk sets (for gentarget tree)

# We don't worry about choosing a target here (you can build any or all)
# We also don't install anything (except in the outer source tree) so we
# don't need installation paths.

#
# C
#
# Default C compiler - this is always the native/host compiler.
# (It doesn't make sense to crosscompile the gentarget tree - you
# want to run it on your build machine.)
#
CC=cc
CFLAGS=$(OPT)
OPT=-O
AR=ar
RANLIB=ranlib
LDFLAGS=
LIBS=

#
# OCaml
#
# OCaml comes two ways: there's a native compiler that supports only
# some platforms, and a byte-compiler for the rest. This affects the
# output filenames. defs.mk should set OCAMLTYPE to either "byte" or
# "native" to choose one or the other.
#

OCAML.byte=ocamlc
OCAMLOEXT.byte=cmo
OCAMLLIBEXT.byte=cma
OCAMLDEPNATIVE.byte=
OCAMLOPT.byte=  # -g to debug, -p to profile
OCAMLPIC.byte=

OCAML.native=ocamlopt
OCAMLOEXT.native=cmx
OCAMLLIBEXT.native=cmxa
OCAMLDEPNATIVE.native=-native
OCAMLOPT.native=-O2  # -g to debug, -p to profile
OCAMLPIC.native=-nodynlink -fno-PIC

OCAML=$(OCAML.$(OCAMLTYPE))
OCAMLOEXT=$(OCAMLOEXT.$(OCAMLTYPE))
OCAMLLIBEXT=$(OCAMLLIBEXT.$(OCAMLTYPE))
OCAMLDEPNATIVE=$(OCAMLDEPNATIVE.$(OCAMLTYPE))
OCAMLOPT=$(OCAMLOPT.$(OCAMLTYPE))
OCAMLPIC=$(OCAMLPIC.$(OCAMLTYPE))

OCAMLWARNS=-w +27+29+32+39+41+44+45 -warn-error +a \
		-safe-string -strict-formats
# -short-paths

# these are the same either way
OCAMLIEXT=cmi
OCAMLDEP=ocamldep
OCAMLYACC=ocamlyacc
OCAMLLEX=ocamllex

# default to native since most people's fast build machines are x86
OCAMLTYPE=native
#OCAMLTYPE=byte

# version-specific ocaml properties
OCAML_UPPERCASE=uppercase_ascii  # ocaml 4.03+ (earlier, just "uppercase")


############################################################

-include ../defs.mk

# The gentarget tree requires BSD make, so set WAIT unconditionally to .WAIT.
WAIT=.WAIT

