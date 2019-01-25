#!/bin/sh
# doinstall.sh - install the toolchain
# usage: doinstall.sh arch
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


echo "*** Installing ***"
# XXX see dobuild.sh
cd /cp2/trees/bintools || exit 1
#cd /cp2/toolchain/build/"$ARCH" || exit 1
bmake install || exit 1

mkdir -p /cp2/toolchain/installed/"$ARCH"/lib
cp progs/ld/crtix.o /cp2/toolchain/installed/"$ARCH"/lib || exit 1

exit 0
