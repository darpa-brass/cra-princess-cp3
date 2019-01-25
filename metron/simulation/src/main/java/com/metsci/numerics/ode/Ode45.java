package com.metsci.numerics.ode;

import static java.lang.Math.abs;
import static java.lang.Math.cos;
import static java.lang.Math.max;
import static java.lang.Math.min;
import static java.lang.Math.pow;
import static java.lang.Math.signum;




/**
 * 
 * @author gratton
 * Adaptive step-size Runge-Kutta 4/5 ODE solver, Cash-Karp variant.
 * Reference: Numerical Recipes in C, Press et al.
 */
public class Ode45 {

	private  DifferentialEquation problem; // Class to compute derivatives
	
	private double dt = 0; // Current time-step
	private double tnow; // Current time
	private double tgoal; // Time to integrate until
	private int neq; // number of equations
	private boolean stepSuccess = true; // Was the last step successful?
	
	// Substep storage
	private double[] k0;
	private double[] k1; 
	private double[] k2;
	private double[] k3;
	private double[] k4;
	private double[] k5;
	private double[] x; // Value of independent variable at time tnow
	private double[] xtmp; // Store substep approximation of x	
	
	// Butcher array coefficients for Runge-Kutta Cash-Karp 4/5
	private final static double ck1 = 1./5.;
	private final static double[] ck2 = new double []{3./40., 9./40.};
	private final static double[] ck3 = new double[]{0.3, -0.9, 1.2};
	private final static double[] ck4 = new double[]{-11./54., 2.5, -70./27., 35./27.};
	private final static double[] ck5 = new double[]{1631./55296., 175./512., 575./13824., 44275./110592., 253./4096. };
	private final static double[] ct = new double[] {0.0, 0.2, 0.3, 0.6, 1.0, 0.875};
	// Solution error substep weights
	private final static double[] ce = new double[] {
	        37./378. - 2825./27648.,
            0,
            250./621. - 18575./48384.,
            125./594. - 13525./55296.,
            0         - 277./14336.,
            512./1771. - 1./4.
	};
	// Solution value substep weights
	private final static double[] cs = new double[] {
	        37./378., 0.0, 250./621., 125./594., 0.0, 512./1771.
	};
			
	private final static double TINY = 1e-20;
	private final static double EPS = 1e-14;
	
	// Method parameters
	private double safety = 0.9;
	private double maxShrink = 0.1;
	private double minGrow = 5.0;
	private double tolerance =Math.sqrt(EPS);
	private double minDt = EPS;
	private double maxDt = 0; // 0 means unlimited	
	private boolean muddleAlong = false; // just keep integrating at minDt in violation of tolerance
	
	public Ode45() { }
	public Ode45(DifferentialEquation arg_problem, double[] state) { 
		setProblem(arg_problem);
		setState(state);
	}
	public void setProblem(DifferentialEquation arg_problem) { problem = arg_problem; }
	
	// Set/Get Methods for algo parameters
	public void setTolerance(double arg_tolerance) { tolerance = arg_tolerance; }
	public double getTolerance() { return tolerance; }
	public void setMinDt(double arg_minDt) { minDt = arg_minDt; }
	public double getMinDt() { return minDt; }
	public void setMaxDt(double arg_maxDt) { maxDt = arg_maxDt; }
	public void setNoMaxDt() { maxDt = 0; }
	public double getMaxDt() { return maxDt; }
	public void setSafety(double arg_safety) { safety = arg_safety; }
	public double getSafety() { return safety; }
	public void setDt(double arg_dt) { dt = arg_dt; } 
	public double getDt() { return dt; }
	public void setMuddle(boolean val) { muddleAlong = val; }
	
