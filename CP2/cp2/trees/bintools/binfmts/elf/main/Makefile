TOP=../../..
include $(TOP)/mk/base.mk

SRCS=elfbits.c elfstrtab.c \
	bf_misc.c bf_hdrsize.c bf_loadsect.c bf_loadsyms.c bf_loadrels.c \
	bf_output.c
LIB=libelf.a
MYCFLAGS=-I$(TOP)/include -I$(TOP)/include/arch/$(CPU)
MYCFLAGS+=-I../include/arch/$(CPU)

include $(TOP)/mk/lib.mk
