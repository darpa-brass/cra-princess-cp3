package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.perturbation.RemusBatteryPerturbation;
import com.cra.princess.metron.remus.perturbation.BatteryPerturbationListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for capturing Battery Perturbation messages sent to the Metron REMUS simulator.
 * 
 */
public class BatteryPerturbationTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(BatteryPerturbationTopicWatcher.class.getName());

	private List<BatteryPerturbationListener> batteryPerturbationListeners = null;

    public BatteryPerturbationTopicWatcher(Session session) {
    	super(session, RemusBatteryPerturbation.BATTERY_PERTURBATION_TOPIC);

    	this.batteryPerturbationListeners = new CopyOnWriteArrayList<BatteryPerturbationListener>();
    }
    
    public void addBatteryPerturbationListener(BatteryPerturbationListener listener) {
    	this.batteryPerturbationListeners.add(listener);
    }

    public void removeBatteryPerturbationListener(BatteryPerturbationListener listener) {
    	this.batteryPerturbationListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Battery Perturbation Message

			LOG.debug("New Battery Perturbation received");

			Double powerReduction = mapMessage.getDouble(RemusBatteryPerturbation.DATA_FIELD_POWER_REDUCTION);

			RemusBatteryPerturbation rbp = new RemusBatteryPerturbation(powerReduction);

			LOG.debug("Sending Battery Perturbation data to listeners");

			for (BatteryPerturbationListener listener : this.batteryPerturbationListeners) {
				listener.batteryPerturbationUpdate(rbp);
			}

			LOG.debug("Battery Perturbation listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
