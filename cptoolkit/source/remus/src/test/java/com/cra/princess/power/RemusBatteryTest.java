package com.cra.princess.power;

import org.junit.Test;

import static junit.framework.TestCase.assertTrue;

/**
 * Testing the simulated array of batteries on a REMUS
 * 
 */
public class RemusBatteryTest {
	@Test
	public void batteryTest() {
		RemusBattery battery = new RemusBattery(1000.0);
		assertTrue(battery != null);

		// Check starting power
		assertTrue(battery.getRemaining() == 1000.0);
		// Check using no power
		battery.useEnergy(0.0);
		assertTrue(battery.getRemaining() == 1000.0);
		// Check using negative power
		battery.useEnergy(-100.0);
		assertTrue(battery.getRemaining() == 1000.0);
		// Check using 1 kWh of power
		battery.useEnergy(600.0);
		assertTrue(battery.getRemaining() == 400.0);
		// Check using remaining power
		battery.useEnergy(400);
		assertTrue(battery.getRemaining() == 0.0);
		// Check over-using remaining power
		battery.useEnergy(100);
		assertTrue(battery.getRemaining() == 0.0);
	}
}
