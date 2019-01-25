#!/bin/sh
# test-run.sh - run a test program using qemu
# usage: test-run.sh arch prog
#
# always uses the emulator; don't run it for Baseline A.
#
# this script *must not* produce output other than either the
# test program's own output, or errors.

ARCH="$1"
PROG="$2"

case "$ARCH" in
    arm)
	GNUTARGET=arm-linux-gnueabi
	;;
    *)
	;;
esac

if [ "x$GNUTARGET" = x ]; then
    GNUTARGET="${ARCH}-linux-gnu"
fi
if [ "x$QEMU" = x ]; then
    QEMU="qemu-${ARCH}"
fi

export LD_LIBRARY_PATH=/usr/${GNUTARGET}/lib
$QEMU $PROG


