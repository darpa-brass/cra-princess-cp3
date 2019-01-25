#!/bin/sh
# dobuild.sh - build csmith
# usage: dobuild.sh (in docker container)

VERSION=2.3.0

cd /csmith || exit 1
tar -xvzf csmith-$VERSION.tar.gz || exit 1
ln -s csmith-csmith-$VERSION src || exit 1
cd csmith-csmith-$VERSION || exit 1
./configure --prefix=/csmith/installed || exit 1
make && make install || exit 1
