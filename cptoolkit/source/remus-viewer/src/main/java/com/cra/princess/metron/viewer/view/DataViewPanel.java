package com.cra.princess.metron.viewer.view;

import java.awt.BorderLayout;

import javax.swing.BoxLayout;
import javax.swing.JPanel;

import com.cra.princess.metron.remus.state.*;
import com.cra.princess.metron.viewer.controller.RemusViewerController;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 16, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class DataViewPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	
	private GroundTruthDataPanel groundTruthDataPanel = null;
	private DvlSensorDataPanel dvlSensorDataPanel = null;
	private SensorDataPanel sensorDataPanel = null;

	public DataViewPanel(RemusViewerController controller, ColorChooserDialog colorChooserDialog, RemusTrackPanel trackPanel) {
		super();

		this.setLayout(new BorderLayout());
		
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		
		this.groundTruthDataPanel = new GroundTruthDataPanel();
		panel.add(this.groundTruthDataPanel);

		this.dvlSensorDataPanel = new DvlSensorDataPanel();
		panel.add(this.dvlSensorDataPanel);

		this.sensorDataPanel = new SensorDataPanel();
		panel.add(this.sensorDataPanel);

		this.add(panel, BorderLayout.NORTH);
	}
	
	public void updateGroundTruthTrack(RemusVehicleState vehicleState) {
		this.groundTruthDataPanel.updateGroundTruthData(vehicleState);
	}

	public void updateDvlSensorData(RemusDvlData dvlDataUpdateMessage) {
		this.dvlSensorDataPanel.updateDvlSensorData(dvlDataUpdateMessage);
	}	

	public void updatePowerData(RemusPowerState powerState) {
		this.sensorDataPanel.updatePowerData(powerState);
	}

	public void updateRpmSensorData(RemusRpmData rpmDataUpdateMessage) {
		this.sensorDataPanel.updateRpmSensorData(rpmDataUpdateMessage);
	}

	public void updateWaterSpeedSensorData(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
		this.sensorDataPanel.updateWaterSpeedSensorData(waterSpeedDataUpdateMessage);
	}

	public void updateObjectDetection(RemusObjectDetectionState objectDetectionState) {
		this.sensorDataPanel.updateObjectDetection(objectDetectionState);
	}

	public void reset() {
		this.groundTruthDataPanel.reset();
		this.dvlSensorDataPanel.reset();
		this.sensorDataPanel.reset();
	}
}
