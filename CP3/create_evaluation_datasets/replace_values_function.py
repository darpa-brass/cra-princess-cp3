#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
import json
from pprint import pprint
import random
from replace_functions import *

files = sys.argv[1]
start_date1 = sys.argv[4]
start_array = start_date1.split("/")
end_date1 = sys.argv[5]
end_array = end_date1.split("/")
start_date = date(int(start_array[2]),int(start_array[0]),int(start_array[1]))

end_date = date(int(end_array[2]),int(end_array[0]),int(end_array[1]))
col1 = sys.argv[2]
function1 = sys.argv[3]

try:
	start_date = date(int(start_array[2]),int(start_array[0]),int(start_array[1]))
	end_date = date(int(end_array[2]),int(end_array[0]),int(end_array[1])) + timedelta(1)
	if start_date > end_date:
		raise ValueError("Start date should preceed end date")
	if len(start_array) != 3:
		raise ValueError("Invalid start date format")
	if len(end_array) != 3:
		raise ValueError("Invalid end date format")

except ValueError as v:
	sys.stdout.write(str(v))
	exit()
	
def daterange(start_date, end_date):
    for n in range(int ((end_date - start_date).days)):
        yield start_date + timedelta(n)
date_range = []

for single_date in daterange(start_date, end_date):
    date_range.append(single_date.strftime("%Y-%m-%d"))

final_data = []

data = json.loads(open(files).read())

x = 0

for i in range(0,len(data)):
	dates = dateutil.parser.parse(data[i]["datetime"]).date()
	if str(dates) in date_range:
  		x = float(data[i][col1])
  		data[i][col1] = eval(function1)(x)


  		
final_data = json.dumps(data, sort_keys = True, indent = 4)

sys.stdout.write(final_data)
