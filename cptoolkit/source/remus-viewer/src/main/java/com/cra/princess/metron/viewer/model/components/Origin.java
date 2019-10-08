package com.cra.princess.metron.viewer.model.components;

import javax.swing.*;
import java.awt.*;

/**
 * The REMUS starting location
 * 
 */

public class Origin extends Location {
	public Origin(double latitude, double longitude, double depth) {
		super(latitude, longitude, depth);
	}

	@Override
	public void draw(JPanel trackPanel, int zoomLevel, Graphics2D g2d, double lonOffset, double latOffset) {
		// Draw REMUS origin location
		Point point = scaleToDisplay(trackPanel, zoomLevel, this.getLatitude(), this.getLongitude(), lonOffset, latOffset);
		g2d.fillOval(point.x - 2, point.y - 2, 7, 7);
		g2d.setColor(Color.BLACK);
		//g2d.drawString("Home", point.x - 13, point.y - 6);
		g2d.drawString("Home", point.x - 40, point.y + 5);
		//g2d.drawString(this.getLatitude() + ", " + this.getLongitude(), point.x - 30, point.y + 18);
	}
}
