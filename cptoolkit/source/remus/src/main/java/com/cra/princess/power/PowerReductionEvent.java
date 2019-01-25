package com.cra.princess.power;

/**
 * An event intended to reduce the amount of available battery power by a set percentage
 * 
 */
public class PowerReductionEvent {

	private int timeIntoScenarioMs = 0;
	private double reductionPercent = 0.0;

    public PowerReductionEvent(int timeIntoScenarioSeconds, int reductionPercent) {
    	if (timeIntoScenarioSeconds < 0) {
			timeIntoScenarioSeconds = 0;
		}

		if (reductionPercent < 0) {
    		reductionPercent = 0;
		}
		else if (reductionPercent > 100) {
			reductionPercent = 100;
		}

		this.reductionPercent = reductionPercent / 100.0;
		this.timeIntoScenarioMs = timeIntoScenarioSeconds * 1000;
    }

	public int getTimeIntoScenarioMs() {
		return timeIntoScenarioMs;
	}

	public double getReductionPercent() {
		return reductionPercent;
	}

	public String toString() { return "PowerReductionEvent(TimeIntoScenarioMs = " + this.timeIntoScenarioMs + ", ReductionPercent = " + this.reductionPercent + ")"; }
}
