#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import sys
import json
from pprint import pprint
from collections import defaultdict
import csv
import numpy as np
from sklearn.linear_model import LinearRegression
from itertools import chain

input_file = sys.argv[1]
change_attributes = sys.argv[2]
change_time = sys.argv[3]
eval_start_time = sys.argv[4]
training_file1 = sys.argv[5]
training_file2 = sys.argv[6]

change_attributes = change_attributes.replace("[","")
change_attributes = change_attributes.replace("]","")
change_attributes = change_attributes.split(",")

def get_data_from_file(f1,f2):
	js = open(f1)
	datax = json.load(js)
	jq = open(f2)
	datay = json.load(jq)
	return datax,datay

def create_csv(jsondata1):
	fi = csv.writer(open("data1.csv","w"),delimiter = ',')
	for records in jsondata1:
		for obs in records["history"]["observations"]:
			l = []
			for x in obs.keys():
				if x not in change_attributes:
					  l.append(obs[x])
			fi.writerow(l)

def create_csv1(jsondata2,row_count1):
	fk = csv.writer(open("data2.csv","w"))
	x = 0
	for records in jsondata2:
		for obs in records["history"]["observations"]:
			if x < row_count1:
				fk.writerow(obs.values())
				x += 1	
			else:
				break

def get_changed_attributes(jsondata1):
	fi = csv.writer(open("data3.csv","w"),delimiter = ',')
        for records in jsondata1:
                for obs in records["history"]["observations"]:
                        l = []
                        for x in obs.keys():
                                if x in change_attributes:
                                          l.append(obs[x])
                        fi.writerow(l)

def test_data(input_file):
	js = open(input_file)
	datax = json.load(js)
	fi = csv.writer(open("data4.csv","w"),delimiter = ',')
	for records in datax:
		for obs in records["history"]["observations"]:
			l = []
			for x in obs.keys():
				if x not in change_attributes:
					  l.append(obs[x])
			fi.writerow(l)

	fj = csv.writer(open("data5.csv","w"),delimiter = ',')
	for records in datax:
		for obs in records["history"]["observations"]:
			l = []
			for x in obs.keys():
				if x in change_attributes:
					  l.append(obs[x])
			fj.writerow(l)


data1,data2 = get_data_from_file(training_file1,training_file2)

create_csv(data1)
row_count1 = 0
with open("data1.csv","r") as f:
    reader = csv.reader(f,delimiter = ",")
    data = list(reader)
    row_count1 = len(data)

create_csv1(data2,row_count1)
get_changed_attributes(data1)
a = np.loadtxt(open("data1.csv", "rb"), delimiter=",")
b = np.loadtxt(open("data2.csv", "rb"), delimiter=",")
c = np.concatenate((a, b), axis=1)
d = np.loadtxt(open("data1.csv", "rb"), delimiter=",")

test_data(input_file)
e = np.loadtxt(open("data4.csv", "rb"), delimiter=",")
f = np.loadtxt(open("data5.csv", "rb"), delimiter=",")
g = np.concatenate((e,f), axis=1)

lm = LinearRegression()
lm.fit(c,d)
predicted_values =  lm.predict(g)
l = []
for x in np.nditer(predicted_values):
	l.append(float(x))
js = open(input_file)
datax = json.load(js)
p = 0
for i in range(0,len(datax)):
	for observation in range(0,len(datax[i]["history"]["observations"])):
		for sensor in change_attributes:
			datax[i]["history"]["observations"][observation][sensor] = round(l[p],4)
        	p += 1

final= json.dumps(datax, sort_keys = True, indent = 4)

sys.stdout.write(final)




