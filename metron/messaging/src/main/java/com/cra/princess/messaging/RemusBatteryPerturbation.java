package com.cra.princess.messaging;

import org.apache.activemq.command.ActiveMQMapMessage;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import java.util.Date;

public class RemusBatteryPerturbation implements MappableMessage {
	public static final String BATTERY_PERTURBATION_TOPIC = "princess.battery.perturbation";

	public long timepoint_ms = 0; // Time in scenario this event will happen (or immediately if this time is in the past)
    public double energyReduction = 0.0;
    public double sensorPower = 0.0;

    public RemusBatteryPerturbation() {
    	this(0, 0, 0);
    }
    
    public RemusBatteryPerturbation(double energyReduction, double sensorPower, long timepoint) {
    	this.energyReduction = energyReduction;
    	this.sensorPower = sensorPower;
    	this.timepoint_ms = timepoint;
    }

    public RemusBatteryPerturbation(RemusBatteryPerturbation perturbation) {
    	if (perturbation != null) {
    		this.energyReduction = perturbation.getEnergyReduction();
    		this.sensorPower = perturbation.getSensorPower();
    		this.timepoint_ms = perturbation.timepoint_ms;
    	}
    }

	public double getEnergyReduction() { return energyReduction; }

	public double getSensorPower() { return sensorPower; }
	
	public MapMessage toMapMessage() {
		MapMessage ans = new ActiveMQMapMessage();
		try {
			ans.setLong("timepoint_ms", this.timepoint_ms);
			ans.setDouble("energyReduction", this.energyReduction);
			ans.setDouble("sensorPower", this.sensorPower);
		} catch (JMSException e) {
			e.printStackTrace();
		}
		return ans;
	}
	
	public String toString() {
		return String.format("%s [timepoint_ms=%s, energyReduction=%6.3f, sensorPower=%6.3f]",
				RemusBatteryPerturbation.class.getSimpleName(), new Date(timepoint_ms).toString(), energyReduction, sensorPower);
	}

	@Override
	public void set(MapMessage msg) {
		try {         
			timepoint_ms = msg.getLong("timepoint_ms");
			energyReduction = msg.getDouble("energyReduction");			
			sensorPower = msg.getDouble("sensorPower");
		} catch (JMSException e) {
			e.printStackTrace();
		} 
	}
}
