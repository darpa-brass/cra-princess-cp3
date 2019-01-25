package com.cra.princess.simulation.events;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.messaging.SensorPerturbation;

public class SensorPerturbationEvent extends TimedEvent {
	public SensorPerturbation perturb = new SensorPerturbation();
	
	
	@Override
	public void configure(JsonObject o) {
	    super.configure(o);
		perturb.name = o.getString("name");
		perturb.bias = o.getJsonNumber("bias").doubleValue();
		perturb.noiseDeviation = o.getJsonNumber("noiseDev").doubleValue();
		perturb.anchor = o.getJsonNumber("anchor").doubleValue();
		perturb.anchorProbability = o.getJsonNumber("anchorProbability").doubleValue();
				
	}


	@Override
	public Object getPayload() {
		return perturb;
	}


    @Override
    public String toString() {
        return "SensorPerturbationEvent [perturb=" + perturb + ", time=" + time + "]";
    }


    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("type", SensorPerturbationEvent.class.getName())
            .add("config", Json.createObjectBuilder()
                    .add("time", ((double)this.getEventTime())*1e-3) // convert from millis to seconds
                    .add("name", perturb.name)
                    .add("bias", perturb.bias)
                    .add("noiseDev", perturb.noiseDeviation)
                    .add("anchor", perturb.anchor)
                    .add("anchorProbability", perturb.anchorProbability).build()
             ).build();
    }

}
