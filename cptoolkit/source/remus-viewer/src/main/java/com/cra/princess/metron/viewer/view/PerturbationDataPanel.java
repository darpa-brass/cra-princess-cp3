package com.cra.princess.metron.viewer.view;

import com.cra.princess.messaging.RemusBatteryPerturbation;
import com.cra.princess.metron.remus.perturbation.RemusSensorPerturbation;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Mar 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class PerturbationDataPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static int PANEL_WIDTH = 230;
	private static int PANEL_HEIGHT = 400;

	private JPanel perturbations = null;

	public PerturbationDataPanel() {
		super();

		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Perturbation Events"));

		Dimension d = new Dimension(PANEL_WIDTH, PANEL_HEIGHT);
		this.setPreferredSize(d);
		
		this.perturbations = new JPanel();

		this.perturbations.setLayout(new BoxLayout(this.perturbations, BoxLayout.Y_AXIS));
		
		JScrollPane scrollPane = new JScrollPane(this.perturbations, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		this.add(scrollPane, BorderLayout.CENTER);
	}

	public void addPerturbation(RemusBatteryPerturbation perturbation) {
		double powerReduction = perturbation.getEnergyReduction();

		BatteryPerturbationDetailsPanel p = new BatteryPerturbationDetailsPanel(powerReduction);

		this.perturbations.add(p, 0);
		this.perturbations.revalidate();

		repaint();
	}

	public void addPerturbation(RemusSensorPerturbation perturbation) {
		String sensorName = perturbation.getName();
		double bias = perturbation.getBias();
		double noiseDeviation = perturbation.getNoiseDeviation();
		double anchor = perturbation.getAnchor();
		double anchorProbability = perturbation.getAnchorProbability();

		SensorPerturbationDetailsPanel p = new SensorPerturbationDetailsPanel(sensorName, bias, noiseDeviation, anchor, anchorProbability);

		this.perturbations.add(p, 0);
		this.perturbations.revalidate();

		repaint();
	}

	public void reset() {
		this.perturbations.removeAll();
		this.perturbations.revalidate();
		
		repaint();
	}
}
