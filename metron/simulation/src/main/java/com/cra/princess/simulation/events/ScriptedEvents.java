package com.cra.princess.simulation.events;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.logging.Logger;

import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonValue;

import com.cra.princess.simulation.JsonConfigurableFactory;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;

public class ScriptedEvents implements TimeStepped {
	private final static Logger LOGGER = Logger.getLogger(ScriptedEvents.class.getName());
	protected long time0 = 0;
	protected long now;
	protected ArrayList<TimedEvent> timeline;
	
	public ScriptedEvents(JsonArray o) {
		TimeManager.addStepper(this);
		configure(o);
	}
		
	public void configure(JsonArray array) {	
		timeline = new ArrayList<TimedEvent>();
		JsonConfigurableFactory fac = new JsonConfigurableFactory();
		for (JsonValue thing : array) {
			JsonObject o = (JsonObject) thing;
			TimedEvent event = (TimedEvent) fac.construct(o);
			timeline.add(event);
		}
		Comparator<TimedEvent> comp = new Comparator<TimedEvent>() {
			@Override
			public int compare(TimedEvent arg0, TimedEvent arg1) {
				long delta = arg0.getEventTime() - arg1.getEventTime();
				if (delta < 0)
					return -1;
				if (delta == 0)
					return 0;
				return 1;				
			}			
		};
		Collections.sort(timeline, comp);
	}

	@Override
	public void initialize() {		
		time0 = TimeManager.now();
	}

	@Override
	public void update() {
		if (time0 == 0)
			initialize();
		long now = TimeManager.now() - time0;
		while (!timeline.isEmpty() && timeline.get(0).getEventTime() <= now) {
		    TimedEvent event = timeline.get(0);
		    EventDispatcher.publishEvent(event.getPayload());
            LOGGER.info(String.format("T%d D%d: %s", now, (now - timeline.get(0).getEventTime() ), event.getPayload().toString()));
            timeline.remove(0);
		}
	}

	@Override
	public void reset() {
		initialize();
	}

	@Override
	public void stop() {
		if (!timeline.isEmpty()) {
			LOGGER.info("Simulation ended with " + timeline.size() + " scripted events left to dispatch.");
		}
	}

}
