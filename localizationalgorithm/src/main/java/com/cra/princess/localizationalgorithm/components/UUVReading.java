package com.cra.princess.localizationalgorithm.components;

import com.cra.princess.localizationalgorithm.KinematicsModel;
import org.apache.commons.lang3.StringUtils;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.RealVector;

/**
 * Implementing class for KalmanFilterObservation<p>
 * Contains the following: <br>
 * <b>actuatorValues</b> - variables from actuator of system<br>
 * <b>measurements</b>   - variables from sensors<br>
 * <b>actuatorNoise</b>  - process noise generated from actuator measurement conversion<p>
 * In this implementation the actuatorValues and measurements are not interdependent<br>
 */
public class UUVReading{
    private static final int KINEMATIC = 0;
    private static final int NOISE = 1;
    //TODO: currently hard coded to be [propeller rpm, gear ratio, pitch angle, slip, heading angle]
    private RealVector actuatorValues;
    private RealVector measurements;

    /**
     * @param actuatorValues vector of values
     * @param measurements vector of measurements
     */
    public UUVReading(RealVector actuatorValues,RealVector measurements){
        if(actuatorValues.getDimension() != 5)
            throw new IllegalArgumentException(String.format("ActuatorValues dimension should be 5 but was %s ", actuatorValues.getDimension()));
        this.actuatorValues = actuatorValues;
        this.measurements	= measurements;
    }

    /**
     * Assumes that the actuator values are meant to preserve velocity readings
     * TODO: Only used for the basic demo!!
     * @param measurements vector of measurements
     */
    public UUVReading(RealVector measurements){
        this.actuatorValues = null;
        this.measurements	= measurements;
    }

    /**
     * Assumes Kinematics of UUV
     * Standard conversion from UUV specifications to speed/accel:
     * Speed measured in inches per second
     *
     * 	  	          RPM     PITCH     100  - SLIP      1
     *		SPEED =  ----- X  ----- X  ------------- X  --
     *     			 RATIO      1 			100   		60
     *
     * Pitch Angle (0 to 2*pi)
     * Heading Angle relative to true north in radians (0 to pi/4)
     * Divided by 60 to obtain inches per second.
     * @param prevState - RealVector(prevX, prevY, prevV_x, prevV_y)
     * @return measurement of current velocity and acceleration
     */
    public RealVector convertToKinematics(RealVector prevState){
        if(this.actuatorValues == null)
            return new ArrayRealVector(new double[] {0, 0, 0, 0});
        return conversionHelper(this.actuatorValues, prevState, KINEMATIC);
    }

    private static RealVector conversionHelper(RealVector vectorToConvert, RealVector prevVector, int conversionType){
        double rpm 		= vectorToConvert.getEntry(0);
        double ratio	= vectorToConvert.getEntry(1);
        double pitch 	= vectorToConvert.getEntry(2);
        double slip  	= vectorToConvert.getEntry(3);
        double heading 	= vectorToConvert.getEntry(4);

        if(conversionType == KINEMATIC) {
            double[] nextAccel = KinematicsModel.getAcceleration(new double[] {rpm, ratio, pitch, slip, heading},
                    new double[] {prevVector.getEntry(2), prevVector.getEntry(3)});
            return new ArrayRealVector(new double[] {0, 0, nextAccel[0], nextAccel[1]});
        }
        else if(conversionType == NOISE)
            throw new UnsupportedOperationException("Noise conversion not supported!");
        else
            throw new IllegalArgumentException("conversion type was neither KINEMATIC nor NOISE!");
    }

    /**
     * Helper method applies Gaussian product rule
     * @param variances - list of n variances
     * @return double - product of n variances
     */
    private static double productNoise(double[] variances){
        double numerator = 1.0;
        double denominator = 0.0;
        for(int i=0;i<variances.length;i++){
            for(int j=i;j<variances.length;j++){
                denominator += Math.pow(variances[i]*variances[j],2);
            }
            numerator *= variances[i];
        }
        numerator *= Math.pow(numerator, 2);
        if(denominator == 0 || Double.isNaN(denominator)) {
            return 0;
        } else {
            return 1 + numerator/denominator;
        }
    }

    public RealVector getMeasurements() {
        return this.measurements;
    }

    public RealVector getActuatorValues() {
        return this.actuatorValues;
    }

    @Override
    public String toString() {
        return "KFObservation(measurements=<" +
                (this.measurements == null ? "(null)" : StringUtils.join(this.measurements.toArray(), ',')) +
                ">, actuators=<" + (this.actuatorValues == null ? "(null)" : StringUtils.join(this.actuatorValues.toArray(), ',')) +
                ">)";
    }
}
