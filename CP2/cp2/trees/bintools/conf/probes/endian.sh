#!/bin/sh
# endian.sh - check host endianness
# usage: ENDIAN=$(sh endian.sh "$CC" "$CFLAGS")
#

#
# Copyright (c) 2002, 2016
#	The President and Fellows of Harvard College.
#
# Written by David A. Holland.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

# XXX this is all rubbish. all very well to test using od, but what we
# want to know about is the endianness of the compiler's execution
# environment.

CC="$1"
CFLAGS="$2"

if [ x"$CC" = x ]; then
    echo "Usage: $0 CC CFLAGS" 1>&2
    exit 1
fi

# avoid compile errors from passing ""
if [ "x$CFLAGS" = x ]; then
    CFLAGS="-Dirrelevant"
fi

(
    echo "   ============   "
    echo "Checking for host endianness"
    echo "Running: echo ab | od -h | awk '{ print \$2 }'"
) >> config.log

# If od exists and is compliant and letters are ascii, this should
# work much more reliably than mucking about with endianness headers,
# as the latter aren't very standardized.

case "$( (echo ab | od -h | awk '{ print $2 }') 2>&1 )" in
    6261) echo LITTLE; echo "Result: little" >> config.log; exit 0;;
    6162) echo BIG; echo "Result: big" >> config.log; exit 0;;
    *) ;;
esac
echo "Did not work" >> config.log

# Unfortunately it didn't work. Let's first try the builtin symbols
# from recent gcc.

for END in BIG LITTLE; do
    cat > __conftest.c <<EOF
#ifdef __BYTE_ORDER__
#ifdef __ORDER_${END}_ENDIAN__
#if __BYTE_ORDER__ == __ORDER_${END}_ENDIAN__
int foo(
#endif
#endif
#endif
);
EOF
    (
	echo "Test program:"
	cat __conftest.c
	echo "Running: $CC $CFLAGS -c __conftest.c"
    ) >> config.log
    if "$CC" "$CFLAGS" -c __conftest.c >> config.log 2>&1; then
	echo "Succeeded; result is $END" >> config.log
	echo "$END"
	rm -f __conftest*
	exit 0
    fi
done

# Now try sys/endian.h (BSD) and machine/endian.h (old BSD) and just
# endian.h (some Linux).

for HEADER in '<sys/endian.h>' '<machine/endian.h>' '<endian.h>'; do
    for END in BIG LITTLE; do
	for US in "" "_"; do
	    cat >__conftest.c <<EOF
#include <sys/types.h>
#include <sys/endian.h>

#if ${US}BYTE_ORDER==${US}${END}_ENDIAN
int foo(void) { return 0; }
#else
-- blooey --
#endif
EOF
	    (
		echo "Test program:"
		cat __conftest.c
		echo "Running: $CC $CFLAGS -c __conftest.c"
	    ) >> config.log
	    if "$CC" "$CFLAGS" -c __conftest.c >> config.log 2>&1; then
		echo "Succeeded; result is $END" >> config.log
		echo "$END"
		rm -f __conftest*
		exit 0
	    fi
	done
    done
done

#
# Ok, next step is to try to dissect compiler output.
#

cat >__conftest.c <<EOF
int testvar = 0xdeadbeef;
EOF
(
    echo "Test program:"
    cat __conftest.c
    echo "Running: $CC $CFLAGS -c __conftest.c"
) >> config.log

if "$CC" "$CFLAGS" -c __conftest.c >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Test program failed to compile"
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

# If we have a GNU toolchain this should do the trick.
for OBJDUMP in objdump "${CC%-*}-objdump"; do
    DATA=$( (objdump -j .data -s __conftest.o || echo FAILED) 2>&1)
    case "$DATA" in
	*deadbeef*)
	    echo "BIG"
	    echo "Result: big" >> config.log
	    rm -f __conftest*
	    exit 0
	    ;;
	*efbeadde*)
	    echo "LITTLE"
	    echo "Result: little" >> config.log
	    rm -f __conftest*
	    exit 0
	    ;;
	*) # oh well
	    ;;
    esac
done

# try od just in case the reason it failed above is that we aren't ascii
echo "Running: od -h __conftest.o" >> config.log
DATA=$( (od -h __conftest.o || echo FAILED) 2>&1)
echo "Results: $DATA" >> config.log
case "$DATA" in
    *"beef    dead"*)
	echo LITTLE
	echo "Result: little" >> config.log
	rm -f __conftest*
	exit 0
	;;
    *"dead    beef"*)
	echo BIG
	echo "Result: big" >> config.log
	rm -f __conftest*
	exit 0
	;;
    *) ;;
esac

# ok, we couldn't objdump, and od doesn't work, and probing compiler
# symbols didn't help. I think it's reasonable to give up.
echo "Out of tests for host endianness" >> config.log
rm -f __conftest*
exit 1
