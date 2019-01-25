'''
Convert matrix data to json format

Input
date	time	temperature	dew_point	humidity	wind_speed	wind_gust	
20150501	00:05	15.70	14.60	93.00	0.00	0.00	
20150501	00:10	15.70	14.60	93.00	0.00	0.00	
20150501	00:15	15.70	14.60	93.00	0.00	0.00	
20150501	00:20	15.70	14.60	93.00	0.00	0.00

[{"hum": "93", "tempi": "15.7", "datetime": "2015-05-01T00:05:00", "wgusti": "0", "dewpti": "14.6", "wspdi": "0"}, {"hum": "93", "tempi": "15.7", "datetime": "2015-05-01T00:10:00", "wgusti": "0", "dewpti": "14.6", "wspdi": "0"}]
'''


import json, os, sys, csv
from datetime import datetime

def process_file(ip_file, op_file):
	json_data = []
	with open(ip_file) as f:
		#Assume date and time headers are present in matrix data. Rest columns are converted as is given.
		for line in csv.DictReader(f, delimiter='\t'):
			dstr = line['date'] + 'T' + line['time'] 
			dt = datetime.strptime(dstr, "%Y%m%dT%H:%M")
			del line['date']
			del line['time']
			if '' in line:
				del line['']
			if None in line:
				del line[None]
			line["datetime"] = dt.isoformat()
			json_data.append(line)

	# base_file_name = os.path.basename(ip_file)
	# filename, fileext = os.path.splitext(base_file_name)
	# op_file = filename + '.json'
	# final_data = json.dumps(json_data, sort_keys = True, indent = 4)
	# sys.stdout.write(final_data)
	with open(op_file, 'w') as outfile:
		json.dump(json_data, outfile, sort_keys = True, indent = 4, ensure_ascii = True)

if __name__=='__main__':
	assert (len(sys.argv) == 3), "This program expects two filename as argument"
	infile = sys.argv[1]
	outfile = sys.argv[2]
	process_file(infile, outfile)
