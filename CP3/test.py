'''
Ex: Usage: python test.py austin1

Run Test for Test Cases in a Cluster.
'''
import json
import imp
import time
import numpy
import sys, os
alignment = imp.load_source('alignement_simple', './alignment/alignment_simple.py')

def rmse(prediction, target):
	return numpy.sqrt(((prediction - target) ** 2).mean())

def compute_error(f1, f2):
	with open(f2) as al_file:
		aligned_data = json.load(al_file)
	with open(f1) as data_file:
		file_data = json.load(data_file)
		sensor_keys = file_data[0].keys()
		sensor_keys.remove("datetime")

	#print aligned_data
	#Create dict with datetime as key
	alignment_dict = {}
	file_dict = {}
	for line in aligned_data:
		alignment_dict[line["datetime"]] = line
	for line in file_data:
		file_dict[line["datetime"]] = line

	#print "alignment_dict",alignment_dict
	#print "file_dict", file_dict
	rmse_values = {}


	for value in sensor_keys:
		prediction = [0]
		target = [0]
		for k,v in alignment_dict.items():
			#exact timestamp should be present
			#print k,v
			if k in file_dict:
				if alignment_dict[k][value] is None or file_dict[k][value] is None:
					continue
				elif float(v[value]) < 0 or float(file_dict[k][value]) < 0 :
					#print alignment_dict[k][value], v[value], file_dict[k][value]
					continue
				else:
					prediction.append(float(v[value]))
					target.append(float(file_dict[k][value]))
					

		#print value, "\nPred\n",prediction, "\nTarget\n",target
		rmse_v = rmse(numpy.array(prediction), numpy.array(target))
		rmse_values[value] = rmse_v
		#print value,rmse_v
	
	return rmse_values

if __name__ == "__main__":
	testcases = sys.argv[1]
	for case in open(testcases):
		sensor_name = json.loads(case)[0]["perturbed_sensor"]
		with open("/test/experiments.json", "w") as f:
			f.write(case)
		print case.strip()
		with open("/test/data", "r") as f:
			j = json.load(f)
		with open("/test/data", "w") as f:
			j[0]["perturbed_sensor"] = sensor_name
			f.write(json.dumps(j))
		os.system('./start')
