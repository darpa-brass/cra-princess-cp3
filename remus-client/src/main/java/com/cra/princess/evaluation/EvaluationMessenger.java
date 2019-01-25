package com.cra.princess.evaluation;

import com.cra.princess.evaluation.messages.*;
import com.cra.princess.evaluation.util.EvaluationUtils;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQMapMessage;
import org.apache.log4j.Logger;
import scala.collection.JavaConverters;

import javax.jms.*;
import java.io.*;
import java.lang.IllegalStateException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * Use to send requests to the ReSTful test harness service
 *
 */
public class EvaluationMessenger implements MessageListener {
  private static final Logger LOG = Logger.getLogger(EvaluationMessenger.class.getName());

  // Property File
  private Properties evaluationProperties = null;

  private static final String PROPERTY_FILE_NAME = "princess.properties";
  private static final String JMS_URL_PROPERTY = "JMS_URL";

  private Connection connection = null;
  private Session session = null;

  private static final String ERROR_TOPIC = "princess.error";
  private Destination errorTopic = null;
  private MessageProducer errorProducer = null;

  private static final String RUNTIME_TOPIC = "princess.runtime";
  private Destination runtimeTopic = null;
  private MessageProducer runtimeProducer = null;

  private static final String RESPONSE_TOPIC = "harness.response";
  private Destination responseTopic = null;
  private MessageConsumer responseConsumer = null;

  private String readyResponse = null;
  private String pathResponse = null;

  // Singleton
  private static EvaluationMessenger instance = null;

  private void loadPropertiesAsResource() {
    try {
      URL propertyFileUrl = this.getClass().getClassLoader().getResource(PROPERTY_FILE_NAME);
      if (null == propertyFileUrl) throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
      String propertyFile = propertyFileUrl.getFile();
      this.evaluationProperties.load(new FileReader(new File(propertyFile)));
    } catch (IOException e) {
      throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
    }
  }

  private EvaluationMessenger() {
    this.evaluationProperties = new Properties();

    try {
      // Try looking for the file in the file system
      FileReader reader = new FileReader(new File(PROPERTY_FILE_NAME));
      this.evaluationProperties.load(reader);
      LOG.debug("Loaded properties from " + PROPERTY_FILE_NAME);
    } catch (IOException e) {
      // The file does not exist in the current working directory - use the embedded resource
      LOG.warn("Cannot read file " + PROPERTY_FILE_NAME + " in current directory. Using default settings.");
      loadPropertiesAsResource();
    }

    ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory(this.evaluationProperties.getProperty(JMS_URL_PROPERTY));
    try {
      this.connection = factory.createConnection();
      this.connection.start();
      this.session = this.connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

      // Create the error topic message producer
      this.errorTopic = this.session.createTopic(ERROR_TOPIC);
      this.errorProducer = this.session.createProducer(this.errorTopic);

      // Create the runtime topic message producer
      this.runtimeTopic = this.session.createTopic(RUNTIME_TOPIC);
      this.runtimeProducer = this.session.createProducer(this.runtimeTopic);

      // Create the response topic message consumer
      this.responseTopic = this.session.createTopic(RESPONSE_TOPIC);
      this.responseConsumer = this.session.createConsumer(this.responseTopic);
      this.responseConsumer.setMessageListener(this);

    } catch (JMSException e) {
      LOG.error(e);
    }
  }

  public static EvaluationMessenger getInstance() {
    if (instance == null) {
      instance = new EvaluationMessenger();
    }

    return instance;
  }

