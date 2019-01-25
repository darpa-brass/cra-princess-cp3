package com.cra.princess.simulation.config;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public class SensorModel implements JsonConfigurable, JsonEncodable {
    private String name;
    private double bias;
    private double noiseDev;
    private double anchor;
    private double anchorProbability;
    
    public String getName() {
        return name;
    }
    public SensorModel setName(String name) {
        this.name = name;
        return this;
    }
    public double getBias() {
        return bias;
    }
    public SensorModel setBias(double bias) {
        this.bias = bias;
        return this;
    }
    public double getNoiseDev() {
        return noiseDev;
    }
    public SensorModel setNoiseDev(double noiseDev) {
        this.noiseDev = noiseDev;
        return this;
    }
    public double getAnchor() {
        return anchor;
    }
    public SensorModel setAnchor(double anchor) {
        this.anchor = anchor;
        return this;
    }
    public double getAnchorProbability() {
        return anchorProbability;
    }
    public SensorModel setAnchorProbability(double anchorProbability) {
        this.anchorProbability = anchorProbability;
        return this;
    }
    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("name", name)
            .add("bias", bias)
            .add("noiseDev", noiseDev)
            .add("anchor", anchor)
            .add("anchorProbability", anchorProbability).build();
    }
    
    @Override
    public void configure(JsonObject o) {
        name = o.getString("name");
        bias = o.getJsonNumber("bias").doubleValue();
        noiseDev = o.getJsonNumber("noiseDev").doubleValue();
        anchor = o.getJsonNumber("anchor").doubleValue();
        anchorProbability = o.getJsonNumber("anchorProbability").doubleValue();
    }
    @Override
    public String toString() {
        return "SensorErrorModel [name = " + name + ", bias=" + bias + ", noiseDev=" + noiseDev + ", anchor=" + anchor + ", anchorProbability=" + anchorProbability + "]";
    }
}
