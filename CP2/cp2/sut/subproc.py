#-*- coding: utf-8 -*-

import subprocess

#
# Process spawning logic.
#
# Provides: spawn, which runs a subprocess and throws an exception
# if it fails (exits nonzero, signals).
#
# args should be a list, where the first element is both argv[0] and the
# path to the command.
#
# The return value is the captured stdout/stderr.
#

def spawn(args):
    print("running: ", args)
    result = subprocess.run(args, shell=False, check=False,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
    			    universal_newlines=True)
    #
    # If we tell subprocess.run to check for failure, the exception
    # it throws doesn't print the full output, and we want to send that
    # back.
    #
    if result.returncode != 0:
        message = "Command " + str(args) + " exited with code " + \
        		str(result.returncode) + "\n" + \
                        "Full output:\n" + \
                        result.stdout # includes stderr
        raise Exception(message)
    return result.stdout
