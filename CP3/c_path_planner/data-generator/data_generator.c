#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <assert.h>

#include "data_generator.h"
#include "metric_calculator.h"

#define drand48() (rand() / (RAND_MAX + 1.0))

extern bounds_struct ctrlBounds[NUM_CONTROLS];

/* set control bounds (note: make inline or macro) */
inline void
setCtrlBounds(int index, double min, double max)
{
  ctrlBounds[index].min = min;
  ctrlBounds[index].max = max;  
}


/* obtain an array of NUM_CONTROLS random values within appropriate ranges */
inline void 
generateControls(double *ctrlsOutput)
{
  int i;
  for(i = 0; i < NUM_CONTROLS; i++) {
    ctrlsOutput[i] = generateUniformCtrl(i);
  }
}

/* given index of control, generate random value within range */	
inline double
generateUniformCtrl(int ctrlIndex)
{
  return generateUniform(ctrlBounds[ctrlIndex].min,ctrlBounds[ctrlIndex].max);
}

/* given min and max values, generate a random value within range */
inline double
generateUniform(double min, double max)
{
  return drand48() * (max - min) + min;
}

/* given controls and input, obtain output as array of location_struct
 * Note: the ordering of controls much match the parameter order in the
 *       transformed createPlan function
 */
//double plan[MAX_PLAN_PTS][2];

int __attribute__((optimize("O0"))) 
calculateOutput(location_struct *output,
                double *controls,
                input_struct *input)
{
  int i;   
  double plan[MAX_PLAN_PTS][2];
  //double **plan;
  double startLocationX = input->startLocation.x;
  double startLocationY = input->startLocation.y;
  double returnLocationX = input->returnLocation.x;
  double returnLocationY = input->returnLocation.y;
  double altitude = input->altitude;
  double fovRadians = input->fovRadians;

  double searchArea[4][2];

  plan[MAX_PLAN_PTS-1][0] = END_MARKER;
  plan[MAX_PLAN_PTS-1][1] = END_MARKER;

  //plan = (double **)(malloc(sizeof(double *)*MAX_PLAN_PTS*10));
  //for(i = 0; i < MAX_PLAN_PTS; i++) {
  //  plan[i] = (double *)(malloc(sizeof(double)*2));
  //}

  //printf("Entered calculateOutput()\n");
  //fflush(stdout);

  /* Note: assumes that search area is always 4 points */
  for(i = 0; i < 4; i++) {
    searchArea[i][0] = input->searchArea[i].x;
    searchArea[i][1] = input->searchArea[i].y;
  }   

  /* TODO: handle exceptions */
  createPlan(controls[0], controls[1], controls[2], controls[3],
             controls[4], controls[5], controls[6], controls[7],
             controls[8], controls[9], controls[10], controls[11],
	     controls[12], controls[13], controls[14], controls[15],
	     controls[16], controls[17], controls[18], controls[19],
	     controls[20], controls[21], controls[22],
	     plan, startLocationX, startLocationY, returnLocationX,
	     returnLocationY, searchArea, 4, altitude, fovRadians);


  /* fill in output array */
  for(i = 0; i < MAX_PLAN_PTS; i++) {
    //printf("calculatOutput(): i = %d\n", i);
    //fflush(stdout);
    //printf("trying to access output\n");
    //fflush(stdout);
    //printf("output[i].x = %f\n", output[i].x);
    //fflush(stdout);
    output[i].x = plan[i][0];
    output[i].y = plan[i][1];
    if(plan[i][0] == DBL_MAX) {
      break;
    } 
  }

  return 0;
}

/* Given input, output, fill in metrics struct */
void 
calculateMetrics(metrics_struct *metrics, 
		 input_struct *input, 
		 location_struct *output,
		 double distanceBudget)
{
  metrics->distance = calculateDistance(output);
  metrics->coverage = calculateCoverage(output, input);
  if(metrics->distance > distanceBudget) {
    metrics->coverage = 0.0;
  }
}

/* write headers to given open file descriptor 
 * Note: this is specific to path planner 
 */
