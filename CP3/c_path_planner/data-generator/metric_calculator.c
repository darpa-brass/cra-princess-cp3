/*
 * Metric Calculation Functions for Path Planner
 */
#include <stdio.h>
#include <math.h>
#include <float.h>

#include "data_generator.h"
#include "metric_calculator.h"

double location_distance(location_struct *p1, location_struct *p2);

/* Calculate distance metric for a given path plan */
double 
calculateDistance(location_struct *plan)
{
  double totalDistance = 0.0;
  int i, j;

  for(i = 0, j = 1; plan[j].x != END_MARKER && j < MAX_PLAN_PTS; i++, j++) {
    //printf("totalDistance: %f, i: %d, j: %d, plan[j].x: %f, plan[j].y: %f\n", totalDistance, i, j, plan[j].x, plan[j].y);
    totalDistance += location_distance(&plan[i], &plan[j]);   
  }
  return totalDistance + (double)(i)*TURN_DISTANCE_FACTOR;
}

/* Calculate coverage metric for a given plan and input */
double
calculateCoverage(location_struct *output, input_struct *input)
{
  double viewSize = 2.0 * input->altitude * tan(input->fovRadians / 2.0);
  searchGrid_init(&searchGrid, &input->searchArea[0], 
                  &input->searchArea[2], viewSize);
  interpolate(&searchGrid, output);
  return searchGrid_getCoverage(&searchGrid);
}

void
searchGrid_init(searchGrid_struct *grid,
                location_struct *p1, 
                location_struct *p2, 
                double cellSize)
{
  int i, j;
  double gridXlen = fabs(p2->x - p1->x);
  double gridYlen = fabs(p2->y - p1->y);
  grid->minX = p1->x;
  grid->minY = p1->y;
  grid->maxX = p2->x;
  grid->maxY = p2->y;
  grid->cellSize = cellSize;
  grid->numCellsX = (int) (ceil(gridXlen / cellSize));
  grid->numCellsY = (int) (ceil(gridYlen / cellSize));
  for(i = 0; i < MAX_SEARCHGRID_EDGE; i++) {
    for(j = 0; j < MAX_SEARCHGRID_EDGE; j++) {
      grid->grid[i][j] = 0;
    }
  }
  grid->numVisited = 0;
}

void
searchGrid_visit(searchGrid_struct *grid, location_struct *p)
{
  double halfview = grid->cellSize / 2.0;
  location_struct pointToVisit;
  location_struct leftPoint;
  location_struct rightPoint;
  location_struct upPoint;
  location_struct downPoint;
  location_struct leftUpPoint;
  location_struct leftDownPoint;
  location_struct rightUpPoint;
  location_struct rightDownPoint;


  pointToVisit.x = p->x;
  pointToVisit.y = p->y;
  
  leftPoint.x = p->x - halfview;
  leftPoint.y = p->y;

  rightPoint.x = p->x + halfview;
  rightPoint.y = p->y;

  upPoint.x = p->x;
  upPoint.y = p->y + halfview;

  downPoint.x = p->x;
  downPoint.y = p->y - halfview;

  leftUpPoint.x = p->x - halfview;
  leftUpPoint.x = p->y + halfview;

  leftDownPoint.x = p->x - halfview;
  leftDownPoint.y = p->y - halfview;

  rightUpPoint.x = p->x + halfview;
  rightUpPoint.y = p->y + halfview;

  rightDownPoint.x = p->x + halfview;
  rightDownPoint.y = p->y - halfview;

  searchGrid_visitHelper(grid, &leftPoint, halfview);
  searchGrid_visitHelper(grid, &rightPoint, halfview);
  searchGrid_visitHelper(grid, &upPoint, halfview);
  searchGrid_visitHelper(grid, &downPoint, halfview);
  searchGrid_visitHelper(grid, &leftUpPoint, halfview);
  searchGrid_visitHelper(grid, &leftDownPoint, halfview);
  searchGrid_visitHelper(grid, &rightUpPoint, halfview);
  searchGrid_visitHelper(grid, &rightDownPoint, halfview);
}

