package com.cra.princess.models.kalmanfiltercomponents;

import com.cra.princess.localizationalgorithm.components.ActuatorVector;

public class KalmanFilterActuatorVector extends ActuatorVector{
  public KalmanFilterActuatorVector(double a1, double a2, double a3, double a4, double a5){
    super(new double[]{a1, a2, a3, a4, a5});
  }
}
