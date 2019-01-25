package com.cra.princess.componentmodel

import com.cra.princess._
import com.cra.princess.core.PrincessFeature
import com.cra.princess.elements.GaussianProcess
import com.cra.princess.util.{KdTree, PrincessTypeUtility, UnitFeatureScaler}
import org.apache.commons.math3.linear.{Array2DRowRealMatrix, ArrayRealVector, MatrixUtils, RealMatrix}
import org.apache.commons.math3.ml.clustering.{Clusterable, KMeansPlusPlusClusterer}
import org.apache.commons.math3.stat.StatUtils

import scala.collection.JavaConverters._

/** A mean function with parameters that can be optimized with a gradient on the likelihood */
trait GradientOptimizableMeanFunction[Env, Input] {
  /** Parameters at which to start the optimization process*/
  def initialParameters():Array[Double]
  /** Computes gradient of the likelihood function at a specific assignment to parameters*/
  def likelihoodGradient(params:Array[Double]):Array[Double]
  /** Calculates likelihood at a specific assignment to parameters*/
  def likelihood(params:Array[Double]):Double
  /** Produces a deterministic mean function at a specified parameter assignment*/
  def responseMeanFun(params:Seq[Double]):Function1[(Env, Input, ComponentControls), Double]
}

/** A mean function where the parameters have a finite domain, which is exhaustively optimized */
trait FiniteOptimizableMeanFunction[Env, Input] {
  /** Sequence of all possible parameter assignments */
  def parameterSpace():Array[Array[Double]]
  /** Computes likelihood at a prospective parameter assignment */
  def likelihood(params:Array[Double]):Double
  /** Produces a deterministic mean function at a specified parameter assignment*/
  def responseMeanFun(params:Seq[Double]):Function1[(Env, Input, ComponentControls), Double]
}

/**
  * A mean function which just returns the median metric
  */
class FixedMeanFunction[Env, Input](val metrics:Seq[Double]) {
  val sortedMetrics = metrics.sorted.toList
  val metricMedian = sortedMetrics((metrics.length / 2.0).toInt)

  def value(v:(Env, Input, ComponentControls)):Double = metricMedian
}

/** Wrapper for point to cluster */
class ClusteringPoint(point:Array[Double], val metricValue:Double, val index:Int) extends Clusterable {
  override def getPoint: Array[Double] = point
}

/**
  * A mean function which returns the mean of the centroid of the cluster a point belongs to
  */
class ClusteringMeanFunction[Env <: PrincessFeature, Input <: PrincessFeature](val inputs:Seq[(Env, Input, ComponentControls)],
                                         val gp:GaussianProcess[(Env, Input, ComponentControls)],
                                         val metrics:Seq[Double]) extends FiniteOptimizableMeanFunction[Env, Input] {

  val flatInputs = inputs.map(PrincessTypeUtility.flatten(_))
  val scaler = new UnitFeatureScaler(flatInputs)
  val scaledInputs = scaler.scaleAll(flatInputs)
  val clusteringInputs = (0 until inputs.length).map(i => new ClusteringPoint(scaledInputs(i).toArray, metrics(i), i))

  // a map from # of clusters to the centers and metric values in that clustering
  val clustersByCount = scala.collection.mutable.Map[Int, List[(Array[Double], Double)]]()

  /** Returns the parameter space for the clustering function, which is a finite set of k-values for k-means */
  override def parameterSpace() = {
    // make sure we're not requesting more clusters than data points
    Array(1.0, 2, 5, 10, 20, 50).filter(v => v < scaledInputs.length).map(v => Array(v))
  }

  /** Produces a piecewise constant mean function guided by the cluster assignments */
  override def responseMeanFun(params: Seq[Double]): ((Env, Input, ComponentControls)) => Double = {
    val nclusters = params(0).toInt
    (v:(Env, Input, ComponentControls)) => {
      // find closest cluster
      val point = scaler.scale(PrincessTypeUtility.flatten(v)).toArray
      val closestCluster = clustersByCount(nclusters).min(Ordering.by[(Array[Double], Double), Double](cl => DistanceUtil.distance(cl._1, point)))
      closestCluster._2
    }
  }

  /**
    * Performs a clustering at the specified k. Evaluates residuals on this mean function, then
    * uses those residuals to compute likelihood of the GP mean.
    * Finally, applies BIC penalization to that likelihood.
    */
  override def likelihood(params: Array[Double]): Double = {
    val nclusters = params(0).toInt
    // cluster at these parameters, no more than 100 iterations
    val clusterer = new KMeansPlusPlusClusterer[ClusteringPoint](nclusters, 100)
    val clusters = clusterer.cluster(clusteringInputs.asJava)

    val indexedPoints = (0 until nclusters).flatMap(c => {
      val points = clusters.get(c).getPoints().asScala
      val meanMetric = StatUtils.mean(points.map(p => p.metricValue).toArray)
      points.map(p => (p.metricValue, meanMetric, p.index))
    }).sortBy(p => p._3)

    val residuals = MatrixUtils.createColumnRealMatrix(indexedPoints.map(p => p._1 - p._2).toArray)
    val clusterInfo = (0 until nclusters).map(c =>
      (clusters.get(c).getCenter.getPoint, StatUtils.mean(clusters.get(c).getPoints.asScala.map(p => p.metricValue).toArray)))
    clustersByCount += nclusters -> clusterInfo.toList
    2 * gp.marginalMeanLikelihood(residuals) - nclusters * scaledInputs(0).length * Math.log(scaledInputs.length)
  }
}

