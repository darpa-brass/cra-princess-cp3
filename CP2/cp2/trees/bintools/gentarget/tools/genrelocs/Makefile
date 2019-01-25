GENTOP=../..
include $(GENTOP)/mk/genbase.mk

PROG=genrelocs
SRCS=\
	rep.ml dumprep.mli dumprep.ml \
	typeinf.ml typecheck.ml transform.ml \
	mkrelocs.mli mkrelocs.ml \
	buildrep.mli buildrep.ml main.ml

SUPPORTDIR=../../support
PARSETREESDIR=../../parsetrees
PARSERSDIR=../../parsers
REPSDIR=../../reps
OUTPUTDIR=../../output

#
# Note: unlike with normal Unix C libs, which work the other way
# around, OCAMLLIBS must be ordered with lower-level stuff first;
# otherwise the higher-level stuff won't link to it.
#

#OCAMLLIBS+=unix.$(OCAMLLIBEXT) nums.$(OCAMLLIBEXT)
OCAMLLIBS+=nums.$(OCAMLLIBEXT)

OCAMLINCS+=-I $(SUPPORTDIR)
OCAMLLIBS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)
OCAMLLIBDEPS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)

OCAMLINCS+=-I $(PARSETREESDIR)
OCAMLLIBS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)
OCAMLLIBDEPS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)

OCAMLINCS+=-I $(PARSERSDIR)
OCAMLLIBS+=$(PARSERSDIR)/libparsers.$(OCAMLLIBEXT)
OCAMLLIBDEPS+=$(PARSERSDIR)/libparsers.$(OCAMLLIBEXT)

OCAMLINCS+=-I $(REPSDIR)
OCAMLLIBS+=$(REPSDIR)/libreps.$(OCAMLLIBEXT)
OCAMLLIBDEPS+=$(REPSDIR)/libreps.$(OCAMLLIBEXT)

OCAMLINCS+=-I $(OUTPUTDIR)
OCAMLLIBS+=$(OUTPUTDIR)/liboutput.$(OCAMLLIBEXT)
OCAMLLIBDEPS+=$(OUTPUTDIR)/liboutput.$(OCAMLLIBEXT)

include $(GENTOP)/mk/ocaml.mk
