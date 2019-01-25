package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.MetronRemusManager;
import com.cra.princess.metron.RemusManagerException;
import com.cra.princess.metron.remus.command.RemusVehicleCommand;
import com.cra.princess.metron.remus.perturbation.RemusBatteryPerturbation;
import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;
import com.cra.princess.metron.viewer.controller.RemusViewerController;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: May 20, 2018<br>
 * <br>
 * Copyright 2018 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class ControlPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private JTextField speedValue = null;
	private JTextField headingValue = null;
	private JTextField depthValue = null;

	private JComboBox<String> sensorNameValue = null;
	private JTextField biasValue = null;
	private JTextField noiseDevValue = null;
	private JTextField anchorValue = null;
	private JTextField anchorProbabilityValue = null;

	private static final String[] sensorNames = new String[] {"", "dvl_roll", "dvl_pitch", "dvl_yaw", "dvl_depth", "dvl_altitude", "dvl_surge", "dvl_sway", "dvl_heave", "water_speed", "rpm"};

	private JTextField powerReductionValue = null;

	private int PANEL_WIDTH = 300;

	public ControlPanel(RemusViewerController controller) {
		super();

		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

		JPanel vehicleCommandPanel = new JPanel();
		vehicleCommandPanel.setMaximumSize(new Dimension(PANEL_WIDTH, 120));
		vehicleCommandPanel.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Send Vehicle Command"));
		vehicleCommandPanel.setLayout(new GridLayout(4, 2, 1, 1));
		JLabel speedLabel = new JLabel("Speed (m/s)");
		this.speedValue = new JTextField(3);
		JLabel headingLabel = new JLabel("Heading (deg)");
		this.headingValue = new JTextField(3);
		JLabel depthLabel = new JLabel("Depth (m)");
		this.depthValue = new JTextField(3);
		JButton sendVehicleCommand = new JButton("Send");
		sendVehicleCommand.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				String rawSpeed = speedValue.getText();
				String rawHeading = headingValue.getText();
				String rawDepth = depthValue.getText();

				if ((rawSpeed != null && rawSpeed.isEmpty() == false) &&
						(rawHeading != null && rawHeading.isEmpty() == false) &&
						(rawDepth != null && rawDepth.isEmpty() == false)) {
					double speed = Double.parseDouble(rawSpeed);
					double heading = Double.parseDouble(rawHeading);
					double depth = Double.parseDouble(rawDepth);

					RemusVehicleCommand vehicleCommand = new RemusVehicleCommand(heading, depth, speed);
					try {
						MetronRemusManager.getInstance().sendVehicleCommand(vehicleCommand);
					} catch (RemusManagerException e) {
						e.printStackTrace();
					}
				}
			}
		});

		vehicleCommandPanel.add(speedLabel);
		vehicleCommandPanel.add(this.speedValue);
		vehicleCommandPanel.add(headingLabel);
		vehicleCommandPanel.add(this.headingValue);
		vehicleCommandPanel.add(depthLabel);
		vehicleCommandPanel.add(this.depthValue);
		vehicleCommandPanel.add(sendVehicleCommand);

		JPanel sensorEventPanel = new JPanel();
		sensorEventPanel.setMaximumSize(new Dimension(PANEL_WIDTH, 160));
		sensorEventPanel.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Send Sensor Perturbation"));
		sensorEventPanel.setLayout(new GridLayout(6, 2, 1, 1));
		JLabel sensorNameLabel = new JLabel("Name");
		this.sensorNameValue = new JComboBox<String>(sensorNames);
		JLabel biasLabel = new JLabel("Bias");
		this.biasValue = new JTextField(3);
		JLabel noiseDevLabel = new JLabel("Noise Dev");
		this.noiseDevValue = new JTextField(3);
		JLabel anchorLabel = new JLabel("Anchor");
		this.anchorValue = new JTextField(3);
		JLabel anchorProbLabel = new JLabel("Anchor Prob");
		this.anchorProbabilityValue = new JTextField(3);
		JButton sendSensorPerturbation = new JButton("Send");
		sendSensorPerturbation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				String sensorName = (String)sensorNameValue.getSelectedItem();
				String rawBias = biasValue.getText();
				String rawNoiseDev = noiseDevValue.getText();
				String rawAnchor = anchorValue.getText();
				String rawAnchorProbability = anchorProbabilityValue.getText();

				if ((sensorName != null && sensorName.isEmpty() == false) &&
						(rawBias != null && rawBias.isEmpty() == false) &&
						(rawNoiseDev != null && rawNoiseDev.isEmpty() == false) &&
						(rawAnchor != null && rawAnchor.isEmpty() == false) &&
						(rawAnchorProbability != null && rawAnchorProbability.isEmpty() == false)) {
					double bias = Double.parseDouble(rawBias);
					double noiseDev = Double.parseDouble(rawNoiseDev);
					double anchor = Double.parseDouble(rawAnchor);
					double anchorProbability = Double.parseDouble(rawAnchorProbability);

					RemusSensorPerturbation sensorPerturbation = new RemusSensorPerturbation(sensorName, bias, noiseDev, anchor, anchorProbability);
					try {
					 MetronRemusManager.getInstance().sendSensorPerturbation(sensorPerturbation);
					} catch (RemusManagerException e) {
						e.printStackTrace();
					}
				}
			}
		});

		sensorEventPanel.add(sensorNameLabel);
		sensorEventPanel.add(this.sensorNameValue);
		sensorEventPanel.add(biasLabel);
		sensorEventPanel.add(this.biasValue);
		sensorEventPanel.add(noiseDevLabel);
		sensorEventPanel.add(this.noiseDevValue);
		sensorEventPanel.add(anchorLabel);
		sensorEventPanel.add(this.anchorValue);
		sensorEventPanel.add(anchorProbLabel);
		sensorEventPanel.add(this.anchorProbabilityValue);
		sensorEventPanel.add(sendSensorPerturbation);

		JPanel powerEventPanel = new JPanel();
		powerEventPanel.setMaximumSize(new Dimension(PANEL_WIDTH, 70));
		powerEventPanel.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Send Battery Perturbation"));
		powerEventPanel.setLayout(new GridLayout(2, 2, 1, 1));
		JLabel powerReductionLabel = new JLabel("Power Reduction (%)");
		this.powerReductionValue = new JTextField(3);
		JButton sendBatteryPerturbation = new JButton("Send");
		sendBatteryPerturbation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				String rawPowerReduction = powerReductionValue.getText();

				if (rawPowerReduction != null && rawPowerReduction.isEmpty() == false) {
					double powerReduction = Double.parseDouble(rawPowerReduction);

				 	RemusBatteryPerturbation batteryPerturbation = new RemusBatteryPerturbation(powerReduction);
				 	try {
				  		MetronRemusManager.getInstance().sendBatteryPerturbation(batteryPerturbation);
					 } catch (RemusManagerException e) {
					 	e.printStackTrace();
					 }
				}
			}
		});

		powerEventPanel.add(powerReductionLabel);
		powerEventPanel.add(this.powerReductionValue);
		powerEventPanel.add(sendBatteryPerturbation);

		this.add(vehicleCommandPanel);
		this.add(sensorEventPanel);
		this.add(powerEventPanel);
	}
}
