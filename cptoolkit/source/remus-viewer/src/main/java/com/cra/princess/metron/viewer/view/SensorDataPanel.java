package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.remus.state.*;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class SensorDataPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 250;
	private static int PANEL_HEIGHT = 105;

	private JLabel powerValue = null;
	private JLabel rpmValue = null;
	private JLabel waterSpeedValue = null;
	private JLabel objectDetectionValue = null;

	public SensorDataPanel() {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setLayout(new GridLayout(4, 2, 1, 1));
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Other Sensor Data"));

		JLabel powerLabel = new JLabel("Energy (Wh)");
		this.powerValue = new JLabel();
		JLabel rpmLabel = new JLabel("Propeller RPM");
		this.rpmValue = new JLabel();
		JLabel waterSpeedLabel = new JLabel("Water Speed (m/s)");
		this.waterSpeedValue = new JLabel();
		JLabel objectDetectionLabel = new JLabel("Target Object");
		this.objectDetectionValue = new JLabel();

		this.add(powerLabel);
		this.add(powerValue);
		this.add(rpmLabel);
		this.add(rpmValue);
		this.add(waterSpeedLabel);
		this.add(waterSpeedValue);
		this.add(objectDetectionLabel);
		this.add(objectDetectionValue);

		reset();
	}

	public void updatePowerData(RemusPowerState powerState) {
		double power = powerState.getPower();

		this.powerValue.setText(String.format("%.4f", power));

		repaint();
	}

	public void updateRpmSensorData(RemusRpmData rpmDataUpdateMessage) {
		double rpm = rpmDataUpdateMessage.getRpm();

		this.rpmValue.setText(String.format("%.1f", rpm));

	    repaint();
	}

	public void updateWaterSpeedSensorData(RemusWaterSpeedData waterSpeedDataUpdateMessage) {
		double speed = waterSpeedDataUpdateMessage.getSpeed();

		this.waterSpeedValue.setText(String.format("%.1f", speed));

		repaint();
	}

	public void updateObjectDetection(RemusObjectDetectionState objectDetectionState) {
		this.objectDetectionValue.setText("DETECTED");

		repaint();
	}

	public void reset() {
		this.powerValue.setText("0.0");
		this.rpmValue.setText("0.0");
		this.waterSpeedValue.setText("0.0");
		this.objectDetectionValue.setText("Not Found");

		repaint();
	}
}
