import json
import datetime
import argparse
import requests
import random
import urllib2
from TestHarnessAdapter import TestHarnessAdapter
import logging

class TestHarnessInteraction:
	def __init__(self):
		self.testAdapter = TestHarnessAdapter() 

	def initialize_system(self):
		json_string = self.testAdapter.sendReadyMessage()
		return json_string

	def record_error(self, timestamp, value, message):
		#f = requests.post(url+"error", headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp , 'Error': value, 'Message': message}))
		#return f.content
		self.testAdapter.sendErrorMessage(value, message)

	def status_message(self, timestamp, value, message):
		#f = requests.post(url+"status", headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp , 'Status': value, 'Message': message}))
                #return f.content
		self.testAdapter.sendStatusMessage(value, message)

        def done(self, timestamp, value, message):
                #f = requests.post(url+"done", headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp , 'Status': value, 'Results': message}))
                #return f.content
		self.testAdapter.sendDoneMessage(message)

	def generate_scenario_file(self,initialization):
		#Actaul API
		# Scenario File Initialization logic
		path = "CurDir/Scenario.json"
		return path

	def perturbation(self):
		#Actaul API
		msg = {	
		"failedsensors" : [{"id": "Sensor1", "Confidence-of-failure": 0.3 },
		{"id": "Sensor3", "Confidence-of-failure": 0.5 }]}
		return msg

	def get_reconstructed_file(self):
		#Actaul API
		file = {
			"Timestamp" : '2016-02-12T00:01:23',
			"Status" : 'RESULTS',
			"Results" : {
					"Lat" : 34.0522, 
					"Lon" : 118.2437,
					"DistanceFromDestination" : 200
				    }
			}
		return file

	
	def state_update(self):
		#Actaul API
		Message = {
		"GroundTruth": {
			"Lat": 224.3,
			"Lon": -99.8,
			"Depth": 440 ,
			"Heading": 'North',
			"Speed": 200
		}
		}
		
		return Message

if __name__ == "__main__":
	c = TestHarnessInteraction()
	LOG_FILENAME = 'TestHarnessAdapter'
	
	logging.debug("Mock CP1 Interation started at :"+ datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S'))
	#	Ready Initialization
	initialization = c.initialize_system()
	print "MOCK SUT INITIALIZED WITH :"+initialization
	logging.debug("MOCK SUT INITIALIZED WITH :"+initialization)

	#	Initialization Error Simulation
	timestamp =  '2017-12-13T02:01:34'
	value = 'INITIALIZATION_FAILURE'
	message = 'Scenario file not generated'
	c.record_error(timestamp,value,message) 
	print 'SIMULATED INITIALIZATION_FAILURE'

	# 	Scenario Generation Started
	timestamp =  '2017-12-13T02:01:45'
        value = 'SCENARIO_GENERATION_STARTED'
        message = c.generate_scenario_file(initialization)
        c.status_message(timestamp,value,message) 
	print 'SCENARIO_GENERATION_STARTED'



	 #       Scenario Generation Error Simulation
        timestamp =  '2017-12-13T02:02:13'
        value = 'SCENARIO_GENERATION_FAILURE'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message) 
	print 'SIMULATING SCENARIO_GENERATION_FAILURE'

	
	#       Scenario Generation Completed
        timestamp =  '2017-12-13T02:02:45'
        value = 'SCENARIO_GENERATION_COMPLETED'
        message = 'N/A'
        c.status_message(timestamp,value,message)
	print 'SCENARIO GENERATION COMPLETED'


	#	Scenario Execution Started
	timestamp =  '2017-12-13T02:03:45'
        value = 'SCENARIO_STARTED'
        message = 'N/A'
        c.status_message(timestamp,value,message)
	print 'SCENARIO STARTED'  

	#       Scenario Execution Error Simulation
        timestamp =  '2017-12-13T03:01:34'
        value = 'SCENARIO_FAILURE'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message)
	print 'SIMULATING SCENARIO FAILURE'
			
	#       State Update Message
        timestamp = '2017-12-13T03:01:34'
	value = 'STATE_UPDATE'
	message = c.state_update() 
        c.status_message(timestamp,value,message)
	print 'SIMULATING STATE UPDATE'
	
	#	Perturbation Detection
	timestamp = '2017-12-13T03:02:34'
        value = 'PERTURBATION_DETECTED'
	message = c.perturbation()
	c.status_message(timestamp, value, message)
	print 'SIMULATING PERTURBATION DETECTION'
	
	#	Adaptation Started
	timestamp = '2017-12-13T03:02:34'
        value = 'ADAPTATION_STARTED'
        message = 'N/A'
        c.status_message(timestamp, value, message) 
	print 'ADAPTATION STARTED'

	
        #       Adaptation Completed
        timestamp = '2017-12-13T03:02:34'
        value = 'ADAPTATION_COMPLETED'
        message = 'Parameters learnt are : P1,P2,P3'
        c.status_message(timestamp, value, message) 
	print 'ADAPTATION COMPLETED'


        #       Adaptation Error Simulation
        timestamp =  '2017-12-13T03:01:34'
        value = 'ADAPTATION_ERROR'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message) 
	print 'SIMULATING ADAPTATION ERROR'

	#       Adaptation Failure Simulation
        timestamp =  '2017-12-13T02:03:45'
        value = 'ADAPTATION_FAILURE'
        message = 'The reason for failure are : F1, F2'
        c.status_message(timestamp,value,message)  
	print 'SIMULATING ADAPTATION FAILURE'


        #       Scenario Completion
        timestamp =  '2017-12-13T05:03:45'
        value = 'SCENARIO_COMPLETED'
        message = 'N/A'
        c.status_message(timestamp,value,message)   
	print 'SCENARIO COMPLETED'


	#	Result
        timestamp =  '2017-12-13T04:03:45'
        value = 'RESULTS'
        message = c.get_reconstructed_file()
        c.done(timestamp,value,message)  
	print 'RESULTS SENT TO TEST HARNESS'
