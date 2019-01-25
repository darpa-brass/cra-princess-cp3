package com.cra.princess.metron.remus.perturbation;

import org.apache.activemq.command.ActiveMQMapMessage;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import java.util.Date;

public class RemusBatteryPerturbation {
	public static final String BATTERY_PERTURBATION_TOPIC = "princess.battery.perturbation";

	public static final String DATA_FIELD_TIMESTAMP = "timestamp";
	public static final String DATA_FIELD_POWER_REDUCTION = "powerReduction";

    private double powerReduction = 0.0;

    public RemusBatteryPerturbation(double powerReduction) {
    	this.powerReduction = powerReduction;
    }

    public RemusBatteryPerturbation(RemusBatteryPerturbation perturbation) {
    	if (perturbation != null) {
    		this.powerReduction = perturbation.getPowerReduction();
    	}
    }

	public double getPowerReduction() { return powerReduction; }

	public MapMessage toMapMessage() {
		MapMessage ans = new ActiveMQMapMessage();
		try {
			ans.setLong("timestamp", new Date().getTime());
			ans.setDouble("powerReduction", this.powerReduction);
		} catch (JMSException e) {
			e.printStackTrace();
		}
		return ans;
	}
}
