#!/bin/bash
#this script replaces values of sensors specified with values of sensors of nearby station
tempfile=`mktemp /tmp/secureXXXXXXXX`

cat > "$tempfile"

replaced_sensor=$1
nearby_filename=$2
nearby_sensor=$3
start_date=$4
end_date=$5

res=`python replace_values.py "$tempfile" $replaced_sensor $nearby_filename $nearby_sensor $start_date $end_date`
rm "$tempfile"
rm "replace_sensor.json"
rm "nearby_sensor.json"
echo $res | jq .

