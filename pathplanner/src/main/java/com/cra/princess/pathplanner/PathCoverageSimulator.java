package com.cra.princess.pathplanner;

/*
 * Simulates following a path to approximate coverage of search area
 */
public class PathCoverageSimulator {
	private double[][] plan;
	private SearchAreaGrid searchGrid;
	private double viewSize;
	
	private class SearchAreaGrid {
		private boolean[][] grid;
	    private int numCellsX;
	    private int numCellsY;
	    private double cellSize;
	    private double minX;
	    private double minY;
	    private double maxX;
	    private double maxY;
	    private int numVisited;

	    // Build grid with cellSize
        SearchAreaGrid(Point p1, Point p2, double cellSize) {
			double gridXlen = Math.abs(p2.getX() - p1.getX());
			double gridYlen = Math.abs(p2.getY() - p1.getY());
			this.minX = p1.getX();
			this.minY = p1.getY();
			this.maxX = p2.getX();
			this.maxY = p2.getY();
			this.cellSize = cellSize;
			this.numCellsX = (int) Math.ceil(gridXlen / cellSize);
			this.numCellsY = (int) Math.ceil(gridYlen / cellSize);
			this.grid = new boolean[numCellsX][numCellsY];
			this.numVisited = 0;
		}

		void visit(Point p) {
			double halfview = this.cellSize / 2.0;

			Point pointToVisit = new Point(p.getX(), p.getY());
			Point leftPoint = new Point(p.getX() - halfview, p.getY());
			Point rightPoint = new Point(p.getX() + halfview, p.getY());
			Point upPoint = new Point(p.getX(), p.getY() + halfview);
			Point downPoint = new Point(p.getX(), p.getY() - halfview);
            Point leftUpPoint = new Point(p.getX() - halfview, p.getY() + halfview);
            Point leftDownPoint = new Point(p.getX() - halfview, p.getY() - halfview);
            Point rightUpPoint = new Point(p.getX() + halfview, p.getY() + halfview);
            Point rightDownPoint = new Point(p.getX() + halfview, p.getY() - halfview);
			visitHelper(pointToVisit, halfview);
			visitHelper(leftPoint, halfview);
			visitHelper(rightPoint, halfview);
			visitHelper(upPoint, halfview);
			visitHelper(downPoint, halfview);
			visitHelper(leftUpPoint, halfview);
			visitHelper(leftDownPoint, halfview);
			visitHelper(rightUpPoint, halfview);
			visitHelper(rightDownPoint, halfview);
		}

		void visitHelper(Point p, double halfview) {
			Point pointToVisit = new Point(p.getX(), p.getY());

			// Find grid cell containing point p, accounting for view window
			if(!inSearchArea(p)) {
				if(Math.abs(p.getX() - this.minX) <= (halfview)) {
					pointToVisit = new Point(this.minX, pointToVisit.getY());
				}
				if(Math.abs(p.getX() - this.maxX) <= (halfview)) {
					pointToVisit = new Point(this.maxX, pointToVisit.getY());
				}
				if(Math.abs(p.getY() - this.minY) <= (halfview)) {
					pointToVisit = new Point(pointToVisit.getX(), this.minY);
				}
				if(Math.abs(p.getY() - this.maxY) <= (halfview)) {
					pointToVisit = new Point(pointToVisit.getX(), this.maxY);
				}
			}

			// central point
			int indexX = (int) Math.floor((pointToVisit.getX() - this.minX) / this.cellSize);
			int indexY = (int) Math.floor((pointToVisit.getY() - this.minY) / this.cellSize);
			if(indexX < this.numCellsX && indexY < this.numCellsY && indexX >= 0 && indexY >= 0) {
				if(!this.grid[indexX][indexY]) {
                    this.grid[indexX][indexY] = true;
                    this.numVisited++;
                    //System.out.println("Visiting: (" + indexX + ", " + indexY + ")" + " numCellsX = " + numCellsX + ", numCellsY = " + numCellsY);
				}
			}
			else {
				//System.out.println("Outside: (" + indexX + ", " + indexY + ")" + " numCellsX = " + numCellsX + ", numCellsY = " + numCellsY);
			}
		}
		
		double getCoverage() {
			int numCells = this.numCellsX * this.numCellsY;
			return (double)this.numVisited / (double)numCells;
		}
	}
	
