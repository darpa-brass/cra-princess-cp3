package com.cra.princess.pathplanner.component

import com.cra.princess.core.{GreaterThan, Intent, LessThan, ThresholdData}
import com.cra.princess.optimizer.ComponentIds

class PathPlannerIntent extends Intent(ComponentIds.PPComponentId, "intent for the path planner",
                                       List.empty,
                                       List(ThresholdData("distance", 2250.0, LessThan()),
                                            ThresholdData("coverage", 0.5, GreaterThan()))
                                      ) {}
