package com.cra.princess.metron.viewer.model.components;

import javax.swing.*;
import java.awt.*;

/**
 * The location of the object the REMUS is searching for
 * 
 */

public class SearchObject extends Location {
	public SearchObject(double latitude, double longitude, double depth) {
		super(latitude, longitude, depth);
	}

	@Override
	public void draw(JPanel trackPanel, int zoomLevel, Graphics2D g2d) {
		// Draw search object location
		Point point = scaleToDisplay(trackPanel, zoomLevel, this.getLatitude(), this.getLongitude());
		g2d.setColor(Color.BLACK);
		g2d.drawString("x", point.x, point.y + 4);
		g2d.drawString("Object", point.x - 16, point.y - 6);
		//g2d.drawString(this.getLatitude() + ", " + this.getLongitude(), point.x - 30, point.y + 18);
	}
}
