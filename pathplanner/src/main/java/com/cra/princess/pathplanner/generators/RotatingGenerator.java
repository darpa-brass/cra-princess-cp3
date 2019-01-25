package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.List;
import java.util.stream.Collectors;

/**
 * A {@link RotatingGenerator} is a {@link FlightPlanGenerator} that can rotate the desired search area by a
 * specified amount. Due to how most {@link FlightPlanGenerator}s work this can result in different a {@link FlightPlan}
 */
public class RotatingGenerator implements FlightPlanGenerator
{
    private final FlightPlanGenerator generator;
    private double angleInRadians;

    public RotatingGenerator(FlightPlanGenerator generator)
    {
        this.generator = generator;
        angleInRadians = 0.0;
    }

    public RotatingGenerator(FlightPlanGenerator generator, double angleInRadians)
    {
        this.generator = generator;
        this.angleInRadians = angleInRadians;
    }

    public void setAngleInRadians(double angleInRadians)
    {
        this.angleInRadians = angleInRadians;
    }

    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        Point center = area.getBounds().centroid();
        VehicleModel rotatedVehicleModel = rotate(vehicleModel, angleInRadians, center);
        SensorModel rotatedSensorModel = rotate(sensorModel, angleInRadians, center);
        Polygon rotatedPoly = rotate(area, angleInRadians, center);
        FlightPlan rotatedFlightPlan = generator.generate(rotatedVehicleModel, rotatedSensorModel, rotatedPoly);
        FlightPlan flightPlan = rotate(rotatedFlightPlan, -angleInRadians, center);
        return flightPlan;
    }

    protected static SensorModel rotate(SensorModel sensorModel, double angle, Point center)
    {
        return sensorModel;
    }

    protected static FlightPlan rotate(FlightPlan flightPlan, double angle, Point center)
    {
        VehicleModel vehicleModel = rotate(flightPlan.getVehicleModel(), angle, center);
        SensorModel sensorModel = rotate(flightPlan.getSensorModel(), angle, center);
        FlightPath flightPath = rotate(flightPlan.getFlightPath(), angle, center);
        Polygon rotatedArea = rotate(flightPlan.getArea(), angle, center);
        return new FlightPlan(vehicleModel, sensorModel, flightPath, rotatedArea);
    }

    protected static FlightPath rotate(FlightPath flightPath, double angle, Point center)
    {
        List<Point> points = rotate(flightPath.getPoints(), angle, center);
        return new FlightPath(points);
    }

    protected static List<Point> rotate(List<Point> points, double angle, Point center)
    {
        return points.stream().map(p -> RotatingGenerator.rotate(p, angle, center)).collect(Collectors.toList());
    }

    protected static Polygon rotate(Polygon polygon, double angle, Point center)
    {
        List<Point> points = rotate(polygon.getPoints(), angle, center);
        return new Polygon(points);
    }

    protected static VehicleModel rotate(VehicleModel vehicleModel, double angle, Point center)
    {
        return new VehicleModel(rotate(vehicleModel.getStartLocation(), angle, center),
                rotate(vehicleModel.getStartLocation(), angle, center),
                vehicleModel.getAltitude());
    }

    protected static Point rotate(Point point, double angle, Point center)
    {
        double s = Math.sin(angle);
        double c = Math.cos(angle);

        Point p = point.minus(center);
        double x = p.getX() * c - p.getY() * s;
        double y = p.getX() * s + p.getY() * c;
        Point newPoint = new Point(x, y);
        return newPoint.plus(center);
    }

    @Override
    public String toString()
    {
        return String.format("%s{gen=%s}", this.getClass().getSimpleName(), generator.toString());
    }
}
