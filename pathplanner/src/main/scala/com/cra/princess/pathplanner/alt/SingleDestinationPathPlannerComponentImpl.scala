package com.cra.princess.pathplanner.alt

import java.util

import com.cra.princess.{ComponentControls, ComponentMetrics}
import com.cra.princess.core.Intent
import com.cra.princess.pathplanner.Waypoint
import com.cra.princess.pathplanner.component.{PPInput, PathPlannerComponent, PathPlannerEnvironment, PathPlannerIntent}
import com.cra.princess.pathplanner.util.LatLonConverter

import scala.collection.JavaConverters._

class SingleDestinationPathPlannerComponentImpl extends PathPlannerComponent {

  private val llConv = new LatLonConverter(0.0, 0.0)

  override def intent(): Intent = new PathPlannerIntent

  /**
    * Run the component and update control variables.
    * If synchronous, call runComponent and updateControls (in some order)
    * If asynchronous, a custom implementation is needed
    *
    * @param e - Env
    * @param i - Input
    * @param c - ComponentControls
    * @return Output
    */
  override def component(e: PathPlannerEnvironment, i: PPInput, c: ComponentControls): util.List[Waypoint] = {
    if (null != c && c.nonEmpty) updateControls(c)
    runComponent(e, i)
  }

  /**
    * Run the component
    *
    * @param e - Env
    * @param i - Input
    * @return Output
    */
override def runComponent(e: PathPlannerEnvironment, i: PPInput): util.List[Waypoint] = {
  List(new Waypoint(i.returnLocationY, i.returnLocationX)).asJava
}

  /**
    * Update control variables for component
    *
    * @param c
    */
  override def updateControls(c: ComponentControls): Unit = {}

  /**
    * @param e - Env
    * @param i - Input
    * @param o - Output
    * @return ComponentMetrics - Current state of component
    */
  override def metricCalculator(e: PathPlannerEnvironment, i: PPInput, o: util.List[Waypoint]): ComponentMetrics = List.empty
}
