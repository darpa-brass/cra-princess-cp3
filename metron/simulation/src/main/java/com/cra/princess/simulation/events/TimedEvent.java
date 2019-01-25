package com.cra.princess.simulation.events;

import javax.json.JsonObject;

import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonEncodable;

public abstract class TimedEvent implements JsonConfigurable, JsonEncodable {
	protected long time;
	
	public long getEventTime() {
		return time;
	}
	
	public void setEventTime(long simMillis) {
		time = simMillis;
	}
	
	@Override
	public void configure(JsonObject o) {
		// Convert time from seconds to millis
		time = (long) (1000.0 * o.getJsonNumber("time").doubleValue());
	}
	
	public abstract Object getPayload(); 
}
