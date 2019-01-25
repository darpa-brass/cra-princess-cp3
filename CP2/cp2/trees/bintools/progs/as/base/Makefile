TOP=../../..
include $(TOP)/mk/base.mk

SRCS=utils.c \
	expr.c expropt.c \
	label.c section.c
LIB=libbase.a

# XXX currently expr.h uses targettoken.h
MYCFLAGS+=-I../frontend/arch/$(CPU)

# XXX currently expropt.c uses reloc.h (and targetreloc.h)
MYCFLAGS+=-I../backend
MYCFLAGS+=-I../backend/arch/$(CPU)

MYCFLAGS+=-I../include
MYCFLAGS+=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)

include $(TOP)/mk/lib.mk
