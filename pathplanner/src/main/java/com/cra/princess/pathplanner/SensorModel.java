package com.cra.princess.pathplanner;

/**
 * Object encapsulating the sensor properties that the planner needs to know about
 */
public class SensorModel
{
    private final double fovRadians;

    public SensorModel(double fovRadians){
        this.fovRadians = fovRadians;
    }

    public double getFovRadians()
    {
        return fovRadians;
    }

    @Override
    public String toString()
    {
        return "SensorModel{" +
                "hFovRadians=" + fovRadians +
                ", hFovDegrees=" + (fovRadians * (180.0 / Math.PI)) +
                '}';
    }
}
