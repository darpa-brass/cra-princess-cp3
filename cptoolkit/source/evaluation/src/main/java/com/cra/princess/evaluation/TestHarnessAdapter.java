package com.cra.princess.evaluation;

import com.cra.princess.evaluation.messages.*;
import com.cra.princess.evaluation.util.EvaluationUtils;
import org.apache.log4j.Logger;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Properties;

/**
 * Use to send requests to the ReSTful test harness service
 *
 */
public class TestHarnessAdapter {
  private static final Logger LOG = Logger.getLogger(TestHarnessAdapter.class.getName());

  // Property File
  private Properties evaluationProperties = null;

  private static final String PROPERTY_FILE_NAME = "princess.properties";

  // HTTP
  private static final int CONTROL_MESSAGE_TIMEOUT_MS = 5000;
  private static final String CONTROL_MESSAGE_REQUEST_METHOD = "POST";
  private static final String CONTROL_MESSAGE_CONTENT_TYPE = "application/json";

  private static final String ERROR_URL_ENDPOINT = "error";
  private static final String READY_URL_ENDPOINT = "ready";
  private static final String STATUS_URL_ENDPOINT = "status";
  private static final String DONE_URL_ENDPOINT = "done";
  private static final String PATH_URL_ENDPOINT = "path";
  private static final String CONFIG_URL_ENDPOINT = "config";

  // Singleton
  private static TestHarnessAdapter instance = null;

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

  private TestHarnessAdapter() {
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
  }

  public static TestHarnessAdapter getInstance() {
    if (instance == null) {
      instance = new TestHarnessAdapter();
    }

    return instance;
  }

  /**
   * Notification by the DAS that an error occurred during startup or processing of test-specific information
   *
   * @param errorType type of error being reported
   * @param errorMessage free text of arbitrary length with error details
   * @throws IOException error
   */
  public void sendErrorMessage(String errorType, String errorMessage) throws IOException {
    String timestamp = EvaluationUtils.getTimestamp();

    if (EvaluationUtils.validateErrorType(errorType) == false) {
      String msg = "Invalid error type: " + errorType;
      LOG.error(msg);
      throw new IllegalArgumentException(msg);
    }

    LOG.debug("Sending ERROR message: " + errorType + ": " + errorMessage);

    String urlEndpoint = ERROR_URL_ENDPOINT;

    ErrorMessage em = new ErrorMessage(timestamp, errorType, errorMessage);
    sendTestHarnessRequest(urlEndpoint, em.toJson());
  }

  /**
   * Notification by the DAS that it has received and processed any test-specific information and
   * that the target system is launched, configured, and ready to process test inputs
   *
   * @return the JSON formatted InitialParams, to be used to initialize the scenario
   * @throws IOException error
   */
  public String sendReadyMessage() throws IOException {
    String timestamp = EvaluationUtils.getTimestamp();

    LOG.debug("Sending READY message");

    String urlEndpoint = READY_URL_ENDPOINT;

    ReadyMessage rm = new ReadyMessage(timestamp);
    return sendTestHarnessRequest(urlEndpoint, rm.toJson());
  }

  /**
   * Set the config directory the Mock Test Harness should load
   *
   * @throws IOException error
   */
  public void sendConfigMessage(String configName) throws IOException {
    String timestamp = EvaluationUtils.getTimestamp();

    LOG.debug("Sending CONFIG message");

    String urlEndpoint = CONFIG_URL_ENDPOINT;

    sendTestHarnessRequest(urlEndpoint, configName);
  }

  /**
   * Notification by the DAS of a change in status, typically associated with the occurrence of
   * a test event that identifies a discrete phase of test execution
   *
   * @param statusType type of status being reported
   * @param statusMessage free text of arbitrary length with status details
   * @throws IOException error
   */
  public void sendStatusMessage(String statusType, String statusMessage) throws IOException {
    String timestamp = EvaluationUtils.getTimestamp();

    if (!EvaluationUtils.validateStatusType(statusType)) {
      String msg = "Invalid status type: " + statusType;
      LOG.error(msg);
      throw new IllegalArgumentException(msg);
    }

    LOG.debug("Sending STATUS message: " + statusType + ": " + statusMessage);

    String urlEndpoint = STATUS_URL_ENDPOINT;

    StatusMessage sm = new StatusMessage(timestamp, statusType, statusMessage);
    sendTestHarnessRequest(urlEndpoint, sm.toJson());
  }

