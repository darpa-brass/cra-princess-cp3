import os
import time
import json
import requests
from flask import Flask

import support
import message
import th_client as th

INTERVAL=10

status_types = message.SutStatusTypes

g_host = None
g_port = None

#def sendstatus():
#    try:
#        f = open("/cp2/STATUS", 'r')
#        text = support.readall(f)
#        f.close()
#        return text

def run(statustype):
    th_client = th.TestHarnessClient(g_host, g_port)
    th_client.target_type = "DSLprog"
    while True:
        time.sleep(INTERVAL)
        th_client.send_status(statustype, log_msg="keepalive on autopilot sorry")
            

def startme(statustype):
    pid = os.fork()
    if pid == 0:
        # child
        run(statustype)
        os._exit(0)
    return pid

def setup(host, port):
    global g_host, g_port
    g_host = host
    g_port = port
