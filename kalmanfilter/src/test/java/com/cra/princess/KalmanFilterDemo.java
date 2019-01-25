package com.cra.princess;

import com.cra.princess.utility.math.Ellipsoid;
import org.apache.commons.math3.filter.*;
import org.apache.commons.math3.linear.*;
import org.apache.commons.math3.random.JDKRandomGenerator;
import org.apache.commons.math3.random.RandomGenerator;
import org.apache.commons.math3.stat.correlation.Covariance;
import org.apache.commons.math3.util.Pair;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;

import java.util.ArrayList;

public class KalmanFilterDemo extends ApplicationFrame {

	private static final long serialVersionUID = 1L;

	public static void main(final String[] args) {

		final KalmanFilterDemo demo = new KalmanFilterDemo("XY Series Demo");
		demo.pack();
		RefineryUtilities.centerFrameOnScreen(demo);
		demo.setVisible(true);
	}

	public KalmanFilterDemo(final String title) {
		super(title);
		ArrayList<Pair<Double, Double>> finalPositions = new ArrayList<Pair<Double, Double>>();
		final XYSeriesCollection data = new XYSeriesCollection();
		double startTime = System.currentTimeMillis(); 
		for (int i = 0; i < 10; i++) {
			ArrayList<Pair<Double, Double>> positionData = kalmanFilter(0,100 * Math.cos(Math.PI / 4), 0, 100 * Math.sin(Math.PI / 4));
			finalPositions.add(positionData.get(positionData.size() - 1));
			data.addSeries(createXYSeries(positionData, i));
		}
		
		// Print data onto chart
		final JFreeChart chart = ChartFactory.createXYLineChart(
				"Kalman Filter Estimates", "X-Position", "Y-Position", data,
				PlotOrientation.VERTICAL, true, true, false);

		final ChartPanel chartPanel = new ChartPanel(chart);
		chartPanel.setPreferredSize(new java.awt.Dimension(750, 500));
		setContentPane(chartPanel);
		double endTime = System.currentTimeMillis(); 
		System.out.println("time elapsed: " + (endTime - startTime)/1000);
	}
	
	public XYSeries createXYSeries(
			ArrayList<Pair<Double, Double>> positionData, int iterationNumber) {
		final XYSeries series = new XYSeries("Path-" + iterationNumber);
		for (Pair<Double, Double> p : positionData) {
			series.add(p.getFirst(), p.getSecond());
		}
		return series;
	}
	/**
	 * 
	 */
	/**
	 * @param finalPositions - the final positions of the kalman filter after running multiple times
	 * @return double representing the covariance measurement 
	 */
	public static double getUncertainty(ArrayList<Pair<Double, Double>> finalPositions){
		// produce covariance matrix and extract eigenvalues to compute error-volume
		double[][] covariates = new double[finalPositions.size()][2];
		for (int i = 0; i < finalPositions.size(); i++) {
			covariates[i][0] = finalPositions.get(i).getFirst();
			covariates[i][1] = finalPositions.get(i).getSecond();
		}
		Covariance c = new Covariance(covariates);
		EigenDecomposition e = new EigenDecomposition(c.getCovarianceMatrix());
		Ellipsoid ellipse = new Ellipsoid(e.getRealEigenvalues());
		return ellipse.getVolume(); 
	}

