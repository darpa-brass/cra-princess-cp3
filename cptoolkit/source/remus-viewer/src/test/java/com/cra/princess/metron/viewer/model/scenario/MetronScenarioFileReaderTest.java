package com.cra.princess.metron.viewer.model.scenario;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.IOException;
import java.util.List;

import com.cra.princess.metron.viewer.model.MetronScenarioFileReader;
import com.cra.princess.metron.viewer.model.ScenarioFileReader;
import org.junit.Test;

import com.cra.princess.metron.viewer.model.components.Location;
import com.cra.princess.metron.viewer.model.components.PerturbingCurrent;

/**
 * Tests for the Metron scenario file reader.
 * 
 */
public class MetronScenarioFileReaderTest {
	@Test
    public void readTest() throws IOException {
		// Load the sample Metron scenario file from ./test/resources
		String scenarioFile = this.getClass().getClassLoader().getResource("scenario.json").getFile();
		ScenarioFileReader reader = new MetronScenarioFileReader(new File(scenarioFile));
		assertNotNull(reader);
		
		Location origin = reader.getRemusOrigin();
		assertNotNull(origin);
		assertTrue(origin.getLatitude() == 30.0);
		assertTrue(origin.getLongitude() == -117.0);
		assertTrue(origin.getDepth() == 10.0);

		Location destination = reader.getRemusDestination();
		assertNotNull(destination);
		assertTrue(destination.getLatitude() == 30.01);
		assertTrue(destination.getLongitude() == -117.0);
		assertTrue(destination.getDepth() == 10.0);

		assertTrue(destination.equals(origin) == false);	

		List<PerturbingCurrent> currentRegions = reader.getPerturbingCurrents();
		assertNotNull(currentRegions);
		assertTrue(currentRegions.size() == 2);

		PerturbingCurrent pc = currentRegions.get(0);
		assertNotNull(pc);
		assertTrue(pc.getSouthLat() == 30.001);
		assertTrue(pc.getWestLon() == -118.0);
		assertTrue(pc.getNorthLat() == 30.002);
		assertTrue(pc.getEastLon() == -116.0);
		assertTrue(pc.getvE() == 10.0);
		assertTrue(pc.getvN() == 10.0);
	}
}