void
writeTrainingHeaders(FILE *fp)
{
  fprintf(fp, "startLocationX,startLocationY,returnLocationX,returnLocationY,searchAreaX0,searchAreaY0,searchAreaX1,searchAreaY1,searchAreaX2,searchAreaY2,searchAreaX3,searchAreaY3,altitude,fovRadians,distanceBudget,ctrlCmp4,ctrlCmp3,ctrlCmp2,ctrlCmp1,ctrlCmp0,ctrlLoop1,ctrlLoop0,ctrlConst15,ctrlConst14,ctrlConst13,ctrlConst12,ctrlConst11,ctrlConst10,ctrlConst9,ctrlConst8,ctrlConst7,ctrlConst6,ctrlConst5,ctrlConst4,ctrlConst3,ctrlConst2,ctrlConst1,ctrlConst0,distance,coverage,outputBegin\n");
}

/* write single training example to open file descriptor */
char str[8192*100000];
void writeTrainingData(FILE *fp,
                       double *controls,
                       input_struct *input,
                       metrics_struct *metrics,
		       double distanceBudget)
{
  int i;
  static int len = 0;
  static int times = 0;

  len += sprintf(str+len, "%f,%f,", input->startLocation.x, 
                 input->startLocation.y);
  len += sprintf(str+len, "%f,%f,", input->returnLocation.x, 
                  input->returnLocation.y);
  
  /* NOTE: assumes search area has 4 points */
  for(i = 0; i < 4; i++) {
    len += sprintf(str+len, "%f,%f,", input->searchArea[i].x, 
                   input->searchArea[i].y);
  }

  len += sprintf(str+len, "%f,%f,%f,", input->altitude, input->fovRadians, 
                 distanceBudget);

  for(i = 0; i < NUM_CONTROLS; i++) {
    len += sprintf(str+len, "%f,", controls[i]);
  }

  len += sprintf(str+len, "%f,%f\n", metrics->distance, metrics->coverage);
 
  //printf("len: %d\n", len); 

  times++;
  if(times == 5000) {
    fwrite(str, sizeof(char), len, fp);
    len = 0;
    times = 0;
  }
  /* For now, do not write the output */
}

/* generate random input and fill in input struct argument */
void
generateTrainingInput(input_struct *input)
{
  /* To faithfully represent a CP3 scenario, we need to generate an initial 
   * search area, and a subset of that search area (i.e., the new search area 
   * after the perturbation). This is because we need a reference point for 
   * the return point, which will differ from the start point in the 
   * after-perturbation search area.
   */
  double searchAreaValX = generateUniform(searchAreaBounds.min,
                                          searchAreaBounds.max);
  double searchAreaValY = generateUniform(searchAreaBounds.min,
                                          searchAreaBounds.max);
  double newSearchAreaMinY = generateUniform(0.0, searchAreaValY);

  /* NOTE: assumes 4 points in search area, rectangular */
  input->searchArea[0].x = 0.0;
  input->searchArea[0].y = newSearchAreaMinY;
  input->searchArea[1].x = 0.0;
  input->searchArea[1].y = searchAreaValY;
  input->searchArea[2].x = searchAreaValX;
  input->searchArea[2].y = searchAreaValY;
  input->searchArea[3].x = searchAreaValX;
  input->searchArea[3].y = newSearchAreaMinY;

  input->altitude = generateUniform(altitudeBounds.min, altitudeBounds.max);
  input->fovRadians = generateUniform(fovRadiansBounds.min, 
		                     fovRadiansBounds.max);

  input->startLocation.x = generateUniform(0.0, searchAreaValX);
  input->startLocation.y = newSearchAreaMinY;

  input->returnLocation.x = 0.0;
  input->returnLocation.y = 0.0;  
}

