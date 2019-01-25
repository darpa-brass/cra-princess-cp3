package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;
import com.cra.princess.metron.remus.perturbation.SensorPerturbationListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for capturing Sensor Perturbation messages sent to the Metron REMUS simulator.
 * 
 */
public class SensorPerturbationTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(SensorPerturbationTopicWatcher.class.getName());

	private List<SensorPerturbationListener> sensorPerturbationListeners = null;

    public SensorPerturbationTopicWatcher(Session session) {
    	super(session, RemusSensorPerturbation.SENSOR_PERTURBATION_TOPIC);

    	this.sensorPerturbationListeners = new CopyOnWriteArrayList<SensorPerturbationListener>();
    }
    
    public void addSensorPerturbationListener(SensorPerturbationListener listener) {
    	this.sensorPerturbationListeners.add(listener);
    }

    public void removeSensorPerturbationListener(SensorPerturbationListener listener) {
    	this.sensorPerturbationListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Sensor Perturbation Message

			LOG.debug("New Sensor Perturbation received");

			String sensorName = mapMessage.getString(RemusSensorPerturbation.DATA_FIELD_NAME);
			Double bias = mapMessage.getDouble(RemusSensorPerturbation.DATA_FIELD_BIAS);
			Double noiseDev = mapMessage.getDouble(RemusSensorPerturbation.DATA_FIELD_NOISE_DEV);
			Double anchor = mapMessage.getDouble(RemusSensorPerturbation.DATA_FIELD_ANCHOR);
			Double anchorProbability = mapMessage.getDouble(RemusSensorPerturbation.DATA_FIELD_ANCHOR_PROB);

			RemusSensorPerturbation rsp = new RemusSensorPerturbation(sensorName, bias, noiseDev, anchor, anchorProbability);

			LOG.debug("Sending Sensor Perturbation data to listeners");

			for (SensorPerturbationListener listener : this.sensorPerturbationListeners) {
				listener.sensorPerturbationUpdate(rsp);
			}

			LOG.debug("Sensor Perturbation listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
