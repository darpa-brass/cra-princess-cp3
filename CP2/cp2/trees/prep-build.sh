#!/bin/sh
# build.sh - build trees
# usage: build.sh

cd /cp2/trees || exit 1

ulimit -s unlimited

#
# set environment variables from opam so we get the ocaml we just
# spent half an hour building.
#
# note: bintools doesn't require this; it works with the ocaml that
# comes with ubuntu 16.04. but cassiopeia does, and it's probably
# better to build everything with the same version.
#
eval $(opam config env)

############################################################
# bintools

# bintools itself gets built during the eval run; but we
# can and should build the gentarget code now.
#
# run the test suite since it doesn't take long and we might
# as well - this is image build time and if it fails we want
# to know.

echo '*** building bintools/gentarget ***'
(
    cd bintools/gentarget || exit 1
    sh ./configure || exit 1
    bmake || exit 1
    bmake test || exit 1
) || exit 1


############################################################
# cassiopeia

echo '*** building cassiopeia ***'
(
    cd cassiopeia || exit 1
    make || exit 1
) || exit 1

#
############################################################

exit 0
