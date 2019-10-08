package com.cra.princess.remusclient.sensortransformer

import com.cra.princess.core.SensorTransformer
import com.cra.princess.optimizer.SensorTransformerPolicy

class NoAdaptationSensorTransformerPolicy extends SensorTransformerPolicy {
  override def shouldTransform(st: SensorTransformer, dim: String): Boolean = false
}
