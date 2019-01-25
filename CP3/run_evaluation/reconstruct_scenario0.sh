#!/bin/bash
filename=$1

tempfile=`mktemp /tmp/secureXXXXXXXX`

./th.sh READY

change_attributes=$2
change_time=$3
train_file1=$4
train_file2=$5

ext=".txt"
newext="_sensor_data.txt"
next="_result.txt"
python json_to_matrix.py "$filename"
python json_to_matrix.py "$train_file1"
python json_to_matrix.py "$train_file2"
filename="${filename%.*}"
train_file1="${train_file1%.*}"
train_file2="${train_file2%.*}"
python tsv_to_matrix_sensor_data.py "$filename$ext"
python tsv_to_matrix_sensor_data.py "$train_file1$ext"
python tsv_to_matrix_sensor_data.py "$train_file2$ext"

change_column_id=`python get_column_id.py $filename$ext $change_attributes`
change_row_id=`python get_row_id.py $filename$ext $change_time`

file1_length=`wc -l $train_file1$newext | cut -f1 -d' '`
file2_length=`wc -l $train_file2$newext | cut -f1 -d' '`
if [ $file1_length -gt $file2_length ]
then
   lines_to_cut=$((file1_length-file2_length))
   echo "`head -n -$lines_to_cut $train_file1$newext`" > $train_file1$newext
else
   lines_to_cut=$((file2_length-file1_length))
   echo "`head -n -$lines_to_cut $train_file2$newext`" > $train_file2$newext
fi

./th.sh ADAP_STARTED 

octave --silent reconstruct_scenario0.m "$filename$newext" "$change_column_id" "$change_row_id" "$train_file1$newext" "$train_file2$newext" "output_file.txt"
python sensor_data_to_matrix_with_headers.py "$filename$ext" output_file.txt 
python matrix_to_json.py "$filename$next" output_temp.json
rm  "output_file.txt"
./th.sh ADAP_COMPLETED
