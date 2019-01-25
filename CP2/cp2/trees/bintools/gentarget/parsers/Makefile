GENTOP=..
include $(GENTOP)/mk/genbase.mk

LIB=parsers
SRCS=\
	lextools.ml \
	baseparse.mly baselex.mll \
	miscparse.mly misclex.mll \
	langparse.mly langlex.mll \
	modeparse.mly modelex.mll \
	modifierparse.mly modifierlex.mll \
        hazardparse.mly hazardlex.mll \
	relocsparse.mly relocslex.mll \
	encodingparse.mly encodinglex.mll \
	opmatchparse.mly opmatchlex.mll

SUPPORTDIR=../support
OCAMLINCS+=-I $(SUPPORTDIR)
#OCAMLLIBS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)

PARSETREESDIR=../parsetrees
OCAMLINCS+=-I $(PARSETREESDIR)
#OCAMLLIBS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)

include $(GENTOP)/mk/ocaml.mk
