package com.cra.princess.simulation.config;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public class CurrentRegion implements JsonConfigurable, JsonEncodable {
    protected double sLat;
    protected double wLon;
    protected double nLat;
    protected double eLon;
    private double vE;
    private double vN;

    public double getsLat() {
        return sLat;
    }

    public CurrentRegion setsLat(double sLat) {
        this.sLat = sLat;
        return this;
    }

    public double getwLon() {
        return wLon;
    }

    public CurrentRegion setwLon(double wLon) {
        this.wLon = wLon;
        return this;
    }

    public double getnLat() {
        return nLat;
    }

    public CurrentRegion setnLat(double nLat) {
        this.nLat = nLat;
        return this;
    }

    public double geteLon() {
        return eLon;
    }

    public CurrentRegion seteLon(double eLon) {
        this.eLon = eLon;
        return this;
    }
    public double getvE() {
        return vE;
    }
    public CurrentRegion setvE(double vE) {
        this.vE = vE;
        return this;
    }
    public double getvN() {
        return vN;
    }
    public CurrentRegion setvN(double vN) {
        this.vN = vN;
        return this;
    }
    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("sLat", sLat)
            .add("wLon", wLon)
            .add("nLat", nLat)
            .add("eLon", eLon)
            .add("vE", vE)
            .add("vN", vN).build();
    }
    
    @Override
    public void configure(JsonObject o) {
        sLat = o.getJsonNumber("sLat").doubleValue();
        wLon = o.getJsonNumber("wLon").doubleValue();
        nLat = o.getJsonNumber("nLat").doubleValue();
        eLon = o.getJsonNumber("eLon").doubleValue();
        vE = o.getJsonNumber("vE").doubleValue();
        vN = o.getJsonNumber("vN").doubleValue();
    }
    @Override
    public String toString() {
        return "CurrentRegion [sLat=" + sLat + ", wLon=" + wLon + ", nLat=" + nLat + ", eLon=" + eLon + ", vE=" + vE + ", vN=" + vN + "]";
    }
}
