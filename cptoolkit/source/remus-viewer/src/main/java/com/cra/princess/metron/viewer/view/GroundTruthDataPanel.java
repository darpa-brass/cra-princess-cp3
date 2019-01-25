package com.cra.princess.metron.viewer.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import com.cra.princess.metron.remus.state.RemusVehicleState;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 16, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class GroundTruthDataPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 250;
	private static int PANEL_HEIGHT = 320;

	private JLabel latValue = null;
	private JLabel lonValue = null;
	private JLabel depthValue = null;
	private JLabel vEValue = null;
	private JLabel vNValue = null;
	private JLabel vUValue = null;
	private JLabel currentEValue = null;
	private JLabel currentNValue = null;
	private JLabel pitchValue = null;
	private JLabel rollValue = null;
	private JLabel headingValue = null;
	private JLabel surgeValue = null;
	private JLabel swayValue = null;
	private JLabel heaveValue = null;

	public GroundTruthDataPanel() {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setLayout(new GridLayout(14, 2, 1, 1));
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Ground Truth Data"));
		
		JLabel latLabel = new JLabel("Latitude");
		this.latValue = new JLabel();
		JLabel lonLabel = new JLabel("Longitude");
		this.lonValue = new JLabel();
		JLabel depthLabel = new JLabel("Depth (m)");
		this.depthValue = new JLabel();
		JLabel vELabel = new JLabel("vE (m/s)");
		this.vEValue = new JLabel();
		JLabel vNLabel = new JLabel("vN (m/s)");
		this.vNValue = new JLabel();
		JLabel vULabel = new JLabel("vU (m/s)");
		this.vUValue = new JLabel();
		JLabel currentELabel = new JLabel("Current vE (m/s)");
		this.currentEValue = new JLabel();
		JLabel currentNLabel = new JLabel("Current vN (m/s)");
		this.currentNValue = new JLabel();
		JLabel pitchLabel = new JLabel("Pitch (deg)");
		this.pitchValue = new JLabel();
		JLabel rollLabel = new JLabel("Roll (deg)");
		this.rollValue = new JLabel();
		JLabel headingLabel = new JLabel("Heading (deg)");
		this.headingValue = new JLabel();
		JLabel surgeLabel = new JLabel("Surge (deg)");
		this.surgeValue = new JLabel();
		JLabel swayLabel = new JLabel("Sway (deg)");
		this.swayValue = new JLabel();
		JLabel heaveLabel = new JLabel("Heave (deg)");
		this.heaveValue = new JLabel();

		this.add(latLabel);
		this.add(latValue);
		this.add(lonLabel);
		this.add(lonValue);
		this.add(depthLabel);
		this.add(depthValue);
		this.add(vELabel);
		this.add(vEValue);
		this.add(vNLabel);
		this.add(vNValue);
		this.add(vULabel);
		this.add(vUValue);
		this.add(currentELabel);
		this.add(currentEValue);
		this.add(currentNLabel);
		this.add(currentNValue);
		this.add(pitchLabel);
		this.add(pitchValue);
		this.add(rollLabel);
		this.add(rollValue);
		this.add(headingLabel);
		this.add(headingValue);
		this.add(surgeLabel);
		this.add(surgeValue);
		this.add(swayLabel);
		this.add(swayValue);
		this.add(heaveLabel);
		this.add(heaveValue);

		reset();
	}
	
	public void updateGroundTruthData(RemusVehicleState vehicleState) {
		double trueLatitude = vehicleState.getTrueLatitude();
		double trueLongitude = vehicleState.getTrueLongitude();
		double trueDepth = vehicleState.getTrueDepth();
		double vE = vehicleState.getvE();
		double vN = vehicleState.getvN();
		double vU = vehicleState.getvU();
		double currentE = vehicleState.getWaterCurrentE();
		double currentN = vehicleState.getWaterCurrentN();
		double pitch = vehicleState.getPitch();
		double roll = vehicleState.getRoll();
		double heading = vehicleState.getHeading();
		double surge = vehicleState.getSurge();
		double sway = vehicleState.getSway();
		double heave = vehicleState.getHeave();

		this.latValue.setText(String.format("%.4f", trueLatitude));
		this.lonValue.setText(String.format("%.4f", trueLongitude));
		this.depthValue.setText(String.format("%.1f", trueDepth));
		this.vEValue.setText(String.format("%.1f", vE));
		this.vNValue.setText(String.format("%.1f", vN));
		this.vUValue.setText(String.format("%.1f", vU));
		this.currentEValue.setText(String.format("%.1f", currentE));
		this.currentNValue.setText(String.format("%.1f", currentN));
		this.pitchValue.setText(String.format("%.1f", pitch));
		this.rollValue.setText(String.format("%.1f", roll));
		this.headingValue.setText(String.format("%.1f", heading));
		this.surgeValue.setText(String.format("%.1f", surge));
		this.swayValue.setText(String.format("%.1f", sway));
		this.heaveValue.setText(String.format("%.1f", heave));
		
	    repaint();
	}

	public void reset() {
		this.latValue.setText("0.0");
		this.lonValue.setText("0.0");
		this.depthValue.setText("0.0");
		this.vEValue.setText("0.0");
		this.vNValue.setText("0.0");
		this.vUValue.setText("0.0");
		this.currentEValue.setText("0.0");
		this.currentNValue.setText("0.0");
		this.pitchValue.setText("0.0");
		this.rollValue.setText("0.0");
		this.headingValue.setText("0.0");
		this.surgeValue.setText("0.0");
		this.swayValue.setText("0.0");
		this.heaveValue.setText("0.0");

		repaint();
	}
}
