package com.cra.princess.metron.remus.perturbation;

public class RemusSensorPerturbation {
	public static final String SENSOR_PERTURBATION_TOPIC = "princess.sensor.perturbation";

	public static final String DATA_FIELD_TIMESTAMP = "timestamp";
	public static final String DATA_FIELD_NAME = "name";
	public static final String DATA_FIELD_BIAS = "bias";
	public static final String DATA_FIELD_NOISE_DEV = "noiseDeviation";
	public static final String DATA_FIELD_ANCHOR = "anchor";
	public static final String DATA_FIELD_ANCHOR_PROB = "anchorProbability";

	private String name = "unknown_sensor";
    private double bias = 0.0;
    private double noiseDeviation = 0.0;
    private double anchor = 0.0;
	private double anchorProbability = 0.0;

    public RemusSensorPerturbation(String name, double bias, double noiseDeviation, double anchor, double anchorProbability) {
    	this.name = name;
    	this.bias = bias;
    	this.noiseDeviation = noiseDeviation;
    	this.anchor = anchor;
    	this.anchorProbability = anchorProbability;
    }

    public RemusSensorPerturbation(RemusSensorPerturbation perturbation) {
    	if (perturbation != null) {
    		this.name = perturbation.getName();
			this.bias = perturbation.getBias();
			this.noiseDeviation = perturbation.getNoiseDeviation();
			this.anchor = perturbation.getAnchor();
			this.anchorProbability = perturbation.getAnchorProbability();
    	}
    }

	public String getName() { return name; }

	public double getBias() {
		return bias;
	}

	public double getNoiseDeviation() {
		return noiseDeviation;
	}

	public double getAnchor() { return anchor; }

	public double getAnchorProbability() { return anchorProbability; }
}
