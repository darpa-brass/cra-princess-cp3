TOP=../../..
include $(TOP)/mk/base.mk

SRCS=token.c arch/$(CPU)/targettoken.c \
	arch/$(CPU)/targetoper.c \
	eparse.c fparse.c

LIB=libfrontend.a

MYCFLAGS+=-I. -Iarch/$(CPU) -I../include
MYCFLAGS+=-I$(TOP)/binfmts/$(BINFMT)/include/arch/$(CPU)
MYCFLAGS+=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)

include $(TOP)/mk/lib.mk
