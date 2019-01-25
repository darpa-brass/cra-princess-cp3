package com.cra.princess.evaluation;

/**
 * Constants for sending messages to the Test Harness
 * 
 */
public class TestHarnessAdapterConstants {
	// Error Types
	public static final String ERROR_INITIALIZATION_FAILURE = "INITIALIZATION_FAILURE";
	public static final String ERROR_PATH_GENERATION_FAILURE = "PATH_GENERATION_FAILURE";
	public static final String ERROR_SCENARIO_GENERATION_FAILURE = "SCENARIO_GENERATION_FAILURE";
	public static final String ERROR_SCENARIO_FAILURE = "SCENARIO_FAILURE";
	public static final String ERROR_ADAPTATION_ERROR = "ADAPTATION_ERROR";

	public static final String ERROR_SYSTEM_FAILURE = "SYSTEM_FAILURE";

	// Status Types
	public static final String STATUS_SCENARIO_GENERATION_STARTED = "SCENARIO_GENERATION_STARTED";
	public static final String STATUS_SCENARIO_GENERATION_COMPLETED = "SCENARIO_GENERATION_COMPLETED";
	public static final String STATUS_SCENARIO_STARTED = "SCENARIO_STARTED";
	public static final String STATUS_SCENARIO_COMPLETED = "SCENARIO_COMPLETED";
	public static final String STATUS_STATE_UPDATE = "STATE_UPDATE";
	public static final String STATUS_PERTURBATION_DETECTED = "PERTURBATION_DETECTED";
	public static final String STATUS_INTENT_VIOLATION_DETECTED = "INTENT_VIOLATION_DETECTED";
	public static final String STATUS_ADAPTATION_STARTED = "ADAPTATION_STARTED";
	public static final String STATUS_ADAPTATION_COMPLETED = "ADAPTATION_COMPLETED";
	public static final String STATUS_ADAPTATION_FAILURE = "ADAPTATION_FAILURE";
	public static final String STATUS_OBJECT_FOUND = "OBJECT_FOUND";
	public static final String STATUS_RESULTS = "RESULTS";

	// State Types
	public static final String STATE_READY = "READY";
	public static final String STATE_DONE = "DONE";
	public static final String STATE_PATH = "PATH";
}