/**
  * A mean function that selects the metric of the closest point in the training data.
  */
class NearestNeighborMeanFunction[Env <: PrincessFeature, Input <: PrincessFeature]
  (val inputs:Seq[(Env, Input, ComponentControls)],
    val gp:GaussianProcess[(Env, Input, ComponentControls)],
    val metrics:Seq[Metric]) extends FiniteOptimizableMeanFunction[Env, Input] {
  val flatInputs = inputs.map(PrincessTypeUtility.flatten(_))
  val scaler = new UnitFeatureScaler(flatInputs)
  val scaledInputs = scaler.scaleAll(flatInputs)

  val tree = new KdTree.SqrEuclid[Metric](scaledInputs(0).length, scaledInputs.length + 1)
  for(i <- 0 until scaledInputs.length) {
    tree.addPoint(scaledInputs(i).toArray, metrics(i))
  }

  override def parameterSpace(): Array[Array[Double]] = {
    Array(Array(1.0), Array(2.0), Array(3.0), Array(5.0), Array(10.0))
  }

  override def responseMeanFun(params: Seq[Double]): ((Env, Input, ComponentControls)) => Double = {
    val nneighbors = params.head.toInt
    (v:(Env, Input, ComponentControls)) => {
      val point = scaler.scale(PrincessTypeUtility.flatten(v)).toArray
      StatUtils.mean(tree.nearestNeighbor(point, nneighbors, false).asScala.map(n => n.value).toArray)
    }
  }

  /**
    * Looks up the k nearest neighbors in the KD tree, uses those to compute residuals,
    * and calculates the GP likelihood from those residuals.
    */
  override def likelihood(params: Array[Double]): Double = {
    val nneighbors = params.head.toInt
    // get one extra neighbor because the first will by myself
    val estMeans = scaledInputs.map(i => StatUtils.mean(tree.nearestNeighbor(i.toArray, nneighbors+1, false).asScala
          .sortBy(e => e.distance).drop(1).map(n => n.value).toArray))
    val residuals = MatrixUtils.createColumnRealMatrix(metrics.zip(estMeans).map(mm => mm._1 - mm._2).toArray)
    gp.marginalMeanLikelihood(residuals)
  }
}

/**
  * Provides facilities to optimize parameters of a mean function based on control variables.
  * The mean function takes the form a_1(x_1 + b_1)^2 + a_2(x_2 + b_2)^2 + ... + a_n(x_n + b_n)^2 + c
  * where each x_i is a control variable.
  **/
