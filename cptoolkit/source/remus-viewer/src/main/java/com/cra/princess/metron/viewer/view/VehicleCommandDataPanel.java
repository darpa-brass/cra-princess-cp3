package com.cra.princess.metron.viewer.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.LineBorder;

import com.cra.princess.metron.remus.command.RemusVehicleCommand;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class VehicleCommandDataPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 230;
	private static int PANEL_HEIGHT = 400;

	private JPanel commands = null;
	
	public VehicleCommandDataPanel() {
		super();

		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Vehicle Commands"));

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		
		this.commands = new JPanel();

		this.commands.setLayout(new BoxLayout(this.commands, BoxLayout.Y_AXIS));
		
		JScrollPane scrollPane = new JScrollPane(this.commands, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		this.add(scrollPane, BorderLayout.CENTER);
	}
	
	public void updateVehicleCommandData(RemusVehicleCommand vehicleCommand) {
		double speed = vehicleCommand.getSpeedTarget();
		double depth = vehicleCommand.getDepthTarget();
		double heading = vehicleCommand.getHeadingTarget();

		CommandDetailsPanel cdp = new CommandDetailsPanel(speed, depth, heading);

		this.commands.add(cdp, 0);
		this.commands.revalidate();
		
	    repaint();
	}
	
	public void reset() {
		this.commands.removeAll();
		this.commands.revalidate();
		
		repaint();
	}
}
