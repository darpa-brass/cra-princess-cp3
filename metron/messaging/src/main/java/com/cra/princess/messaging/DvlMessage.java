package com.cra.princess.messaging;

import java.util.Date;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Data representing vehicle state at a single point in time. This implementation is morally equivalent to a C struct,
 * with public, mutable members.
 * 
 * @author chagnon
 *
 */
public class DvlMessage implements MappableMessage {
    /**
     * The (simulated) time at which the state was measured. Suitable for constructing a Java Date object: milliseconds
     * since 1/1/1970 0:00:00 UTC.
     */
    public long timestamp;

    /**
     * Depth of vehicle, m
     */
    public double depth;
    
    /**
     * Distance from vehicle to sea floor, m
     */
    public double altitude;

    /**
     * Eastward velocity, m/s.
     */
    public double vE;
    /**
     * Northward velocity, m/s.
     */
    public double vN;
    
    /**
     * Upwards velocity, m/s.
     */
    public double vU;

    /**
     * Surge velocity, m/s.
     */
    public double surge;
    /**
     * Sway velocity, m/s.
     */
    public double sway;
    
    /**
     * Heave velocity, m/s.
     */
    public double heave;
    
    /**
     * Pitch (positive is bow up), degrees.
     */
    public double pitch;
    /**
     * Roll (positive is port up), degrees.
     */
    public double roll;
    /**
     * Heading, degrees clockwise from North.
     */
    public double heading;

    public DvlMessage() {
    }
    
    public DvlMessage(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            timestamp = msg.getLong("timestamp");
            depth = msg.getDouble("depth");
            altitude = msg.getDouble("altitude");

            vE = msg.getDouble("vE");
            vN = msg.getDouble("vN");
            vU = msg.getDouble("vU");
            
            surge = msg.getDouble("surge");
            sway = msg.getDouble("sway");
            heave = msg.getDouble("heave");

            pitch = msg.getDouble("pitch");
            roll = msg.getDouble("roll");
            heading = msg.getDouble("heading");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setLong("timestamp", timestamp);
                        
            ans.setDouble("depth", depth);
            ans.setDouble("altitude", altitude);

            ans.setDouble("vE", vE);
            ans.setDouble("vN", vN);
            ans.setDouble("vU", vU);

            ans.setDouble("surge", surge);
            ans.setDouble("sway", sway);
            ans.setDouble("heave", heave);
            
            ans.setDouble("pitch", pitch);
            ans.setDouble("roll", roll);
            ans.setDouble("heading", heading);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
        return String.format("%s [timestamp=%s, depth=%6.3f, altitude=%6.3g, vE=%6.3f, vN=%6.3f, vU=%6.3f, surge=%6.3f, sway=%6.3f, heave=%6.3f, pitch=%5.2f, roll=%5.2f, heading=%7.2f]",
                DvlMessage.class.getSimpleName(), new Date(timestamp).toString(), depth, altitude, vE, vN, vU, surge, sway, heave, pitch, roll, heading);
    }

}