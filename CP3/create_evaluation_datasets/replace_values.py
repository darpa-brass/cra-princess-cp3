#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
import json
from pprint import pprint
from collections import defaultdict
import numpy as np
import pandas as pd
import time
import json
from optparse import OptionParser
import decimal
import alignment_simple
files = sys.argv[1]
start_date = sys.argv[5]
end_date = sys.argv[6]
start_date = start_date + 'T00:00'
end_date = datetime.strptime(end_date, '%m/%d/%Y').date() + timedelta(1)
end_date = end_date.strftime('%m/%d/%Y') + 'T00:00'
sensors = sys.argv[2]
nearby_filename = sys.argv[3]
nearby_sensor = sys.argv[4]
start_date =datetime.strptime(start_date, '%m/%d/%YT%H:%M').isoformat()
end_date=datetime.strptime(end_date, '%m/%d/%YT%H:%M').isoformat() 

x = []
sensors = sensors.replace("[","")
sensors = sensors.replace("]","")
sensors = sensors.split(",")

nearby_sensor = nearby_sensor.replace("[","")
nearby_sensor = nearby_sensor.replace("]","")
nearby_sensor = nearby_sensor.split(",")

try:

  if start_date > end_date:
    raise ValueError("Start date should preceed end date")


except ValueError as v:
  sys.stdout.write(str(v))
  exit()
  

final_replace_data = []
final_nearby_data = []

replace_data = json.loads(open(files).read())

res1 = []

for i in range(0,len(replace_data)):

  if replace_data[i]["datetime"] >= start_date and replace_data[i]["datetime"] < end_date: 
      inner = {}
      inner["datetime"] = str(replace_data[i]["datetime"])
      for sensor in sensors:
        inner[sensor] = str(replace_data[i][sensor])
      res1.append(inner)

with open('replace_sensor.json', 'w') as outfile:
    json.dump(res1, outfile, sort_keys = True, indent = 4, ensure_ascii = True)


nearby_data = json.loads(open(nearby_filename).read())
res = []
outer = defaultdict(dict)
for i in range(0,len(nearby_data)):
  if nearby_data[i]["datetime"] >= start_date and nearby_data[i]["datetime"] < end_date:
    inner = {}
    inner["datetime"] = str(nearby_data[i]["datetime"])
    for sensor in nearby_sensor:
      inner[sensor] = str(nearby_data[i][sensor])
      res.append(inner)

with open('nearby_sensor.json', 'w') as outfile2:
    json.dump(res, outfile2, sort_keys = True, indent = 4, ensure_ascii = True)

a = alignment_simple.alignment_linear("replace_sensor.json","nearby_sensor.json")
output = alignment_simple.print_reslut(a)

for j in range(0,len(replace_data)):
  for i in range(0,len(output)):
    if replace_data[j]["datetime"] == output[i]["datetime"]:
      for cs in sensors:
          replace_data[j][str(cs)] =  output[i][str(cs)]

print json.dumps(replace_data)  





