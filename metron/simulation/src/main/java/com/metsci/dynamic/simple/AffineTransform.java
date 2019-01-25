package com.metsci.dynamic.simple;

/*
 * An affine transform of the form
 *  
 *   y = R*(x + z)
 * Note the offset z is applied before the rotation 
 */

public class AffineTransform {

	// Offset
	protected double xo;
	protected double yo;
	protected double zo;
	
	// Rotation
	protected double m00;
	protected double m01;
	protected double m02;
	protected double m10;
	protected double m11;
	protected double m12;
	protected double m20;
	protected double m21;
	protected double m22;
	
	
	public AffineTransform() {
		this(0,0,0,0,0,0);
	}
	public AffineTransform(double x, double y, double z, double roll, double pitch, double yaw) {
		setOffset(x,y,z);
		setRotation(roll, pitch, yaw);
	}

	public AffineTransform setRotation(double roll, double pitch, double yaw) {
		double cpsi = Math.cos(yaw);
		double spsi = Math.sin(yaw);
		double ctheta = Math.cos(pitch);
		double stheta = Math.sin(pitch);
		double cphi = Math.cos(roll);
		double sphi = Math.sin(roll);
		m00 = cpsi*ctheta;
		m01 = -spsi*cphi + cpsi*stheta*sphi;
		m02 = spsi*sphi + cpsi*cphi*stheta;
		m10 = spsi*ctheta;
		m11 = cpsi*cphi + sphi*stheta*spsi;
		m12 = -cpsi*sphi + stheta*spsi*cphi;
		m20 = -stheta;
		m21 = ctheta*sphi;
		m22 = ctheta*cphi;
		return this;
	}
	
	public AffineTransform setOffset(double x, double y, double z) {
		xo = x;
		yo = y;
		zo = z;
		return this;
	}
	
	/*
	 * Transpose in place
	 */
	public AffineTransform transpose() {
		double t = m01;
		m01 = m10;
		m10 = t;
		t = m02;
		m02 = m20;
		m20 = t;
		t = m12;
		m12 = m21;
		m21 = t;
		return this;
	}

	/**
	 * Transform val = R*(val + z), where R is the rotation and z is the offset
	 * @param val -- 3-vector to be transformed
	 * @return val, transformed
	 */
	public double[] transform(double[] val) {		
		double x = val[0] + xo;
		double y = val[1] + yo;
		double z = val[2] + zo;
		
		val[0] = m00*x + m01*y + m02*z;
		val[1] = m10*x + m11*y + m12*z;
		val[2] = m20*x + m21*y + m22*z;
		return val;
	}
	
	public static void main(String[] args) {
		AffineTransform a = new AffineTransform();
		double[] x = new double[] { 1, 0, 0};
		a.transform(x);
		System.out.println(String.format("x = [%g, %g, %g]", x[0], x[1], x[2]));
		a.setRotation(0.1, 0.2, 0.3);
		a.transform(x);
		System.out.println(String.format("x = [%g, %g, %g]", x[0], x[1], x[2]));
		System.out.println(String.format("true = [0.936293, 0.289629, -0.198669]"));
	}
	
}
