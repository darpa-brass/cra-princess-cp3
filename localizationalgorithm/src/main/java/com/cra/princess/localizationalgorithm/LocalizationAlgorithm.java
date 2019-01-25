package com.cra.princess.localizationalgorithm;

import com.cra.princess.localizationalgorithm.components.*;
import org.apache.commons.math3.linear.RealMatrix;

public interface LocalizationAlgorithm {

    LocalizationOutput runAlgorithm(ComponentState state,
                                    ActuatorVector actuators,
                                    SensorVector sensorValues,
                                    RealMatrix p_prev);

    ComponentState getPredictedState(ComponentState state, UUVReading reading);

    long getSamplingPeriod();

    RealMatrix getTransitionMatrix();

    String toString();
}
