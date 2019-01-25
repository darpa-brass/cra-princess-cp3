package com.cra.sim.sensor;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.simulation.ConfigurationException;

public class BasicObjectDetectionModel extends ObjectDetectionModel {

	double Pd = 1;
	
	public BasicObjectDetectionModel() {
	    super();
	}
	
	@Override
    public boolean detect(double[] op) {
		return (generator.nextDouble() < Pd);			
	}

	@Override
	public void configure(JsonObject o) {
		Pd = o.getJsonNumber("Pd").doubleValue();
		ConfigurationException.check("Pd", Pd, 0, 1);
	}

    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
                .add("type", BasicObjectDetectionModel.class.getName())
                .add("config", Json.createObjectBuilder()
                        .add("Pd", Pd)
                        .build())
                .build();
    }

    public double getPd() {
        return Pd;
    }

    public void setPd(double pd) {
        Pd = pd;
    }

    @Override
    public String toString() {
        return "BasicObjectDetectionModel [Pd=" + Pd + "]";
    }

}
