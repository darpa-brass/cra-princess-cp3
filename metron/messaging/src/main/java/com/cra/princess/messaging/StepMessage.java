package com.cra.princess.messaging;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

/**
 * Signal the sim to take a timestep of the given size
 * Only honored in stepping mode
 * 
 * @author gratton
 *
 */
public class StepMessage implements MappableMessage {
	public long timestep_ms = 100L;
       
    public StepMessage() { }
    public StepMessage(long timestep) { this.timestep_ms = timestep; }
    
    public StepMessage(MapMessage message) {    			    		
        set(message);
    }
    
    @Override
    public void set(MapMessage message) {
        try {
        	timestep_ms = message.getLong("timestep_ms");        	
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
        

    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
        	ans.setLong("timestep_ms", timestep_ms);            
        } catch (JMSException e) {
            e.printStackTrace();
        }
        
        return ans;
    }

}
