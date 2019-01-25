'''
Script to convert matrix data with headers to matrix data with only sensor values
Input
date	time	temperature	dew_point	humidity	wind_speed	wind_gust	
20150501	00:05	15.70	14.60	93.00	0.00	0.00	
20150501	00:10	15.70	14.60	93.00	0.00	0.00	
20150501	00:15	15.70	14.60	93.00	0.00	0.00	
20150501	00:20	15.70	14.60	93.00	0.00	0.00
Output
15.70	14.60	93.00	0.00	0.00	
15.70	14.60	93.00	0.00	0.00	
15.70	14.60	93.00	0.00	0.00	
15.70	14.60	93.00	0.00	0.00
'''

import json, os, sys, csv

def process_file(ip_file):
	data = []
	with open(ip_file) as f:
		#Assume date and time headers are present in matrix data. Rest columns are converted as is given.
		reader = csv.reader(f, delimiter='\t')
		next(reader, None)
		for line in reader:
			if '' in line:
				line.remove('')
			data.append(line[2:]) #ignore the date and time values

		
	base_file_name = os.path.basename(ip_file)
	filename, fileext = os.path.splitext(base_file_name)
	op_file = filename + '_sensor_data.txt'
	path = os.path.join(os.path.dirname(os.path.abspath(ip_file)), op_file)
	with open(path, 'w') as outfile:
		for obs in data:
			val = '\t'.join(obs)
			outfile.write(val)
			outfile.write('\n')


if __name__ == '__main__':
	assert (len(sys.argv) == 2), "This program expects one filename as argument"
	filename = sys.argv[1]
	process_file(filename)
