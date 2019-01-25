package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.*;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * TODO: This is not fully tested
 * ASSUMPTION: polygon is ordered clockwise
 */
public class OffsetPolygon implements FlightPlanGenerator
{
    @Override
    public FlightPlan generate(VehicleModel vehicleModel, SensorModel sensorModel, Polygon area)
    {
        double viewSize = GeneratorUtils.groundViewInMeters(vehicleModel, sensorModel);
        Bounds bounds = area.getBounds();
        double longestSide = Math.max(bounds.getWidth(), bounds.getHeight());
        int legs = (int)(Math.floor(longestSide / (viewSize * 2)));
        legs = (legs == 0) ? 1 : legs;
        double distance = viewSize / 2;
        List<Polygon> polygons = new ArrayList<>();
        Polygon currentPolygon = area;
        for(int i = 0; i < legs; ++i){
            currentPolygon = offset(currentPolygon, distance);
            polygons.add(currentPolygon);
            if(currentPolygon.getSegments().size() < 3){
                break;
            }
        }

        List<Point> path = new ArrayList<>();
        for(Polygon polygon: polygons){
            path.addAll(polygon.getPoints());
        }

        return new FlightPlan(vehicleModel, sensorModel, new FlightPath(path), area);
    }

    public Polygon offset(Polygon polygon, double amount){
        List<Segment> segments = polygon.getSegments()
                .stream()
                .map(s -> offsetToTheRight(s, amount))
                .collect(Collectors.toList());
        List<Segment> prunedSegments = pruneOverlaps(segments);
        List<Point> mergedPoints = mergeIntersections(prunedSegments);
        return new Polygon(mergedPoints);
    }

    public List<Segment> pruneOverlaps(List<Segment> segments){
        List<Segment> pruned = new ArrayList<>();
        for(int i = 0; i < segments.size(); ++i)
        {
            Segment prev = segments.get((i - 1 + segments.size()) % segments.size());
            Segment cur = segments.get(i);
            Segment next = segments.get((i + 1) % segments.size());

            if(!GeneratorUtils.intersects(prev, next)){
                pruned.add(cur);
            }
        }
        return pruned;
    }

    public List<Point> mergeIntersections(List<Segment> segments){
        List<Point> points = new ArrayList<>();
        for(int i = 0; i < segments.size(); ++i){
            Segment prev = segments.get((i - 1 + segments.size()) % segments.size());
            Segment cur = segments.get(i);
            if(GeneratorUtils.intersects(prev, cur)){
                points.add(GeneratorUtils.intersection(prev, cur));
            } else {
                points.add(cur.getStart());
            }
        }
        return points;
    }

    public Segment offsetToTheRight(Segment segment, double amount){
        Point offset = computeNormal(segment).scale(amount);
        Point p1New = segment.getStart().plus(offset);
        Point p2New = segment.getEnd().plus(offset);
        return new Segment(p1New, p2New);
    }

    public Point computeNormal(Segment segment){
        Point dir = segment.getEnd().minus(segment.getStart());
        return dir.rotate(-(Math.PI / 2.0)).normalize();
    }

    @Override
    public String toString()
    {
        return this.getClass().getSimpleName();
    }
}
