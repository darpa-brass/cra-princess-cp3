#!/bin/sh
# prep-download.sh - download additional software
#
# This script fetches the following:
#    - Racket
#    - Rosette
#    - Boolector
#
# Rosette specifically needs Racket 6.6. Until proven otherwise we'll
# use the binary download from upstream.
#
# We are using Rosette's head version, not the last release, which
# apparently doesn't quite work.

RACKET_FILE=racket-6.6-x86_64-linux.sh
RACKET_URL=https://mirror.racket-lang.org/installers/6.6/$RACKET_FILE

# this needs to be the full commit hash because that's the name of the
# directory that github sends in the download tarball.
#ROSETTE_COMMIT=4d75e7e12e85779208f46231263742363dcbece7
ROSETTE_COMMIT=0b1a630dcaee467e382d6766f6198048a43046cf
ROSETTE_URL=https://github.com/emina/rosette/archive/$ROSETTE_COMMIT.tar.gz

BOOLECTOR_NAME=boolector-2.4.1-with-lingeling-bbc
BOOLECTOR_URL=https://boolector.github.io/solver-archive/$BOOLECTOR_NAME.tar.xz

UCLIBC_NAME=uClibc-ng-1.0.30
UCLIBC_URL=https://downloads.uclibc-ng.org/releases/1.0.30/$UCLIBC_NAME.tar.xz

##############################

cd /cp2/software || exit 1

mkdir racket || exit 1
cd racket
echo "wget -q $RACKET_URL"
wget -q $RACKET_URL

cd ..
mkdir rosette || exit 1
cd rosette

echo "wget -q $ROSETTE_URL"
wget -q $ROSETTE_URL || exit 1
echo "tar -xzf $ROSETTE_COMMIT.tar.gz"
tar -xzf $ROSETTE_COMMIT.tar.gz || exit 1

echo "mv rosette-$ROSETTE_COMMIT rosette"
mv rosette-$ROSETTE_COMMIT rosette
cd ..

mkdir boolector || exit 1
cd boolector
echo "wget -q $BOOLECTOR_URL"
wget -q $BOOLECTOR_URL || exit 1
echo "tar -xJf $BOOLECTOR_NAME.tar.xz"
tar -xJf $BOOLECTOR_NAME.tar.xz || exit 1

echo "mv $BOOLECTOR_NAME boolector"
mv $BOOLECTOR_NAME boolector
cd ..

mkdir uclibc || exit 1
cd uclibc
echo "wget -q $UCLIBC_URL"
wget -q $UCLIBC_URL || exit 1
echo "tar -xJf $UCLIBC_NAME.tar.xz"
tar -xJf $UCLIBC_NAME.tar.xz || exit 1

echo "mv $UCLIBC_NAME uclibc"
mv $UCLIBC_NAME uclibc
cd ..

