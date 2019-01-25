package com.cra.princess.optimizer

import com.cra.princess.core.SensorTransformer

trait SensorTransformerPolicy {
  def shouldTransform(st: SensorTransformer, dim: String): Boolean
}

class DefaultSensorTransformerPolicy extends SensorTransformerPolicy {
  override def shouldTransform(st: SensorTransformer, dim: String): Boolean = true
}