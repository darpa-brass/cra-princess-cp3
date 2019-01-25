package com.cra.princess.metron;

import java.io.*;
import java.lang.IllegalStateException;
import java.net.URL;
import java.util.Properties;

import javax.jms.*;

import com.cra.princess.evaluation.messages.TransformedDvlReading;
import com.cra.princess.messaging.SensorPerturbation;
import com.cra.princess.messaging.types.Location;
import com.cra.princess.metron.remus.control.SimulationControlMessage;
import com.cra.princess.metron.remus.perturbation.RemusBatteryPerturbation;
import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;
import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.topic.*;
import com.cra.princess.power.PowerReductionEvent;
import com.cra.princess.power.RemusPowerSimulator;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.log4j.Logger;

import com.cra.princess.messaging.VehicleCommand;
import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.control.SimulationControlListener;

/**
 * Class for handling the messages to and from the Metron REMUS simulator.
 *
 */
public class MetronRemusManager {
	private static final Logger LOG = Logger.getLogger(MetronRemusManager.class.getName());

	// Singleton
	private static MetronRemusManager instance = null;

    private Properties managerProperties = null;
	private static final String PROPERTY_FILE_NAME = "princess.properties";
	private static final String JMS_URL_PROPERTY = "JMS_URL";

    private Connection connection = null;
    private Session session = null;

    private static final String ESTIMATED_LOCATION_TOPIC = "princess.vehicle.location.estimated";

    private Destination commandTopic = null;
    private Destination controlTopic = null;
    private Destination sensorPerturbationTopic = null;
    private Destination batteryPerturbationTopic = null;
    private Destination estimatedLocationTopic = null;
    private Destination transformedDvlDataTopic = null;
    private MessageProducer commandProducer = null;
    private MessageProducer controlProducer = null;
    private MessageProducer sensorPerturbationProducer = null;
    private MessageProducer batteryPerturbationProducer = null;
    private MessageProducer estimatedLocationProducer = null;
    private MessageProducer transformedDvlDataProducer = null;

    private GroundTruthTopicWatcher groundTruthTopicWatcher = null;
    private DvlDataTopicWatcher dvlDataTopicWatcher = null;
    private SimulationControlTopicWatcher simulationControlTopicWatcher = null;
    private ObjectDetectionTopicWatcher objectDetectionTopicWatcher = null;
    private RpmDataTopicWatcher rpmDataTopicWatcher = null;
    private WaterSpeedDataTopicWatcher waterSpeedDataTopicWatcher = null;
    private VehicleCommandTopicWatcher vehicleCommandTopicWatcher = null;
    private PowerTopicWatcher powerTopicWatcher = null;
    private TransformedDvlDataTopicWatcher transformedDvlDataTopicWatcher = null;

    private RemusPowerSimulator remusPowerSimulator = null;

    private boolean isStarted = false;

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

