#!/bin/bash
res=`cat /test/experiments.json`
BASEDIR="/vagrant/raw_data/"
RESDIR="/test"
PROSDIR="/vagrant/processed_data/json_data/"
ext=".csv"
ext1=".json"
tmp="/"
rmse="rmse_"
perturbed_sensor=`echo $res | jq .[0] | jq .perturbed_sensor | sed -e 's/^"//' -e 's/"$//'`
perturbed_sensor="[$perturbed_sensor]"
export cluster=`echo $res | jq .[0] | jq .cluster | sed -e 's/^"//' -e 's/"$//'`
export target_station=`echo $res | jq .[0] | jq .target_station | sed -e 's/^"//' -e 's/"$//'`
export nearby_station=`echo $res | jq .[0] | jq .nearby_station | sed -e 's/^"//' -e 's/"$//'`
export operational_data_start_date=`echo $res | jq .[0] | jq .operational_data_start_date | sed -e 's/^"//' -e 's/"$//'`
export operational_data_end_date=`echo $res | jq .[0] | jq .operational_data_end_date | sed -e 's/^"//' -e 's/"$//'`
export training_data_start_date=`echo $res | jq .[0] | jq .training_data_start_date | sed -e 's/^"//' -e 's/"$//'`
export training_data_end_date=`echo $res | jq .[0] | jq .training_data_end_date | sed -e 's/^"//' -e 's/"$//'`
export perturbed_sensor
export BASEDIR
export RESDIR
export PROSDIR
export tmp
export ext
export ext1

cd create_evaluation_datasets

./load_data.sh  $BASEDIR$cluster$tmp$target_station$ext1 | ./date_select.sh $operational_data_start_date $operational_data_end_date | ./attribute_project.sh $perturbed_sensor > $RESDIR/target_station$ext1

./load_data.sh  $BASEDIR$cluster$tmp$target_station$ext1 | ./date_select.sh $operational_data_start_date $operational_data_end_date > $RESDIR/target_station_all_sensors$ext1
echo "target station loaded"

./load_data.sh  $BASEDIR$cluster$tmp$nearby_station$ext1 | ./date_select.sh $operational_data_start_date $operational_data_end_date > $RESDIR/nearby_station$ext1

echo "nearby station loaded"

cat $RESDIR/target_station_all_sensors$ext1 | ./replace_values.sh $perturbed_sensor $RESDIR/nearby_station$ext1 $perturbed_sensor $operational_data_start_date $operational_data_end_date > $RESDIR/target_station_changed$ext1

echo "replace_values done"

./load_data.sh  $BASEDIR$cluster$tmp$target_station$ext1 | ./date_select.sh $training_data_start_date $training_data_end_date > $RESDIR/target_training_file$ext1

echo "training_file1 generated"

./load_data.sh $BASEDIR$cluster$tmp$nearby_station$ext1 | ./date_select.sh $training_data_start_date $training_data_end_date | ./attribute_project.sh $perturbed_sensor > $RESDIR/nearby_training_file$ext1

echo "training_file2 generated"
cd ..
cp $PROSDIR$cluster$tmp$rmse$cluster$ext1 /test/rmse_error.json

rm /test/nearby_station$ext1	
