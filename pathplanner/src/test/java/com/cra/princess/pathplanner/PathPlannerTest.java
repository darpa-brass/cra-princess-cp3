package com.cra.princess.pathplanner;

import org.junit.Test;

import java.util.List;

import static junit.framework.TestCase.*;

/**
 * Testing the path planner
 * 
 */
public class PathPlannerTest {
	@Test
	public void pathPlannerTest() {
		double searchAreaLowerLeftLat = 30.0;
		double searchAreaLowerLeftLon = -117.0;
		double searchAreaUpperRightLat = 30.001;
		double searchAreaUpperRightLon = -116.998;

		double searchDepthMeters = 20.0;
		double sensorFieldOfViewRadians = Math.toRadians(30.0);

		double rotation = 0.0;

		// Bounded Lawnmower Pattern
		PathPlanner pathPlanner = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
				searchAreaUpperRightLat, searchAreaUpperRightLon,
				searchDepthMeters, sensorFieldOfViewRadians,
				PathPlanner.LAWNMOWER_PATTERN,true, rotation);
		assertTrue(pathPlanner != null);

		List<Waypoint> waypoints = pathPlanner.plan();
		assertTrue(waypoints != null);

		int size = waypoints.size();
		assertTrue(size == 18);

		Waypoint head = waypoints.get(0);
		Waypoint tail = waypoints.get(size - 1);
		assertTrue(head.getNorth() == tail.getNorth());
		assertTrue(head.getEast() == tail.getEast());

		// Unbounded Lawnmower Pattern
		pathPlanner = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
				searchAreaUpperRightLat, searchAreaUpperRightLon,
				searchDepthMeters, sensorFieldOfViewRadians,
				PathPlanner.LAWNMOWER_PATTERN,false, rotation);
		assertTrue(pathPlanner != null);

		waypoints = pathPlanner.plan();
		assertTrue(waypoints != null);

		size = waypoints.size();
		assertTrue(size == 10);

		head = waypoints.get(0);
		tail = waypoints.get(size - 1);
		assertTrue(head.getNorth() == tail.getNorth());
		assertTrue(head.getEast() == tail.getEast());

		// Bounded Spiral Pattern
		pathPlanner = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
				searchAreaUpperRightLat, searchAreaUpperRightLon,
				searchDepthMeters, sensorFieldOfViewRadians,
				PathPlanner.SPIRAL_PATTERN,true, rotation);
		assertTrue(pathPlanner != null);

		waypoints = pathPlanner.plan();
		assertTrue(waypoints != null);

		size = waypoints.size();
		assertTrue(size == 20);

		head = waypoints.get(0);
		tail = waypoints.get(size - 1);
		assertTrue(head.getNorth() == tail.getNorth());
		assertTrue(head.getEast() == tail.getEast());

		// Unbounded Spiral Pattern
		pathPlanner = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
				searchAreaUpperRightLat, searchAreaUpperRightLon,
				searchDepthMeters, sensorFieldOfViewRadians,
				PathPlanner.SPIRAL_PATTERN,false, rotation);
		assertTrue(pathPlanner != null);

		waypoints = pathPlanner.plan();
		assertTrue(waypoints != null);

		size = waypoints.size();
		assertTrue(size == 12);

		head = waypoints.get(0);
		tail = waypoints.get(size - 1);
		assertTrue(head.getNorth() == tail.getNorth());
		assertTrue(head.getEast() == tail.getEast());
	}

	@Test
	public void locationTest() {
		double searchAreaLowerLeftLat = 0.0;
		double searchAreaLowerLeftLon = 0.0;
		double searchAreaUpperRightLat = 0.005;
		double searchAreaUpperRightLon = 0.005;

		double searchDepthMeters = 20.0;
		double sensorFieldOfViewRadians = Math.toRadians(30.0);

		double rotation = 0.0;

		// Bounded Lawnmower Pattern
		PathPlanner pathPlanner = new PathPlanner(searchAreaLowerLeftLat, searchAreaLowerLeftLon,
				searchAreaUpperRightLat, searchAreaUpperRightLon,
				searchDepthMeters, sensorFieldOfViewRadians,
				PathPlanner.LAWNMOWER_PATTERN,true, rotation);
		assertTrue(pathPlanner != null);

		List<Waypoint> waypoints = pathPlanner.plan();
		assertTrue(waypoints != null);

		int size = waypoints.size();
		assertTrue(size == 98);

		Waypoint head = waypoints.get(0);
		Waypoint tail = waypoints.get(size - 1);
		assertTrue(head.getNorth() == tail.getNorth());
		assertTrue(head.getEast() == tail.getEast());
	}

	@Test
	public void truncateTest(){
		double [] endMarker = new double[]{Double.MAX_VALUE,Double.MAX_VALUE};
		double[][] oldPath = new double[][]{new double[]{0.0,0.0}, new double[]{0.0,100.0}, new double[]{100.0,100.0}, new double[]{100.0,0.0}, new double[]{0.0, 0.0}, endMarker};
		System.out.println(SingleFunctionPathPlanner.distance(oldPath));
		double budget = 342 + 22.35 * 3.0;
		double[][] newPath = SingleFunctionPathPlanner.truncatePath(oldPath, budget);
		System.out.println(SingleFunctionPathPlanner.distance(newPath));
		for(int i = 0; i < newPath.length; i++) {
			System.out.println("(" + newPath[i][0] + "," + newPath[i][1] + ")");
		}
		assertTrue(newPath[0][0] == 0.0 && newPath[0][1] == 0.0);
		assertTrue(newPath[1][0] == 0.0 && newPath[1][1] == 100.0);
		assertTrue(newPath[2][0] == 100.0 && newPath[2][1] == 100.0);
		assertTrue(newPath[3][0] == 0.0 && newPath[3][1] == 0.0);
		assertTrue(newPath[4][0] == Double.MAX_VALUE && newPath[4][1] == Double.MAX_VALUE);
	}
}
