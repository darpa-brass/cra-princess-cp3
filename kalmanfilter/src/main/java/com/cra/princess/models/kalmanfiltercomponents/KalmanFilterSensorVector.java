package com.cra.princess.models.kalmanfiltercomponents;

import com.cra.princess.localizationalgorithm.components.SensorVector;

public class KalmanFilterSensorVector extends SensorVector{
    public KalmanFilterSensorVector(double a1, double a2){
        super(new double[]{a1, a2});
    }
}
