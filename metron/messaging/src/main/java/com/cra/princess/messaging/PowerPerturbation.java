package com.cra.princess.messaging;

import java.util.Date;

import javax.jms.JMSException;
import javax.jms.MapMessage;

import org.apache.activemq.command.ActiveMQMapMessage;

public class PowerPerturbation implements MappableMessage {
	public double powerSpike = 0; // Instantaneously set power to this value
	public double energyDrain = 0; // Reduce energy reserves by this amount
	public long timestamp;

	@Override
	public void set(MapMessage msg) {
		try {         
			timestamp = msg.getLong("timestamp");
			powerSpike = msg.getDouble("powerSpike");
			energyDrain = msg.getDouble("energyDrain");
		} catch (JMSException e) {
			e.printStackTrace();
		}
	}


	@Override
	public MapMessage toMapMessage() {
		MapMessage ans = new ActiveMQMapMessage();
		try {
			ans.setLong("timestam", timestamp);
			ans.setDouble("powerSpike", powerSpike);
			ans.setDouble("energyDrain", energyDrain);
		} catch (JMSException e) {
			e.printStackTrace();
		}
		return ans;
	}

	@Override
	public String toString() {
		return String.format("%s [timestamp=%s, power=%6.3f, energyRemaining=%6.3g]",
				PowerPerturbation.class.getSimpleName(), new Date(timestamp).toString(), powerSpike, energyDrain);
	}
}
