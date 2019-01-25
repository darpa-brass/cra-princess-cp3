GENTOP=..
include $(GENTOP)/mk/genbase.mk

LIB=parsetrees
SRCS=\
	typetree.ml typedump.ml \
	exprtree.ml exprdump.ml \
	\
	basetree.ml basedump.ml basecheck.mli basecheck.ml \
	misctree.ml miscdump.ml misccheck.mli misccheck.ml \
	langtree.ml langdump.ml langcheck.mli langcheck.ml \
	modetree.ml modedump.ml \
	modifiertree.ml modifierdump.ml \
	hazardtree.ml hazarddump.ml hazardcheck.mli hazardcheck.ml \
	relocstree.ml relocsdump.ml relocscheck.mli relocscheck.ml \
	encodingtree.ml encodingdump.ml encodingcheck.mli encodingcheck.ml \
	opmatchtree.ml opmatchdump.ml opmatchcheck.mli opmatchcheck.ml

SUPPORTDIR=../support
OCAMLINCS+=-I $(SUPPORTDIR)
#OCAMLLIBS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)

include $(GENTOP)/mk/ocaml.mk
