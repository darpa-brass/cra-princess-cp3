package com.cra.princess.models;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

public class Transformed4DSingleFunctionKF {
  private RealMatrix A;

  private RealMatrix B;

  private RealMatrix H;

  private RealMatrix Q;

  private RealMatrix R;

  public Transformed4DSingleFunctionKF(){
    this.A = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 , 0 , 0 } , new double[]{ 0 , 1 , 0 , 0 } , new double[]{ 0 , 0 , 1 , 0 } , new double[]{ 0 , 0 , 0 , 1 } });
    this.B = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 , 0 , 0 } , new double[]{ 0 , 1 , 0 , 0 } , new double[]{ 0 , 0 , 1 , 0 } , new double[]{ 0 , 0 , 0 , 1 } });
    this.H = new Array2DRowRealMatrix(new double[][]{ new double[]{ 0 , 0 } , new double[]{ 0 , 0 } , new double[]{ 1 , 0 } , new double[]{ 0 , 1 } });
    this.Q = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 , 0 , 0 } , new double[]{ 0 , 1 , 0 , 0 } , new double[]{ 0 , 0 , 1 , 0 } , new double[]{ 0 , 0 , 0 , 1 } });
    this.R = new Array2DRowRealMatrix(new double[][]{ new double[]{ 1 , 0 , 0 , 0 } , new double[]{ 0 , 1 , 0 , 0 } , new double[]{ 0 , 0 , 1 , 0 } , new double[]{ 0 , 0 , 0 , 1 } });
  }

  private static RealMatrix SetMatrixEntries(long samplingPeriod, int dim) {
    RealMatrix m = MatrixUtils.createRealIdentityMatrix(dim);
    for (int i = 0; i < dim; i++)
      m.setEntry(i, i, samplingPeriod);

    return m;
  }

  public Object[] autoTransformedrunAlgorithm(RealVector xPrev, RealVector Zn, RealVector Un, RealMatrix P_prev,  double ctrlVar0,  double ctrlVar1,  double ctrlVar2,  double ctrlVar3,  double ctrlVar4,  double ctrlVar5,  double ctrlVar6,  double ctrlVar7,  double ctrlVar8,  double ctrlVar9,  double ctrlVar10,  double ctrlVar11,  double ctrlVar12,  double ctrlVar13,  double ctrlVar14,  double ctrlVar15,  double ctrlVar16,  double ctrlVar17,  double ctrlVar18,  double ctrlVar19,  double ctrlVar20,  double ctrlVar21,  double ctrlVar22,  double ctrlVar23,  double ctrlVar24,  double ctrlVar25,  double ctrlVar26,  double ctrlVar27,  double ctrlVar28,  double ctrlVar29,  double ctrlVar30,  double ctrlVar31,  double ctrlVar32,  double ctrlVar33,  double ctrlVar34,  double ctrlVar35,  double ctrlVar36,  double ctrlVar37,  double ctrlVar38,  double ctrlVar39,  double ctrlVar40,  double ctrlVar41,  double ctrlVar42,  double ctrlVar43,  double ctrlVar44,  double ctrlVar45,  double ctrlVar46,  double ctrlVar47,  double ctrlVar48,  double ctrlVar49,  double ctrlVar50,  double ctrlVar51,  double ctrlVar52,  double ctrlVar53,  double ctrlVar54,  double ctrlVar55,  double ctrlVar56,  double ctrlVar57,  double ctrlVar58,  double ctrlVar59,  double ctrlVar60,  double ctrlVar61,  double ctrlVar62,  double ctrlVar63,  double ctrlVar64,  double ctrlVar65,  double ctrlVar66,  double ctrlVar67,  double ctrlVar68,  double ctrlVar69,  double ctrlVar70,  double ctrlVar71) {
    this.R = new Array2DRowRealMatrix(new double[][]{ new double[]{ ctrlVar56 , ctrlVar57 , ctrlVar58 , ctrlVar59 } , new double[]{ ctrlVar60 , ctrlVar61 , ctrlVar62 , ctrlVar63 } , new double[]{ ctrlVar64 , ctrlVar65 , ctrlVar66 , ctrlVar67 } , new double[]{ ctrlVar68 , ctrlVar69 , ctrlVar70 , ctrlVar71 } });
    this.Q = new Array2DRowRealMatrix(new double[][]{ new double[]{ ctrlVar40 , ctrlVar41 , ctrlVar42 , ctrlVar43 } , new double[]{ ctrlVar44 , ctrlVar45 , ctrlVar46 , ctrlVar47 } , new double[]{ ctrlVar48 , ctrlVar49 , ctrlVar50 , ctrlVar51 } , new double[]{ ctrlVar52 , ctrlVar53 , ctrlVar54 , ctrlVar55 } });
    this.H = new Array2DRowRealMatrix(new double[][]{ new double[]{ ctrlVar32 , ctrlVar33 } , new double[]{ ctrlVar34 , ctrlVar35 } , new double[]{ ctrlVar36 , ctrlVar37 } , new double[]{ ctrlVar38 , ctrlVar39 } });
    this.B = new Array2DRowRealMatrix(new double[][]{ new double[]{ ctrlVar16 , ctrlVar17 , ctrlVar18 , ctrlVar19 } , new double[]{ ctrlVar20 , ctrlVar21 , ctrlVar22 , ctrlVar23 } , new double[]{ ctrlVar24 , ctrlVar25 , ctrlVar26 , ctrlVar27 } , new double[]{ ctrlVar28 , ctrlVar29 , ctrlVar30 , ctrlVar31 } });
    this.A = new Array2DRowRealMatrix(new double[][]{ new double[]{ ctrlVar0 , ctrlVar1 , ctrlVar2 , ctrlVar3 } , new double[]{ ctrlVar4 , ctrlVar5 , ctrlVar6 , ctrlVar7 } , new double[]{ ctrlVar8 , ctrlVar9 , ctrlVar10 , ctrlVar11 } , new double[]{ ctrlVar12 , ctrlVar13 , ctrlVar14 , ctrlVar15 } });
    if ((Zn.getDimension()) != (this.H.getRowDimension()))
      throw new IllegalArgumentException(String.format(("H row dimension is %s but sensorReading " + "vector dimension is %s "), H.getRowDimension(), Zn.getDimension()));

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

