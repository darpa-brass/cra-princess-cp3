package com.cra.princess.metron.viewer.model.components;

import javax.swing.*;
import java.awt.*;

/**
 * An area encompassing the object the REMUS is searching for
 * 
 */

public class SearchArea extends Area {
	private double vE = 0.0;
	private double vN = 0.0;

	public SearchArea(double southLat, double westLon, double northLat, double eastLon) {
		super(southLat, westLon, northLat, eastLon);
	}

	@Override
	public void draw(JPanel trackPanel, int zoomLevel, Graphics2D g2d) {
		// Draw search area

		// Point areaPoint1 = scaleToDisplay(trackPanel, zoomLevel, this.getSouthLat(), this.getEastLon());
		Point areaPoint2 = scaleToDisplay(trackPanel, zoomLevel, this.getNorthLat(), this.getEastLon());
		Point areaPoint3 = scaleToDisplay(trackPanel, zoomLevel, this.getNorthLat(), this.getWestLon());
		Point areaPoint4 = scaleToDisplay(trackPanel, zoomLevel, this.getSouthLat(), this.getWestLon());

		int x = areaPoint3.x;
		int y = areaPoint3.y;
		int width = Math.abs(areaPoint2.x - areaPoint3.x);
		int height = Math.abs(areaPoint2.y - areaPoint4.y);

		Rectangle rect = new Rectangle(x, y, width, height);
		g2d.draw(rect);
	}
}
