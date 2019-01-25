package com.cra.princess.pathplanner;

public class Waypoint
{
    private double north = 0.0;
    private double east = 0.0;

    public Waypoint(double lat, double lon)
    {
        this.north = lat;
        this.east = lon;
    }

    public double getNorth()
    {
        return north;
    }

    public double getEast()
    {
        return east;
    }

    @Override
    public String toString()
    {
        return String.format("Waypoint{north=%.1f, east=%.1f}", north, east);
    }
}
