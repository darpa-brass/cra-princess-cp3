package com.cra.princess.remusclient.navigation

import com.cra.princess.{ComponentControls, ComponentMetrics, Control}
import com.cra.princess.core._
import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector
import com.cra.princess.optimizer.ComponentIds
import com.cra.princess.pathplanner.Waypoint

/**
  * @param home - starting point
  * @param path - series of way-points to follow
  */
class OptimizablePathFollower(home: Waypoint, path: List[Waypoint])
  extends PathFollower(home, path) with OptimizableComponent[PathFollowerEnvironment, PathFollowerInput, KalmanFilterActuatorVector]{
  override def intent(): Intent = PathFollowerIntent()

  private var currentControls: ComponentControls = Map("headingDeviation" -> new BoundedScalarPrincessFeature(0.0,0,0))

    /**
    * Run the component and update control variables.
    * If synchronous, call runComponent and updateControls (in some order)
    * If asynchronous, a custom implementation is needed
    *
    * @param e - Env
    * @param i - Input
    * @param c - ComponentControls
    * @return Output - heading value in degrees
    */
  override def component(e:  PathFollowerEnvironment, i:  PathFollowerInput, c:  ComponentControls): KalmanFilterActuatorVector = {
    if (null != c && c.nonEmpty) updateControls(c)
    val av = runComponent(e, i)
    val headingDeviation = getCVal(currentControls("headingDeviation"))
    new KalmanFilterActuatorVector(av.getEntry(0),av.getEntry(1), av.getEntry(2), av.getEntry(3), av.getEntry(4) + headingDeviation)
  }

  /**
    * Run the component
    *
    * @param e - Empty Environment
    * @param input - LatLon
    * @return Output - heading value in degrees
    */
  override def runComponent(e:  PathFollowerEnvironment, input: PathFollowerInput): KalmanFilterActuatorVector = {
    generateActuatorVector(input.latLon)
  }

  /**
    * Update control variables for component
    * @param c - control variables
    */
  override def updateControls(c:  ComponentControls): Unit = {
    if (null != c) {
      currentControls = c
    }
  }

  /**
    * @param e - Empty Environment
    * @param i - LatLon
    * @param o - Empty List
    * @return ComponentMetrics - Current state of component
    */
  override def metricCalculator(e:  PathFollowerEnvironment, i: PathFollowerInput, o: KalmanFilterActuatorVector): ComponentMetrics = List.empty

  private def getCVal(c:Control): Double = c match {
    case scalar: ScalarPrincessFeature => scalar.value
    case _ => throw new IllegalArgumentException(s"control should be Scalar Princess Feature but was ${c.getClass}.")
  }
}

case class PathFollowerEnvironment() extends PrincessFeatureCollection(List.empty)

case class PathFollowerInput(latLon: LatLon) extends PrincessFeature

case class PathFollowerIntent() extends Intent(ComponentIds.PPComponentId, "intent for the path planner",
  List.empty,
  List(ThresholdData("distance", 0.0, LessThan()),
    ThresholdData("coverage", 0.0, GreaterThan()))
) {}