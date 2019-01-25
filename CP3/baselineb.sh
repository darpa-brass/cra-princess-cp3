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
cd run_evaluation
./reconstruct_baselineb.sh $observed_data

echo "reconstruct_scenario complete"

echo "evaluation_started"

./eval_result.sh  /test/target_reconst_file.json /$true_data $operation_start_date $perturbed_sensor /test/rmse_error.json

echo "evaluation_complete"

echo "scenario baseline completed"

cd ..
