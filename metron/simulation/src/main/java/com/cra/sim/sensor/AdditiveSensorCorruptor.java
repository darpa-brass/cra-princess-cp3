package com.cra.sim.sensor;

import java.util.Random;

import javax.json.JsonObject;

import com.cra.princess.messaging.JmsManager.MessageHandler;
import com.cra.princess.messaging.SensorPerturbation;
import com.cra.princess.simulation.ConfigurationException;
import com.cra.princess.simulation.JsonConfigurable;
import com.cra.princess.simulation.RandomManager;

public class AdditiveSensorCorruptor implements JsonConfigurable, MessageHandler<SensorPerturbation> {
	protected String name;
    protected double bias;
    protected Random generator;
    protected double anchor;
    protected double anchorProbability;
    protected WhiteNoise sampleNoise;
    
    public AdditiveSensorCorruptor() {
    	this("unknown");
    }
    
    public AdditiveSensorCorruptor(String name) {
    	this.name = name;
    	generator = RandomManager.getGenerator();    	
    }
    
    public AdditiveSensorCorruptor copy() {
    	AdditiveSensorCorruptor other = new AdditiveSensorCorruptor(name);    	    	
    	other.updateModel(this.bias, this.sampleNoise.baseSigma, this.anchor, this.anchorProbability);
    	return other;
    }
    
    public String getName() {
    	return name;
    }
    
    public AdditiveSensorCorruptor setName(String name) {
    	this.name = name;
    	return this;
    }
    
    public AdditiveSensorCorruptor updateModel(double fixedBias, double noiseDev, double anchor, double anchorProbability) {
    	this.bias = fixedBias;
        this.sampleNoise = new WhiteNoise(noiseDev);
        this.anchor = anchor;
        this.anchorProbability = anchorProbability;
        return this;
    }
    
    public double corrupt(double signal) {
        double w = sampleNoise.update();
        if (generator.nextDouble() < anchorProbability)
        	return anchor;
        return signal + bias + w;
    }

	@Override
	public void configure(JsonObject o) {			
		name = o.getJsonString("name").getString();
        bias = o.getJsonNumber("bias").doubleValue();
        double noiseDev = o.getJsonNumber("noiseDev").doubleValue();
        anchor = o.getJsonNumber("anchor").doubleValue();
        anchorProbability = o.getJsonNumber("anchorProbability").doubleValue();            
        ConfigurationException.check("anchorProbability", anchorProbability, 0, 1);
        updateModel(bias, noiseDev, anchor, anchorProbability);
	}

	@Override
	public void handleMessage(SensorPerturbation message) {
		if (message.name.equals(name)) {
			updateModel(message.bias, message.noiseDeviation, message.anchor, message.anchorProbability);
		}
	}
    
    
}
