#!/bin/sh
# checkgnu99.sh - see if --std=gnu99 is needed
# usage: RESULT=sh checkgnu99.sh "$CC" "$CFLAGS"
# prints "yes", "no", or "maybe".
#

#
# Copyright (c) 2017
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
#include <limits.h>
#ifndef LLONG_MAX
choke and die
#endif
EOF

(
	echo "   ============   "
	echo "Checking if we need --std=gnu99"
	echo "Test file is:
	cat __conftest.c
	echo "Running: $CC $CFLAGS -c __conftest.c
) >> config.log

if "$CC" $CFLAGS -c __conftest.c >> config.log 2>&1; then
    # all good
    rm -f __conftest*
    (
	echo "Succeeded, we should be ok."
    ) >> config.log
    echo "no"
    exit 0
fi
(
	echo "Exit $?"
	echo "That failed.
	echo "Running: $CC $CFLAGS --std=gnu99 -c __conftest.c
) >> config.log

if "$CC" $CFLAGS --std=gnu99 -c __conftest.c >> config.log 2>&1; then
    # all good
    rm -f __conftest*
    (
	echo "Ok, that worked."
    ) >> config.log
    echo "yes"
    exit 0
fi
(
	echo "Exit $?"
	echo "That failed too. Well, let's hope the build works anyway."
) >> config.log
rm -f __conftest*
echo "maybe"
exit 0
