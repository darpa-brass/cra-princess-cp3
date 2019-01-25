#!/bin/sh
# checkar.sh - see if the selected static library archiver exists and works
# usage: sh checkar.sh "$CC" "$CFLAGS" "$AR"
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

#
# The principle is this: while most platforms don't actually need
# ranlib, a few do. While the test library and programs are created in
# a way such that traditional ar/ranlib implementations will fail to
# link without ranlib, it's difficult to be *sure* that if this
# library works without ranlib, a more complicated one will also. So,
# if ranlib seems to exist and doesn't garbage the library file, use
# it; otherwise skip it. With luck we won't hit a platform where
# ranlib trashes files and is also required.
#

CC="$1"
CFLAGS="$2"
AR="$3"

if [ "x$CC" = x ]; then
    echo "Usage: $0 CC CFLAGS AR" 1>&2
    exit 1
fi

if [ "x$CFLAGS" = x ]; then
    # avoid errors from passing ""
    CFLAGS=-Dirrelevant
fi

cat >__conftest.c <<EOF
    int foo(int f) {
	return f + 1;
    }
EOF

(
	echo "   ============   "
	echo "Trying static archiver $AR"
	echo "Test library module is:
	cat __conftest.c
	echo "Running: $CC $CFLAGS -c __conftest.c
) >> config.log

if "$CC" "$CFLAGS" -c __conftest.c >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Oops: the compiler failed."
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

if [ ! -f __conftest.o ]; then
    echo "Oops: the compiler did not produce __conftest.o" >> config.log
    rm -f __conftest*
    exit 1
fi

rm -f __conftest.a # just in case
echo "Running: $AR cq __conftest.a __conftest.o" >> config.log
if "$AR" cq __conftest.a __conftest.o >> config.log 2>&1; then
    :
else
    (
	echo "Exit $?"
	echo "Oops: it failed. Help?"
    ) >> config.log
    rm -f __conftest*
    exit 1
fi

(
    echo "Running: $AR t __conftest.a"
    if "$AR" t __conftest.a; then
	:
    else
	echo "Exit $?"
	echo "Failed -- not a good sign"
    fi
) >> config.log 2>&1

STUFF=$("$AR" t __conftest.a 2>&1 | grep __conftest.o)
if [ "x$STUFF" = x ]; then
    echo "The output doesn't seem to include __conftest.o" >> config.log
    rm -f __conftest*
    exit 1
fi
echo "Seems ok" >> config.log

rm -f __conftest*
exit 0
