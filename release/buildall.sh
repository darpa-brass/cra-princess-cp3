#!/usr/bin/env bash
cd ..
sbt clean compile
sbt test:compile test
sbt package
sbt packageSrc
sbt packageDoc

cd release