  /**
   * Notification by the DAS that the system failed to initialize
   */
  public void sendInitializationFailureError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_INITIALIZATION_FAILURE, reasonForFailure);
  }

  /**
   * Notification by the DAS that the system failed to generate a search path
   */
  public void sendPathGenerationFailureError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_PATH_GENERATION_FAILURE, reasonForFailure);
  }

  /**
   * Notification by the DAS that the system failed to generate a scenario
   */
  public void sendScenarioGenerationFailureError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_SCENARIO_GENERATION_FAILURE, reasonForFailure);
  }

  /**
   * Notification by the DAS that the system failed to generate a scenario that was accepted by the simulator
   */
  public void sendScenarioFailureError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_SCENARIO_FAILURE, reasonForFailure);
  }

  /**
   * Notification by the DAS that an error occurred while the system was adapting
   */
  public void sendAdaptationError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_ADAPTATION_ERROR, reasonForFailure);
  }

  /**
   * Notification by the DAS that the system has encountered an error that left it in an unusable state
   */
  public void sendSystemFailureError(String reasonForFailure) {
    sendErrorMessage(TestHarnessAdapterConstants.ERROR_SYSTEM_FAILURE, reasonForFailure);
  }

  /*
   * Notification by the DAS that an error occurred during startup or processing of test-specific information
   *
   * @param errorType type of error being reported
   * @param errorMessage free text of arbitrary length with error details
   */
  private void sendErrorMessage(String errorType, String errorMessage) {
    if (EvaluationUtils.validateErrorType(errorType) == false) {
      String msg = "Invalid error type: " + errorType;
      LOG.error(msg);
      throw new IllegalArgumentException(msg);
    }

    LOG.debug("Sending ERROR message: " + errorType + ": " + errorMessage);

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", errorType);
      mapMessage.setString("messageContent", errorMessage);
      this.errorProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }
  }

  /**
   * Notification by the DAS that it has received and processed any test-specific information and
   * that the target system is launched, configured, and ready to process test inputs
   *
   * @return the JSON formatted InitialParams, to be used to initialize the scenario
   */
  public String sendReadyMessage() {
    LOG.debug("Sending READY message");

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", TestHarnessAdapterConstants.STATE_READY);
      mapMessage.setString("messageContent", "");
      this.runtimeProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }

    // Block and wait for response
    while (this.readyResponse == null) {
      try {
        Thread.sleep(50);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }

    String val = this.readyResponse;
    this.readyResponse = null;

    return val;
  }

  /**
   * Notification by the DAS that all input parameters are accepted and scenario generation has started
   */
  public void sendScenarioGenerationStartedMessage() {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_SCENARIO_GENERATION_STARTED, "Unused");
  }

  /**
   * Notification by the DAS that scenario generation has completed successfully
   */
  public void sendScenarioGenerationCompletedMessage() {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_SCENARIO_GENERATION_COMPLETED, "Unused");
  }

  /**
   * Notification by the DAS that scenario has started
   */
  public void sendScenarioStartedMessage() {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_SCENARIO_STARTED, "Unused");
  }

  /**
   * Notification by the DAS that an intent violation was detected
   */
  public void sendIntentViolationDetectedMessage(String msg) {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_INTENT_VIOLATION_DETECTED, msg);
  }

  /**
   * Notification by the DAS that a sensor perturbation was detected
   */
  public void sendPerturbationDetectedMessage(String sensorName, Double confidence) {
    String timestamp = EvaluationUtils.getTimestamp();
    String status = TestHarnessAdapterConstants.STATUS_PERTURBATION_DETECTED;
    PerturbationDetectedMessageBody pdmb = PerturbationDetectedMessageBody.apply(FailedSensorType.apply(sensorName, confidence));
    PerturbationDetectedMessage pdm = PerturbationDetectedMessage.apply(timestamp, status, pdmb);
    String msg = pdm.toJson().replace("ConfidenceOfFailure", "Confidence-of-failure");
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_PERTURBATION_DETECTED, msg);

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", TestHarnessAdapterConstants.STATUS_PERTURBATION_DETECTED);
      mapMessage.setString("messageContent", msg);
      this.runtimeProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }
  }

  /**
   * Notification by the DAS that the system is adapting to an intent violation
   */
  public void sendAdaptationStartedMessage(String msg) {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_ADAPTATION_STARTED, msg);
  }

  /**
   * Notification by the DAS that the system adaptation is complete
   */
  public void sendAdaptationCompletedMessage(String msg) {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_ADAPTATION_COMPLETED, msg);
  }

  /**
   * Notification by the DAS that the system adaptation was unable to complete
   */
  public void sendAdaptationFailureMessage(String reasonForFailure) {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_ADAPTATION_FAILURE, reasonForFailure);
  }

  /**
   * Notification by the DAS that the search target object was located
   */
  public void sendObjectLocatedMessage(double objectLat, double objectLon) {
    String jsonMessage = "{Lat: " + objectLat + ", Lon: " + objectLon + "}";
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_OBJECT_FOUND, jsonMessage);
  }

  /**
   * Notification by the DAS that the scenario has completed successfully
   */
  public void sendScenarioCompletedMessage() {
    sendStatusMessage(TestHarnessAdapterConstants.STATUS_SCENARIO_COMPLETED, "Unused");
  }

  /*
   * Notification by the DAS of a change in status, typically associated with the occurrence of
   * a test event that identifies a discrete phase of test execution
   *
   * @param statusType type of status being reported
   * @param statusMessage free text of arbitrary length with status details
   */
  private void sendStatusMessage(String statusType, String statusMessage) {
    if (!EvaluationUtils.validateStatusType(statusType)) {
      String msg = "Invalid status type: " + statusType;
      LOG.error(msg);
      throw new IllegalArgumentException(msg);
    }

    LOG.debug("Sending STATUS message: " + statusType + ": " + statusMessage);

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", statusType);
      mapMessage.setString("messageContent", statusMessage);
      this.runtimeProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }
  }

  /**
   * Notification by the DAS that test execution has completed
   *
   * @param sufficientPower true if platform had sufficient power to return home
   * @param objectDetected true if platform found target object of search
   * @param lat the final location latitude
   * @param lon the final location longitude
   * @param distanceFromDestination the distance from the destination
   */
  public void sendCp3DoneMessage(boolean sufficientPower, boolean objectDetected, double lat, double lon, double distanceFromDestination)
  {
    LOG.debug("Sending CP3 DONE message");

    String timestamp = EvaluationUtils.getTimestamp();
    CP3ResultsType results = new CP3ResultsType(sufficientPower, objectDetected, lat, lon, distanceFromDestination);
    CP3SutFinishedStatus sfs = new CP3SutFinishedStatus(timestamp, TestHarnessAdapterConstants.STATUS_RESULTS, results);

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", TestHarnessAdapterConstants.STATE_DONE);
      mapMessage.setString("messageContent", sfs.toJson());
      this.runtimeProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }
  }

  /**
   * Notification by the DAS that the search path has been generated
   *
   * @param path the ordered list of waypoints that make up the search path
   * @param maxSpeedMetersPerSecond the maximum speed of the platform while executing a search
   * @return the JSON formatted BatteryPerturbations, to be used to initialize the scenario
   */
  public String sendPathMessage(List<LatLon> path, double maxSpeedMetersPerSecond)
  {
    String timestamp = EvaluationUtils.getTimestamp();

    LOG.debug("Sending PATH message");

    List<LatLon> waypoints = new ArrayList<>();
    for (LatLon waypoint : path) {
      waypoints.add(waypoint);
    }
    scala.collection.immutable.List<LatLon> scalaWps = JavaConverters.asScalaBuffer(waypoints).toList();
    SearchPath sp = new SearchPath(timestamp, Double.toString(maxSpeedMetersPerSecond), scalaWps);

    MapMessage mapMessage = new ActiveMQMapMessage();
    try {
      mapMessage.setString("messageType", TestHarnessAdapterConstants.STATE_PATH);
      mapMessage.setString("messageContent", sp.toJson());
      this.runtimeProducer.send(mapMessage);
    } catch (JMSException e) {
      LOG.error(e);
    }

    // Block and wait for response
    while (this.pathResponse == null) {
      try {
        Thread.sleep(50);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }

    String val = this.pathResponse;
    this.pathResponse = null;

    return val;
  }

  @Override
  public void onMessage(Message message) {
    if (message instanceof MapMessage || message instanceof ActiveMQMapMessage) {
      LOG.debug("New MapMessage received");

      MapMessage mapMessage = (MapMessage)message;
      try {
        String responseType = mapMessage.getString("messageType");
        String responseContent = mapMessage.getString("messageContent");

        if (responseType.equals(TestHarnessAdapterConstants.STATE_READY)) {
          this.readyResponse = responseContent;
        }
        else if (responseType.equals(TestHarnessAdapterConstants.STATE_PATH)) {
          this.pathResponse = responseContent;
        }
        else {
          LOG.warn("Unexpected response message type received: " + responseType);
        }
      } catch (JMSException e) {
        LOG.error(e);
      }
    }
    else {
      LOG.warn("Unexpected JMS message type received: " + message.getClass().toString());
    }
  }
}