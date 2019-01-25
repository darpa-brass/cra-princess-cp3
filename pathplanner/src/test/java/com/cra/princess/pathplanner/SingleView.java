package com.cra.princess.pathplanner;

import java.util.ArrayList;
import java.util.List;

public class SingleView
{
    public static void main(String[] args) {
        final VehicleModel vehicleModel = new VehicleModel(new Point(30,10), new Point(0,0), 10);
        final SensorModel sensorModel = new SensorModel(45 * (Math.PI / 180.0));
        FlightPlanFactory generator = new FlightPlanFactory();
        List<Point> points = new ArrayList<>();
        points.add(new Point(30, 0));
        points.add(new Point(30, 20));
        points.add(new Point(0, 20));
        points.add(new Point(0, 60));
        points.add(new Point(100, 60));
        points.add(new Point(100, 0));
        Polygon area = new Polygon(points);
        FlightPlan flightPlan = generator.generate(vehicleModel, sensorModel, area);
        QuickView.display(flightPlan);
    }
}
