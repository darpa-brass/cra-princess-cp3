package com.cra.sim.sensor;

import javax.json.JsonObject;

import com.cra.princess.messaging.GroundTruthMessage;
import com.cra.princess.simulation.JsonConfigurable;
import com.metsci.dynamic.simple.AffineTransform;

public class BodyVelocitySensor implements JsonConfigurable, Sensor {
    protected AdditiveSensorCorruptor surgeCorruptor;
    protected AdditiveSensorCorruptor swayCorruptor;
    protected AdditiveSensorCorruptor heaveCorruptor;    

    public static class BodyVelocity {
    	public final double[] v;
        public double surge() { return v[0]; }
        public double sway() { return v[1]; }
        public double heave() { return v[2]; }
        
        
        public BodyVelocity(double surge, double sway, double heave) {
        	v = new double[] {surge, sway, heave};            
        }
    }
    
    public BodyVelocitySensor() {  	
    }
       
    public BodyVelocity observe(GroundTruthMessage state) {
    	// Reconstruct speed over ground
    	// Transform the current into the body frame
    	double[] currentWorld = new double[] {state.waterCurrentN, state.waterCurrentE, 0.0};
    	AffineTransform worldToBody = (new AffineTransform(0,0,0, 
    			Math.toRadians(state.roll), 
    			Math.toRadians(state.pitch), 
    			Math.toRadians(state.heading))).transpose();    	
    	double[] currentBody = worldToBody.transform(currentWorld);
        return new BodyVelocity(
                surgeCorruptor.corrupt(state.surge + currentBody[0]),
                swayCorruptor.corrupt(state.sway + currentBody[1]),
                heaveCorruptor.corrupt(state.heave + currentBody[2]));
    }

	@Override
	public void configure(JsonObject o) {
		surgeCorruptor = new AdditiveSensorCorruptor("dvl_surge");
		surgeCorruptor.configure(o.getJsonObject("surge"));
		swayCorruptor = new AdditiveSensorCorruptor("dvl_sway");
		swayCorruptor.configure(o.getJsonObject("sway"));
		heaveCorruptor = new AdditiveSensorCorruptor("dvl_heave");
		heaveCorruptor.configure(o.getJsonObject("heave"));
	}

	@Override
	public void register(SensorManager manager) {
		manager.register(surgeCorruptor.getName(), surgeCorruptor);
		manager.register(swayCorruptor.getName(), swayCorruptor);
		manager.register(heaveCorruptor.getName(), heaveCorruptor);
	}
    
}
