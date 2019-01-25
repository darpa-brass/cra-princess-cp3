#!/bin/sh
# checkcc.sh - see if the selected C compiler exists and works
# usage: sh checkcc.sh "$CC" "$CFLAGS"
#
# Records to config.log but isn't chatty on the terminal.
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

if [ "x$CC" = x ]; then
    echo "Usage: $0 CC CFLAGS" 1>&2
    exit 1
fi

if [ "x$CFLAGS" = x ]; then
    # avoid errors from passing ""
    CFLAGS=-Dirrelevant
fi

cat >__conftest.c <<EOF
    int main(int argc, char *argv[]) {
	char *volatile a = argv[argc-1];
	(void)a;
        return 0;
    }
EOF

(
	echo "   ============   "
	echo "Trying compiler $CC with CFLAGS $CFLAGS"
	echo "Test program is:"
	cat __conftest.c
	echo "Running: $CC $CFLAGS __conftest.c -o __conftest"
) >> config.log

if ("$CC" "$CFLAGS" __conftest.c -o __conftest) >> config.log 2>&1; then
    if [ -x __conftest ]; then
	echo 'Succeeded' >> config.log

	#
	# At this point we really ought to try running __conftest to
	# make sure we don't have some situation like, say, a
	# dynamically linked -lgcc that doesn't work. Unfortunately,
	# if $CC is a cross-compiler we also won't be able to run the
	# output and there's not really any good way to distinguish
	# these cases.
	#

	rm -f __conftest*
	exit 0
    fi

    if [ -e __conftest ]; then
	(
	    echo "Output program is not executable:"
	    ls -ld __conftest
	) >> config.log
	rm -f __conftest*
	exit 1
    fi
    echo "No output program __conftest found." >> config.log
    rm -f __conftest*
    exit 1
fi

(
    echo "Oops: the compiler $CC didn't run."
    echo "Maybe it didn't like the flags $CFLAGS?"
) >> config.log
rm -f __conftest*
exit 1