	// Time/state control
	public void setTnow(double arg_tnow) { tnow = arg_tnow; }
	public double getTnow() { return tnow; }
	public void setTgoal(double arg_tgoal) { tgoal = arg_tgoal; }
	public double getTgoal() { return tgoal; }
	public void setState(double[] arg_x) { 
	    if (arg_x == x)
	        return;
		if (neq != arg_x.length) {
			neq = arg_x.length;
			k0 = new double[neq];
			k1 = new double[neq];
			k2 = new double[neq];
			k3 = new double[neq];
			k4 = new double[neq];
			k5 = new double[neq];			
			x = new double[neq];
			xtmp = new double[neq];			
		}
		System.arraycopy(arg_x, 0, x, 0, neq);
	}
	public double[] getState() { return x; }
	
	
	/*
	 * Integrate in time. Function calls follow Matlab order: time interval, then 
	 * independent variable.  Unspecified values are taken from class members.
	 */
	public void integrate(double arg_tnow, double arg_tgoal, double[] arg_x) 
		throws TimestepException {
		System.arraycopy(arg_x, 0, x, 0, neq);
		integrate(arg_tnow, arg_tgoal);
	}
	public void integrate(double arg_tnow, double arg_tgoal) 
		throws TimestepException {
		tnow = arg_tnow;
		integrate(arg_tgoal);
	}
	public void integrate(double arg_tgoal) 
		throws TimestepException {
		tgoal = arg_tgoal;
		integrate();
	}
	public void integrate() 
		throws TimestepException {
		@SuppressWarnings("unused")
		int total_steps = 0;
		double stored_dt = 0;
		if (abs(dt) < EPS) dt = 0.1 * (tgoal-tnow) * pow(tolerance, 0.25);
		// System.out.println("Integrating chunk with initial dt = " + dt);
		while (tnow < tgoal) {
			if (tnow + dt > tgoal) {
				stored_dt = dt;
				dt = Math.max(tgoal - tnow, minDt);
			}
			rkStep();
			total_steps++;
			if ( stored_dt != 0 && stepSuccess) {
				dt = stored_dt;
			    stored_dt = 0;
			}
			if (dt < minDt) {
				if (muddleAlong) {
					dt = minDt;
				} else {
					throw new TimestepException("Timestep smaller than minDt requested. Abort.");
				}
			} else if (maxDt != 0 && dt > maxDt) {
				dt = maxDt;
			}
		}
		// System.out.println("Took " + total_steps + " steps to get to goal (including failed steps).");
		// System.out.println("Final dt = " + dt);
	}
	
	
	private void rkStep() {
		// Compute substeps to integrate this time interval
		double t = tnow;
		problem.computeDerivative(k0, x, t);
		
		for (int i=0; i<neq; i++) {
			xtmp[i] = x[i] + dt*ck1*k0[i];			
		}
		t = tnow + ct[1]*dt;
		problem.computeDerivative(k1, xtmp, t);

		for (int i=0; i<neq; i++) {
			xtmp[i] = x[i] + dt*(ck2[0]*k0[i]  + ck2[1]*k1[i]);
		}
		t = tnow + ct[2]*dt;
		problem.computeDerivative(k2, xtmp, t);

		for (int i=0; i<neq; i++) {
			xtmp[i] = x[i] + dt*(ck3[0]*k0[i] + ck3[1]*k1[i] + ck3[2]*k2[i]);
		}
		t = tnow + ct[3]*dt;		
		problem.computeDerivative(k3, xtmp, t);

		for (int i=0; i<neq; i++) {
			xtmp[i] = x[i] + dt*(ck4[0]*k0[i] + ck5[1]*k1[i] + ck4[2]*k2[i] + ck4[3]*k3[i]);
		}
		t = tnow + ct[4]*dt;
		problem.computeDerivative(k4, xtmp, t);

		for (int i=0; i<neq; i++) {
			xtmp[i] = x[i] + dt*(ck5[0]*k0[i] + ck5[1]*k1[i] + ck5[2]*k2[i] + ck5[3]*k3[i] + ck5[4]*k4[i]);
		}
		t = tnow + ct[5]*dt;
		problem.computeDerivative(k5, xtmp, t);
		
		// Compute error estimate
		double error = 0;
		for (int i=0; i<neq; i++) {
		    double xscale = abs(x[i] + abs(dt*k0[i])) + TINY;		    
		    double thisError = abs(dt*(ce[0]*k0[i] + ce[1]*k1[i] + ce[2]*k2[i] + ce[3]*k3[i] + ce[4]*k4[i] + ce[5]*k5[i])/xscale);
			error = max( error,  thisError);
		}
		error /= tolerance;
		if (error > 1.0 && dt > minDt) { // Step failed, reduce time-step
			double new_dt = safety * dt * pow(error, -0.25);
			dt = signum(dt)*max(abs(new_dt), maxShrink*abs(dt));
			stepSuccess = false;
		} else { // Step worked, increase time-step and compute new position			
			for (int i=0; i<neq; i++)
				x[i] += dt*(cs[0]*k0[i] + cs[1]*k1[i] + cs[2]*k2[i] + cs[3]*k3[i] + cs[4]*k4[i] + cs[5]*k5[i]);
			tnow += dt;
			double new_dt = safety * abs(dt) * pow(error, -0.2);
			dt = signum(dt)*min(abs(new_dt), minGrow*abs(dt));
			stepSuccess = true;
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		double frequency = 0.5;
		double tmax = 10;
		MassSpringProblem testProblem = new MassSpringProblem(frequency);
		double[] state = {1.0, 0};
		Ode45 solver = new Ode45(testProblem, state);
		try {
			solver.integrate(0, tmax);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		double x_true = cos(frequency*solver.getTnow());
		double x_approx = solver.getState()[0];
		System.out.printf( "t = %g, x = %g, x_true = %g, error = %g\n",
				solver.getTnow(), x_approx, x_true, abs(x_approx - x_true) );

		try {
			solver.integrate(2*tmax);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		x_true = cos(frequency*solver.getTnow());
		x_approx = solver.getState()[0];
		System.out.printf( "t = %g, x = %g, x_true = %g, error = %g\n",
				solver.getTnow(), x_approx, x_true, abs(x_approx - x_true) );
		try {
			solver.integrate(3*tmax);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		x_true = cos(frequency*solver.getTnow());
		x_approx = solver.getState()[0];
		System.out.printf( "t = %g, x = %g, x_true = %g, error = %g\n",
				solver.getTnow(), x_approx, x_true, abs(x_approx - x_true) );
	}
}


/**
 * Test problem for Ode45: mass-spring system 
 */
class MassSpringProblem 
implements DifferentialEquation {
	public double coef = 1.0;
	public MassSpringProblem(double arg_freq) { coef=arg_freq*arg_freq; }
	
	public void computeDerivative(double[] rhs, final double[] state, double t) {
		rhs[0] =  state[1];
		rhs[1] = -coef*state[0];
	}
}