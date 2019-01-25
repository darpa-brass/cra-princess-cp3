import numpy as np
import pandas as pd
import json
from optparse import OptionParser
import time


def alignment_pd(file_a, file_b, m):
	temp_dict = dict()
	for line in json.load(open(file_a)):
		datetime_key = pd.to_datetime(line["datetime"], format="%Y-%m-%dT%H:%M:%S")
		del line["datetime"]
		temp_dict[datetime_key] = line
	df_a = pd.DataFrame.from_dict(temp_dict,orient='index')
	df_a = df_a.astype(float)
	temp_dict = dict()
	for line in json.load(open(file_b)):
		datetime_key = pd.to_datetime(line["datetime"], format="%Y-%m-%dT%H:%M:%S")
		del line["datetime"]
		temp_dict[datetime_key] = line
	df_b = pd.DataFrame.from_dict(temp_dict,orient='index')
	df_b = df_b.astype(float)

	for item in df_a.columns:
		df_a[item] = np.nan
	df = pd.concat([df_a, df_b]).sort_index()
	df = df.groupby(df.index).first()
	df = df.interpolate(method=m)
	df_c = df.ix[df_a.index.tolist()]
	if pd.isnull(df_c.iloc[0]['hum']):
		df_c.iloc[0] = df_b.iloc[0]
	return df_c

def interpolate(dict_c, dict_n, x, y, z):
	ans = dict()
	for key in dict_c:
		if dict_c[key] == None or dict_n[key] == None:
			ans[key] = None
		else:
			ans[key] = float(dict_c[key])+(float(dict_n[key])-float(dict_c[key]))/(z-y)*(x-y)
	return ans

def alignment_linear(file_a, file_b):
	dict_a = dict()
	for line in json.load(open(file_a)):
		timestamp = time.mktime(time.strptime(line["datetime"], "%Y-%m-%dT%H:%M:%S"))
		del line["datetime"]
		for key in line:
			line[key] = None
		dict_a[timestamp] = line
	dict_b = dict()
	for line in json.load(open(file_b)):
		timestamp = time.mktime(time.strptime(line["datetime"], "%Y-%m-%dT%H:%M:%S"))
		del line["datetime"]
		dict_b[timestamp] = line
	
	ts_b = dict_b.keys()
	ts_b.sort()
	ts_a = dict_a.keys()
	ts_a.sort()
	k = 0
	for j in xrange(0, len(ts_a)):
		t = ts_a[j]
		if t <= ts_b[0]:
			k += 1
	for i in xrange(0,len(ts_b)-1):
		ts = ts_b[i]
		ts_next = ts_b[i+1]
		temp = k
		for j in xrange(k, len(ts_a)):
			t = ts_a[j]
			if t <= ts_next:
				dict_a[t] = interpolate(dict_b[ts], dict_b[ts_next], t, ts, ts_next)
				temp += 1
			else:
				k = temp
				break
	for j in xrange(k, len(ts_a)):
		t = ts_a[j]
		if t >= ts_b[-1]:
			k += 1
	return dict_a

if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-a", "--fileA", dest="fileA", type="string",
                      help="input file A")
    parser.add_option("-b", "--fileB", dest="fileB", type="string",
                      help="input file B")
    parser.add_option("-m", "--method", dest="method", type="string",
                      help="interpolate method", default="index")

    (c_options, args) = parser.parse_args()

    file_a = c_options.fileA
    file_b = c_options.fileB
    m = c_options.method

    # df = alignment_pd(file_a, file_b, m)
    # output = list()
    # for ts in df.index:
    # 	d = df.loc[ts].to_dict()
    # 	d["datetime"] = ts.strftime(format="%Y-%m-%dT%H:%M:%S")
    # 	output.append(d)
    # print json.dumps(output)
    a = alignment_linear(file_a, file_b)
    keys = a.keys()
    keys.sort()
    output = list()
    for k in keys:
    	for dk in a[k]:
    		if a[k][dk] != None:
    			a[k][dk] = '%0.2f'%a[k][dk]
    	a[k]["datetime"] = time.strftime("%Y-%m-%dT%H:%M:%S",time.localtime(k))
    	output.append(a[k])
    print json.dumps(output)
