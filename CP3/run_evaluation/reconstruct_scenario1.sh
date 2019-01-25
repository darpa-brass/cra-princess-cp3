#!/bin/bash
observed_data=$1
training_data_old=$2
cat $training_data_old <(echo ',') $observed_data > "temp.json"
cat "temp.json" | sed -r 's/(\[|\])//g' > "temp2.json"
echo -e "[\n$(cat "temp2.json")\n]" > "/test/target_scenario1.json"
rm temp2.json
rm temp.json
filename="/test/target_scenario1.json"

change_attributes=$3
change_time=$4
eval_time=$5

python json_to_matrix.py "$filename"
filename="${filename%.*}"
ext=".txt"
newext="_sensor_data.txt"
next="_result.txt"
change_column_id=`python get_column_id.py $filename$ext $change_attributes`
change_row_id=`python get_row_id.py $filename$ext $change_time`
eval_row_id=`python get_row_id.py $filename$ext $eval_time`
output_file_name=$filename$newext$ext
python tsv_to_matrix_sensor_data.py "$filename$ext"

if [ -z "$eval_row_id" -a "$eval_row_id" != " " ]
	then
	./th.sh DATA_ERROR Insufficient_test_data
	exit
fi

./th.sh READY
./th.sh ADAP_STARTED

octave --silent reconstruct_scenario1.m "$filename$newext" "$change_column_id" "$change_row_id" "$eval_row_id" "output_file.txt"
python sensor_data_to_matrix_with_headers.py "$filename$ext" output_file.txt 
python matrix_to_json.py "$filename$next" output_temp.json
rm "output_file.txt"

./th.sh ADAP_COMPLETED
