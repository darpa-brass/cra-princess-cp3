package com.cra.princess.pathplanner.generators;

import com.cra.princess.pathplanner.Point;
import com.cra.princess.pathplanner.Polygon;
import com.cra.princess.pathplanner.Segment;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

public class GeneratorUtilsTest
{
    @Test
    public void testInside(){
        List<Point> points = new ArrayList<>();
        points.add(new Point(10, 10));
        points.add(new Point(50, 70));
        points.add(new Point(300, 100));
        points.add(new Point(350, 10));
        Polygon polygon = new Polygon(points);

        Assert.assertTrue(GeneratorUtils.inside(new Point(50, 20), polygon));
        Assert.assertTrue(GeneratorUtils.inside(new Point(200, 50), polygon));

        Assert.assertFalse(GeneratorUtils.inside(new Point(50, -10), polygon));
        Assert.assertFalse(GeneratorUtils.inside(new Point(200, 100), polygon));
    }

    @Test
    public void testIntersections()
    {
        List<Point> points = new ArrayList<>();
        points.add(new Point(0, 0));
        points.add(new Point(0, 10));
        points.add(new Point(10, 10));
        points.add(new Point(10, 0));
        Polygon polygon = new Polygon(points);

        Segment segment = new Segment(new Point(-1, 5), new Point(11, 5));
        List<Point> intersections = GeneratorUtils.intersections(segment, polygon);
        Assert.assertEquals(2, intersections.size());
        Assert.assertEquals(0.0, intersections.get(0).getX(), 0.0001);
        Assert.assertEquals(5.0, intersections.get(0).getY(), 0.0001);
        Assert.assertEquals(10.0, intersections.get(1).getX(), 0.0001);
        Assert.assertEquals(5.0, intersections.get(1).getY(), 0.0001);
    }
}
