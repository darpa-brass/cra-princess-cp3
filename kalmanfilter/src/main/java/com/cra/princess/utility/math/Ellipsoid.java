package com.cra.princess.utility.math;

import org.apache.commons.math3.special.Gamma;
import org.apache.commons.math3.stat.descriptive.summary.Product;

/**
 * Represents an N-Dimensional Ellipsoid
 */
public class Ellipsoid {

	private int dimension;
	private double[] radii;
	private boolean isSphere;

	/**
	 * @param radii
	 *            - each element of the array represents the length of one
	 *            radius assumes at least two radius are different
	 */
	public Ellipsoid(double[] radii) {
		this.radii = radii;
		this.dimension = radii.length;
		this.isSphere = false;
	}

	/**
	 * Constructs instance as a sphere
	 */
	public Ellipsoid(double radii, int dimension) {
		this.radii = new double[] { radii };
		this.dimension = dimension;
		this.isSphere = true;
	}

	public double getVolume() {
		double gamma = Gamma.gamma(this.dimension / 2.0 + 1);
		double piTerm = Math.pow(Math.PI, this.dimension / 2.0);
		if (this.isSphere) {
			return (piTerm / gamma) * Math.pow(this.radii[0], this.dimension);
		}
		Product p = new Product();
		return (piTerm / gamma) * p.evaluate(radii);
	}

	public boolean isSphere() {
		return this.isSphere;
	}

	public int getDimension() {
		return this.dimension;
	}

	public double[] getRadii() {
		return this.radii;
	}
}
