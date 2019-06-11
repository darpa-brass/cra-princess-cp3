package com.cra.princess.metron.remus.state;

public class RemusPowerState {
    public static final String POWER_TOPIC = "princess.power";

    public static final String DATA_FIELD_TIMESTAMP = "timestamp";
    public static final String DATA_FIELD_ENERGY_REMAINING = "energyRemaining";

    private long timestamp;
    private double energyRemaining;

    public RemusPowerState(long timestamp, double energyRemaining) {
        this.timestamp = timestamp;
        this.energyRemaining = energyRemaining;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getEnergyRemaining() {
		return energyRemaining;
	}
}
