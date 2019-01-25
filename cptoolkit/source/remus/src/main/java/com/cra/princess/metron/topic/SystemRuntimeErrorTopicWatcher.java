package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.SystemRuntimeError;
import com.cra.princess.metron.remus.state.SystemRuntimeErrorUpdateListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling error messages from a running PRINCESS challenge problem.
 * 
 */
public class SystemRuntimeErrorTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(SystemRuntimeErrorTopicWatcher.class.getName());

    private List<SystemRuntimeErrorUpdateListener> systemRuntimeErrorUpdateListeners = null;

    public SystemRuntimeErrorTopicWatcher(Session session) {
    	super(session, SystemRuntimeError.ERROR_TOPIC);

    	this.systemRuntimeErrorUpdateListeners = new CopyOnWriteArrayList<SystemRuntimeErrorUpdateListener>();
    }
    
    public void addSystemRuntimeErrorUpdateListener(SystemRuntimeErrorUpdateListener listener) {
    	this.systemRuntimeErrorUpdateListeners.add(listener);
    }

    public void removeSystemRuntimeErrorUpdateListener(SystemRuntimeErrorUpdateListener listener) {
    	this.systemRuntimeErrorUpdateListeners.remove(listener);
    }    

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// System Runtime Error Message

			LOG.debug("New system runtime error update received");

			String messageType = mapMessage.getString(SystemRuntimeError.DATA_FIELD_MESSAGE_TYPE);
			String messageContent = mapMessage.getString(SystemRuntimeError.DATA_FIELD_MESSAGE_CONTENT);

			SystemRuntimeError sre = new SystemRuntimeError(messageType, messageContent);

			LOG.debug("Sending system runtime error update to listeners");

			for (SystemRuntimeErrorUpdateListener listener : this.systemRuntimeErrorUpdateListeners) {
				listener.systemRuntimeErrorUpdate(sre);
			}

			LOG.debug("System runtime error listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
