package com.cra.princess.pathplanner.component

import com.cra.princess.core.OptimizableComponent
import com.cra.princess.pathplanner.Waypoint

trait PathPlannerComponent extends OptimizableComponent[PathPlannerEnvironment, PPInput, java.util.List[Waypoint]] with Serializable {

}
