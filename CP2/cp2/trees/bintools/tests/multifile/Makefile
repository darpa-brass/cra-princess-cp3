TOP=../..
include $(TOP)/mk/base.mk

SOURCEDIR=../sources/$(CPU)
GOODDIR=../sources/$(CPU)

.include "$(SOURCEDIR)/TESTS.mk"

TEST_AS=../../progs/as/main/new-as
TEST_NM=../../progs/nm/new-nm
TEST_OBJDUMP=../../progs/objdump/main/new-objdump
TEST_SIZE=../../progs/size/new-size

TEST_AR=../../progs/ar/new-ar
TEST_RANLIB=../../progs/ranlib/new-ranlib
TEST_LD=../../progs/ld/main/new-ld

all: run-tests .WAIT show-diffs

#
# First, assemble all the sources for each library and each program.
# We don't dump the output or check the results; this is done in
# the singlefile tests. If those fail, nothing here is likely to
# work anyway. For each file we generate a .o file; for sources in
# shared libs we generate a .pico (PIC object) file as well.
#
# Then for each library we construct:
#   - a plain .a file with ar
#   - a ranlib'd version of the .a file
#   - an ld -r .o file with ld
#   - an .a file wrapping the previous
#   - a ranlib'd version of that .a file
#
# and for each shared library additionally
#   - a plain .pica file (PIC .a) with ar from the .pico files
#   - a ranlib'd version of that
#   - an ld -r .pico file 
#   - a .pica file wrapping the previous
#   - a ranlib'd version of that
#   - a -shared .so file with ld built from the .pico files
#   - a -shared .so file with ld built from the .pica file
#   - a -shared .so file with ld built from the ld -r .pico file
#   - a -shared .so file with ld built from the ld -r .pica file
#
# and then for each program we construct:
#   - an ld -r .o file with ld
#   - a program built with the .o files and the default version of each library
#   - a program built with the ld -r .o file and ditto
#   - a program built with the .o files and the other versions of each library
#
# Note that a library must not have the same base name as any of its
# sources; otherwise some of the output names conflict.
#
# Note that libraries in SHAREDLIBRARIES should not also be in LIBRARIES.
#

############################################################
# assemble the sources

.for X in $(LIBRARIES) $(SHAREDLIBRARIES) $(PROGRAMS)
.for S in $(SOURCES.$(X))
OBJECTS.$(X)+=$(S).o
$(S).o: $(SOURCEDIR)/$(S).s $(TEST_AS)
	$(TEST_AS) -o $@ $(SOURCEDIR)/$(S).s
.endfor
.endfor
.for X in $(SHAREDLIBRARIES)
.for S in $(SOURCES.$(X))
PICOBJECTS.$(X)+=$(S).pico
$(S).pico: $(SOURCEDIR)/$(S).s $(TEST_AS)
	$(TEST_AS) $(TARGET_PIC_ASFLAGS) -o $@ $(SOURCEDIR)/$(S).s
.endfor
.endfor

############################################################
# non-shared libraries

.for L in $(LIBRARIES) $(SHAREDLIBRARIES)
run-tests: $(L).a.out
$(L).a $(L).a.out: $(OBJECTS.$(L)) $(TEST_AR)
	rm -f $(L).a
	$(TEST_AR) -cq $(L).a $(OBJECTS.$(L)) \
		> $(L).a.out 2>&1 || echo FAILED >> $(L).a.out

run-tests: $(L).ranlib-a.out
$(L).ranlib-a $(L).ranlib-a.out: $(L).a $(TEST_RANLIB)
	cp $(L).a $(L).ranlib-a
	$(TEST_RANLIB) -D $(L).ranlib-a \
		> $(L).ranlib-a.out 2>&1 || echo FAILED >> $(L).ranlib-a.out

run-tests: $(L).o.out
$(L).o $(L).o.out: $(OBJECTS.$(L)) $(TEST_LD)
	$(TEST_LD) -r -o $(L).o $(OBJECTS.$(L)) \
		> $(L).o.out 2>&1 || echo FAILED >> $(L).o.out

run-tests: $(L).o.a.out
$(L).o.a $(L).o.a.out: $(L).o $(TEST_AR)
	rm -f $(L).
	$(TEST_AR) -cq $(L).o.a $(L).o \
		> $(L).o.a.out 2>&1 || echo FAILED >> $(L).o.a.out

run-tests: $(L).o.ranlib-a.out
$(L).o.ranlib-a $(L).o.ranlib-a.out: $(L).o.a $(TEST_RANLIB)
	cp $(L).o.a $(L).
	$(TEST_RANLIB) -D $(L).o.ranlib-a \
	    > $(L).o.ranlib-a.out 2>&1 || echo FAILED >> $(L).o.ranlib-a.out

.for CASE in a ranlib-a o o.a o.ranlib-a
DUMPS+=$(L).$(CASE)
OUTFILES+=$(L).$(CASE).out
.endfor # CASE
.endfor # L

############################################################
# shared libraries

