package com.cra.princess.power;

import org.apache.log4j.Logger;

import java.util.Random;

/**
 * Periodically decrements remaining battery power to simulate use over time
 *
 */
public class PowerReductionThread extends Thread {
	private static final Logger LOG = Logger.getLogger(PowerReductionThread.class.getName());

	private boolean doWork = true;
	private RemusBattery battery = null;

	private long timeTick = 1000; // ms
	private double speed = 0.0; // meters per second
	private double prevSpeed = 0.0; // meters per second
	private double heading = 0.0; // degrees
    private double prevHeading = 0.0; // degrees
	private double prevESpeed = 0.0; // m/s
	private double prevNSpeed = 0.0; // m/s

	private boolean paused = false;

	public PowerReductionThread(RemusBattery battery) {
		super();

		if (battery == null) {
			String msg = "Invalid battery provided";
			LOG.error(msg);
			throw new IllegalArgumentException(msg);
		}

		this.battery = battery;
	}
	
	@Override
	public void run() {
		// Gaussian standard deviation for noise in measurements as a percentage of energy loss
		double stdevPercentage = 0.05;
		Random rand = new Random();

		while(doWork) {
			if (this.paused == false) {
				try {
					Thread.sleep(this.timeTick);

					// Calculate power consumption (Watts)
					// ASSUMPTION: max speed of REMUS 600 is 3.2 meters per second, avg speed is 1.6 meters per second
					// ASSUMPTION: avg endurance of a REMUS 600 with a full battery is 70 hours

					// RULE: power consumption must account for vessel drag
					// ASSUMPTION: vessel is operating in a laminar flow with drag force proportional to speed
					// because power is proportional to force * speed, it is therefore proportional to speed^2
					double coeff_drag = 1000.0;
					double power = coeff_drag * this.speed * this.speed;

					// RULE: power consumption must account for acceleration due to heading changes
					// ASSUMPTION: heading changes incur additional cost depending on the angle of change
					// power is proportional to the change in velocity squared
					double newESpeed = this.speed * Math.cos(this.heading * Math.PI / 180.0);
					double newNSpeed = this.speed * Math.sin(this.heading * Math.PI / 180.0);

					double coeff_vel = 10000.0;
					power += coeff_vel * ((newESpeed - this.prevESpeed) * (newESpeed - this.prevESpeed) +
							(newNSpeed - this.prevNSpeed) * (newNSpeed - this.prevNSpeed));
					this.prevESpeed = newESpeed;
					this.prevNSpeed = newNSpeed;

					// RULE: routine power consumption must account for power used by other systems
					double nonPropulsionPower = 1.0;
					power = power + nonPropulsionPower;

					// convert watts to watt-hours since last timeTick
					double energyUsed = power * this.timeTick / 1000 / 3600;

					// add Gaussian noise
					energyUsed += energyUsed * rand.nextGaussian() * stdevPercentage;

					this.battery.useEnergy(energyUsed);
				} catch (InterruptedException e) {
					// Ignore
				}
			}
			else {
				// Wait to resume
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// Ignore
				}
			}
		}
	}

	public void stopWork() {
		this.doWork = false;
	}

	public void pauseWork() {
		this.paused = true;
	}

	public void resumeWork() {
		this.paused = false;
	}

	public synchronized void setSpeed(double speed) {
	    this.prevSpeed = this.speed;
		this.speed = speed;
    }

    public synchronized void setHeading(double heading) {
	    this.prevHeading = this.heading;
        this.heading = heading;
    }
}