class OptimizableParabolicMeanFunction[Env, Input](val controls:Seq[ComponentControls],
                                           val gp:GaussianProcess[(Env, Input, ComponentControls)],
                                           val metrics:Seq[Double]) extends GradientOptimizableMeanFunction[Env, Input] {
  val flatControls = controls.map(i => PrincessTypeUtility.flatten(i).toArray)
  val nflatcontrols = flatControls(0).length

  /**
    * Initial parameters for this mean function yield c=mean(response), a_i=0.
    * As a result, the final model won't be less accurate than just using a zero-mean GP.
    */
  def initialParameters() = {
    val metricMean = StatUtils.mean(metrics.toArray)
    val parameters:Array[Double] = Array.fill(nflatcontrols * 2 + 1)(0.0)
    parameters(nflatcontrols * 2) = metricMean
    parameters
  }

  /** Build a return a function of only control variables */
  def responseMeanFun(terms:Seq[Double]) = {
    val aterms = terms.take(nflatcontrols)
    val bterms = terms.drop(nflatcontrols).take(nflatcontrols)
    val c = terms(nflatcontrols * 2)

    (v:Tuple3[Env, Input, ComponentControls]) => {
      val curControls = PrincessTypeUtility.flatten(v._3).toArray
      responseForControls(aterms, bterms, c, curControls)
    }
  }

  def responseForControls(aterms:Seq[Double], bterms:Seq[Double], c:Double, controls:Seq[Double]) =
    (0 until nflatcontrols).map(ci => aterms(ci) * math.pow(controls(ci) + bterms(ci), 2)).sum + c

  /**
    * Evaluate the gradient of the likelihood wrt the parameters.
    * The gradient of this function wrt a_i is x_i^2 + 2xb + b^2.
    * The gradient of this function wrt b_i is 2ax + 2ab.
    * The gradient of this function wrt c is 1.
    */
  def likelihoodGradient(params:Array[Double]):Array[Double] = {
    val aterms = params.take(nflatcontrols)
    val bterms = params.drop(nflatcontrols).take(nflatcontrols)
    val c = params(nflatcontrols * 2)

    val means = flatControls.map(i => responseForControls(aterms, bterms, c, i))
    val residuals = MatrixUtils.createColumnRealMatrix((0 until metrics.length).map(i => metrics(i) - means(i)).toArray)

    // sum over data cases (flatControls)
    val agrad = new Array2DRowRealMatrix(flatControls.map(ctrl => (0 until nflatcontrols).map(i =>
      ctrl(i) * ctrl(i) + 2 * ctrl(i) * bterms(i) + bterms(i) * bterms(i)).toArray).toArray)
    val bgrad = new Array2DRowRealMatrix(flatControls.map(ctrl => (0 until nflatcontrols).map(i =>
      2 * aterms(i) * ctrl(i) + 2 * aterms(i) * bterms(i)).toArray).toArray)
    val cgrad = new Array2DRowRealMatrix(Array.fill(flatControls.length)(Array.fill(nflatcontrols)(1.0)))

    val term1 = gp.marginalMeanLikelihoodGradient(residuals)
    val lgrad = term1.multiply(agrad).getRow(0) ++ term1.multiply(bgrad).getRow(0) ++ term1.multiply(cgrad).getRow(0)
    lgrad
  }

  /**
    * Calculates residuals at the specified parameter assignments,
    * and uses those residuals to evaluate GP likelihood.
    * @param params The parameters for which to evaluate likelihood
    * @return
    */
  def likelihood(params:Array[Double]) = {
    val aterms = params.take(nflatcontrols)
    val bterms = params.drop(nflatcontrols).take(nflatcontrols)
    val c = params(nflatcontrols * 2)

    val means = flatControls.map(i => responseForControls(aterms, bterms, c, i))
    val residuals = MatrixUtils.createColumnRealMatrix((0 until metrics.length).map(i => metrics(i) - means(i)).toArray)
    gp.marginalMeanLikelihood(residuals)
  }
}

