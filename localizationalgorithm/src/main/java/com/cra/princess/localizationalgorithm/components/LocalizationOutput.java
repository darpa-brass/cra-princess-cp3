package com.cra.princess.localizationalgorithm.components;

import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

public interface LocalizationOutput {
    public RealMatrix getCovariance();
    public ComponentState getState();
    public double getErrorVolume();
    public RealVector getMeasurementResidual();
    public void setMeasurementResidual(RealVector measurementResidual);
}
