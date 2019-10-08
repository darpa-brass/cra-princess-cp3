package com.cra.princess.pathplanner;

import java.util.ArrayList;
import java.util.List;
import org.apache.log4j.Logger;

public class SingleFunctionPathPlanner {

	private static final Logger LOG = Logger.getLogger(SingleFunctionPathPlanner.class.getName());

	// Constants, will need to be made known to analyzing code
	static final int maxPlanPts = 64;
	public static final double END_MARKER = Double.MAX_VALUE;
	public static final double turnDistanceFactor = 22.35; // meters that could be traveled going straight using same amt of energy as turning 90 deg

	// Note: this doesn't clamp the points to be within the search space, i.e., boundedbySearchArea = false
	// Note: if we can't use arrays, then we'll have to have a separate variable for each input/output point
	public double[][] Plan(double startLocationX, double startLocationY, double returnLocationX, 
			double returnLocationY, double[][] searchArea, int numPts, double altitude, double fovRadians) {

		// VehicleModel: altitude, startLocationX, startLocationY, returnLocationX, returnLocationY
	    
		// Sensor Model: fovRadians
		
		// plan to output
		double plan[][] = new double[maxPlanPts][2];  // Problem here with dynamic allocation?
		
		double boundsMinX = Double.MAX_VALUE;
		double boundsMinY = Double.MAX_VALUE;
		double boundsMaxX = -Double.MAX_VALUE;
		double boundsMaxY = -Double.MAX_VALUE;
		
		// find bounds of search area
		for(int i = 0; i < numPts; i++) {
			if(searchArea[i][0] < boundsMinX) {
				boundsMinX = searchArea[i][0];
			}
			if(searchArea[i][0] > boundsMaxX) {
				boundsMaxX = searchArea[i][0];
			}
			if(searchArea[i][1] < boundsMinY) {
				boundsMinY = searchArea[i][1];
			}
			if(searchArea[i][1] > boundsMaxY) {
				boundsMaxY = searchArea[i][1];
			}
		}
		
		double boundsHeight = boundsMaxY - boundsMinY;
		double viewSize = 2.0 * altitude * Math.tan(fovRadians/2.0); // can we use Math.tan?
//		LOG.debug("fov = " + fovRadians + ", viewSize = " + viewSize);
		int legs = (int)Math.ceil(boundsHeight / viewSize) - 1; // can we use Math.ceil?

		if(legs <= 1) {
			legs = 1;
			viewSize = boundsHeight;
		}
		
		double halfViewSize = viewSize / 2.0;
		double crossDirX = 0.0;
		double crossDirY = viewSize;
		double p1X = boundsMinX;
		double p1Y = boundsMinY + halfViewSize;
		double p2X = boundsMaxX;
		double p2Y = boundsMinY + halfViewSize;
		
		// Construct plan based on bounds
		int curPlanIndex = 0;
		// Add starting point
		plan[curPlanIndex][0] = startLocationX;
		plan[curPlanIndex][1] = startLocationY;
		curPlanIndex++;
		for(int i = 0; i < legs; i++) {
			plan[curPlanIndex][0] = p1X;
			plan[curPlanIndex][1] = p1Y;
			curPlanIndex++;
			plan[curPlanIndex][0] = p2X;
			plan[curPlanIndex][1] = p2Y;
			curPlanIndex++;
			double tempX = p1X + crossDirX;
			double tempY = p1Y + crossDirY;
			p1X = p2X + crossDirX;
			p1Y = p2Y + crossDirY;
			p2X = tempX;
			p2Y = tempY;
		}
		// Add return point
		plan[curPlanIndex][0] = returnLocationX;
		plan[curPlanIndex][1] = returnLocationY;
		curPlanIndex++;
		// So we can tell where the plan ends
		plan[curPlanIndex][0] = END_MARKER;
		plan[curPlanIndex][1] = END_MARKER;
		
		return plan;
	}
	
