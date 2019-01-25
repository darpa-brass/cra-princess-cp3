package com.cra.princess.metron.remus.state;

public class RemusWaterSpeedData {
    public static final String WATER_SPEED_SENSOR_TOPIC = "princess.waterspeed";

    public static final String DATA_FIELD_TIMESTAMP = "timestamp";
    public static final String DATA_FIELD_WATER_SPEED = "WaterSpeed";

    private long timestamp;
    private double speed;

    public RemusWaterSpeedData(long timestamp, double speed) {
        this.timestamp = timestamp;
        this.speed = speed;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getSpeed() {
		return speed;
	}
}
