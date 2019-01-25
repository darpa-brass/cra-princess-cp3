'''
Ex: Usage: python random_testcases.py scenario0 AUSTIN1 > austin1.jl

Create Test Cases for Evaluation.
'''
import json
from os import walk
import random
import time, datetime
import sys
import os

def strTimeProp(start, end, format, prop):
    """Get a time at a proportion of a range of two formatted times.

    start and end should be strings specifying times formated in the
    given format (strftime-style), giving an interval [start, end].
    prop specifies how a proportion of the interval to be taken after
    start.  The returned time will be in the specified format.
    """

    stime = time.mktime(time.strptime(start, format))
    etime = time.mktime(time.strptime(end, format))

    ptime = stime + prop * (etime - stime)

    return time.strftime(format, time.localtime(ptime))

def randomDate(start, end, prop):
    return strTimeProp(start, end, '%m/%d/%Y', prop)

def getRandomWin(start, end, end2):
	tstart = randomDate(start, end, random.random())
	tend = time.mktime(time.strptime(tstart, '%m/%d/%Y')) + 2592000 * 2
	tend = time.strftime('%m/%d/%Y',time.localtime(tend))
	ostart = randomDate(start, end2, random.random())
	oend = time.mktime(time.strptime(ostart, '%m/%d/%Y')) + 2592000
	oend = time.strftime('%m/%d/%Y',time.localtime(oend))
	while tstart <= ostart <= tend or tstart <= oend <= tend:
		ostart = randomDate(start, end2, random.random())
		oend = time.mktime(time.strptime(ostart, '%m/%d/%Y')) + 2592000
		oend = time.strftime('%m/%d/%Y',time.localtime(oend))
	return tstart, tend, ostart, oend

def getRandomWin2(start, end):
	tstart = randomDate(start, end, random.random())
	tend = time.mktime(time.strptime(tstart, '%m/%d/%Y')) + 2592000 * 2
	tend = time.strftime('%m/%d/%Y',time.localtime(tend))
	ostart = time.mktime(time.strptime(tstart, '%m/%d/%Y')) + 2592000 * 2
	ostart = time.strftime('%m/%d/%Y',time.localtime(ostart))
	oend = time.mktime(time.strptime(tstart, '%m/%d/%Y')) +2592000 * 4
	oend = time.strftime('%m/%d/%Y',time.localtime(oend))
	return tstart, tend, ostart, oend

def timeconvert(x):
	return time.strftime("%m/%d/%Y",time.strptime(x, "%Y-%m-%dT%H:%M:%S"))

def generate(scenario, cluster):
	if not (os.path.isdir("./raw_data/"+cluster)):
		print "There is no cluster called "+cluster
		return False
	if scenario.lower() == "baseline":
		with open("/test/data", "w") as f:
			data = [{
				"stage": "BaselineB",
				"perturbed_sensor": "tempi",
				"true_data": "test/target_station.json",
				"observed_data": "test/target_station_changed.json"
			}]
			f.write(json.dumps(data))
	elif scenario.lower() == "scenario0":
		with open("/test/data", "w") as f:
			data = [{
				"stage": "Challenge",
				"scenario": "0",
				"perturbed_sensor": "tempi",
				"true_data": "test/target_station.json",
				"observed_data": "test/target_station_changed.json",
				"training_data_old": "test/target_training_file.json",
				"training_data_new": "test/nearby_training_file.json"
			}]
			f.write(json.dumps(data))
	elif scenario.lower() == "scenario1":
		with open("/test/data", "w") as f:
			data = [{
				"stage": "Challenge",
				"scenario": "1",
				"perturbed_sensor": "tempi",
				"true_data": "test/target_station.json",
				"observed_data": "test/target_station_changed.json",
				"training_data_old": "test/target_training_file.json",
				"num_adaptation_days": 30
			}]
			f.write(json.dumps(data))
	else:
		print "wrong scenario name"
		return False

	sensors = ["dewpti", "hum", "tempi", "wgusti", "wspdi"]
	
	for (dirpath, dirnames, filenames) in walk("raw_data/"+cluster):
		stations = random.sample(filenames, 2)
		for i in xrange(0,5):
			stations = random.sample(filenames, 2)
			if scenario.lower() == "scenario1":
				times = getRandomWin2("01/01/2015", "06/01/2016")
			else:
				times = getRandomWin("01/01/2015", "07/01/2016", "08/01/2016")
			for s in sensors:
				res = [{"cluster":cluster,"target_station":stations[0].replace(".json",""),"nearby_station":stations[1].replace(".json",""),
				"operational_data_start_date":times[2],"operational_data_end_date":times[3],
				"training_data_start_date":times[0],"training_data_end_date":times[1],"perturbed_sensor":s}]
				print json.dumps(res)
		break
	return True

if __name__ == "__main__":
	scenario = sys.argv[1]
	cluster = sys.argv[2]
	generate(scenario, cluster)