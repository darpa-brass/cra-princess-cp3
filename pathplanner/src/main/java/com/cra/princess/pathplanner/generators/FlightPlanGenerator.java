package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.VehicleModel;
import com.cra.princess.pathplanner.FlightPlan;
import com.cra.princess.pathplanner.Polygon;
import com.cra.princess.pathplanner.SensorModel;

/**
 * Interface for objects that can generate flight paths that cover a given search area
 */
public interface FlightPlanGenerator
{
    /**
     * Generate a new FlightPlan based on the properties of the vehicle, sensor and area to cover.
     * NOTE: The all coordinates should be in a local cartesian coordinate system and not in latitude/longitude
     * @param vehicleModel
     * @param sensorModel
     * @param area to cover with a FlightPlan
     * @return a FlightPlan detailing a path a UAV should take to cover the given area
     */
    FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area);
}
