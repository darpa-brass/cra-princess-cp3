package com.cra.princess.pathplanner;

public class Bounds
{
    private final double minX, maxX, minY, maxY;
    private final double width, height;

    public Bounds(double minX, double maxX, double minY, double maxY)
    {
        this.minX = minX;
        this.maxX = maxX;
        this.minY = minY;
        this.maxY = maxY;
        this.width = maxX - minX;
        this.height = maxY - minY;
    }

    public double getMinX()
    {
        return minX;
    }

    public double getMaxX()
    {
        return maxX;
    }

    public double getMinY()
    {
        return minY;
    }

    public double getMaxY()
    {
        return maxY;
    }

    public double getWidth()
    {
        return width;
    }

    public double getHeight()
    {
        return height;
    }

    public Bounds union(Bounds other){
        double minX = Math.min(other.minX, this.minX);
        double maxX = Math.max(other.maxX, this.maxX);
        double minY = Math.min(other.minY, this.minY);
        double maxY = Math.max(other.maxY, this.maxY);
        return new Bounds(minX, maxX, minY, maxY);
    }

    public Point centroid(){
        return new Point(minX + width / 2.0, minY + height / 2.0);
    }

    public Bounds expand(double scale){
        Point center = centroid();
        double halfWidth = (width / 2.0) * scale;
        double halfHeight = (height / 2.0) * scale;
        return new Bounds(center.getX() - halfWidth, center.getX() + halfWidth, center.getY() - halfHeight, center.getY() + halfHeight);
    }

    @Override
    public String toString()
    {
        return String.format("Bounds{minX=%.1f, maxX=%.1f, minY=%.1f, maxY=%.1f, width=%.1f, height=%.1f", minX, maxX, minY, maxY, width, height);
    }
}
