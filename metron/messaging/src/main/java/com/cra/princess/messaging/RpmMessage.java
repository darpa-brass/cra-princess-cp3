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
public class RpmMessage implements MappableMessage {
    /**
     * The (simulated) time at which the state was measured. Suitable for constructing a Java Date object: milliseconds
     * since 1/1/1970 0:00:00 UTC.
     */
    public long timestamp;

    /**
     * Rotational speed of propeller (revolutions per minute) 
     */
    public double rpm;


    public RpmMessage() {
    }
    
    public RpmMessage(MapMessage msg) {
        set(msg);
    }
    
    @Override
    public void set(MapMessage msg) {
        try {
            timestamp = msg.getLong("timestamp");
            rpm = msg.getDouble("PropellerRpm");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
    
    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setLong("timestamp", timestamp);                        
            ans.setDouble("PropellerRpm", rpm);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return ans;
    }
    
    @Override
    public String toString() {
        return String.format("%s [timestamp=%s, rpm=%6.3f]",
                RpmMessage.class.getSimpleName(), new Date(timestamp).toString(), rpm);
    }

}