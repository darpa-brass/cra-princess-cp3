import oct2py
import sys
import pandas as pd
import numpy
from oct2py import octave as oct

data = pd.read_csv('simulator_data_test.txt', header = None,sep='\t')
data = data.as_matrix()

n = len(data)
print(n)
data_train = data[0:500,0:6]
adapt_model = oct.feval("train_adapter_interface", data, 3)
data_test = data[501]
print(data_test)
for i in range(20):
    fail_conf = oct.feval("detection_interface", data[500+i])
