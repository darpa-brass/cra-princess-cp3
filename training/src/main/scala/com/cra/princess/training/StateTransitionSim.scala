package com.cra.princess.training

import com.cra.princess.training.training.TrainingState

trait StateTransitionSim extends (TrainingState => TrainingState) {
}
