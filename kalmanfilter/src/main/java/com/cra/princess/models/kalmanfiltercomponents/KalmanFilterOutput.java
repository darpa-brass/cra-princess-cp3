package com.cra.princess.models.kalmanfiltercomponents;
import com.cra.princess.localizationalgorithm.components.ComponentState;
import com.cra.princess.localizationalgorithm.components.LocalizationOutput;
import com.cra.princess.utility.math.Ellipsoid;
import org.apache.commons.math3.linear.EigenDecomposition;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

/**
 * Wrapper for Kalman Filter output variables<p>
 * Contains: <br>
 * <b>state</b> - the predicted state of each variable in the machine<br>
 * <b>covariance</b> - covariance matrix denoting uncertainty of prediction <br>
 * <b>errorVolume</b> - Change in errorVolume over time
 */
public class KalmanFilterOutput implements LocalizationOutput{
    private RealMatrix covariance;
    private RealVector measurementResidual;
    private ComponentState state;

    public KalmanFilterOutput(ComponentState state, RealMatrix covariance, RealVector measurementResidual){
        this.covariance = covariance;
        this.state = state;
        this.measurementResidual = measurementResidual;
    }
    public RealMatrix getCovariance() {
        return covariance;
    }
    public ComponentState getState() {
        return state;
    }
    public double getErrorVolume() {return computeVolume(covariance);}
    private double computeVolume(RealMatrix m) {
        EigenDecomposition e = new EigenDecomposition(m);
        Ellipsoid ellipse = new Ellipsoid(e.getRealEigenvalues());
        return ellipse.getVolume();
    }
    public RealVector getMeasurementResidual() {
        return measurementResidual;
    }

    public void setMeasurementResidual(RealVector measurementResidual) {
        this.measurementResidual = measurementResidual;
    }
}