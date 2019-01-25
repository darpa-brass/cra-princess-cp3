package com.cra.princess.power;

import org.apache.log4j.Logger;

import java.util.List;
import java.util.LinkedList;

/**
 * Periodically decrements remaining battery power to simulate use over time
 *
 */
public class PowerReductionEventPlayer extends Thread {
	private static final Logger LOG = Logger.getLogger(PowerReductionEventPlayer.class.getName());

	private boolean doWork = true;
	private RemusBattery battery = null;
	private LinkedList<PowerReductionEvent> events = null;
	private long msCount = 0L;
	private boolean paused = false;

	public PowerReductionEventPlayer(RemusBattery battery, List<PowerReductionEvent> events) {
		super();

		if (battery == null) {
			String msg = "Invalid battery provided";
			LOG.error(msg);
			throw new IllegalArgumentException(msg);
		}

		this.battery = battery;

		this.events = new LinkedList<PowerReductionEvent>();
		if (events != null && events.isEmpty() == false) {
			LOG.debug("Loading " + events.size() + " battery perturbation events");
			this.events.addAll(events);
		}
	}
	
	@Override
	public void run() {
		PowerReductionEvent event = null;
		long timeIntoScenarioMs = 0L;

		long start = System.currentTimeMillis();

		// Set up the first event
		if (this.events.isEmpty() == false) {
			event = this.events.remove();
			timeIntoScenarioMs = event.getTimeIntoScenarioMs();
		}

		long runTimeMs = start;

		while(doWork) {
			if (this.paused == false) {
				this.msCount = runTimeMs - start;
				if (this.msCount >= timeIntoScenarioMs && event != null) {
					LOG.debug("Playing battery perturbation event: " + event.getReductionPercent() + "% reduction");
					double energyUsed = this.battery.getRemaining() * event.getReductionPercent();
					LOG.debug("Deducting " + energyUsed + " watt-hours from battery");
					this.battery.useEnergy(energyUsed);

					// Set up the next event
					if (this.events.isEmpty() == false) {
						event = this.events.remove();
						timeIntoScenarioMs = event.getTimeIntoScenarioMs();
					} else {
						event = null;
						timeIntoScenarioMs = 0;
					}
				}

				runTimeMs = runTimeMs + 100;
			}

			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// Ignore
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
}
