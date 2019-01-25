# -*- coding: utf-8 -*-

from enum import Enum

#
# The kind of test run: Baseline A, Baseline B, or Challenge.
#
class InitBaselineTypes(Enum):
    A = "A"
    Astar = "A*"
    B = "B"
    CHALLENGE = "Challenge"


#
# Which side of the house we're on.
#
class SutTargetTypes(Enum):
    CPROG = "Cprog"
    DSLPROG = "DSLprog"


#
# The possible error codes.
#
class SutErrorTypes(Enum):
    BAD_FILE = "BADFILE"
    TOOL_BUILD_FAILED = "TOOL BUILD FAILED"
    INSTALL_FAILED = "INSTALL FAILED"
    PROG_BUILD_FAILED = "PROGRAM BUILD FAILED"
    SYSTEM_BUILD_FAILED = "SYSTEM BUILD FAILED"
    VERIFICATION_FAILED = "VERIFICATION FAILED"
    CPROG_FAILED = "CPROG FAILED"
    SYNTH_FAILED = "SYNTHESIS FAILED"
    DISALLOWED_OPERATION = "DISALLOWED_OPERATION"


#
# The allowable status responses.
#
class SutStatusTypes(Enum):
    PERTURBING_SYSTEM = "PERTURBING SYSTEM"
    SYSTEM_PERTURBED = "SYSTEM PERTURBED"
    BUILDING_SYSTEM = "BUILDING SYSTEM"
    SYSTEM_BUILT = "SYSTEM BUILT"
    COMPILING_PROGRAM = "COMPILING PROGRAM"
    RUNNING_PROGRAM = "RUNNING PROGRAM"
    RUNNING_KEEPALIVE = "RUNNING KEEPALIVE"
    VERIFYING_SYSTEM = "VERIFYING SYSTEM"
    VERIFICATION_KEEPALIVE = "VERIFICATION KEEPALIVE"
