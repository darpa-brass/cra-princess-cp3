# -*- coding: utf-8 -*-

#
# The kinds of messages we have.
#
# These are python encodings of the messages we can pass around on our
# end; they get converted to (or from) json for transport.
#

import json

from enums import *

from jsonobject import JsonObject, StringProperty, DictProperty, IntegerProperty
from jsonobject.base_properties import AssertTypeProperty


#
# This is a thing that uses python reflection goo to convert instances
# of the enums from enums.py to and from strings.
#
class EnumProperty(AssertTypeProperty):
    """A jsonobject property that serializes/deserializes enum.Enum types into
    strings.
    """

    _type = str

    def __init__(self, enum_cls, *args, **kwargs):
        self.enum_cls = enum_cls
        return super(EnumProperty, self).__init__(*args, **kwargs)

    def _wrap(self, obj):
        return self.enum_cls(obj)

    def _unwrap(self, obj):
        return self._wrap(obj), obj


#
# InitialParams (from them to us, in response to READY)
#    
class InitialParamsMessage(JsonObject):
    """InitialParams message sent in success response to READY. """

    Baseline = EnumProperty(InitBaselineTypes)
    Target = IntegerProperty()
    TargetType = EnumProperty(SutTargetTypes)
    Contents = StringProperty()

#
# ErrorMessage (from us to them, when something goes wrong)
#
class ErrorMessage(JsonObject):
    """ErrorMsg message sent to test harness upon error. """

    TargetType = EnumProperty(SutTargetTypes)
    ErrorType = EnumProperty(SutErrorTypes)
    LogMsg = StringProperty()


#
# SutStatusMessage (from us to them, while we're running)
#
class SutStatusMessage(JsonObject):
    """SutStatus message sent to test harness indicating SUT system status. """

    TargetType = EnumProperty(SutTargetTypes)
    StatusType = EnumProperty(SutStatusTypes)
    LogMsg = StringProperty()


#
# SutFinishedStatusMessage (from us to them, when we're done)
#
class SutFinishedStatusMessage(JsonObject):
    """SutFinishedStatus message sent to test harness with test outcome. """

    TargetType = StringProperty()
    Result = StringProperty(str)
    LogMsg = StringProperty(str)
