package com.cra.princess.elements

import org.apache.commons.math3.linear._
import com.cra.figaro.util._
import org.apache.commons.math3.analysis._
import com.cra.figaro.language._
import com.cra.figaro.library.atomic.continuous._
import org.apache.commons.math3.analysis.function.Power

import scala.collection.JavaConverters._
import java.util.Arrays

import com.cra.princess.componentmodel._
import com.cra.princess.util.{Logs, MatrixHelper}
import org.apache.commons.math3.stat.StatUtils

import scala.collection.mutable.ListBuffer

/**
 * Estimates and performs posterior prediction from a Gaussian process.
  *
  * @param covarianceFunction Defines the inner product between feature vectors
  * @param noiseVariance Prior variance of noise at design points
  * @param regressorSubsetFraction A fraction of the training points to use when approximating the full GP covariance.
  *                                    Null value indicates that no approximation will be employed.
  *                                    See http://www.gaussianprocess.org/gpml/chapters/RW.pdf, sec 8.3
 */
class GaussianProcess[Input](var covarianceFunction: CovarianceFunction[Input] = null,
                             var meanFunction:Input => Double = null, noiseVariance: Double = 0.001,
                             var regressorSubsetFraction:Option[Double] = None)
    extends TrainableModel[Input, Double] with Logs {

  private var responseDeviation: Double = 0
  private var covarianceInverse: RealMatrix = null
  private var covarianceDecomp: LUDecomposition = null

  private var inputs: Seq[Input] = null
  private var alpha: RealMatrix = null
  private var rawResponses: Array[Double] = null
  private var responses: Array[Double] = null

  /** Landmark points used in subset of regressor approximation */
  private var landmarks:Seq[Int] = null
  /** L x N matrix, where L is the number of landmark points and N is the number of points */
  private var landmarkFullCov:RealMatrix = null
  /** L x L covariance matrix */
  private var landmarkLandmarkCov:RealMatrix = null

  /**
   * Estimate the conditional density of a new point.
   *
   * @param newInput The point to evaluate at
   * @return An element representing the posterior predictive distribution given the new point
   */
  def model(newInput: Input): Element[Double] = {
    if (covarianceInverse == null) {
      throw new IllegalArgumentException("The Gaussian process must be fit or provided with the inverse of the covariance matrix")
    }

    var newCovariance:RealMatrix = null
    if(regressorSubsetFraction.isDefined) {
      newCovariance = MatrixUtils.createColumnRealMatrix(landmarks.map(l => covarianceFunction(inputs(l), newInput)).toArray)
    } else {
      newCovariance = MatrixUtils.createColumnRealMatrix(inputs.map(i => covarianceFunction(i, newInput)).toArray)
    }
    var variance = (covarianceFunction(newInput, newInput) + noiseVariance) -
        newCovariance.transpose().multiply(covarianceInverse).multiply(newCovariance).getEntry(0, 0)
    val mean = alpha.preMultiply(newCovariance.transpose()).getEntry(0, 0)

    if (Math.abs(variance) < 1e-10) {
      variance = 0
    }

    Normal(meanFunction(newInput) + mean * responseDeviation, variance * math.pow(responseDeviation, 2))
  }

  /**
    * Train a GP with the same covariance matrix as a previously trained GP.
    * This saves an expensive matrix inversion if using the same inputs to independently model multiple outputs.
    */
  def trainWithSameCovariance(data: List[(Input, Double)], gp:GaussianProcess[Input]) = {
    covarianceInverse = gp.covarianceInverse
    landmarks = gp.landmarks
    landmarkFullCov = gp.landmarkFullCov
    landmarkLandmarkCov = gp.landmarkLandmarkCov

    train(data)
  }

  /**
   * Estimates the parameters of the Gaussian process (the inverse of the covariance matrix) from data
    * @param data A sequence of input, output pairs to use when fitting the model
   */
  def train(data: List[(Input, Double)]) = {
    inputs = data map { _._1 }
    rawResponses = data map { _._2 } toArray
    val rawMean = StatUtils.mean(rawResponses)
    responseDeviation = math.sqrt(StatUtils.variance(rawResponses))

    if(meanFunction == null) {
      meanFunction = (i:Input) => rawMean
    }

    // standardize responses
    responses = data.map(v => (v._2 - meanFunction(v._1)) / responseDeviation).toArray

    if(regressorSubsetFraction.isDefined)
      trainSubsetOfRegressors()
    else
      trainFull()
  }

  /** Train the GP using the complete data covariance matrix */
  def trainFull() = {
    // the user can set an inverse covariance matrix before calling train
    if (covarianceInverse == null) {
      val covariance = covarianceFunction.outer(inputs, inputs)

      log.trace("Inverting " + covariance.getColumnDimension + " x " + covariance.getRowDimension  + " covariance matrix")
      covarianceDecomp = new LUDecomposition(covariance
        .add(MatrixUtils.createRealIdentityMatrix(covariance.getRowDimension).scalarMultiply(noiseVariance)))
      covarianceInverse = covarianceDecomp.getSolver.getInverse
    }

    alpha = covarianceInverse.multiply(new Array2DRowRealMatrix(responses))
  }

  /** Train the GP using the 'subset of regressions' approximation, using a smaller set of landmark points.
    * This is faster but less accurate, and likelihood calculation can't be performed in the low-dimensional representation. */
  def trainSubsetOfRegressors() = {
    if(covarianceInverse == null) {
      val nlandmarks = (inputs.length * regressorSubsetFraction.get).toInt
      landmarks = com.cra.figaro.util.random.shuffle[Int, IndexedSeq](0 until inputs.length).take(nlandmarks).toList.sorted
      landmarkFullCov = MatrixUtils.createRealMatrix(nlandmarks, inputs.length)
      landmarkLandmarkCov = MatrixUtils.createRealMatrix(nlandmarks, nlandmarks)

      landmarkFullCov = covarianceFunction.outer(landmarks.map(inputs(_)), inputs)

      (0 until nlandmarks).foreach(l1 => {
        landmarkLandmarkCov.setColumn(l1, landmarkFullCov.getColumn(landmarks(l1)))
      })

      log.trace("Inverting " + nlandmarks + " x " + nlandmarks + " covariance matrix")
      covarianceInverse = MatrixUtils.inverse(landmarkFullCov.multiply(landmarkFullCov.transpose())
        .add(landmarkLandmarkCov.scalarMultiply(noiseVariance)))
    }
    alpha = covarianceInverse.multiply(landmarkFullCov).multiply(new Array2DRowRealMatrix(responses))
  }

  /** Computes the log-likelihood of the inverse covariance */
  def covarianceLikelihood():Double = {
    if(regressorSubsetFraction.isDefined)
      throw new IllegalArgumentException("Likelihood calculation not supported for subset-of-regressors GP")
    if(covarianceInverse == null)
      throw new IllegalArgumentException("GP must be fit before covariance likelihood is available")

    val logCovarianceDet = MatrixHelper.getLogDeterminant(covarianceDecomp)
    val responseMat = MatrixUtils.createColumnRealMatrix(responses)

    (-1/2.0 * logCovarianceDet
      - 1/2.0 * responseMat.transpose().multiply(covarianceInverse).multiply(responseMat).getEntry(0, 0)
      - inputs.length / 2.0 * math.log(2 * math.Pi))
  }

  /** Computes the log-likelihood of the mean function.
    * @param residuals Residuals arising from
    */
  def marginalMeanLikelihood(residuals:RealMatrix):Double = {
    if(regressorSubsetFraction.isDefined)
      throw new IllegalArgumentException("Likelihood calculation not supported for subset-of-regressors GP")
    - 1.0 * covarianceInverse.preMultiply(residuals.transpose()).multiply(residuals).getEntry(0, 0)
  }

  /** Computes the gradient of the mean function log-likelihood */
  def marginalMeanLikelihoodGradient(residuals:RealMatrix):RealMatrix = {
    if(regressorSubsetFraction.isDefined)
      throw new IllegalArgumentException("Likelihood calculation not supported for subset-of-regressors GP")
    residuals.transpose().multiply(covarianceInverse).scalarMultiply(-1.0)
  }

  /**
    * Replaces the mean function and other internal objects that depend on that function.
    * This should only be called after training.
    */
  def updateMeanFunction(meanFun:Function1[Input, Double]) = {
    meanFunction = meanFun
    responses = (0 until inputs.length).map(i => (rawResponses(i) - meanFunction(inputs(i))) / responseDeviation).toArray
    if(regressorSubsetFraction.isDefined)
      alpha = covarianceInverse.multiply(landmarkFullCov).multiply(new Array2DRowRealMatrix(responses))
    else
      alpha = covarianceInverse.multiply(new Array2DRowRealMatrix(responses))
  }

}