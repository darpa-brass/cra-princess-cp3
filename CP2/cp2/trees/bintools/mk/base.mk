# Defaults for things that defs.mk sets

# The cpu/binfmt/os must be set explicitly
# (the default should be "native" but we can't probe that from here)
TARGET=$(CPU)-$(BINFMT)-$(OS)
CPU=nocpu
BINFMT=nobinfmt
OS=noos

# Default install path is /usr/local
# Default install target is ""
DESTDIR=
PREFIX=/usr/local
INSTALLTARGET=

# Install program
INSTALL=install

# Default compiler
CC=cc
CFLAGS=$(OPT)
OPT=-O
AR=ar
RANLIB=ranlib
LDFLAGS=
LIBS=

# Compiler for building things used in the build
TOOLCC=cc
TOOLCFLAGS=$(TOOLOPT)
TOOLOPT=-O
TOOLLDFLAGS=
TOOLLIBS=

-include $(TOP)/defs.mk

# If we are BSD make, set WAIT to .WAIT; otherwise to empty.
# This makes parallel builds work correctly. Note that gmake lacks
# this feature and can't do safe parallel builds.
#
# In BSD make, because CC is defined above, $(CC:D.WAIT) will evalute
# to .WAIT. In gmake (and legacy make) the modifier form isn't
# understood and the results are empty.
#
# XXX we should probably have the configure script probe the make type.
WAIT=$(CC:D.WAIT)

