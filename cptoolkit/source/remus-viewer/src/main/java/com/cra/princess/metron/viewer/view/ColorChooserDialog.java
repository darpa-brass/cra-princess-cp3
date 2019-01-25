package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.viewer.controller.RemusViewerController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: May 17, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class ColorChooserDialog extends JDialog {
	private static final long serialVersionUID = 1L;

	private RemusViewerController controller = null;
	private Frame ownerFrame = null;

	private JButton groundTruthColor = null;
	private JButton dvlSensorColor = null;
	private JButton kalmanFilterColor = null;
	private JButton currentBorderColor = null;
	private JButton searchAreaBorderColor = null;
	private JButton transformedDvlSensorColor = null;
	private JButton originColor = null;
	private JButton destinationColor = null;

	public ColorChooserDialog(RemusViewerController controller, RemusViewerFrame ownerFrame) {
		super(ownerFrame, "Set Colors...", true);

		this.controller = controller;
		this.ownerFrame = ownerFrame;

		setDefaultCloseOperation(JDialog.HIDE_ON_CLOSE);

		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(8,2, 5, 5));

		JLabel groundTruthLabel = new JLabel("Ground Truth Color");
		this.groundTruthColor = new JButton();
		this.groundTruthColor.setBackground(controller.getGroundTruthTrackColor());
		this.groundTruthColor.setOpaque(true);
		this.groundTruthColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose Ground Truth Color", controller.getGroundTruthTrackColor());
				if (c != null) {
					controller.setGroundTruthTrackColor(c);
					groundTruthColor.setBackground(controller.getGroundTruthTrackColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel dvlSensorLabel = new JLabel("DVL Sensor Color");
		this.dvlSensorColor = new JButton();
		this.dvlSensorColor.setBackground(controller.getDvlSensorTrackColor());
		this.dvlSensorColor.setOpaque(true);
		this.dvlSensorColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose DVL Sensor Color", controller.getDvlSensorTrackColor());
				if (c != null) {
					controller.setDvlSensorTrackColor(c);
					dvlSensorColor.setBackground(controller.getDvlSensorTrackColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel kalmanFilterLabel = new JLabel("Kalman Filter Color");
		this.kalmanFilterColor = new JButton();
		this.kalmanFilterColor.setBackground(controller.getKalmanFilterTrackColor());
		this.kalmanFilterColor.setOpaque(true);
		this.kalmanFilterColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose Kalman Filter Color", controller.getKalmanFilterTrackColor());
				if (c != null) {
					controller.setKalmanFilterTrackColor(c);
					kalmanFilterColor.setBackground(controller.getKalmanFilterTrackColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel currentBorderLabel = new JLabel("Current Area Color");
		this.currentBorderColor = new JButton();
		this.currentBorderColor.setBackground(controller.getCurrentBorderColor());
		this.currentBorderColor.setOpaque(true);
		this.currentBorderColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose Current Area Color", controller.getCurrentBorderColor());
				if (c != null) {
					controller.setCurrentBorderColor(c);
					currentBorderColor.setBackground(controller.getCurrentBorderColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel searchAreaBorderLabel = new JLabel("Search Area Color");
		this.searchAreaBorderColor = new JButton();
		this.searchAreaBorderColor.setBackground(controller.getSearchAreaBorderColor());
		this.searchAreaBorderColor.setOpaque(true);
		this.searchAreaBorderColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose Search Area Color", controller.getSearchAreaBorderColor());
				if (c != null) {
					controller.setSearchAreaBorderColor(c);
					searchAreaBorderColor.setBackground(controller.getSearchAreaBorderColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel transformedDvlSensorLabel = new JLabel("Transformed DVL Color");
		this.transformedDvlSensorColor = new JButton();
		this.transformedDvlSensorColor.setBackground(controller.getTransformedDvlSensorTrackColor());
		this.transformedDvlSensorColor.setOpaque(true);
		this.transformedDvlSensorColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Choose Transformed DVL Color", controller.getTransformedDvlSensorTrackColor());
				if (c != null) {
					controller.setTransformedDvlSensorTrackColor(c);
					transformedDvlSensorColor.setBackground(controller.getTransformedDvlSensorTrackColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel originLabel = new JLabel("Home Color");
		this.originColor = new JButton();
		this.originColor.setBackground(controller.getOriginColor());
		this.originColor.setOpaque(true);
		this.originColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Home Color", controller.getOriginColor());
				if (c != null) {
					controller.setOriginColor(c);
					originColor.setBackground(controller.getOriginColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		JLabel destinationLabel = new JLabel("Destination Color");
		this.destinationColor = new JButton();
		this.destinationColor.setBackground(controller.getDestinationColor());
		this.destinationColor.setOpaque(true);
		this.destinationColor.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Color c = JColorChooser.showDialog(ownerFrame, "Destination Color", controller.getDestinationColor());
				if (c != null) {
					controller.setDestinationColor(c);
					destinationColor.setBackground(controller.getDestinationColor());
					ownerFrame.getLegendDialog().repaint();
				}
			}
		});

		panel.add(groundTruthLabel);
		panel.add(this.groundTruthColor);
		panel.add(dvlSensorLabel);
		panel.add(this.dvlSensorColor);
		panel.add(transformedDvlSensorLabel);
		panel.add(this.transformedDvlSensorColor);
		panel.add(kalmanFilterLabel);
		panel.add(this.kalmanFilterColor);
		panel.add(currentBorderLabel);
		panel.add(this.currentBorderColor);
		panel.add(searchAreaBorderLabel);
		panel.add(this.searchAreaBorderColor);
		panel.add(originLabel);
		panel.add(this.originColor);
		panel.add(destinationLabel);
		panel.add(this.destinationColor);

		this.add(panel, BorderLayout.CENTER);

		this.pack();
	}
}
