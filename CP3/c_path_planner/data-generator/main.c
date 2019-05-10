#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "data_generator.h"

void
setCtrlBoundsMain()
{
  int i;

  /* set control bounds */

  for(i = 0; i <= 6; i++) {
    /* ctrlCmp and ctrlLoop center around 0 */
    ctrlBounds[i].min = -2.0;
    ctrlBounds[i].max = 2.0;
  }

  /* ctrlConst15 (END_MARKER) */
  ctrlBounds[i].min = END_MARKER;
  ctrlBounds[i].max = END_MARKER;
  i++;

  /* ctrlConst14 (END_MARKER) */
  ctrlBounds[i].min = END_MARKER;
  ctrlBounds[i].max = END_MARKER;
  i++;

  /* ctrlConst13 (0) */
  ctrlBounds[i].min = -2.0;
  ctrlBounds[i].max = 2.0;
  i++;

  /* ctrlConst12 (0.0) */
  ctrlBounds[i].min = -2.0;
  ctrlBounds[i].max = 2.0;
  i++;

  /* ctrlConst11 (0.0) */
  ctrlBounds[i].min = -2.0;
  ctrlBounds[i].max = 2.0;
  i++;

  /* ctrlConst10 (2.0) */
  ctrlBounds[i].min = 0.0;
  ctrlBounds[i].max = 4.0;
  i++;

  /* ctrlConst9 (1) */
  ctrlBounds[i].min = -1.0;
  ctrlBounds[i].max = 3.0;
  i++;

  /* ctrlConst8 (1) */
  ctrlBounds[i].min = -1.0;
  ctrlBounds[i].max = 3.0;
  i++;

  /* ctrlConst7 (1) */
  ctrlBounds[i].min = -1.0;
  ctrlBounds[i].max = 3.0;
  i++;

  /* ctrlConst6 (2.0) */
  ctrlBounds[i].min = 0.0;
  ctrlBounds[i].max = 4.0;
  i++;

  /* ctrlConst5 (2.0) */
  ctrlBounds[i].min = 0.0;
  ctrlBounds[i].max = 4.0;
  i++;

  /* ctrlConst4 (0) */
  ctrlBounds[i].min = -2.0;
  ctrlBounds[i].max = 2.0;
  i++;

  /* ctrlConst3 (DBL_MAX) */
  ctrlBounds[i].min = DBL_MAX;
  ctrlBounds[i].max = DBL_MAX;
  i++;

  /* ctrlConst2 (DBL_MAX) */
  ctrlBounds[i].min = DBL_MAX;
  ctrlBounds[i].max = DBL_MAX;
  i++;

  /* ctrlConst1 (DBL_MAX) */
  ctrlBounds[i].min = DBL_MAX;
  ctrlBounds[i].max = DBL_MAX;
  i++;

  /* ctrlConst0 (DBL_MAX) */
  ctrlBounds[i].min = DBL_MAX;
  ctrlBounds[i].max = DBL_MAX;

}

void
setInputBounds()
{
  /* altitudeBounds */
  altitudeBounds.min = 90.0;
  altitudeBounds.max = 90.0;

  /* fovRadiansBounds */
  fovRadiansBounds.min = 0.174533;
  fovRadiansBounds.max = 0.174533;

  /* searchAreaBounds */
  searchAreaBounds.min = 100.0;
  searchAreaBounds.max = 500.0;
}

void
setDistanceBudgetBounds()
{
  /* distanceBudgetBounds */
  distanceBudgetBounds.min = 1000.0;
  distanceBudgetBounds.max = 3000.0;
}

#define APPEND 0
#define TEST_DATA 0
#define CTRL_COMBOS 100
#define NUM_INPUTS 100000 
void
main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("usage: %s <outfile>\n", argv[0]);
    exit(0);
  }
  setCtrlBoundsMain();
  setInputBounds();
  setDistanceBudgetBounds();
  generateTrainingData(argv[1], APPEND, TEST_DATA, NUM_INPUTS, CTRL_COMBOS); 
}

