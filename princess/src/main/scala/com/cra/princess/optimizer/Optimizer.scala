package com.cra.princess.optimizer

import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.core.PrincessFeature
import com.cra.princess.{ComponentControls, ComponentThresholds, InputModel}

trait Optimizer[Env <: PrincessFeature, Input <: PrincessFeature] extends Function3[ComponentModel[Env, Input], InputModel[Env, Input], ControlGenerator, ComponentControls] {
  def thresholds(): ComponentThresholds

}
