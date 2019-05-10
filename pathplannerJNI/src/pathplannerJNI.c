#include <jni.h>
#include <stdio.h>
#include <float.h>
#include "PathPlannerJNI.h"

#include <stdlib.h>

//#define DEBUG

#define MAX_PLAN_PTS 128 
#define END_MARKER DBL_MAX

JNIEXPORT jobjectArray JNICALL 
Java_com_cra_princess_pathplanner_PathPlannerJNI_nativeCreatePlan(
		                          JNIEnv *env, 
					  jobject thisObj,
		                          jdouble ctrlCmp4,
                                          jdouble ctrlCmp3,
                                          jdouble ctrlCmp2,
                                          jdouble ctrlCmp1,
                                          jdouble ctrlCmp0,
                                          jdouble ctrlLoop1,
                                          jdouble ctrlLoop0,
                                          jdouble ctrlConst15,
                                          jdouble ctrlConst14,
                                          jdouble ctrlConst13,
                                          jdouble ctrlConst12,
                                          jdouble ctrlConst11,
                                          jdouble ctrlConst10,
                                          jdouble ctrlConst9,
                                          jdouble ctrlConst8,
                                          jdouble ctrlConst7,
                                          jdouble ctrlConst6,
                                          jdouble ctrlConst5,
                                          jdouble ctrlConst4,
                                          jdouble ctrlConst3,
                                          jdouble ctrlConst2,
                                          jdouble ctrlConst1,
                                          jdouble ctrlConst0,
                                          jdouble startLocationX,
                                          jdouble startLocationY,
                                          jdouble returnLocationX,
                                          jdouble returnLocationY,
					  jobjectArray searchArea,
					  jint numPts,
                                          jdouble altitude, 
                                          jdouble fovRadians) 
{
  int i;

  double plan[MAX_PLAN_PTS][2];
  double searchAreaC[4][2];

  /* for constructing 2d java array to return */
  jclass doubleArrayClass = (*env)->FindClass(env, "[D");
  jobjectArray returnArray = 
    (*env)->NewObjectArray(env, (jsize)MAX_PLAN_PTS, doubleArrayClass, NULL);

  /* convert search area array */
  for(int i=0; i<4; ++i){
     jdoubleArray oneDim = 
       (jdoubleArray)(*env)->GetObjectArrayElement(env, searchArea, i);
     jdouble *element=(*env)->GetDoubleArrayElements(env, oneDim, 0);
     for(int j=0; j<2; ++j) {
        searchAreaC[i][j]= element[j];
     }
  }

#ifdef DEBUG
  printf("Search area contents:\n");
  for(i = 0; i < 4; i++) {
    printf("(%f, %f) ", searchAreaC[i][0], searchAreaC[i][1]);
  }
  printf("\n");
#endif

  /* call transformed createPlan() */
  createPlan(ctrlCmp4, ctrlCmp3, ctrlCmp2, ctrlCmp1, ctrlCmp0,
            ctrlLoop1, ctrlLoop0, ctrlConst15, ctrlConst14,
            ctrlConst13, ctrlConst12, ctrlConst11, ctrlConst10,
            ctrlConst9, ctrlConst8, ctrlConst7, ctrlConst6,
            ctrlConst5, ctrlConst4, ctrlConst3, ctrlConst2,
            ctrlConst1, ctrlConst0,
            plan, startLocationX, startLocationY, returnLocationX,
            returnLocationY, searchAreaC, numPts, altitude, fovRadians);
 
#ifdef DEBUG
  printf("ctrlConst0 = %f\n", ctrlConst0);
  printf("plan output:\n");
  for(i = 0; i < MAX_PLAN_PTS; i++) {
    if(plan[i][0] == END_MARKER || plan[i][1] == END_MARKER) {
      break;
    }
    printf("plan[%d][0] = %f\n", i, plan[i][0]);
    printf("plan[%d][1] = %f\n", i, plan[i][1]);
  }
#endif

  /* convert plan array and return */
  for (unsigned int i = 0; i < MAX_PLAN_PTS; i++) {
        jdoubleArray doubleArray = (*env)->NewDoubleArray(env, 2);
        (*env)->SetDoubleArrayRegion(env, doubleArray, (jsize) 0, (jsize) 2, 
                                     (jdouble*) plan[i]);
        (*env)->SetObjectArrayElement(env, returnArray, (jsize) i,
			              doubleArray);
        (*env)->DeleteLocalRef(env, doubleArray);
  }
  return returnArray;
}
