package com.cra.princess.models;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

public class TransformedSingleFunctionKalmanFilter {
    private RealMatrix A;

    private RealMatrix B;

    private RealMatrix H;

    private RealMatrix Q;

    private RealMatrix R;

    public TransformedSingleFunctionKalmanFilter() {
      this.A = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
      this.B = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
      this.H = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
      this.Q = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
      this.R = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
    }

  public Object[] autoTransformedrunAlgorithm(RealVector xPrev, RealVector Zn, RealVector Un, RealMatrix P_prev,
                                              double ctrlVar0,  double ctrlVar1,  double ctrlVar2,  double ctrlVar3,
                                              double ctrlVar4,  double ctrlVar5,  double ctrlVar6,  double ctrlVar7,
                                              double ctrlVar8,  double ctrlVar9,  double ctrlVar10,  double ctrlVar11,
                                              double ctrlVar12,  double ctrlVar13,  double ctrlVar14,  double ctrlVar15,
                                              double ctrlVar16,  double ctrlVar17,  double ctrlVar18,  double ctrlVar19) {
      this.R = new Array2DRowRealMatrix(new double[][]{
              new double[]{ ctrlVar16 , ctrlVar17 } ,
              new double[]{ ctrlVar18 , ctrlVar19 } });
      this.Q = new Array2DRowRealMatrix(new double[][]{
              new double[]{ ctrlVar12 , ctrlVar13 } ,
              new double[]{ ctrlVar14 , ctrlVar15 } });
      this.H = new Array2DRowRealMatrix(new double[][]{
              new double[]{ ctrlVar8 , ctrlVar9 } ,
              new double[]{ ctrlVar10 , ctrlVar11 } });
      this.B = new Array2DRowRealMatrix(new double[][]{
              new double[]{ ctrlVar4 , ctrlVar5 } ,
              new double[]{ ctrlVar6 , ctrlVar7 } });
      this.A = new Array2DRowRealMatrix(new double[][]{
              new double[]{ ctrlVar0 , ctrlVar1 } ,
              new double[]{ ctrlVar2 , ctrlVar3 } });
      if ((Zn.getDimension()) != (this.H.getRowDimension()))
        throw new IllegalArgumentException(String.format(("H row dimension is %s but sensorReading "
                + "vector dimension is %s "), H.getRowDimension(), Zn.getDimension()));

      RealVector X_predicted = A.operate(xPrev).add(B.operate(Un));
      RealMatrix P_predicted = A.multiply(P_prev).multiply(A.transpose()).add(Q);
      RealVector Y_hat = Zn.subtract(H.operate(X_predicted));
      RealMatrix S = H.multiply(P_predicted).multiply(H.transpose()).add(R);
      RealMatrix K = P_predicted.multiply(H.transpose()).multiply(MatrixUtils.inverse(S));
      RealVector xNext = X_predicted.add(K.operate(Y_hat));
      RealMatrix I = MatrixUtils.createRealIdentityMatrix(H.getColumnDimension());
      RealMatrix pNext = I.subtract(K.multiply(H)).multiply(P_predicted);
      return new Object[]{ xNext , pNext , Y_hat };
    }
}
