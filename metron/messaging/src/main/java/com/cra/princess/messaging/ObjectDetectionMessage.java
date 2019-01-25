package com.cra.princess.messaging;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Data representing detected objects
 * 
 * @author gratton
 *
 */
public class ObjectDetectionMessage implements MappableMessage {
    /**
     * The (simulated) time at which the state was measured. Suitable for constructing a Java Date object: milliseconds
     * since 1/1/1970 0:00:00 UTC.
     */
    public long timestamp;

    /**
     * Range in meters to object 
     */
    public double range;
    /**
     * horizontal bearing in sensor coords to object (deg)
     */
    public double theta;
    /**
     * vertical bearing in sensor coords to object (deg)
     */
    public double phi;

    public void set(double[] valInRadians) {
    	range = valInRadians[0];
    	theta = Math.toDegrees(valInRadians[1]);
    	phi = Math.toDegrees(valInRadians[2]);
    }
    
    public ObjectDetectionMessage() {
    }
    
    public ObjectDetectionMessage(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            timestamp = msg.getLong("timestamp");            
            range = msg.getDouble("range");
            theta = msg.getDouble("theta");
            phi = msg.getDouble("phi");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setLong("timestamp", timestamp);                     
            ans.setDouble("range", range);
            ans.setDouble("theta", theta);
            ans.setDouble("phi", phi);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
    	return String.format("%s [timestamp=%d, range=%6.3g, theta=%6.3g, phi=%6.3g]", 
    			ObjectDetectionMessage.class.getSimpleName(), timestamp, range, theta, phi);

    }

}