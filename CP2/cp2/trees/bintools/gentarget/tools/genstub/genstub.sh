#!/bin/sh
# genstub.sh - stub out stuff that isn't finished yet
# usage: genstub.sh specdir dir subdir file

SPECDIR="$1"
DIR="$2"
SUBDIR="$3"
FILE="$4"

case "$FILE" in
    targetmodes.*|targetreloc.*|targettoken.*) FROM=mips-handwritten;;
    *) FROM=mips;;
esac

cp "$DIR/$FROM/$SUBDIR/$FILE" "$FILE" || exit 1

