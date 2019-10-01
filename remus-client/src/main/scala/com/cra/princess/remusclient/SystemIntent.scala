package com.cra.princess.remusclient

import com.cra.princess.core.{GreaterThan, Intent, LessThan, ThresholdData}
import com.cra.princess.optimizer.ComponentIds

class SystemIntent extends Intent(ComponentIds.SystemComponentId,
  "System-level intent concerning power consumption",
  List.empty,
  List(ThresholdData("power", 750, LessThan()))) {}
