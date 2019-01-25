package com.cra.sim.sensor;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.RpmMessage;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;

public class RpmSensor implements JsonConfigurable, MessageHandler<GroundTruthMessage>, TimeStepped, Sensor {

	protected AdditiveSensorCorruptor corruptor;	
	private GroundTruthMessage cachedState = null;
    private long lastMessageTime = 0;
    private long messageInterval = 200;
	
    public RpmSensor() {
        EventDispatcher.registerConsumer(GroundTruthMessage.class, this);
        TimeManager.addStepper(this);
    }
    

	@Override
	public void initialize() {		
	}

	@Override
	public void update() {
		long elapsed = TimeManager.now() - lastMessageTime;
		if (elapsed >= messageInterval && cachedState != null) {
			lastMessageTime = TimeManager.now();
			RpmMessage measurement = getMeasurement(cachedState);
			EventDispatcher.publishEvent(measurement);
			JmsManager.sendRpmMessage(measurement);
		}
	}
	
	private RpmMessage getMeasurement(GroundTruthMessage state) {
		RpmMessage message = new RpmMessage();		
		message.rpm = corruptor.corrupt(state.rpm);
		message.timestamp = lastMessageTime;
		return message;
	}

	@Override
	public void reset() {
		cachedState = null;
		lastMessageTime = 0;
	}

	@Override
	public void stop() {		
	}

	@Override
	public void handleMessage(GroundTruthMessage message) {
		cachedState = message;		
	}

	@Override
	public void configure(JsonObject o) {		        
		corruptor = new AdditiveSensorCorruptor("rpm");
		corruptor.configure(o);          		       
	}


	@Override
	public void register(SensorManager manager) {
		manager.register(corruptor.getName(), corruptor);
	}

}
