package com.cra.princess.training

import com.cra.princess.training.training.TrainingControls

trait ControlGeneratorParams

trait ControlGenerator extends ( () => List[TrainingControls] ) {
  val params: ControlGeneratorParams
}
