package com.cra.princess.pathplanner.component

import com.cra.princess.{ComponentControls, ComponentMetrics, Threshold}
import com.cra.princess.core.{Intent, NormalPriorPrincessFeature}
import com.cra.princess.pathplanner.{PathCoverageSimulator, SingleFunctionPathPlanner, Waypoint}
import com.cra.princess.util.{Logs, PrincessProperties}

import scala.collection.JavaConverters._

class PathPlannerComponentImpl(pathPlanner: SingleFunctionPathPlanner, initialControls: ComponentControls) extends PathPlannerComponent with Logs {
  private var currentControls: ComponentControls = initialControls
  private val _intent = new PathPlannerIntent
  override def intent(): Intent = _intent

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
  override def component(e: PathPlannerEnvironment, i: PPInput, c: ComponentControls): java.util.List[Waypoint] =
  {
    if((c != null) && c.nonEmpty) {
      updateControls(c)
    }
    runComponent(e, i)
  }

  /**
    * Run the component
    *
    * @param e - Env
    * @param i - Input
    * @return Output
    */
  override def runComponent(e: PathPlannerEnvironment, i: PPInput): java.util.List[Waypoint] =
  {
    val output: Array[Array[Double]] = pathPlanner.TransformedPlan(currentControls("ctrl0").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl1").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl2").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl3").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl4").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl5").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl6").asInstanceOf[NormalPriorPrincessFeature].value,
                                currentControls("ctrl7").asInstanceOf[NormalPriorPrincessFeature].value,
                                i.startLocationX,
                                i.startLocationY,
                                i.returnLocationX,
                                i.returnLocationY,
                                i.searchArea.map(_.toArray).toArray,
                                i.searchArea.length,
                                i.altitude,
                                i.fovRadians)

    val budgetThreshold: Threshold = {
      if(this.intent != null) {
        this.intent.thresholds.head
      } else {
        log.debug("Setting budget threshold to 2250.0")  // TODO: throw exception and/or log, this shouldn't ever happen
        2250.0
      }
    }
    log.debug(s"truncate path = ${PrincessProperties.truncatePath}, distance budget = ${budgetThreshold}")
    val truncatedOutput = if (PrincessProperties.truncatePath) SingleFunctionPathPlanner.truncatePath(output, budgetThreshold) else output
    // convert output to Waypoint
    log.debug(s"New Path: ${outputToWaypointList(truncatedOutput)}")
    outputToWaypointList(truncatedOutput)
  }

  private def outputToWaypointList(output: Array[Array[Double]]): java.util.List[Waypoint] = {
    val outputConverted = new java.util.ArrayList[Waypoint]()
    var idx: Int = 0
    var endMarkerFound: Boolean = false
    while (idx < output.length && !endMarkerFound) {
      val xVal = output(idx)(0)
      val yVal: Double = output(idx)(1)
      if(xVal != SingleFunctionPathPlanner.END_MARKER) {
        val w: Waypoint = new Waypoint(yVal, xVal)
        outputConverted.add(w)
      } else {
        endMarkerFound = true
      }
      idx = idx + 1
    }
    outputConverted
  }

  private def wayPointListToOutput(wayPointList: java.util.List[Waypoint]): Array[Array[Double]] = {
    (wayPointList.asScala.toList.map(w => List(w.getEast, w.getNorth).toArray) :+ Array(SingleFunctionPathPlanner.END_MARKER, SingleFunctionPathPlanner.END_MARKER)).toArray
  }

  /**
    * Update control variables for component
    *
    * @param c
    */
  override def updateControls(c: ComponentControls): Unit = {
    this.currentControls = c
  }

  /**
    * @param e - Env
    * @param i - Input
    * @param o - Output
    * @return ComponentMetrics - Current state of component
    */
  override def metricCalculator(e: PathPlannerEnvironment, i: PPInput, o: java.util.List[Waypoint]): ComponentMetrics = {
    val plan = wayPointListToOutput(o)
    // calculate coverage
    val pathCoverageSimulator: PathCoverageSimulator =
      new PathCoverageSimulator(plan, i.searchArea(0).toArray, i.searchArea(2).toArray, i.altitude, i.fovRadians)
    // calculate distance
    val distance: Double = SingleFunctionPathPlanner.distance(plan)
    List(distance, pathCoverageSimulator.coverage())
  }
}

object ppInitialControls extends (() => ComponentControls) {
  def apply(): ComponentControls = {
    Map("ctrl0" -> new NormalPriorPrincessFeature(0.0, 0.0, 0.0), // ctrlLoop0
        "ctrl1" -> new NormalPriorPrincessFeature(0.0, 0.0, 0.0), // ctrlLoop1
        "ctrl2" -> new NormalPriorPrincessFeature(0.0, 0.0, 0.0), // ctrlCmp0
        "ctrl3" -> new NormalPriorPrincessFeature(2.0, 0.0, 0.0), // ctrlConst0
        "ctrl4" -> new NormalPriorPrincessFeature(1.0, 0.0, 0.0), // ctrlConst1
        "ctrl5" -> new NormalPriorPrincessFeature(1.0, 0.0, 0.0), // ctrlConst2
        "ctrl6" -> new NormalPriorPrincessFeature(2.0, 0.0, 0.0), // ctrlConst3
        "ctrl7" -> new NormalPriorPrincessFeature(0.0, 0.0, 0.0)  // ctrlConst4
    )
  }
}