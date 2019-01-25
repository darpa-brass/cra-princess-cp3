import subprocess
import time
from multiprocessing import Process
import os
import signal
import psutil
import sys
import datetime
import random
from shutil import copyfile
import json

# Global Parameters 
# NOTE: RELEASES_DIR path MUST BE ABSOLUTE (should not contain env vars or ~)
RELEASES_DIR = "C:/dev/princess_collab/releases/"

# General Test Parameters
NUM_TESTS = 1000 

# CP3-specific parameters
RUN_CP3 = True 
CP3_MIN_PERTURBATIONS = 1
CP3_MAX_PERTURBATIONS = 2 
CP3_MIN_PERTURBATION_TIME = 10
CP3_MAX_PERTURBATION_TIME = 360
CP3_MIN_POWER_REDUCTION = 20
CP3_MAX_POWER_REDUCTION = 80

# CP1-specific parameters
RUN_CP1 = False 
CP1_MIN_PERTURBATIONS = 0 
CP1_MAX_PERTURBATIONS = 0
CP1_MIN_CURRENTS = 1
CP1_MAX_CURRENTS = 3
CP1_MIN_PERTURB_TIME = 50
CP1_MAX_PERTURB_TIME = 75

# Internal Constants 
GRIZZLY_LOG_PREFIX = "grizzly_log_"
PRINCESS_LOG_PREFIX = "princess_"
REMUS_LOG = "princess.log"
LOG_DIR = "logs/"
CP1_DIR = "princess-cp1_1.0.0-2.12/"
CP3_DIR = "princess-cp3_1.0.0-2.12/"
PRINCESS_LOG = "princess.log"
ACTIVEMQ_COMMAND = "activemq start"

# Sensor perturbation types
CP1_STUCKAT_PERTURBATION = 1
CP1_NOISE_PERTURBATION = 2
CP1_BIAS_PERTURBATION = 3
SURGE_MU=3.2
SURGE_SIGMA=0.017

def find_procs_by_name(name):
    "Return a list of processes matching 'name'."
    ls = []
    for p in psutil.process_iter(attrs=['name']):
        if p.info['name'] == name:
            ls.append(p)
    return ls

def kill_proc_tree(pid, sig=signal.SIGTERM, include_parent=True,
                   timeout=None, on_terminate=None):
    """Kill a process tree (including grandchildren) with signal
    "sig" and return a (gone, still_alive) tuple.
    "on_terminate", if specified, is a callabck function which is
    called as soon as a child terminates.
    """
    if pid == os.getpid():
        return ([], [])
        #raise RuntimeError("I refuse to kill myself")
    parent = psutil.Process(pid)
    children = parent.children(recursive=True)
    if include_parent:
        children.append(parent)
    for p in children:
        p.send_signal(sig)
    gone, alive = psutil.wait_procs(children, timeout=timeout,
                                    callback=on_terminate)
    return (gone, alive)

def remus_proc():
    if(os.name == "nt"):
        remus_cmd = "run.bat"
    else:
        remus_cmd = "bash ./run"
    p = subprocess.call(remus_cmd, shell=True)

# TODO make filename arg
def grizzly_proc():
    grizzly_logfile=GRIZZLY_LOG_PREFIX
    if(os.name == "nt"):
        grizzly_cmd = "java -cp \"./lib/*;./target/scala-2.12/classes\" com.cra.brass.testharness.GrizzlyService"
    else:
        grizzly_cmd = "java -cp \"./lib/*:./target/scala-2.12/classes\" com.cra.brass.testharness.GrizzlyService"
    with open(grizzly_logfile, "w+") as outfile:
        p = subprocess.call(grizzly_cmd, shell=True, stdout=outfile) 

def activemq_proc():
    if(os.name == "nt"):
        p = subprocess.call(ACTIVEMQ_COMMAND, shell=True)

def start_proc(target_func):
    process = Process(target = target_func)
    process.start()
    return process.pid
    
