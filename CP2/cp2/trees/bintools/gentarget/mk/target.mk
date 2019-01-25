#
# Makefile for building target sources.
#
# Client should set TARGET to the target name.
#

TOOLDIR=$(GENTOP)/tools
TARGETDIR=$(REALTOP)/targets/$(TARGET)

ELFDIR=$(REALTOP)/binfmts/elf
ASDIR=$(REALTOP)/progs/as
LDDIR=$(REALTOP)/progs/ld
OBJDUMPDIR=$(REALTOP)/progs/objdump

DIFF=diff -u

# XXX this might need to be taught to specifically use ocamlrun
# for platforms where there isn't a native ocaml compiler.

all:;

############################################################
# Tables of info

# The generated files, their generators, and their destinations
GENFILES=\
	targetelfdefs.h		basic	$(ELFDIR)/include/arch/$(TARGET)  \
	targetdefs.h		basic	$(REALTOP)/include/arch/$(TARGET) \
	langdefs.h		langdefs $(ASDIR)/frontend/arch/$(TARGET)   \
	targettoken.h		lang	$(ASDIR)/frontend/arch/$(TARGET)   \
	targettoken.c		lang	$(ASDIR)/frontend/arch/$(TARGET)   \
	targetoper.c		lang	$(ASDIR)/frontend/arch/$(TARGET)   \
	targetoper.h		lang	$(ASDIR)/frontend/arch/$(TARGET)   \
	targetmatch.h		match	$(ASDIR)/backend/arch/$(TARGET)    \
	targetmatch.c		match	$(ASDIR)/backend/arch/$(TARGET)    \
	targetinsns.c		encoding $(ASDIR)/backend/arch/$(TARGET)   \
	elfreloc.h		relocs	$(ELFDIR)/include/arch/$(TARGET)/  \
	targetreloc.h		relocs	$(ASDIR)/backend/arch/$(TARGET)/   \
	targetreloc.c		relocs	$(ASDIR)/backend/arch/$(TARGET)/   \
	treloc.c		relocs	$(LDDIR)/relocs/$(TARGET)/         \
	targetmodes.h		modes	$(ASDIR)/backend/arch/$(TARGET)/   \
	targetmodes.c		modes	$(ASDIR)/backend/arch/$(TARGET)/   \
	targetopcode.h		decoding $(OBJDUMPDIR)/decode/$(TARGET)/   \
	decode.c		decoding $(OBJDUMPDIR)/decode/$(TARGET)/

# The generator programs
GENERATOR.basic=$(TOOLDIR)/genmisc/genmisc
GENERATOR.langdefs=$(TOOLDIR)/genlangdefs/genlangdefs
GENERATOR.lang=$(TOOLDIR)/genlanguage/genlanguage
GENERATOR.match=$(TOOLDIR)/opmatch/opmatch
GENERATOR.encoding=$(TOOLDIR)/genencoding/genencoding
GENERATOR.relocs=$(TOOLDIR)/genrelocs/genrelocs
GENERATOR.modes=$(TOOLDIR)/genmodes/genmodes
GENERATOR.decoding=$(TOOLDIR)/genstub/genstub.sh

# The spec files each generator uses
SPECFILES.basic=misc.def
SPECFILES.langdefs=language.def
SPECFILES.lang=base.def misc.def language.def
SPECFILES.match=base.def opmatch.def
SPECFILES.encoding=base.def encoding.def opmatch.def misc.def
SPECFILES.relocs=base.def misc.def encoding.def modifiers.def relocs.def
SPECFILES.modes=modes.def
SPECFILES.decoding=

############################################################
# Main rules

.for F G DEST in $(GENFILES)
all: $(F)
$(F): $(GENERATOR.$(G))
$(F): $(SPECFILES.$(G):S/^/$(TARGETDIR)\//)
.endfor

depend:;

install:
.for F G DEST in $(GENFILES)
	@if ! diff $(F) $(DEST)/$(F) >/dev/null 2>&1; then \
		echo "cp $(F) $(DEST)/$(F)"; \
		cp $(F) $(DEST)/$(F) || exit 1; \
	 fi
.endfor

diff:
.for F G DEST in $(GENFILES)
	@$(DIFF) $(DEST)/$(F) $(F) || true
.endfor

clean distclean:
.for F G DEST in $(GENFILES)
	rm -f $(F)
.endfor
	rm -f *.c *.h .tmp*

############################################################
# Specific output rules

#
# Basic defs
#

targetdefs.h targetelfdefs.h:
	$(GENERATOR.basic) ../../../targets/$(TARGET)/misc.def

#
# Language definition
#

GENERATOR.stublang=$(TOOLDIR)/genstub/genstub.sh

langdefs.h:
	$(GENERATOR.langdefs) ../../../targets/$(TARGET)/language.def

targettoken.h targettoken.c targetoper.h targetoper.c:
	$(GENERATOR.lang) $(TARGETDIR)

#
# operand/instruction signature matching
#

allmatch.def: $(TARGETDIR)/opmatch.def $(TOOLDIR)/opmatch/dirmatch.def 
	cat $(TARGETDIR)/opmatch.def $(TOOLDIR)/opmatch/dirmatch.def > $@

targetmatch.h targetmatch.c: allmatch.def
	$(GENERATOR.match) allmatch.def $(TARGETDIR)/base.def \
		.tmph .tmpc
	mv -f .tmph targetmatch.h
	mv -f .tmpc targetmatch.c

clean distclean: clean-allmatch
clean-allmatch:
	rm -f allmatch.def

#
# instruction encoding procedures
#

targetinsns.c:
	$(GENERATOR.encoding) $(TARGETDIR)

#
# relocation handling
#

elfreloc.h targetreloc.h targetreloc.c treloc.c:
	$(GENERATOR.relocs) $(TARGETDIR)

#
# modes
#

targetmodes.h targetmodes.c:
	$(GENERATOR.modes) ../../../targets/$(TARGET)

#
# decoding
#

# ugh, this shouldn't need to know that it's a sh script (XXX)
targetopcode.h:
	sh $(GENERATOR.decoding) ../../../targets/$(TARGET) $(OBJDUMPDIR)/decode . targetopcode.h

decode.c:
	sh $(GENERATOR.decoding) ../../../targets/$(TARGET) $(OBJDUMPDIR)/decode . decode.c


############################################################
# create dirs for a new target

# The makefiles in the target dirs are the same for every target
# (perhaps I should reorg things so they don't need to exist)
# (update: the ones in as don't)
# so copy the mips ones to get started.

# maybe also $(REALTOP)/tests/sources
TARGETDIRS=\
	$(ELFDIR)/include/arch \
	$(ASDIR)/frontend/arch \
	$(ASDIR)/backend/arch \
	$(LDDIR)/relocs \
	$(OBJDUMPDIR)/decode \
	$(REALTOP)/include/arch

newtarget:
.for D in $(TARGETDIRS) 
	[ -d $(D)/$(TARGET) ] || mkdir $(D)/$(TARGET)
	@if [ -f $(D)/mips/Makefile ]; then \
	    echo "cp $(D)/mips/Makefile $(D)/$(TARGET)/Makefile"; \
	    cp $(D)/mips/Makefile $(D)/$(TARGET)/Makefile; \
	 fi
.endfor

############################################################


