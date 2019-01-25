package com.cra.princess.metron.viewer.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import com.cra.princess.metron.remus.state.RemusDvlData;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class DvlSensorDataPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 250;
	private static int PANEL_HEIGHT = 230;

	private JLabel depthValue = null;
	private JLabel vEValue = null;
	private JLabel vNValue = null;
	private JLabel vUValue = null;
	private JLabel pitchValue = null;
	private JLabel rollValue = null;
	private JLabel headingValue = null;
	private JLabel surgeValue = null;
	private JLabel swayValue = null;
	private JLabel heaveValue = null;

	public DvlSensorDataPanel() {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setLayout(new GridLayout(10, 2, 1, 1));
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "DVL Sensor Data"));
		
		JLabel depthLabel = new JLabel("Depth (m)");
		this.depthValue = new JLabel();
		JLabel vELabel = new JLabel("vE (m/s)");
		this.vEValue = new JLabel();
		JLabel vNLabel = new JLabel("vN (m/s)");
		this.vNValue = new JLabel();
		JLabel vULabel = new JLabel("vU (m/s)");
		this.vUValue = new JLabel();
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

		this.add(depthLabel);
		this.add(depthValue);
		this.add(vELabel);
		this.add(vEValue);
		this.add(vNLabel);
		this.add(vNValue);
		this.add(vULabel);
		this.add(vUValue);
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
	
	public void updateDvlSensorData(RemusDvlData dvlDataUpdateMessage) {
		double trueDepth = dvlDataUpdateMessage.getDepth();
		double vE = dvlDataUpdateMessage.getvE();
		double vN = dvlDataUpdateMessage.getvN();
		double vU = dvlDataUpdateMessage.getvU();
		double pitch = dvlDataUpdateMessage.getPitch();
		double roll = dvlDataUpdateMessage.getRoll();
		double heading = dvlDataUpdateMessage.getHeading();
		double surge = dvlDataUpdateMessage.getSurge();
		double sway = dvlDataUpdateMessage.getSway();
		double heave = dvlDataUpdateMessage.getHeave();

		this.depthValue.setText(String.format("%.1f", trueDepth));
		this.vEValue.setText(String.format("%.1f", vE));
		this.vNValue.setText(String.format("%.1f", vN));
		this.vUValue.setText(String.format("%.1f", vU));
		this.pitchValue.setText(String.format("%.1f", pitch));
		this.rollValue.setText(String.format("%.1f", roll));
		this.headingValue.setText(String.format("%.1f", heading));
		this.surgeValue.setText(String.format("%.1f", surge));
		this.swayValue.setText(String.format("%.1f", sway));
		this.heaveValue.setText(String.format("%.1f", heave));

	    repaint();
	}
	
	public void reset() {
		this.depthValue.setText("0.0");
		this.vEValue.setText("0.0");
		this.vNValue.setText("0.0");
		this.vUValue.setText("0.0");
		this.pitchValue.setText("0.0");
		this.rollValue.setText("0.0");
		this.headingValue.setText("0.0");
		this.surgeValue.setText("0.0");
		this.swayValue.setText("0.0");
		this.heaveValue.setText("0.0");

		repaint();
	}
}
