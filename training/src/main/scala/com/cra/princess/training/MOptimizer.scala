package com.cra.princess.training

import com.cra.princess.training.training.{TrainingControls, TrainingState}

trait MOptimizer extends ( (List[TrainingControls], TrainingState) => TrainingControls ) {
  val actorCriticNetwork: ActorCriticNetwork
}

