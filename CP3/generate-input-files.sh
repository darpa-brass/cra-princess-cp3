#!/bin/bash

################################################################################
# This script will write input files in a directory hierarchy designed to be
# convenient for quick comparisons between inputs and outputs of
# the same test conditions as follows:
# ./BambooEvalDir/<Test>/<Iteration>/<Baseline>/inputs/*.json
# where <Test> is one of Tests, Iteration is in 1 to Iterations, and Baseline is
# in Baselines. If "outputs" are stored in the same location as "inputs", this
# may save steps later for comparing output to input.
#
# There are configuration parameters at the top of the script that adjust the
# number, types, and ranges for values in the evaluation tests that are run. For
# an overview of the script logic, main is at the
# bottom of the script. The main logic calls helper functions to generate and
# write json files for the various test configurations.
#
# This script was originally intended to be used as an inline script task in a
# Bamboo deployment project.
################################################################################

################################################################################
# Configuration Parameters
################################################################################

InitialParamsFileName="cp3-initialParams.json"
BatteryPerturbFileName="cp3-batteryPerturbations.json"

# Number of tests to perform
Iterations=10
# Types of test cases (can remove items if only interested in a subset)
declare -a Tests=("StuckAt" "HighNoise" "MisCalibration" "Spikes")
# Types of baselines (can remove items if only interested in a subset)
declare -a Baselines=("A" "B" "ChallengeStage")

# SearchRegion Ranges (listed as "min max")
SearchRegion_LowerLeft_Lat_Range="0.0 0.0"
SearchRegion_LowerLeft_Lon_Range="0.0 0.0"
SearchRegion_UpperRight_Lat_Range="0.001 0.002"
SearchRegion_UpperRight_Lon_Range="0.001 0.002"
ObjectLocation_Lat_Range="0.001 0.002"
ObjectLocation_Lon_Range="0.0 0.002"

Origin_Lat_Range="0.0 0.0"
Origin_Lon_Range="0.0 0.0"
Destination_Lat_Range="0.0 0.0"
Destination_Lon_Range="0.0 0.0"

# Perturbing currents (PC)
PC_Num_Range="1 5"
PC_LowerLeft_Lat_Range="-0.0005 0.002"
PC_LowerLeft_Lon_Range="-0.0005 0.002"
PC_UpperRight_Lat_Range="0.0 0.0025"
PC_UpperRight_Lon_Range="0.0 0.0025"
PC_vE_Range="-2.0 2.0"
PC_vN_Range="-2.0 2.0"

# Battery perturbs
BatteryPerturbTimeIntoScenario_Range="10 360"
BatteryPerturbsNum_Range="1 2"
BatteryPowerReduction_Range="0.2 0.8" # todo Should this be fractional or int percent?

# Sensors perturbs
declare -a SetOfSensorsToPerturb=("dvl_surge" "water_speed" "RPM")
function getNominalSensorNoise() {
	case $1 in
	"dvl_surge")
		echo "0.017"
		;;
	"water_speed")
		echo "0.12"
		;;
	"RPM")
		echo "10.0"
		;;
	esac
}
# todo Confirm Mu/Sigma for Phase 3.
function getSensorMu() {
	case $1 in
	"dvl_surge")
		echo "2.84"
		;;

	*)
		echo "1.0"
		;;
	esac
}
function getSensorSigma() {
	case $1 in
	"dvl_surge")
		echo "0.83"
		;;

	*)
		echo "0.5"
		;;
	esac
}
# nominal bias, anchor, and anchorProbability are 0 in all cases
SensorPerturbTimeIntoScenario_Range="10 360"
NumRepeatedSpikes="5 30"


################################################################################
# Helper functions
################################################################################

function getRandomIntInRange() {
local min=$1
local max=$2
local n=${3:-1}

for randoms in 1..$(seq 1 1 ${n})
do
	echo $((min + RANDOM % (1 + max - min)))
done
}

