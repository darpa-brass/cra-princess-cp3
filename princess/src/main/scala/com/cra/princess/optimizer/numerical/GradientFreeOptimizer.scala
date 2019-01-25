package com.cra.princess.optimizer.numerical

import com.cra.princess._
import com.cra.figaro.language._
import com.cra.figaro.library.atomic.discrete.AtomicUniform
import com.cra.figaro.library.collection.Container
import com.cra.princess.componentmodel.{ComponentModel, ComponentModelInput, ControlGenerator}
import com.cra.princess.core._
import com.cra.princess.optimizer.Optimizer

/**
  * Common functionality for numerical optimizers that do not rely on gradient computations
  */
trait GradientFreeOptimizer[Env <: PrincessFeature, Input <: PrincessFeature] extends Optimizer[Env, Input] {

  /** Weights to be applied to metrics after scaling by threshold,
    * so that the weight expresses the relative importance of each metric*/
  def metricWeights():List[Double]

  /** Variance of metrics, used to standarize multi-objective problems */
  def metricVariances():List[Double]

  /**
    * Construct the objective function, which is E[M|C=c] (technically a weighted sum of metrics)
    */
  protected def buildObjective(initialState:Map[String, Control], cm:ComponentModel[Env, Input], im:InputModel[Env, Input],
                             controlElements:Map[String, Element[Control]],
                             controlGenerator:ControlGenerator, elementCollection:ElementCollection,
                               numSamples:Int = 100) = {

    val sortedControl = controlElements.toSeq.sortBy(_._1)
    val (controlNames, celements) = sortedControl.unzip
    val (lowerbounds, upperbounds) = celements.map(elt => {
      elt match {
        case (v:NormalScalarPrincessElement) => (v.mean - 3 * v.stdDev, v.mean + 3 * v.stdDev)
        case (v:UniformScalarPrincessElement) => (v.lowerBound, v.upperBound)
        case (v:AtomicUniform[PriorPrincessFeature]) =>
          (v.clauses.head._2.asInstanceOf[ScalarPrincessFeature].value,
            v.clauses.last._2.asInstanceOf[ScalarPrincessFeature].value)
        case _ => (Double.NegativeInfinity, Double.PositiveInfinity)
      }
    }).unzip
    val controlContainer = Container(celements:_*)
    val combinedControls = controlContainer.foldLeft(List[Control]())((c:List[Control], p:Control) => c :+ p)

    // construct CPDs for metrics
    val componentChains = (0 until cm.numMetrics).map(metricIndex =>
          Chain(im, combinedControls, (ei: (Env, Input), l: List[Control]) => {
            val componentControls = Map[String, Control](controlNames.zip(l):_*)

            val metricElt = cm(ComponentModelInput(ei._1, ei._2, componentControls))(metricIndex)
            metricElt
          })("ComponentModel" + metricIndex, elementCollection)
        )

    val objective = new MarginalMapObjective(initialState, controlElements,
      componentChains, metricWeights(), metricVariances(), thresholds(), numSamples)
    (objective, lowerbounds.toArray, upperbounds.toArray)
  }

  def cleanUp(objective:MarginalMapObjective) = {
    objective.targets.foreach(t => {
      t.deactivate()
      t.universe.remove(t)
    })
  }
}
