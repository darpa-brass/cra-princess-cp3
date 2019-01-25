#!/bin/sh
# dogenerate.sh - generate csmith outputs
# usage: dogenerate.sh SEED NUM (in the docker container)
# where NUM is the number of examples to generate.
#
# Note: the output examples are numbered 0..NUM-1, regardless of which
# actual examples are chosen and rejected.  Changing the filtering
# will change the numbering. This script is supposed to be
# deterministic (two runs with everything the same should produce the
# same test corpus) but it is not meant to be mostly-invariant under
# minor changes.
#
# Also note that I'm not sure how csmith's internal randomization
# works, and whether it has its own random generator or it uses the C
# library; if the latter, building on a different OS or different libc
# version might produce different results. This is one of the reasons
# I'm putting it in a docker container.
#

#
# config
#
# - Based on https://github.com/csmith-project/csmith/issues/46, use 
#   --take-no-union-field-addr; otherwise csmith may generate code that
#   violates the C99 aliasing rules.
#
# - Based on https://github.com/csmith-project/csmith/issues/46, use
#   --no-packed-struct; otherwise csmith may generate unaligned accesses,
#   which crash on most non-x86 platforms. (Also, packed structures aren't
#   standard C.)
#
# - Use --no-float because of concerns that hashing the representation
#   of floats won't necessarily produce portable results; plus,
#   despite IEEE754 rounding behavior and thus error is not
#   necessarily portable; plus, there's some concern about FP bugs in
#   qemu.
#
CSMITH_ARGS='
	--take-no-union-field-addr
	--no-packed-struct
	--no-float
'

############################################################
# setup

SEED="$1"
NUM="$2"
if [ "x$NUM" = x ]; then
    echo "Usage: $0 seed number-of-tests" 1>&2
    exit 1
fi

if ! echo "$SEED" | grep -q '^[0-9][0-9]*$'; then
    echo "$0: $SEED: Not a number" 1>&2
    exit 1
fi
if ! echo "$NUM" | grep -q '^[0-9][0-9]*$'; then
    echo "$0: $NUM: Not a number" 1>&2
    exit 1
fi
CUR=0
CURFAILURE=0

CSMITH=/csmith/installed/bin/csmith
CSMITH_HOME=/csmith/src
export CSMITH_HOME  # csmith itself needs this

# set these so the filter scripts can use them
CC=gcc
CFLAGS=-I/csmith/src/runtime
export CC CFLAGS

echo "$SEED" > /corpus/masterseed.txt || exit 1

############################################################
# installation of examples

failinstall() {
    CURFAILURESTR=$(printf "f%05d" $CURFAILURE)
    cp can.c /corpus/failed/$CURFAILURESTR.c
    echo "$SEED" > /corpus/failed/$CURFAILURESTR.seed
    for FILT in /csmith/filters/*.filter; do
	FB=$(basename "$FILT")
	if [ -f log.$FB ]; then
	    cp log.$FB /corpus/failed/$CURFAILURESTR.log.$FB
	fi
    done
    echo "Seed $SEED saved as failed/$CURFAILURESTR.c"
}

keepinstall() {
    CURSTR=$(printf "t%05d" $CUR)
    cp can.c /corpus/$CURSTR.c
    echo "$SEED" > /corpus/$CURSTR.seed
    for FILT in /csmith/filters/*.filter; do
	FB=$(basename "$FILT")
	cp log.$FB /corpus/$CURSTR.log.$FB
    done
    echo "Seed $SEED installed as $CURSTR.c"
}

############################################################
# main loop

# continue making examples until we have enough
while [ $CUR -lt $NUM ]; do

    # do this first rather than at the end of the loop body so the
    # initial user-supplied seed number doesn't actually get used
    # directly.
    SEED=$(printf "%d" 0x$(echo "$SEED" | md5sum - | cut -c1-8))

    # make a new work directory
    cd /csmith || exit 1
    if [ -d work ]; then
	rm -r work || exit 1
    fi
    mkdir work || exit 1
    cd work || exit 1

    # Generate a new candidate
    echo
    echo "Trying csmith seed $SEED"
    $CSMITH $CSMITH_ARGS --seed $SEED > can.c

    #
    # The most basic filter: does it compile? Reject candidates that
    # don't, or that crash the compiler.
    #
    # Produce -O0, -O1, -O2, and -O3 builds that the filters can use.
    #
    # Turn off warnings because csmith output isn't expected to be
    # warning-free.
    #
    if ! $CC $CFLAGS -w -O0 can.c -o can-O0; then
	echo "Build failed at -O0"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -O1 can.c -o can-O1; then
	echo "Build failed at -O1"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -O2 can.c -o can-O2; then
	echo "Build failed at -O2"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -O3 can.c -o can-O3; then
	echo "Build failed at -O3"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -m32 -O0 can.c -o can-O0-32; then
	echo "Build failed at -m32 -O0"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -m32 -O1 can.c -o can-O1-32; then
	echo "Build failed at -m32 -O1"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -m32 -O2 can.c -o can-O2-32; then
	echo "Build failed at -m32 -O2"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    if ! $CC $CFLAGS -w -m32 -O3 can.c -o can-O3-32; then
	echo "Build failed at -m32 -O3"
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi
    echo "Seed $SEED compiled successfully."

    #
    # Run all the filters.
    #
    BAD=0
    for FILT in /csmith/filters/*.filter; do
	FB=$(basename "$FILT")
	if $FILT can > log.$FB 2>&1; then
	    echo "Seed $SEED passed filter $FB"
	else
	    echo "Seed $SEED failed filter $FB; log output follows:"
	    cat log.$FB
	    BAD=1
	    break
	fi
    done
    if [ $BAD = 1 ]; then
	failinstall
	CURFAILURE=$(( $CURFAILURE + 1 ))
	continue
    fi

    # passed; install it
    keepinstall

    CUR=$(( $CUR + 1 ))
done

echo
echo 'Complete.'
