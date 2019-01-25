package com.cra.princess.models;

import com.cra.princess.localizationalgorithm.LocalizationAlgorithm;
import com.cra.princess.localizationalgorithm.components.ComponentState;
import com.cra.princess.localizationalgorithm.components.SensorVector;
import com.cra.princess.localizationalgorithm.components.UUVReading;
import com.cra.princess.localizationalgorithm.components.ActuatorVector;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorWeights;
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput;
import com.cra.princess.utility.math.LatLonConverter;
import org.apache.commons.math3.linear.*;
import org.apache.log4j.Logger;

import java.util.Collections;
import java.util.List;

/**
 * <p>****************************** CONTROL VARIABLES FOR PRINCESS ************************************</p>
 * <p>
 * A    - state transition matrix <br>
 * Q    - process noise covariance matrix, controlled by process noise scalar<br>
 * R    - sensor noise covariance matrix, controller by sensor noise scalars list<br>
 * B    - control input matrix<br>
 * <p>
 * <p>**************************************** Inputs **************************************************</P>
 * <p>
 * X_prev            - Previous x_prev vector, example:
 *                          [x coordinate, y coordinate, x velocity, y velocity] <br>
 * actuator settings - values of the motor system <br>
 * sensor readings   - values read from sensor system <br>
 *
 * <p>**************************************** Outputs *************************************************</P>
 * <p>
 * P        - Error estimate and covariance matrix <br>
 * X_pred   - Predicted x_prev vector<br>
 * Residual - Difference between sensor readings and the predicted values for the corresponding components
 */

public class KalmanFilter implements LocalizationAlgorithm {

    private static Logger LOG = Logger.getLogger(KalmanFilter.class.getName());
    private RealMatrix A;
    private RealMatrix Q;
    private RealMatrix R;
    private long samplingPeriod;
    LatLonConverter llc = new LatLonConverter(0.0, 0.0); //TODO: assumes starting point has lat/lon of (0,0) degrees
    private RealMatrix B;
    private RealMatrix H;

    /**
     * Specify each field manually!
     */
    private KalmanFilter(RealMatrix A, RealMatrix B, RealMatrix Q, RealMatrix H, RealMatrix R, long samplingPeriod) {
        this.samplingPeriod = samplingPeriod;
        this.A = A;
        this.B = B;
        this.Q = Q;
        this.H = H;
        this.R = R;
    }


    /**
     * @param indicesOfMeasured - List containing the indices of the state vector that are captured in sensor readings
     * @param actuatorWeights - Diagonal Terms of the B - Matrix
     * @param samplingPeriod - Time between each instance of running the Kalman Filter (measured in milliseconds)
     * @param processNoise - Component-wise independent noise induced when estimating the state vector
     * @param sensorNoise - Component-wise independent noise in sensor readings
     */
    public KalmanFilter(List<Integer> indicesOfMeasured, KalmanFilterActuatorWeights actuatorWeights,
                        long samplingPeriod, RealVector processNoise, RealVector sensorNoise) {
        this(setStateTransition(samplingPeriod, processNoise.getDimension()),
                createControlInputModel(actuatorWeights, samplingPeriod),
                computeIdealProcessNoise(processNoise, processNoise.getDimension()),
                setConversionMatrix(indicesOfMeasured, processNoise.getDimension()),
                computeIdealMeasurementNoise(sensorNoise, indicesOfMeasured.size()), samplingPeriod);
    }

    /**********************************************************************************************
     ***************************  Helper Methods for Constructor **********************************
     **********************************************************************************************/
    private static RealMatrix setConversionMatrix(List<Integer> indicesOfMeasured, int stateDim) {
        Collections.sort(indicesOfMeasured);
        int measuredDim = indicesOfMeasured.size();
        double[][] hEntries = new double[measuredDim][stateDim];
        for (int i = 0; i < measuredDim; i++) {
            for (int j = 0; j < stateDim; j++) {
                if (j == indicesOfMeasured.get(i))
                    hEntries[i][j] = 1;
                else
                    hEntries[i][j] = 0;
            }
        }
        return new Array2DRowRealMatrix(hEntries);
    }

