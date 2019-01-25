package com.cra.princess.simulation.events;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.messaging.PowerPerturbation;

public class PowerPerturbationEvent extends TimedEvent {
	public PowerPerturbation perturb = new PowerPerturbation();
	
	
	@Override
	public void configure(JsonObject o) {
	    super.configure(o);
		perturb.timestamp = this.getEventTime();
		if (o.getJsonNumber("energyDrain") != null)
			perturb.energyDrain = o.getJsonNumber("energyDrain").doubleValue();
		if (o.getJsonNumber("powerSpike") != null)
			perturb.powerSpike = o.getJsonNumber("powerSpike").doubleValue();	
	}


	@Override
	public Object getPayload() {
		return perturb;
	}


    @Override
    public String toString() {
        return "PowerPerturbation [perturb=" + perturb + ", time=" + time + "]";
    }


    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("type", PowerPerturbationEvent.class.getName())
            .add("config", Json.createObjectBuilder()
                    .add("time", ((double)this.getEventTime())*1e-3) // convert from millis to seconds                    
                    .add("powerSpike", perturb.powerSpike)
                    .add("energyDrain", perturb.energyDrain
                    ).build() 
            ).build();                                 
    }

}
