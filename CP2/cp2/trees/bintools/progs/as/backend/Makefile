TOP=../../..
include $(TOP)/mk/base.mk

SRCS=reloc.c arch/$(CPU)/targetreloc.c \
	as.c compile.c \
	arch/$(CPU)/targetmodes.c modeops.c \
	labelops.c sectionops.c relocops.c debugops.c miscops.c \
	arch/$(CPU)/targetinsns.c dataops.c \
	arch/$(CPU)/targetmatch.c match.c
LIB=libbackend.a

# XXX because expr.h uses targettoken.h
MYCFLAGS+=-I../frontend/arch/$(CPU)

MYCFLAGS+=-I. -Iarch/$(CPU) -I../include
MYCFLAGS+=-I$(TOP)/binfmts/$(BINFMT)/include/arch/$(CPU)
MYCFLAGS+=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)

include $(TOP)/mk/lib.mk
