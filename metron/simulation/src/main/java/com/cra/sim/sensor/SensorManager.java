package com.cra.sim.sensor;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import javax.json.JsonArray;
import javax.json.JsonException;
import javax.json.JsonObject;
import javax.json.JsonValue;

import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SensorPerturbation;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.JsonConfigurableFactory;
import com.cra.princess.simulation.events.EventDispatcher;

public class SensorManager implements 
MessageHandler<SensorPerturbation>,
JsonConfigurable
{
	private final static Logger LOGGER = Logger.getLogger(SensorManager.class.getName());
	
	protected Map<String, MessageHandler<SensorPerturbation> > perturbationConsumers = new HashMap<>();
	protected List<Sensor> sensors = new ArrayList<Sensor>();
	
	public SensorManager() {
		EventDispatcher.registerConsumer(SensorPerturbation.class, this);
	}
	
	public void register(String name, MessageHandler<SensorPerturbation> consumer) {
		perturbationConsumers.put(name, consumer);
	}

	
	@Override
	public void handleMessage(SensorPerturbation message) {
		if (perturbationConsumers.containsKey(message.name)) {
			perturbationConsumers.get(message.name).handleMessage(message);
			JmsManager.sendSensorPerturbation(message);
		} else {
			LOGGER.fine("Event for " + message.name + ", but no registered consumer:\n\t" + message);
		}		
	}
	
	public void configure(JsonArray o) {
		JsonConfigurableFactory fac = new JsonConfigurableFactory();        
        for (JsonValue s : o) { 
        	Sensor sensor = (Sensor) fac.construct((JsonObject) s);
        	sensors.add(sensor);
        	sensor.register(this);
        }		
	}

	@Override
	public void configure(JsonObject o) {
		try {
			JsonArray array = o.getJsonArray("sensors");
			configure(array);
		} catch (JsonException e) {
			throw new ConfigurationException("Missing sensor array data");
		}
	}
}
