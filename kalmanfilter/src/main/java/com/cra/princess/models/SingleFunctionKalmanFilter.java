package com.cra.princess.models;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

public class SingleFunctionKalmanFilter {

  private RealMatrix A, B, H, Q, R;

  public SingleFunctionKalmanFilter(){
    this.A = new Array2DRowRealMatrix(new double[][] {
            { 1, 0 },
            { 0, 1 }});
    this.B = new Array2DRowRealMatrix(new double[][] {
            { 1, 0 },
            { 0, 1 }});
    this.H = new Array2DRowRealMatrix(new double[][] {
            { 1, 0 },
            { 0, 1 }});
    this.Q = new Array2DRowRealMatrix(new double[][] {
            { 1, 0 },
            { 0, 1 }});
    this.R = new Array2DRowRealMatrix(new double[][] {
            { 1, 0 },
            { 0, 1 }});
  }

  private static RealMatrix SetMatrixEntries(long samplingPeriod, int dim) {
    RealMatrix m = MatrixUtils.createRealIdentityMatrix(dim);
    // delta units are in seconds, samplingPeriod is in ms
    for (int i = 0; i < dim; i++)
      m.setEntry(i, i, samplingPeriod);
    return m;
  }

  public Object[] runAlgorithm(RealVector xPrev,
                               RealVector Zn, RealVector Un, RealMatrix P_prev) {

    if (Zn.getDimension() != this.H.getRowDimension())
      throw new IllegalArgumentException(String.format("H row dimension is %s but sensorReading "
              + "vector dimension is %s ", H.getRowDimension(), Zn.getDimension()));

    RealVector X_predicted = A.operate(xPrev).add(B.operate(Un));
    RealMatrix P_predicted = A.multiply(P_prev).multiply(A.transpose()).add(Q);

    // correction step, H converts from estimation space to sensorMeasurement space
    RealVector Y_hat = Zn.subtract(H.operate(X_predicted)); // the residual
    RealMatrix S = (H.multiply(P_predicted).multiply(H.transpose())).add(R);

    // H-transpose and K converts from sensorMeasurement space back to estimation space
    RealMatrix K = P_predicted.multiply(H.transpose()).multiply(MatrixUtils.inverse(S));
    RealVector xNext = X_predicted.add(K.operate(Y_hat));
    RealMatrix I = MatrixUtils.createRealIdentityMatrix(H.getColumnDimension());
    RealMatrix pNext = (I.subtract(K.multiply(H))).multiply(P_predicted);

    return new Object[]{xNext, pNext, Y_hat};
  }
}
