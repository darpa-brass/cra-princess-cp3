package com.cra.princess.metron.viewer.model.components;

import javax.swing.*;
import java.awt.*;

/**
 * An area of current affecting REMUS speed and heading
 * 
 */

public class PerturbingCurrent extends Area {
	private double vE = 0.0;
	private double vN = 0.0;
	
	public PerturbingCurrent(double southLat, double westLon, double northLat, double eastLon, double vE, double vN) {
		super(southLat, westLon, northLat, eastLon);
		this.vE = vE;
		this.vN = vN;
	}

	public double getvE() {
		return vE;
	}

	public double getvN() {
		return vN;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		if (!super.equals(o)) return false;

		PerturbingCurrent that = (PerturbingCurrent) o;

		if (Double.compare(that.vE, vE) != 0) return false;
		return Double.compare(that.vN, vN) == 0;
	}

	@Override
	public int hashCode() {
		int result = super.hashCode();
		long temp;
		temp = Double.doubleToLongBits(vE);
		result = 31 * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(vN);
		result = 31 * result + (int) (temp ^ (temp >>> 32));
		return result;
	}

	@Override
	public void draw(JPanel trackPanel, int zoomLevel, Graphics2D g2d) {
		// Draw perturbing areas of current

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

		drawCenteredString(g2d, "vE " + this.getvE() + " m/s, vN " + this.getvN() + " m/s", rect);
	}
}
