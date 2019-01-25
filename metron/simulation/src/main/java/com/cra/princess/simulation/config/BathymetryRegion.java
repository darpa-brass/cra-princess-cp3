package com.cra.princess.simulation.config;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public class BathymetryRegion implements JsonConfigurable, JsonEncodable {
    protected double sLat;
    protected double wLon;
    protected double nLat;
    protected double eLon;
    private double depth;    

    public double getsLat() {
        return sLat;
    }

    public BathymetryRegion setsLat(double sLat) {
        this.sLat = sLat;
        return this;
    }

    public double getwLon() {
        return wLon;
    }

    public BathymetryRegion setwLon(double wLon) {
        this.wLon = wLon;
        return this;
    }

    public double getnLat() {
        return nLat;
    }

    public BathymetryRegion setnLat(double nLat) {
        this.nLat = nLat;
        return this;
    }

    public double geteLon() {
        return eLon;
    }

    public BathymetryRegion seteLon(double eLon) {
        this.eLon = eLon;
        return this;
    }
    
    public BathymetryRegion setDepth(double depth) {
        this.depth = depth;
        return this;
    }
    public double getDepth()
    {
    	return depth;
    }    
    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("sLat", sLat)
            .add("wLon", wLon)
            .add("nLat", nLat)
            .add("eLon", eLon)
            .add("depth", depth).build();
    }
    
    @Override
    public void configure(JsonObject o) {
        sLat = o.getJsonNumber("sLat").doubleValue();
        wLon = o.getJsonNumber("wLon").doubleValue();
        nLat = o.getJsonNumber("nLat").doubleValue();
        eLon = o.getJsonNumber("eLon").doubleValue();
        depth = o.getJsonNumber("depth").doubleValue();        
    }
    @Override
    public String toString() {
        return "BathymetryRegion [sLat=" + sLat + ", wLon=" + wLon + ", nLat=" + nLat + ", eLon=" + eLon + ", depth=" + depth + "]";
    }
}
