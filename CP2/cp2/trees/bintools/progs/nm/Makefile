TOP=../..
include $(TOP)/mk/base.mk

SRCS=nm.c
PROG=nm

MYCFLAGS=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)
MYLIBS=$(TOP)/binfmts/$(BINFMT)/main/lib$(BINFMT).a
MYLIBS+=$(TOP)/support/libsupport.a

include $(TOP)/mk/prog.mk
