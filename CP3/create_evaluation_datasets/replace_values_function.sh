#!/bin/bash
#replaces  sensor values with external values specified
tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

col1=$1

function=$2

START_RANGE=$3

END_RANGE=$4

res=`python replace_values_function.py "$tempfile" $col1 $function $START_RANGE $END_RANGE`

echo $res | jq .