/* generate data set and write to specified file */
void 
generateTrainingData(char *filename,
                     int append,    //bool
                     int testData,  //bool
                     int numInputs,
                     int numControls)
{
  int i, j;
  int inputIdx;
  FILE *fp = NULL;
  input_struct input;
  double distanceBudget;
  double optimalCoverage;
  double optimalCoverageDist;
  double optimalDistance;
  double optimalDistanceDist;
  double *optimalControls = NULL;
  double *optimalControlsDist = NULL;
  double baselineControls[NUM_CONTROLS];
  double generatedControls[NUM_CONTROLS];
  location_struct baselineOutput[MAX_PLAN_PTS];
  location_struct output[MAX_PLAN_PTS];
  location_struct *optimalOutput = NULL;
  location_struct *optimalOutputDist = NULL;
  int ctrlIterations = testData ? 1 : numControls;
  int res;
  metrics_struct metrics;
  metrics_struct baselineMetrics;
  metrics_struct optimalMetrics;

  /* initialize baseline controls (avg of ctrl bounds) and get output */
  for(j = 0; j < NUM_CONTROLS; j++) {
    if(ctrlBounds[j].min == ctrlBounds[j].max) {
      baselineControls[j] = ctrlBounds[j].max;
    } else {
      baselineControls[j] = (ctrlBounds[j].min + ctrlBounds[j].max)/2.0;
    }
  }

  if(append) {
    fp = fopen(filename, "ab");
  } else {
    fp = fopen(filename, "wb");
    writeTrainingHeaders(fp);
  }
  if(!fp) {
    fprintf(stderr, "Unable to open file: %s\n", filename);
  }

  inputIdx = 0;
  while(inputIdx < numInputs) {
    if(inputIdx % 5000 == 0) {
      printf("Generating training record: %d\n", inputIdx);
      fflush(stdout);
    }
    generateTrainingInput(&input);
    distanceBudget = generateUniform(distanceBudgetBounds.min,
                                     distanceBudgetBounds.max);
    optimalCoverage = -1.0;
    optimalCoverageDist = -1.0;
    optimalDistance = DBL_MAX;
    optimalDistanceDist = DBL_MAX;
    optimalControls = NULL;
    optimalControlsDist = NULL;
    optimalOutput = NULL;
    optimalOutputDist = NULL;
    
    for(i = 0; i < ctrlIterations; i++) {
      assert(input.altitude == 90.0);
      generateControls(generatedControls);
      /* TODO: handle exceptions */
      //printf("in control iterations loop: i = %d\n", i); fflush(stdout);
      res = calculateOutput(output, /*baselineControls*/ generatedControls, &input);
      if(res == 0) { // test for exception 
        calculateMetrics(&metrics, &input, output, distanceBudget);
        //printf("after calculateMetrics: i = %d, distance = %f, coverage = %f\n",
	//       i, metrics.distance, metrics.coverage);	
        /* First try to maximize coverage while under distance budget */
        if ( ((!optimalControls) || (metrics.coverage > optimalCoverage)) &&
             (metrics.distance < distanceBudget)) {
          optimalCoverage = metrics.coverage;
	  optimalControls = generatedControls;
	  optimalOutput = output;
	  optimalDistance = metrics.distance; 
        }
        
        /* Find minimal distance in case we can't get under budget */
        /* START FROM HERE */
        if(metrics.distance < optimalDistance) {
          optimalCoverageDist = metrics.coverage;
          optimalControlsDist = generatedControls;
          optimalOutputDist = output;
          optimalDistanceDist = metrics.distance;
        }
      }  
    }

    res = calculateOutput(baselineOutput, baselineControls, &input);
    //if(!res) { // TODO: deal with this case (baseline throws exception)
    //  continue;
    //}

    /* In case we never got a valid output under distance budget */
    if(!optimalControls) {
      optimalControls = optimalControlsDist;
      optimalCoverage = optimalCoverageDist;
      optimalDistance = optimalDistanceDist;
      optimalOutput = optimalOutputDist;
    }

    optimalMetrics.distance = optimalDistance;
    optimalMetrics.coverage = optimalCoverage;

    /* get metrics with baseline controls */
    calculateMetrics(&baselineMetrics, 
                     &input, 
                     baselineOutput, 
                     distanceBudget);
   
    /* could do distance < distanceBudget here if we trust the budget */ 
    if((baselineMetrics.coverage > optimalCoverage) &&
       (baselineMetrics.distance < optimalDistance)) {
      optimalControls = baselineControls;
      optimalMetrics.distance = baselineMetrics.distance;
      optimalMetrics.coverage = baselineMetrics.coverage;
    }

    /* write data line */
    writeTrainingData(fp, 
                      optimalControls, 
                      &input, 
                      &optimalMetrics, 
                      distanceBudget);
    inputIdx++;
  }
}

