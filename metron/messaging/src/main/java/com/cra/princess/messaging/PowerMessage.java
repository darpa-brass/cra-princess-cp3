package com.cra.princess.messaging;

import java.util.Date;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

public class PowerMessage implements MappableMessage {

	public double power_W; // Current power drain in watts
	public double energyRemaining_J; // Energy remaining in joules
	public long timestamp;

	public PowerMessage() { 
	}

	public PowerMessage(MapMessage msg) {
		set(msg);
	}


	@Override
	public void set(MapMessage msg) {
		try {
			timestamp = msg.getLong("timestamp");
			power_W = msg.getDouble("power");
			energyRemaining_J = msg.getDouble("energyRemaining");
		} catch (JMSException e) {
			e.printStackTrace();
		}
	}


	@Override
	public MapMessage toMapMessage() {
		MapMessage ans = new ActiveMQMapMessage();
		try {
			ans.setLong("timestamp", timestamp);                    
			ans.setDouble("power", power_W);
			ans.setDouble("energyRemaining", energyRemaining_J);
		} catch (JMSException e) {
			e.printStackTrace();
		}
		return ans;
	}

	@Override
	public String toString() {
		return String.format("%s [timestamp=%s, power=%6.3f, energyRemaining=%6.3g]",
				PowerMessage.class.getSimpleName(), new Date(timestamp).toString(), power_W, energyRemaining_J);
	}
}