	public double[][] TransformedPlan(double ctrlLoop0, double ctrlLoop1, double ctrlCmp0,         // 
									  double ctrlConst0, double ctrlConst1, double ctrlConst2,     // New control vars
									  double ctrlConst3, double ctrlConst4,                        //
			double startLocationX, double startLocationY, double returnLocationX, 
			double returnLocationY, double[][] searchArea, int numPts, double altitude, double fovRadians) {

		// VehicleModel: altitude, startLocationX, startLocationY, returnLocationX, returnLocationY
	    
		// Sensor Model: fovRadians

		double plan[][] = new double[maxPlanPts][2];  // Problem here with dynamic allocation?
		
		double boundsMinX = Double.MAX_VALUE;
		double boundsMinY = Double.MAX_VALUE;
		double boundsMaxX = -Double.MAX_VALUE;
		double boundsMaxY = -Double.MAX_VALUE;
		
		// find bounds of search area
		for(int i = 0; i < numPts + ctrlLoop0; i++) {  // Transformed
			if(searchArea[i][0] < boundsMinX) {
				boundsMinX = searchArea[i][0];
			}
			if(searchArea[i][0] > boundsMaxX) {
				boundsMaxX = searchArea[i][0];
			}
			if(searchArea[i][1] < boundsMinY) {
				boundsMinY = searchArea[i][1];
			}
			if(searchArea[i][1] > boundsMaxY) {
				boundsMaxY = searchArea[i][1];
			}
		}
		
		double boundsHeight = boundsMaxY - boundsMinY;
		double viewSize = /*2.0*/ ctrlConst0 * altitude * Math.tan(fovRadians/2.0);  // Transformed

		LOG.debug("fov = " + fovRadians + ", viewSize = " + viewSize);
		int legs = (int)Math.ceil(boundsHeight / viewSize) - (int)ctrlConst1 /*1*/;  // Transformed (needs cast)
		
		if(legs <= 1 + ctrlCmp0) {  // Transformed
			legs = (int)ctrlConst2 /*1*/;  // Transformed (needs cast)
			viewSize = boundsHeight;
		}
		
		double halfViewSize = viewSize / ctrlConst3 /*2.0*/;  // Transformed
		double crossDirX = ctrlConst4 /*0.0*/;  // Transformed
		double crossDirY = viewSize;
		double p1X = boundsMinX;
		double p1Y = boundsMinY + halfViewSize;
		double p2X = boundsMaxX;
		double p2Y = boundsMinY + halfViewSize;
		
		// Construct plan based on bounds
		int curPlanIndex = 0;
		// Add starting point
		plan[curPlanIndex][0] = startLocationX;
		plan[curPlanIndex][1] = startLocationY;
		curPlanIndex++;
		for(int i = 0; i < legs + ctrlLoop1; i++) { // Transformed
			plan[curPlanIndex][0] = p1X;
			plan[curPlanIndex][1] = p1Y;
			curPlanIndex++;
			plan[curPlanIndex][0] = p2X;
			plan[curPlanIndex][1] = p2Y;
			curPlanIndex++;
			double tempX = p1X + crossDirX;
			double tempY = p1Y + crossDirY;
			p1X = p2X + crossDirX;
			p1Y = p2Y + crossDirY;
			p2X = tempX;
			p2Y = tempY;
		}
		// Add return point
		plan[curPlanIndex][0] = returnLocationX;
		plan[curPlanIndex][1] = returnLocationY;
		curPlanIndex++;
		// So we can tell where the plan ends
		plan[curPlanIndex][0] = END_MARKER;
		plan[curPlanIndex][1] = END_MARKER;
		
		return plan;
	}
	
	// Calculate total plan distance
	public static double distance(double[][] plan) {
        double totalDistance = 0.0;
		int i, j;
		for(i = 0, j = 1; plan[j][0] != END_MARKER; i++, j++) {
			double point1X = plan[i][0];
        	double point1Y = plan[i][1];
        	double point2X = plan[j][0];
        	double point2Y = plan[j][1];
        	totalDistance += Math.sqrt(Math.pow(point2X-point1X, 2) + Math.pow(point2Y-point1Y, 2));
		}
		return totalDistance + i*turnDistanceFactor;
	}

	public static double[][] truncatePath(double[][] path, double budget){
		List<double[]> truncatedPath = new ArrayList<>();
		double [] endMarker = new double[]{Double.MAX_VALUE,Double.MAX_VALUE};
		double[] returnLoc = new double[]{0.0, 0.0};
		truncatedPath.add(path[0]);
		double totalDistance = 0.0;
		double returnDistance;
		for(int i=1; i < path.length; i++){
			double[] p1 = path[i-1];
			double[] p2 = path[i];
			totalDistance += distance(new double[][]{p1, p2, endMarker});
			returnDistance = distance(new double[][]{p2, returnLoc, endMarker});
			if(totalDistance + returnDistance <= budget)
				truncatedPath.add(p2);
			else{
				truncatedPath.add(returnLoc);
				truncatedPath.add(endMarker);
				double[][] truncatedPathArray = new double[truncatedPath.size()][2];
				return truncatedPath.toArray(truncatedPathArray);
			}
		}
		truncatedPath.add(endMarker);
		double[][] truncatedPathArray = new double[truncatedPath.size()][2];
		return truncatedPath.toArray(truncatedPathArray);
	}
}
