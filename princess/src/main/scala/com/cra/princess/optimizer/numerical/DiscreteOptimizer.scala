package com.cra.princess.optimizer.numerical

import com.cra.figaro.language.ElementCollection
import com.cra.princess._
import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.core.{OrdinalPrincessFeature, PrincessFeature}
import com.cra.princess.util.Logs

import scala.collection.mutable.{ArrayBuffer, ListBuffer}

/**
  * An optimizer for suitable for small discrete control spaces
  */
class DiscreteOptimizer[Env <: PrincessFeature, Input <: PrincessFeature](
  val thresholds:ComponentThresholds, initialState:Map[String, OrdinalPrincessFeature], val metricWeights:List[Double], val metricVariances:List[Double],
  elementCollection:ElementCollection, numSamples:Int)
  extends GradientFreeOptimizer[Env, Input] with Logs {

  var objective:MarginalMapObjective = null

  override def apply(cm: ComponentModel[Env, Input], im: InputModel[Env, Input], cg: ControlGenerator): ComponentControls = {
    val objectiveInfo = buildObjective(initialState, cm, im, cg.elements, cg, elementCollection, numSamples)
    objective = objectiveInfo._1

    // expand the control space, warning about large spaces (> 100 records)
    val controlRanges = initialState.mapValues(p => (p.start to p.bound))
    val controlDomainSize = controlRanges.values.map(v => v.size).product
    if(controlDomainSize > 100) {
      log.warn("The size of the joint control space (" + controlDomainSize + ") may be too large for DiscreteOptimizer to efficiently handle.")
    }
    val controlNames = controlRanges.keys.toArray
    var controlAssignments:Array[Array[Int]] = controlRanges(controlNames.head).map(v => Array(v)).toArray
    for(control <- controlNames.drop(1)) {
      val nextAssignments = ArrayBuffer.empty[Array[Int]]
      for(v <- controlRanges(control)) {
        nextAssignments ++= controlAssignments.map(a => a ++ Array(v))
      }
      controlAssignments = nextAssignments.toArray
    }

    for(assignment <- controlAssignments) {
      objective.expectation(controlNames.zip(assignment).toMap.transform((k, v) =>
        new OrdinalPrincessFeature(v, initialState(k).start, initialState(k).bound)))
    }

    val bestIteration = objective.evaluations.min(Ordering.by[ObjectiveEvaluation, Double](r => r.objective))
    cleanUp(objective)

    log.debug("Final value: " + bestIteration.objective)
    bestIteration.controls
  }
}

object DiscreteOptimizer {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](thresholds: List[Threshold], initialState: Map[String, OrdinalPrincessFeature],
                                                              metricWeights:List[Double], metricVariances:List[Double], numSamples:Int=100)
                 (implicit elementCollection: ElementCollection) =
    new DiscreteOptimizer[Env, Input](thresholds, initialState, metricWeights,
      metricVariances, elementCollection, numSamples)
}
