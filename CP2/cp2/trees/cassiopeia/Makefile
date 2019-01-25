BYTE_CASP=cassiopeia.byte
PROG_CASP=cassiopeia
BYTE_ALE=alewife.byte
PROG_ALE=alewife

FLAGS=\
	-use-ocamlfind \
	-tag debug -tag safe_string \
	-tag warn\(A-4-27-33-40-42-44-60\) \
	-tag dtypes -tag annot \
	-use-menhir -menhir 'menhir --explain'

all: cassiopeia alewife

ML_GEN=$(wildcard *.ml.gen)
%.ml: %.ml.gen ml_gen.sh
	./ml_gen.sh $@ $<

cassiopeia: $(ML_GEN:.ml.gen=.ml)
	ocamlbuild ${FLAGS} ${BYTE_CASP}
	mv ${BYTE_CASP} ${PROG_CASP}

alewife:
	ocamlbuild ${FLAGS} ${BYTE_ALE}
	mv ${BYTE_ALE}  ${PROG_ALE}

regress:
	(cd regressiontest && $(MAKE) && $(MAKE) check-diffs)

clean:
	rm -f $(ML_GEN:.ml.gen=.ml)
	rm -rf _build cassiopeia alewife

distclean: clean

.PHONY: all rules depend regress clean distclean