void
searchGrid_visitHelper(searchGrid_struct *grid, 
                       location_struct *p, 
                       double halfView)
{
  int indexX, indexY;
  location_struct pointToVisit;
  pointToVisit.x = p->x;
  pointToVisit.y = p->y;

  /* Find grid cell containing point p, accounting for view window */
  if(!searchGrid_inSearchArea(grid, p)) {
    if(fabs(p->x - grid->minX) <= halfView) {
      pointToVisit.x = grid->minX;
    }
    if(fabs(p->x - grid->maxX) <= halfView) {
      pointToVisit.x = grid->maxX;
    }
    if(fabs(p->y - grid->minY) <= halfView) {
      pointToVisit.y = grid->minY;
    }
    if(fabs(p->y - grid->maxY) <= halfView) {
      pointToVisit.y = grid->maxY;
    }
  }

  indexX = (int) floor((pointToVisit.x - grid->minX) / grid->cellSize);
  indexY = (int) floor((pointToVisit.y - grid->minY) / grid->cellSize);
  if(indexX < grid->numCellsX && indexY < grid->numCellsY && indexX >= 0 &&
     indexY >= 0) {
    if(!grid->grid[indexX][indexY]) {
      grid->grid[indexX][indexY] = 1;
      grid->numVisited++;
    }
  }
}

double
searchGrid_getCoverage(searchGrid_struct *grid)
{
  int numCells = grid->numCellsX * grid->numCellsY;
  if(numCells == 0) {
    return 0.0;
  }
  //printf("Coverage = %f\n", ((double)grid->numVisited) / ((double)numCells)); 
  return ((double)grid->numVisited) / ((double)numCells);
}

int
searchGrid_inSearchArea(searchGrid_struct *grid, location_struct *p)
{
  if((p->x < grid->minX) ||
     (p->x > grid->maxX) ||
     (p->y < grid->minY) ||
     (p->y > grid->maxY)) {
    return 0;
  }
  return 1;
}

/* find distance between two locations (private function) */
double
location_distance(location_struct *p1, location_struct *p2)
{
  double xDiff = (p1->x - p2->x);
  double yDiff = (p1->y - p2->y);
  return sqrt(xDiff*xDiff + yDiff*yDiff);
}

void
interpolate(searchGrid_struct *grid, location_struct *plan)
{
  int i, j, k;
  double legSize;
  double interpDistance;
  double xIncrement;
  double yIncrement;
  double slope;
  location_struct startPoint;
  location_struct endPoint;
  int numLegPts;
  location_struct *curPoint;
  location_struct nextPoint;
  int slopeSet;

  for(i = 0, j = 1;
      plan[i].x < END_MARKER && isfinite(plan[i].x) &&
      plan[i].y < END_MARKER && isfinite(plan[i].y) &&
      plan[j].x < END_MARKER && isfinite(plan[j].x) &&
      plan[j].y < END_MARKER && isfinite(plan[j].y) &&
      i < MAX_PLAN_PTS && j < MAX_PLAN_PTS; i++, j++) {
    slopeSet = 0;

    /* calculate slope if defined */
    if((plan[j].x - plan[i].x) != 0.0) { // TODO: should this be !=?
      slope = (plan[j].y - plan[i].y) / (plan[j].x - plan[i].x);
      slopeSet = 1;
    } //else {
      //printf("slope not set, %f\n", plan[j].x - plan[i].x); fflush(stdout);
    //}
    startPoint.x = plan[i].x;
    startPoint.y = plan[i].y;
    endPoint.x = plan[j].x;
    endPoint.y = plan[j].y;

    searchGrid_visit(grid, &startPoint);

    legSize = location_distance(&startPoint, &endPoint);
    
    interpDistance = grid->cellSize / 2.0; // was also tried with 1.0 and 2.0
    
    /* calculate x and y increment for each point interior to leg */
    xIncrement = (slopeSet != 0) ? 
                 sqrt(pow(interpDistance, 2.0) / (1.0 + slope*slope)) : 0.0;
    yIncrement = (slopeSet != 0) ?
                 fabs(slope) * xIncrement : interpDistance;

    /* ensure correct sign for the xIncrement */
    if(plan[i].x > plan[j].x) {
      xIncrement *= -1.0;
    }
    /* ensure correct sign for the yIncrement */
    if(plan[i].y > plan[j].y) {
      yIncrement *= -1.0;
    }

    numLegPts = (int)(floor(legSize / interpDistance)); // # of interior pts
    //printf("(%f, %f) -> (%f, %f); numLegPts = %d\n", plan[i].x, plan[i].y,
    //       plan[j].x, plan[j].y, numLegPts);
    curPoint = &startPoint;

    for(k = 0; k < numLegPts; k++) {
      nextPoint.x = curPoint->x + xIncrement;
      nextPoint.y = curPoint->y + yIncrement;
      searchGrid_visit(grid, &nextPoint);
      curPoint = &nextPoint;
    }
    searchGrid_visit(grid, &endPoint);
  }
}

