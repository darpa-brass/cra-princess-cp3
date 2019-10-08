package com.cra.princess.metron.viewer.model.components;

import com.cra.princess.metron.viewer.view.RemusTrackPanel;

import javax.swing.*;
import java.awt.*;

/**
 * Base for all components found in a scenario
 * 
 */

public abstract class ScenarioComponent {
	public ScenarioComponent() {
	}

	public abstract void draw(JPanel trackPanel, int zoomLevel, Graphics2D g2d, double lonOffset, double latOffset);

	/* Map a lat, lon value to an x, y coordinate suitable for drawing */
	public static Point scaleToDisplay(JPanel trackPanel, int zoomLevel, double lat, double lon, double lonOffset, double latOffset) {
		double SCALE_FACTOR_X = trackPanel.getWidth() / (RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON) * (1.0 + (zoomLevel / 10.0));
		double SCALE_FACTOR_Y = trackPanel.getHeight() / (RemusTrackPanel.MAX_LAT - RemusTrackPanel.MIN_LAT) * (1.0 + (zoomLevel / 10.0));

		// Map lat, lon to Point containing display coordinates
		int displayX = (int)(((lon - lonOffset) * SCALE_FACTOR_X));
		int displayY = (int)(((lat - latOffset) * SCALE_FACTOR_Y));

		return new Point(displayX, displayY);
	}
	/* Map a lat, lon value to an x, y coordinate suitable for drawing */
	public static Double[] displayToLonLat(JPanel trackPanel, int zoomLevel, double y, double x, double lonOffset, double latOffset) {
		double SCALE_FACTOR_X = trackPanel.getWidth() / (RemusTrackPanel.MAX_LON - RemusTrackPanel.MIN_LON) * (1.0 + (zoomLevel / 10.0));
		double SCALE_FACTOR_Y = trackPanel.getHeight() / (RemusTrackPanel.MAX_LAT - RemusTrackPanel.MIN_LAT) * (1.0 + (zoomLevel / 10.0));

		// Map lat, lon to Point containing display coordinates
		double mappedLongitude = (double)((x / SCALE_FACTOR_X) + lonOffset);
		double mappedLatitude = (double)((y / SCALE_FACTOR_Y) + latOffset);

		return new Double[]{mappedLongitude, mappedLatitude};
	}

	/* Draw text centered in a Rectangle */
	protected void drawCenteredString(Graphics2D g2d, String text, Rectangle rect) {
		Font curFont = g2d.getFont();
		Font font = new Font("serif", Font.PLAIN, 12);
		g2d.setFont(font);
		// Get the FontMetrics
		FontMetrics metrics = g2d.getFontMetrics(font);
		// Determine the X coordinate for the text
		int x = (rect.width - metrics.stringWidth(text)) / 2;
		// Determine the Y coordinate for the text (note we add the ascent, as in java 2d 0 is top of the screen)
		int y = ((rect.height - metrics.getHeight()) / 2) + metrics.getAscent();
		// Draw the String
		g2d.setColor(Color.GRAY);
		g2d.drawString(text, rect.x + x, rect.y + y);
		g2d.setColor(Color.BLACK);
		g2d.setFont(curFont);
	}
}
