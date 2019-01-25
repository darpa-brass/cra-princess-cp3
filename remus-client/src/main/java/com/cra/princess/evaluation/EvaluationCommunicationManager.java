package com.cra.princess.evaluation;

import com.cra.princess.evaluation.util.EvaluationUtils;
import com.cra.princess.metron.remus.state.SystemRuntimeState;
import com.cra.princess.metron.remus.state.SystemRuntimeStateUpdateListener;
import com.cra.princess.metron.topic.SystemRuntimeStateTopicWatcher;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQMapMessage;
import org.apache.log4j.Logger;

import javax.jms.*;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.lang.IllegalStateException;
import java.net.URL;
import java.util.Properties;

/**
 * Sends runtime state messages to the ReSTful test harness service
 *
 */
public class EvaluationCommunicationManager extends Thread implements SystemRuntimeStateUpdateListener {
    private static final Logger LOG = Logger.getLogger(EvaluationCommunicationManager.class.getName());

    private Properties managerProperties = null;
    private static final String PROPERTY_FILE_NAME = "princess.properties";
    private static final String JMS_URL_PROPERTY = "JMS_URL";

    private Connection connection = null;
    private Session session = null;

    private static final String RESPONSE_TOPIC = "harness.response";
    private Destination responseTopic = null;
    private MessageProducer responseProducer = null;

    private TestHarnessAdapter testHarnessAdapter = null;
    private SystemRuntimeStateTopicWatcher runtimeStateTopicWatcher = null;

    private boolean working = true;

    public EvaluationCommunicationManager() {
        this.testHarnessAdapter = TestHarnessAdapter.getInstance();

        this.managerProperties = new Properties();

        try {
            // Try looking for the file in the file system
            FileReader reader = new FileReader(new File(PROPERTY_FILE_NAME));
            this.managerProperties.load(reader);
            LOG.debug("Loaded properties from " + PROPERTY_FILE_NAME);
        } catch (IOException e) {
            // The file does not exist in the current working directory - use the embedded resource
            LOG.warn("Cannot read file " + PROPERTY_FILE_NAME + " in current directory. Using default settings.");
            loadPropertiesAsResource();
        }

        ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory(this.managerProperties.getProperty(JMS_URL_PROPERTY));
        try {
            this.connection = factory.createConnection();
            this.connection.start();
            this.session = this.connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

            // Create the topic to send responses back to PRINCESS
            this.responseTopic = this.session.createTopic(RESPONSE_TOPIC);
            this.responseProducer = this.session.createProducer(this.responseTopic);

            // Create topic watchers to get updates from PRINCESS
            this.runtimeStateTopicWatcher = new SystemRuntimeStateTopicWatcher(this.session);
            this.runtimeStateTopicWatcher.addSystemRuntimeStateUpdateListener(this);
            this.runtimeStateTopicWatcher.start();
        } catch (JMSException e) {
            LOG.error(e);
        }
    }

    private void loadPropertiesAsResource() {
        try {
            URL propertyFileUrl = this.getClass().getClassLoader().getResource(PROPERTY_FILE_NAME);
            if (null == propertyFileUrl) throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
            String propertyFile = propertyFileUrl.getFile();
            this.managerProperties.load(new FileReader(new File(propertyFile)));
        } catch (IOException e) {
            throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
        }
    }

    @Override
    public void run() {
        LOG.debug("Starting Evaluation Communication Manager");
        while (this.working) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                // Ignore
            }
        }

        this.runtimeStateTopicWatcher.stopWatching();
    }

    public void stopWork() {
        this.working = false;
    }

    @Override
    public void systemRuntimeStateUpdate(SystemRuntimeState runtimeStateUpdateMessage) {
        if (runtimeStateUpdateMessage != null) {
            String type = runtimeStateUpdateMessage.getMessageType();
            String content = runtimeStateUpdateMessage.getMessageContent();
            String response = null;
            MapMessage responseMessage = null;

            if (EvaluationUtils.validateStatusType(type) == true || EvaluationUtils.validateStateType(type) == true) {
                try {
                    if (type.equalsIgnoreCase(TestHarnessAdapterConstants.STATE_READY)) {
                        response = this.testHarnessAdapter.sendReadyMessage();

                        // Send READY response to harness.response topic
                        responseMessage = new ActiveMQMapMessage();
                        try {
                            responseMessage.setString(SystemRuntimeState.DATA_FIELD_MESSAGE_TYPE, TestHarnessAdapterConstants.STATE_READY);
                            responseMessage.setString(SystemRuntimeState.DATA_FIELD_MESSAGE_CONTENT, response);
                            this.responseProducer.send(responseMessage);
                        } catch (JMSException e) {
                            LOG.error(e.getMessage(), e);
                        }
                    }
                    else if (type.equalsIgnoreCase(TestHarnessAdapterConstants.STATE_PATH)) {
                        response = this.testHarnessAdapter.sendPathMessage(content);

                        // Send PATH response to harness.response topic
                        responseMessage = new ActiveMQMapMessage();
                        try {
                            responseMessage.setString(SystemRuntimeState.DATA_FIELD_MESSAGE_TYPE, TestHarnessAdapterConstants.STATE_PATH);
                            responseMessage.setString(SystemRuntimeState.DATA_FIELD_MESSAGE_CONTENT, response);
                            this.responseProducer.send(responseMessage);
                        } catch (JMSException e) {
                            LOG.error(e.getMessage(), e);
                        }
                    }
                    else if (type.equalsIgnoreCase(TestHarnessAdapterConstants.STATUS_PERTURBATION_DETECTED)) {
                        this.testHarnessAdapter.sendPerturbationDetectedMessage(content);
                    }
                    else if (type.equalsIgnoreCase(TestHarnessAdapterConstants.STATE_DONE)) {
                        this.testHarnessAdapter.sendDoneMessage(content);
                    }
                    else {
                        this.testHarnessAdapter.sendStatusMessage(type, content);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            else {
                LOG.error("Invalid Status or State Type: " + type);
            }
        }
        else {
            LOG.error("Missing runtime state message");
        }
    }
}
