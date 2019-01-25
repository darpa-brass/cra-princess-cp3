import stomp
import time
import json
import datetime
from call_octave_API import OctaveAPIs

 
#f = open('simulator_data_with_pert2.txt',"ab")
#f = open('simulator_data_with_pert.txt',"ab")
#f = open('simulator_data_with_pert2.txt',"ab")
#f = open('dvl_experiment_ex_yuan_updated_1.txt',"ab")
f = open('simulator_data_with_pert_forTesting4.txt',"ab")
readings_timestamp = {}
j = 0

class SampleListener_DVL(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    #create octave API object
    apio = OctaveAPIs()
    global j
    y = json.loads(msg)
    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['altitude','depth','heading','vN','roll','pitch','vE','vU','surge','heave','sway']:        
            #print(readings_list[i]['string'],readings_list[i]['double'])       
            reading[readings_list[i]['string']] = readings_list[i]['double']
        if readings_list[i]['string'] == 'timestamp':
            reading['timestamp'] = readings_list[i]['long']
    
    
    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['DVL'] = reading
    if len(readings_timestamp[reading['timestamp']]) == 3:
	#print readings_timestamp[reading['timestamp']]['DVL']['depth']
        #print (str(readings_timestamp[reading['timestamp']]['DVL']['altitude']) + " " + str(readings_timestamp[reading['timestamp']]['DVL']['heading']))
        f.write(str(readings_timestamp[reading['timestamp']]['DVL']['altitude']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vE']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vN']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['pitch']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['roll']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['depth']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vU']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['surge']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['heave']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['sway']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['heading']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['RPM']['PropellerRpm']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['Waterspeed']['WaterSpeed']) +
                "\n")
	print readings_timestamp[reading['timestamp']]['DVL']['heading']
	j+=1
        if j == 100:
            #command_reading = {}
            command_reading ='depthTarget'
	    command_reading+=':='
            command_reading+="25.0"
	    command_reading+=','
            command_reading+='speedTarget'
            command_reading+=':='
	    command_reading+= "4.0"
            command_reading+=','
            command_reading+= 'headingTarget'
	    command_reading+=':='
	    command_reading+= "180.0"

            #conn_dvl.send("/topic/princess.vehicle.command", command_reading, persistent='false',headers={'transformation': 'jms-map-json'})
            #print command_reading
	    #print type(command_reading)


        #del(readings_timestamp[reading['timestamp']])

    #print ({'dvl' :reading})

class SampleListener_RPM(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    y = json.loads(msg)
    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['PropellerRpm']:
            #print(readings_list[i]['string'],readings_list[i]['double'])       
            reading[readings_list[i]['string']] = readings_list[i]['double']
        if readings_list[i]['string'] == 'timestamp':
            reading['timestamp'] = readings_list[i]['long']


    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['RPM'] = reading
    if len(readings_timestamp[reading['timestamp']]) == 3:
        #print (readings_timestamp[reading['timestamp']]['DVL']['altitude'])
        f.write(str(readings_timestamp[reading['timestamp']]['DVL']['altitude']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vE']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vN']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['pitch']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['roll']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['depth']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vU']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['surge']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['heave']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['sway']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['heading']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['RPM']['PropellerRpm']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['Waterspeed']['WaterSpeed']) +
                "\n")

        #del(readings_timestamp[reading['timestamp']])
    #print ({'rpm' :reading})

class SampleListener_Waterspeed(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    y = json.loads(msg)
    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['WaterSpeed']:
            #print(readings_list[i]['string'],readings_list[i]['double'])       
            reading[readings_list[i]['string']] = readings_list[i]['double']
        if readings_list[i]['string'] == 'timestamp':
            reading['timestamp'] = readings_list[i]['long']


    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['Waterspeed'] = reading
    if len(readings_timestamp[reading['timestamp']]) == 3:
        #print (readings_timestamp[reading['timestamp']]['DVL']['altitude'])
        f.write(str(readings_timestamp[reading['timestamp']]['DVL']['altitude']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vE']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vN']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['pitch']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['roll']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['depth']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['vU']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['surge']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['heave']) + "\t" +
		str(readings_timestamp[reading['timestamp']]['DVL']['sway']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['DVL']['heading']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['RPM']['PropellerRpm']) + "\t" +
                str(readings_timestamp[reading['timestamp']]['Waterspeed']['WaterSpeed']) +
                "\n")
        #print(readings_timestamp)

        #del(readings_timestamp[reading['timestamp']])


    #print ({'waterSpped' :reading})



#RPM Substription
conn_rpm = stomp.Connection([('localhost', 61613)])

conn_rpm.set_listener('SampleListener_RPM', SampleListener_RPM())

conn_rpm.start()

conn_rpm.connect()
conn_rpm.subscribe(destination='/topic/princess.rpm', id=1, ack='auto', headers={'transformation': 'jms-map-json'})


#DVL Subscription
conn_dvl = stomp.Connection([('localhost', 61613)])
 
conn_dvl.set_listener('SampleListener_DVL', SampleListener_DVL())
 
conn_dvl.start()
 
conn_dvl.connect() 
conn_dvl.subscribe(destination='/topic/princess.dvl', id=1, ack='auto', headers={'transformation': 'jms-map-json'})


#waterspeed Subscription

conn_ws = stomp.Connection([('localhost', 61613)])

conn_ws.set_listener('SampleListener_Waterspeed', SampleListener_Waterspeed())

conn_ws.start()

conn_ws.connect()
conn_ws.subscribe(destination='/topic/princess.waterspeed', id=1, ack='auto', headers={'transformation': 'jms-map-json'})

#write to a detection queue

'''
user = "admin"
password = "password"
host =  "localhost"
port =  61613
destination =  ["/topic/CP1.detection"]
destination = destination[0]


connd = stomp.Connection(host_and_ports = [(host, port)])
connd.start()
connd.connect(login=user,passcode=password)

'''

time.sleep(2500)
conn_dvl.disconnect()
conn_rpm.disconnect()
conn_ws.disconnect()
f.close()

9840443707