function getRandomRealInRange () {
local min=$1
local max=$2

if (( $(echo "$min == $max" | bc -l) ))
then
	echo 0.0
else
	echo `perl -le "print rand(${max}-(${min})) +(${min})"`
fi
}

function getConstrainedRandomRealInRange() {
# use when a range must be further constrained by another range
local min=$1
local max=$2
local altMin=$3
local altMax=$4

#take greatest min
local actualMin=
if (( $(echo "$min > $altMin" | bc -l) ))
then
	actualMin=$min
else
	actualMin=$altMin
fi

#take smallest max
local actualMax=
if (( $(echo "$max < $altMax" | bc -l) ))
then
	actualMax=$max
else
	actualMax=$altMax
fi

getRandomRealInRange $actualMin $actualMax
}

function printLocation() {
cat << EOF
			"Lat": $1,
			"Lon": $2
EOF
}

################################################################################
# Print initial params
################################################################################

function printSearchRegion() {
cat << EOF
	"SearchRegion": {
		"LowerLeftLocation": {
$1
		},
		"UpperRightLocation": {
$2
		},
		"ObjectLocation": {
$3
		}
	}
EOF
}

function printSearchRegionWrapper() {
    searchRegion_LowerLeft_Lat=$(getRandomRealInRange $SearchRegion_LowerLeft_Lat_Range)
	searchRegion_LowerLeft_Lon=$(getRandomRealInRange $SearchRegion_LowerLeft_Lon_Range)
	searchRegion_LowerLeft=$(printLocation $searchRegion_LowerLeft_Lat $searchRegion_LowerLeft_Lon)
	searchRegion_UpperRight_Lat=$(getRandomRealInRange $SearchRegion_UpperRight_Lat_Range)
	searchRegion_UpperRight_Lon=$(getRandomRealInRange $SearchRegion_UpperRight_Lon_Range)
	searchRegion_UpperRight=$(printLocation $searchRegion_UpperRight_Lat $searchRegion_UpperRight_Lon)
	# object location must be within the search region, so we further constrain
	objectLocation_Lat=$(getConstrainedRandomRealInRange $ObjectLocation_Lat_Range $searchRegion_LowerLeft_Lat $searchRegion_UpperRight_Lat)
	objectLocation_Lon=$(getConstrainedRandomRealInRange $ObjectLocation_Lon_Range $searchRegion_LowerLeft_Lon $searchRegion_UpperRight_Lon)
	objectLocation=$(printLocation $objectLocation_Lat $objectLocation_Lon)
	echo "$(printSearchRegion "$searchRegion_LowerLeft" "$searchRegion_UpperRight" "$objectLocation")"
}

function printOrigin() {
    origin_Lat=$(getRandomRealInRange $Origin_Lat_Range)
	origin_Lon=$(getRandomRealInRange $Origin_Lon_Range)
cat << EOF
		"Origin": {
			$(printLocation "$origin_Lat" "$origin_Lon")
		}
EOF

}

function printDestination() {
	destination_Lat=$(getRandomRealInRange $Destination_Lat_Range)
	destination_Lon=$(getRandomRealInRange $Destination_Lon_Range)
cat << EOF
		"Destination": {
			$(printLocation "$destination_Lat" "$destination_Lon")
		}
EOF
}

function printPerturbCurrent() {
cat << EOF
		{
            "LowerLeftLocation": {
$1
            },
            "UpperRightLocation": {
$2
            },
            "vE": $3,
            "vN": $4
        }
EOF
}

function printPerturbCurrents() {
    pC_Num=$(getRandomIntInRange $PC_Num_Range)
	for i in $(seq 1 1 ${pC_Num})
	do
		pC_LowerLeft_Lat=$(getRandomRealInRange $PC_LowerLeft_Lat_Range)
		pC_LowerLeft_Lon=$(getRandomRealInRange $PC_LowerLeft_Lon_Range)
		pC_LowerLeft=$(printLocation $pC_LowerLeft_Lat $pC_LowerLeft_Lon)
		pC_UpperRight_Lat=$(getRandomRealInRange $PC_UpperRight_Lat_Range)
		pC_UpperRight_Lon=$(getRandomRealInRange $PC_UpperRight_Lon_Range)
		pC_UpperRight=$(printLocation $pC_UpperRight_Lat $pC_UpperRight_Lon)
		pC_vE=$(getRandomRealInRange $PC_vE_Range)
		pC_vN=$(getRandomRealInRange $PC_vN_Range)

		if (( $i > 1 )); then
			echo ","
		fi
		printPerturbCurrent "${pC_LowerLeft}" "${pC_UpperRight}" $pC_vE $pC_vN
	done
}

