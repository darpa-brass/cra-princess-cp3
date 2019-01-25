#!/bin/bash

tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

sensors=$1

res=`python attribute_project.py "$tempfile" $sensors`

rm "$tempfile"

echo $res | jq .
