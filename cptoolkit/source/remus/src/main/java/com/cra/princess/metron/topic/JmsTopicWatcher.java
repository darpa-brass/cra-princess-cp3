package com.cra.princess.metron.topic;

import javax.jms.*;

import com.cra.princess.evaluation.messages.SerializationException;
import org.apache.activemq.command.ActiveMQBytesMessage;
import org.apache.activemq.command.ActiveMQMapMessage;
import org.apache.activemq.command.ActiveMQTextMessage;
import org.apache.log4j.Logger;

import java.io.UnsupportedEncodingException;

/**
 * Abstract class for handling JMS messages from the Metron REMUS simulator.
 * 
 */
public abstract class JmsTopicWatcher extends Thread implements MessageListener {
	private static final Logger LOG = Logger.getLogger(JmsTopicWatcher.class.getName());

    private boolean isRunning = true;
    private String topicName = null;
    private Session session = null;
    private Destination topic = null;
    
    public JmsTopicWatcher(Session session, String topicName) {
    	super();

    	this.session = session;
    	this.topicName = topicName;
    }
    
    @Override
    public void run() {
        // Create the topic to get data updates from the REMUS simulator
        try {
			this.topic = this.session.createTopic(this.topicName);
	        MessageConsumer consumer = this.session.createConsumer(this.topic);
	        consumer.setMessageListener(this);
        } catch (JMSException e) {
        	LOG.error(e);
        	isRunning = false;
		}

        while(this.isRunning) {
    		try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				LOG.warn(e);
			}
    	}
    }
    
    public void stopWatching() {
        LOG.debug("Stopping JmsTopicWatcher");
        isRunning = false;
        LOG.debug("JmsTopicWatcher stopped");
    }

    @Override
    public void onMessage(Message message) {
    	if (isRunning && (message instanceof MapMessage || message instanceof ActiveMQMapMessage)) {
        	LOG.debug("New MapMessage received from simulator");

        	processMapMessage((MapMessage)message);
        }
    	else if (isRunning && (message instanceof TextMessage || message instanceof ActiveMQTextMessage)) {
        	LOG.debug("New TextMessage received from simulator");

        	processTextMessage((TextMessage)message);
        }
        else if (isRunning && (message instanceof BytesMessage || message instanceof ActiveMQBytesMessage)) {
    		LOG.debug("New BytesMessage received from simulator");
    		processBytesMessage((BytesMessage)message);
		}
    	else {
        	LOG.warn("Unexpected JMS message type received from simulator: " + message.getClass().toString());
    	}
    }

    protected String readBytesAsString(BytesMessage msg) throws SerializationException {
		try {
			byte[] bytes = new byte[(int)msg.getBodyLength()];
			msg.readBytes(bytes);
			return new String(bytes, "UTF-8");
		} catch (JMSException | UnsupportedEncodingException e) {
			throw new SerializationException(e.getMessage(), e);
		}
	}
    
    protected void processMapMessage(MapMessage mapMessage) {}
    protected void processTextMessage(TextMessage textMessage) {}
    protected void processBytesMessage(BytesMessage bytesMessage) {}
}
