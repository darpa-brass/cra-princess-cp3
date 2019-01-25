#!/bin/sh
# dockerrun.sh - run the csmith docker container and produce a test corpus
# usage: dockerrun.sh [seed [number-of-tests]]
# (build it with dockerbuild.sh first)

case $# in
    2) SEED="$1" NUM="$2";;
    1) SEED="$1" NUM='100';;
    0) SEED="12345" NUM='100';;
    *) echo "$0: usage: $0 [seed [numtests]]" 1>&2; exit 1;;
esac

IMAGE=harvard-princess/csmith:latest
GEN=/csmith/scripts/dogenerate.sh

if ! [ -d corpus ]; then
    mkdir corpus corpus/failed || exit 1
else
    echo "*** WARNING: corpus/ already exists ***" 1>&2
fi

echo "docker run --rm -v $PWD/corpus:/corpus $IMAGE $GEN $SEED $NUM"
docker run --rm -v $PWD/corpus:/corpus $IMAGE $GEN $SEED $NUM
