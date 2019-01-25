#!/bin/sh
# nativetarget.sh - determine native target name of environment
# usage: TARGET=$(sh nativetarget.sh)
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

# XXX this should probably be passed CC and examine the output of
# CC rather than random bins on the system, because the latter aren't
# too meaningful if we're crosscompiling.

(
    echo "   ============   "
    echo "Probing the native target type."
) >> config.log

CPU=$( (uname -p || echo FAILED) 2>&1 | tr '\n' ' ')
echo "uname -p produced: $CPU" >> config.log
case "$CPU" in
    *FAILED*)
	CPU=$( (uname -m || echo FAILED) 2>&1 | tr '\n' ' ')
	echo "uname -m produced: $CPU" >> config.log
	case "$CPU" in
	    *FAILED*) exit 1;;
	    *) ;;
	esac
	;;
    *) ;;
esac
CPU=$(echo "$CPU" | tr A-Z a-z | tr -d /- | tr -d '[:space:]')

# canonicalize some annoying cases
case "$CPU" in
    i[34567]86|80[34567]86) CPU=i386;;
    amd64) CPU=x86_64;;
    *) ;;
esac
echo "CPU: $CPU" >> config.log

BINFMT=

TMP=$( (file "$0" || echo FAILED) 2>&1 | tr '\n' ' ')
echo "file on myself produced: $TMP" >> config.log
case "$TMP" in
    *FAILED*)
	# file probably isn't present
	;;
    *text*)
	# file seems to be here, so give it a try.
	for P in /bin/cat /bin/rm /bin/sh /sbin/init; do
	    TMP="$(file /bin/cat 2>&1)"
	    echo "file on $P produced: $TMP" >> config.log
	    case "$TMP" in
		*ELF*) BINFMT=elf ;;
		*Mach-O*) BINFMT=macho ;;
		*PECOFF*) BINFMT=pecoff ;;
		*ECOFF*) BINFMT=ecoff ;;
		*XCOFF*) BINFMT=xcoff ;;
		*COFF*) BINFMT=coff ;;
		*a.out*) BINFMT=aout ;;
		*) ;;
	    esac
	    if [ x"$BINFMT" != x ]; then
		echo "BINFMT (via file $P): $BINFMT" >> config.log
		break
	    fi
	done
	;;
esac

if [ "x$BINFMT" = x ]; then
    for P in /bin/cat /bin/rm /bin/sh /sbin/init; do
	# test for elf the hard way
	TMP=$( (dd if=$P bs=1 skip=1 count=3 || echo FAILED) 2>/dev/null)
	case "$TMP" in
	    ELF)
		BINFMT=elf;
		echo "BINFMT (via dd $P): $BINFMT" >> config.log
		break
		;;
	    *) ;;
	esac
	# should test for other formats but we don't actually support
	# them so there isn't a whole lot of point yet.
    done
fi

if [ "x$BINFMT" = x ]; then
    echo "No binary format recognized." >> config.log
    exit 1
fi

OS=`(uname -s | tr A-Z a-z | sed 's,[/-],,g') 2>&1 || echo FAILED`
echo "uname -s (munged) produced: $OS" >> config.log
echo "OS: $OS" >> config.log

TARGET="${CPU}-${BINFMT}-${OS}"
echo "TARGET: $TARGET" >> config.log

case "$TARGET" in
    *FAILED*)
	exit 1
	;;
    *) 
	;;
esac

echo "$TARGET"
exit 0
