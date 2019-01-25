import json
import datetime
import argparse
import requests
import random
import urllib2
import logging

class TestHarnessAdapter:
	LOG_FILENAME = 'TestHarnessAdapter'
	ERROR_URL_ENDPOINT = "/error"
	READY_URL_ENDPOINT = "/ready"
	STATUS_URL_ENDPOINT = "/status"
	DONE_URL_ENDPOINT = "/done"
	PATH_URL_ENDPOINT = "/path"
	URL = ""
	def __init__(self):
		LOG_FILENAME = 'TestHarnessAdapter'
		logging.basicConfig(filename= LOG_FILENAME ,level=logging.DEBUG)
		f = open('princess.properties','r')
		u = f.readline()
		url = u[10:len(u)-1]
		self.URL = url
	'''
	* Notification by the DAS that an error occurred during startup or processing of test-specific information
      
	@param errorType type of error being reported
	@param errorMessage free text of arbitrary length with error details
	@throws IOException error
	'''
		
	def sendErrorMessage(self,errorType, errorMessage):
		try:
			timestamp = datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S')
			logging.debug("Sending ERROR message: " + errorType + ": " + str(errorMessage))
		
			f = requests.post(self.URL+ self.ERROR_URL_ENDPOINT, headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp , 'Error': errorType, 'Message': errorMessage}))
		except IOError:
			print 'An IO Exception Occured'
			logging.debug("An IO Exception Occurred while Sending ERROR message: " + errorType + ": " + str(errorMessage))

	'''
	* Notification by the DAS that it has received and processed any test-specific information and
	* that the target system is launched, configured, and ready to process test inputs
	'''
	def sendReadyMessage(self):
		try:
			timestamp = datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S')

			logging.debug("Sending READY message")

			f = requests.post(self.URL+ self.READY_URL_ENDPOINT, headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp}))
			return f.content
		except IOError:
			logging.debug("An IO Exception occured while sending READY Message")
			return 'An IO Exception Occured'
	'''
	CP1 Done Message
	'''
	def sendDoneMessage(self,results):
		try:
			timestamp = datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S')
			
			logging.debug("Sending CP1 Done Message")
		
			f = requests.post(self.URL+ self.DONE_URL_ENDPOINT, headers={'Content-Type': 'application/json'}, data=json.dumps(results))
		except IOError:
			logging.debug("An IO Exception occured while sending DONE Meesage")
	
			

	'''
	Notification by the DAS of a change in status, typically associated with the occurrence of
	a test event that identifies a discrete phase of test execution

	@param statusType type of status being reported
	@param statusMessage free text of arbitrary length with status details
	@throws IOException error
	'''
	def sendStatusMessage(self, statusType, statusMessage):
		try:
			timestamp = datetime.datetime.today().strftime('%Y-%m-%dT%H:%M:%S')

			logging.debug("Sending STATUS message: " + statusType + ": " + str(statusMessage))
		
			f = requests.post(self.URL+ self.STATUS_URL_ENDPOINT, headers={'Content-Type': 'application/json'}, data=json.dumps({'Timestamp': timestamp , 'Status': statusType, 'Message': statusMessage}))
		except IOError:
			print 'AN IO Exception Occured'
			logging.debug("An IO Exception Occured while sending STATUS message:"+ statusType + " : "+ str(statusMessage))


'''
	Testing TestHarnessAdapter
'''

'''
t = TestHarnessAdapter() 
t.sendErrorMessage('hi','hello')
print t.sendReadyMessage()
t.sendStatusMessage('why','where')
t.sendDoneMessage({'1': '11','2':'22'})
'''
