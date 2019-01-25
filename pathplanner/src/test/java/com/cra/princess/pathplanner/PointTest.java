package com.cra.princess.pathplanner;

import com.cra.princess.pathplanner.Point;
import org.junit.Assert;
import org.junit.Test;

public class PointTest
{
    @Test
    public void testPoint_rotation()
    {
        Point p1 = new Point(1.0, 0.0);

        Point p2 = p1.rotate(Math.PI / 2);
        Assert.assertEquals(0.0, p2.getX(), 0.00001);
        Assert.assertEquals(1.0, p2.getY(), 0.00001);

        Point p3 = p2.rotate(Math.PI / 2);
        Assert.assertEquals(-1.0, p3.getX(), 0.00001);
        Assert.assertEquals(0.0, p3.getY(), 0.00001);

        Point p4 = p3.rotate(Math.PI / 2);
        Assert.assertEquals(0.0, p4.getX(), 0.00001);
        Assert.assertEquals(-1.0, p4.getY(), 0.00001);

        Point pNeg = p1.rotate(- (Math.PI / 2));
        Assert.assertEquals(0.0, pNeg.getX(), 0.00001);
        Assert.assertEquals(-1.0, pNeg.getY(), 0.00001);
    }
}
