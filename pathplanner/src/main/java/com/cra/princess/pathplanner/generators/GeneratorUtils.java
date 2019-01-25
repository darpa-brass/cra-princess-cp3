package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.ArrayList;
import java.util.List;

/**
 * {@link GeneratorUtils} is a collection of useful functions for generating FlightPaths
 */
public class GeneratorUtils
{
    private GeneratorUtils(){}

    /**
     * Given the field of view and the altitude determine how much of the ground can be seen.
     * Currently assumes the sensor is looking straight down.
     * @param vehicleModel
     * @param sensorModel
     * @return lengtn of the ground that can be observed, in meters.
     */
    public static double groundViewInMeters(VehicleModel vehicleModel, SensorModel sensorModel)
    {
        return 2.0 * vehicleModel.getAltitude() * Math.tan(sensorModel.getFovRadians());
    }

    /**
     * Determine if two Segments intersect
     * @param s1
     * @param s2
     * @return
     */
    public static Point intersection(Segment s1, Segment s2){
        return intersection(s1.getStart(), s1.getEnd(), s2.getStart(), s2.getEnd());
    }

    public static boolean intersects(Segment s1, Segment s2){
        return intersection(s1.getStart(), s1.getEnd(), s2.getStart(), s2.getEnd()) != Point.INVALID;
    }


    /**
     * // TODO this needs unit tests
     * Return the intersection of two line segments, or Point.INVALID if there is no such intersection
     * @param p first point of the first segment
     * @param pr second point of the first segment
     * @param q first point of the second segment
     * @param qs second point of the second segment
     * @return the intersection point or Point.INVALID
     */
    public static Point intersection(Point p, Point pr, Point q, Point qs){
        Point r = pr.minus(p);
        Point s = qs.minus(q);
        double rXs = r.cross(s);
        double qpXr = q.minus(p).cross(r);
        if(rXs == 0.0 && qpXr ==0.0){
            // Segments are colinear
            return Point.INVALID;
        } else if(rXs == 0.0 && qpXr != 0.0){
            // Segments are parallel
            return Point.INVALID;
        } else if(rXs != 0.0 && qpXr != 0.0) {
            Point qMp = q.minus(p);
            double rXsInv = 1.0 / rXs;
            double t = qMp.cross(s.scale(rXsInv));
            double u = qMp.cross(r.scale(rXsInv));
            if(t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0){
                return p.plus(r.scale(t));
            }
        }
        return Point.INVALID;
    }

    /**
     * Find all the intersections between a segment and a polygon. Intersection points are ordered
     * by distance to the start of the segment
     * @param segment
     * @param polygon
     * @return
     */
    public static List<Point> intersections(Segment segment, Polygon polygon){
        List<Point> intersections = new ArrayList<>();
        for(Segment polySide: polygon.getSegments()){
            Point intersection = intersection(segment, polySide);
            if(intersection != Point.INVALID){
                intersections.add(intersection);
            }
        }

        // Ensure intersections are ordered from closest to the start of the segment to the end
        final Point start = segment.getStart();
        intersections.sort((o1, o2) -> Double.compare(start.distance(o1), start.distance(o2)));

        return intersections;
    }

    /**
     * Check if a point is inside a polygon.
     * Works by creating a segment from the point to +infinty.
     * If the segment intersects an even number of sides the it is outside
     * If the segment intersects an odd number of sides the it is inside
     * @param point
     * @param polygon
     * @return
     */
    public static boolean inside(Point point, Polygon polygon){
        // Use a point we know is outside of the polygon to construct the segment
        Bounds bounds = polygon.getBounds();
        Point outsidePoint = new Point(bounds.getMaxX() + 1000.0, bounds.getMaxY() + 1000.0);
        Segment segment = new Segment(point, outsidePoint);
        List<Point> intersections = intersections(segment, polygon);
        return (intersections.size() % 2) == 1;
    }

}
