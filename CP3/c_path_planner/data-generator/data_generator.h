#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

typedef struct location_struct
{
  double x;
  double y;
} location_struct;

typedef struct bounds_struct
{
  double min;
  double max;
} bounds_struct;

typedef struct metrics_struct
{
  double distance;
  double coverage;
} metrics_struct;

typedef struct input_struct
{
  double altitude;
  double fovRadians;
  location_struct startLocation;
  location_struct returnLocation;
  location_struct searchArea[4];
} input_struct;

#define NUM_CONTROLS 23

/* Path planner specific defines */
#define END_MARKER DBL_MAX
#define MAX_PLAN_PTS 128 // max number of location_structs in path

/* Global vars (PP specific) */
bounds_struct ctrlBounds[NUM_CONTROLS];
bounds_struct altitudeBounds;
bounds_struct fovRadiansBounds;
bounds_struct searchAreaBounds;
bounds_struct distanceBudgetBounds;

/* set control bounds (note: make inline or macro) */
void setCtrlBounds(int index, double min, double max);

/* obtain an array of NUM_CONTROLS random values within appropriate ranges */
void generateControls(double *ctrlsOutput);

/* given index of control, generate random value within range */
double generateUniformCtrl(int ctrlIndex);

/* given min and max values, generate a random value within range */
double generateUniform(double min, double max);

/* given controls and input, obtain output as array of location_struct */
int calculateOutput(location_struct *output, 
                    double *controls, 
                    input_struct *input);

/* Given input, output, fill in metrics struct */
void calculateMetrics(metrics_struct *metrics,
		      input_struct *input, 
		      location_struct *output,
		      double distanceBudget);

/* write headers to given open file descriptor */
void writeTrainingHeaders(FILE *fp);

/* write single training example to open file descriptor */
void writeTrainingData(FILE *fp, 
		       double *controls, 
		       input_struct *input,
		       metrics_struct *metrics,
		       double distanceBudget);

/* generate random input and fill in input struct argument */
void generateTrainingInput(input_struct *input);

/* generate data set and write to specified file */
void generateTrainingData(char *filename,
                          int append,    //bool
			  int testData,  //bool
			  int numInputs,
			  int numControls);

#endif /* DATA_GENERAHOR_H */
