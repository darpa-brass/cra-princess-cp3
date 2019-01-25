import time
import json
import numpy
#import pandas as pd
from oct2py import octave as oct

class OctaveAPIs:
     def call_detection_api(self,reading,train_adapt,sensor,failure_status):
        reading = numpy.matrix(reading)
        detect = oct.feval("detection", reading, sensor, train_adapt,failure_status)
        return detect
     def call_adaptation_api(self,reading,train_adapt,sensor):
        reading = numpy.matrix(reading)
        detect = oct.feval("adapt", reading, sensor, train_adapt)
        return detect
