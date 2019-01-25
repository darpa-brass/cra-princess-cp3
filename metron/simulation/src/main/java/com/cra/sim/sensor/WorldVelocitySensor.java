package com.cra.sim.sensor;

import javax.json.JsonObject;

import com.cra.princess.messaging.DvlMessage;
import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.messaging.JmsManager;
import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.TimeManager;
import com.cra.princess.simulation.TimeManager.TimeStepped;
import com.cra.princess.simulation.events.EventDispatcher;
import com.cra.sim.sensor.BodyVelocitySensor.BodyVelocity;
import com.metsci.dynamic.simple.AffineTransform;
import com.metsci.dynamic.simple.MotionModel;

public class WorldVelocitySensor implements JsonConfigurable, MessageHandler<GroundTruthMessage>, TimeStepped, Sensor {
    protected BodyVelocitySensor bodyVelocitySensor;
    protected AdditiveSensorCorruptor rollSensor;
    protected AdditiveSensorCorruptor pitchSensor;
    protected AdditiveSensorCorruptor yawSensor;
    protected AdditiveSensorCorruptor depthSensor;
    protected AdditiveSensorCorruptor altitudeSensor;
    private GroundTruthMessage cachedState = null;
    private long lastMessageTime = 0;
    private long messageInterval = 200;
    
    public WorldVelocitySensor() {
        EventDispatcher.registerConsumer(GroundTruthMessage.class, this);
        TimeManager.addStepper(this);
    }
    
    @Override
    public void handleMessage(GroundTruthMessage state) {
        cachedState = state;
    }

    @Override
    public void configure(JsonObject sensor) {    	    	
        try {                    	        	
        	rollSensor = new AdditiveSensorCorruptor("dvl_roll");
        	rollSensor.configure(sensor.getJsonObject("roll"));        	
        	pitchSensor = new AdditiveSensorCorruptor("dvl_pitch");
        	pitchSensor.configure(sensor.getJsonObject("pitch"));        	       
        	yawSensor = new AdditiveSensorCorruptor("dvl_yaw");
        	yawSensor.configure(sensor.getJsonObject("yaw"));    
        	depthSensor = new AdditiveSensorCorruptor("dvl_depth");
        	depthSensor.configure(sensor.getJsonObject("depth"));    
        	altitudeSensor = new AdditiveSensorCorruptor("dvl_altitude");
        	altitudeSensor.configure(sensor.getJsonObject("altitude"));        	        	
        	bodyVelocitySensor = new BodyVelocitySensor();
            bodyVelocitySensor.configure(sensor.getJsonObject("velocity"));
            
        } catch (NullPointerException e) {
            throw new ConfigurationException("Missing one or more required sensor parameters.\n" + e.getLocalizedMessage()); 
        }        
    }
    

	@Override
	public void register(SensorManager manager) {
		manager.register(rollSensor.getName(), rollSensor);
		manager.register(pitchSensor.getName(), pitchSensor);
		manager.register(yawSensor.getName(), yawSensor);
		manager.register(depthSensor.getName(), depthSensor);
		manager.register(altitudeSensor.getName(), altitudeSensor);
		bodyVelocitySensor.register(manager);
	}

    @Override
    public void initialize() {
    }

    @Override
    public void update() {
        long elapsed = TimeManager.now() - lastMessageTime;
        if (elapsed >= messageInterval && cachedState != null) {
            lastMessageTime = TimeManager.now();
            DvlMessage measurement = getMeasurement(cachedState);
            EventDispatcher.publishEvent(measurement);
            JmsManager.sendDvlMessage(measurement);
        }
    }

    @Override
    public void reset() {
    	cachedState = null;
		lastMessageTime = 0;
    }

    @Override
    public void stop() {
    }
    

    private DvlMessage getMeasurement(GroundTruthMessage state) {
        DvlMessage m = new DvlMessage();        
        // state has values in radians, so these are in radians here (needed for rot matrix below)
        m.roll = Math.toRadians(rollSensor.corrupt(state.roll));
        m.pitch = Math.toRadians(pitchSensor.corrupt(state.pitch));
        m.heading = Math.toRadians(yawSensor.corrupt(state.heading));                    
        BodyVelocity v = bodyVelocitySensor.observe(state);
        m.surge = v.surge();
        m.sway = v.sway();
        m.heave = v.heave();
        AffineTransform bodyToWorld = new AffineTransform(0, 0, 0, m.roll, m.pitch, m.heading);   
        double[] vworld = bodyToWorld.transform(v.v);
        m.vN = vworld[0];
        m.vE = vworld[1];
        m.vU = -vworld[2];       
        m.timestamp = TimeManager.now();    
        m.depth = depthSensor.corrupt(state.trueDepth);
        m.altitude = altitudeSensor.corrupt(state.waterDepth - state.trueDepth);
        // Convert to output degrees
        m.roll = Math.toDegrees(m.roll);
        m.pitch = Math.toDegrees(m.pitch);
        m.heading = Math.toDegrees(MotionModel.unwind(m.heading));
        return m;
    }


}
