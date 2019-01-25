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
		"failedsensors" : { "Sensor1" :  {"Confidence-of-failure": 0.3 },
		"Sensor3": {"Confidence-of-failure": 0.5 }}}
		return msg

	def get_reconstructed_file(self):
		#Actaul API
		file = {
			"Timestamp" : '2016-02-12T00:01:23',
			"Status" : 'RESULTS',
			"Results" : {
			"SensorReadings" : [{
				"Timestamp" : '2016-01-11T00:01:11',
					"Sensor1" : {
					"original" :  0.4,  
					"confidence-of-correctness" : 0.56,
					"adapted-value": 0.6,
					"accuracy" :  0.80},
		          
					"Sensor2" : {
                                        "original" :  0.2,
                                        "confidence-of-correctness" : 0.34,
                                        "adapted-value": 0.1,
                                        "accuracy" :  0.12},
                                
					"Sensor3" : {
                                        "original" :  0.5,
                                        "confidence-of-correctness" : 0.51,
                                        "adapted-value": 0.8,
                                        "accuracy" :  0.20},
                                },
				{"Timestamp" : '2016-01-11T00:02:11',
                                        "Sensor1" : {
                                        "original" :  0.4,
                                        "confidence-of-correctness" : 0.56,
                                        "adapted-value": 0.6,
                                        "accuracy" :  0.80},
                                
                                        "Sensor2" : {
                                        "original" :  0.2,
                                        "confidence-of-correctness" : 0.34,
                                        "adapted-value": 0.1,
                                        "accuracy" :  0.12},
                               
                                        "Sensor3" : {
                                        "original" :  0.5,
                                        "confidence-of-correctness" : 0.51,
                                        "adapted-value": 0.8,
                                        "accuracy" :  0.20},
                                }]
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
		},
		"EstimatedState": "Working",
		"SensorReading": {
			"DVLSensor": {
				"Depth": 150,
				"Heading": 'North',
				"Speed": 200
			}
		}
		}
		
		return Message

if __name__ == "__main__":
	c = TestHarnessInteraction()
	LOG_FILENAME = 'TestHarnessAdapter'
	
	logging.debug("Mock CP1 Interation started at :"+ datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S'))
	#	Ready Initialization
	initialization = c.initialize_system()
	logging.debug("MOCK SUT INITIALIZED WITH :"+initialization)

	#	Initialization Error Simulation
	timestamp =  '2017-12-13T02:01:34'
	value = 'INITIALIZATION_FAILURE'
	message = 'Scenario file not generated'
	c.record_error(timestamp,value,message) 


	# 	Scenario Generation Started
	timestamp =  '2017-12-13T02:01:45'
        value = 'SCENARIO_GENERATION_STARTED'
        message = c.generate_scenario_file(initialization)
        c.status_message(timestamp,value,message) 


	 #       Scenario Generation Error Simulation
        timestamp =  '2017-12-13T02:02:13'
        value = 'SCENARIO_GENERATION_FAILURE'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message) 
	
	#       Scenario Generation Completed
        timestamp =  '2017-12-13T02:02:45'
        value = 'SCENARIO_GENERATION_COMPLETED'
        message = 'N/A'
        c.status_message(timestamp,value,message)

	#	Scenario Execution Started
	timestamp =  '2017-12-13T02:03:45'
        value = 'SCENARIO_STARTED'
        message = 'N/A'
        c.status_message(timestamp,value,message)  

	#       Scenario Execution Error Simulation
        timestamp =  '2017-12-13T03:01:34'
        value = 'SCENARIO_FAILURE'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message)
	
	'''
	#       State Update Message
        timestamp = '2017-12-13T03:01:34'
	value = 'STATE_UPDATE'
	message = c.state_update() 
        c.status_message(timestamp,value,message) 	
	'''
	
	#	Perturbation Detection
	timestamp = '2017-12-13T03:02:34'
        value = 'PERTURBATION_DETECTED'
	message = c.perturbation()
	c.status_message(timestamp, value, str(message)) 

	#	Adaptation Started
	timestamp = '2017-12-13T03:02:34'
        value = 'ADAPTATION_STARTED'
        message = 'N/A'
        c.status_message(timestamp, value, message) 

	
        #       Adaptation Completed
        timestamp = '2017-12-13T03:02:34'
        value = 'ADAPTATION_COMPLETED'
        message = 'Parameters learnt are : P1,P2,P3'
        c.status_message(timestamp, value, message) 


        #       Scenario Execution Error Simulation
        timestamp =  '2017-12-13T03:01:34'
        value = 'SCENARIO_FAILURE'
        message = 'Reason for failure (exception information)'
        c.record_error(timestamp,value,message) 

	#       Adaptation Failure Simulation
        timestamp =  '2017-12-13T02:03:45'
        value = 'ADAPTATION_FAILURE'
        message = 'The reason for failure are : F1, F2'
        c.status_message(timestamp,value,message)  

        #       Scenario Completion
        timestamp =  '2017-12-13T05:03:45'
        value = 'SCENARIO_COMPLETED'
        message = 'N/A'
        c.status_message(timestamp,value,message)   


	#	Result
        timestamp =  '2017-12-13T04:03:45'
        value = 'RESULTS'
        message = c.get_reconstructed_file()
        c.done(timestamp,value,message)  