.for L in $(LIBRARIES)
run-tests: $(L).pica.out
$(L).pica $(L).pica.out: $(PICOBJECTS.$(L)) $(TEST_AR)
	rm -f $(L).
	$(TEST_AR) -cq $(L).pica $(PICOBJECTS.$(L)) \
		> $(L).pica.out 2>&1 || echo FAILED >> $(L).pica.out

run-tests: $(L).ranlib-pica.out
$(L).ranlib-pica $(L).ranlib-pica.out: $(L).pica $(TEST_RANLIB)
	cp $(L).pica $(L).
	$(TEST_RANLIB) -D $(L).ranlib-pica \
	    > $(L).ranlib-pica.out 2>&1 || echo FAILED >> $(L).ranlib-pica.out

run-tests: $(L).pico.out
$(L).pico $(L).pico.out: $(PICOBJECTS.$(L)) $(TEST_LD)
	$(TEST_LD) -r -o $(L).pico $(PICOBJECTS.$(L)) \
		> $(L).pico.out 2>&1 || echo FAILED >> $(L).pico.out

run-tests: $(L).pico.pica.out
$(L).pico.pica $(L).pico.pica.out: $(L).pico $(TEST_AR)
	rm -f $(L).
	$(TEST_AR) -cq $(L).pico.pica $(L).pico \
		> $(L).pico.pica.out 2>&1 || echo FAILED >> $(L).pico.pica.out

run-tests: $(L).pico.ranlib-pica.out
$(L).pico.ranlib-pica $(L).pico.ranlib-pica.out: $(L).pico.pica $(TEST_RANLIB)
	cp $(L).pico.pica $(L).
	$(TEST_RANLIB) -D $(L).pico.ranlib-pica \
		> $(L).pico.ranlib-pica.out 2>&1 || \
			echo FAILED >> $(L).pico.ranlib-pica.out

run-tests: $(L).so.out
$(L).so $(L).so.out: $(PICOBJECTS.$(L)) $(TEST_LD)
	$(TEST_LD) -shared -o $(L).so $(PICOBJECTS.$(L)) \
		> $(L).so.out 2>&1 || echo FAILED >> $(L).so.out

run-tests: $(L).pica.so.out
$(L).pica.so $(L).pica.so.out: $(L).pica $(TEST_LD)
	$(TEST_LD) -shared -o $(L).pica.so --whole-archive $(L).pica \
		> $(L).pica.so.out 2>&1 || echo FAILED >> $(L).pica.so.out

run-tests: $(L).pico.so.out
$(L).pico.so $(L).pico.so.out: $(L).pico $(TEST_LD)
	$(TEST_LD) -shared -o $(L).pico.so $(L).pico \
		> $(L).pico.so.out 2>&1 || echo FAILED >> $(L).pico.so.out

run-tests: $(L).pico.pica.so.out
$(L).pico.pica.so $(L).pico.pica.so.out: $(L).pico.pica $(TEST_LD)
	$(TEST_LD) -shared -o $(L).pico.pica.so --whole-archive $(L).pico.pica\
		> $(L).pico.pica.out 2>&1 || echo FAILED >> $(L).pico.pica.out

.for CASE in pica ranlib-pica pico pico.pica pico.ranlib-pica \
		so pica.so pico.so pico.pica.so
DUMPS+=$(L).$(CASE)
OUTFILES+=$(L).$(CASE).out
.endfor # CASE
.endfor # L

############################################################
# programs

#
# Each library has the following cases:
#   .a .o .o.a 
#   .so .pica.so .pico.so .pico.pica.so (if shared)
#
# We don't link all combinations of all libraries because that would
# generate an enormous combinatorial explosion. Instead we link the
# same types together. This gives quite enough cases!
#
# So we link the following cases of programs:
#   P-so
#   P-pica-so
#   P-pico-so
#   P-pico-pica-so
#   P-a
#   P-o
#   P-o-a
#
# and in addition we link .so and .a forms with the ld -r output from
# the program objects, to get P-so-ldr and P-a-ldr.
#
# If there are no SHLIBS.$(P) we don't issue the shared versions,
# and if there are no LIBS.$(P) we only issue P-a (and P-a-ldr).
#

.for P in $(PROGRAMS)
PCASES:=ldr.o
run-tests: $(P)-ldr.o.out
$(P)-ldr.o $(P)-ldr.o.out: $(TEST_LD) $(OBJECTS.$(P))
	$(TEST_LD) -o $(P)-ldr.o $(OBJECTS.$(P)) \
		> $(P)-ldr.o.out 2>&1 || echo FAILED >> $(P)-ldr.o.out

.if !empty(SHLIBS.$(P))
PCASES+=so
run-tests: $(P)-so.out
$(P)-so $(P)-so.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.so) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-so $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.so) $(LIBS.$(P):=.a) \
		> $(P)-so.out 2>&1 || echo FAILED >> $(P)-so.out

