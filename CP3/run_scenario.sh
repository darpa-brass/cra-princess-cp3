#!/bin/bash
res=`cat /test/data`
length=`echo $res | jq '. | length'`
VARIABLE=0
while [ $VARIABLE -lt "$length" ]
do	
	input=`echo $res | jq .[$VARIABLE]`
	tempfile=`mktemp /tmp/secureXXXXXXXX`
	echo $input > "$tempfile"
	stage=`echo $res | jq .[$VARIABLE] | jq .stage | sed -e 's/^"//' -e 's/"$//'`
	true_data=`echo $res | jq .[$VARIABLE] | jq .true_data | sed -e 's/^"//' -e 's/"$//'`
	observed_data=`echo $res | jq .[$VARIABLE] | jq .observed_data | sed -e 's/^"//' -e 's/"$//'`
	perturbed_sensor=`echo $res | jq .[$VARIABLE] | jq .perturbed_sensor | sed -e 's/^"//' -e 's/"$//'`
	perturbed_sensor="[$perturbed_sensor]"

	if [ "$stage" == "BaselineB" ]; then
		./baselineb.sh $true_data $observed_data $perturbed_sensor
	fi
	if [ "$stage" == "Challenge" ]; then
		scenario=`echo $res | jq .[$VARIABLE] | jq .scenario | sed -e 's/^"//' -e 's/"$//'`
		if [ "$scenario" == "0" ]; then
			training_data_old=`echo $res | jq .[$VARIABLE] | jq .training_data_old | sed -e 's/^"//' -e 's/"$//'`
			training_data_new=`echo $res | jq .[$VARIABLE] | jq .training_data_new | sed -e 's/^"//' -e 's/"$//'`
			./scenario0.sh $true_data $observed_data $perturbed_sensor $training_data_old $training_data_new
			
		else
			num_adaptation_days=`echo $res | jq .[$VARIABLE] | jq .num_adaptation_days`
			training_data_old=`echo $res | jq .[$VARIABLE] | jq .training_data_old | sed -e 's/^"//' -e 's/"$//'`
			./scenario1.sh $true_data $observed_data $perturbed_sensor $training_data_old $num_adaptation_days

			
		fi
	fi
	((VARIABLE++)) 
done
