package com.cra.princess.metron.viewer.view;

import com.cra.princess.metron.viewer.controller.RemusViewerController;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;

/**
 * User interface for the REMUS Viewer<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 16, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class LegendPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private LegendViewPanel legendViewPanel = null;
	private LegendColorPanel legendColorPanel = null;

	public LegendPanel(RemusViewerController controller, ColorChooserDialog colorChooserDialog, RemusTrackPanel trackPanel) {
		super();

		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createTitledBorder(new LineBorder(Color.BLACK, 1), "Legend"));

		this.legendViewPanel = new LegendViewPanel(trackPanel);
		this.legendColorPanel = new LegendColorPanel(controller, colorChooserDialog);

		this.add(this.legendViewPanel, BorderLayout.WEST);
		this.add(this.legendColorPanel, BorderLayout.CENTER);
	}
}
