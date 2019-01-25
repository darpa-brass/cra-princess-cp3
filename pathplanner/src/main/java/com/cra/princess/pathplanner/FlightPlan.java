package com.cra.princess.pathplanner;

/**
 * Represents a fully specified Flight plan for a given mission
 */
public class FlightPlan
{
    private final VehicleModel vehicleModel;
    private final SensorModel sensorModel;
    private final FlightPath flightPath;
    private final Polygon area;

    public FlightPlan(VehicleModel vehicleModel, SensorModel sensorModel, FlightPath flightPath, Polygon area)
    {
        this.vehicleModel = vehicleModel;
        this.sensorModel = sensorModel;
        this.flightPath = flightPath;
        this.area = area;
    }

    public FlightPath getFlightPath()
    {
        return flightPath;
    }

    public VehicleModel getVehicleModel()
    {
        return vehicleModel;
    }

    public SensorModel getSensorModel()
    {
        return sensorModel;
    }

    public Polygon getArea()
    {
        return area;
    }
}
