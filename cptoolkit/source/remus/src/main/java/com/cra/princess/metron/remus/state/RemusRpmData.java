package com.cra.princess.metron.remus.state;

public class RemusRpmData {
    public static final String RPM_TOPIC = "princess.rpm";

    public static final String DATA_FIELD_TIMESTAMP = "timestamp";
    public static final String DATA_FIELD_RPM = "PropellerRpm";

    private long timestamp;
    private double rpm;

    public RemusRpmData(long timestamp, double rpm) {
        this.timestamp = timestamp;
        this.rpm = rpm;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getRpm() {
		return rpm;
	}
}
