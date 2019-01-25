package com.cra.princess.metron.remus.state;

import java.util.Formatter;

public class RemusDvlData {
	public static final String DVL_SENSOR_TOPIC = "princess.dvl";

	public static final String DATA_FIELD_TIMESTAMP = "timestamp";
	public static final String DATA_FIELD_DEPTH = "depth";
	public static final String DATA_FIELD_VE = "vE";
	public static final String DATA_FIELD_VN = "vN";
	public static final String DATA_FIELD_VU = "vU";
	public static final String DATA_FIELD_PITCH = "pitch";
	public static final String DATA_FIELD_ROLL = "roll";
	public static final String DATA_FIELD_HEADING = "heading";
	public static final String DATA_FIELD_SURGE = "surge";
	public static final String DATA_FIELD_SWAY = "sway";
	public static final String DATA_FIELD_HEAVE = "heave";

    private long timestamp;
    private double depth;
    private double vE;
    private double vN;
    private double vU;
    private double pitch;
    private double roll;
    private double heading;
	private double surge;
	private double sway;
	private double heave;

    public RemusDvlData(long timestamp, double depth, double vE, double vN, double vU, double pitch, double roll, double heading, double surge, double sway, double heave) {
        this.timestamp = timestamp;
        this.depth = depth;
        this.vE = vE;
        this.vN = vN;
        this.vU = vU;
        this.pitch = pitch;
        this.roll = roll;
        this.heading = heading;
        this.surge = surge;
        this.sway = sway;
        this.heave = heave;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getDepth() {
		return depth;
	}

	public double getvE() {
		return vE;
	}

	public double getvN() {
		return vN;
	}

	public double getvU() {
		return vU;
	}

	public double getPitch() {
		return pitch;
	}

	public double getRoll() {
		return roll;
	}

	public double getHeading() {
		return heading;
	}

	public double getSurge() { return surge; }

	public double getSway() { return sway; }

	public double getHeave() { return heave; }

	@Override
	public String toString() {
    	StringBuilder sb = new StringBuilder();
    	Formatter f = new Formatter(sb);
    	f.format("%d: depth(%.16f), vE(%.16f), vN(%.16f), vU(%.16f), roll(%.16f), pitch(%.16f), heading(%.16f), surge(%.16f), sway(%.16f), heave(%.16f)",
						timestamp, depth, vE, vN, vU, roll, pitch, heading, surge, sway, heave);
    	return sb.toString();
	}
}
