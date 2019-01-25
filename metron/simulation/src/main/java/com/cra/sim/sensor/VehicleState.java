package com.cra.sim.sensor;

/*
 * Ground-truth vehicle state
 */
public class VehicleState {
    // Velocity in m/s body frame relative to water
    public double surge;
    public double sway;
    public double heave;
    // Attitude in radians, roll-pitch-yaw convention
    public double roll;
    public double pitch;
    public double yaw;
    // Attitude rate in rad/s.
    public double rollRate;
    public double pitchRate;
    public double yawRate;
    // Position relative to origin in meters
    public double northing;
    public double easting;
    public double depth;
    // water current velocity m/s world frame
    public double currentEasting;
    public double currentNorthing;
}
