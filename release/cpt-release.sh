#!/usr/bin/env bash

# Set script variables

export PROJECT_NAME="CPToolkit"
export RELEASE_VERSION="1.3.0"
export RELEASE_SCALA="2.12"

# Create and populate the binary distribution directory structure

cd ../cptoolkit/latest

# Evaluation JAR

[[ -d ./evaluation ]] && rm -rf ./evaluation
mkdir ./evaluation
cd ./evaluation
mkdir ./lib
mkdir ./api
mkdir ./src

cp -R ../../source/evaluation/lib/. ./lib/
cp ../../source/evaluation/*.sh ./
cp ../../source/evaluation/*.bat ./
cp ../../../properties/*.properties ./
cp ../../source/evaluation/target/scala-${RELEASE_SCALA}/evaluation_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../source/evaluation/target/scala-${RELEASE_SCALA}/evaluation_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../source/evaluation/target/scala-${RELEASE_SCALA}/evaluation_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../../pathplanner/target/scala-${RELEASE_SCALA}/pathplanner_${RELEASE_SCALA}-*.jar ./lib/
cp ../../../lib_managed/jars/org.scala-lang/scala-library/scala-library-${RELEASE_SCALA}.8.jar ./lib/
cp ../../../lib_managed/jars/net.liftweb/lift-json_${RELEASE_SCALA}/lift-json_${RELEASE_SCALA}-*.jar ./lib/

cd ..

# REMUS Manager JAR

[[ -d ./remus ]] && rm -rf ./remus
mkdir ./remus
cd ./remus
mkdir ./lib
mkdir ./api
mkdir ./src

cp -R ../../source/remus/lib/. ./lib/
cp ../../../properties/*.properties ./
cp ../../source/remus/target/scala-${RELEASE_SCALA}/remus_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../source/remus/target/scala-${RELEASE_SCALA}/remus_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../source/remus/target/scala-${RELEASE_SCALA}/remus_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../../lib_managed/jars/org.scala-lang/scala-library/scala-library-${RELEASE_SCALA}.8.jar ./lib/
cp ../../../lib_managed/jars/net.liftweb/lift-json_${RELEASE_SCALA}/lift-json_${RELEASE_SCALA}-3.2.0.jar ./lib/

cd ..

# REMUS Viewer Application

[[ -d ./remus-viewer ]] && rm -rf ./remus-viewer
mkdir ./remus-viewer
cd ./remus-viewer
mkdir ./lib
mkdir ./api
mkdir ./src

cp -R ../../source/remus-viewer/lib/. ./lib/
cp -R ../../source/remus/lib/. ./lib/
cp ../../../properties/*.properties ./
cp ../../source/remus-viewer/*.sh ./
cp ../../source/remus-viewer/*.bat ./
cp ../../source/remus-viewer/*.properties ./
cp ../../source/remus-viewer/target/scala-${RELEASE_SCALA}/remusviewer_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../source/remus-viewer/target/scala-${RELEASE_SCALA}/remusviewer_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../source/remus-viewer/target/scala-${RELEASE_SCALA}/remusviewer_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../source/remus/target/scala-${RELEASE_SCALA}/remus_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./src/
cp ../../../lib_managed/jars/org.scala-lang/scala-library/scala-library-${RELEASE_SCALA}.8.jar ./lib/
cp ../../../lib_managed/jars/net.liftweb/lift-json_${RELEASE_SCALA}/lift-json_${RELEASE_SCALA}-3.2.0.jar ./lib/
cp ../../source/evaluation/target/scala-${RELEASE_SCALA}/evaluation_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/

cd ..

# Mock Test Harness Web Service

[[ -d ./mockwebservice ]] && rm -rf ./mockwebservice
mkdir ./mockwebservice
cd ./mockwebservice
mkdir ./lib
mkdir ./api
mkdir ./src
mkdir ./config

cp -R ../../source/mockwebservice/lib/. ./lib/
cp -R ../../source/mockwebservice/config/. ./config/
cp -R ../../source/evaluation/lib/. ./lib/
cp ../../../properties/*.properties ./
cp ../../source/mockwebservice/*.sh ./
cp ../../source/mockwebservice/*.bat ./
cp ../../source/mockwebservice/target/scala-${RELEASE_SCALA}/mockwebservice_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../source/mockwebservice/target/scala-${RELEASE_SCALA}/mockwebservice_${RELEASE_SCALA}-${RELEASE_VERSION}-javadoc.jar ./api/
cp ../../source/mockwebservice/target/scala-${RELEASE_SCALA}/mockwebservice_${RELEASE_SCALA}-${RELEASE_VERSION}-sources.jar ./src/
cp ../../../lib_managed/jars/org.scala-lang/scala-library/scala-library-${RELEASE_SCALA}.8.jar ./lib/
cp ../../../lib_managed/jars/net.liftweb/lift-json_${RELEASE_SCALA}/lift-json_${RELEASE_SCALA}-3.2.0.jar ./lib/
cp ../../source/evaluation/target/scala-${RELEASE_SCALA}/evaluation_${RELEASE_SCALA}-${RELEASE_VERSION}.jar ./lib/
cp ../../../pathplanner/target/scala-${RELEASE_SCALA}/pathplanner_${RELEASE_SCALA}-*.jar ./lib/

cd ..

# Documentation

cp ../source/doc/*.pdf ./

echo
echo Done!
echo
echo PRINCESS ${PROJECT_NAME} v${RELEASE_VERSION} is ready for distribution.
echo

# Clear script variables

export PROJECT_NAME=
export RELEASE_VERSION=
export RELEASE_SCALA=
exit 0
