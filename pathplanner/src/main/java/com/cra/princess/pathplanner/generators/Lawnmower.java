package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.ArrayList;
import java.util.List;

/**
 * A {@link Lawnmower} is a {@link FlightPlanGenerator} that uses evenly spaced parallel legs to cover a search area.
 */
public class Lawnmower implements FlightPlanGenerator
{
    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        Bounds bounds = area.getBounds();
        double viewSize = GeneratorUtils.groundViewInMeters(vehicleModel, sensorModel);
        int legs = (int)Math.ceil(bounds.getHeight() / viewSize) - 1;
        if(legs <= 1){
            legs = 1;
            viewSize = bounds.getHeight();
        }
        double halfViewSize = viewSize / 2.0;
        Point crossDir = new Point(0.0, viewSize);
        Point p1 = new Point(bounds.getMinX(), bounds.getMinY() + halfViewSize);
        Point p2 = new Point(bounds.getMaxX(), bounds.getMinY() + halfViewSize);
        List<Point> plan = new ArrayList<>();
        for(int i = 0; i < legs; ++i){
            plan.add(p1);
            plan.add(p2);
            Point temp = p1.plus(crossDir);
            p1 = p2.plus(crossDir);
            p2 = temp;
        }
        return new FlightPlan(vehicleModel, sensorModel, new FlightPath(plan), area);
    }

    @Override
    public String toString()
    {
        return this.getClass().getSimpleName();
    }
}
