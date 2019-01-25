#!/bin/sh
# checkranlib.sh - see if the selected static library indexer exists and works
# usage: sh checkranlib.sh "$CC" "$CFLAGS" "$AR" "$RANLIB"
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

CC="$1"
CFLAGS="$2"
AR="$3"
RANLIB="$4"

if [ "x$CC" = x ]; then
    echo "Usage: $0 CC CFLAGS AR RANLIB" 1>&2
    exit 1
fi

if [ "x$CFLAGS" = x ]; then
    # avoid errors from passing ""
    CFLAGS=-Dirrelevant
fi

cat >__conftest1.c <<EOF
    int bar(int b) {
	return b + 2;
    }
EOF

cat >__conftest2.c <<EOF
    int bar(int);
    int foo(int f) {
	return bar(f) + 1;
    }
EOF

cat >__conftestmain.c <<EOF
    int foo(int);
    int main(void) {
	return foo(3);
    }
EOF

(
	echo "   ============   "
	echo "Trying static archiver $AR"
	echo "First test library module is:"
	cat __conftest1.c
	echo "Second test library module is:"
	cat __conftest2.c
	echo "Main program module is:"
	cat __conftestmain.c
	echo "Running: $CC $CFLAGS -c __conftest1.c"
) >> config.log

if "$CC" "$CFLAGS" -c __conftest1.c >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Oops: the compiler failed."
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

(
	echo "Running: $CC $CFLAGS -c __conftest2.c"
) >> config.log

if "$CC" "$CFLAGS" -c __conftest2.c >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Oops: the compiler failed."
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

# Since we got through checkcc and checkar before we got here,
# just assume the compiler produced the .o files we expected.


# Add __conftest1.o first so the reference from foo to bar goes
# backwards in the .a file. With normal Unix linkers that requires the
# .a file to be indexed.

rm -f __conftest.a # just in case
echo "Running: $AR cq __conftest.a __conftest1.o __conftest2.o" >> config.log
if ("$AR" cq __conftest.a __conftest1.o __conftest2.o) >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Oops: $AR failed. Help?"
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

echo "Running: $RANLIB __conftest.a" >> config.log
if ("$RANLIB" __conftest.a) >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "$RANLIB failed."
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

# Now try linking.

echo "Running: $CC $CFLAGS __conftestmain.c __conftest.a -o __conftest" \
	>> config.log
if "$CC" "$CFLAGS" __conftestmain.c __conftest.a -o __conftest \
	>> config.log 2>&1; then
    echo "Succeeded." >> config.log
    rm -f __conftest*
    exit 0
fi

(
    echo "Exit $?"
    echo "Failed."
    echo "Running: $CC $CFLAGS __conftestmain.c __conftest.a __conftest.a " \
	"-o __conftest"
) >> config.log

if "$CC" "$CFLAGS" __conftestmain.c __conftest.a __conftest.a -o __conftest \
	>> config.log 2>&1; then
    echo "That worked, which means $RANLIB definitively does not." \
	>> config.log
    rm -f __conftest*
    exit 1
fi

echo "That didn't work either. Maybe something deeper is wrong." >> config.log
rm -f __conftest*
exit 1
