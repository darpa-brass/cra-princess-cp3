#!/usr/bin/env bash

# Set script variables

export PROJECT_NAME="princess-cp3"
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

mkdir lib
find ../../lib_managed -iname '*.jar' -exec cp {} ./lib/ \;

cp ../../kalmanfilter/target/scala-${RELEASE_SCALA}/kalmanfilter_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../kalmanfilter-component/target/scala-${RELEASE_SCALA}/kalmanfiltercomponent_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../localizationalgorithm/target/scala-${RELEASE_SCALA}/localizationalgorithm_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../princess/target/scala-${RELEASE_SCALA}/princess_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../cptoolkit/latest/evaluation/lib/*.jar ./lib/
cp ../../cptoolkit/latest/remus/lib/remus_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}.jar ./lib/
cp ../../cptoolkit/latest/remus/lib/messaging-0.1-SNAPSHOT.jar ./lib/
cp ../../remus-client/target/scala-${RELEASE_SCALA}/remusclient_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../remus-client/lib/*.jar ./lib/
cp ../../pathplanner/target/scala-${RELEASE_SCALA}/pathplanner_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../training/target/scala-${RELEASE_SCALA}/training_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/

# Copy PRISM native libs
cp -R ../../princess/lib/. ./lib/

# Copy Octave bridge native libs
cp ../../octave-bridge/src/liboctavebridge.so ./lib
cp ../../octave-bridge/src/octavebridge.dll ./lib

cp -R ../../launcher/. ./

# Grizzly Service

cp -R ../../cptoolkit/latest/mockwebservice/lib/. ./lib/
cp -R ../../cptoolkit/latest/mockwebservice/config/. ./config/
cp ../../cptoolkit/latest/mockwebservice/*.sh ./
cp ../../cptoolkit/latest/mockwebservice/*.bat ./
cp ../../cptoolkit/latest/mockwebservice/*.properties ./
cp ../../cptoolkit/latest/mockwebservice/lib/mockwebservice_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}.jar ./lib/

# Copy all JavaDoc/ScalaDoc

mkdir api
cp ../../cptoolkit/latest/evaluation/api/evaluation_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}-javadoc.jar ./api/
cp ../../cptoolkit/latest/remus/api/remus_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}-javadoc.jar ./api/
cp ../../kalmanfilter/target/scala-${RELEASE_SCALA}/kalmanfilter_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../kalmanfilter-component/target/scala-${RELEASE_SCALA}/kalmanfiltercomponent_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../localizationalgorithm/target/scala-${RELEASE_SCALA}/localizationalgorithm_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../princess/target/scala-${RELEASE_SCALA}/princess_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../remus-client/target/scala-${RELEASE_SCALA}/remusclient_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../pathplanner/target/scala-${RELEASE_SCALA}/pathplanner_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../training/target/scala-${RELEASE_SCALA}/training_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/

# Copy all source

mkdir src
cp ../../cptoolkit/latest/evaluation/src/evaluation_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}-sources.jar ./src/
cp ../../cptoolkit/latest/remus/src/remus_${RELEASE_SCALA}-${CPTOOLKIT_VERSION}-sources.jar ./src/
cp ../../kalmanfilter/target/scala-${RELEASE_SCALA}/kalmanfilter_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../kalmanfilter-component/target/scala-${RELEASE_SCALA}/kalmanfiltercomponent_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../localizationalgorithm/target/scala-${RELEASE_SCALA}/localizationalgorithm_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../princess/target/scala-${RELEASE_SCALA}/princess_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../remus-client/target/scala-${RELEASE_SCALA}/remusclient_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../pathplanner/target/scala-${RELEASE_SCALA}/pathplanner_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../training/target/scala-${RELEASE_SCALA}/training_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/

# Copy text files and runtime scripts

cp -R ../../CP3/. ./

cd ..

echo
echo Done!
echo
echo PRINCESS-CP3 v${RELEASE_VERSION} is ready for distribution.
echo

# Clear script variables

export PROJECT_NAME=
export RELEASE_VERSION=
export CPTOOLKIT_VERSION=
export RELEASE_SCALA=
