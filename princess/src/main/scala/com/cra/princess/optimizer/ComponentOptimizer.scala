package com.cra.princess.optimizer

import com.cra.princess.ComponentControls
import com.cra.princess.core.Intent

trait ComponentOptimizer[Env, Input] extends ((Env, Input) => ComponentControls) {
  private var _intent: Intent = _
  def intent: Intent = _intent
  def intent_=(intent: Intent): Unit = {
    _intent = intent
  }
  def optimize(testInputs: List[Double]): List[Double] = List.empty[Double]
}
