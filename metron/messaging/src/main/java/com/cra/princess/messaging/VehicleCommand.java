package com.cra.princess.messaging;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Data representing vehicle command. This implementation is morally equivalent to a C struct, with public, mutable
 * members.
 * 
 * @author chagnon
 *
 */
public class VehicleCommand implements MappableMessage {
    /**
     * Desired heading, in degrees clockwise from North.
     */
    public double headingTarget;
    /**
     * Desired depth below the ocean surface in meters.
     */
    public double depthTarget;
    /**
     * Desired surge speed in meters / second.
     */
    public double speedTarget;

    public VehicleCommand() {
    }
    
    public VehicleCommand(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            headingTarget = msg.getDouble("headingTarget");
            depthTarget = msg.getDouble("depthTarget");
            speedTarget = msg.getDouble("speedTarget");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setDouble("headingTarget", headingTarget);
            ans.setDouble("depthTarget", depthTarget);
            ans.setDouble("speedTarget", speedTarget);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
        return "VehicleCommand [headingTarget=" + headingTarget + ", depthTarget=" + depthTarget + ", speedTarget=" + speedTarget + "]";
    }

}
