package com.cra.princess.metron.viewer.model.components;

/**
 * An area in a scenario
 * 
 */

public abstract class Area extends ScenarioComponent {
	private double southLat = 0.0;
	private double westLon = 0.0;
	private double northLat = 0.0;
	private double eastLon = 0.0;

	public Area(double southLat, double westLon, double northLat, double eastLon) {
		this.southLat = southLat;
		this.westLon = westLon;
		this.northLat = northLat;
		this.eastLon = eastLon;
	}

	public double getSouthLat() {
		return southLat;
	}

	public double getWestLon() {
		return westLon;
	}

	public double getNorthLat() {
		return northLat;
	}

	public double getEastLon() {
		return eastLon;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(eastLon);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(northLat);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(southLat);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(westLon);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Area other = (Area) obj;
		if (Double.doubleToLongBits(eastLon) != Double
				.doubleToLongBits(other.eastLon))
			return false;
		if (Double.doubleToLongBits(northLat) != Double
				.doubleToLongBits(other.northLat))
			return false;
		if (Double.doubleToLongBits(southLat) != Double
				.doubleToLongBits(other.southLat))
			return false;
		if (Double.doubleToLongBits(westLon) != Double
				.doubleToLongBits(other.westLon))
			return false;
		return true;
	}
}
