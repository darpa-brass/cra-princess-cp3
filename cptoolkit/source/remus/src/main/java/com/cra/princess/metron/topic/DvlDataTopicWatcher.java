package com.cra.princess.metron.topic;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.state.DvlSensorUpdateListener;
import com.cra.princess.metron.remus.state.RemusDvlData;

/**
 * Class for handling DVL data messages from the Metron REMUS simulator.
 * 
 */
public class DvlDataTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(DvlDataTopicWatcher.class.getName());

	private List<DvlSensorUpdateListener> dvlSensorUpdateListeners = null;
    
    public DvlDataTopicWatcher(Session session) {
    	super(session, RemusDvlData.DVL_SENSOR_TOPIC);

    	this.dvlSensorUpdateListeners = new CopyOnWriteArrayList<DvlSensorUpdateListener>();
    }
    
    public void addDvlSensorUpdateListener(DvlSensorUpdateListener listener) {
    	this.dvlSensorUpdateListeners.add(listener);
    }

    public void removeDvlSensorUpdateListener(DvlSensorUpdateListener listener) {
    	this.dvlSensorUpdateListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// DVL Sensor Data Message

			LOG.debug("New REMUS DVL data update received");

			Long timestamp = mapMessage.getLong(RemusDvlData.DATA_FIELD_TIMESTAMP);
			Double depth = mapMessage.getDouble(RemusDvlData.DATA_FIELD_DEPTH);
			Double vE = mapMessage.getDouble(RemusDvlData.DATA_FIELD_VE);
			Double vN = mapMessage.getDouble(RemusDvlData.DATA_FIELD_VN);
			Double vU = mapMessage.getDouble(RemusDvlData.DATA_FIELD_VU);
			Double pitch = mapMessage.getDouble(RemusDvlData.DATA_FIELD_PITCH);
			Double roll = mapMessage.getDouble(RemusDvlData.DATA_FIELD_ROLL);
			Double heading = mapMessage.getDouble(RemusDvlData.DATA_FIELD_HEADING);
			Double surge = mapMessage.getDouble(RemusDvlData.DATA_FIELD_SURGE);
			Double sway = mapMessage.getDouble(RemusDvlData.DATA_FIELD_SWAY);
			Double heave = mapMessage.getDouble(RemusDvlData.DATA_FIELD_HEAVE);

			RemusDvlData rdd = new RemusDvlData(timestamp, depth, vE, vN, vU, pitch, roll, heading, surge, sway, heave);

			LOG.debug("Sending DVL data to listeners");

			for (DvlSensorUpdateListener listener : this.dvlSensorUpdateListeners) {
				listener.dvlSensorUpdate(rdd);
			}

			LOG.debug("DVL listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
