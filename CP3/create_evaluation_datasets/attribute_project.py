#!/usr/bin/env python

from datetime import  datetime, timedelta,date
import sys
import json
from pprint import pprint
from collections import defaultdict
files = sys.argv[1]
sensors = sys.argv[2]

sensors = sensors.replace("[","")
sensors = sensors.replace("]","")

sensors = sensors.split(",")
data = json.loads(open(files).read())

if len(data) == 0:
  final_data = json.dumps(data, sort_keys = True, indent = 4)
  sys.stdout.write(final_data)
else:
  try:
    for sensor in sensors:
      if sensor not in data[0].keys():
        raise ValueError("not a valid attribute")

  except ValueError as v:
    sys.stdout.write(str(v))
    exit()

  res =[]
  for i in range(0,len(data)):
    outer = defaultdict(dict)

    for j in range(0,len(data[i])):    
      inner = {}
      inner["datetime"] = str(data[i]["datetime"])
      for sensor in sensors:
        if data[i][sensor] is not None:
          inner[sensor] = str(data[i][sensor])
        else:
          inner[sensor] = None


    res.append(inner)
  final_data = json.dumps(res, sort_keys = True, indent = 4)
  sys.stdout.write(final_data)
