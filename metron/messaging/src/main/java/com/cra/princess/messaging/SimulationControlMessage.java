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
public class SimulationControlMessage implements MappableMessage {
	public enum PlayControl {
		PLAY,
		PAUSE,
		STOP
	}
    /**
     * Reserved for future use - possibly a summary of simulation events.
     */
    public String detail = "N/A";
    
    /**
     * Play/Pause/Stop command
     */
    public PlayControl playControl = PlayControl.PLAY;
    
    /**
     * Desired simulation speed (negative values mean don't change the speed)
     */
    public double simSpeed = -1.0;
    
    public static SimulationControlMessage stop() {
    	SimulationControlMessage message = new SimulationControlMessage();
    	message.playControl = PlayControl.STOP;
    	return message;
    }
    public static SimulationControlMessage pause() {
    	SimulationControlMessage message = new SimulationControlMessage();
    	message.playControl = PlayControl.PAUSE;
    	return message;
    }
    public static SimulationControlMessage play() {
    	SimulationControlMessage message = new SimulationControlMessage();
    	message.playControl = PlayControl.PLAY;
    	return message;
    }
    public static SimulationControlMessage play(double speed) {
    	SimulationControlMessage message = SimulationControlMessage.play();
    	message.simSpeed = speed;
    	return message;
    }
    
    public SimulationControlMessage() { }
    
    public SimulationControlMessage(MapMessage message) {    			    		
        set(message);
    }
    
    @Override
    public void set(MapMessage message) {
        try {
        	detail = message.getString("detail");
        	playControl = PlayControl.valueOf(message.getString("playControl"));
        	simSpeed = message.getDouble("simSpeed");
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }
        

    @Override
    public MapMessage toMapMessage() {
        MapMessage ans = new ActiveMQMapMessage();
        try {
            ans.setString("detail", detail);
            ans.setString("playControl", playControl.name());
            ans.setDouble("simSpeed", simSpeed);
        } catch (JMSException e) {
            e.printStackTrace();
        }
        
        return ans;
    }

}
