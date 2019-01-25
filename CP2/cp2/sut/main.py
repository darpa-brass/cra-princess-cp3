# -*- coding: utf-8 -*-

#
# Main: top level of SUT logic.
#
# This module takes care of (a) setup based on commandline args, and
# (b) sending the READY message to the other side, getting the result
# back, interpreting it, and dispatching to either the toolchain or
# synthesis part of things.
#

import argparse
import json

import runsynthesis, runtoolchain
import enums
import message
import th_client as th
import listener
import keepalive

#
# The initial parameters message is supposed to have mixed-case field
# names (Baseline, TargetType) but for legacy reasons they may come
# in with lowercase and underscores.
#
# The json decoder always creates the mixed-case fields (they are
# declared in message.py, which makes this happen) but the lower-case
# fields will only appear if they came in the message.
#
# So the way this mess manifests after json decoding is that if we got
# a legacy-form message both sets of fields are present but the
# mixed-case fields are None.
#
# So, for each of the fields, if the mixed-case field is None and the
# lower-case field is present, set the mixed-case field to the value
# from the lower-case field and clear the lower-case field.
#
# ...furthermore Target is supposed to be an int, but we're getting
# strings from the LL test harness, so clean that up (assigning
# from "target" to "Target" checks that in the message object and
# barfs otherwise)
#
def fix_params(params):
    if "target" in params and type(params["target"]) != type(12345):
        params["target"] = int(params["target"])

    def fix_field(f, F):
        if f in params and params[F] is None:
            params[F] = params[f]
            del params[f]
    fix_field("baseline", "Baseline")
    fix_field("target", "Target")
    fix_field("target_type", "TargetType")
    fix_field("contents", "Contents")
    return params

#
# Send READY to the test harness client, decode the results, pick
# the SUT class to use, and create/return an instance.
#
# XXX: because currently the harness doesn't send us the initial
# parameters, send down a flag that says what kind of parameters
# to make up and return.
#
def initialize_sut(th_client):
    """Send /ready message and parse SUT initialParams from response. """

    #
    # send READY
    #

    # send ready and get the initial parameters
    init_params_raw  = th_client.send_ready()

    # decode the initial parameters
    init_params_decoded = json.loads(init_params_raw)
    init_params = message.InitialParamsMessage(init_params_decoded)
    init_params = fix_params(init_params)
    # let test-harness client know about target type to stick into messages
    th_client.target_type = init_params.TargetType

    # pick a SUT object
    if init_params.TargetType == 'DSLprog':
        sut = runsynthesis.OSSynthesizerSUT(th_client)
    elif init_params.TargetType == 'Cprog':
        sut = runtoolchain.ToolchainSUT(th_client)
    else:
        msg = 'unknown target type: {}'.format(init_params.TargetType)
        th_client.send_error(enums.SutErrorTypes.BAD_FILE, msg)
        raise Exception(msg)
    return (sut, init_params)

#
# get the arguments:
#    --host hostname		hostname to contact the LL code at
#    --port portnum		port number to contact the LL code at
#
# These are not set by the docker arrangements so the default gets used.
# (which is localhost:9870)
#
def parse_args():
    """Get test-harness server host/port from CLI arguments. """

    parser = argparse.ArgumentParser(description='run Harvard-PRINCESS CP2 SUT')
    parser.add_argument('-hh', '--host', type=str, help='test harness server host',
            default='localhost')
    parser.add_argument('-hp', '--port', type=int, help='test harness server port',
            default=9870)
    return parser.parse_args()

#
# Top top level.
# Get the args, make a test harness client object, and use it as the
# connection to initialize a SUT object.
#
# XXX: currently because the test harness doesn't send us our initial
# parameters, we make them up, and in particular do it twice so we can
# test both sides of the house.
#
def main():
    """Run the SUT (System Under Test). """

    args = parse_args()
    th_client = th.TestHarnessClient(args.host, args.port)

    keepalive.setup(args.host, args.port)
    listener.startme()

    (sut, initparams) = initialize_sut(th_client)
    sut.run(initparams)


if __name__ == '__main__':
    main()
