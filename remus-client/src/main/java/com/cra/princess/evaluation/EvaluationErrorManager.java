package com.cra.princess.evaluation;

import com.cra.princess.evaluation.util.EvaluationUtils;
import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.topic.SystemRuntimeErrorTopicWatcher;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.log4j.Logger;

import javax.jms.Connection;
import javax.jms.JMSException;
import javax.jms.Session;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Properties;

/**
 * Sends runtime error messages to the ReSTful test harness service
 *
 */
public class EvaluationErrorManager extends Thread implements SystemRuntimeErrorUpdateListener {
    private static final Logger LOG = Logger.getLogger(EvaluationErrorManager.class.getName());

    private Properties managerProperties = null;
    private static final String PROPERTY_FILE_NAME = "princess.properties";
    private static final String JMS_URL_PROPERTY = "JMS_URL";

    private Connection connection = null;
    private Session session = null;

    private TestHarnessAdapter testHarnessAdapter = null;
    private SystemRuntimeErrorTopicWatcher runtimeErrorTopicWatcher = null;

    private boolean working = true;

    public EvaluationErrorManager() {
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

            // Create topic watchers to get updates from PRINCESS
            this.runtimeErrorTopicWatcher = new SystemRuntimeErrorTopicWatcher(this.session);
            this.runtimeErrorTopicWatcher.addSystemRuntimeErrorUpdateListener(this);
            this.runtimeErrorTopicWatcher.start();
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
        LOG.debug("Starting Evaluation Error Manager");
        while (this.working) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                // Ignore
            }
        }

        this.runtimeErrorTopicWatcher.stopWatching();
    }

    public void stopWork() {
        this.working = false;
    }

    @Override
    public void systemRuntimeErrorUpdate(SystemRuntimeError errorStateUpdateMessage) {
        if (errorStateUpdateMessage != null) {
            if (EvaluationUtils.validateErrorType(errorStateUpdateMessage.getErrorType()) == true) {
                try {
                    String errorType = errorStateUpdateMessage.getErrorType();
                    this.testHarnessAdapter.sendErrorMessage(errorType, errorStateUpdateMessage.getErrorContent());

                    if (errorType.equals(TestHarnessAdapterConstants.ERROR_INITIALIZATION_FAILURE) ||
                            errorType.equals(TestHarnessAdapterConstants.ERROR_SCENARIO_FAILURE) ||
                            errorType.equals(TestHarnessAdapterConstants.ERROR_SCENARIO_GENERATION_FAILURE) ||
                            errorType.equals(TestHarnessAdapterConstants.ERROR_PATH_GENERATION_FAILURE) ||
                            errorType.equals(TestHarnessAdapterConstants.ERROR_SYSTEM_FAILURE)) {
                        princessDead();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            else {
                LOG.error("Invalid Error Type: " + errorStateUpdateMessage.getErrorType());
            }
        }
        else {
            LOG.error("Missing error state message");
        }
    }

    // Set PRINCESS "alive" state to false
    private void princessDead() {
        String urlString = "http://localhost:8081/setAlive/false";

        HttpURLConnection connection = null;
        InputStream is = null;

        try {
            // Set up the HTTP GET request
            URL url = new URL(urlString);
            connection = (HttpURLConnection)url.openConnection();
            connection.setReadTimeout(5000);
            connection.setRequestMethod("GET");
            connection.setUseCaches(false);
            connection.setRequestProperty("Content-Type", "text/plain");
            is = connection.getInputStream();
        }
        catch (IOException e) {
            LOG.error(e);
        }
        finally {
            if (is != null) {
                try {
                    is.close();
                } catch (IOException e) {
                    LOG.error(e);
                }
            }

            if (connection != null) {
                connection.disconnect();
            }
        }
    }
}
