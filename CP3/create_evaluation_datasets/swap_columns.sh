#!/bin/bash
#to swap values of two sensors for particular date range
tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

col1=$1

col2=$2

START_RANGE=$3

END_RANGE=$4

res=`python swap_columns.py $filename $col1 $col2 $START_RANGE $END_RANGE`
rm "$tempfile"
echo $res | jq .

