package com.cra.princess.simulation;

public interface BathymetrySource {
    double depth(double lat, double lon);
    
    static BathymetrySource nullSource  = new BathymetrySource() {        
        @Override
        public double depth(double lat, double lon) {
            return Double.MAX_VALUE;
        }
    };
}