	/**
	 * Class that approximates coverage of a given plan and path planner inputs
	 * 
	 * @param plan Plan (output from path planner, all coordinates in meters from origin)
	 * @param searchP1 lower-left point of search area
	 * @param searchP2 upper-right point of search area
	 * @param altitude distance from sea floor (meters)
	 * @param fovRadians field of view angle in radians
	 */
	public PathCoverageSimulator(double[][] plan, double searchP1[], double searchP2[], double altitude, double fovRadians) {
		this.viewSize = 2.0 * altitude * Math.tan(fovRadians/2.0);
		this.plan = plan;
		this.searchGrid = new SearchAreaGrid(new Point(searchP1[0], searchP1[1]), 
										     new Point(searchP2[0], searchP2[1]), viewSize);
	}
	
	/*
	 * Determine if point is within the search area
	 */
	private boolean inSearchArea(Point p) {
		if(p.getX() < this.searchGrid.minX ||
		   p.getX() > this.searchGrid.maxX ||
		   p.getY() < this.searchGrid.minY ||
		   p.getY() > this.searchGrid.maxY) {
		   return false;
		}
		return true;
	}
	
	/*
	 * Interpolate points s.t. they are spaced by no more than cellSize/2 along each plan leg and visit grid for each
	 */
	private void interpolate() {
		for(int i = 0, j = 1;
            plan[i][0] < SingleFunctionPathPlanner.END_MARKER && Double.isFinite(plan[i][0])
                && plan[i][1] < SingleFunctionPathPlanner.END_MARKER && Double.isFinite(plan[i][1])
                && plan[j][0] < SingleFunctionPathPlanner.END_MARKER && Double.isFinite(plan[j][0])
                && plan[j][1] < SingleFunctionPathPlanner.END_MARKER && Double.isFinite(plan[j][1]); i++, j++) {
			Double slope = null;
			
			/* calculate slope if defined */
			if((plan[j][0] - plan[i][0]) > 0.0) {
				slope = (plan[j][1] - plan[i][1]) / (plan[j][0] - plan[i][0]);
			}
			Point startPoint = new Point(plan[i][0], plan[i][1]);  // first point in leg
			Point endPoint = new Point(plan[j][0], plan[j][1]);    // last point in leg

			this.searchGrid.visit(startPoint);

			double legSize = endPoint.distance(startPoint);        // calculate leg size

			double interpDistance = this.searchGrid.cellSize / 4.0; //1.0; //this.searchGrid.cellSize / 2.0;

			// Calculate x and y increment for each point interior to leg (each point separated by viewSize/2.0)
			double xIncrement = (slope != null) ? Math.sqrt(Math.pow(interpDistance, 2.0) / (1.0 + slope*slope)) : 0.0;
			double yIncrement = (slope != null) ? Math.abs(slope) * xIncrement : interpDistance;

			// ensure correct sign for the xIncrement
            if(plan[i][0] > plan[j][0]) {
				xIncrement *= -1.0;
            }
            // ensure correct sign for the yIncrement
            if(plan[i][1] > plan[j][1]) {
			    yIncrement *= -1.0;
            }
			
			int numLegPts = (int)Math.floor(legSize / interpDistance);  // calculate number of interior leg points
            // Debug
            //System.out.println("viewSize = " + this.viewSize + ", numLegPts = " + numLegPts + ", legSize = " + legSize + ", startPoint = (" + startPoint.getX() + "," + startPoint.getY() + "), " + "endPoint = (" + endPoint.getX() + "," + endPoint.getY() + ")");
            //System.out.println("i = " + i + ", slope = " + slope + ", plan[i][0] = " + plan[i][0] + ", plan[i][1] = " + plan[i][1] + ", plan[j][0] = " + plan[j][0] + ", plan[j][1] = " + plan[j][1]);
			Point curPoint = startPoint;
				
			for(int k = 0; k < numLegPts; k++) { // loop adding interior points to list
				Point nextPoint = new Point(curPoint.getX() + xIncrement, curPoint.getY() + yIncrement);
				this.searchGrid.visit(nextPoint);
				curPoint = nextPoint;
			}
			this.searchGrid.visit(endPoint);
		}
	}
	
	/**
	 * Visit interpolated points and calculate coverage
	 * 
	 * @return approximate percentage of search area covered
	 */
	public double coverage() {
		this.interpolate();
		return searchGrid.getCoverage();
	}
}