    private MetronRemusManager() {
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

            // Create the topic to send vehicle commands to the REMUS
            this.commandTopic = this.session.createTopic(RemusVehicleCommand.VEHICLE_COMMAND_TOPIC);
            this.commandProducer = this.session.createProducer(this.commandTopic);

            // Create the topic to send control commands to the REMUS simulator
            this.controlTopic = this.session.createTopic(SimulationControlMessage.CONTROL_TOPIC);
            this.controlProducer = this.session.createProducer(this.controlTopic);

            // Create the topic to send sensor perturbation events to the REMUS simulator
            this.sensorPerturbationTopic = this.session.createTopic(RemusSensorPerturbation.SENSOR_PERTURBATION_TOPIC);
            this.sensorPerturbationProducer = this.session.createProducer(this.sensorPerturbationTopic);

            // Create the topic to send battery perturbation events to the REMUS power simulator
            this.batteryPerturbationTopic = this.session.createTopic(RemusBatteryPerturbation.BATTERY_PERTURBATION_TOPIC);
            this.batteryPerturbationProducer = this.session.createProducer(this.batteryPerturbationTopic);

            // Create the topic to send estimated location to the viewer
            this.estimatedLocationTopic = this.session.createTopic(ESTIMATED_LOCATION_TOPIC);
            this.estimatedLocationProducer = this.session.createProducer(this.estimatedLocationTopic);

            // Create the topic to send transformed DVL data (to be consumed by RemusClient)
            this.transformedDvlDataTopic = this.session.createTopic(TransformedRemusDvlData.TRANSFORMED_DVL_SENSOR_TOPIC);
            this.transformedDvlDataProducer = this.session.createProducer(this.transformedDvlDataTopic);

        	// Create topic watchers to get updates from the REMUS simulator
            this.groundTruthTopicWatcher = new GroundTruthTopicWatcher(this.session);
            this.dvlDataTopicWatcher = new DvlDataTopicWatcher(this.session);
            this.simulationControlTopicWatcher = new SimulationControlTopicWatcher(this.session);
            this.objectDetectionTopicWatcher = new ObjectDetectionTopicWatcher(this.session);
            this.rpmDataTopicWatcher = new RpmDataTopicWatcher(this.session);
            this.waterSpeedDataTopicWatcher = new WaterSpeedDataTopicWatcher(this.session);
            this.vehicleCommandTopicWatcher = new VehicleCommandTopicWatcher(this.session);
            this.powerTopicWatcher = new PowerTopicWatcher(this.session);

            // Create topic watchers to receive transformed DVL data
            this.transformedDvlDataTopicWatcher = new TransformedDvlDataTopicWatcher(this.session);

            // Create the REMUS Power Simulator
            this.remusPowerSimulator = new RemusPowerSimulator(2200.0, this.session);
            this.groundTruthTopicWatcher.addVehicleGroundTruthUpdateListener(this.remusPowerSimulator);
        } catch (JMSException e) {
        	LOG.error(e);
        }
    }

    public static MetronRemusManager getInstance() {
    	if (instance == null) {
    		instance = new MetronRemusManager();
    	}

    	return instance;
    }

    public void addVehicleGroundTruthUpdateListener(VehicleGroundTruthUpdateListener listener) {
    	this.groundTruthTopicWatcher.addVehicleGroundTruthUpdateListener(listener);
    }

    public void removeVehicleGroundTruthUpdateListener(VehicleGroundTruthUpdateListener listener) {
    	this.groundTruthTopicWatcher.removeVehicleGroundTruthUpdateListener(listener);
    }

    public void addDvlSensorUpdateListener(DvlSensorUpdateListener listener) {
    	this.dvlDataTopicWatcher.addDvlSensorUpdateListener(listener);
    }

    public void removeDvlSensorUpdateListener(DvlSensorUpdateListener listener) {
    	this.dvlDataTopicWatcher.removeDvlSensorUpdateListener(listener);
    }

    public void addSimulationControlListener(SimulationControlListener listener) {
    	this.simulationControlTopicWatcher.addSimulationControlListener(listener);
    }

    public void removeSimulationControlListener(SimulationControlListener listener) {
    	this.simulationControlTopicWatcher.removeSimulationControlListener(listener);
    }

    public void addObjectDetectionListener(ObjectDetectionListener listener) {
        this.objectDetectionTopicWatcher.addObjectDetectionListener(listener);
    }

    public void removeObjectDetectionListener(ObjectDetectionListener listener) {
        this.objectDetectionTopicWatcher.removeObjectDetectionListener(listener);
    }

    public void addRpmSensorUpdateListener(RpmSensorUpdateListener listener) {
        this.rpmDataTopicWatcher.addRpmSensorUpdateListener(listener);
    }

    public void removeRpmSensorUpdateListener(RpmSensorUpdateListener listener) {
        this.rpmDataTopicWatcher.removeRpmSensorUpdateListener(listener);
    }

    public void addWaterSpeedSensorUpdateListener(WaterSpeedSensorUpdateListener listener) {
        this.waterSpeedDataTopicWatcher.addWaterSpeedSensorUpdateListener(listener);
    }

    public void removeWaterSpeedSensorUpdateListener(RpmSensorUpdateListener listener) {
        this.rpmDataTopicWatcher.removeRpmSensorUpdateListener(listener);
    }

    public void addVehiclePowerUpdateListener(VehiclePowerUpdateListener listener) {
        this.powerTopicWatcher.addVehiclePowerUpdateListener(listener);
    }

    public void removeVehiclePowerUpdateListener(VehiclePowerUpdateListener listener) {
        this.powerTopicWatcher.removeVehiclePowerUpdateListener(listener);
    }

    public void addTransformedDvlSensorUpdateListener(TransformedDvlSensorUpdateListener listener) {
      this.transformedDvlDataTopicWatcher.addTransformedDvlSensorUpdateListener(listener);
    }

    public void removeTransformedDvlSensorUpdateListener(TransformedDvlSensorUpdateListener listener) {
      this.transformedDvlDataTopicWatcher.removeTransformedDvlSensorUpdateListener(listener);
    }

    public void sendVehicleCommand(RemusVehicleCommand command) throws RemusManagerException {
        LOG.debug("Sending command to REMUS");

        try {
        	VehicleCommand vc = new VehicleCommand();
        	vc.headingTarget = command.getHeadingTarget();
        	vc.depthTarget = command.getDepthTarget();
        	vc.speedTarget = command.getSpeedTarget();

        	this.commandProducer.send(vc.toMapMessage());
        } catch (Exception e) {
        	LOG.error(e);
        	throw new RemusManagerException(e);
        }

        LOG.debug("Command sent to REMUS");
    }

    public void sendSensorPerturbation(RemusSensorPerturbation perturbation) throws RemusManagerException {
        LOG.debug("Sending sensor perturbation to REMUS");

        try {
            SensorPerturbation sp = new SensorPerturbation();
            sp.name = perturbation.getName();
            sp.bias = perturbation.getBias();
            sp.noiseDeviation = perturbation.getNoiseDeviation();
            sp.anchor = perturbation.getAnchor();
            sp.anchorProbability = perturbation.getAnchorProbability();

            this.sensorPerturbationProducer.send(sp.toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Sensor perturbation sent to REMUS");
    }

    public void sendBatteryPerturbation(RemusBatteryPerturbation perturbation) throws RemusManagerException {
        LOG.debug("Sending battery perturbation to REMUS power simulator");

        try {
            this.batteryPerturbationProducer.send(perturbation.toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Battery perturbation sent to REMUS power simulator");
    }

    public void sendSimulationEnded() throws RemusManagerException {
        LOG.debug("Sending Simulation Ended control command to REMUS simulator");

        try {
            SimulationControlMessage simulationEndedMessage = new SimulationControlMessage(SimulationControlMessage.CONTROL_COMMAND_STOP);
            this.controlProducer.send(simulationEndedMessage.mapTo().toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Simulation STOP control command sent to REMUS simulator");
    }

    public void sendSimulationPause() throws RemusManagerException {
        LOG.debug("Pausing simulation");

        try {
            SimulationControlMessage simulationPauseMessage = new SimulationControlMessage(SimulationControlMessage.CONTROL_COMMAND_PAUSE);
            this.controlProducer.send(simulationPauseMessage.mapTo().toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Simulation paused");
    }

    public void sendSimulationResume() throws RemusManagerException {
        LOG.debug("Resuming simulation");

        try {
            SimulationControlMessage simulationResumeMessage = new SimulationControlMessage(SimulationControlMessage.CONTROL_COMMAND_PLAY);
            this.controlProducer.send(simulationResumeMessage.mapTo().toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Simulation resumed");
    }

    public void sendScenarioPlaybackSpeed(double speed) throws RemusManagerException {
        LOG.debug("Changing scenario playback speed to: " + speed);

        try {
            SimulationControlMessage simulationSpeedMessage = new SimulationControlMessage(speed);
            this.controlProducer.send(simulationSpeedMessage.mapTo().toMapMessage());
        } catch (Exception e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }

        LOG.debug("Scenario playback speed changed");
    }

    public void sendEstimatedLocation(Location loc) throws RemusManagerException {
        try {
            String json = loc.toJson();
            Message msg = session.createTextMessage(json);
            this.estimatedLocationProducer.send(msg);
        } catch (JMSException e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }
    }

    public void sendTransformedDvlData(TransformedRemusDvlData data) throws RemusManagerException {
        try {
            MapMessage mapMsg = data.toMapMessage();
            this.transformedDvlDataProducer.send(mapMsg);
        } catch (JMSException e) {
            LOG.error(e);
            throw new RemusManagerException(e);
        }
    }

    public void start() throws RemusManagerException {
        if (this.isStarted == false) {
            LOG.debug("Starting MetronRemusManager");

            this.groundTruthTopicWatcher.start();
            this.dvlDataTopicWatcher.start();
            this.simulationControlTopicWatcher.start();
            this.objectDetectionTopicWatcher.start();
            this.rpmDataTopicWatcher.start();
            this.waterSpeedDataTopicWatcher.start();
            this.vehicleCommandTopicWatcher.start();
            this.powerTopicWatcher.start();
            this.transformedDvlDataTopicWatcher.start();

            this.isStarted = true;

            LOG.debug("MetronRemusManager started");
        }
    }

    public void stop() {
        if (this.isStarted) {
            LOG.debug("Stopping MetronRemusManager");

            this.groundTruthTopicWatcher.stopWatching();
            this.dvlDataTopicWatcher.stopWatching();
            this.simulationControlTopicWatcher.stopWatching();
            this.objectDetectionTopicWatcher.stopWatching();
            this.rpmDataTopicWatcher.stopWatching();
            this.waterSpeedDataTopicWatcher.stopWatching();
            this.vehicleCommandTopicWatcher.stopWatching();
            this.powerTopicWatcher.stopWatching();
            this.transformedDvlDataTopicWatcher.stopWatching();

            try {
                if (this.session != null) {
                    this.session.close();
                }

                if (this.connection != null) {
                    this.connection.close();
                }
            } catch (JMSException e) {
                LOG.error(e);
            } finally {
                this.connection = null;
                this.session = null;
            }

            this.isStarted = false;

            LOG.debug("MetronRemusManager stopped");
        }
    }

    public void addPowerReductionEvent(PowerReductionEvent event) {
        this.remusPowerSimulator.addPowerReductionEvent(event);
    }

    public void startRemusPowerSimulator() {
        this.remusPowerSimulator.start();
    }

    public void stopRemusPowerSimulator() {
        if (this.remusPowerSimulator != null) {
            this.remusPowerSimulator.stop();
        }
    }

    public void pauseRemusPowerSimulator() {
        if (this.remusPowerSimulator != null) {
            this.remusPowerSimulator.pause();
        }
    }

    public void resumeRemusPowerSimulator() throws RemusManagerException {
        if (this.remusPowerSimulator != null) {
            this.remusPowerSimulator.resume();
        }
    }
}