    /**
     * Creates a model relating control inputs / actuators to x_prev changes. Resulting matrix looks like:
     * [ 0  	0 	0.5 M1*dt^2      0
     *   0  	0 	0            0.5 M2*dt^2
     *   0  	0 	M3 * dt	 	 0
     *   0		0	0			 M4 * dt]
     *
     * @param multipliers Elements to multiply by standard delta-t terms
     * @return A control-input model
     */
    private static RealMatrix createControlInputModel(RealVector multipliers, long samplingPeriod) {
        RealMatrix m = MatrixUtils.createRealMatrix(multipliers.getDimension(), multipliers.getDimension());
        int firstDeltaIndex = multipliers.getDimension() / 2;
        for (int i = 0; i < firstDeltaIndex; i++) {
            m.setEntry(i, i + firstDeltaIndex, multipliers.getEntry(i)
                * 0.5 * Math.pow(samplingPeriod / 1000.0, 2));
        }
        for (int i = firstDeltaIndex; i < multipliers.getDimension(); i++) {
            m.setEntry(i, i, multipliers.getEntry(i) * samplingPeriod / 1000.0);
        }
        return m;
    }

    /**
     * @param samplingPeriod - in milliseconds
     * @return RealMatrix representing transition matrix (or a component thereof)
     */
    private static RealMatrix setStateTransition(long samplingPeriod, int dim) {
        RealMatrix m = MatrixUtils.createRealIdentityMatrix(dim);
        int firstDeltaIndex = dim / 2;
        for (int i = 0; i < firstDeltaIndex; i++) {
            // delta units are in seconds, samplingPeriod is in ms
            m.setEntry(i, i + firstDeltaIndex, samplingPeriod / 1000.0);
        }
        return m;
    }

    /**
     * Computes process noise by assuming a diagonal matrix
     * where all entries along diagonal have same noise
     *
     * @param noises - noise for each component due to process overhead
     * @return process noise matrix
     */
    private static RealMatrix computeIdealProcessNoise(RealVector noises, int dim) {
        if (noises.getDimension() != dim)
            throw new IllegalArgumentException(String.format("noise vector was %s but should be %s",
                noises.getDimension(), dim));
        RealMatrix I = MatrixUtils.createRealIdentityMatrix(dim);
        for (int i = 0; i < I.getColumnDimension(); i++)
            I.setEntry(i, i, noises.getEntry(i));
        return I;
    }

    /**
     * Computes process noise by assuming a diagonal matrix
     * where all entries along diagonal have same noise
     *
     * @param noises - noise for each component due to measurement error
     * @return sensorMeasurment noise matrix
     */
    private static RealMatrix computeIdealMeasurementNoise(RealVector noises, int dim) {
        if (noises.getDimension() != dim)
            throw new IllegalArgumentException("noises list size: " + noises.getDimension()
                    + "does not match H row dim: " + dim);
        RealMatrix mNoise = MatrixUtils.createRealIdentityMatrix(noises.getDimension());
        for (int i = 0; i < mNoise.getRowDimension(); i++) {
            mNoise.setEntry(i, i, noises.getEntry(i));
        }
        return mNoise;
    }


    /**********************************************************************************************************
     ***************************************  Kalman Filter Method and Helpers ********************************
     **********************************************************************************************************/

