#!/bin/sh
# fixperms.sh - restore execute permissions
# usage: sh ./fixperms.sh
#
# Run this if execute permissions on the tree have been lost.

if [ $(dirname "$0") != . ]; then
    echo "$0: run me at the top of the tree" 1>&2
    exit 1
fi

chmod +x \
      cp2/docker*.sh \
      cp2/trees/bintools/configure \
      cp2/trees/bintools/gentarget/configure \
      cp2/trees/bintools/gentarget/tools/genstub/genstub.sh \
      cp2/trees/cassiopeia/ml_gen.sh \
      cp2/trees/update-*.sh \
      csmith/docker*.sh \
      csmith/filters/*.filter \
      csmith/scripts/*.sh

# for completeness
chmod +x fixperms.sh

exit 0
