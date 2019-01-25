# -*- coding: utf-8 -*-
import os

import message
import sut
import subproc
import support
import keepalive

spawn = subproc.spawn

baseline_types = message.InitBaselineTypes
status_types = message.SutStatusTypes
error_types = message.SutErrorTypes

known_targets = {
    0: "armv7-a",	# 32-bit arm (to be supported)
    1: "x86_64",	# 64-bit x86 (to be supported)
    2: "invalid",	# behavior unspecified
    #2: "riscv-32e",	# 32-bit riscv (rv32e) (not supported)
    3: "invalid",	# behavior unspecified
    #3: "powerpc",	# 32-bit powerpc (not supported)
    4: "invalid",	# behavior unspecified
    5: "invalid",	# behavior unspecified
    6: "invalid",	# behavior unspecified
    7: "invalid",	# behavior unspecified
    8: "invalid",	# behavior unspecified
    9: "invalid",	# behavior unspecified
    10: "invalid",	# behavior unspecified
    11: "invalid",	# behavior unspecified
    12: "invalid",	# behavior unspecified
    13: "invalid",	# behavior unspecified
    14: "invalid",	# behavior unspecified
    15: "invalid",	# behavior unspecified
}
TARGET_MODULUS = 16

class OSSynthesizerSUT(sut.SUT):

    #
    # The InitialParams response to us contains:
    #    Baseline (one of the values from enums.InitBaselineTypes)
    #    Target (64-bit integer)
    #    TargetType (if we're here, it's "DSLprog")
    #    Contents (contents of the C file to be tested)
    #
    # It seems that e.g. "TargetType" is a json thing whose value ends up
    # as "target_type". Too much magic...
    #
    def validate_init_contents(self, initparams):
        assert (initparams.TargetType == "DSLprog")
        #
        # XXX we're getting strings not enum values; not sure if this is
        # expected or because the dummy InitParams is wrong.
        #
        if initparams.Baseline == baseline_types.A:
            baseline = initparams.Baseline
        elif initparams.Baseline == "A":
            baseline = baseline_types.A
        elif (initparams.Baseline == baseline_types.Astar or
             initparams.Baseline == "A*"):
            self.th_client.send_error(error_types.BAD_FILE,
                "Baseline A* is not valid for target_type == DSLprog")
            exit(1)
        elif initparams.Baseline == baseline_types.B:
            baseline = initparams.baseline
        elif initparams.Baseline == "B":
            baseline = baseline_types.B
        elif initparams.Baseline == baseline_types.CHALLENGE:
            baseline = initparams.baseline
        elif initparams.Baseline == "CHALLENGE":
            baseline = baseline_types.CHALLENGE
        else:
            msg = "Invalid value of Baseline ({}) in InitialParams".format(initparams.Baseline)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)
        self.baseline = baseline
        target = int(initparams.Target) % TARGET_MODULUS
        self.targetname = known_targets[target]
        self.perturbation = int(initparams.Target) // TARGET_MODULUS
        self.perturbationstr = str(self.perturbation)
        self.target = initparams.Target

        if self.perturbation < 0 or self.perturbation > 4:
            msg = "Invalid perturbation ({}) in InitialParams".format(self.perturbation)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)

        #
        # Because there are now two files (the spec, and the handwritten
        # .prog file, which is per-architecture) don't use support.mightbefile.
        # Instead, if it's a number, read both files, and if it's not,
        # take the first two lines as the spec, and require the rest to be
        # a handwritten .prog for the current architecture.
        #
        snippetnum = support.trynumber(initparams.Contents)
        if snippetnum is not None:
            specpath = "/cp2/snippets/spec{:02}.ale".format(snippetnum)
            progpath = "/cp2/snippets/native{:02}-{}-{}.prog".format(snippetnum, self.targetname, self.perturbation)
            self.spectext = support.readfile(specpath)
            self.progtext = support.readfile(progpath)
        else:
            lines = initparams.Contents.splitlines(keepends=True)
            self.spectext = lines[0] + lines[1]
            self.progtext = "".join(lines[2:])
        #(self.snippettext, _) = support.mightbefile(initparams.Contents, "/cp2/snippets/snip{:02}.ale")
        if self.spectext is None:
            msg = "Invalid Contents value ({}) in InitialParams: no specification by that number".format(initparams.Contents)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)
        if self.progtext is None:
            msg = "Invalid Contents value ({}) in InitialParams: no native/handwritten version".format(initparams.Contents)
            self.th_client.send_error(error_types.BAD_FILE, msg)
            exit(1)

        print("DSLprog: baseline is {}".format(self.baseline))
        print("DSLprog: target (machine) is {}".format(self.targetname))
        print("DSLprog: perturbation is {}".format(self.perturbation))
        print("DSLprog: code snippet spec:")
        print("   ------")
        print("{}".format(self.spectext))
        print("   ------")
        print("DSLprog: code snippet native handwritten version:")
        print("   ------")
        print("{}".format(self.progtext))
        print("   ------")
        f = open("/cp2/synth/test.ale", "w")
        f.write(self.spectext)
        f.close()
        f = open("/cp2/synth/native.prog", "w")
        f.write(self.progtext)
        f.close()

    def perturb_architecture(self):
        log = spawn(["sh", "/cp2/synth/runale.sh", self.targetname, self.perturbationstr])
        return log

    def generate_os_snippet(self):
        if self.baseline == baseline_types.A:
            # For baseline A we're supposed to just verify the handwritten
            # snippet. I think this means that the result text is the
            # snippet native text. XXX: is this correct? (dholland)
            return (self.progtext, None)
        elif self.baseline == baseline_types.B:
            # For baseline B, we're supposed to generate an empty statement
            # and then try to verify it; this is supposed to fail.
            return ("\n", None)
        else:
            assert(self.baseline == baseline_types.CHALLENGE)
            #if self.perturbation == 0:
            #    # XXX: this should happen as a result of perturb.sh making
            #    # intentionally invalid changes.
            #    raise Exception("Invalid architecture description")

            kapid = keepalive.startme(status_types.RUNNING_KEEPALIVE)
            log = spawn(["sh", "/cp2/synth/dosynth.sh",
                         self.targetname, self.perturbationstr])
            os.kill(kapid, 15);
            f = open("/cp2/synth/test.output", 'r')
            code = support.readall(f)
            f.close()
            # return the synthesized code and also the log
            return (code, log)

    def verify_code_snippet(self, code):
        f = open("/cp2/synth/verify.prog", "w")
        f.write(code)
        f.close()
        kapid = keepalive.startme(status_types.VERIFICATION_KEEPALIVE)
        log = spawn(["sh", "/cp2/synth/doverify.sh",
                     self.targetname, self.perturbationstr])
        os.kill(kapid, 15)
        # if it succeeded, read the result out
        f = open("/cp2/synth/verify.result", "r")
        verdict = support.readall(f)
        f.close()
        return (verdict, log)

    def run(self, initparams):

        self.validate_init_contents(initparams)

        # 1. CP2 will send a STATUS message with “type “PERTURBING SYSTEM”.
        self.th_client.send_status(status_types.PERTURBING_SYSTEM)

        # 2. Based on the target value, CP2 will perturb the architecture, and
        # send a STATUS message with “type” “SYSTEM PERTURBED”.
        log = self.perturb_architecture()
        self.th_client.send_status(status_types.SYSTEM_PERTURBED, log_msg=log)

        # 3. CP2 will send a STATUS message with “type” “BUILDING SYSTEM”.
        self.th_client.send_status(status_types.BUILDING_SYSTEM)

        # 4. Using the “Contents,” CP2 will generate an OS snippet, including
        # pre-condition and post-condition code in C. Upon error, CP2 will send
        # an ERROR message with “ErrorType” “SYSTEM BUILD FAILED” and
        # terminate.

        code = None

        # TODO(apatel): 5.Should code synthesis proceed more slowly than the
        # agreed upon timeout interval, CP2 will issue STATUS messages of
        # “type” “RUNNING # KEEPALIVE” as many times as necessary.
        try:
            (code, log) = self.generate_os_snippet()

            # 6. When code synthsis is complete, CP2 will send a STATUS message
            # with “type” “SYSTEM BUILT”; “LogMsg” will contain the synthesized
            # C code.

            # dholland: append the actual log after the synthesized code and
            # a separator
            if log is not None:
                log = code + "\n\n\n\n********************************\n" + log
            else:
                log = code
            self.th_client.send_status(status_types.SYSTEM_BUILT, log_msg=log)
        except Exception as e:
            self.th_client.send_error(error_types.SYSTEM_BUILD_FAILED, str(e))
            exit(1)

        log = None
        try:
            # 7.CP2 will then enter a “verification” state. It will send a STATUS
            # message with “type” “VERIFYING SYSTEM”. 
            self.th_client.send_status(status_types.VERIFYING_SYSTEM)

            # 8. It will attempt to verify that the code snippet satisfies its
            # post-condition, given that its pre-condition is true on entry. 
            (result, log) = self.verify_code_snippet(code)

            # TODO(apatel) 9. Should code synthesis proceed more slowly than the
            # agreed upon timeout interval, CP2 will issue STATUS messages of
            # “type” “VERIFICATION KEEPALIVE” as many times as necessary.

        except Exception as e:
            # 10. On error, it will send an ERROR message with “ErrorType”
            # “VERIFICATION FAILED.”
            self.th_client.send_error(error_types.VERIFICATION_FAILED, str(e))
            exit(1)

        # 11. Upon completion, CP2 will send a DONE message with “Result”
        # containing the output of the verification procedure.
        self.th_client.send_finished_status(result, log)

            
