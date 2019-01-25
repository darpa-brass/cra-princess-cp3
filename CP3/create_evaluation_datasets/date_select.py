#!/usr/bin/env python
from datetime import  datetime, timedelta,date
import dateutil.parser
import sys
from os import path
import json
from pprint import pprint

files = sys.argv[1]
start_date1 = sys.argv[2]
start_date1 = start_date1 + 'T00:00'
end_date1 = sys.argv[3]
end_date1 = datetime.strptime(end_date1, '%m/%d/%Y').date() + timedelta(1)
end_date1 = end_date1.strftime('%m/%d/%Y') + 'T00:00'
try:
	start_date =datetime.strptime(start_date1, '%m/%d/%YT%H:%M').isoformat()
	end_date=datetime.strptime(end_date1, '%m/%d/%YT%H:%M').isoformat()	
	if start_date > end_date:
		raise ValueError("Start date should preceed end date")

except ValueError as v:
	sys.stdout.write(str(v))
	exit()


final_data = []

data = json.loads(open(files).read())

for i in range(0,len(data)):
	#dates = dateutil.parser.parse(data[i]["datetime"]).date()
	if data[i]["datetime"] >= start_date and data[i]["datetime"] < end_date:
		final_data.append(data[i])
	# if str(dates) in date_range:
	# 		final_data.append(data[i])

final_data = json.dumps(final_data, sort_keys = True, indent = 4)

sys.stdout.write(final_data)
