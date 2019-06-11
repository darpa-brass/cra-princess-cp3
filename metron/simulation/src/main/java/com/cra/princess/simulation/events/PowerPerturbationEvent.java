package com.cra.princess.simulation.events;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.messaging.RemusBatteryPerturbation;

public class PowerPerturbationEvent extends TimedEvent {
	public RemusBatteryPerturbation perturb = new RemusBatteryPerturbation(0, 0, 0);
	
	public PowerPerturbationEvent() {
		
	}
	
	public PowerPerturbationEvent(RemusBatteryPerturbation rawPerturbation) {
		this.perturb = rawPerturbation;
	}
	
	@Override
	public void configure(JsonObject o) { 
	    super.configure(o);
		long timestamp = this.getEventTime();
		double energyReduction = 0.0;
		double sensorPower = 0.0;
		if (o.getJsonNumber("energyReduction") != null) {
			energyReduction = o.getJsonNumber("energyReduction").doubleValue();
		} 
		if (o.getJsonNumber("sensorPower") != null) {
			sensorPower = o.getJsonNumber("sensorPower").doubleValue();					
		}
		perturb = new RemusBatteryPerturbation(energyReduction, sensorPower, timestamp);
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
                    .add("energyReduction", perturb.getEnergyReduction())
                    .add("sensorPower", perturb.getSensorPower())
                    .build() 
            ).build();                                 
    }

}

