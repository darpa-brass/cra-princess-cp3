package com.cra.princess.evaluation;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.cra.princess.evaluation.messages.LatLon;
import com.cra.princess.evaluation.messages.CP3ResultsType;
import com.cra.princess.evaluation.messages.SearchPath;
import com.cra.princess.evaluation.messages.CP3SutFinishedStatus;
import com.cra.princess.evaluation.util.EvaluationUtils;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import com.sun.grizzly.http.SelectorThread;
import com.sun.jersey.api.container.grizzly.GrizzlyServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import scala.collection.JavaConverters;

/**
 * Class to test sending Test Harness test control messages and DAS logging
 * 
 */
public class TestHarnessAdapterTest {
	private static SelectorThread server = null;

	public static SelectorThread getServer() {
		return server;
	}

	@BeforeClass
	public static void setUpClass() throws IOException {
		// Create and start a Grizzly HTTP server
		server = GrizzlyServerFactory.create("http://localhost:8080/", new PackagesResourceConfig("com.cra.brass.testharness"));
	}

	@AfterClass
	public static void tearDownClass() {
		if (getServer() != null) {
			getServer().stopEndpoint();
		}
	}

	@Test
	public void adapterTest() throws IOException {
		TestHarnessAdapter adapter = TestHarnessAdapter.getInstance();
		assertNotNull(adapter);

		adapter.sendConfigMessage("test");

		String paramsJson = adapter.sendReadyMessage();
		assertNotNull(paramsJson);
    	
    	adapter.sendStatusMessage(TestHarnessAdapterConstants.STATUS_INTENT_VIOLATION_DETECTED, "Status message content");

    	// CP3 Done
		String timestamp = EvaluationUtils.getTimestamp();
		CP3ResultsType results = new CP3ResultsType(true, true, 0.0, 0.0, 0.0);
		CP3SutFinishedStatus sfs = new CP3SutFinishedStatus(timestamp, TestHarnessAdapterConstants.STATUS_RESULTS, results);
        adapter.sendDoneMessage(sfs.toJson());

    	adapter.sendErrorMessage(TestHarnessAdapterConstants.ERROR_INITIALIZATION_FAILURE, "Error message content");

    	List<LatLon> path = new ArrayList<LatLon>();
		LatLon wp0 = new LatLon(-117.0, 30.0);
		LatLon wp1 = new LatLon(-117.1, 30.1);
		LatLon wp2 = new LatLon(-117.2, 30.2);
		LatLon wp3 = new LatLon(-117.3, 30.3);

		List<LatLon> waypoints = new ArrayList<>();
		for (LatLon waypoint : path) {
			waypoints.add(waypoint);
		}
		scala.collection.immutable.List<LatLon> scalaWps = JavaConverters.asScalaBuffer(waypoints).toList();
		SearchPath sp = new SearchPath(timestamp, Double.toString(2.0), scalaWps);

		String sensorEvents = adapter.sendPathMessage(sp.toJson());
		assertNotNull(sensorEvents);
	}
}
