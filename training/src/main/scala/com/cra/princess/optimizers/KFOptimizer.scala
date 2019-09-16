package com.cra.princess.optimizers

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import com.cra.princess.optimizer.ComponentOptimizer
import com.cra.princess.training.actorcritic.{ActorCriticNetwork, D4JNetwork}
import com.cra.princess.training.training.TrainingState

class KFOptimizer(acNetwork: ActorCriticNetwork)
  extends ComponentOptimizer[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper]{

  override def apply(env: KalmanFilterEnvironmentWrapper, input: KalmanFilterInputWrapper): ComponentControls = {
    val inputState: TrainingState = input.state.getCombinedState.toArray
    val optimizedCtrls = optimize(inputState.toList).toArray
    val controlsToReturn = Map(
      "bDiag0" -> new BoundedScalarPrincessFeature(optimizedCtrls(0), 0, 0),
      "bDiag1" -> new BoundedScalarPrincessFeature(optimizedCtrls(1), 0, 0),
      "qDiag0" -> new BoundedScalarPrincessFeature(optimizedCtrls(2), 0, 0),
      "qDiag1" -> new BoundedScalarPrincessFeature(optimizedCtrls(3), 0, 0),
      "rDiag0" -> new BoundedScalarPrincessFeature(optimizedCtrls(4), 0, 0),
      "rDiag1" -> new BoundedScalarPrincessFeature(optimizedCtrls(5), 0, 0))
    require(controlsToReturn.size == optimizedCtrls.length)
    controlsToReturn
  }

  override def optimize(input: List[Double]): List[Double] = acNetwork.optimize(input).toList
}

object KFOptimizer{
  def apply(actorFile: String, criticFile: String): KFOptimizer = {
    val model = new D4JNetwork(actorFile, criticFile)
    new KFOptimizer(model)
  }
}