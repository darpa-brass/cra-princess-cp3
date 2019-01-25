package com.cra.princess.optimizer

import com.cra.figaro.language._
import com.cra.figaro.algorithm.sampling.MetropolisHastingsAnnealer
import com.cra.figaro.algorithm.sampling.ProposalScheme
import com.cra.figaro.algorithm.sampling.Schedule
import com.cra.princess._
import com.cra.figaro.library.collection.Container
import com.cra.princess.componentmodel.{ComponentModel, ComponentModelInput, ControlGenerator}
import com.cra.princess.core.PrincessFeature

/**
  * Uses simulated annealing to optimize control variables.
  * In fact, SA finds the MAP assignment to all variables,
  * so this is really a rough approximation to the marginal MAP problem.
  * @param thresholds Specifies an acceptable quality level for each metric
  * @param elementCollection
  * @param initialState Starting state of control variables in the optimization
  * @tparam Env
  * @tparam Input
  */
class SimulatedAnnealingOptimizer[Env <: PrincessFeature, Input <: PrincessFeature](
          val thresholds: List[Threshold], elementCollection: ElementCollection,
          val initialState: Map[String, Control]) extends Optimizer[Env, Input] {

  val SATISFIED_CONSTRAINT = 1e6

  /**
    * Creates the optimization model by wiring
    * together the control variables, component model, and input model.
    */
  def makeOptimizationModel(control: Map[String, Element[Control]], cm: ComponentModel[Env, Input],
                            im: Element[(Env, Input)]):Element[List[Control]] = {
    if(!(thresholds.length == cm.numMetrics)) {
      throw new IllegalArgumentException("Got " + cm.numMetrics + " metrics, but " + thresholds.length + " thresholds")
    }

     val sortedControl = control.toSeq.sortBy(_._1)
     val (controlNames, controlElements) = sortedControl.unzip
     val controlContainer = Container(controlElements:_*)
     val combinedControl = controlContainer.foldLeft(List[Control]())((p: List[Control], d: Control) => p :+ d)

    // construct CPDs for metrics
     val componentChains = (0 until cm.numMetrics).map(metricIndex =>
       Chain(im, combinedControl, (ei: (Env, Input), l: List[Control]) => {
       val componentControls = Map[String, Control](controlNames.zip(l):_*)

         cm(ComponentModelInput(ei._1, ei._2, componentControls))(metricIndex)
       })("ComponentModel" + metricIndex, elementCollection)
     )

    // add constraints to all of the metrics. this constraint has a slight gradient with a sharp step at the threshold value
    componentChains.zipWithIndex.foreach(elti => {
      val (elt, i) = elti
      elt.addConstraint((d: Metric) => {
        val term1 = 1 / (1 + Math.exp(d - thresholds(i))) // grows as d shrinks, bounded 0/1
        val term2 = if (d < thresholds(i)) SATISFIED_CONSTRAINT else 0
        val constraintVal = (term1 + term2) / (SATISFIED_CONSTRAINT + 1)
        constraintVal
      })
    })

    combinedControl
  }

  /**
    * Perform the optimization and return the optimized control variables
    */
  def apply(cm: ComponentModel[Env, Input], im: Element[(Env, Input)], cg: ControlGenerator): Map[String, Control] = {
  	val control = cg.elements
    val	optimizationTarget = makeOptimizationModel(control, cm, im)

    val alg = InitialStateMetropolosHastingsAnnealer(10000, ProposalScheme.default, Schedule.default(2.0), control.values.toList)

    // set initial state of the optimizer
    control.foreach(kv => {
      val (name, elt) = kv
      elt.set(initialState(name))
      elt.deactivate()
    })
    alg.run()
    val optimalControls = alg.mostLikelyValue(optimizationTarget)

    val namedResult = (control.keys.toList.sorted).zip(optimalControls).toMap
    namedResult
  }

}

object SimulatedAnnealingOptimizer {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](thresholds: List[Threshold], initialState: Map[String, Control])(implicit elementCollection: ElementCollection) =
    new SimulatedAnnealingOptimizer[Env, Input](thresholds, elementCollection, initialState)
}