package com.cra.princess.messaging;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Data representing a sensor performance perturbation
 * 
 * @author gratton
 *
 */
public class SensorPerturbation implements MappableMessage {
    /**
     * Name of sensor component to alter
     */
    public String name;
    /**
     * Bias value added to all measurements
     */
    public double bias;
    /**
     * Standard deviation of Gaussian noise added to all measurements
     */
    public double noiseDeviation;
    /**
     * With probability p, send this value instead of a measurement
     */
    public double anchor;
    /**
     * ...this is that probability p
     */
    public double anchorProbability;
    

    public SensorPerturbation() {
    }
    
    public SensorPerturbation(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            name = msg.getString("name");
            bias = msg.getDouble("bias");
            noiseDeviation = msg.getDouble("noiseDeviation");
            anchor = msg.getDouble("anchor");
            anchorProbability = msg.getDouble("anchorProbability");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
        	ans.setString("name", name);
            ans.setDouble("bias", bias);            
            ans.setDouble("noiseDeviation", noiseDeviation);
            ans.setDouble("anchor", anchor);
            ans.setDouble("anchorProbability", anchorProbability);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
        return String.format("SensorPerturbation [name=%s, bias=%g, noiseDeviation=%g, anchor=%g, anchorProbability=%g]",
        		name, bias, noiseDeviation, anchor, anchorProbability);
    }

}
