package com.cra.princess.pathplanner;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * A {@link FlightPath} specifies a series of waypoints for a vehicle to follow.
 */
public class FlightPath
{
    private final List<Point> points;
    private final List<Segment> segments;

    public FlightPath(List<Point> points)
    {
        this.points = Collections.unmodifiableList(points);
        List<Segment> segments = new ArrayList<>();
        if(!points.isEmpty()){
            Point last = null;
            for(Point p: points){
                if(last == null){
                    last = p;
                    continue;
                }
                segments.add(new Segment(last, p));
                last = p;
            }
        }
        this.segments = Collections.unmodifiableList(segments);
    }

    public List<Point> getPoints()
    {
        return points;
    }

    public List<Segment> getSegments()
    {
        return segments;
    }

    public Bounds getBounds()
    {
        double minX = Double.MAX_VALUE;
        double maxX = Double.MIN_VALUE;
        double minY = Double.MAX_VALUE;
        double maxY = Double.MIN_VALUE;
        for(Point p: points){
            minX = Math.min(minX, p.getX());
            maxX = Math.max(maxX, p.getX());
            minY = Math.min(minY, p.getY());
            maxY = Math.max(maxY, p.getY());
        }
        return new Bounds(minX, maxX, minY, maxY);
    }
}
