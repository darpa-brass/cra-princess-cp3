package com.cra.princess.metron.viewer.capture;

// import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.viewer.controller.RemusViewerController;
import org.apache.log4j.Logger;

/**
 * A tool to capture incoming messages and save them as a set of JMS Test Harness map message data files<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 17, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class JmsTestHarnessCapture {
	private static Logger LOG = Logger.getLogger(JmsTestHarnessCapture.class.getName());

	private VehicleGroundTruthMessageWriter vehicleGroundTruthMessageWriter = null;
	private DvlSensorMessageWriter dvlSensorMessageWriter = null;
	private TransformedDvlSensorMessageWriter transformedDvlSensorMessageWriter = null;
	private VehicleCommandMessageWriter vehicleCommandMessageWriter = null;
	private SimulationControlMessageWriter simulationControlMessageWriter = null;
	private KalmanFilterMessageWriter kalmanFilterOutputMessageWriter = null;
	private VehiclePowerMessageWriter vehiclePowerMessageWriter = null;
	private ObjectDetectionMessageWriter objectDetectionMessageWriter = null;
	private RpmSensorMessageWriter rpmSensorMessageWriter = null;
	private WaterSpeedSensorMessageWriter waterSpeedSensorMessageWriter = null;
	// private BatteryPerturbationMessageWriter batteryPerturbationMessageWriter = null;
	// private SensorPerturbationMessageWriter sensorPerturbationMessageWriter = null;

	public JmsTestHarnessCapture(RemusViewerController controller) {
		if (controller == null) {
			String msg = "No controller provided";
			LOG.error(msg);
			throw new IllegalArgumentException(msg);
		}

		this.vehicleGroundTruthMessageWriter = new VehicleGroundTruthMessageWriter(controller);
		this.dvlSensorMessageWriter = new DvlSensorMessageWriter(controller);
		this.transformedDvlSensorMessageWriter = new TransformedDvlSensorMessageWriter(controller);
		this.vehicleCommandMessageWriter = new VehicleCommandMessageWriter(controller);
		this.simulationControlMessageWriter = new SimulationControlMessageWriter(controller);
		this.kalmanFilterOutputMessageWriter = new KalmanFilterMessageWriter(controller);
		this.vehiclePowerMessageWriter = new VehiclePowerMessageWriter(controller);
		this.objectDetectionMessageWriter = new ObjectDetectionMessageWriter(controller);
		this.rpmSensorMessageWriter = new RpmSensorMessageWriter(controller);
		this.waterSpeedSensorMessageWriter = new WaterSpeedSensorMessageWriter(controller);
		// this.batteryPerturbationMessageWriter = new BatteryPerturbationMessageWriter(controller);
		// this.sensorPerturbationMessageWriter = new SensorPerturbationMessageWriter(controller);
	}

	public void start() {
		this.vehicleGroundTruthMessageWriter.start();
		this.dvlSensorMessageWriter.start();
		this.transformedDvlSensorMessageWriter.start();
		this.vehicleCommandMessageWriter.start();
		this.simulationControlMessageWriter.start();
		this.kalmanFilterOutputMessageWriter.start();
		this.vehiclePowerMessageWriter.start();
		this.objectDetectionMessageWriter.start();
		this.rpmSensorMessageWriter.start();
		this.waterSpeedSensorMessageWriter.start();
		// this.batteryPerturbationMessageWriter.start();
		// this.sensorPerturbationMessageWriter.start();

		LOG.debug("JmsTestHarnessCapture started");
	}

	public void stopCapture() {
		this.vehicleGroundTruthMessageWriter.stopCapture();
		this.dvlSensorMessageWriter.stopCapture();
		this.transformedDvlSensorMessageWriter.stopCapture();
		this.vehicleCommandMessageWriter.stopCapture();
		this.simulationControlMessageWriter.stopCapture();
		this.kalmanFilterOutputMessageWriter.stopCapture();
		this.vehiclePowerMessageWriter.stopCapture();
		this.objectDetectionMessageWriter.stopCapture();
		this.rpmSensorMessageWriter.stopCapture();
		this.waterSpeedSensorMessageWriter.stopCapture();
		// this.batteryPerturbationMessageWriter.stopCapture();
		// this.sensorPerturbationMessageWriter.stopCapture();

		LOG.debug("JmsTestHarnessCapture stopped");
	}
}
