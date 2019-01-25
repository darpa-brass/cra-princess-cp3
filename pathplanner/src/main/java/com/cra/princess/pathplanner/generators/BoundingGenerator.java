package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.ArrayList;
import java.util.List;

/**
 * A {@link BoundingGenerator} takes the output of some other {@link FlightPlanGenerator} and clamps the legs of the
 * {@link FlightPath} to be inside or on the boundary of the search area.
 */
public class BoundingGenerator implements FlightPlanGenerator
{
    private final FlightPlanGenerator generator;

    public BoundingGenerator(FlightPlanGenerator generator)
    {
        this.generator = generator;
    }

    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        FlightPlan initialFlightPlan = generator.generate(vehicleModel, sensorModel, area);
        FlightPath initialFlightPath = initialFlightPlan.getFlightPath();
        List<Point> path = new ArrayList<>();
        for(Segment segment: initialFlightPath.getSegments())
        {
            List<Point> intersections = GeneratorUtils.intersections(segment, area);
            if(GeneratorUtils.inside(segment.getStart(), area)){
                path.add(segment.getStart());
            }
            path.addAll(intersections);
            if(GeneratorUtils.inside(segment.getEnd(), area)){
                path.add(segment.getEnd());
            }
        }
        return new FlightPlan(vehicleModel, sensorModel, new FlightPath(path), area);
    }

    @Override
    public String toString()
    {
        return String.format("%s{gen=%s}", this.getClass().getSimpleName(), generator.toString());
    }
}
