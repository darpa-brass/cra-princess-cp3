#!/bin/sh
# doverify.sh - verify code snippet
# usage: doverify.sh arch perturbation
#
# Expects to find:
# ... the lowered cassiopeia as "test.spec"
# ... and the file to verify as "verify.prog"
#

ARCH="$1"
PERTURBATION="$2"

CASSIOPEIA=/cp2/trees/cassiopeia/cassiopeia

# to get racket
PATH=$PATH:/cp2/software/installed/bin
export PATH

case "$ARCH" in
    armv7-a)
	CASPARCH=arm-swi-small/arm-tiny-"$PERTURBATION"/arm-swi-tiny"$PERTURBATION"
	;;
    powerpc)
	CASPARCH=syscall-powerpc/powerpc-tiny-"$PERTURBATION"/syscall-powerpc-tiny"$PERTURBATION"
	;;
    riscv-32e)
	CASPARCH=syscall-riscv/riscv-tiny-"$PERTURBATION"/syscall-riscv-tiny"$PERTURBATION"
	;;
    x86_64)
	CASPARCH=x86-64-syscall/x86_tiny_"$PERTURBATION"/x86-64-syscall-tiny"$PERTURBATION"
	;;
    *)
	CASPARCH="$ARCH"
	;;
esac

cd /cp2/synth || exit 1

echo "$CASSIOPEIA /cp2/trees/cassiopeia/$CASPARCH.casp -verify test.spec verify.prog -o verify.rkt"
$CASSIOPEIA /cp2/trees/cassiopeia/$CASPARCH.casp \
	    -verify test.spec verify.prog -o verify.rkt || exit 1

echo "raco make verify.rkt"
raco make verify.rkt || exit 1

echo "racket verify.rkt"
racket verify.rkt > verify.result || exit 1

exit 0
