package com.cra.princess.pathplanner.component

import com.cra.princess.{ComponentControls, InputModel}
import com.cra.princess.componentmodel.{ComponentModel, ControlGenerator}
import com.cra.princess.optimizer.ComponentOptimizer

class PathPlannerEmptyOptimizer extends ComponentOptimizer[PathPlannerEnvironment, PathPlannerInputEmpty] {
  def thresholds() = List.empty
  def apply(v1: PathPlannerEnvironment, v2: PathPlannerInputEmpty): ComponentControls = Map.empty
  def apply(v1: ComponentModel[PathPlannerEnvironment, PathPlannerInputEmpty], v2: InputModel[PathPlannerEnvironment, PathPlannerInputEmpty], v3: ControlGenerator) = Map.empty
}
