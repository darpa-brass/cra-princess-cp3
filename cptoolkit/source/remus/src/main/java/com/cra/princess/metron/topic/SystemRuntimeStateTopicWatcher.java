package com.cra.princess.metron.topic;

import com.cra.princess.metron.remus.state.SystemRuntimeState;
import com.cra.princess.metron.remus.state.SystemRuntimeStateUpdateListener;
import org.apache.log4j.Logger;

import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Class for handling state update messages from a running PRINCESS challenge problem.
 * 
 */
public class SystemRuntimeStateTopicWatcher extends JmsTopicWatcher {
	private static final Logger LOG = Logger.getLogger(SystemRuntimeStateTopicWatcher.class.getName());

    private List<SystemRuntimeStateUpdateListener> systemRuntimeStateUpdateListeners = null;

    public SystemRuntimeStateTopicWatcher(Session session) {
    	super(session, SystemRuntimeState.RUNTIME_TOPIC);

    	this.systemRuntimeStateUpdateListeners = new CopyOnWriteArrayList<SystemRuntimeStateUpdateListener>();
    }
    
    public void addSystemRuntimeStateUpdateListener(SystemRuntimeStateUpdateListener listener) {
    	this.systemRuntimeStateUpdateListeners.add(listener);
    }

    public void removeSystemRuntimeStateUpdateListener(SystemRuntimeStateUpdateListener listener) {
    	this.systemRuntimeStateUpdateListeners.remove(listener);
    }    

    @Override
    protected void processMapMessage(MapMessage mapMessage) {
		try {
			// System Runtime State Message

			LOG.debug("New system runtime state update received");

			String messageType = mapMessage.getString(SystemRuntimeState.DATA_FIELD_MESSAGE_TYPE);
			String messageContent = mapMessage.getString(SystemRuntimeState.DATA_FIELD_MESSAGE_CONTENT);

			SystemRuntimeState srs = new SystemRuntimeState(messageType, messageContent);

			LOG.debug("Sending system runtime state update to listeners");

			for (SystemRuntimeStateUpdateListener listener : this.systemRuntimeStateUpdateListeners) {
				listener.systemRuntimeStateUpdate(srs);
			}

			LOG.debug("System runtime state listeners updated");
		} catch (JMSException e) {
			LOG.error(e);
		}
    }
    
    @Override
    protected void processTextMessage(TextMessage textMessage) {
    }
}
