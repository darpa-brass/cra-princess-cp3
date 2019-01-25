#!/bin/sh -x
# dockershell.sh - run the csmith docker container and open a shell
# usage: dockershell.sh
# (build it with dockerbuild.sh first)

docker run --rm -i -t harvard-princess/csmith:latest /bin/bash