	/**
	 * *************************************** 
	 * V - velocity vector 
	 * dv - Acceleration vector 
	 * A - state transition matrix 
	 * B - control input matrix
	 * H - measurement matrix 
	 * Q - process noise covariance matrix 
	 * R - measurement noise covariance matrix
	 * 
	 * @return List of Pairs<Position, Velocity>
	 * ***************************************/
	public static ArrayList<Pair<Double, Double>> kalmanFilter(double xcoord, double xvelocity, double ycoord, double yvelocity) {
		ArrayList<Pair<Double, Double>> data = new ArrayList<Pair<Double, Double>>();
		// discrete time interval
		double dt = 0.1d;
		// gravity
		double g = 9.8;
		// position measurement noise (meter)
		double measurementNoise = 10d;
		// acceleration noise (meter/sec^2)
		double accelNoise = 0.2d;

		// x - State Vector [ x-position ]
		// 					[ x-velocity ]
		// 					[ y-position ]
		// 					[ y-velocity ]
		// Initial state using ground truth data
		RealVector x0 = new ArrayRealVector(new double[] { xcoord, xvelocity, ycoord, yvelocity});

		// control vector, accounts for gravity (and other forces as needed)
		RealVector u = new ArrayRealVector(new double[] { 0, 0, -0.5 * g * Math.pow(dt, 2), -g * dt });

		// A = 	[ 1 dt 0 0 ]
		// 		[ 0 1  0 0 ]
		// 		[ 0 0 1 dt ]
		// 		[ 0 0 0  1 ]
		RealMatrix A = new Array2DRowRealMatrix(new double[][] {{ 1, dt, 0, 0 }, 
																{ 0, 1, 0, 0 }, 
																{ 0, 0, 1, dt },
																{ 0, 0, 0, 1 } });
		// B = 	[ 0 0 0 0 ]
		// 		[ 0 0 0 0 ]
		// 		[ 0 0 1 0 ]
		// 		[ 0 0 0 1 ]
		RealMatrix B = new Array2DRowRealMatrix(new double[][] {{ 0, 0, 0, 0 }, 
																{ 0, 0, 0, 0 },
																{ 0, 0, 1, 0 }, 
																{ 0, 0, 0, 1 }});
		
		// H =  [ 1 0 0 0 ], observation matrix, represents conversion to measurement data
		// 		[ 0 1 0 0 ]  in this example we have no such conversion so we use identity matrix
		// 		[ 0 0 1 0 ]  but in general, this can be used to model sensor measurement conversion
		// 		[ 0 0 0 1 ]
		RealMatrix H = new Array2DRowRealMatrix(new double[][] {{ 1, 0, 0, 0 }, 
																{ 0, 1, 0, 0 },
																{ 0, 0, 1, 0 }, 
																{ 0, 0, 0, 1 } });

		// Q = 	[ 0 0 0 0 ], process error covariance matrix, in this example we have none
		// 		[ 0 0 0 0 ]
		// 		[ 0 0 0 0 ]
		// 		[ 0 0 0 0 ]
		RealMatrix Q = new Array2DRowRealMatrix(new double[][] {{ 0, 0, 0, 0 }, 
																{ 0, 0, 0, 0 },
																{ 0, 0, 0, 0 }, 
																{ 0, 0, 0, 0 } });

		// P0 = [ 1 0 0 0 ], depends on outside information as well, we make another simplifying assumption
		// 		[ 0 1 0 0 ]
		// 		[ 0 0 1 0 ]
		// 		[ 0 0 0 1 ]
		RealMatrix P0 = new Array2DRowRealMatrix(new double[][]{{ 1, 0, 0, 0 }, 
																{ 0, 1, 0, 0 },
																{ 0, 0, 1, 0 }, 
																{ 0, 0, 0, 1 } });

		// R =  [ 0.2 0 0 0 ], measurement error covariance matrix
		// 		[ 0 0.2 0 0 ]
		// 		[ 0 0 0.2 0 ]
		// 		[ 0 0 0 0.2 ]
		RealMatrix R = new Array2DRowRealMatrix(new double[][] {{ 1.5, 0, 0, 0 }, 
																{ 0, 2.0, 0, 0 }, 
																{ 0, 0, 0.1, 0 },
																{ 0, 0, 0, 1.0 } });

		ProcessModel pm = new DefaultProcessModel(A, B, Q, x0, P0);
		MeasurementModel mm = new DefaultMeasurementModel(H, R);
		KalmanFilter filter = new KalmanFilter(pm, mm);

		RandomGenerator rand = new JDKRandomGenerator();
		
		// state transition noise
		RealVector tmpPNoise = new ArrayRealVector(new double[] { 1.0, 1.0, 1.0, 1.0 });
		RealVector mNoise = new ArrayRealVector(4);

		// iterate 150 steps
		for (int i = 0; i < 144; i++) {
			filter.predict(u);

			// simulate the process given noise term accelNoise
			RealVector pNoise = tmpPNoise.mapMultiply(accelNoise * rand.nextGaussian());

			// x = A * x + B * u + pNoise
			x0 = A.operate(x0).add(B.operate(u)).add(pNoise);

			// simulate the measurement
			mNoise.setEntry(0, measurementNoise * rand.nextGaussian());

			// z = H * x + m_noise
//			RealVector z = H.operate(x0).add(mNoise);		
			// kalman filter adds noise in addition to standard state transition
			filter.correct(x0);

			double xPos = filter.getStateEstimation()[0];
			double yPos = filter.getStateEstimation()[2];
			data.add(new Pair<Double, Double>(xPos, yPos));
		}
		return data;
	}
	
	/**
	 * @param A - State matrix 
	 * @param P - Average error from previous time step 
	 * @param Q - Covariance from previous time step 
	 * @return Matrix of Covariance n time steps forward in kalman filter
	 */
	public static RealMatrix forwardSampledCovarianceMatrix(RealMatrix A,RealMatrix P0, RealMatrix Q, RealMatrix H, RealMatrix R, int numTimeSteps){
		RealMatrix p_predicted = A.multiply(P0).multiply(A.transpose()).add(Q);
//		RealMatrix S = H.multiply(p_predicted).multiply(H.transpose()).add(R);
//		RealMatrix K = p_predicted.multiply(H.transpose()).multiply(MatrixUtils.inverse(S));
//		RealMatrix I = MatrixUtils.createRealIdentityMatrix(4);
//		RealMatrix Pn = (I.subtract(K.multiply(H))).multiply(p_predicted);
		for(int i=0;i<numTimeSteps-1;i++){
			p_predicted = A.multiply(p_predicted).multiply(A.transpose()).add(Q);
//			S = H.multiply(p_predicted).multiply(H.transpose()).add(R);
//			K = p_predicted.multiply(H.transpose()).multiply(MatrixUtils.inverse(S));
//			I = MatrixUtils.createRealIdentityMatrix(4);
			//Pn = (I.subtract(K.multiply(H))).multiply(p_predicted);
		}
		return p_predicted;
	}
}