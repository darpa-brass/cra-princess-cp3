#ifndef METRICS_CALCULATOR_H
#define METRICS_CALCULATOR_H

#include "data_generator.h"

/*
 * Metric Calculation Functions for Path Planner
 */

/* MAX_SEARCHGRID_EDGE worst case can be calculated as follows:
 * ceil((searchAreaMax - searchAreaMin) / (2.0 * altitude * tan(fovRadians / 2.0))) */
#define MAX_SEARCHGRID_EDGE 128

#define TURN_DISTANCE_FACTOR 22.35

/* Data structures */
typedef struct searchGrid_struct {
  int grid[MAX_SEARCHGRID_EDGE][MAX_SEARCHGRID_EDGE];
  int numCellsX;
  int numCellsY;
  double cellSize;
  double minX;
  double minY;
  double maxX;
  double maxY;
  int numVisited;
} searchGrid_struct;

/* Global vars */
searchGrid_struct searchGrid;

/* Calculate distance metric for a given path plan */
double calculateDistance(location_struct *plan);

/* Calculate coverage metric for a given plan and input */
double calculateCoverage(location_struct *output, input_struct *input);

void searchGrid_init(searchGrid_struct *grid,
                     location_struct *p1,
                     location_struct *p2,
                     double cellSize);

void searchGrid_visit(searchGrid_struct *grid, location_struct *p);

void searchGrid_visitHelper(searchGrid_struct *grid, 
                            location_struct *p, 
                            double halfView);

double searchGrid_getCoverage(searchGrid_struct *grid);

int searchGrid_inSearchArea(searchGrid_struct *grid, location_struct *p);

void interpolate(searchGrid_struct *grid, location_struct *plan);

#endif /* METRICS_CALCULATOR_H */
