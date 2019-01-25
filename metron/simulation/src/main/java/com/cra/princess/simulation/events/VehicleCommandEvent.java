package com.cra.princess.simulation.events;

import javax.json.Json;
import javax.json.JsonObject;

import com.cra.princess.messaging.VehicleCommand;

public class VehicleCommandEvent extends TimedEvent {
	public VehicleCommand command = new VehicleCommand();
	
	
	@Override
	public void configure(JsonObject o) {
	    super.configure(o);		
		command.headingTarget = o.getJsonNumber("headingTarget").doubleValue();
		command.depthTarget = o.getJsonNumber("depthTarget").doubleValue();
		command.speedTarget = o.getJsonNumber("speedTarget").doubleValue();					
	}


	@Override
	public Object getPayload() {
		return command;
	}


    @Override
    public String toString() {
        return "VehicleCommandEvent [command=" + command + ", time=" + time + "]";
    }


    @Override
    public JsonObject getJsonObject() {
        return Json.createObjectBuilder()
            .add("type", VehicleCommandEvent.class.getName())
            .add("config", Json.createObjectBuilder()
                    .add("time", ((double)this.getEventTime())*1e-3) // convert from millis to seconds
                    .add("headingTarget", command.headingTarget)
                    .add("depthTarget", command.depthTarget)
                    .add("speedTarget", command.speedTarget)            
             ).build();
    }

}
