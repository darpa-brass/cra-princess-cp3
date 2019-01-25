'''
Script to convert matrix data with only sensor values to matrix data with headers. This does a row by row substitution

Attention!!! the file formats has to be in the exact same order. Otherwise this script will not work


Input File A
date	time	temperature	dew_point	humidity	wind_speed	wind_gust	
20150501	00:05	15.70	14.60	93.00	0.00	0.00	
20150501	00:10	15.70	14.60	93.00	0.00	0.00	
20150501	00:15	15.70	14.60	93.00	0.00	0.00	
20150501	00:20	15.70	14.60	93.00	0.00	0.00

Input File B
13.70	12.60	92.00	0.00	0.00	
15.70	14.60	92.00	0.00	0.00	
15.70	14.60	90.00	0.00	0.00	
15.70	14.60	93.00	0.00	0.00


Output
date	time	temperature	dew_point	humidity	wind_speed	wind_gust	
20150501	00:05	13.70	12.60	92.00	0.00	0.00	
20150501	00:10	15.70	14.60	92.00	0.00	0.00	
20150501	00:15	15.70	14.60	90.00	0.00	0.00	
20150501	00:20	15.70	14.60	93.00	0.00	0.00

'''

import json, os, sys, csv

def process_file(fileA, fileB):
	ipdata = []
	reader = csv.DictReader(open(fileA), delimiter='\t')
	headers = reader.fieldnames
	if '' in headers:
		headers.remove('')
	#Assume date and time headers are present in matrix data. Rest columns are converted as is given.
	for line in reader:
		if '' in line:
			del line['']
		ipdata.append(line)

	opdata = []
	with open(fileB) as f:
		#There are no date and time headers are present in raw matrix data
		for line in csv.reader(f):
			if '' in line:
				line.remove('')
			opdata.append(line)

	base_file_name = os.path.basename(fileA)
	filename, fileext = os.path.splitext(base_file_name)
	op_file = filename + '_result.txt'
	path = os.path.join(os.path.dirname(os.path.abspath(fileA)), op_file)
	with open(path, 'w') as outfile:
		outfile.write('\t'.join(headers))
		outfile.write('\n')
		for initial, final in zip(ipdata, opdata):
			result = [initial["date"], initial["time"]]
			result.extend(final)
			for val in result:
				outfile.write(str(val))
				outfile.write('\t')
			outfile.write('\n')




if __name__ == '__main__':
	assert (len(sys.argv) == 3), "This program expects one filename as argument"
	fileA = sys.argv[1]
	fileB = sys.argv[2]
	process_file(fileA, fileB)