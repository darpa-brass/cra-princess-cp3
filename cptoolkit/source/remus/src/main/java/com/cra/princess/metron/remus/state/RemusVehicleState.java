package com.cra.princess.metron.remus.state;

public class RemusVehicleState {
	public static final String TRUTH_TOPIC = "princess.truth";

	public static final String DATA_FIELD_TIMESTAMP = "timestamp";
	public static final String DATA_FIELD_TRUELON = "trueLongitude";
	public static final String DATA_FIELD_TRUELAT = "trueLatitude";
	public static final String DATA_FIELD_TRUEDEPTH = "trueDepth";
	public static final String DATA_FIELD_VE = "vE";
	public static final String DATA_FIELD_VN = "vN";
	public static final String DATA_FIELD_VU = "vU";
	public static final String DATA_FIELD_PITCH = "pitch";
	public static final String DATA_FIELD_ROLL = "roll";
	public static final String DATA_FIELD_HEADING = "heading";
	public static final String DATA_FIELD_SURGE = "surge";
	public static final String DATA_FIELD_SWAY = "sway";
	public static final String DATA_FIELD_HEAVE = "heave";
	public static final String DATA_FIELD_CURRENT_VN = "waterCurrentN";
	public static final String DATA_FIELD_CURRENT_VE = "waterCurrentE";

    private long timestamp;
    private double trueLongitude;
    private double trueLatitude;
    private double trueDepth;
    private double vE;
    private double vN;
    private double vU;
    private double pitch;
    private double roll;
    private double heading;
	private double surge;
	private double sway;
	private double heave;
	private double waterCurrentN;
	private double waterCurrentE;

    public RemusVehicleState(long timestamp, double trueLatitude, double trueLongitude, double trueDepth, double vE, double vN, double vU, double pitch, double roll, double heading, double surge, double sway, double heave, double waterCurrentN, double waterCurrentE) {
        this.timestamp = timestamp;
        this.trueLatitude = trueLatitude;
        this.trueLongitude = trueLongitude;
        this.trueDepth = trueDepth;
        this.vE = vE;
        this.vN = vN;
        this.vU = vU;
        this.pitch = pitch;
        this.roll = roll;
        this.heading = heading;
		this.surge = surge;
		this.sway = sway;
		this.heave = heave;
		this.waterCurrentN = waterCurrentN;
		this.waterCurrentE = waterCurrentE;
    }

	public long getTimestamp() {
		return timestamp;
	}

	public double getTrueLatitude() {
		return trueLatitude;
	}

	public double getTrueLongitude() {
		return trueLongitude;
	}
	
	public double getTrueDepth() {
		return trueDepth;
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

	public double getWaterCurrentN() { return waterCurrentN; }

	public double getWaterCurrentE() { return waterCurrentE; }
}
