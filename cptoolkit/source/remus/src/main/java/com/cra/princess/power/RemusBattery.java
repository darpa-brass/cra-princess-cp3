package com.cra.princess.power;

import org.apache.log4j.Logger;

/**
 * A simulated array of batteries on a REMUS
 * 
 */
public class RemusBattery {
	private static final Logger LOG = Logger.getLogger(RemusBattery.class.getName());

	// Energy stored in the battery in Watt-hours
	private double energyWh = 0.0;

    public RemusBattery(double energyWh) {
    	this.energyWh = energyWh;
    	LOG.info("Battery has " + this.energyWh + " Watt-hours remaining");
    }

	/**
	 * Get the remaining life in the battery
	 *
	 * @return remaining store in watt-hours
	 */
	public synchronized double getRemaining() {
    	return this.energyWh;
	}

	/**
	 * Consume specified amount of energy from the battery
	 *
	 * @param energyLoss the energy loss from the battery in watt-hours
	 */
	public synchronized void useEnergy(double energyLoss) {
		LOG.info("Using " + energyLoss + " Wh");


		if (energyLoss >= this.energyWh) {
			this.energyWh = 0.0;
			LOG.info("Battery has " + this.energyWh + " Watt-hours remaining");
		}
		else if (energyLoss > 0.0) {
			this.energyWh = this.energyWh - energyLoss;
			LOG.info("Battery has " + this.energyWh + " Watt-hours remaining");
		}
	}
}
