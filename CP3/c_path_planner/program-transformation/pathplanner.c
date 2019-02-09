//#include <stdio.h> // printf()
//#include <float.h> // DBL_MAX
//#include <math.h>  // tan(), ceil()
#define DBL_MAX 99999999.0
#define MAX_PLAN_PTS 64
#define END_MARKER DBL_MAX 

void 
createPlan(double plan[][2],      // output
           double startLocationX,
           double startLocationY,
           double returnLocationX,
           double returnLocationY,
           double searchArea[][2],
           int numPts,            // # of points in searchArea
           double altitude,
           double fovRadians) 
{
  /* search area bounds */
  double boundsMinX = DBL_MAX;
  double boundsMinY = DBL_MAX;
  double boundsMaxX = -DBL_MAX;
  double boundsMaxY = -DBL_MAX;
  
  double boundsHeight, viewSize;
  int i, legs;
  int curPlanIndex;

  double halfViewSize, p1X, p1Y, p2X, p2Y;
  double tempX, tempY;
  double crossDirX;
  double crossDirY;


  /* find bounds of search area */
  for (i = 0; i < numPts; i++) {
    if (searchArea[i][0] < boundsMinX) {
      boundsMinX = searchArea[i][0];
    }
    if (searchArea[i][0] > boundsMaxX) {
      boundsMaxX = searchArea[i][0];
    }
    if (searchArea[i][1] < boundsMinY) {
      boundsMinY = searchArea[i][1];
    }
    if (searchArea[i][1] > boundsMaxY) {
      boundsMaxY = searchArea[i][1];
    } 
  }

  boundsHeight = boundsMaxY - boundsMinY;
  viewSize = 2.0 * altitude * tan(fovRadians / 2.0);
  legs = ((int)ceil(boundsHeight / viewSize)) - 1;

  if (legs <= 1) {
    legs = 1;
    viewSize = boundsHeight;
  }

  halfViewSize = viewSize / 2.0;
  crossDirX = 0.0;
  crossDirY = viewSize;
  p1X = boundsMinX;
  p1Y = boundsMinY + halfViewSize;
  p2X = boundsMaxX;
  p2Y = boundsMinY + halfViewSize;
  
  curPlanIndex = 0.0;

  /* add starting point */
  plan[curPlanIndex][0] = startLocationX;
  plan[curPlanIndex][1] = startLocationY;
  curPlanIndex++;

  /* construct plan */
  for (i = 0; i < legs; i++) {
    plan[curPlanIndex][0] = p1X;
    plan[curPlanIndex][1] = p1Y;
    curPlanIndex++;
    plan[curPlanIndex][0] = p2X;
    plan[curPlanIndex][1] = p2Y;
    curPlanIndex++;
    tempX = p1X + crossDirX;
    tempY = p1Y + crossDirY;
    p1X = p2X + crossDirX;
    p1Y = p2Y + crossDirY;
    p2X = tempX;
    p2Y = tempY; 
  }  

  /* add return point */
  plan[curPlanIndex][0] = returnLocationX;
  plan[curPlanIndex][1] = returnLocationY;
  curPlanIndex++;

  /* mark end of plan */
  plan[curPlanIndex][0] = END_MARKER;
  plan[curPlanIndex][1] = END_MARKER;
}
