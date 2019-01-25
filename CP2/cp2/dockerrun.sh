#!/bin/sh
# dockerrun.sh - run the cp2 docker container
# usage: dockerrun.sh [host[:port]]
# (build it with dockerbuild.sh first)

case "$1" in
    "")
	HOSTARG=
	PORTARG=
	;;
    *:*)
	HOST=$(echo "$1" | sed 's,:.*,,')
	HOSTARG="--host $HOST"
	PORT=$(echo "$1" | sed 's,.*:,,')
	PORTARG="--port $PORT"
	;;
    *)
	HOST="$1"
	HOSTARG="--host $HOST"
	PORTARG=
	;;
esac

IMAGE=harvard-princess/sut:latest

echo "docker run --rm $IMAGE python3 main.py $HOSTARG $PORTARG"
docker run --rm $IMAGE python3 main.py $HOSTARG $PORTARG
