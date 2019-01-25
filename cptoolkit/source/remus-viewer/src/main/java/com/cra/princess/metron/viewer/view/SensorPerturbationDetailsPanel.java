package com.cra.princess.metron.viewer.view;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.util.Date;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 21, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class SensorPerturbationDetailsPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 220;
	private static int PANEL_HEIGHT = 130;

	public SensorPerturbationDetailsPanel(String sensorName, double bias, double noiseDeviation,	double anchor, double anchorProbability) {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setBorder(new LineBorder(Color.BLACK, 1));
		
		this.setLayout(new GridLayout(6, 2, 1, 1));

		JLabel timeLabel = new JLabel("Time");
		JLabel timeValue = new JLabel(String.format("%tT", new Date()));
		JLabel sensorLabel = new JLabel("Sensor");
		JLabel sensorValue = new JLabel(sensorName);
		JLabel biasLabel = new JLabel("Bias");
		JLabel biasValue = new JLabel(String.format("%.5f", bias));
		JLabel noiseDevLabel = new JLabel("Noise Dev");
		JLabel noiseDevValue = new JLabel(String.format("%.5f", noiseDeviation));
		JLabel anchorLabel = new JLabel("Anchor");
		JLabel anchorValue = new JLabel(String.format("%.5f", anchor));
		JLabel anchorProbLabel = new JLabel("Anchor Prob");
		JLabel anchorProbValue = new JLabel(String.format("%.5f", anchorProbability));

		this.add(timeLabel);
		this.add(timeValue);
		this.add(sensorLabel);
		this.add(sensorValue);
		this.add(biasLabel);
		this.add(biasValue);
		this.add(noiseDevLabel);
		this.add(noiseDevValue);
		this.add(anchorLabel);
		this.add(anchorValue);
		this.add(anchorProbLabel);
		this.add(anchorProbValue);
	}
}