    /***
     * Runs Kalman filter algorithm one step forward in time
     * @param x_prevLatLon - the previous state estimation of the component
     * @param actuatorSettings - Values for each motor control component
     * @param sensorReadings - Measurements taken from sensor readings
     * @param P_prev - Covariance Matrix associated with prev state estimation
     * @return KalmanFilterOutput - contains state estimate, covariance and residual
     */
    public KalmanFilterOutput runAlgorithm(ComponentState x_prevLatLon,
                                           ActuatorVector actuatorSettings,
                                           SensorVector sensorReadings,
                                           RealMatrix P_prev) {

        //convert position from lat/lon to XY
        ComponentState x_prev = toComponentWithXY(x_prevLatLon);
        UUVReading uuvReading = new UUVReading(actuatorSettings, sensorReadings);
        RealVector Zn = uuvReading.getMeasurements();

        if (Zn.getDimension() != this.H.getRowDimension())
            throw new IllegalArgumentException(String.format("H row dimension is %s but sensorReading "
                    + "vector dimension is %s ", H.getRowDimension(), Zn.getDimension()));

        // convert actuator measurements to velocity and acceleration
        RealVector X = x_prev.getCombinedState();
        RealVector Un = uuvReading.convertToKinematics(X);
        LOG.debug("Un = " + Un);
        // prediction step takes into account X and X_extra
        RealVector X_predicted = A.operate(X).add(B.operate(Un));
        RealMatrix P_predicted = A.multiply(P_prev).multiply(A.transpose()).add(Q);

        // correction step, H converts from estimation space to sensorMeasurement space
        RealVector Y_hat = Zn.subtract(H.operate(X_predicted)); // the residual
        RealMatrix S = (H.multiply(P_predicted).multiply(H.transpose())).add(R);

        // H-transpose and K converts from sensorMeasurement space back to estimation space
        RealMatrix K = P_predicted.multiply(H.transpose()).multiply(MatrixUtils.inverse(S));
        RealVector Xn = X_predicted.add(K.operate(Y_hat));
        RealMatrix I = MatrixUtils.createRealIdentityMatrix(H.getColumnDimension());
        RealMatrix Pn = (I.subtract(K.multiply(H))).multiply(P_predicted);

        // Convert position back to lat/lon
        int componentDim = x_prev.getComponentDimension();
        ComponentState new_xLatLon = toComponentWithLatLon(new ComponentState(Xn, componentDim));

        return new KalmanFilterOutput(new_xLatLon, Pn, Y_hat);
    }


    /**********************************************************************************************
     *****************************  Getters and Setters below *************************************
     **********************************************************************************************/
    public ComponentState getPredictedState(ComponentState kfs, UUVReading kfr) {
        // convert actuator measurements to velocity and acceleration
        RealVector X = kfs.getCombinedState();
        RealVector Un = kfr.convertToKinematics(X);

        // prediction step takes into account X and X_extra
        RealVector X_predicted = A.operate(X).add(B.operate(Un));
        return new ComponentState(X_predicted, kfs.getComponentDimension());
    }

    public void updateControlInputModel(KalmanFilterActuatorWeights multipliers){
        if(this.B.getColumnDimension() != multipliers.getDimension())
            throw new IllegalArgumentException("multipliers size: " + multipliers.getDimension()
                    + "does not match B column dim: " + B.getColumnDimension());
        this.B = createControlInputModel(multipliers, samplingPeriod);
    }

    public void updateProcessNoise(RealVector noises){
        this.Q = computeIdealProcessNoise(noises, noises.getDimension());
    }

    public void updateMeasurementNoise(RealVector noises){
        this.R = computeIdealMeasurementNoise(noises, noises.getDimension());
    }

    public void updateStateTransitionModel(RealMatrix A){
        this.A = A;
    }

    public long getSamplingPeriod() {
        return this.samplingPeriod;
    }
    public RealMatrix getTransitionMatrix() {
        return this.A;
    }
    public String toString() {
        return "Kalman Filter";
    }

    /**
     * Converts vector in cartesian meters/second to polar radians/second
     * @return RealVector
     */
    private ComponentState toComponentWithXY(ComponentState stateWithLatLon){
        double lat = stateWithLatLon.getStateComponents().getEntry(0);
        double lon = stateWithLatLon.getStateComponents().getEntry(1);
        RealVector newStateComponent =  new ArrayRealVector(llc.getXY(lat, lon));
        return new ComponentState(newStateComponent, stateWithLatLon.getDeltaComponents());
    }

    private ComponentState toComponentWithLatLon(ComponentState stateWithXY){
        double easting = stateWithXY.getStateComponents().getEntry(0);
        double northing = stateWithXY.getStateComponents().getEntry(1);
        RealVector newStateComponent =  new ArrayRealVector(llc.getLatLon(northing, easting));
        return new ComponentState(newStateComponent, stateWithXY.getDeltaComponents());
    }
}
