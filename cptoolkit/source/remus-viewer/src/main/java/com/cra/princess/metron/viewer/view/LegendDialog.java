package com.cra.princess.metron.viewer.view;

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

public class LegendDialog extends JDialog {
	private static final long serialVersionUID = 1L;
	private LegendPanel legendPanel = null;

	public LegendDialog(RemusViewerController controller, ColorChooserDialog colorChooserDialog, RemusTrackPanel trackPanel, Frame ownerFrame) {
		super(ownerFrame, "Legend", false);

		this.legendPanel = new LegendPanel(controller, colorChooserDialog, trackPanel);

		this.add(this.legendPanel);

		this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

		this.pack();
	}
}
