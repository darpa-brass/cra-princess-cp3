package com.cra.princess.metron.viewer.model;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import com.cra.princess.metron.viewer.model.components.Location;
import org.junit.Test;

/**
 * Tests for the Location class.
 * 
 */
public class LocationTest {
	@Test
    public void locationTest() {
		// Creation
		double lat1 = 30.0;
		double lon1 = -117.0;
		double depth1 = 10.0;
		
		Location location1 = new Location(lat1, lon1, depth1);
		assertNotNull(location1);
		assertTrue(location1.getLatitude() == lat1);
		assertTrue(location1.getLongitude() == lon1);
		assertTrue(location1.getDepth() == depth1);

		// Difference
		double lat2 = 33.6;
		double lon2 = -118.009;
		double depth2 = 21.1;
		
		Location location2 = new Location(lat2, lon2, depth2);
		assertNotNull(location2);
		
		assertTrue(location1.equals(location2) == false);
		assertTrue(location1.hashCode() != location2.hashCode());

		// Equality
		double lat3 = 30.0;
		double lon3 = -117.0;
		double depth3 = 10.0;
		
		Location location3 = new Location(lat3, lon3, depth3);
		assertNotNull(location3);	
		assertTrue(location1.equals(location3));
		assertTrue(location1.hashCode() == location3.hashCode());
	}
}
