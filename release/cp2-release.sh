#!/usr/bin/env bash

# Set script variables

export PROJECT_NAME="princess-cp2"
export RELEASE_VERSION="1.0.0"
export CPTOOLKIT_VERSION="1.3.0"
export RELEASE_SCALA="2.12"

cd ..

# Create and populate the binary distribution directory structure

[[ -d ./releases ]] || mkdir ./releases
cd releases
[[ -d ./${PROJECT_NAME}_${RELEASE_VERSION}-${RELEASE_SCALA} ]] && rm -rf ./${PROJECT_NAME}_${RELEASE_VERSION}-${RELEASE_SCALA}
mkdir ./${PROJECT_NAME}_${RELEASE_VERSION}-${RELEASE_SCALA}

cd ./${PROJECT_NAME}_${RELEASE_VERSION}-${RELEASE_SCALA}

cp -R ../../CP2/. ./

# mkdir lib
# mkdir -p target/scala-${RELEASE_SCALA}
# copy ../../cptoolkit/latest/evaluation/lib/evaluation_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}.jar ./target/scala-${RELEASE_SCALA}/

cd ..

echo
echo Done!
echo
echo PRINCESS-CP2 v${RELEASE_VERSION} is ready for distribution.
echo

# Clear script variables

export PROJECT_NAME=
export RELEASE_VERSION=
export CPTOOLKIT_VERSION=
export RELEASE_SCALA=
