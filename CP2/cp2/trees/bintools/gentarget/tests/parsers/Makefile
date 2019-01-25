GENTOP=../..
include $(GENTOP)/mk/genbase.mk

TESTS=\
	base-01 \
	encoding-01 \
	hazard-01 \
	lang-01 \
	misc-01 \
	mode-01 \
	modifier-01 \
	opmatch-01 \
	relocs-01

all: run-tests $(WAIT) show-diffs

run-tests:;

.for T in $(TESTS)
run-tests: $(T).diff
$(T).diff: $(T).good $(T).out
	diff -u $(T).good $(T).out > $@ || true
$(T).out: ../../testprogs/$(T:C/-.*//)/$(T:C/-.*//) $(T).def
	../../testprogs/$(T:C/-.*//)/$(T:C/-.*//) $(T).def \
		>$@ 2>&1 || echo FAILED >> $@
.endfor

show-diffs:
.for T in $(TESTS)
	@cat $(T).diff
.endfor

good:
.for T in $(TESTS)
	cp $(T).out $(T).good
.endfor

clean:
	rm -f *.out *.diff
