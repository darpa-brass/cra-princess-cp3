GENTOP=..
include $(GENTOP)/mk/genbase.mk

LIB=support
SRCS=\
	util.ml upcase.mlx types.ml pos.ml \
	tsort.mli tsort.ml \
	dumpinfo.mli dumpinfo.ml \
	dumptools.ml

include $(GENTOP)/mk/ocaml.mk

upcase.ml: upcase.mlx
	sed < upcase.mlx -e 's/@OCAML_UPPERCASE@/$(OCAML_UPPERCASE)/' > $@.new
	mv -f $@.new $@
