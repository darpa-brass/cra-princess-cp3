package com.cra.princess.componentmodel

import com.cra.princess.elements.ApacheRandomGeneratorWrapper
import org.apache.commons.math3.linear._
import org.apache.commons.math3.distribution.MultivariateNormalDistribution
import org.apache.commons.math3.stat.correlation.Covariance
import org.apache.commons.math3.exception.{MathUnsupportedOperationException, MaxCountExceededException}

import scala.collection.mutable.ListBuffer

/**
  * Performs density estimation using kernel functions to smooth density estimates around observed inputs.
  *
  * @param samples Sequence of instances, where each instance is a d-dimensional array
  * @param bandwidth Bandwidth matrix. If not supplied, we'll estimate this using an extension of Scott's rule.
  * @param skipDimensions Dimensions to exclude from the KDE. This can be helpful in ignoring constant dimensions
  * @author Dan Garant
  */
class MultivariateKernelDensityEstimator(samples: Seq[Array[Double]],
                                         var bandwidth:RealMatrix = null, val skipDimensions: Set[Int] = Set.empty) {
  
  val ndim = samples(0).length
  var nsamples = samples.length
  
  val transposed = (0 until ndim).map(i => samples.map(_(i)))
  val means = transposed.map(t => t.sum / nsamples)
  val stdDevs = (0 until ndim).map(i => if(skipDimensions.contains(i)) 0 else Math.sqrt(transposed(i).map(t => Math.pow(t - means(i), 2)).sum / (nsamples - 1)))
  
  // dropping dimensions with zero variance
  val zeroVarDimensions = (0 until stdDevs.length).filter(i => stdDevs(i) < 1e-10)
  val nonzeroVarDimensions = (0 until stdDevs.length).filter(i => !zeroVarDimensions.contains(i))
  val nonZeroDim = ndim - zeroVarDimensions.length
  
  private val rng = new ApacheRandomGeneratorWrapper(com.cra.figaro.util.random)

  if(bandwidth == null) {
    // generalization of Scott's rule, AMISE estimator would be a lot of work
    // from "Nonparametric and Semiparametric Models"
    val sampleCovariance = new Covariance(samples.map(s => nonzeroVarDimensions.map(d => s(d)).toArray).toArray).getCovarianceMatrix()

    // need to take square root of covariance matrix
    val decomposition = new SingularValueDecomposition(sampleCovariance)
    val diagMat = decomposition.getS
    (0 until diagMat.getRowDimension).foreach(r => diagMat.setEntry(r, r, Math.sqrt(diagMat.getEntry(r, r))))
    bandwidth = decomposition.getU.multiply(diagMat).multiply(decomposition.getVT)
      .scalarMultiply(Math.pow(nsamples, -1.0 / (nonZeroDim + 4))).scalarAdd(0.0)
  }
  
  // for Gaussian kernels, bandwidth is proportional to the std. dev of the KDE
  // this distribution represents the density centered at some sample point
  var pointMvn:MultivariateNormalDistribution = null
  try {
    pointMvn = new MultivariateNormalDistribution(rng, Array.fill(nonZeroDim)(0), bandwidth.getData)
  } catch {
    case ex @ (_: SingularMatrixException | _:MathUnsupportedOperationException | _:NonPositiveDefiniteMatrixException | _:MaxCountExceededException) => {
      System.err.println("Warning (MultivariateKernelDensityEstimator): Covariance is singular, falling back to diagonal bandwidth matrix")
      // fall back to Silverman's rule of thumb, with off diagonal elements set to zero
      bandwidth = MatrixUtils.createRealDiagonalMatrix(
        stdDevs.filter(s => s > 1e-10).map(sd => Math.pow(Math.pow(4.0 / (nonZeroDim + 2), 1.0 / (nonZeroDim + 4)) * Math.pow(nsamples, -1.0 / (nonZeroDim + 4)) * sd, 2)) toArray)
      pointMvn = new MultivariateNormalDistribution(rng, Array.fill(nonZeroDim)(0), bandwidth.getData)        
    }
  }

  val curSamples = ListBuffer[Array[Double]](samples:_*)
  val pointWeights = ListBuffer.fill(samples.length)(1.0)

  // generate a random index, respecting the point weights, using N exponential distributions
  private def randomIndex():Int = {
    val weights = pointWeights.map(w => -math.log(com.cra.figaro.util.random.nextDouble()) / w)
    (0 until pointWeights.length).min(Ordering.by[Int, Double](i => weights(i)))
  }

  def sample():Array[Double] = {
    val idx = randomIndex()
    val shift = pointMvn.sample()
    
    // shift the mean of pointMvn onto the sample at idx
    var mvnCtr = 0
    (0 until ndim).map(i => {
      var ret:Double = 0
      if(zeroVarDimensions.contains(i)) {
         ret = curSamples(0)(i)
      } else {
        ret = shift(mvnCtr) + curSamples(idx)(i)
        mvnCtr += 1
      }
      ret
    }) toArray
  }

  def addPoint(point:Array[Double], weight:Double=1) = {
    curSamples += point
    pointWeights += weight
  }

  def setWeights(weights:Array[Double]) = {
    (0 until weights.length).foreach(i => pointWeights(i) = weights(i))
  }

  def removePoint(pointIndex:Int) = {
    curSamples.remove(pointIndex)
    pointWeights.remove(pointIndex)
  }
  
  /** Computes the density of a new d-dimensional point */
  def density(point:Array[Double]):Double = {
    // TODO: n MVN density calculations is bad
    // better would be to index points based on a tree or something, and compute distance only within points in the leaf
    // one implementation of this idea can be found in:
    // https://github.com/scikit-learn/scikit-learn/blob/51a765acfa4c5d1ec05fc4b406968ad233c75162/sklearn/neighbors/binary_tree.pxi, function kernel_density
    // alternately, we can switch to the Epanechnikov kernel and use a KD tree like in KernelDensity

    val totalWeight = pointWeights.sum
    val densities = curSamples.map(sample => {
      val diff = nonzeroVarDimensions.map(i => sample(i) - point(i)).toArray
      val anyZeroVarNotEqual = zeroVarDimensions.exists(i => !sample(i).equals(point(i)))
      if(anyZeroVarNotEqual) 0 else pointMvn.density(diff)
    })
    
    densities.zip(pointWeights).map(v => v._1 * v._2).sum / totalWeight
  }
}