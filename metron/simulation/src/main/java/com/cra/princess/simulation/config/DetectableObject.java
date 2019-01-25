package com.cra.princess.simulation.config;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public class DetectableObject implements JsonConfigurable, JsonEncodable {
    protected double lat;
    protected double lon;
    
    public double getLat() {
        return lat;
    }
    
    public double getLon() {
        return lon;
    }   
    
    public DetectableObject setLat(double lat) {
        this.lat = lat;
        return this;
    }

    public DetectableObject setLon(double lon) {
        this.lon = lon;
        return this;
    }

    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("lat", lat)
            .add("lon", lon).build();
    }
    
    @Override
    public void configure(JsonObject o) {
        lat = o.getJsonNumber("lat").doubleValue();
        lon = o.getJsonNumber("lon").doubleValue();               
    }
    @Override
    public String toString() {
        return "DetectableObject [lat=" + lat + ", lon=" + lon + "]";
    }
}
