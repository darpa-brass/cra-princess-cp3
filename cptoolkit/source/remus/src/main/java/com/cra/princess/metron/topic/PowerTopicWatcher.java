package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.RemusPowerState;
import com.cra.princess.metron.remus.state.VehiclePowerUpdateListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling power data messages from the REMUS power simulator.
 * 
 */
public class PowerTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(PowerTopicWatcher.class.getName());

    private List<VehiclePowerUpdateListener> vehiclePowerUpdateListeners = null;

    public PowerTopicWatcher(Session session) {
    	super(session, RemusPowerState.POWER_TOPIC);

    	this.vehiclePowerUpdateListeners = new CopyOnWriteArrayList<VehiclePowerUpdateListener>();
    }
    
    public void addVehiclePowerUpdateListener(VehiclePowerUpdateListener listener) {
    	this.vehiclePowerUpdateListeners.add(listener);
    }

    public void removeVehiclePowerUpdateListener(VehiclePowerUpdateListener listener) {
    	this.vehiclePowerUpdateListeners.remove(listener);
    }    

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Power Message

			LOG.debug("New REMUS power update received");

			Long timestamp = mapMessage.getLong(RemusPowerState.DATA_FIELD_TIMESTAMP);
			Double power = mapMessage.getDouble(RemusPowerState.DATA_FIELD_POWER);

			RemusPowerState rps = new RemusPowerState(timestamp, power);

			LOG.debug("Sending power update to listeners");

			for (VehiclePowerUpdateListener listener : this.vehiclePowerUpdateListeners) {
				listener.vehiclePowerUpdate(rps);
			}

			LOG.debug("Power listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
