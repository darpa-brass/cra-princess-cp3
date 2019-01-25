package com.cra.princess.pathplanner.util;


public class LatLonConverter {

    private static final double EARTH_RADIUS = 6371008.8; // m WGS84 mean radius
    // private static final double LAT_DEGREE_METER =  180.0 / (2.0*Math.PI*EARTH_RADIUS);
    private static final double LAT_DEGREE_METER =  180.0 / (Math.PI*EARTH_RADIUS);

    protected final double originLatDeg;
    protected final double originLonDeg;
    protected final double lonDegreeMeter;

    public LatLonConverter(double originLatDeg, double originLonDeg) {
        this.originLatDeg = originLatDeg;
        this.originLonDeg = originLonDeg;
        lonDegreeMeter =  LAT_DEGREE_METER / Math.cos(Math.toRadians(originLatDeg));
    }

    public double[] getLatLon(double northing, double easting) {
        double lat = originLatDeg + northing * LAT_DEGREE_METER;
        double lon = originLonDeg + easting * lonDegreeMeter;
        return new double[]{lat, lon};
    }

    public double[] getXY(double lat, double lon) {
        double x = (lon - originLonDeg)/lonDegreeMeter;
        double y = (lat - originLatDeg)/LAT_DEGREE_METER;
        return new double[]{x,y};
    }
}
