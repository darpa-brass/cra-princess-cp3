#-*- coding: utf-8 -*-

#
# Listener for the send-to-us part of the interaction protocol.
#

import os
import json
import requests
from flask import Flask

import support
import message
import sut


status_types = message.SutStatusTypes
error_types = message.SutErrorTypes


# XXX set this for real somehow
listener_target_type = "Cprog"

app = Flask(__name__)

def reject():
    message = message.ErrorMessage(
        TargetType=listener_target_type,
        ErrorType=error_types.DISALLOWED_OPERATION.value,
        LogMsg="",
    )
    json = message.to_json()
    return json

def sendstatus():
    try:
        f = open("/cp2/STATUS", 'r')
        text = support.readall(f)
        f.close()
        return text
    except Exception as e:
        # this is the best match I can see of the allowed errors
        reject(str(e))

@app.route("/alive", methods=["POST"])
def alive():
   return sendstatus()

@app.route("/query", methods=["POST"])
def query():
   return sendstatus()

@app.route("/perturb", methods=["POST"])
def perturb():
   return reject("invalid /perturb")

@app.route("/enable", methods=["POST"])
def enable():
   return reject("invalid /enable")

@app.route("/disable", methods=["POST"])
def disable():
   return reject("invalid /disable")


def startme():
    pid = os.fork()
    if pid == 0:
        # child
        app.run(port=5555)
        os._exit(0)

