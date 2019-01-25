package com.cra.princess.pathplanner;

public class Point
{
    public static final Point INVALID = new Point(Double.NaN, Double.NaN);
    private final double x,y;

    public Point(double x, double y)
    {
        this.x = x;
        this.y = y;
    }

    public double getX()
    {
        return x;
    }

    public double getY()
    {
        return y;
    }

    public Point minus(Point other){
        return new Point(this.x - other.x, this.y - other.y);
    }

    public Point plus(Point other){
        return new Point(this.x + other.x, this.y + other.y);
    }

    public Point scale(double v){
        return new Point(v * this.x, v * this.y);
    }

    public double magnitude(){
        return Math.sqrt(x*x+ y*y);
    }

    public Point normalize(){
        double mag = magnitude();
        return new Point(x / mag, y / mag);
    }

    public double cross(Point other){
        return this.x * other.y - other.x * this.y;
    }

    public Point invert(){
        return new Point(1.0 / x, 1.0 / y);
    }

    public double distance(Point other) {
        double dx = x - other.x;
        double dy = y - other.y;
        return Math.sqrt(dx*dx + dy*dy);
    }

    public Point rotate(double angleInRadians){
        double s = Math.sin(angleInRadians);
        double c = Math.cos(angleInRadians);
        double nx = x * c - y * s;
        double ny = x * s + y * c;
        return new Point(nx, ny);
    }

    @Override
    public String toString()
    {
        return String.format("Point{x=%.1f, y=%.1f}", x, y);
    }
}
