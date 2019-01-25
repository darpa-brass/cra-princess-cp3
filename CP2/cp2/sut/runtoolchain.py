# -*- coding: utf-8 -*-

# XXX temporary
import os

import message
import sut
import subproc
import support

spawn = subproc.spawn

baseline_types = message.InitBaselineTypes
status_types = message.SutStatusTypes
error_types = message.SutErrorTypes

# XXX: this list is not finalized.
# note that the last target is intentionally one that doesn't work.
# also we said in one place that the targets should be 0..ntargets-1
# and later on that they should be 1, 2, 3, ... and 99 for invalid.
# the former's what's in the offficial doc though.
known_targets = {
    0: "invalid",	# Rejected at this level
    1: "arm",		# To be supported
    2: "sparc64",	# To be supported
    #3: "mips",		# behavior unspecified: unsupported; active for testing
    3: "invalid",	# behavior unspecified
    4: "invalid",	# behavior unspecified
    5: "invalid",	# behavior unspecified
    6: "invalid",	# behavior unspecified
    7: "invalid",	# behavior unspecified
    8: "invalid",	# behavior unspecified
    9: "invalid",	# behavior unspecified
    10: "invalid",	# behavior unspecified
    11: "invalid",	# behavior unspecified
    12: "invalid",	# behavior unspecified
    13: "vax",		# No description in bintools
    14: "broken",	# Description in bintools is invalid
    15: "nocross",	# No cross compiler installed
}
TARGET_MODULUS = 16

