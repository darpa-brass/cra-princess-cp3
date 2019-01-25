package com.cra.princess.simulation;

import java.awt.geom.Point2D;

public interface CurrentSource {
    Point2D current(double lat, double lon, double depth);
    
    static CurrentSource nullSource  = new CurrentSource() {
        Point2D zero = new Point2D.Double();
        @Override
        public Point2D current(double lat, double lon, double depth) {
            return zero;
        }
    };
}
