package com.cra.princess.metron.remus.state;

public class RemusObjectDetectionState {
    public static final String OBJECT_DETECTION_TOPIC = "princess.objectdetection";

    public static final String DATA_FIELD_TIMESTAMP = "timestamp";
    public static final String DATA_FIELD_RANGE = "range";
    public static final String DATA_FIELD_THETA = "theta";
    public static final String DATA_FIELD_PHI = "phi";

    private long timestamp;
    private double range;
    private double theta;
    private double phi;

    public RemusObjectDetectionState(long timestamp, double range, double theta, double phi) {
        this.timestamp = timestamp;
        this.range = range;
        this.theta = theta;
        this.phi = phi;
    }

	public long getTimestamp() {
		return timestamp;
	}

    public double getRange() {
        return range;
    }

    public double getTheta() {
        return theta;
    }
    public double getPhi() {
        return phi;
    }
}