function printSensorPerturb() {
cat << EOF
		{
			"TimeIntoScenario": $1,
			"SensorName": "$2",
			"SensorBias": $3,
			"SensorNoise": $4,
			"SensorAnchor": $5,
			"SensorAnchorProbability": $6
		}
EOF
}

chooseRandomSensor() {
	echo "${SetOfSensorsToPerturb[$RANDOM % ${#SetOfSensorsToPerturb[@]} ]}"
}

function printStuckAt() {
	sensorName=$(chooseRandomSensor)

	mu=$(getSensorMu $sensorName)
	sigma=$(getSensorSigma $sensorName)

	min=$(echo "$mu + $sigma" | bc -l)
	max=$(echo "$mu + 6 * $sigma" | bc -l)

	timeIntoScenario=$(getRandomIntInRange $SensorPerturbTimeIntoScenario_Range)
	sensorBias=0
	sensorNoise=0
	sensorAnchor=$(getRandomRealInRange $min $max)
	sensorAnchorProbability=1
	printSensorPerturb "${timeIntoScenario}" "${sensorName}" "${sensorBias}" "${sensorNoise}" "${sensorAnchor}" "${sensorAnchorProbability}"
}

function printHighNoise() {
	sensorName=$(chooseRandomSensor)

	sigma=$(getSensorSigma $sensorName)

	min=$sigma
	max=$(echo "6 * $sigma" | bc -l)

	timeIntoScenario=$(getRandomIntInRange $SensorPerturbTimeIntoScenario_Range)
	sensorBias=0
	sensorNoise=$(getRandomRealInRange $min $max)
	sensorAnchor=0
	sensorAnchorProbability=0
	printSensorPerturb "${timeIntoScenario}" "${sensorName}" "${sensorBias}" "${sensorNoise}" "${sensorAnchor}" "${sensorAnchorProbability}"
}

function printMisCalibration() {
	sensorName=$(chooseRandomSensor)

	sigma=$(getSensorSigma $sensorName)

	min=$sigma
	max=$(echo "6 * $sigma" | bc -l)

	timeIntoScenario=$(getRandomIntInRange $SensorPerturbTimeIntoScenario_Range)
	sensorBias=$(getRandomRealInRange $min $max)
	sensorNoise=$(getNominalSensorNoise $sensorName)
	sensorAnchor=0
	sensorAnchorProbability=0
	printSensorPerturb "${timeIntoScenario}" "${sensorName}" "${sensorBias}" "${sensorNoise}" "${sensorAnchor}" "${sensorAnchorProbability}"
}

function printSpikes() {
	sensorName=$(chooseRandomSensor)

	sigma=$(getSensorSigma $sensorName)

	min=$sigma
	max=$(echo "10 * $sigma" | bc -l)

	spikeDelta=$(getRandomRealInRange $min $max)
	numSpikes=$(getRandomIntInRange $NumRepeatedSpikes)


	timeIntoScenarioStart=$(getRandomIntInRange $SensorPerturbTimeIntoScenario_Range)
	sensorNoise=$(getNominalSensorNoise $sensorName)
	sensorAnchor=0
	sensorAnchorProbability=0

	maxIdx=$(echo "${numSpikes} * 4" | bc)
	for spike in $(seq 0 1 $maxIdx)
	do
		phase=$(echo "${spike} % 4" | bc)
		if [ $phase -eq 3 ]; then
			phase=1
		fi

		sensorBias=$(echo "$phase * $spikeDelta" | bc -l)
		timeIntoScenario=$(echo "$timeIntoScenarioStart + $spike" | bc)

		if (( $spike > 0 )); then
		echo ","
		fi
		printSensorPerturb "${timeIntoScenario}" "${sensorName}" "${sensorBias}" "${sensorNoise}" "${sensorAnchor}" "${sensorAnchorProbability}"
	done
}

