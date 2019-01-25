#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
from os import path
import json
from pprint import pprint

files = sys.argv[1]
data = json.loads(open(files).read())

res =[]
for i in range(0,len(data)):  
  	inner = {}
  	for key in data[i].keys():
  		if key in ["wgusti", "wspdi"]:
  			if data[i][key] in ["-99","-99.0","-99.9","-999","-999.0","-999.9","-9999","-9999.0","-9999.9","null","None"]:
  				inner[key] = None
  			elif 0 <= float(data[i][key]) <= 100:
  				inner[key] = data[i][key]
  			else:
  				inner[key] = None
  		elif key in ["dewpti", "tempi"]:
  			if data[i][key] in ["-99","-99.0","-99.9","-999","-999.0","-999.9","-9999","-9999.0","-9999.9","null","None"]:
  				inner[key] = None
  			elif -40 <= float(data[i][key]) <= 140:
  				inner[key] = data[i][key]
  			else:
  				inner[key] = None
  		elif key == "hum":
  			if data[i][key] in ["-99","-99.0","-99.9","-999","-999.0","-999.9","-9999","-9999.0","-9999.9","null","None"]:
  				inner[key] = None
  			elif 0 < float(data[i][key]) <= 100:
  				inner[key] = data[i][key]
  			else:
  				inner[key] = None
  		else:
  			inner[key] = inner[key] = data[i][key]
  	res.append(inner)

final_data = json.dumps(res, sort_keys = True, indent = 4)

sys.stdout.write(final_data)
