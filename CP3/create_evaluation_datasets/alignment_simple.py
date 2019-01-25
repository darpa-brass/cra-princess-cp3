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
    x = time.mktime(time.strptime(x, "%Y-%m-%dT%H:%M:%S"))
    y = time.mktime(time.strptime(y, "%Y-%m-%dT%H:%M:%S"))
    z = time.mktime(time.strptime(z, "%Y-%m-%dT%H:%M:%S"))
    ans = dict()
    for key in dict_c:
        if dict_c[key] != None and dict_n[key] != None and dict_c[key] != "None" and dict_n[key] != "None":
            ans[key] = float(dict_c[key])+(float(dict_n[key])-float(dict_c[key]))/(z-y)*(x-y)
        else:
            ans[key] = None
    return ans

def alignment_linear(file_a, file_b):
    dict_a = dict()
    for line in json.load(open(file_a)):
        timestamp = line["datetime"]
        del line["datetime"]
        for key in line:
            line[key] = None
        dict_a[timestamp] = line
    dict_b = dict()
    for line in json.load(open(file_b)):
        timestamp = line["datetime"]
        del line["datetime"]
        dict_b[timestamp] = line
    
    ts_b = dict_b.keys()
    ts_b.sort()
    ts_a = dict_a.keys()
    ts_a.sort()

    k = 0
    i = 0
    
    while i < len(ts_a) and k < len(ts_b)-1:
        if ts_b[k] <=  ts_a[i]:
            if ts_b[k+1] >= ts_a[i]:
                dict_a[ts_a[i]] = interpolate(dict_b[ts_b[k]], dict_b[ts_b[k+1]], ts_a[i], ts_b[k], ts_b[k+1])
                i += 1
            else:
                k += 1
        else:
            i += 1

    return dict_a

def print_reslut(a):
    keys = a.keys()
    keys.sort()
    output = list()
    for k in keys:
    	temp = dict()
        for dk in a[k]:
            if a[k][dk] != None:
                temp[dk] = '%0.2f'%a[k][dk]
            else:
            	temp[dk] = a[k][dk]
        temp["datetime"] = k
        output.append(temp)
    return output
