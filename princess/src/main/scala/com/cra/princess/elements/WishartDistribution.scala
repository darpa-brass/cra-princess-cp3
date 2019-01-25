package com.cra.princess.elements

import com.cra.figaro.language._
import org.apache.commons.math3.linear._
import org.apache.commons.math3.distribution.ChiSquaredDistribution
import org.apache.commons.math3.distribution.NormalDistribution
import org.apache.commons.math3.special.Gamma

/**
 * Element representing distribution on real positive semi-definite matrices
 */
class WishartDistribution(name: Name[RealMatrix], val degreesOfFreedom:Int, val sigma:RealMatrix, collection: ElementCollection) 
  extends Element[RealMatrix](name, collection) with Atomic[RealMatrix] {
  
  if(sigma.getRowDimension != sigma.getColumnDimension) {
    throw new IllegalArgumentException("Scale matrix sigma must be square");
  }
  
  MatrixUtils.checkSymmetric(sigma, 1e-5)
  
  // cache inverse and determinant
  val sigmaLuDecomp = new LUDecomposition(sigma)
  private val sigmaInv = sigmaLuDecomp.getSolver.getInverse
  private val sigmaDet = sigmaLuDecomp.getDeterminant
  
  private val dim = sigma.getRowDimension
  
  private val rng = new ApacheRandomGeneratorWrapper(com.cra.figaro.util.random)
  
  // generating random samples using the Bartlett decomposition
  // randomness is a lower-diagonal matrix participating in this decomposition
  // see: http://www.jstor.org/stable/2346290?seq=1#page_scan_tab_contents
  type Randomness = RealMatrix
  
  // we need the cholesky factor of sigma to generate random variates
  private val cdecomp = new CholeskyDecomposition(sigma)
  private val choleskyFactor = cdecomp.getL
  private val densityDenom = Math.pow(2, degreesOfFreedom * dim / 2.0) * Math.pow(sigmaDet, degreesOfFreedom / 2.0) * multivariateGamma(degreesOfFreedom / 2.0)
  
  private def multivariateGamma(x:Double):Double = {
    Math.pow(Math.PI, dim * (dim - 1) / 4.0) * (1 to dim).map(i => Gamma.gamma(x + (1 - i) / 2.0)).foldLeft(1.0)((v1, v2) => v1 * v2)
  }
  
  def density(x: RealMatrix): Double = {
    val xDecomp = new LUDecomposition(x)
    val numerator = Math.pow(xDecomp.getDeterminant, (degreesOfFreedom - dim - 1) / 2.0) * Math.exp( - sigmaInv.multiply(x).getTrace / 2.0)
    numerator / densityDenom
  }

  def generateRandomness(): Randomness = {
    // diagonal is distributed as the square root of chi-squared variables
    val randomness = new Array2DRowRealMatrix(sigma.getRowDimension, sigma.getRowDimension)
    for(i <- 0 until sigma.getRowDimension) {
      val eltDistr = new ChiSquaredDistribution(rng, degreesOfFreedom - i + 2)
      randomness.setEntry(i, i, Math.sqrt(eltDistr.sample()))
    }
    
    // elements of lower triangle are distributed as standard normals 
    val standardNormal = new NormalDistribution(rng, 0, 1)
    for(i <- 1 until sigma.getRowDimension) {
      for(j <- 0 until i) {
        randomness.setEntry(i, j, standardNormal.sample())
      }
    }
    
    randomness
  }

  def generateValue(rand: Randomness): RealMatrix = {
    choleskyFactor.multiply(rand.multiply(rand.transpose()).multiply(choleskyFactor.transpose()))
  }
}

object WishartDistribution {
  def apply(degressOfFreedom:Int, sigma:RealMatrix)(implicit name:Name[RealMatrix], collection: ElementCollection) = 
    new WishartDistribution(name, degressOfFreedom, sigma, collection)
}