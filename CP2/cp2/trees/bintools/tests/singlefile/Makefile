TOP=../..
include $(TOP)/mk/base.mk

SRCDIR=../sources/$(CPU)
GOODDIR=../sources/$(CPU)

TEST_AS=../../progs/as/main/new-as
TEST_NM=../../progs/nm/new-nm
TEST_OBJDUMP=../../progs/objdump/main/new-objdump
TEST_SIZE=../../progs/size/new-size
TEST_STRIP=../../progs/strip/new-strip

TESTS=\
	std-halt \
	std-allinsns std-allregs \
	std-align

.include "../sources/$(CPU)/TESTS.mk"

TESTS+=$(EXTRATESTS)
.for P in $(PROGRAMS)
TESTS+=$(SOURCES.$(P))
.endfor

all: run-tests .WAIT show-diffs

#
# For each test file we:
#   - run the assembler to make a .o file
#   - hexdump the .o file
#   - run size
#   - run nm
#   - run objdump
#   - run strip and hexdump the output of that
#
# The generated names are:
#   test.tool.out	- the terminal output of each tool
#   test.tool.hex	- hexdump of the tool's binary file output, if any
#
# Each of these also has a .good file (these are MD) and generates a
# .diff file against the .good file.
#
# We don't actually do strip yet as the strip we have doesn't do
# anything yet itself.
#

CASES=as.out as.hex size.out nm.out objdump-d.out # strip.out strip.hex


.for T in $(TESTS)
.for CASE in $(CASES)

run-tests: $(T).$(CASE).diff
$(T).$(CASE).diff: $(GOODDIR)/$(T).$(CASE).good $(T).$(CASE)
	diff -u $(GOODDIR)/$(T).$(CASE).good $(T).$(CASE) > $@ || true
.endfor

# hex
$(T).as.hex: $(T).o
	hexdump -C $(T).o > $(T).as.hex

$(T).strip.hex: $(T).strip-o
	hexdump -C $(T).strip-o > $(T).strip.hex

# as
# delete the output file beforehand, and then touch it afterwards;
# if the assembler fails it doesn't produce one.
# if we leave none make gets upset, and if we allow an old one to
# hang around anyone trying to read the diffs gets confused.
$(T).o $(T).as.out: $(SRCDIR)/$(T).s $(TEST_AS)
	rm -f $(T).o
	$(TEST_AS) -Lvv -o $(T).o $(SRCDIR)/$(T).s \
		> $(T).as.out 2>&1 || echo FAILED >> $(T).as.out
	touch $(T).o

# nm
$(T).nm.out: $(T).o $(TEST_NM)
	$(TEST_NM) $(T).o \
		> $@ 2>&1 || echo FAILED >> $@

# objdump
$(T).objdump-d.out: $(T).o $(TEST_OBJDUMP)
	$(TEST_OBJDUMP) -d $(T).o \
		> $@ 2>&1 || echo FAILED >> $@

# size
$(T).size.out: $(T).o $(TEST_SIZE)
	$(TEST_SIZE) $(T).o \
		> $@ 2>&1 || echo FAILED >> $@

# strip
$(T).strip.out: $(T).o $(TEST_STRIP)
	$(TEST_STRIP) -o $(T).strip-o $(T).o \
		> $@ 2>&1 || echo FAILED >> $@

.endfor

show-diffs:
.for T in $(TESTS)
.for CASE in $(CASES)
	@cat $(T).$(CASE).diff
.endfor
.endfor

good:
.for T in $(TESTS)
.for CASE in $(CASES)
	cp $(T).$(CASE) $(GOODDIR)/$(T).$(CASE).good
.endfor
.endfor



clean:
	rm -f *.o *.hex *.out *.diff

.PHONY: all run-tests show-diffs good clean
