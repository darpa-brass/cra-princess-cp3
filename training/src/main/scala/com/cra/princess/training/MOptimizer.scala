package com.cra.princess.training

import com.cra.princess.training.actorcritic.ActorCriticNetwork
import com.cra.princess.training.training.{TrainingControls, TrainingState}

class MOptimizer(actorCriticNetwork: ActorCriticNetwork) {
  def getOptimizedControls(controls: List[TrainingControls], state: TrainingState): TrainingControls = {
    require(actorCriticNetwork.criticInputDim == (controls.head ++ state).length)
    controls.map{ c =>
      val reward = actorCriticNetwork.getReward(c.toList ++ state.toList)
//      println(c.toList ++ state, reward)
      (c, reward)
    }.maxBy(_._2)._1
  }
}