class ToolchainSUT(sut.SUT):

    #
    # The InitialParams response to us contains:
    #    Baseline (one of the values from enums.InitBaselineTypes)
    #    Target (64-bit integer)
    #    TargetType (if we're here, it's "Cprog")
    #    Contents (contents of the C file to be tested)
    #
    # It seems that e.g. "TargetType" is a json thing whose value ends up
    # as "target_type". Too much magic...
    #
    def validate_init_contents(self, initparams):
        assert (initparams.TargetType == "Cprog")
        #
        # XXX we're getting strings not enum values; not sure if this is
        # expected or because the dummy InitParams is wrong.
        #
        if initparams.Baseline == baseline_types.A:
            baseline = initparams.baseline
        elif initparams.Baseline == "A":
            baseline = baseline_types.A
        elif initparams.Baseline == baseline_types.Astar:
            baseline = initparams.baseline
        elif initparams.Baseline == "A*":
            baseline = baseline_types.Astar
        elif (initparams.Baseline == baseline_types.B or
             initparams.Baseline == "B"):
            self.th_client.send_error(error_types.BAD_FILE,
                "Baseline B is not valid for target_type == Cprog")
            exit(1)
        elif initparams.Baseline == baseline_types.CHALLENGE:
            baseline = initparams.Baseline
        elif initparams.Baseline == "CHALLENGE":
            baseline = baseline_types.CHALLENGE
        else:
            msg = "Invalid value of Baseline ({}) in InitialParams".format(initparams.Baseline)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)
        self.baseline = baseline
        target = int(initparams.Target) % TARGET_MODULUS
        self.targetname = known_targets[target]
        (self.testfiletext, testfilenum) = support.mightbefile(initparams.Contents, "/cp2/corpus/t{:05}.c")
        if self.testfiletext is None:
            msg = "Invalid Contents ({}) in InitialParams".format(initparams.Contents)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)

        print("Cprog: baseline is {}".format(self.baseline))
        print("Cprog: target (machine) is {}".format(self.targetname))
        if testfilenum is not None:
            print("Cprog: test file {}".format(testfilenum))
        print("Cprog: first three lines of test file:")
        tmp = "".join((self.testfiletext.splitlines(keepends=True))[0:3])
        print("   ------")
        print("{}".format(tmp))
        print("   ------")

        if self.targetname == "invalid":
            msg = "Selected target ({}) is not valid".format(target)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)

    def build_toolchain(self):
        return spawn(["sh", "/cp2/toolchain/adapt-build.sh", self.targetname])

    def install_toolchain(self):
        return spawn(["sh", "/cp2/toolchain/adapt-install.sh", self.targetname])

    def write_contents(self):
        spawn(["sh", "/cp2/toolchain/test-mkworkarea.sh"])
        file = open("/cp2/toolchain/work/test.c", 'w')
        file.write(self.testfiletext)
        file.close()

    def compile_program(self):
        if self.baseline == baseline_types.A:
            log = spawn(["sh", "/cp2/toolchain/test-compile.sh", "A", self.targetname])
        elif self.baseline == baseline_types.Astar:
            log = spawn(["sh", "/cp2/toolchain/test-compile.sh", "Ax", self.targetname])
        else:
            assert(self.baseline == baseline_types.CHALLENGE)
            log = spawn(["sh", "/cp2/toolchain/test-compile.sh", "C", self.targetname])
        # make sure we actually got something
        try:
            tmp = open("/cp2/toolchain/work/test", 'r')
            tmp.close()
        except FileNotFoundError as e:
            msg = "Compile script succeeded, " + \
                  "but output program was not created\n" + \
                  "Full output:\n" + \
                  log
            raise Exception(msg)
        except Exception as e:
            raise
        
        return log

    def run_program(self):
        if self.baseline == baseline_types.A:
            log = spawn(["/cp2/toolchain/work/test"])
        else:
            log = spawn(["sh", "/cp2/toolchain/test-run.sh", self.targetname, "/cp2/toolchain/work/test"])
        # return the program's output
        return log

    def run(self, initparams):

        self.validate_init_contents(initparams)
        
        # 1.CP2 will send a STATUS message with “type “PERTURBING SYSTEM”.
        self.th_client.send_status(status_types.PERTURBING_SYSTEM)

        # 2.Based on the target value, CP2 will select one of the supported
        # architectures, and send a STATUS message with “type” “SYSTEM
        # PERTURBED”.
        self.th_client.send_status(status_types.SYSTEM_PERTURBED)

        # 3.CP2 will send a STATUS message with “type” “BUILDING SYSTEM”.
        self.th_client.send_status(status_types.BUILDING_SYSTEM)

        # 4.CP2 will build a toolchain for the selected architecture. If this
        # build fails, CP2 will send an ERROR, with “ErrorType” of “TOOL BUILD
        # FAILED” and terminate.
        try:
            log = self.build_toolchain()
        except Exception as e:
            self.th_client.send_error(error_types.TOOL_BUILD_FAILED, str(e))
            exit(1)

        # 5.Upon successful completion of the build, CP2 will send a STATUS
        # message with “type” “SYSTEM BUILT”
        self.th_client.send_status(status_types.SYSTEM_BUILT, log)

        # 6.CP2 will then install the newly built toolchain on the target VM. On
        # error, CP2 will send an ERROR message with ErrorType “INSTALL FAILED”
        # and terminate.
        try:
            log = self.install_toolchain()
        except Exception as e:
            self.th_client.send_error(error_types.INSTALL_FAILED, str(e))
            exit(1)

        # 7.CP2 will write “Contents” to the target VM file system and then
        # send a STATUS message with “type” of “COMPILING PROGRAM”.
        try:
            self.write_contents()
        except Exception as e:
            # we couldn't write the file out (derp?) so make like a compile
            # error.
            msg = "Could not write out test program:\n" + str(e)
            self.th_client.send_status(status_types.COMPILING_PROGRAM)
            self.th_client.send_error(error_types.PROG_BUILD_FAILED, msg)
            exit(1)
        self.th_client.send_status(status_types.COMPILING_PROGRAM, log)

        # 8.CP2 will then compile, assemble, link, and run the program specified
        # in “Contents.” On error, CP2 will send an ERROR message with “ErrorType”
        # of “PROGRAM BUILD FAILED” and terminate.
        try:
            log = self.compile_program()
        except Exception as e:
            self.th_client.send_error(error_types.PROG_BUILD_FAILED, str(e))
            exit(1)

        # 9.CP2 will send a STATUS message with “type” of “RUNNING PROGRAM.”
        # On error, CP2 will send ERROR message with ErrorType “CPROG FAILED” and
        # terminate.
        self.th_client.send_status(status_types.RUNNING_PROGRAM, log)
        try:
            result = self.run_program()

            # 10. CP2 will send a DONE message with “Result” set to the output
            # of the program specified in “Contents”.
            self.th_client.send_finished_status(result)

        except Exception as e:
            self.th_client.send_error(error_types.CPROG_FAILED, str(e))
            exit(1)
