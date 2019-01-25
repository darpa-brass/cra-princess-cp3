package com.cra.princess.simulation.config;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public class Region  implements JsonConfigurable, JsonEncodable {
    private double sLat;
    private double wLon;
    private double nLat;
    private double eLon;

    public double getsLat() {
        return sLat;
    }

    public void setsLat(double sLat) {
        this.sLat = sLat;
    }

    public double getwLon() {
        return wLon;
    }

    public void setwLon(double wLon) {
        this.wLon = wLon;
    }

    public double getnLat() {
        return nLat;
    }

    public void setnLat(double nLat) {
        this.nLat = nLat;
    }

    public double geteLon() {
        return eLon;
    }

    public void seteLon(double eLon) {
        this.eLon = eLon;
    }

    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("sLat", sLat)
            .add("wLon", wLon)
            .add("nLat", nLat)
            .add("eLon", eLon).build();
    }
    
    @Override
    public void configure(JsonObject o) {
        sLat = o.getJsonNumber("sLat").doubleValue();
        wLon = o.getJsonNumber("wLon").doubleValue();
        nLat = o.getJsonNumber("nLat").doubleValue();
        eLon = o.getJsonNumber("eLon").doubleValue();
    }
}