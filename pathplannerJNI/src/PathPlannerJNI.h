/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class PathPlannerJNI */

#ifndef _Included_PathPlannerJNI
#define _Included_PathPlannerJNI
#ifdef __cplusplus
extern "C" {
#endif
#undef PathPlannerJNI_MAX_PLAN_PTS
#define PathPlannerJNI_MAX_PLAN_PTS 128L
#undef PathPlannerJNI_END_MARKER
#define PathPlannerJNI_END_MARKER 1.7976931348623157E308
#undef PathPlannerJNI_DBL_MAX
#define PathPlannerJNI_DBL_MAX 1.7976931348623157E308
/*
 * Class:     PathPlannerJNI
 * Method:    nativeCreatePlan
 * Signature: (DDDDDDDDDDDDDDDDDDDDDDDDDDD[Ljava/lang/Object;IDD)[Ljava/lang/Object;
 */
JNIEXPORT jobjectArray JNICALL Java_PathPlannerJNI_nativeCreatePlan
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble, jobjectArray, jint, jdouble, jdouble);

#ifdef __cplusplus
}
#endif
#endif