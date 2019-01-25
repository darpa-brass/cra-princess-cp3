#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
from os import path
import json
from pprint import pprint
import numpy

files = sys.argv[1]

start_date1 = sys.argv[2]
start_array = start_date1.split("/")
start_date = start_array[2]+start_array[0]+start_array[1]
counter = -1

with open(files) as f:
	data = f.readlines()

	for line in data:
		val = line.split("\t")
		counter += 1
		if val[0] != "date" and val[0] >= start_date:
			sys.stdout.write(str(counter))
			exit()



