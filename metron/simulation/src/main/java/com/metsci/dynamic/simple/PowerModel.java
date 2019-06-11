package com.metsci.dynamic.simple;

import java.util.logging.Logger;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.PowerMessage;
import com.cra.princess.messaging.RemusBatteryPerturbation;
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
	protected long lastMessageTime = -1L;
	protected long messageInterval = 1000L;
	protected double baselineEnergy;
	protected double energyRemaining = 0;
	protected double propulsorCoefficient  = 0;
	protected double rudderCoefficient = 0;
	protected double elevatorCoefficient = 0;
	protected double sensorPower = 0;
	protected double hotelLoad = 0;
	protected Object mutex = new Object();
	
	public MessageHandler<GroundTruthMessage> truthHandle = new MessageHandler<GroundTruthMessage>() {
		@Override
		public void handleMessage(GroundTruthMessage message) {
			state = message;
		}	
	};
	public MessageHandler<RemusBatteryPerturbation> powerHandle = new MessageHandler<RemusBatteryPerturbation>() {
		 @Override
		 public void handleMessage(RemusBatteryPerturbation message) {
			 synchronized(mutex) {
				 energyRemaining = energyRemaining * (1.0 - message.getEnergyReduction());		
				 sensorPower = message.getSensorPower();
			 }
		 }
	};
	
	public PowerModel() {
		EventDispatcher.registerConsumer(GroundTruthMessage.class, truthHandle);
		EventDispatcher.registerConsumer(RemusBatteryPerturbation.class, powerHandle);
		TimeManager.addStepper(this);
	}
	
	protected double getPower(GroundTruthMessage state) {
		return hotelLoad + propulsorCoefficient*Math.pow(state.rpm, 3) 
			+ (rudderCoefficient*state.rudderAngle
					+ elevatorCoefficient*state.elevatorAngle)*Math.pow(state.surge, 3)
			+ sensorPower;
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
		if (o.containsKey("rudderCoefficient")) {
			rudderCoefficient = o.getJsonNumber("rudderCoefficient").doubleValue();
		} else {			
			rudderCoefficient = 0;
		}
		if (o.containsKey("elevatorCoefficient")) {
			elevatorCoefficient = o.getJsonNumber("elevatorCoefficient").doubleValue();
		} else {			
			elevatorCoefficient = 0;
		}
		if (o.containsKey("hotelLoad")) {
			hotelLoad = o.getJsonNumber("hotelLoad").doubleValue();
		} else {			
			LOGGER.warning("No hotel load given!");
		} 
		
	}
	 

}
