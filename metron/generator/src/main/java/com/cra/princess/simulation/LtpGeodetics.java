package com.cra.princess.simulation;

public class LtpGeodetics {    
    private static final double EARTH_EQUI_RADIUS_M = 6378137.0;
    private static final double EARTH_ECCENTRICIY = 0.08181919;    
    
    protected final double originLatDeg;
    protected final double originLonDeg;
    protected final double latDegreeMeter;
    protected final double lonDegreeMeter;
    protected double[] latLon = new double[2];
    protected double[] northEast = new double[2];
    
    public LtpGeodetics(double originLatDeg, double originLonDeg) {
        this.originLatDeg = originLatDeg;
        this.originLonDeg = originLonDeg;
        
        double sinLat = Math.sin(originLatDeg*Math.PI/180.0);
        double cosLat = Math.cos(originLatDeg*Math.PI/180.0);
        double d =Math.sqrt(1.0 - EARTH_ECCENTRICIY*EARTH_ECCENTRICIY*sinLat*sinLat);
        double Rn = EARTH_EQUI_RADIUS_M*(1.0 - EARTH_ECCENTRICIY*EARTH_ECCENTRICIY)/(d*d*d);
        double Re = EARTH_EQUI_RADIUS_M/d;
        latDegreeMeter = 180.0/(Math.PI * Rn);
        lonDegreeMeter = 180.0/(Math.PI * Re * cosLat);        
    }
    
    public double[] getLatLon(double northing, double easting) {
        latLon[0] = originLatDeg + northing * latDegreeMeter;        
        latLon[1] = originLonDeg + easting * lonDegreeMeter;
        return latLon;
    }

    public double[] getNorthingEasting(double lat, double lon) {
        northEast[0] = (lat - originLatDeg)/latDegreeMeter;
        northEast[1] = (lon - originLonDeg)/lonDegreeMeter;
        return northEast;
    }

    public static void main(String[] args) {
        LtpGeodetics ltp = new LtpGeodetics(32, 170);
        double[] latLon = ltp.getLatLon(5000/Math.sqrt(2.0), 5000/Math.sqrt(2.0));
        System.out.format("5000 m at 45 deg azi from 32, 170 is %.14g, %.14g", latLon[0], latLon[1]);
    }
}
