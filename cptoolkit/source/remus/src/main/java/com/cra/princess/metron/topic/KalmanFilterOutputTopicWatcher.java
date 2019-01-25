package com.cra.princess.metron.topic;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.log4j.Logger;

import com.cra.princess.metron.remus.state.KalmanFilterOutputListener;

/**
 * Class for capturing Kalman Filter Output data messages sent from the PRINCESS Kalman Filter.
 * 
 */
public class KalmanFilterOutputTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(KalmanFilterOutputTopicWatcher.class.getName());

	public static final String KF_OUTPUT_TOPIC = "princess.vehicle.location.estimated";

	private List<KalmanFilterOutputListener> kalmanFilterOutputListeners = null;
    
    public KalmanFilterOutputTopicWatcher(Session session) {
    	super(session, KF_OUTPUT_TOPIC);

    	this.kalmanFilterOutputListeners = new CopyOnWriteArrayList<KalmanFilterOutputListener>();
    }
    
    public void addKalmanFilterOutputListener(KalmanFilterOutputListener listener) {
    	this.kalmanFilterOutputListeners.add(listener);
    }

    public void removeKalmanFilterOutputListener(KalmanFilterOutputListener listener) {
    	this.kalmanFilterOutputListeners.remove(listener);
    }     

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
		try {
			// Kalman Filter Output

			LOG.debug("New Kalman Filter Output received");
			
			String json = textMessage.getText();
			com.cra.princess.messaging.types.Location location = com.cra.princess.messaging.types.Location$.MODULE$.fromJson(json);

			LOG.debug("Sending Kalman Filter Output data to listeners");

			for (KalmanFilterOutputListener listener : this.kalmanFilterOutputListeners) {
				listener.kalmanFilterOutputUpdate(location);
			}

			LOG.debug("Kalman Filter Output listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
}
