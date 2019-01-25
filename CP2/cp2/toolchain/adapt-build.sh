#!/bin/sh
# dobuild.sh - generate machine-dependent code and compile the toolchain
# usage: dobuild.sh arch
# where arch is one of: XXX

ARCH="$1"

if [ "x$ARCH" = xnocross ]; then
    # special-purpose archiecture selection where we are supposed to adapt
    # but not be able to compile.
    ARCH=trivial
fi

cd /cp2/trees/bintools || exit 1

if [ x"$ARCH" = x ]; then
    echo "$0: usage: $0 arch" 1>&2
    exit 1
fi

if [ ! -d targets/"$ARCH" ]; then
    echo "$0: Unknown/unsupported architecture $ARCH" 1>&2
    exit 1
fi

cd gentarget/targets/"$ARCH" || exit 1
echo "*** Generating code for $ARCH ***"
bmake || exit 1
echo "*** Installing code for $ARCH ***"
bmake newtarget || exit 1
bmake install || exit 1

echo "*** Preparing to build bintools ***"

#
# XXX: currently building outside the source tree is borked. Build *in*
# the source tree. The proper logic is commented out. When fixing this,
# don't forget to also update install.sh.
#

cd /cp2/trees/bintools || exit 1

if [ -f defs.mk ]; then
    bmake distclean || exit 1
fi

#cd /cp2/toolchain
#[ -d build ] || mkdir build || exit 1
#cd build || exit 1
#
## In case we're running a second time
## XXX: if we're running the same arch a second time, we probably should
## just exit 0 instead of recompiling for no particular reason.
#if [ -d "$ARCH" ]; then
#    rm -rf "$ARCH"
#fi
#
#mkdir "$ARCH" || exit 1
#cd "$ARCH" || exit 1

TARGET=${ARCH}-elf-linux

sh ./configure --prefix=/cp2/toolchain/installed/"$ARCH" --target=$TARGET || exit 1
#/cp2/trees/bintools/configure --prefix=/cp2/toolchain/installed/"$ARCH" --target=$TARGET || exit 1

echo "*** Building ***"
bmake || exit 1

cd progs/ld || exit 1
../as/main/new-as -o crtix.o crtix.s || exit 1

# install happens in adapt-install.sh

exit 0
