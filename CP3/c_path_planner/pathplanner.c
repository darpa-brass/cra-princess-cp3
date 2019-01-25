#include <stdio.h> // printf()
#include <float.h> // DBL_MAX
#include <math.h>  // tan(), ceil()

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

void
transformedCreatePlan(double ctrlLoop0,      // new ctrl vars
                      double ctrlLoop1,
                      double ctrlCmp0,
                      double ctrlConst0,
                      double ctrlConst1,
                      double ctrlConst2,
                      double ctrlConst3,
                      double ctrlConst4,
		      double plan[][2],      // output
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
  for (i = 0; i < numPts + ctrlLoop0; i++) { // transformed
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
  viewSize = /*2.0*/ ctrlConst0*altitude*tan(fovRadians / 2.0); // transformed
  legs = ((int)ceil(boundsHeight / viewSize)) - // transformed (needs cast) 
	 ((int)(ctrlConst1)) /*1*/;

  if (legs <= 1 + ctrlCmp0) { // transformed
    legs = (int)(ctrlConst2) /*1*/; // transformed (needs cast)
    viewSize = boundsHeight;
  }

  halfViewSize = viewSize / ctrlConst3 /*2.0*/; // transformed
  crossDirX = ctrlConst4 /*0.0*/; // transformed
  crossDirY = viewSize;
  p1X = boundsMinX;
  p1Y = boundsMinY + halfViewSize;
  p2X = boundsMaxX;
  p2Y = boundsMinY + halfViewSize;

  curPlanIndex = 0;

  /* add starting point */
  plan[curPlanIndex][0] = startLocationX;
  plan[curPlanIndex][1] = startLocationY;
  curPlanIndex++;

  /* construct plan */
  for (i = 0; i < legs + ctrlLoop1; i++) { // transformed
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

/* 
 * this tests to make sure that createPlan output matches transformedCreatePlan
 * (with equivalent control values)
 */
void 
main()
{
  int i;
  double plan[MAX_PLAN_PTS][2];
  double transformedPlan[MAX_PLAN_PTS][2];
  double searchArea[4][2] = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}; 
  int plansMatch = 1;
   
  createPlan(plan, 0.0, 0.0, 0.0, 0.0, searchArea, 4, 0.1, 0.3926991);
 
  printf("createPlan():\n"); 
  for(i = 0; i < MAX_PLAN_PTS; i++) {
    if(plan[i][0] == END_MARKER) {
      break;
    }
    printf("%f %f\n", plan[i][0], plan[i][1]);
  }   

  transformedCreatePlan(0.0, 0.0, 0.0, 2.0, 1.0, 1.0, 2.0, 0.0, // controls
		        transformedPlan, 0.0, 0.0, 0.0, 0.0, searchArea, 4, 
                        0.1,0.3926991);

  printf("\ntransformedCreatePlan():\n");
  for(i = 0; i < MAX_PLAN_PTS; i++) {
    if(transformedPlan[i][0] == END_MARKER) {
      break;
    }
    if((transformedPlan[i][0] != plan[i][0]) ||
       (transformedPlan[i][1] != plan[i][1])) {
      plansMatch = 0;
    }
    printf("%f %f\n", transformedPlan[i][0], transformedPlan[i][1]);
  }
  if(plansMatch == 1) {
    printf("\nPlans match\n");
  }
  else {
    printf("\nError: PLANS DO NOT MATCH\n");
  }
}
