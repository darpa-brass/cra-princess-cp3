package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.remus.state.RemusPowerState;
import com.cra.princess.metron.viewer.controller.RemusViewerController;

import javax.swing.*;
import java.awt.*;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Jul 23, 2018<br>
 * <br>
 * Copyright 2018 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class PowerDialog extends JDialog {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 240;
	private static int PANEL_HEIGHT = 25;

	private JPanel powerPanel = null;
	private JLabel powerValue = null;

	public PowerDialog(Frame ownerFrame) {
		super(ownerFrame, "Remaining Energy (Wh)", false);

		this.powerPanel = new JPanel();
		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.powerPanel.setPreferredSize(d);
		this.powerPanel.setMinimumSize(d);
		this.powerPanel.setMaximumSize(d);

		this.powerValue = new JLabel("0.0");
		this.powerPanel.add(this.powerValue);
		this.add(this.powerPanel);

		this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

		this.pack();
	}

	public void updatePowerData(RemusPowerState powerState) {
		double power = powerState.getPower();

		this.powerValue.setText(String.format("%.4f", power));

		repaint();
	}
}
