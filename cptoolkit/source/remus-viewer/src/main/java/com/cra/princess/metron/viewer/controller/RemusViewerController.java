package com.cra.princess.metron.viewer.controller;

import java.io.*;
import java.net.URL;
import java.util.Properties;
import java.awt.*;

import javax.jms.Connection;
import javax.jms.JMSException;
import javax.jms.Session;

import com.cra.princess.metron.remus.control.SimulationControlListener;
import com.cra.princess.metron.remus.perturbation.BatteryPerturbationListener;
import com.cra.princess.metron.remus.perturbation.SensorPerturbationListener;
import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.topic.*;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.log4j.Logger;

import com.cra.princess.metron.RemusManagerException;
import com.cra.princess.metron.remus.command.VehicleCommandListener;
import com.cra.princess.metron.viewer.model.MetronScenarioFileReader;
import com.cra.princess.metron.viewer.model.ScenarioFileReader;

/**
 * Controller
 * 
 */
public class RemusViewerController {
	private static final Logger LOG = Logger.getLogger(RemusViewerController.class.getName());
	
    private Properties viewerProperties = null;
	private static final String PROPERTY_FILE_NAME = "remusviewer.properties";
	private static final String JMS_URL_PROPERTY = "JMS_URL";

    private static final String GROUND_TRUTH_TRACK_COLOR_PROPERTY = "groundTruthTrackColor";
    private static final String DVL_SENSOR_TRACK_COLOR_PROPERTY = "dvlSensorTrackColor";
    private static final String TRANSFORMED_DVL_SENSOR_TRACK_COLOR_PROPERTY = "transformedDvlSensorTrackColor";
    private static final String KALMAN_FILTER_TRACK_COLOR_PROPERTY = "kalmanFilterTrackColor";
    private static final String CURRENT_BORDER_COLOR_PROPERTY = "currentBorderColor";
    private static final String SEARCH_AREA_BORDER_COLOR_PROPERTY = "searchAreaBorderColor";
    private static final String ORIGIN_COLOR_PROPERTY = "originColor";
    private static final String DESTINATION_COLOR_PROPERTY = "destinationColor";

    private Connection connection = null;
    private Session session = null;

    private GroundTruthTopicWatcher truthTopicWatcher = null;
    private DvlDataTopicWatcher dvlDataTopicWatcher = null;
    private TransformedDvlDataTopicWatcher transformedDvlDataTopicWatcher = null;
    private VehicleCommandTopicWatcher vehicleCommandTopicWatcher = null;
    private KalmanFilterOutputTopicWatcher kalmanFilterOutputTopicWatcher = null;
    private PowerTopicWatcher powerTopicWatcher = null;
    private SimulationControlTopicWatcher controlTopicWatcher = null;
    private ObjectDetectionTopicWatcher objectDetectionTopicWatcher = null;
    private RpmDataTopicWatcher rpmTopicWatcher = null;
    private WaterSpeedDataTopicWatcher waterSpeedTopicWatcher = null;
    private BatteryPerturbationTopicWatcher batteryPerturbationTopicWatcher = null;
    private SensorPerturbationTopicWatcher sensorPerturbationTopicWatcher = null;

    public RemusViewerController() {
    	this.viewerProperties = new Properties();

        try {
            // Try looking for the file in the file system
            FileReader reader = new FileReader(new File(PROPERTY_FILE_NAME));
            this.viewerProperties.load(reader);
            LOG.debug("Loaded properties from " + PROPERTY_FILE_NAME);
        } catch (IOException e) {
            // The file does not exist in the current working directory - use the embedded resource
            loadPropertiesAsResource();
        }

        ActiveMQConnectionFactory factory = new ActiveMQConnectionFactory(this.viewerProperties.getProperty(JMS_URL_PROPERTY));
        try {
            this.connection = factory.createConnection();
            this.connection.start();
            this.session = this.connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

            this.truthTopicWatcher = new GroundTruthTopicWatcher(this.session);
            this.dvlDataTopicWatcher = new DvlDataTopicWatcher(this.session);
            this.transformedDvlDataTopicWatcher = new TransformedDvlDataTopicWatcher(this.session);
            this.vehicleCommandTopicWatcher = new VehicleCommandTopicWatcher(this.session);
            this.kalmanFilterOutputTopicWatcher = new KalmanFilterOutputTopicWatcher(this.session);
            this.powerTopicWatcher = new PowerTopicWatcher(this.session);
            this.controlTopicWatcher = new SimulationControlTopicWatcher(this.session);
            this.objectDetectionTopicWatcher = new ObjectDetectionTopicWatcher(this.session);
            this.rpmTopicWatcher = new RpmDataTopicWatcher(this.session);
            this.waterSpeedTopicWatcher = new WaterSpeedDataTopicWatcher(this.session);
            this.batteryPerturbationTopicWatcher = new BatteryPerturbationTopicWatcher(this.session);
            this.sensorPerturbationTopicWatcher = new SensorPerturbationTopicWatcher(this.session);
        } catch (JMSException e) {
            LOG.error(e);
        }
    }

