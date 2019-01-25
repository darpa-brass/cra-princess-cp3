'''
Ex: Usage: python create_baseline/create_baseline_error.py create_baseline/test_baseline/SANFRANCISCO/ < rmse_san_frncisco.json

Create Baseline Error for the weather data sets.This is precomputed on the weather data sets.


For each pair of station(A,B) in a region(NY/SF/LA)
	Compute alignment(A,B) - [aligns B sensor values to A sensor values]
	For each attribute (sensor reading) at a given timestamp,
		Calculate RMSE of the pair
		Calculate average of the recordings
'''
#import time
import json, os, sys, imp, time, numpy
from collections import defaultdict
alignment = imp.load_source('alignement_simple', './alignment/alignment_simple.py')

#SENSOR_VALUES = ["hum", "tempi","wgusti", "dewpti", "wspdi"]


def rmse(prediction, target):
	return numpy.sqrt(((prediction - target) ** 2).mean())


def compute_error(f1, f2):
	a = alignment.alignment_linear(f1, f2)
	keys = a.keys()
	keys.sort()
	aligned_data = list()
	for k in keys:
		for dk in a[k]:
			if a[k][dk] != None:
				a[k][dk] = '%0.2f'%a[k][dk]
		a[k]["datetime"] = time.strftime("%Y-%m-%dT%H:%M:%S",time.localtime(k))
		aligned_data.append(a[k])
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


def process_files(dir):
	region_files = []
	for subdir, dirs, filenames in os.walk(directory_path):
		files = [os.path.join(subdir,i) for i in filenames]
		region_files.extend(files)

	#print "Caluclating RMSE for ", region_files
	count = 0
	rmse_avg = defaultdict(float)
	#for v in SENSOR_VALUES:
	#	rmse_avg[v] = 0
	for f1 in region_files:
		for f2 in region_files:
			if f1 == f2:
				continue
			else:
				#print "computing RMSE for ", f1, "and ", f2
				count += 1
				rmse_values = compute_error(f1,f2)
				for k in rmse_values.keys():
					rmse_avg[k] += rmse_values[k]

	for k in rmse_values.keys():
		rmse_avg[k] /= count

	#print "RMSE Average",rmse_avg 
	#with open('./rmse.json', 'w'):
	#	json.dumps(rmse_avg)
	print json.dumps(rmse_avg)


if __name__ == '__main__':
	
	assert (len(sys.argv) == 2), "This program expects a directory path as argument"
	
	directory_path = sys.argv[1]
	process_files(directory_path)




