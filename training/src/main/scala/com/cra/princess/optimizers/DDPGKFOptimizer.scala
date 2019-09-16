package com.cra.princess.optimizers

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import com.cra.princess.optimizer.ComponentOptimizer
import com.cra.princess.training.ddpg.DDPGTrainer
import com.cra.princess.training.ddpg.structures.{Actor, Critic}

class DDPGKFOptimizer(actor: Actor,  critic: Critic, batchSize: Int,
                      discountFactor: Double, delta: Double, saveFile: String, isTrainingMode: Boolean)
  extends DDPGTrainer(actor, critic, batchSize, discountFactor, delta, saveFile)
    with ComponentOptimizer[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] {

  override def apply(v1: KalmanFilterEnvironmentWrapper, v2: KalmanFilterInputWrapper): ComponentControls = {
    val currentState = v2.state.getCombinedState.toArray
    val optimizedCtrls = calculateExploreExploitCtrls(currentState, 0, 0) //TODO: these zeroes are placeholders!
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
}
