package com.cra.princess.metron.viewer;

import javax.swing.SwingUtilities;

import com.cra.princess.metron.viewer.controller.RemusViewerController;
import com.cra.princess.metron.viewer.view.RemusViewerFrame;

/**
 * Application for displaying the Metron REMUS track data.
 * <br>
 * This data comes from listening to a variety of Metron REMUS simulator ActiveMQ topics.
 * 
 */
public class RemusViewer {
    public RemusViewer() {
    	RemusViewerController controller = new RemusViewerController();

    	SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				new RemusViewerFrame(controller);
			}
		}); 
    }

    public static void main(String[] args) {
    	new RemusViewer();
    }
}