function printInitialParams() {
local searchRegion=$1
local origin=$2
local destination=$3
local sensorPerturbs=$4
local perturbingCurrents=$5
local adaptEnabled=$6

cat << EOF
{
$searchRegion,
$origin,
$destination,
	"DVLSensorPerturbations": [
$sensorPerturbs
	],
	"PerturbingCurrents": [
$perturbingCurrents
	],
	"Adaptation": $adaptEnabled
}
EOF
}

################################################################################
# Print battery perturbs
################################################################################

function printBatteryPerturb() {
cat << EOF
		{
            "TimeIntoScenario": $1,
            "PowerReduction": $2
        }
EOF
}

function printBatteryPerturbs() {
# sort battery perturbs by time into scenario
batteryPerturbsNum=$(getRandomIntInRange $BatteryPerturbsNum_Range)
declare -a batteryPerturbTimes=(`getRandomIntInRange $BatteryPerturbTimeIntoScenario_Range $batteryPerturbsNum | tr " " "\n" | sort -n | tr "\n" " "`)

maxIdx="$(($batteryPerturbsNum-1))"
for i in $(seq 0 1 $maxIdx)
do
	batteryPertubTime=${batteryPerturbTimes[$i]}
	batteryPowerReduction=$(getRandomRealInRange $BatteryPowerReduction_Range)

	if (( $i > 0 )); then
		echo ","
	fi
	printBatteryPerturb $batteryPertubTime $batteryPowerReduction
done
}

function printBatteryPerturbsWrapper() {
cat << EOF
{
	"BatteryPerturbations": [
$1
	]
}
EOF
}

################################################################################
# Main
################################################################################

main() {
evalDir="BambooEvalDir"
mkdir $evalDir
cd $evalDir
for iter in $(seq 1 1 ${Iterations})
do
	for test in "${Tests[@]}"
	do
		# use the same search region and perturbs across baselines, so we can compare
		searchRegion=$(printSearchRegionWrapper)
		origin=$(printOrigin)
		destination=$(printDestination)
		commonSensorPerturbs=$(print${test})
		commonPerturbCurrents=$(printPerturbCurrents)
		commonBatteryPerturbs=$(printBatteryPerturbs)

		for baseline in "${Baselines[@]}"
		do
			# create test location
			testDir="${test}/${iter}/${baseline}"
			inputsDir="inputs"
			outputsDir="outputs"

			mkdir -p $testDir
			cd $testDir

			mkdir $inputsDir
			mkdir $outputsDir
			cd $inputsDir

			case $baseline in
			A)
				sensorPerturbs=""
				perturbingCurrents=""
				batteryPerturbs=""
				adaptEnabled=false
			;;
			B)
				sensorPerturbs="${commonSensorPerturbs}"
				perturbingCurrents="${commonPerturbCurrents}"
				batteryPerturbs="${commonBatteryPerturbs}"
				adaptEnabled=false
			;;
			ChallengeStage)
				sensorPerturbs="${commonSensorPerturbs}"
				perturbingCurrents="${commonPerturbCurrents}"
				batteryPerturbs="${commonBatteryPerturbs}"
				adaptEnabled=true
			;;
			esac

			echo "Writing json files for iteration ${iter} of test ${test} and baseline ${baseline}..."
			printInitialParams "${searchRegion}" "${origin}" "${destination}" "${sensorPerturbs}" "${perturbingCurrents}" $adaptEnabled | jq . >> "${InitialParamsFileName}"
			printBatteryPerturbsWrapper "${batteryPerturbs}" | jq . >> "${BatteryPerturbFileName}"
			cd ../../../..
		done
	done
done
cd ..
echo "Done!"
}

time main