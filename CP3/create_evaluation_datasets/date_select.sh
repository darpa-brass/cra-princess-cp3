#!/bin/bash
#script to select data belonging to a particular date range
tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

str=$filename

START_RANGE=$1

END_RANGE=$2

# res=`python date_select.py "$tempfile" $START_RANGE $END_RANGE`

# rm "$tempfile"

# echo $res | jq .

python date_select.py "$tempfile" $START_RANGE $END_RANGE