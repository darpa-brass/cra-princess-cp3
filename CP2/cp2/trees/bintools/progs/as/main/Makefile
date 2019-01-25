TOP=../../..
include $(TOP)/mk/base.mk

SRCS=load.c main.c
PROG=as

MYCFLAGS=-I../include

MYLIBS+=../frontend/libfrontend.a
MYLIBS+=../backend/libbackend.a

# XXX: main.c uses reloc.h
MYCFLAGS+=-I../backend
# XXX for targetreloc.h, used by reloc.h
MYCFLAGS+=-I../backend/arch/$(CPU)
# XXX because expr.h uses targettoken.h
MYCFLAGS+=-I../frontend/arch/$(CPU)

MYLIBS+=../base/libbase.a

MYCFLAGS+=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)
MYLIBS+=$(TOP)/binfmts/$(BINFMT)/main/lib$(BINFMT).a
MYLIBS+=$(TOP)/support/libsupport.a

include $(TOP)/mk/prog.mk
