package com.cra.princess.elements

import org.scalatest.FlatSpec
import org.scalatest.Matchers
import org.apache.commons.math3.linear.MatrixUtils
import org.apache.commons.math3.linear.Array2DRowRealMatrix

/**
 * Verifies that the Wishart element 
 * returns correct density estimates and valid samples
 */
class WishartDistributionTest extends FlatSpec with Matchers {
  
  "A WishartDistribution" should "correctly compute density of matrices" in {
    
    var distr = WishartDistribution(2, MatrixUtils.createRealIdentityMatrix(2))
    distr.density(MatrixUtils.createRealIdentityMatrix(2)) should be(0.02927492 +- 1e-5)
    
    distr = WishartDistribution(5, MatrixUtils.createRealDiagonalMatrix(Array(1.5, 2.5)))
    distr.density(new Array2DRowRealMatrix(Array(Array(3.0, 1.0), Array(1.0, 4.0)))) should be(0.0008855709 +- 1e-5)
  }
  
  it should "generate valid samples" in {
    var distr = WishartDistribution(5, MatrixUtils.createRealDiagonalMatrix(Array(1.5, 2.5)))
    val randomness = distr.generateRandomness()
    // verify lower triangular
    randomness.getEntry(0, 1) should equal(0)
    
    val variate = distr.generateValue(randomness)
    MatrixUtils.checkSymmetric(variate, 1e-5)
  }
    
}