    private void loadPropertiesAsResource() {
        try {
            URL propertyFileUrl = this.getClass().getClassLoader().getResource(PROPERTY_FILE_NAME);
            if (null == propertyFileUrl) throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
            String propertyFile = propertyFileUrl.getFile();
            this.viewerProperties.load(new FileReader(new File(propertyFile)));
        } catch (IOException e) {
            throw new IllegalStateException("Resource not found: " + PROPERTY_FILE_NAME);
        }
    }
    
    public void addVehicleGroundTruthUpdateListener(VehicleGroundTruthUpdateListener groundTruthListener) {
    	this.truthTopicWatcher.addVehicleGroundTruthUpdateListener(groundTruthListener);
    }
    
    public void addDvlSensorUpdateListener(DvlSensorUpdateListener dvlSensorListener) {
    	this.dvlDataTopicWatcher.addDvlSensorUpdateListener(dvlSensorListener);
    }

    public void addTransformedDvlSensorUpdateListener(TransformedDvlSensorUpdateListener transformedDvlSensorListener) {
        this.transformedDvlDataTopicWatcher.addTransformedDvlSensorUpdateListener(transformedDvlSensorListener);
    }

    public void addVehicleCommandUpdateListener(VehicleCommandListener vehicleCommandListener) {
    	this.vehicleCommandTopicWatcher.addVehicleCommandListener(vehicleCommandListener);
    }    

    public void addKalmanFilterOutputListener(KalmanFilterOutputListener kalmanFilterOutputListener) {
    	this.kalmanFilterOutputTopicWatcher.addKalmanFilterOutputListener(kalmanFilterOutputListener);
    }

    public void addPowerListener(VehiclePowerUpdateListener powerListener) {
        this.powerTopicWatcher.addVehiclePowerUpdateListener(powerListener);
    }

    public void addControlListener(SimulationControlListener controlListener) { this.controlTopicWatcher.addSimulationControlListener(controlListener); }

    public void addObjectDetectionListener(ObjectDetectionListener objectDetectionListener) { this.objectDetectionTopicWatcher.addObjectDetectionListener(objectDetectionListener); }

    public void addRpmSensorUpdateListener(RpmSensorUpdateListener rpmSensorUpdateListener) { this.rpmTopicWatcher.addRpmSensorUpdateListener(rpmSensorUpdateListener); }

    public void addWaterSpeedSensorUpdateListener(WaterSpeedSensorUpdateListener waterSpeedSensorUpdateListener) { this.waterSpeedTopicWatcher.addWaterSpeedSensorUpdateListener(waterSpeedSensorUpdateListener); }

    public void addBatteryPerturbationListener(BatteryPerturbationListener batteryPerturbationListener) { this.batteryPerturbationTopicWatcher.addBatteryPerturbationListener(batteryPerturbationListener); }

    public void addSensorPerturbationListener(SensorPerturbationListener sensorPerturbationListener) { this.sensorPerturbationTopicWatcher.addSensorPerturbationListener(sensorPerturbationListener); }

    public void start() throws RemusManagerException {
        LOG.debug("Starting RemusViewerController");

        this.truthTopicWatcher.start();
        this.dvlDataTopicWatcher.start();
        this.transformedDvlDataTopicWatcher.start();
        this.vehicleCommandTopicWatcher.start();
        this.kalmanFilterOutputTopicWatcher.start();
        this.powerTopicWatcher.start();
        this.controlTopicWatcher.start();
        this.objectDetectionTopicWatcher.start();
        this.rpmTopicWatcher.start();
        this.waterSpeedTopicWatcher.start();
        this.batteryPerturbationTopicWatcher.start();
        this.sensorPerturbationTopicWatcher.start();

        LOG.debug("RemusViewerController started");    
    }
    
