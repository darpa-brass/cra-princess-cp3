GENTOP=..
include $(GENTOP)/mk/genbase.mk

LIB=output
SRCS=\
	gcode.ml gdump.ml \
	ccode.ml cdump.ml \
	textrep.ml \
	text.mli text.ml \
	gtoc.mli gtoc.ml \
	ctotext.mli ctotext.ml \
	output.mli output.ml \
	typeemit.ml expremit.ml

SUPPORTDIR=../support
OCAMLINCS+=-I $(SUPPORTDIR)
#OCAMLLIBS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)

REPSDIR=../reps
OCAMLINCS+=-I $(REPSDIR)
#OCAMLLIBS+=$(REPSDIR)/libreps.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(REPSDIR)/libreps.$(OCAMLLIBEXT)

include $(GENTOP)/mk/ocaml.mk
