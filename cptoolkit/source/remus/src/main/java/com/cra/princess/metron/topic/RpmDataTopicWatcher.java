package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.RemusPowerState;
import com.cra.princess.metron.remus.state.RemusRpmData;
import com.cra.princess.metron.remus.state.RpmSensorUpdateListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling RPM data messages from the Metron REMUS simulator.
 * 
 */
public class RpmDataTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(RpmDataTopicWatcher.class.getName());

	private List<RpmSensorUpdateListener> rpmSensorUpdateListeners = null;

    public RpmDataTopicWatcher(Session session) {
    	super(session, RemusRpmData.RPM_TOPIC);

    	this.rpmSensorUpdateListeners = new CopyOnWriteArrayList<RpmSensorUpdateListener>();
    }
    
    public void addRpmSensorUpdateListener(RpmSensorUpdateListener listener) {
    	this.rpmSensorUpdateListeners.add(listener);
    }

    public void removeRpmSensorUpdateListener(RpmSensorUpdateListener listener) {
    	this.rpmSensorUpdateListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// RPM Sensor Data Message

			LOG.debug("New REMUS RPM data update received");

			Long timestamp = mapMessage.getLong(RemusRpmData.DATA_FIELD_TIMESTAMP);
			Double rpm = mapMessage.getDouble(RemusRpmData.DATA_FIELD_RPM);

			RemusRpmData rrd = new RemusRpmData(timestamp, rpm);

			LOG.debug("Sending RPM data to listeners");

			for (RpmSensorUpdateListener listener : this.rpmSensorUpdateListeners) {
				listener.rpmSensorUpdate(rrd);
			}

			LOG.debug("RPM listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
