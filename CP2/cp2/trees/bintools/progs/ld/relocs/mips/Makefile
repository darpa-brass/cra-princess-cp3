TOP=../../../..
include $(TOP)/mk/base.mk

SRCS=treloc.c
LIB=librelocs.a
MYCFLAGS=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)

# XXX
MYCFLAGS+=-I../../main

# XXX XXX
MYCFLAGS+=-I$(TOP)/binfmts/$(BINFMT)/include/arch/$(CPU)

include $(TOP)/mk/lib.mk
