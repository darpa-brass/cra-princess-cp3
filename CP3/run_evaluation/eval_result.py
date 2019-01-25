#!/usr/bin/env python

from datetime import  datetime, timedelta,date
import sys
import json
import dateutil.parser
from pprint import pprint
from collections import defaultdict
import math
import csv
import os

reconstruct_file = sys.argv[1]
truth_file = sys.argv[2]
start_date1 = sys.argv[3]
start_date1 = start_date1 + 'T00:00'
start_date =datetime.strptime(start_date1, '%m/%d/%YT%H:%M').isoformat()
x = []
ref_error_file = sys.argv[5]
perturbed_sensors = sys.argv[4]
perturbed_sensors = perturbed_sensors.replace("[","")
perturbed_sensors = perturbed_sensors.replace("]","")
perturbed_sensors = perturbed_sensors.split(",")
reconstruct_data = json.loads(open(reconstruct_file).read())
init_data = json.loads(open(truth_file).read())
ref_error = json.loads(open(ref_error_file).read())
error = defaultdict(float)
count = defaultdict(int)
n = 0
truth_data = []
reconstructed_data = []
for i in range(0,len(init_data)):
	if init_data[i]["datetime"] >= start_date:
			truth_data.append(init_data[i])

for i in range(0,len(reconstruct_data)):
	if reconstruct_data[i]["datetime"] >= start_date:
			reconstructed_data.append(reconstruct_data[i])			

for j in range(0,len(truth_data)):
	for key in perturbed_sensors:
		if truth_data[j][key] is not None and str(key) != "datetime" and reconstructed_data[j][key] is not None:
			error[key] = error[key] + pow(float(truth_data[j][key])-float(reconstructed_data[j][key]), 2)
			count[key] = count[key] + 1

end_date = truth_data[-1]["datetime"]
end_date = end_date.split("T")
final_res = []

for key in error.keys():
	eval_res = {}
	n = count[key]
	error[key] = round(math.sqrt(error[key]/n),4)
	if error[key] <= ref_error[0][key]:
		res = "PASS"
	else:
		res = "FAIL"
	eval_res["sensor"] = key
	eval_res["reconstruction_error"] = error[key]
	eval_res["ref_error"] = str(round(ref_error[0][key],3))
	eval_res["perc_improvement"] = str(round((((ref_error[0][key]-error[key])/ref_error[0][key])*100),3))
	eval_res["pass/fail"] = res
	final_res.append(eval_res)


re = []
for key in error.keys():
	if error[key] != 0:
		re.append(error[key])
final_data = json.dumps(final_res, sort_keys = True)
print(final_data)
print(",".join(str(x) for x in re))
print(datetime.strptime( end_date[0], "%Y-%m-%d" ).strftime('%m/%d/%Y'))