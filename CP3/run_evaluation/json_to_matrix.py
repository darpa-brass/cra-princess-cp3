'''
Simple script to format input json data
EX: KCASANFR110.json with file contents [{"hum": "93", "tempi": "15.7", "datetime": "2015-05-01T00:05:00", "wgusti": "0", "dewpti": "14.6", "wspdi": "0"}, {"hum": "93", "tempi": "15.7", "datetime": "2015-05-01T00:10:00", "wgusti": "0", "dewpti": "14.6", "wspdi": "0"}..]
Output
20150501	00:05	15.70	14.60	93.00	0.00	0.00	
20150501	00:10	15.70	14.60	93.00	0.00	0.00	
20150501	00:15	15.70	14.60	93.00	0.00	0.00	
20150501	00:20	15.70	14.60	93.00	0.00	0.00
'''

import json, os, sys
from datetime import datetime
#Some of the sensor values may be None (or null in json)
ERROR_VALUE = -99999.0

error_files = []

def process_json(ip_file):
	# print 'Processing file: ' , ip_file
	try:
		data = json.loads(open(ip_file).read())

		formatted_txt = []
		json_keys = data[0].keys()
		#assumption json file should have datetime object
		json_keys.remove("datetime")
		headers = ['date', 'time'] + json_keys
		formatted_txt.append(headers)
		for obsv in data:
			try:
				dt = datetime.strptime(obsv["datetime"], "%Y-%m-%dT%H:%M:%S")
				mdata = [dt.strftime('%Y%m%d'), dt.strftime('%H:%M')]
				for h in headers[2:]:
					#Some of the sensor values may be None (or null in json)
					v = None
					if h in obsv:
						v = ERROR_VALUE if (obsv[h] is None) else float(obsv[h])
					mdata.append(v)
				formatted_txt.append(mdata)
				
			except KeyError as e:
				print ip_file, ": Has some missing recordings"
				continue


		base_file_name = os.path.basename(ip_file)
		filename, fileext = os.path.splitext(base_file_name)
		op_matrix_file = filename + '.txt'
		path = os.path.join(os.path.dirname(os.path.abspath(ip_file)), op_matrix_file)
		#print 'Writing formatted txt file: ' , op_matrix_file

		with open(path, 'w') as outtxt:
			for obs in formatted_txt:
				for val in obs:
					# if type(val) is float:
					# 	outtxt.write('%0.2f' %val)
					# else:
					# 	outtxt.write(val)
					# outtxt.write('\t')
					outtxt.write(str(val).strip())
					outtxt.write('\t')
				outtxt.write('\n')
	except Exception as e:
		print 'Could not process file:' + ip_file
		print 'Exception: ', repr(e)
	#else:
		#print 'Finished processing file: ' + ip_file
	

if __name__=='__main__':
	assert (len(sys.argv) == 2), "This program expects one filename as argument"
	filename = sys.argv[1]
	process_json(filename)
