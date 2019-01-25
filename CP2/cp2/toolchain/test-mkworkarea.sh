#!/bin/sh
# prepworkarea.sh - clear out any previous work results and make a new workdir
# usage: prepworkarea.sh

cd /cp2/toolchain || exit 1
if [ -d work ]; then
    rm -rf work
fi
mkdir work || exit 1
exit 0
