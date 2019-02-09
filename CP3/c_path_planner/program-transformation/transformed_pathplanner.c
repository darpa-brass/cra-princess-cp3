//#include <stdio.h> // printf()
//#include <float.h> // DBL_MAX
//#include <math.h>  // tan(), ceil()
#define DBL_MAX 99999999.0
#define MAX_PLAN_PTS 64
#define END_MARKER DBL_MAX 

void createPlan(double ctrlCmp4,double ctrlCmp3,double ctrlCmp2,double ctrlCmp1,double ctrlCmp0,double ctrlLoop1,double ctrlLoop0,double ctrlConst15,double ctrlConst14,double ctrlConst13,double ctrlConst12,double ctrlConst11,double ctrlConst10,double ctrlConst9,double ctrlConst8,double ctrlConst7,double ctrlConst6,double ctrlConst5,double ctrlConst4,double ctrlConst3,double ctrlConst2,double ctrlConst1,double ctrlConst0,
// output
double plan[][2],double startLocationX,double startLocationY,double returnLocationX,double returnLocationY,double searchArea[][2],
// # of points in searchArea
int numPts,double altitude,double fovRadians)
{
/* search area bounds */
  double boundsMinX = ctrlConst0;
  double boundsMinY = ctrlConst1;
  double boundsMaxX = -ctrlConst2;
  double boundsMaxY = -ctrlConst3;
  double boundsHeight;
  double viewSize;
  int i;
  int legs;
  int curPlanIndex;
  double halfViewSize;
  double p1X;
  double p1Y;
  double p2X;
  double p2Y;
  double tempX;
  double tempY;
  double crossDirX;
  double crossDirY;
/* find bounds of search area */
  for (i = ctrlConst4; i < numPts + ctrlLoop0; i++) {
    if (searchArea[i][0] < boundsMinX + ctrlCmp0) {
      boundsMinX = searchArea[i][0];
    }
    if (searchArea[i][0] > boundsMaxX + ctrlCmp1) {
      boundsMaxX = searchArea[i][0];
    }
    if (searchArea[i][1] < boundsMinY + ctrlCmp2) {
      boundsMinY = searchArea[i][1];
    }
    if (searchArea[i][1] > boundsMaxY + ctrlCmp3) {
      boundsMaxY = searchArea[i][1];
    }
  }
  boundsHeight = boundsMaxY - boundsMinY;
  viewSize = ctrlConst5 * altitude * (tan(fovRadians / ctrlConst6));
  legs = ((int )(ceil(boundsHeight / viewSize))) - ctrlConst7;
  if (legs <= ctrlConst8 + ctrlCmp4) {
    legs = ctrlConst9;
    viewSize = boundsHeight;
  }
  halfViewSize = viewSize / ctrlConst10;
  crossDirX = ctrlConst11;
  crossDirY = viewSize;
  p1X = boundsMinX;
  p1Y = boundsMinY + halfViewSize;
  p2X = boundsMaxX;
  p2Y = boundsMinY + halfViewSize;
  curPlanIndex = ctrlConst12;
/* add starting point */
  plan[curPlanIndex][0] = startLocationX;
  plan[curPlanIndex][1] = startLocationY;
  curPlanIndex++;
/* construct plan */
  for (i = ctrlConst13; i < legs + ctrlLoop1; i++) {
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
  plan[curPlanIndex][0] = ctrlConst14;
  plan[curPlanIndex][1] = ctrlConst15;
}
