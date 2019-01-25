package com.cra.princess.metron.remus.command;

public class RemusVehicleCommand {
	public static final String VEHICLE_COMMAND_TOPIC = "princess.vehicle.command";

	public static final String DATA_FIELD_TIMESTAMP = "timestamp";
	public static final String DATA_FIELD_DEPTH_TARGET = "depthTarget";
	public static final String DATA_FIELD_HEADING_TARGET = "headingTarget";
	public static final String DATA_FIELD_SPEED_TARGET = "speedTarget";

    private double headingTarget = 0.0;
    private double depthTarget = 0.0;
    private double speedTarget = 0.0;

    public RemusVehicleCommand(double headingTarget, double depthTarget, double speedTarget) {
    	this.headingTarget = headingTarget;
    	this.depthTarget = depthTarget;
    	this.speedTarget = speedTarget;
    }

    public RemusVehicleCommand(RemusVehicleCommand cmd) {
    	if (cmd != null) {
    		this.headingTarget = cmd.getHeadingTarget();
    		this.depthTarget = cmd.getDepthTarget();
    		this.speedTarget = cmd.getSpeedTarget();
    	}
    }

	public double getHeadingTarget() {
		return headingTarget;
	}

	public double getDepthTarget() {
		return depthTarget;
	}

	public double getSpeedTarget() {
		return speedTarget;
	}    
}
