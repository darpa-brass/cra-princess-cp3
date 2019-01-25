package com.cra.princess.metron.viewer.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.Date;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 21, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class CommandDetailsPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 220;
	private static int PANEL_HEIGHT = 90;
	
	public CommandDetailsPanel(double speed, double depth, double heading) {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setBorder(new LineBorder(Color.BLACK, 1));
		
		this.setLayout(new GridLayout(4, 2, 1, 1));

		JLabel timeLabel = new JLabel("Time");
		JLabel timeValue = new JLabel(String.format("%tT", new Date()));
		JLabel speedLabel = new JLabel("Speed (m/s)");
		JLabel speedValue = new JLabel(String.format("%.1f", speed));
		JLabel depthLabel = new JLabel("Depth (m)");
		JLabel depthValue = new JLabel(String.format("%.1f", depth));
		JLabel headingLabel = new JLabel("Heading (deg)");
		JLabel headingValue = new JLabel(String.format("%.1f", heading));

		this.add(timeLabel);
		this.add(timeValue);
		this.add(speedLabel);
		this.add(speedValue);
		this.add(depthLabel);
		this.add(depthValue);
		this.add(headingLabel);
		this.add(headingValue);
	}
}
