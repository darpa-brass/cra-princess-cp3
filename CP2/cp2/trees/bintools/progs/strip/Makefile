TOP=../..
include $(TOP)/mk/base.mk

SRCS=strip.c
PROG=strip

MYCFLAGS=-I$(TOP)/include
MYLIBS=$(TOP)/binfmts/$(BINFMT)/main/lib$(BINFMT).a
MYLIBS+=$(TOP)/support/libsupport.a

include $(TOP)/mk/prog.mk
