package com.cra.princess.models.kalmanfiltercomponents;

import org.apache.commons.math3.linear.ArrayRealVector;

public class KalmanFilterActuatorWeights extends ArrayRealVector {
    public KalmanFilterActuatorWeights(double a1, double a2, double a3, double a4){
        super(new double[]{a1, a2, a3, a4});
    }
}

