# -*- coding: utf-8 -*-

#
# base class for the SUT
# (there are two kinds of this, found in target/, one for the
# toolchain and one for the synthesis)
#
# it has two methods: validate_init_contents, which is supposed to
# check the initial params, and run, that does everything else.
#
# validate_init_contents is not actually called from outside target/
# so it doesn't really need to be part of the base class at this point...
#

import message
import enums
import th_client


class SUT(object):
    """A base class to implement CP2 Systems-Under-Test (SUT). 
    
    Subclass this to implement SUT harnesses for toolchain and OS synthesizer.
    """

    def __init__(self, th_client):
        self.th_client = th_client
	
    def validate_init_contents(self, initparams):
        raise NotImplementedError()

    def run(self, initparams):
        raise NotImplementedError()
