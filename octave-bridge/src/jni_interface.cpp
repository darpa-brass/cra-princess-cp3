#include <jni.h>
#include <octave/oct.h>
#include <octave/ovl.h>
#include <octave/dNDArray.h>
#include <octave/interpreter.h>
#include <iostream>

#include "call_octave_api.h"

#ifndef _PRINCESS_JNI_INTERFACE
#define _PRINCESS_JNI_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif

octave::embedded_application* app;
bool initialized = false;

/**
 * This function takes a 1D java array of Double, represented in JNI as a jdoubleArray (in Java,
 * an Array<double>) and converts it into a single-dimensional NDArray, an Octave array of double.
 */
NDArray* jdoubleArrayToOctaveArray(JNIEnv * env, jdoubleArray& jda)
{
	// put the contents of the jDoubleArray into the array octOut
	jdouble* elems = env->GetDoubleArrayElements(jda, 0);
	jsize numElems = env->GetArrayLength(jda);

	dim_vector dv (1, (int)numElems);
	NDArray* arr = new NDArray(dv);

	for (int i = 0; i < numElems; ++i)
	{
		(*arr)(i) = elems[i];
	}

	return arr;
	// NOTE: Whoever uses this function needs to delete the value that it returns when they're done using it!
}

/**
 * This function takes a 2D java array of Double, represented in JNI as a jobectArray (in Java,
 * an Array<Array<double>>) and converts it into an MxN matrix containing the elements of the
 * 2D array. For this function, M is the dimension of the outer array, and N is the dimension
 * of the inner arrays.
 *
 * This function assumes that N is fixed. In Java, if you have an array of arrays, each "sub-array"
 * could theoretically have a different size. This function assumes that each sub-array is the same
 * size.
 *
 * This function also assumes that M > 0. It looks at the size of the first sub-array to obtain the
 * value of N. If there are no sub-arrays in the top-level array, then this call will fail.
 *
 * NOTE: This function allocates memory for its return value using 'new'. Whoever uses this function
 * needs to delete the value that it returns when they're done using it!
 */
Matrix* jobjectArrayToOctaveMatrix(JNIEnv * env, jobjectArray& jda)
{
	int m = env->GetArrayLength(jda);
	jdoubleArray dim = (jdoubleArray)env->GetObjectArrayElement(jda, 0);

	int n = env->GetArrayLength(dim);

	// put the contents of the 2D jDoubleArray into the matrix octOut
	dim_vector dv (m, n);
	Matrix* mtx = new Matrix(dv);

    // handle case where n is variable
	for (int i = 0; i < m; ++i) {
		jdoubleArray oneDim = (jdoubleArray)env->GetObjectArrayElement(jda, i);
		jdouble *elem = env->GetDoubleArrayElements(oneDim, 0);
		for (int j = 0; j < n; ++j) {
			(*mtx)(i, j) = elem[j];
		}
	}

	return mtx;
}

/**
 * This function takes a jdoubleArray, a JNI object that represents an array of jdouble (in Java,
 * an Array<double>) and converts it to a Mx1 matrix containing the elements of the jdouble array.
 *
 * NOTE: This function allocates memory for its return value using 'new'. Whoever uses this function
 * needs to delete the value that it returns when they're done using it!
 */
Matrix* jdoubleArrayToOctaveMatrix(JNIEnv * env, jdoubleArray& jda)
{
	// put the contents of the jDoubleArray into the array octOut
	jdouble* elems = env->GetDoubleArrayElements(jda, 0);
	jsize numElems = env->GetArrayLength(jda);

	dim_vector dv ((int)numElems, 1);
	Matrix* mtx = new Matrix(dv);

	for (int i = 0; i < numElems; ++i)
	{
		(*mtx)(i, 0) = elems[i];
	}

	return mtx;
}

/**
 * This function converts an Octave NDArray (1D array of doubles) into a jdoubleArray (in Java,
 * an Array<double>).
 */
jdoubleArray convertToJdoublearray(JNIEnv * env, NDArray& ndArr, size_t start_idx) {
	int len = ndArr.numel();
	jdoubleArray result = env->NewDoubleArray(len - start_idx);
	jboolean isCopy;
	jdouble destElems[len - start_idx];

	for (int i = start_idx; i < len; ++i) {
		destElems[i - start_idx] = ndArr(i);
	}

	env->SetDoubleArrayRegion(result, 0, len - start_idx, destElems);
	return result;
}

/**
 * Creates and starts an embedded Octave application and initializes the script path
 *
 * Parameters:
 *  path - a string representing the path (relative or absolute) containing the "detection" and "adapt" scripts
 *
 * Returns:
 *  true if the embedded application was successfully started
 */