    public void stop() {
        LOG.debug("Stopping RemusViewerController");
        try {
        	if (this.truthTopicWatcher != null) {
        		this.truthTopicWatcher.stopWatching();
        	}

        	if (this.dvlDataTopicWatcher != null) {
        		this.dvlDataTopicWatcher.stopWatching();
        	}

            if (this.transformedDvlDataTopicWatcher != null) {
                this.transformedDvlDataTopicWatcher.stopWatching();
            }

        	if (this.vehicleCommandTopicWatcher != null) {
        		this.vehicleCommandTopicWatcher.stopWatching();
        	}        	

        	if (this.kalmanFilterOutputTopicWatcher != null) {
        		this.kalmanFilterOutputTopicWatcher.stopWatching();
        	}

            if (this.powerTopicWatcher != null) {
                this.powerTopicWatcher.stopWatching();
            }

            if (this.controlTopicWatcher != null) {
                this.controlTopicWatcher.stopWatching();
            }

            if (this.objectDetectionTopicWatcher != null) {
                this.objectDetectionTopicWatcher.stopWatching();
            }

            if (this.rpmTopicWatcher != null) {
                this.rpmTopicWatcher.stopWatching();
            }

            if (this.waterSpeedTopicWatcher != null) {
                this.waterSpeedTopicWatcher.stopWatching();
            }

            if (this.batteryPerturbationTopicWatcher != null) {
        	    this.batteryPerturbationTopicWatcher.stopWatching();
            }

            if (this.sensorPerturbationTopicWatcher != null) {
        	    this.sensorPerturbationTopicWatcher.stopWatching();
            }

        	if (this.session != null) {
        		this.session.close();
            }

            if (this.connection != null) {
            	this.connection.close();
            }
        } catch (JMSException e) {
            LOG.error(e);
        } finally {
        	this.truthTopicWatcher = null;
        	this.dvlDataTopicWatcher = null;
        	this.transformedDvlDataTopicWatcher = null;
        	this.vehicleCommandTopicWatcher = null;
        	this.kalmanFilterOutputTopicWatcher = null;
            this.powerTopicWatcher = null;
            this.controlTopicWatcher = null;
            this.objectDetectionTopicWatcher = null;
            this.rpmTopicWatcher = null;
            this.waterSpeedTopicWatcher = null;
            this.batteryPerturbationTopicWatcher = null;
            this.sensorPerturbationTopicWatcher = null;

        	this.connection = null;
        	this.session = null;
        }
        LOG.debug("RemusViewerController stopped");
    }
    
    public ScenarioFileReader getScenarioFileReader(File scenarioFile) throws IOException {
    	ScenarioFileReader reader = new MetronScenarioFileReader(scenarioFile);

    	return reader;
    }

    public Color getGroundTruthTrackColor() {
        String colorValue = this.viewerProperties.getProperty(GROUND_TRUTH_TRACK_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setGroundTruthTrackColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(GROUND_TRUTH_TRACK_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getDvlSensorTrackColor() {
        String colorValue = this.viewerProperties.getProperty(DVL_SENSOR_TRACK_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setDvlSensorTrackColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(DVL_SENSOR_TRACK_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getTransformedDvlSensorTrackColor() {
        String colorValue = this.viewerProperties.getProperty(TRANSFORMED_DVL_SENSOR_TRACK_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setTransformedDvlSensorTrackColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(TRANSFORMED_DVL_SENSOR_TRACK_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getKalmanFilterTrackColor() {
        String colorValue = this.viewerProperties.getProperty(KALMAN_FILTER_TRACK_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setKalmanFilterTrackColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(KALMAN_FILTER_TRACK_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getCurrentBorderColor() {
        String colorValue = this.viewerProperties.getProperty(CURRENT_BORDER_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setCurrentBorderColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(CURRENT_BORDER_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getSearchAreaBorderColor() {
        String colorValue = this.viewerProperties.getProperty(SEARCH_AREA_BORDER_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setSearchAreaBorderColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(SEARCH_AREA_BORDER_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getOriginColor() {
        String colorValue = this.viewerProperties.getProperty(ORIGIN_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setOriginColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(ORIGIN_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public Color getDestinationColor() {
        String colorValue = this.viewerProperties.getProperty(DESTINATION_COLOR_PROPERTY);
        String[] rgb = colorValue.split(",");
        return new Color(Integer.parseInt(rgb[0]), Integer.parseInt(rgb[1]), Integer.parseInt(rgb[2]));
    }

    public void setDestinationColor(Color color) {
        String colorValue = Integer.toString(color.getRed()) + "," + Integer.toString(color.getGreen()) + "," + Integer.toString(color.getBlue());
        this.viewerProperties.setProperty(DESTINATION_COLOR_PROPERTY, colorValue);

        try {
            FileOutputStream out = new FileOutputStream(PROPERTY_FILE_NAME);
            this.viewerProperties.store(out, null);
        }
        catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }
}
