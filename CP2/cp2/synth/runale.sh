#!/bin/sh
# runale.sh - run alewife to produce specs
# usage: runale.sh arch perturbation
#
# Expects to find the input snippet spec as "test.ale".
# 

ARCH="$1"
PERTURBATION="$2"

SPEC=/cp2/synth/test.ale

ALEWIFE=/cp2/trees/cassiopeia/alewife

echo "cd /cp2/synth"
cd /cp2/synth || exit 1

echo "$ALEWIFE test.ale -o test.spec"
$ALEWIFE test.ale -o test.spec || exit 1

exit 0
