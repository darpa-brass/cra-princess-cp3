package com.metsci.dynamic.simple;

import java.util.logging.Logger;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.PowerMessage;
import com.cra.princess.messaging.PowerPerturbation;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;

public class PowerModel implements 
JsonConfigurable, 
TimeStepped {
	private final static Logger LOGGER = Logger.getLogger(PowerModel.class.getName());
	protected GroundTruthMessage state = null;
	protected double oldPower = 0;
	protected long oldTime = -1;
	protected double powerOverride = -1;
	protected long lastMessageTime = -1L;
	protected long messageInterval = 1000L;
	protected double baselineEnergy;
	protected double energyRemaining = 0;
	protected double propulsorCoefficient  = 0;
	protected double hotelLoad = 0;
	protected Object mutex = new Object();
	
	public MessageHandler<GroundTruthMessage> truthHandle = new MessageHandler<GroundTruthMessage>() {
		@Override
		public void handleMessage(GroundTruthMessage message) {
			state = message;
		}	
	};
	public MessageHandler<PowerPerturbation> powerHandle = new MessageHandler<PowerPerturbation>() {
		 @Override
		 public void handleMessage(PowerPerturbation message) {
			 synchronized(mutex) {
				 energyRemaining -= message.energyDrain;
				 powerOverride = message.powerSpike;
			 }
		 }
	};
	
	public PowerModel() {
		EventDispatcher.registerConsumer(GroundTruthMessage.class, truthHandle);
		EventDispatcher.registerConsumer(PowerPerturbation.class, powerHandle);
		TimeManager.addStepper(this);
	}
	
	protected double getPower(GroundTruthMessage state) {
		return hotelLoad + propulsorCoefficient*Math.pow(state.rpm, 3);
		// TODO actuators and sensors?
	}
	
	@Override
	public void initialize() {
		reset();
	}

	@Override
	public void update() {
		if (state == null) {
			return;
		}
		if (oldTime == -1) {
			oldTime = TimeManager.now();
			oldPower = getPower(state);
			return;
		}
		// Trapezoid rule accounting for energy loss
		double dt = 1e-3 * (double)(state.timestamp - oldTime);
		synchronized(mutex) {
			double newPower = getPower(state);
			if (this.powerOverride > 0) {
				newPower = this.powerOverride;
				this.powerOverride = 0;
			}
			energyRemaining -= 0.5*dt*(newPower + oldPower);
			oldPower = newPower;
			oldTime = TimeManager.now();
		        
			if (TimeManager.now() - lastMessageTime >= messageInterval) {
				lastMessageTime = TimeManager.now();
				PowerMessage msg = new PowerMessage();
				msg.timestamp = oldTime;
				msg.power_W = oldPower;
				msg.energyRemaining_J = energyRemaining;
				EventDispatcher.publishEvent(msg);        
				JmsManager.sendPowerMessage(msg);
			}
		}
	}

	@Override
	public void reset() {
		oldPower = 0;
		oldTime = -1;
		powerOverride = 0;
		lastMessageTime = -1;
		energyRemaining = baselineEnergy;
		state = null;
	}

	@Override
	public void stop() {
	}

	@Override
	public void configure(JsonObject o) {
		if (o.containsKey("baselineEnergy")) {
			baselineEnergy = o.getJsonNumber("baselineEnergy").doubleValue();
		} else {			
			LOGGER.warning("No baseline energy given!");
		}
		if (o.containsKey("propulsorCoefficient")) {
			propulsorCoefficient = o.getJsonNumber("propulsorCoefficient").doubleValue();
		} else {			
			LOGGER.warning("No propulsorCoefficient given!");
		}				
		if (o.containsKey("hotelLoad")) {
			hotelLoad = o.getJsonNumber("hotelLoad").doubleValue();
		} else {			
			LOGGER.warning("No hotel load given!");
		} 
	}
	 

}
