#-*- coding: utf-8 -*-

#
# Protocol-level logic.
# Everything in here is part of the TestHarnessClient class.
#

import json
import requests
import time

import enums
import message

# this is no longer used by default
# (to enable it for testing, uncomment its call site)
def fake_initparams():
    #target_type = 'Cprog'
    target_type = 'DSLprog'

    baseline = 'A'
    #baseline = 'A*'
    #baseline = 'B'
    #baseline = 'CHALLENGE'

    # perturbation*16 + architecture
    # for Cprog:
    #    architecture: 1 (arm) or 2 (sparc64)
    #    perturbation: ignored
    # for DSLprog:
    #    architecure: 0 (arm), 1 (powerpc), or 2 (riscv)
    #    perturbation: 0 (invalid), 1-4 (documented elsewhere)
    target = 2*16 + 1
    #target = 2*16 + 0

    if target_type == 'Cprog':
        #contents = 'int main() { return 0; }'
        contents = '1'
    else:
        #contents = 'fnord == 0;\n\nfnord == 0;'
        contents = '1'
    
    return json.dumps({
        'baseline': baseline,
        'target': target,
        'target_type': target_type,
        'contents': contents,
    })


class TestHarnessClient:
    """A class that manages interacting with the test harness over the network.
    """

    #
    # Initialize by storing the host and port.
    #
    # This is the target URL for connecting to the test harness, and
    # it has a trailing slash so we can stuff things on the end of
    # the string.
    #
    def __init__(self, host, port):
        self.host = "http://{0}:{1}/".format(host, port)
        self.target_type = None

        # list of valid message types
        self.message_types = {
            'ready': 'ready',
            'error': 'error',
            'status': 'status',
            'done': 'done',
        }

    #
    # send a message.
    # message_type must be one of the strings in self.message_types;
    # message is the contents, which can be anything that supports to_json().
    #
    def send_message(self, message_type, message=None):
        """POST a message to the test harness, looping until connection is
        successful.
        """

        # cons up the URL (the message type is the path part)
        assert message_type in self.message_types
        endpoint = self.host + self.message_types[message_type]

        # log it
        print_post = message_type.upper()
        if message:
            print_post = print_post +  ': ' + str(message.to_json())
        print(print_post)

        # send it off via http; keep trying until it works
        failures = 0
        while True:
            try:
                if message:
                    return requests.post(endpoint, json=message.to_json())
                else:
                    return requests.post(endpoint)
            except requests.exceptions.RequestException as e:
                print("post failure: ", str(e))
                if failures > 5:
                    print("Can't reach the test harness. Giving up.")
                    exit(1)
                failures += 1
                time.sleep(2)
            finally:
                pass

    # send the READY message
    # returns the raw json of the InitialParams response
    def send_ready(self):
        """Send a READY message to test harness. """

        # no message contents, just send it
        ret = self.send_message('ready')
        # make up the results as requested
        #return fake_initparams()
        return ret.text

    # send the ERROR message
    # error_type must be one of the SutErrorTypes in enums.py
    # log_msg is the string that goes with it
    def send_error(self, error_type, log_msg):
        """Send ERROR message to test harness. """

        assert isinstance(error_type, enums.SutErrorTypes)
        assert isinstance(log_msg, str)

        # cons up the message contents, an ErrorMessage
        err_message = message.ErrorMessage(
            TargetType=self.target_type,
            ErrorType=error_type.value,
            LogMsg=log_msg,
        )
        
        return self.send_message('error', message=err_message)

    # send the STATUS message
    # status_type must be one of the SutStatusTypes in enums.py
    # log_msg is the string to go with it, if any
    def send_status(self, status_type, log_msg=''):
        """Send STATUS message to test harness. """
        
        assert isinstance(status_type, enums.SutStatusTypes)

        # cons up the message contents, a SutStatusMessage
        status_message = message.SutStatusMessage(
            TargetType=self.target_type,
            StatusType=status_type.value,
            LogMsg=log_msg,
        )

        # stash the most recent status in /cp2/STATUS
        # write out the json blob so sending it requires no further work
        # if for some reason this doesn't work, don't crash
        text = status_message.to_json()
        try:
            f = open("/cp2/STATUS", 'w')
            f.write(text)
            f.close()
        except Exception as e:
            pass

        return self.send_message('status', message=status_message)

    # send the FINISHED message
    # result must be a suitable dictionary (map)
    # (what goes in this?)
    # log_msg is any accompaying text
    def send_finished_status(self, result, log_msg=''):
        """Send FINISHED message to test harness. """

        assert isinstance(result, str)

        # cons up the message contents, a SutFinishedStatusMessage
        finished_message = message.SutFinishedStatusMessage(
            TargetType=self.target_type,
            Result=result,
            LogMsg=log_msg,
        )
        
        return self.send_message('done', message=finished_message)
