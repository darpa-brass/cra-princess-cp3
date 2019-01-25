#!/bin/bash

tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

col1=$1

function=$2

START_RANGE=$3

END_RANGE=$4

res=`python change_units.py "$tempfile" $START_RANGE $END_RANGE $col1 $function`

rm "$tempfile"

echo $res | jq .
