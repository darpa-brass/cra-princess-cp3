package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.ArrayList;
import java.util.List;

/**
 * A {@link Spiral} is a {@link FlightPlanGenerator} that starts at the centroid and spirals out to cover the search area
 */
public class Spiral implements FlightPlanGenerator
{
    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        Bounds bounds = area.getBounds();
        double viewSize = GeneratorUtils.groundViewInMeters(vehicleModel, sensorModel);
        int levelsX = (int)Math.ceil(bounds.getWidth() / viewSize);
        int levelsY = (int)Math.ceil(bounds.getHeight() / viewSize);
        int levels = Math.max(levelsX, levelsY);
        double stepX = bounds.getWidth() / levels;
        double stepY = bounds.getHeight() / levels;

        Point point = bounds.centroid();
        Point direction = new Point(1.0, 0.0);
        double magnitudeX = stepX;
        double magnitudeY = stepY * 2;
        List<Point> path = new ArrayList<>();
        path.add(point);
        int i = 0;
        while(i < levels){

            point = point.plus(direction.scale(magnitudeX));
            path.add(point);
            direction = direction.rotate(Math.PI / 2);
            magnitudeX += stepX*2;
            i++;
            if(i >= levels){
                break;
            }

            point = point.plus(direction.scale(magnitudeY));
            path.add(point);
            direction = direction.rotate(Math.PI / 2);
            magnitudeY += stepY*2;
            i++;
        }

        return new FlightPlan(vehicleModel, sensorModel, new FlightPath(path), area);
    }

    @Override
    public String toString()
    {
        return this.getClass().getSimpleName();
    }
}
