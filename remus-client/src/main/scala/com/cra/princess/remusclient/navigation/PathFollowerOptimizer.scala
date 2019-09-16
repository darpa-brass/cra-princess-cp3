package com.cra.princess.remusclient.navigation

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.optimizer.ComponentOptimizer

// TODO: Currently a stub, will eventually contain and query the DDPG model!
class PathFollowerOptimizer extends ComponentOptimizer[PathFollowerEnvironment, PathFollowerInput]{
  override def apply(v1: PathFollowerEnvironment, v2: PathFollowerInput): ComponentControls = {
    val headingDeviation = Math.toDegrees(0.0) // heading deviation must be in degrees!
    Map("headingDeviation" -> new BoundedScalarPrincessFeature(headingDeviation, 0, 0))
  }
}

