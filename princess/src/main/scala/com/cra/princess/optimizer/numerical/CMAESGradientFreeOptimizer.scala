package com.cra.princess.optimizer.numerical

import com.cra.figaro.language.ElementCollection
import com.cra.princess._
import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.core.PrincessFeature
import com.cra.princess.elements.ApacheRandomGeneratorWrapper
import com.cra.princess.util.{Logs, PrincessTypeUtility}
import org.apache.commons.math3.optim._
import org.apache.commons.math3.optim.nonlinear.scalar.noderiv.CMAESOptimizer.{PopulationSize, Sigma}
import org.apache.commons.math3.optim.nonlinear.scalar.{GoalType, ObjectiveFunction}

/**
  * Uses the "covariance matrix adaptation evolution strategy" to find optimal control values
  */
class CMAESGradientFreeOptimizer[Env <: PrincessFeature, Input <: PrincessFeature](
        val thresholds:ComponentThresholds, initialState:Map[String, Control], val metricWeights:List[Double], val metricVariances:List[Double],
        elementCollection:ElementCollection, maxIter:Int, numSamples:Int, numRestarts:Int = 10)
  extends GradientFreeOptimizer[Env, Input] with Logs {


  var objective:MarginalMapObjective = null
  /**
    * Performs optimization using a gradient-free technique
    *
    * @return A map from control name to the locally optimal value of that control
    */
  override def apply(cm: ComponentModel[Env, Input], im: InputModel[Env, Input], cg: ControlGenerator): ComponentControls =  {
    val objectiveInfo = buildObjective(initialState, cm, im, cg.elements, cg, elementCollection, numSamples)
    objective = objectiveInfo._1
    val lowerbounds = objectiveInfo._2
    val upperbounds = objectiveInfo._3
    val sigmas = upperbounds.zip(lowerbounds).map(ul => (ul._1 - ul._2) / 3.0)

    val controlGuesses = Seq(objective.initialState()) ++ (0 until numRestarts).map(i => PrincessTypeUtility.flatten(cg()).toArray)
    val optimizer = new org.apache.commons.math3.optim.nonlinear.scalar.noderiv.CMAESOptimizer(
      maxIter, 0, true, 10, 3, new ApacheRandomGeneratorWrapper(com.cra.figaro.util.random), false, new SimplePointChecker(Double.MaxValue, 1e-5))

    val nparams = objective.initialState().length
    val initialValue = objective.value(objective.initialState())
    controlGuesses.foreach(guess => {
      optimizer.optimize(new ObjectiveFunction(objective),
        new InitialGuess(guess),
        new MaxEval(10000),
        new MaxIter(maxIter),
        new Sigma(sigmas),
        new PopulationSize((4 + 3 * Math.log(nparams)).toInt),
        GoalType.MINIMIZE,
        new SimpleBounds(lowerbounds, upperbounds))
    })

    val bestIteration = objective.evaluations.min(Ordering.by[ObjectiveEvaluation, Double](r => r.objective))

    cleanUp(objective)
    log.debug("Initial value: " + initialValue + ", final value: " + bestIteration.objective)
    bestIteration.controls
  }

}

object CMAESGradientFreeOptimizer {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](thresholds: List[Threshold], initialState: Map[String, Control],
                                                              metricWeights:List[Double], metricVariances:List[Double], maxIter:Int=500, numSamples:Int=100, numRestarts:Int=10)
                 (implicit elementCollection: ElementCollection) =
    new CMAESGradientFreeOptimizer[Env, Input](thresholds, initialState, metricWeights,
      metricVariances, elementCollection, maxIter, numSamples, numRestarts)
}
