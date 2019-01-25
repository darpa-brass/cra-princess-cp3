#!/bin/sh -x
# dockerbuild.sh - build the cp2 docker container directly
# usage: ./dockerbuild.sh

docker build -t harvard-princess/sut .
