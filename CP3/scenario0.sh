#!/bin/bash
true_data=$1
observed_data=$2
perturbed_sensor=$3
operation_start_date=`cat $true_data | jq .[0] | jq .datetime | sed -e 's/^"//' -e 's/"$//'`
IFS='T' read -ra ADDR <<< "$operation_start_date"
for i in "${ADDR[@]}"; do
    operation_start_date="$i"
    break
done
operation_start_date=`date -d $operation_start_date +%m/%d/%Y`
training_data_old=$4
training_data_new=$5

cd run_evaluation
./reconstruct_scenario0.sh  $observed_data $perturbed_sensor $operation_start_date $training_data_old $training_data_new
./load_reconst_data.sh /test/target_reconst_file.json

echo "reconstruct_scenario0 complete"

echo "evaluation_started"

./eval_result.sh /test/target_reconst_file.json /test/target_station.json $operation_start_date $perturbed_sensor /test/rmse_error.json 

echo "evaluation_complete"

echo "scenario 0 completed"

cd ..
rm -rf /test/*.txt

