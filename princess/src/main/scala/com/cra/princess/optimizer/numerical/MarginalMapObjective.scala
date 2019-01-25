package com.cra.princess.optimizer.numerical

import com.cra.figaro.algorithm.sampling.{Importance, MetropolisHastings, ProposalScheme}
import com.cra.princess._
import com.cra.figaro.language._
import com.cra.princess.core.ScalarPrincessFeature
import com.cra.princess.util.{Logs, PrincessTypeUtility}
import org.apache.commons.math3.analysis.MultivariateFunction

import scala.collection.mutable.ListBuffer

case class ObjectiveEvaluation(val controls:ComponentControls, val metrics:Seq[Double], val objective:Double)

/**
  * An objective function which uses importance sampling to compute expectations at specified control values
  * @param initialControls starting values of control variables
  * @param controlElements control variable elements to optimize for in the model
  * @param targets metrics to optimize for
  * @param targetWeights relative importance of metrics
  * @param targetVariances variance of each metric, used to standardize expectations to unit variance
  * @param targetThresholds thresholds of each metric, used to center expectations at the threshold
  * @param numSamples number of importance sampling steps to approximate the conditional expectation of metrics
  */
class MarginalMapObjective(initialControls:ComponentControls, controlElements:Map[String, Element[Control]],
                           val targets:Seq[Element[Metric]],
                           targetWeights:Seq[Double],
                           targetVariances:Seq[Double],
                           targetThresholds:Seq[Double],
                           numSamples:Int) extends MultivariateFunction with Logs {

  var numEvals = 0

  var evaluations = new ListBuffer[ObjectiveEvaluation]

  def initialState():Array[Double]  = {
    PrincessTypeUtility.flatten(initialControls).toArray
  }

  /**
    * Computes the objective function value as as weighted, normalized combination of expectations:
    * Objective = w0 (E[M0|C] - t0) / s0 + w1 (E[M1|C] - t1) / s1 + ... + wn (E[Mn|C] - tn) / sn, where:
    *   wi is the relative weight for metric i,
    *   ti is the threshold for metric i,
    *   si is the standard deviation of metric i.
    *
    * As a result, each expectation is standardized such that it is centered at the threshold value, and has unit variance.
    * This allows the user to specify scale-invariant weights.
    * The standardized metric is less than zero when the metric is lower than the threshold, and greater than zero when the metric exceeds the threshold.
    */
  def expectation(controls:ComponentControls) = {
    controls.transform((name, value) => {
      if(!controlElements(name).active)
        controlElements(name).activate()
      controlElements(name).observe(value)
      controlElements(name).deactivate()
    })

    val alg = Importance(numSamples, targets:_*)
    alg.start()
    val expectations = targets.map(target => alg.computeExpectation(target, (m:Double) => m))
    alg.kill()

    // standardize the expectations and weight them to yield the objective
    val objective = (0 until expectations.length).map(i =>
      targetWeights(i) * (expectations(i) - targetThresholds(i)) / Math.sqrt(targetVariances(i))).sum

    val controlNames = controls.keys.toList.sorted
    if(numEvals == 0) {
      val metricNames = (0 until targets.length).map(i => "E[M" + i + "|C]").mkString(",")
      log.trace("objective," + metricNames + "," + controlNames.mkString(","))
    }
    numEvals += 1
    evaluations += ObjectiveEvaluation(controls, expectations, objective)
    log.trace(objective + "," + expectations.mkString(",") + "," + controlNames.map(n => controls(n).asInstanceOf[ScalarPrincessFeature].value).mkString(","))
    objective
  }


  override def value(args:Array[Double]) = {
      expectation(PrincessTypeUtility.unflatten(initialControls, args))
    }
}
