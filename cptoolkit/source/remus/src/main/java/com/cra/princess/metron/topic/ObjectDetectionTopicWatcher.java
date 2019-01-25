package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.ObjectDetectionListener;
import com.cra.princess.metron.remus.state.RemusObjectDetectionState;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling object detection sensor messages from the REMUS simulator.
 * 
 */
public class ObjectDetectionTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(ObjectDetectionTopicWatcher.class.getName());

    private List<ObjectDetectionListener> objectDetectionListeners = null;

    public ObjectDetectionTopicWatcher(Session session) {
    	super(session, RemusObjectDetectionState.OBJECT_DETECTION_TOPIC);

    	this.objectDetectionListeners = new CopyOnWriteArrayList<ObjectDetectionListener>();
    }
    
    public void addObjectDetectionListener(ObjectDetectionListener listener) {
    	this.objectDetectionListeners.add(listener);
    }

    public void removeObjectDetectionListener(ObjectDetectionListener listener) {
    	this.objectDetectionListeners.remove(listener);
    }    

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// Object Detection Message

			LOG.debug("New REMUS object detection update received");

			Long timestamp = mapMessage.getLong(RemusObjectDetectionState.DATA_FIELD_TIMESTAMP);
			Double range = mapMessage.getDouble(RemusObjectDetectionState.DATA_FIELD_RANGE);
			Double theta = mapMessage.getDouble(RemusObjectDetectionState.DATA_FIELD_THETA);
			Double phi = mapMessage.getDouble(RemusObjectDetectionState.DATA_FIELD_PHI);

			RemusObjectDetectionState rods = new RemusObjectDetectionState(timestamp, range, theta, phi);

			LOG.debug("Sending object detection update to listeners");

			for (ObjectDetectionListener listener : this.objectDetectionListeners) {
				listener.objectDetected(rods);
			}

			LOG.debug("Object detection listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
