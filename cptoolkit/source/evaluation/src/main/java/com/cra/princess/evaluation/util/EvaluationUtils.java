package com.cra.princess.evaluation.util;

import java.io.StringWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonWriter;

import com.cra.princess.evaluation.TestHarnessAdapterConstants;

public class EvaluationUtils {
	// Property Keys
	public static final String BASE_URL_PROPERTY = "baseUrl";

	// Default Property Values
	public static final String BASE_URL_PROPERTY_DEFAULT_VALUE = "http://localhost:8080/brass-th/cp3";

	// Test Control and Test Action Message Data Field Names
	public static final String FIELD_TIME = "Timestamp";
	public static final String FIELD_ERROR = "Error";
	public static final String FIELD_STATUS = "Status";
	public static final String FIELD_MESSAGE = "Message";

	// Date Formatting
	public static final String ECMASCRIPT_DATE_FORMAT = "yyyy-MM-dd'T'HH:mm:ss.SSSZ";

	public static String getTimestamp() {
        Date now = new Date();
        SimpleDateFormat dateFormatter = new SimpleDateFormat(ECMASCRIPT_DATE_FORMAT);
        String timestamp = dateFormatter.format(now);
        
        return timestamp;
    }

    public static boolean validateTimestamp(String timestamp) {
    	boolean isValid = false;
    	
    	if (timestamp != null && timestamp.isEmpty() == false && (
    			timestamp.contains("-") ||
    			timestamp.contains("T") ||
    			timestamp.endsWith(":"))) {
    		isValid = true;
    	}
    	
    	return isValid;
    }

    public static boolean validateErrorType(String errorType) {
    	boolean isValid = false;
    	
    	if (errorType != null && errorType.isEmpty() == false && (
    			errorType.equals(TestHarnessAdapterConstants.ERROR_INITIALIZATION_FAILURE) ||
    			errorType.equals(TestHarnessAdapterConstants.ERROR_PATH_GENERATION_FAILURE) ||
    			errorType.equals(TestHarnessAdapterConstants.ERROR_SCENARIO_GENERATION_FAILURE) ||
				errorType.equals(TestHarnessAdapterConstants.ERROR_ADAPTATION_ERROR) ||
    			errorType.equals(TestHarnessAdapterConstants.ERROR_SCENARIO_FAILURE) ||
				errorType.equals(TestHarnessAdapterConstants.ERROR_SYSTEM_FAILURE))) {
    		isValid = true;
    	}
    	
    	return isValid;
    }

    public static boolean validateStatusType(String statusType) {
    	boolean isValid = false;

    	if (statusType != null && statusType.isEmpty() == false && (
				statusType.equals(TestHarnessAdapterConstants.STATUS_SCENARIO_GENERATION_STARTED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_SCENARIO_GENERATION_COMPLETED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_SCENARIO_STARTED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_SCENARIO_COMPLETED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_STATE_UPDATE) ||
    			statusType.equals(TestHarnessAdapterConstants.STATUS_PERTURBATION_DETECTED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_INTENT_VIOLATION_DETECTED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_OBJECT_FOUND) ||
    			statusType.equals(TestHarnessAdapterConstants.STATUS_ADAPTATION_STARTED) ||
				statusType.equals(TestHarnessAdapterConstants.STATUS_ADAPTATION_FAILURE) ||
    			statusType.equals(TestHarnessAdapterConstants.STATUS_ADAPTATION_COMPLETED))) {
    		isValid = true;
    	}    	
    	
    	return isValid;
    }

	public static boolean validateStateType(String stateType) {
		boolean isValid = false;

		if (stateType != null && stateType.isEmpty() == false && (
				stateType.equals(TestHarnessAdapterConstants.STATE_READY) ||
						stateType.equals(TestHarnessAdapterConstants.STATE_PATH) ||
						stateType.equals(TestHarnessAdapterConstants.STATE_DONE))) {
			isValid = true;
		}

		return isValid;
	}

    public static String jsonToString(JsonObject contentObject) {
        StringWriter stringWriter = new StringWriter();
        JsonWriter writer = Json.createWriter(stringWriter);
        writer.writeObject(contentObject);
        writer.close();
        String jsonString = stringWriter.getBuffer().toString().trim();
        
        return jsonString;
    }
}
