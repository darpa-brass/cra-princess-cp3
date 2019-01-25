#!/bin/bash

for outerDir in /vagrant/auto_gen_scenarios/bounding_box_*
do
	arrOuterIN=(${outerDir//// })
	mkdir /vagrant/output//${arrOuterIN[2]}
	for dir in ${outerDir}/dest*
	do

		arrIN=(${dir//// })
		mkdir /vagrant/output/${arrIN[2]}/${arrIN[3]}
		mkdir /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_A_runs/
		mkdir /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_B_runs/
		mkdir /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_C_runs/
		for file in ${dir}/*.json
		do
			cp $file /test/data
			echo "copied $file to /test/data ..."
			nohup ./grizzly-service.sh &
			./start
			sleep 1200
			pkill -f osgi
			pkill -f GrizzlyService
			pkill -f remus-simulator
			echo "finished running CP3 with $file ..."
			sleep 5
			mv /vagrant/cp3_kf_out_* /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_A_runs/
		done
		for file in ${dir}/baseline_B_params/*.json
		do
			cp $file /test/data
			echo "copied $file to /test/data ..."
			nohup ./grizzly-service.sh &
			./start
			sleep 1200
			pkill -f osgi
			pkill -f GrizzlyService
			pkill -f remus-simulator
			echo "finished running CP3 with $file ..."
			sleep 5
			mv /vagrant/cp3_kf_out_* /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_B_runs/
		done
		for file in ${dir}/baseline_C_params/*.json
		do
			cp $file /test/data
			echo "copied $file to /test/data ..."
			nohup ./grizzly-service.sh &
			./start
			sleep 1200
			pkill -f osgi
			pkill -f GrizzlyService
			pkill -f remus-simulator
			echo "finished running CP3 with $file ..."
			sleep 5
			mv /vagrant/cp3_kf_out_* /vagrant/output/${arrIN[2]}/${arrIN[3]}/baseline_C_runs/
		done
	done
done

