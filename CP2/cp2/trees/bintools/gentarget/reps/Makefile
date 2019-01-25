GENTOP=..
include $(GENTOP)/mk/genbase.mk

LIB=reps
SRCS=\
	typerep.ml \
	exprrep.ml \
	exprtypeinf.mli exprtypeinf.ml \
	exprtypecheck.mli exprtypecheck.ml \
	exprtransform.mli exprtransform.ml \
	exprutil.mli exprutil.ml \
	typebuild.ml \
	exprbuild.ml \
	hazresolve.mli hazresolve.ml \
        predsplit.mli predsplit.ml

SUPPORTDIR=../support
OCAMLINCS+=-I $(SUPPORTDIR)
#OCAMLLIBS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(SUPPORTDIR)/libsupport.$(OCAMLLIBEXT)

PARSETREESDIR=../parsetrees
OCAMLINCS+=-I $(PARSETREESDIR)
#OCAMLLIBS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)
#OCAMLLIBDEPS+=$(PARSETREESDIR)/libparsetrees.$(OCAMLLIBEXT)

include $(GENTOP)/mk/ocaml.mk
