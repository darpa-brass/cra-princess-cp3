package com.cra.princess.remusclient

import com.cra.princess.core.SensorTransformer
import com.cra.princess.optimizer.SensorTransformerPolicy

class Cp3SensorTransformerPolicy extends SensorTransformerPolicy {
  override def shouldTransform(st: SensorTransformer, dim: String): Boolean = false
}
