package com.cra.princess.messaging;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Signal the end of a simulation run.
 * 
 * @author chagnon
 *
 */
public class SimulationEnded implements MappableMessage {
    /**
     * Reserved for future use - possibly a summary of simulation events.
     */
    public String detail = "Simulation over";
    
    public SimulationEnded() { }
    
    public SimulationEnded(MapMessage message) {
        set(message);
    }
    
    @Override
    public void set(MapMessage message) {
        try {
            detail = message.getString("detail");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setString("detail", detail);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        
        return ans;
    }

}
