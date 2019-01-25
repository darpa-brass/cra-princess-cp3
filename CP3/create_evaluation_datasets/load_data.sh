#!/bin/bash
#script to load data

tempfile=`mktemp /tmp/secureXXXXXXXX`

cat $1 > "$tempfile"

res=`python load_data.py "$tempfile"`

rm "$tempfile"

echo $res | jq .
