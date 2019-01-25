package com.cra.princess.metron.remus.state;

public class RemusPowerState {
    public static final String POWER_TOPIC = "princess.power";

    public static final String DATA_FIELD_TIMESTAMP = "timestamp";
    public static final String DATA_FIELD_POWER = "remainingPower";

    private long timestamp;
    private double power;

    public RemusPowerState(long timestamp, double power) {
        this.timestamp = timestamp;
        this.power = power;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getPower() {
		return power;
	}
}
