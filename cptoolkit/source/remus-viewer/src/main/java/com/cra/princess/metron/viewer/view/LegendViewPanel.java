package com.cra.princess.metron.viewer.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 16, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class LegendViewPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 20;
	private static int PANEL_HEIGHT = 144;

	private RemusTrackPanel trackPanel = null;

	public LegendViewPanel(RemusTrackPanel trackPanel) {
		super();

		this.trackPanel = trackPanel;

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		this.setLayout(new GridLayout(8, 1, 1, 1));

		JCheckBox groundTruthTrack = new JCheckBox();
		groundTruthTrack.setSelected(true);
		groundTruthTrack.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowRemusTrack(false);
				}
				else {
					trackPanel.setShowRemusTrack(true);
				}
			}
		});

		JCheckBox dvlSensorTrack = new JCheckBox();
		dvlSensorTrack.setSelected(true);
		dvlSensorTrack.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowDvlSensorTrack(false);
				}
				else {
					trackPanel.setShowDvlSensorTrack(true);
				}
			}
		});

		JCheckBox kalmanFilterTrack = new JCheckBox();
		kalmanFilterTrack.setSelected(true);
		kalmanFilterTrack.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowKalmanFilterTrack(false);
				}
				else {
					trackPanel.setShowKalmanFilterTrack(true);
				}
			}
		});

		JCheckBox perturbationAreas = new JCheckBox();
		perturbationAreas.setSelected(true);
		perturbationAreas.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowPerturbationAreas(false);
				}
				else {
					trackPanel.setShowPerturbationAreas(true);
				}
			}
		});

		JCheckBox searchArea = new JCheckBox();
		searchArea.setSelected(true);
		searchArea.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowSearchArea(false);
				}
				else {
					trackPanel.setShowSearchArea(true);
				}
			}
		});

		JCheckBox transformedDvlSensorTrack = new JCheckBox();
		transformedDvlSensorTrack.setSelected(true);
		transformedDvlSensorTrack.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowTransformedDvlSensorTrack(false);
				}
				else {
					trackPanel.setShowTransformedDvlSensorTrack(true);
				}
			}
		});

		JCheckBox originLocation = new JCheckBox();
		originLocation.setSelected(true);
		originLocation.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowOriginLocation(false);
				}
				else {
					trackPanel.setShowOriginLocation(true);
				}
			}
		});

		JCheckBox destinationLocation = new JCheckBox();
		destinationLocation.setSelected(true);
		destinationLocation.addItemListener(new ItemListener()
		{
			public void itemStateChanged(ItemEvent e)
			{
				if (e.getStateChange() == ItemEvent.DESELECTED) {
					trackPanel.setShowDestinationLocation(false);
				}
				else {
					trackPanel.setShowDestinationLocation(true);
				}
			}
		});

		this.add(groundTruthTrack);
		this.add(dvlSensorTrack);
		this.add(transformedDvlSensorTrack);
		this.add(kalmanFilterTrack);
		this.add(perturbationAreas);
		this.add(searchArea);
		this.add(originLocation);
		this.add(destinationLocation);
	}
}
