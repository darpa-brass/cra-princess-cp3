package com.metsci.numerics.ode;

public interface DifferentialEquation {
	public void computeDerivative(double[] rhs, final double[] state, double t);
}
