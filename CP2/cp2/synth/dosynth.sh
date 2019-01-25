#!/bin/sh
# dosynth.sh - run synthesis
# usage: dosynth.sh arch perturbation
#
# Expects to find:
# ... the lowered cassiopeia as "test.spec"
#
# We expect the precondition to be the first line and the postcondition
# to be the last line, and the stuff in between to be the original
# handwritten code, which we ignore.
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

#
# The workflow is: we already fed the input pre- and post-conditions
# (which are MI) to alewife, which produces cassiopeia material that
# we then run cassiopeia on; that produces rosette stuff that we feed
# to rosette.
#

echo "$CASSIOPEIA /cp2/trees/cassiopeia/$CASPARCH.casp -synth test.spec -o test.rkt"
$CASSIOPEIA /cp2/trees/cassiopeia/$CASPARCH.casp -synth test.spec -o test.rkt || exit 1

echo "raco make test.rkt"
raco make test.rkt || exit 1

echo "racket test.rkt"
racket test.rkt > test.preoutput || exit 1

echo "Raw output:"
cat test.preoutput

echo 'sed < test.preoutput -n '"'"'/^Succeeded:$/,$p'"'"' | sed '1d' > test.output'
sed < test.preoutput -n '/^Succeeded:$/,$p' | sed '1d' > test.output

$CASSIOPEIA /cp2/trees/cassiopeia/$CASPARCH.casp -extract test.output -o test.s || exit 1

echo "Assembler-syntax output:"
cat test.s

exit 0
