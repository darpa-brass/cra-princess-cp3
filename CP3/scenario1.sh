#!/bin/bash
true_data=$1
observed_data=$2
perturbed_sensor=$3
operation_start_date=`cat $true_data | jq .[0] | jq .datetime | sed -e 's/^"//' -e 's/"$//'`
training_data_old=$4
num_adaptation_days=$5
IFS='T' read -ra ADDR <<< "$operation_start_date"
for i in "${ADDR[@]}"; do
    operation_start_date="$i"
    break
done
operation_start_date=`date -d $operation_start_date +%m/%d/%Y`
eval_start_date=$(date +%m/%d/%Y -d "$operation_start_date + $num_adaptation_days day")

cd run_evaluation
./reconstruct_scenario1.sh $observed_data $training_data_old $perturbed_sensor $operation_start_date $eval_start_date
if [ ! -f output_temp.json ]
	then
	exit
fi
./load_reconst_data.sh /test/target_reconst_file.json

echo "reconstruct_scenario1 complete"

echo "evaluation_started"

./eval_result.sh /test/target_reconst_file.json /test/target_station.json $eval_start_date $perturbed_sensor /test/rmse_error.json 

echo "evaluation_complete"

echo "scenario 1 completed"

cd ..

rm -rf /test/*.txt
rm /test/target_scenario1.json