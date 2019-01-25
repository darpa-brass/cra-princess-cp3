package com.cra.princess.simulation.config;

/**
 * Represents a point in the ocean, including depth.
 *
 */
public class ConfigLocation {
    private final double latitude;
    private final double longitude;
    private final double depth;
    
    public ConfigLocation(double latitude, double longitude, double depth) {
        this.latitude = latitude;
        this.longitude = longitude;
        this.depth = depth;
    }

    public double getLatitude() {
        return latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public double getDepth() {
        return depth;
    }

    @Override
    public String toString() {
        return "ConfigLocation [latitude=" + latitude + ", longitude=" + longitude + ", depth=" + depth + "]";
    }
}
