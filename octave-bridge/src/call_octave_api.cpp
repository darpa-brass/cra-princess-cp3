/*
 * bridge_test.cpp
 *
 *  Created on: Dec 10, 2018
 *      Author: smarotta
 */

#include "call_octave_api.h"

#include <iostream>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/ovl.h> // TODO verify this exists
#include <octave/dNDArray.h> // TODO verify this exists
#include <octave/interpreter.h>

octave_value_list callDetectionApi(Matrix* reading, Matrix* trainAdapt, int sensor, NDArray* failureStatus)
{
	// Put objects into an octave_value_list
	octave_value_list in;
	in(0) = *reading;
	in(1) = sensor;
	in(2) = *trainAdapt;
	in(3) = *failureStatus;

	// Call feval with "detection" as function and octave_value_list as arguments
	octave_value_list out = feval ("detection", in, 1);
	// Return the value list (consider creating a struct that has the values listed out)
	return out;
}

octave_value_list callAdaptationApi(Matrix* reading, Matrix* trainAdapt, int sensor)
{
	// Put objects into an octave_value_list
	octave_value_list in;
	in(0) = *reading;
	in(1) = sensor;
	in(2) = *trainAdapt;

	// Call feval with "adapt" as function and octave_value_list as arguments
	octave_value_list out = feval ("adapt", in, 1);

	// Return the value list (consider creating a struct that has the values listed out)
	return out;
}
