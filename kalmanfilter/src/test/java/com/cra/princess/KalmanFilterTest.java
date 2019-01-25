package com.cra.princess;

import com.cra.princess.localizationalgorithm.components.ActuatorVector;
import com.cra.princess.localizationalgorithm.components.ComponentState;
import com.cra.princess.localizationalgorithm.components.SensorVector;
import com.cra.princess.models.KalmanFilter;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorWeights;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterSensorVector;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;
import org.apache.commons.math3.util.Pair;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

public class KalmanFilterTest {

    @Test
    public void testKFCreation(){
        KalmanFilter kf = createKF();
        RunKF(kf);
    }

    private static void RunKF(KalmanFilter kf){
        ArrayList<Pair<ActuatorVector, SensorVector>> data = new ArrayList<>();

        /**Simulated data, realistically this data would stream through ActiveMQ */
        for(int i=0;i<100;i++){
            ActuatorVector actuatorValues = new KalmanFilterActuatorVector(10, 2, Math.PI/6, 0.2, Math.PI/4);
            SensorVector stateMeasurements = new KalmanFilterSensorVector(10,10);
            data.add(new Pair<>(actuatorValues, stateMeasurements));
        }

        /**Create initial component state for Kalman Filter to ingest
        * All Subsequent states are generated from the Kalman Filter
        * These two vectors need to be the same dimension!*/
        RealVector stateComponents = new ArrayRealVector(new double[] {0.0,0.0});
        RealVector stateDeltas = new ArrayRealVector(new double[] {0, 0});
        ComponentState X0 = new ComponentState(stateComponents, stateDeltas);
        RealMatrix cov = MatrixUtils.createRealIdentityMatrix(4);

        for(Pair<ActuatorVector,SensorVector> p : data){

            /**Ignore the fact that we are reading pairs, assume this data streams from activeMQ*/
            ActuatorVector actuatorReadings = p.getFirst();
            SensorVector sensorReadings = p.getSecond();
            /** Note that the Kalman Filter only predicts 1 time-step forward, thus to obtain predictions multiple
            *  time-steps forward requires calling kf.runAlgorithm within this loop/data-stream*/
            KalmanFilterOutput kfo = kf.runAlgorithm(X0,actuatorReadings, sensorReadings, cov);
            cov = kfo.getCovariance();
            X0 = kfo.getState();
            System.out.println("errorVolumeDelta: " + kfo.getErrorVolume() + "  " + kfo.getMeasurementResidual());
        }
    }

    private static KalmanFilter createKF() {

        long dt = 1000;
        RealVector pNoise = new ArrayRealVector(new double[]{1, 1, 1, 1});
        RealVector mNoise = new ArrayRealVector(new double[]{1, 1});

        KalmanFilterActuatorWeights actuatorWeights = new KalmanFilterActuatorWeights(1.0,1.0,1.0,1.0);

        List<Integer> indicesOfMeasured = new ArrayList<>();
        indicesOfMeasured.add(3);
        indicesOfMeasured.add(2);

        return new KalmanFilter(indicesOfMeasured, actuatorWeights, dt, pNoise, mNoise);
    }
}
