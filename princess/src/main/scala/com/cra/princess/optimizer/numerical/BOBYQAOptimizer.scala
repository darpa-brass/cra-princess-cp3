package com.cra.princess.optimizer.numerical

import com.cra.figaro.language.ElementCollection
import com.cra.princess._
import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.core.PrincessFeature
import com.cra.princess.util.{Logs, PrincessTypeUtility}
import org.apache.commons.math3.optim.nonlinear.scalar.{GoalType, ObjectiveFunction}
import org.apache.commons.math3.optim.{InitialGuess, MaxEval, MaxIter, SimpleBounds}

/**
  * Estimates argmin_c E[M|C=c] using numeric optimization
  */
class BOBYQAGradientFreeOptimizer[Env <: PrincessFeature, Input <: PrincessFeature](
          val thresholds: ComponentThresholds, val initialState: Map[String, Control], val metricWeights: List[Double], val metricVariances:List[Double],
          maxIter:Int, elementCollection: ElementCollection)
  extends GradientFreeOptimizer[Env, Input] with Logs {

  var objective:MarginalMapObjective = null

  /**
    * Performs optimization using a gradient-free technique
    *
    * @return A map from control name to the locally optimal value of that control
    */
  override def apply(cm: ComponentModel[Env, Input], im: InputModel[Env, Input], cg: ControlGenerator): ComponentControls =  {
    val objResult = buildObjective(initialState, cm, im, cg.elements, cg, elementCollection)
    objective = objResult._1
    val lowerbounds = objResult._2
    val upperbounds = objResult._3

    val optimizer = new org.apache.commons.math3.optim.nonlinear.scalar.noderiv.BOBYQAOptimizer((objective.initialState().length * 1.5).toInt)
    val initialValue = objective.value(objective.initialState())
    val result = optimizer.optimize(new ObjectiveFunction(objective),
      new InitialGuess(objective.initialState()),
      new MaxEval(10000),
      new MaxIter(maxIter),
      GoalType.MINIMIZE,
      new SimpleBounds(lowerbounds, upperbounds))

    log.debug("Initial value: " + initialValue + ", final value: " + result.getValue)
    PrincessTypeUtility.unflatten(initialState, result.getPoint)
  }
}

object BOBYQAGradientFreeOptimizer {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](thresholds: List[Threshold], initialState: Map[String, Control],
                                                              metricWeights:List[Double], metricVariances:List[Double], maxIter:Int=500)(implicit elementCollection: ElementCollection) =
    new BOBYQAGradientFreeOptimizer[Env, Input](thresholds, initialState, metricWeights, metricVariances, maxIter, elementCollection)
}
