package com.cra.princess.testharness.example

import com.cra.figaro.library.atomic.continuous.Uniform
import com.cra.figaro.language._
import scala.collection.mutable.Map
import com.cra.figaro.library.compound.^^
import math.{ pow, log }
import JSci.maths.SpecialMath.{ beta, gamma, logGamma }
import com.cra.figaro.util._
import com.cra.figaro.algorithm.ProbQueryAlgorithm
import com.cra.figaro.library.atomic.discrete.FromRange
import com.cra.figaro.library.atomic.continuous.Beta
import com.cra.figaro.library.atomic.continuous.Normal

/**
 * Build a model of a clustering algorithm's metrics, assuming three control variables: number of clusters,
 * initialization method, maximum number of iterations. The class will create a probability
 * distribution for every combination of the control variables. (i.e., P(Purity, Runtime | clusters, init, iters))
 *
 * @param numClustersSupport lower and upper (inclusive) bounds of the number of clusters
 * @param initMethodSupport lower and upper (inclusive) bounds of the initialization method
 * @param maxItersSupport lower and upper (inclusive) bounds of the maximum number of iterations.
 */
class ClusterModel(numClustersSupport: (Int, Int), initMethodSupport: (Int, Int), maxItersSupport: (Int, Int)) {
  val universe = new Universe

  val numClusters = FromRange(numClustersSupport._1, numClustersSupport._2 + 1)("numClusters", universe)
  val initMethod = FromRange(initMethodSupport._1, initMethodSupport._2 + 1)("initMethod", universe)
  val maxIters = FromRange(maxItersSupport._1, maxItersSupport._2 + 1)("maxIters", universe)
  val controlTuple = ^^(numClusters, initMethod, maxIters)("", universe)

  // Purity
  def alphaPrior = Uniform(0.0, 1.0)("", universe)
  def betaPrior = Uniform(0.0, 1.0)("", universe)
  val purityPriors: Map[(Int, Int, Int), Element[(Double, Double)]] = Map()

  def makePurityPriors() = {
    for { c <- numClustersSupport._1 to numClustersSupport._2 } {
      for { i <- initMethodSupport._1 to initMethodSupport._2 } {
        for { m <- maxItersSupport._1 to maxItersSupport._2 } {
          purityPriors += (c, i, m) -> ^^(alphaPrior, betaPrior)("", universe)
        }
      }
    }
  }

  // Runtime
  val maxRuntime = 100.0
  val maxStdRange = 0.2
  def meanPrior = Uniform(0.0, maxRuntime)("", universe)
  def stdPrior = Uniform(1.0, maxRuntime * maxStdRange)("", universe)
  val runtimePriors: Map[(Int, Int, Int), Element[(Double, Double)]] = Map()

  def makeRuntimePriors() = {
    for { c <- numClustersSupport._1 to numClustersSupport._2 } {
      for { i <- initMethodSupport._1 to initMethodSupport._2 } {
        for { m <- maxItersSupport._1 to maxItersSupport._2 } {
          runtimePriors += (c, i, m) -> ^^(meanPrior, stdPrior)("", universe)
        }
      }
    }
  }

  /**
   * Make a Bayesian learning model from the priors and the data. Returns the universe of the model, and a map from
   * each value of the control variables to the elements that it is learning.
   *
   * @param data a map from values of the control variables to observed purity and runtime
   *
   */
  def makeLearningModel(data: scala.collection.immutable.Map[(Int, Int, Int), List[(Double, Double)]]): (Universe, Map[(Int, Int, Int), (Element[_], Element[_])]) = {
    makePurityPriors()
    makeRuntimePriors()

    val purity = Chain(controlTuple, (d: (Int, Int, Int)) => purityPriors(d))("", universe)
    val runtime = Chain(controlTuple, (d: (Int, Int, Int)) => runtimePriors(d))("", universe)

    ^^(controlTuple, purity)("", universe).addLogConstraint((v: ((Int,Int,Int), (Double, Double))) => {
      if (data.contains(v._1)) {
        val s = data(v._1).map(d => ClusterModel.logpBeta(v._2._1, v._2._2, math.max(0.000001, math.min(d._1, 0.999999))))
        s.sum
      } else {
        0.0
      }
    })
    
    ^^(controlTuple, runtime)("", universe).addLogConstraint((v: ((Int,Int,Int), (Double, Double))) => {
      if (data.contains(v._1)) {
        val s = data(v._1).map(d => ClusterModel.logpNormal(v._2._1, v._2._2*v._2._2, d._2))
        s.sum
      } else {
        0.0
      }
    })   
    
    (universe, purityPriors.map(v => v._1 -> (v._2, runtimePriors(v._1))))
  }

  def makePosteriorModel(alg: ProbQueryAlgorithm): Universe = {
    val nextUniverse = new Universe
    val purityExpectations = purityPriors.mapValues { p =>
      ((0.0, 0.0) /: alg.distribution(p))((c: (Double, Double), n: (Double, (Double, Double))) => (c._1 + n._1 * n._2._1, c._2 + n._1 * n._2._2))
    }
    val runtimeExpectations = runtimePriors.mapValues { p =>
      ((0.0, 0.0) /: alg.distribution(p))((c: (Double, Double), n: (Double, (Double, Double))) => (c._1 + n._1 * n._2._1, c._2 + n._1 * n._2._2))
    }

    val clusters = FromRange(numClustersSupport._1, numClustersSupport._2 + 1)("numClusters", nextUniverse)
    val init = FromRange(initMethodSupport._1, initMethodSupport._2 + 1)("initMethod", nextUniverse)
    val iters = FromRange(maxItersSupport._1, maxItersSupport._2 + 1)("maxIters", nextUniverse)

    val purity = Chain(^^(clusters, init, iters), (c: (Int, Int, Int)) => {
      val (alpha, beta) = purityExpectations(c)
      Beta(alpha, beta)("", nextUniverse)
    })("purity", nextUniverse)

    val runtime = Chain(^^(clusters, init, iters), (c: (Int, Int, Int)) => {
      val (mean, std) = runtimeExpectations(c)
      Normal(mean, std * std)("", nextUniverse)
    })("runtime", nextUniverse)

    nextUniverse
  }

}

object ClusterModel {
  def logpBeta(aValue: Double, bValue: Double, value: Double) =
    bound(
      logGamma(aValue + bValue) - logGamma(aValue) - logGamma(bValue) +
        (aValue - 1) * log(value) + (bValue - 1) * log(1 - value),
      aValue > 0,
      bValue > 0)

  def logpNormal(meanValue: Double, varianceValue: Double, value: Double) =
    bound(
      (-(value - meanValue) * (value - meanValue) / varianceValue + log(1 / math.Pi / 2.0 / varianceValue)) / 2.0,
      varianceValue > 0)

}
