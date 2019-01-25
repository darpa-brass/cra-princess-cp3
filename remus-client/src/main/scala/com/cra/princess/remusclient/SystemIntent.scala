package com.cra.princess.remusclient

import com.cra.princess.core.{GreaterThan, Intent, LessThan, ThresholdData}
import com.cra.princess.optimizer.ComponentIds

// TODO This intent requires that the power level be greater than zero. We are obviously going to need to change this.
class SystemIntent extends Intent(ComponentIds.SystemComponentId, "System-level intent concerning power consumption", List.empty, List(ThresholdData("power", 100, LessThan()))) {}