JNIEXPORT jboolean JNICALL Java_com_cra_princess_remusclient_sensortransformer_NativeSensorTransformer_init(JNIEnv * env, jobject thisObj, jstring path)
{
    if (!initialized) {
        string_vector argv(2);
        argv(0) = "embedded";
        argv(1) = "-q";
        app = new octave::embedded_application(2, argv.c_str_vec());
        bool success = app->execute();
        if (success) {
            const char* pathStr = env->GetStringUTFChars(path, 0);
            octave_value_list arg;
            arg(0) = pathStr;
            env->ReleaseStringUTFChars(path, pathStr);
            feval("addpath", arg);
            initialized = true;
        }
        return (jboolean)success;
	} else return false;
}

/**
 * Performs cleanup, consisting of deallocating and destroying the embedded Octave application
 */
JNIEXPORT void JNICALL Java_com_cra_princess_remusclient_sensortransformer_NativeSensorTransformer_cleanUp(JNIEnv * env, jobject thisObj)
{
	delete app;
}

/**
 * Invokes the detection script via Octave
 *
 * Parameters:
 *  reading - An Array<Array<Double>> (2D array) containing sensor readings of all types. The size of the 2D array is 1x12.
 *  train_adapt - A 1D array containing training data
 *  sensor - an int representing the index of the sensor for which we want to detect failures
 *  failure_status - 1 1D array containing failure states
 *
 * Returns:
 *  a value of type com.cra.princess.remusclient.sensortransformer.DetectionResult
 */
JNIEXPORT jobject JNICALL Java_com_cra_princess_remusclient_sensortransformer_NativeSensorTransformer_detect(JNIEnv * env, jobject thisObj,
		jobjectArray reading, jdoubleArray train_adapt, jint sensor, jdoubleArray failure_status)
{
	// Convert the input parameters to their Octave types
	Matrix* readingOct = jobjectArrayToOctaveMatrix(env, reading);
	Matrix* trainAdaptOct = jdoubleArrayToOctaveMatrix(env, train_adapt);
	int sensorOct = (int)sensor;
	NDArray* failureStatusOct = jdoubleArrayToOctaveArray(env, failure_status);

	// Pass arguments to corresponding functions in bridge_test
	octave_value_list ret = callDetectionApi(readingOct, trainAdaptOct, sensorOct, failureStatusOct);

	delete readingOct;
	delete trainAdaptOct;
	delete failureStatusOct;

	// return a value (populate a jobject)
	jobject detectResult;
	jmethodID constructor;
	jclass clazz;
	clazz = env->FindClass("com/cra/princess/remusclient/sensortransformer/DetectionResult");

	constructor = env->GetMethodID(clazz, "<init>", "(DI[D)V");

	NDArray outArr = ret(0).array_value();
	jdoubleArray newFSJni = convertToJdoublearray(env, outArr, 2);
	detectResult = env->NewObject(clazz, constructor, outArr(0), (int)(outArr(1)), newFSJni);
	return detectResult;
}

/**
 * Invokes the adapt script via Octave
 *
 * Parameters:
 *  reading - An Array<Array<Double>> (2D array) containing sensor readings of all types. The size of the 2D array is 1x12.
 *  train_adapt - A 1D array containing training data
 *  sensor - an int representing the index of the sensor we want to adapt
 *
 * Returns:
 *  a value of type com.cra.princess.remusclient.sensortransformer.AdaptationResult
 */
JNIEXPORT jobject JNICALL Java_com_cra_princess_remusclient_sensortransformer_NativeSensorTransformer_adapt(JNIEnv * env, jobject thisObj,
		jobjectArray reading, jdoubleArray train_adapt, jint sensor)
{
	// Convert the input parameters to their Octave types
	Matrix* readingOct = jobjectArrayToOctaveMatrix(env, reading);
	Matrix* trainAdaptOct = jdoubleArrayToOctaveMatrix(env, train_adapt);
	int sensorOct = (int)sensor;

	// Pass arguments to corresponding functions in bridge_test
	octave_value_list ret = callAdaptationApi(readingOct, trainAdaptOct, sensorOct);

	delete readingOct;
	delete trainAdaptOct;

	// return a value (populate a jobject)
	jobject adaptResult;
	jmethodID constructor;
	jclass clazz;
	clazz = env->FindClass("com/cra/princess/remusclient/sensortransformer/AdaptationResult");

	constructor = env->GetMethodID(clazz, "<init>", "(DD)V");

	NDArray outArr = ret(0).array_value();
	adaptResult = env->NewObject(clazz, constructor, outArr(0), outArr(1));
	return adaptResult;
}

#ifdef __cplusplus
}
#endif
#endif
