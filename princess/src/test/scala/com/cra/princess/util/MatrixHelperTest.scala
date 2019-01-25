package com.cra.princess.util

import org.apache.commons.math3.linear.{Array2DRowRealMatrix, LUDecomposition}
import org.scalatest.{FlatSpec, Matchers}

class MatrixHelperTest extends FlatSpec with Matchers {

    "MatrixHelper" should "accurately compute log-determinants" in {
      val covariance = new Array2DRowRealMatrix(Array(
        Array(1.0, 0.36787944, 0.36787944),
        Array(0.36787944, 1.0, 0.0183156),
        Array(0.36787944, 0.01831564, 1)
      ))
      val logCovarianceDeterminant = math.log(0.7339515)

      MatrixHelper.getLogDeterminant(new LUDecomposition(covariance)) should be(logCovarianceDeterminant +- 1e-5)
    }

}
