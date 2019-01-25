package com.cra.princess.pathplanner;

/**
 * Object encapsulating the extrinsic properties of the vehicle for the mission
 */
public class VehicleModel
{
    private final Point startLocation;
    private final Point returnLocation;
    private final double altitude;

    public VehicleModel(Point startLocation, Point returnLocation, double altitude)
    {
        this.startLocation = startLocation;
        this.returnLocation = returnLocation;
        this.altitude = altitude;
    }

    public double getAltitude()
    {
        return altitude;
    }

    public Point getStartLocation()
    {
        return startLocation;
    }

    public Point getReturnLocation()
    {
        return returnLocation;
    }

    @Override
    public String toString()
    {
        return "VehicleModel{" +
                "startLocation=" + startLocation +
                ", altitude=" + altitude +
                '}';
    }
}