def get_random_params_cp1(adaptation):
    params_file = RELEASES_DIR+CP1_DIR+"config/default/cp1-initialParams.json"

    # Load json object from existing file
    with open(params_file) as f:
        params = json.load(f)

    if(adaptation == True):
        # Generate random origin, destination, current
        origin = {}
        origin["Lat"] = 0.0
        origin["Lon"] = 0.0

        dest = {}
        dest["Lat"] = 0.005
        dest["Lon"] = 0.0

        # Generate list of random currents
        numCurrents = random.randint(CP1_MIN_CURRENTS, CP1_MAX_CURRENTS)
        currentList = []
        for i in xrange(numCurrents):
            current = {}
            current["LowerLeftLocation"] = {}
            current["UpperRightLocation"] = {}
            currentLowerLeftLat = random.uniform(0.0015, 0.005)
            currentLowerLeftLon = -0.005
            currentUpperRightLat = random.uniform(currentLowerLeftLat, 0.005)
            currentUpperRightLon = 0.005
            current["LowerLeftLocation"]["Lat"] = currentLowerLeftLat
            current["LowerLeftLocation"]["Lon"] = currentLowerLeftLon
            current["UpperRightLocation"]["Lat"] = currentUpperRightLat
            current["UpperRightLocation"]["Lon"] = currentUpperRightLon
            current["vE"] = random.uniform(-2.0, 2.0)
            current["vN"] = random.uniform(-2.0, 2.0)
            currentList.append(current)

        # Generate list of random sensor perturbations
        numPerturbations = random.randint(CP1_MIN_PERTURBATIONS, CP1_MAX_PERTURBATIONS)
        perturbList = []
        for i in xrange(numPerturbations):
            perturb = {}
            perturbationType = random.randint(1, 3)
            perturb["TimeIntoScenario"] = random.randint(CP1_MIN_PERTURB_TIME, CP1_MAX_PERTURB_TIME)
            perturb["SensorName"] = "dvl_surge"
            # Generate a bias perturbation if applicable
            if (perturbationType == CP1_BIAS_PERTURBATION):
                perturb["SensorBias"] = random.uniform(SURGE_SIGMA, 10 * SURGE_SIGMA)
            else:
                perturb["SensorBias"] = 0.0

            # Generate a noise perturbation if applicable
            if (perturbationType == CP1_NOISE_PERTURBATION):
                perturb["SensorNoise"] = random.uniform(SURGE_SIGMA, 10 * SURGE_SIGMA)
            else:
                perturb["SensorNoise"] = 0.017

            # Generate a stuck-at perturbation if applicable
            if (perturbationType == CP1_STUCKAT_PERTURBATION):
                perturb["SensorAnchor"] = random.uniform(SURGE_MU + SURGE_SIGMA, SURGE_MU + 30 * SURGE_SIGMA)
                perturb["SensorAnchorProbability"] = 1.0
                perturb["SensorNoise"] = 0.0
            else:
                perturb["SensorAnchor"] = 0.0
                perturb["SensorAnchorProbability"] = 0.0

            perturbList.append(perturb)

        # Sort sensor perturbations by time
        sorted(perturbList, key=lambda item: item["TimeIntoScenario"])

        params["Origin"] = origin
        params["Destination"] = dest
        params["DVLSensorPerturbations"] = perturbList
        params["PerturbingCurrents"] = currentList

    params["Adaptation"] = adaptation

    # Write out to file
    with open(params_file, 'w+') as f:
        json.dump(params, f, indent=True)

def get_random_params_cp3(adaptation):
    params_file = RELEASES_DIR+CP3_DIR+"config/default/cp3-initialParams.json"
    perturb_file = RELEASES_DIR+CP3_DIR+"config/default/cp3-batteryPerturbations.json"

    # Load json objects from existing files
    with open(params_file) as f:
        params = json.load(f)
    with open(perturb_file) as f:
        perturb = json.load(f)
   
    if(adaptation == True):
        # Generate random search area and object location
        upperRightLat = random.uniform(0.001,0.002)
        upperRightLon = random.uniform(0.001,0.002)
        objectLocLat = random.uniform(0.0007,upperRightLat)
        objectLocLon = random.uniform(0.0,upperRightLon)
        params["SearchRegion"]["UpperRightLocation"]["Lat"] = upperRightLat 
        params["SearchRegion"]["UpperRightLocation"]["Lon"] = upperRightLon 
        params["SearchRegion"]["ObjectLocation"]["Lat"] = objectLocLat
        params["SearchRegion"]["ObjectLocation"]["Lon"] = objectLocLon

        # Generate random battery perturbations
        numPerturbations = random.randint(CP3_MIN_PERTURBATIONS,CP3_MAX_PERTURBATIONS)
        batteryPerturbations = []
        for i in xrange(numPerturbations):     
            perturbation = {}
            perturbation["TimeIntoScenario"] = random.randint(CP3_MIN_PERTURBATION_TIME, CP3_MAX_PERTURBATION_TIME)
            perturbation["PowerReduction"] = random.uniform(CP3_MIN_POWER_REDUCTION, CP3_MAX_POWER_REDUCTION)
            batteryPerturbations.append(perturbation)
        perturb["BatteryPerturbations"] = batteryPerturbations


    params["Adaptation"] = adaptation

    # Write out to file
    with open(params_file, 'w+') as f:
        json.dump(params, f, indent=True)
    with open(perturb_file, 'w+') as f:
        json.dump(perturb, f, indent=True)

