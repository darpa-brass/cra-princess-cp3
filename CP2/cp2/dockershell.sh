#!/bin/sh -x
# dockershell.sh - run the cp2 docker container and open a shell
# usage: dockershell.sh
# (build it with dockerbuild.sh first)

docker run --rm -i -t harvard-princess/sut:latest /bin/bash

