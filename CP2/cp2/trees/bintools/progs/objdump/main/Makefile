TOP=../../..
include $(TOP)/mk/base.mk

SRCS=main.c dump.c dumptbl.c
PROG=objdump

MYLIBS=../decode/$(CPU)/libdecode.a

MYCFLAGS=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)
MYLIBS+=$(TOP)/binfmts/$(BINFMT)/main/lib$(BINFMT).a
MYLIBS+=$(TOP)/support/libsupport.a

# XXX
MYCFLAGS+=-I$(TOP)/progs/as

include $(TOP)/mk/prog.mk