  /**
   * Notification by the DAS that test execution has completed
   *
   * @param resultsJson JSON-formatted results (see CP3 description document)
   */
  public void sendDoneMessage(String resultsJson) throws IOException
  {
    LOG.debug("Sending DONE message");

    String urlEndpoint = DONE_URL_ENDPOINT;

    LOG.debug(resultsJson);

    sendTestHarnessRequest(urlEndpoint, resultsJson);
  }

  /**
   * Notification by the DAS that a perturbation has been detected
   *
   * @param perturbationDetectedMessageJson the JSON text of the message to send
   * @throws IOException error
   */
  public void sendPerturbationDetectedMessage(String perturbationDetectedMessageJson) throws IOException {
    LOG.debug("Sending PERTURBATION_DETECTED message");

    String urlEndpoint = STATUS_URL_ENDPOINT;

    LOG.debug(perturbationDetectedMessageJson);

    sendTestHarnessRequest(urlEndpoint, perturbationDetectedMessageJson);
  }

  /**
   * Notification by the DAS that the search path has been generated
   *
   * @param searchPathJson JSON-formatted search path (see CP3 description document)
   * @return the JSON formatted BatteryPerturbations, to be used to initialize the scenario
   */
  public String sendPathMessage(String searchPathJson) throws IOException
  {
    LOG.debug("Sending PATH message");

    String urlEndpoint = PATH_URL_ENDPOINT;

    LOG.debug(searchPathJson);

    return sendTestHarnessRequest(urlEndpoint, searchPathJson);
  }

  // Sends an HTTP request to the Test Harness service and returns any response as a String
  private String sendTestHarnessRequest(String urlEndpoint, String content) throws IOException {
    StringBuilder responseCollector = new StringBuilder();

    if (urlEndpoint == null || urlEndpoint.isEmpty()) {
      String msg = "Missing test control message URL endpoint";
      LOG.error(msg);

      throw new IllegalArgumentException(msg);
    }

    if (content == null || content.isEmpty()) {
      String msg = "Missing test control message content";
      LOG.error(msg);

      throw new IllegalArgumentException(msg);
    }

    String urlString = this.evaluationProperties.getProperty(EvaluationUtils.BASE_URL_PROPERTY) + "/" + urlEndpoint;

    HttpURLConnection connection = null;
    BufferedReader inputReader = null;
    OutputStream os = null;

    try {
      // Set up the connection
      URL url = new URL(urlString);
      connection = (HttpURLConnection)url.openConnection();
      connection.setReadTimeout(CONTROL_MESSAGE_TIMEOUT_MS);
      connection.setRequestMethod(CONTROL_MESSAGE_REQUEST_METHOD);
      connection.setDoInput(true);
      connection.setDoOutput(true);
      connection.setUseCaches(false);
      connection.setRequestProperty("Accept", "text/html, text/plain, application/json");
      connection.setRequestProperty("Content-Type", CONTROL_MESSAGE_CONTENT_TYPE);
      connection.setRequestProperty("Content-Length", new Integer(content.length()).toString());

      // Write the content
      // The request is automatically sent when the output stream is closed
      os = connection.getOutputStream();
      os.write(content.getBytes());
      os.flush();
      os.close();
      os = null;

      // Process the response
      InputStream inputStream = connection.getInputStream();
      if (inputStream != null) {
        inputReader = new BufferedReader(new InputStreamReader(inputStream));
        String inputLine = null;
        while ((inputLine = inputReader.readLine()) != null) {
          responseCollector.append(inputLine);
        }
      }
    }
    catch (IOException e) {
      LOG.error(e);
      // Re-throw
      throw e;
    }
    finally {
      try {
        if (os != null) {
          os.close();
        }

        if (inputReader != null) {
          inputReader.close();
        }

        if (connection != null) {
          connection.disconnect();
        }
      } catch (IOException e) {
        LOG.error(e);
      }
    }

    return responseCollector.toString();
  }
}