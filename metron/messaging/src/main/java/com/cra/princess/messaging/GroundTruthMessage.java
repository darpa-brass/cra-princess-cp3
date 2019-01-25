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
public class GroundTruthMessage implements MappableMessage {
    /**
     * The (simulated) time at which the state was measured. Suitable for constructing a Java Date object: milliseconds
     * since 1/1/1970 0:00:00 UTC.
     */
    public long timestamp;

    /**
     * Ground truth longitude, degrees (-180 - 180).
     */
    public double trueLongitude;
    /**
     * Ground truth latitude, degrees.
     */
    public double trueLatitude;
    /**
     * Ground truth depth, meters
     */
    public double trueDepth;

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
    
    // Extended state information:
    // Velocity relative to water (m/s)
    public double surge; // axial
    public double sway; // positive to starboard
    public double heave; // positive down
    // Local coordinate system position (m)
    public double northing;
    public double easting;
    public double down;
    // All environmental information (m or m/s)
    public double waterDepth;
    public double waterCurrentN;
    public double waterCurrentE;
    // Actuator information
    public double rpm;

    public GroundTruthMessage() {
    }
    
    public GroundTruthMessage(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            timestamp = msg.getLong("timestamp");
            
            trueLongitude = msg.getDouble("trueLongitude");
            trueLatitude = msg.getDouble("trueLatitude");
            trueDepth = msg.getDouble("trueDepth");

            vE = msg.getDouble("vE");
            vN = msg.getDouble("vN");
            vU = msg.getDouble("vU");

            pitch = msg.getDouble("pitch");
            roll = msg.getDouble("roll");
            heading = msg.getDouble("heading");
            
            surge = msg.getDouble("surge");
            sway = msg.getDouble("sway");
            heave = msg.getDouble("heave");
            
            northing = msg.getDouble("northing");
            easting = msg.getDouble("easting");
            down = msg.getDouble("down");
            
            waterDepth = msg.getDouble("waterDepth");
            waterCurrentN = msg.getDouble("waterCurrentN");
            waterCurrentE = msg.getDouble("waterCurrentE");
            
            rpm = msg.getDouble("rpm");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setLong("timestamp", timestamp);
            
            ans.setDouble("trueLongitude", trueLongitude);
            ans.setDouble("trueLatitude", trueLatitude);
            ans.setDouble("trueDepth", trueDepth);

            ans.setDouble("vE", vE);
            ans.setDouble("vN", vN);
            ans.setDouble("vU", vU);

            ans.setDouble("pitch", pitch);
            ans.setDouble("roll", roll);
            ans.setDouble("heading", heading);
            
            ans.setDouble("surge", surge);
            ans.setDouble("sway", sway);
            ans.setDouble("heave", heave);
            
            ans.setDouble("northing", northing);
            ans.setDouble("easting", easting);
            ans.setDouble("down", down);
            
            ans.setDouble("waterDepth", waterDepth);
            ans.setDouble("waterCurrentN", waterCurrentN);
            ans.setDouble("waterCurrentE", waterCurrentE);
            
            ans.setDouble("rpm", rpm);
            
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
        return String.format("StateMessage [timestamp=%s, trueLongitude=%.6f, trueLatitude=%.6f, trueDepth=%6.3f, vE=%6.3f,"
        		+ " vN=%6.3f, vU=%6.3f, pitch=%5.2f, roll=%5.2f, heading=%7.2f, surge=%6.3f, sway=%6.3f, heave=%6.3f,"
        		+ " northing=%6.3f, easting=%6.3f, down=%6.3f, waterDepth=%5.2g, waterCurrentN=%5.2f, waterCurrentE=%5.2f, rpm=%3.2f]",
                new Date(timestamp).toString(), trueLongitude, trueLatitude, trueDepth, vE, vN, vU, pitch, roll, heading,
                surge, sway, heave, northing, easting, down, waterDepth, waterCurrentN, waterCurrentE, rpm);
    }

}