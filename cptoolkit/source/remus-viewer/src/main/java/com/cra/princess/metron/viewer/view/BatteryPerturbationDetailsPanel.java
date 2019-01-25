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

public class BatteryPerturbationDetailsPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 220;
	private static int PANEL_HEIGHT = 50;

	public BatteryPerturbationDetailsPanel(double powerReduction) {
		super();

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setMinimumSize(d);
		this.setMaximumSize(d);
		
		this.setBorder(new LineBorder(Color.BLACK, 1));
		
		this.setLayout(new GridLayout(2, 2, 1, 1));

		JLabel timeLabel = new JLabel("Time");
		JLabel timeValue = new JLabel(String.format("%tT", new Date()));
		JLabel reductionLabel = new JLabel("Power Red. %");
		JLabel reductionValue = new JLabel(String.format("%.3f", powerReduction));

		this.add(timeLabel);
		this.add(timeValue);
		this.add(reductionLabel);
		this.add(reductionValue);
	}
}
