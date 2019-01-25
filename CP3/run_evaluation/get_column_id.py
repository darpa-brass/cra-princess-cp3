#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
from os import path
import json	
import csv
sensors = sys.argv[2]
ip_file = sys.argv[1]
sensors = sensors.replace("[","")
sensors = sensors.replace("]","")

sensors = sensors.split(",")


with open(ip_file) as f:
		x = f.readline().split()
		for i in sensors:
			if i in x:
				changed_column = x.index(i)-1
print changed_column


