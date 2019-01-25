package com.cra.princess.pathplanner;

public class Segment
{
    private final Point start, end;

    public Segment(Point start, Point end)
    {
        this.start = start;
        this.end = end;
    }

    public Point getStart()
    {
        return start;
    }

    public Point getEnd()
    {
        return end;
    }

    public Segment flip(){
        return new Segment(end, start);
    }

    @Override
    public String toString()
    {
        return "Segment{" +
                "start=" + start +
                ", end=" + end +
                '}';
    }
}