PCASES+=so-ldr
run-tests: $(P)-so-ldr.out
$(P)-so-ldr $(P)-so-ldr.out: $(TEST_LD) $(P)-ldr.o \
			$(SHLIBS.$(P):=.so) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-so-ldr $(P)-ldr.o \
		$(SHLIBS.$(P):=.so) $(LIBS.$(P):=.a) \
		> $(P)-so-ldr.out 2>&1 || echo FAILED >> $(P)-so-ldr.out

PCASES+=pica-so
run-tests: $(P)-pica-so.out
$(P)-pica-so $(P)-pica-so.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.pica-so) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-pica-so $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.pica-so) $(LIBS.$(P):=.a) \
		> $(P)-pica-so.out 2>&1 || echo FAILED >> $(P)-pica-so.out

PCASES+=pico-so
run-tests: $(P)-pico-so.out
$(P)-pico-so $(P)-pico-so.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.pico.so) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-pico-so $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.pico.so) $(LIBS.$(P):=.a) \
		> $(P)-pico-so.out 2>&1 || echo FAILED >> $(P)-pico-so.out

PCASES+=pico-pica-so
run-tests: $(P)-pico-pica-so.out
$(P)-pico-pica-so $(P)-pico-pica-so.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.pico.pica.so) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-pico-pica-so $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.pico.pica.so) $(LIBS.$(P):=.a) \
		> $(P)-pico-pica-so.out 2>&1 || \
			echo FAILED >> $(P)-pico-pica-so.out
.endif # SHLIBS.$(P)

PCASES+=a
run-tests: $(P)-a.out
$(P)-a $(P)-a.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.a) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-a $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.a) $(LIBS.$(P):=.a) \
		> $(P)-a.out 2>&1 || echo FAILED >> $(P)-a.out

PCASES+=a-ldr
run-tests: $(P)-a-ldr.out
$(P)-a-ldr $(P)-a-ldr.out: $(TEST_LD) $(P)-ldr.o \
			$(SHLIBS.$(P):=.a) $(LIBS.$(P):=.a)
	$(TEST_LD) -o $(P)-a-ldr $(P)-ldr.o \
		$(SHLIBS.$(P):=.a) $(LIBS.$(P):=.a) \
		> $(P)-a-ldr.out 2>&1 || echo FAILED >> $(P)-a-ldr.out

.if !empty(SHLIBS.$(P)) || !empty(LIBS.$(P))
PCASES+=o
run-tests: $(P)-o.out
$(P)-o $(P)-o.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.o) $(LIBS.$(P):=.o)
	$(TEST_LD) -o $(P)-o $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.o) $(LIBS.$(P):=.o) \
		> $(P)-o.out 2>&1 || echo FAILED >> $(P)-o.out

PCASES+=o-a
run-tests: $(P)-o-a.out
$(P)-o-a $(P)-o-a.out: $(TEST_LD) $(OBJECTS.$(P)) \
			$(SHLIBS.$(P):=.o.a) $(LIBS.$(P):=.o.a)
	$(TEST_LD) -o $(P)-o-a $(OBJECTS.$(P)) \
		$(SHLIBS.$(P):=.o.a) $(LIBS.$(P):=.o.a) \
		> $(P)-o-a.out 2>&1 || echo FAILED >> $(P)-o-a.out
.endif # LIBS.$(P)

.for CASE in $(PCASES)
DUMPS+=$(P)-$(CASE)
OUTFILES+=$(P)-$(CASE).out
CLEANFILES+=$(P)-$(CASE)
.endfor # CASE
.endfor # L

############################################################
# hexdumps

.for H in $(DUMPS)
run-tests: $(H).hex
$(H).hex: $(H)
	hexdump -C $(H) > $@
.endfor

############################################################
# disassemblies

.for H in $(DUMPS)
run-tests: $(H).objdump
$(H).objdump: $(H)
	$(TEST_OBJDUMP) -d $(H) > $@
.endfor

############################################################
# diffs

.for D in $(OUTFILES) $(DUMPS:=.hex) $(DUMPS:=.objdump)
run-tests: $(D).diff
$(D).diff: $(GOODDIR)/$(D).good $(D)
	diff $(GOODDIR)/$(D).good $(D) > $@ || true
.endfor

############################################################
# show-diffs

show-diffs:
.for D in $(OUTFILES) $(DUMPS:=.hex) $(DUMPS:=.objdump)
	@cat $(D).diff
.endfor

############################################################
# good

good:
.for D in $(OUTFILES) $(DUMPS:=.hex) $(DUMPS:=.objdump)
	cp $(D) $(GOODDIR)/$(D).good
.endfor

#touchgood:
#.for D in $(OUTFILES) $(DUMPS:=.hex) $(DUMPS:=.objdump)
#	touch $(GOODDIR)/$(D).good
#.endfor

############################################################
# clean

clean:
	rm -f *.o *.a *.pico *.pica *.hex *.objdump *.out *.diff
	rm -f $(CLEANFILES)

############################################################

.PHONY: all run-tests show-diffs good clean
