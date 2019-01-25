#!/bin/sh -x
# dockerbuild.sh - build the docker container with csmith
# usage: ./dockerbuild.sh

docker build -t harvard-princess/csmith .
