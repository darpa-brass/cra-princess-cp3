#!/usr/bin/env bash

./buildall.sh

./cpt-release.sh

cd ../release
./cp2-release.sh

cd ../release
./cp3-release.sh
