#!/bin/bash
#evaluates the result of reconstructed values
reconstructed_data=$1
truth_data=$2
eval_start=$3
ref_error=$5
perturbed_sensor=$4
array=()
while IFS= read -r line ; do
    array+=("$line")
done < <(python eval_result.py $reconstructed_data $truth_data $eval_start $perturbed_sensor $ref_error)

./th.sh RESULTS ${array[0]}

./th.sh DONE ${array[1]} $eval_start ${array[2]}
