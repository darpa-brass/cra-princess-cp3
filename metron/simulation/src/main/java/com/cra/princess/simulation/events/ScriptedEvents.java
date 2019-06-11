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
	
	private void sortTimeline() {
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
	
	public void configure(JsonArray array) {			
		timeline = new ArrayList<TimedEvent>();
		JsonConfigurableFactory fac = new JsonConfigurableFactory();
		if (array == null)
			return;
		for (JsonValue maybeEventJson : array) {
			JsonObject eventJson = (JsonObject) maybeEventJson;
			if (eventJson != null) {
				TimedEvent event = (TimedEvent) fac.construct(eventJson);
				timeline.add(event);
			}
		}
		sortTimeline();
	}
	
	public void add(TimedEvent event) {
		timeline.add(event);
		sortTimeline();
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
		    timeline.remove(0);
		    EventDispatcher.publishEvent(event.getPayload());
            LOGGER.info(String.format("T%d D%d: %s", now, (now - event.getEventTime() ), event.getPayload().toString()));            
		}
	}

	@Override
	public void reset() {
		initialize();
	}

	@Override
	public void stop() {
		if (!timeline.isEmpty()) {			
			StringBuilder sb = new StringBuilder();
			sb.append("Simulation ended with " + timeline.size() + " scripted events left to dispatch:\n");
			int i=0;
			for (TimedEvent e : timeline) {
				sb.append(String.format("%d: T%d D%d: %s\n", i++, now, (now - e.getEventTime() ), e.getPayload().toString()));
			}
			LOGGER.info(sb.toString());
		}
	}

}
