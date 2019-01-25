import oct2py
import stomp
import time
import datetime
import json
from oct2py import octave as oct
import numpy
from call_octave_API import OctaveAPIs


readings_timestamp = {}
data_list =numpy.zeros((1,13))
data_list_train = []
adapted_surge = 0.0
stop_signal = False
copy_data_list = []
copy_timestamp = 0.0
j = 0
fail_event = 0
copy_data_list = []
copy_timestamp = 0.0
failure_status = numpy.zeros(20)
Rpm_global = 0.0
Ws_global = 0.0


class SampleListener_StopSignal(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    global stop_signal
    y = json.loads(msg)
    readings_stop = y['map']['entry']
    for x in readings_stop['string']:
        if x == 'Simulation over':
            stop_signal = True
            break

class SampleListener_DVL_Adapt(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    global copy_data_list
    global copy_timestamp
    global adapted_surge
    y = json.loads(msg)
    adapted_data = {}
    readings_adapt = y['map']['entry']
    for i in range(len(readings_adapt)):
        if readings_adapt[i]['string'] == 'timestamp':
            #if readings_adapt[i]['long'] == copy_timestamp:
                adapt_val = apio.call_adaptation_api(copy_data_list, data_model_surge,4)
                #print adapt_val
                #adapted_data['altitude'] = copy_data_list[0][6]
                adapted_data['depth'] = copy_data_list[0][8]
                adapted_data['heading'] = copy_data_list[0][9]
                adapted_data['vN'] = copy_data_list[0][1]
                adapted_data['roll'] = copy_data_list[0][7]
                adapted_data['pitch'] = copy_data_list[0][6]
                adapted_data['vE'] = copy_data_list[0][0]
                adapted_data['vU'] = copy_data_list[0][2]
                adapted_data['surge'] = adapt_val[0][0]
                adapted_surge = adapt_val[0][0]
                adapted_data['heave'] = copy_data_list[0][4]
                adapted_data['sway'] = copy_data_list[0][5]
                adapted_data['timestamp'] = copy_timestamp
                adapted_data['vEConf'] = 1
                adapted_data['vNConf'] = 1
                adapted_data['vUConf'] = 1
                adapted_data['vEStdDev'] = 0
                adapted_data['vNStdDev'] = 0
                adapted_data['vUStdDev'] = 0
                adapted_data['surgeConf'] = adapt_val[0][1]
                adapted_data['swayConf'] = 1
                adapted_data['heaveConf'] = 0
                adapted_data['surgeStdDev'] = 0
                adapted_data['swayStdDev'] = 0
                adapted_data['heaveStdDev'] = 0
                adapted_data_json = json.dumps(adapted_data)
                conn_ad.send("/topic/princess.dvl.transformed", adapted_data_json, persistent='false',
                              headers={'transformation': 'jms-map-json'})
                adapted_data.clear()


class SampleListener_DVL(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    #create octave API object
    apio = OctaveAPIs()
    global dvl_var
    global dvl_flag
    global j
    global fail_event
    global copy_data_list
    global copy_timestamp
    global failure_status
    global adapted_surge
    global Rpm_global
    global Ws_global
    dt2 = datetime.datetime.now()
    #print datetime.datetime.now()
    y = json.loads(msg)
    #print y

    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    dt3 = datetime.datetime.now()
    #print datetime.datetime.now()
    reading = {}
    fail_reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['altitude','depth','heading','vN','roll','pitch','vE','vU','surge','heave','sway']:
            #print(readings_list[i]['string'],readings_list[i]['double'])
            reading[readings_list[i]['string']] = readings_list[i]['double']
            dt = datetime.datetime.now()
        if readings_list[i]['string'] == 'timestamp':
            reading[readings_list[i]['string']] = readings_list[i]['long']
            reading['vEConf'] = 1
            reading['vNConf'] = 1
            reading['vUConf'] = 1
            reading['vEStdDev'] = 0
            reading['vNStdDev'] = 0
            reading['vUStdDev'] = 0
            reading['surgeConf'] = 1
            reading['swayConf'] = 1
            reading['heaveConf'] = 1
            reading['surgeStdDev'] = 0
            reading['swayStdDev'] = 0
            reading['heaveStdDev'] = 0
            if adapted_surge > 0:
                reading['surge'] = adapted_surge

    readings_json = json.dumps(reading)
    conn_dvl.send("/topic/princess.dvl.transformed", readings_json, persistent='false',
                  headers={'transformation': 'jms-map-json'})



    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['DVL'] = reading


    #print readings_timestamp[reading['timestamp']]

    #if len(readings_timestamp[reading['timestamp']]) == 3:
    data_list[j][0] = (readings_timestamp[reading['timestamp']]['DVL']['vE'])
    data_list[j][1] = readings_timestamp[reading['timestamp']]['DVL']['vN']
    data_list[j][2] = readings_timestamp[reading['timestamp']]['DVL']['vU']
    data_list[j][3] = readings_timestamp[reading['timestamp']]['DVL']['surge']
    data_list[j][4] = readings_timestamp[reading['timestamp']]['DVL']['heave']
    data_list[j][5] = readings_timestamp[reading['timestamp']]['DVL']['sway']
       #data_list[j][6] = readings_timestamp[reading['timestamp']]['DVL']['altitude']
    data_list[j][6] = readings_timestamp[reading['timestamp']]['DVL']['pitch']
    data_list[j][7] = readings_timestamp[reading['timestamp']]['DVL']['roll']
    data_list[j][8] = readings_timestamp[reading['timestamp']]['DVL']['depth']
    data_list[j][9] = readings_timestamp[reading['timestamp']]['DVL']['heading']
    data_list[j][10] = Rpm_global
    data_list[j][11] = Ws_global

    fail_conf_surge = apio.call_detection_api(data_list, data_model_surge,4,failure_status)
    dt4 = datetime.datetime.now()

       #print datetime.datetime.now()

    #print "Surge_Values" +"\t" +str(data_list[j][3]) + "\t" + str(dt2) + "\t" + str(dt3) +"\t" +str(dt4) +"\t" + str(fail_conf_surge[0][0])

    for i in range(2,len(fail_conf_surge[0])):
         failure_status[i-2] = fail_conf_surge[0][i]

    if(fail_conf_surge[0][0] > 0.5):

       fail_reading['timestamp'] = reading['timestamp']
       fail_reading['dimension']  = "dvl_surge"
       fail_reading['failuretype'] = fail_conf_surge[0][1]
       fail_reading['confidence'] = fail_conf_surge[0][0]
       fail_reading_json = json.dumps(fail_reading)
       copy_data_list = data_list
       copy_timestamp = fail_reading['timestamp']
       conn_dvl.send("/topic/princess.dvl.failure", fail_reading_json, persistent='false',
                     headers={'transformation': 'jms-map-json'})
       fail_reading.clear()
       fail_event = 0



    conn_dvl.send("/topic/princess.adaptation.status", "adaptation completed",persistent='false',headers={'transformation' : 'jms-map-json'})


class SampleListener_RPM(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    global Rpm_global
    y = json.loads(msg)
    apio = OctaveAPIs()
    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['PropellerRpm']:
            #print(readings_list[i]['string'],readings_list[i]['double'])       
            reading[readings_list[i]['string']] = readings_list[i]['double']
	    Rpm_global = readings_list[i]['double']
        if readings_list[i]['string'] == 'timestamp':
            reading['timestamp'] = readings_list[i]['long']



    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['RPM'] = reading
    #Rpm_global =  readings_timestamp[reading['timestamp']]['RPM']

    readings_json=json.dumps(readings_timestamp)

#detection
    user = "admin"
    password = "password"
    host =  "localhost"
    port =  61613

    #connd.send("/topic/princess.sensor.event", readings_json, persistent='false',headers={'transformation' : 'jms-map-json'})

    #training

    conn_rpm.send("/topic/princess.adaptation.status","adaptation completed", persistent='false',headers={'transformation' : 'jms-map-json'})


class SampleListener_Waterspeed(object):
  def on_error(self, headers, message):
    print('received an error "%s"' % message)
  def on_message(self, headers, msg):
    global Ws_global
    #print "WaterSpeed"
    y = json.loads(msg)
    #print y
    #print (y['map']['entry'])
    readings_list = y['map']['entry']
    reading = {}
    for i in range(0,len(readings_list)):
        if readings_list[i]['string'] in ['WaterSpeed']:
            #print(readings_list[i]['string'],readings_list[i]['double'])       
            reading[readings_list[i]['string']] = readings_list[i]['double']
            Ws_global = readings_list[i]['double']
        if readings_list[i]['string'] == 'timestamp':
            reading['timestamp'] = readings_list[i]['long']


    #add readings to dictionary
    if reading['timestamp'] not in readings_timestamp:
        readings_timestamp[reading['timestamp']] = {}
    readings_timestamp[reading['timestamp']]['Waterspeed'] = reading
    #Ws_global = readings_timestamp[reading['timestamp']]['Waterspeed']

    readings_json = json.dumps(readings_timestamp)
    #print readings_json
#detection
    user = "admin"
    password = "password"
    host =  "localhost"
    port =  61613


    #conn_ws.send("/topic/princess.sensor.event",readings_json, persistent='false')

    conn_ws.send("/topic/princess.adaptation.status","adaptation completed", persistent='false',headers={'transformation' : 'jms-map-json'})

    #del(readings_timestamp[reading['timestamp']])

if __name__ == "__main__":

    #Read the detection models
    global data_model_surge
    data_model_surge = numpy.genfromtxt('model_surge.txt')
    data_model_surge = data_model_surge.T
    data_model_surge = numpy.reshape(data_model_surge, (104, 1))

    global data_model_heave
    data_model_heave = numpy.genfromtxt('model_heave.txt')
    data_model_heave = data_model_heave.T
    data_model_heave = numpy.reshape(data_model_heave, (119, 1))

    global data_model_sway
    data_model_sway = numpy.genfromtxt('model_sway.txt')
    data_model_sway = data_model_sway.T
    data_model_sway = numpy.reshape(data_model_sway, (41, 1))

    #RPM Substription
    conn_rpm = stomp.Connection([('localhost', 61613)])
    apio = OctaveAPIs()

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

    #Adaptation Subscription
    conn_ad = stomp.Connection([('localhost', 61613)])

    conn_ad.set_listener('SampleListener_DVL_Adapt', SampleListener_DVL_Adapt())

    conn_ad.start()

    conn_ad.connect()
    conn_ad.subscribe(destination='/topic/princess.dvl.learn', id=1, ack='auto',
                      headers={'transformation': 'jms-map-json'})

    #StopSignal Subscription
    conn_ss = stomp.Connection([('localhost', 61613)])

    conn_ss.set_listener('SampleListener_StopSignal', SampleListener_StopSignal())

    conn_ss.start()

    conn_ss.connect()
    conn_ss.subscribe(destination='/topic/princess.control', id=1, ack='auto', headers={'transformation': 'jms-map-json'})

    print "Final"
    #print readings_timestamp

    #write to a detection queue

    #'''
    user = "admin"
    password = "password"
    host =  "localhost"
    port =  61613
    destination =  ["/topic/CP1.detection"]
    destination = destination[0]


    connd = stomp.Connection(host_and_ports = [(host, port)])
    connd.start()
    connd.connect(login=user,passcode=password)

    while(stop_signal != True):
        time.sleep(1)
    conn_dvl.disconnect()
    conn_rpm.disconnect()
    conn_ws.disconnect()
    conn_ss.disconnect()
    conn_ad.disconnect()
    connd.disconnect()


