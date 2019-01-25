package com.cra.princess.metron.viewer.model;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import com.cra.princess.metron.viewer.model.components.PerturbingCurrent;
import org.junit.Test;

/**
 * Tests for the PerturbingCurrent class.
 * 
 */
public class PerturbingCurrentTest {
	@Test
    public void perturbingCurrentTest() {
		// Creation
		double southLat1 = 30.0;
		double westLon1 = -117.0;
		double northLat1 = 30.1;
		double eastLon1 = -117.1;
		double vE1 = 2.0;
		double vN1 = -3.0;
		
		PerturbingCurrent current1 = new PerturbingCurrent(southLat1, westLon1, northLat1, eastLon1, vE1, vN1);
		assertNotNull(current1);
		assertTrue(current1.getSouthLat() == southLat1);
		assertTrue(current1.getWestLon() == westLon1);
		assertTrue(current1.getNorthLat() == northLat1);
		assertTrue(current1.getEastLon() == eastLon1);
		assertTrue(current1.getvE() == vE1);
		assertTrue(current1.getvN() == vN1);
		
		// Difference
		double southLat2 = 30.1;
		double westLon2 = -117.1;
		double northLat2 = 30.2;
		double eastLon2 = -117.2;
		double vE2 = -2.0;
		double vN2 = 3.0;
		
		PerturbingCurrent current2 = new PerturbingCurrent(southLat2, westLon2, northLat2, eastLon2, vE2, vN2);
		assertNotNull(current2);
		
		assertTrue(current1.equals(current2) == false);
		assertTrue(current1.hashCode() != current2.hashCode());

		// Equality
		double southLat3 = 30.0;
		double westLon3 = -117.0;
		double northLat3 = 30.1;
		double eastLon3 = -117.1;
		double vE3 = 2.0;
		double vN3 = -3.0;
		
		PerturbingCurrent current3 = new PerturbingCurrent(southLat3, westLon3, northLat3, eastLon3, vE3, vN3);
		assertNotNull(current3);	
		assertTrue(current1.equals(current3));
		assertTrue(current1.hashCode() == current3.hashCode());
	}
}
