package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.viewer.controller.RemusViewerController;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: May 14, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class LegendColorPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 220;
	private static int PANEL_HEIGHT = 192;

	private RemusViewerController controller = null;

	private static final String GROUND_TRUTH_LABEL = "Ground Truth";
	private static final String DVL_SENSOR_LABEL = "Original Dead Reckoning";
	private static final String TRANSFORMED_DVL_LABEL = "Transformed Dead Reckoning";
	private static final String KALMAN_FILTER_LABEL = "Kalman Filter";
	private static final String CURRENT_BORDER_LABEL = "Current Area";
	private static final String SEARCH_AREA_BORDER_LABEL = "Search Area";
	private static final String ORIGIN_LABEL = "Home";
	private static final String DESTINATION_LABEL = "Destination";

	private ColorChooserDialog colorChooserDialog = null;

	public LegendColorPanel(RemusViewerController controller, ColorChooserDialog colorChooserDialog) {
		super();

		this.controller = controller;
		this.colorChooserDialog = colorChooserDialog;

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setBackground(new Color(153, 204, 255));

		addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				colorChooserDialog.setVisible(true);
			}
		});
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2d = (Graphics2D) g;

		Color curColor = g2d.getColor();

		g2d.setColor(this.controller.getGroundTruthTrackColor());
		g2d.fillRect(20, 10, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(GROUND_TRUTH_LABEL, 50, 16);

		g2d.setColor(this.controller.getDvlSensorTrackColor());
		g2d.fillRect(20, 34, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(DVL_SENSOR_LABEL, 50, 40);

		g2d.setColor(this.controller.getTransformedDvlSensorTrackColor());
		g2d.fillRect(20, 58, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(TRANSFORMED_DVL_LABEL, 50, 64);

		g2d.setColor(this.controller.getKalmanFilterTrackColor());
		g2d.fillRect(20, 82, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(KALMAN_FILTER_LABEL, 50, 88);

		g2d.setColor(this.controller.getCurrentBorderColor());
		g2d.fillRect(20, 106, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(CURRENT_BORDER_LABEL, 50, 112);

		g2d.setColor(this.controller.getSearchAreaBorderColor());
		g2d.fillRect(20, 130, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(SEARCH_AREA_BORDER_LABEL, 50, 136);

		g2d.setColor(this.controller.getOriginColor());
		g2d.fillRect(20, 154, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(ORIGIN_LABEL, 50, 160);

		g2d.setColor(this.controller.getDestinationColor());
		g2d.fillRect(20, 178, 20, 5);
		g2d.setColor(Color.BLACK);
		g2d.drawString(DESTINATION_LABEL, 50, 184);

		g2d.setColor(curColor);
	}
}
