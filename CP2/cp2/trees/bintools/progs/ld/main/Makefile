TOP=../../..
include $(TOP)/mk/base.mk

SRCS=main.c \
     loadfile.c section.c symtab.c outputsym.c outputrel.c savefile.c \
     utils.c
PROG=ld

MYLIBS=../relocs/$(CPU)/librelocs.a

MYCFLAGS=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)
MYLIBS+=$(TOP)/binfmts/$(BINFMT)/main/lib$(BINFMT).a
MYLIBS+=$(TOP)/support/libsupport.a

# XXX
MYCFLAGS+=-I../relocs/$(CPU)

include $(TOP)/mk/prog.mk
