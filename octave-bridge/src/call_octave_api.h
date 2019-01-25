/*
 * bridge_test.h
 *
 *  Created on: Jan 3, 2019
 *      Author: smarotta
 */

#ifndef SRC_CALL_OCTAVE_API_H_
#define SRC_CALL_OCTAVE_API_H_


#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/ovl.h>
#include <octave/dNDArray.h>

octave_value_list callDetectionApi(Matrix* reading, Matrix* trainAdapt, int sensor, NDArray* failureStatus);

octave_value_list callAdaptationApi(Matrix* reading, Matrix* trainAdapt, int sensor);


#endif /* SRC_CALL_OCTAVE_API_H_ */