def pre_run(cpstr, testNum, adaptation):
    # Prepare scenario file for new run
    if(cpstr == "cp1"):
        scenario_params = get_random_params_cp1(adaptation)
    else: # Assuming cp3
        scenario_params = get_random_params_cp3(adaptation)

def post_run(cpstr, testNum, adaptation):
    # Clean up after run
    if(cpstr == "cp1"):
        log_dir = RELEASES_DIR+CP1_DIR+LOG_DIR
    else:
        log_dir = RELEASES_DIR+CP3_DIR+LOG_DIR
    timestamp = datetime.datetime.now().replace(microsecond=0).isoformat('-')
    timestamp = timestamp.replace(":",".")
    
    grizzly_log_prefix = GRIZZLY_LOG_PREFIX
    princess_log_prefix = PRINCESS_LOG_PREFIX

    if(adaptation == False):
        grizzly_log_prefix = grizzly_log_prefix + "noadapt_"
        princess_log_prefix = princess_log_prefix + "noadapt_"

    # Rename grizzly log
    os.rename(GRIZZLY_LOG_PREFIX, 
              log_dir+grizzly_log_prefix+str(testNum)+"_"+timestamp+".txt")
    # Rename remus (princess) log
    os.rename(PRINCESS_LOG,
              log_dir+princess_log_prefix+str(testNum)+"_"+timestamp+".txt")

    # Copy cp3 params files
    if(adaptation == True and cpstr == "cp3"):
        copyfile(RELEASES_DIR+CP3_DIR+"config/default/cp3-initialParams.json",
             log_dir+"cp3-initialParams_"+str(testNum)+"_"+timestamp+".json")
        copyfile(RELEASES_DIR+CP3_DIR+"config/default/cp3-batteryPerturbations.json", log_dir+"cp3-batteryPerturbations_"+str(testNum)+"_"+timestamp+".json")

    # Copy cp1 params file
    if(adaptation == True and cpstr == "cp1"):
        copyfile(RELEASES_DIR+CP1_DIR+"config/default/cp1-initialParams.json",
             log_dir+"cp1-initialParams_"+str(testNum)+"_"+timestamp+".json")

def run_once(cpstr, testNum, adaptation):
    if(cpstr != "cp1" and cpstr != "cp3"):
        print "Unsupported Challenge Problem Specified"
        sys.exit(1)

    pre_run(cpstr, testNum, adaptation)

    if(cpstr == "cp1"):
        os.chdir(RELEASES_DIR+CP1_DIR)
    else:
        os.chdir(RELEASES_DIR+CP3_DIR)

    # RUN

    activemqPID = start_proc(activemq_proc)
    time.sleep(10) # wait for activemq to start

    # start grizzly process
    grizzlyPID = start_proc(grizzly_proc)
    time.sleep(10) # wait for grizzly to start
    
    # start remus client
    remusPID = start_proc(remus_proc)
    
    # wait for remus to finish
    remusProcess = psutil.Process(remusPID)
    psutil.wait_procs([remusProcess], timeout=3600)
    print "Remus client finished"

    # stop grizzly process
    kill_proc_tree(grizzlyPID)
    kill_proc_tree(activemqPID)
    pythonProcs = find_procs_by_name("python.exe")
    for p in pythonProcs:
        kill_proc_tree(p.pid)
    time.sleep(10) # wait for grizzly/activmq to quit

    post_run(cpstr, testNum, adaptation)
    
if __name__ == '__main__':
    # Create logs dirs if they don't exist
    if(RUN_CP1 == True):
        try: 
            os.makedirs(RELEASES_DIR+CP1_DIR+LOG_DIR)
        except OSError:
            if not os.path.isdir(RELEASES_DIR+CP1_DIR+LOG_DIR):
                raise

    if(RUN_CP3 == True):
        try:
            os.makedirs(RELEASES_DIR+CP3_DIR+LOG_DIR)
        except OSError:
            if not os.path.isdir(RELEASES_DIR+CP3_DIR+LOG_DIR):
                raise

    # Remove existing princess log files
    if(RUN_CP1 == True):
        try:
            os.remove(RELEASES_DIR+CP1_DIR+PRINCESS_LOG)
        except OSError:
            pass

    if(RUN_CP3 == True):
        try:
            os.remove(RELEASES_DIR+CP3_DIR+PRINCESS_LOG)
        except OSError:
            pass

    # Main loop
    for i in xrange(NUM_TESTS):
        if(RUN_CP1 == True):
            run_once("cp1", i, True)
            run_once("cp1", i, False)
        if(RUN_CP3 == True):
            run_once("cp3", i, True)
            run_once("cp3", i, False)

