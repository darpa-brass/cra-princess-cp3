package com.cra.princess.optimizer

import com.cra.princess.core._
import com.cra.princess.util.Logs

import scala.collection.mutable.ListBuffer

class MissionPrioritizer(val stateEstimator: StateEstimator,
                         val CAMs: ListBuffer[ComponentAdaptationManager[_ <: PrincessFeature, _ <: PrincessFeature,_]],
                         val energyToDistanceConversion: Double,
                         val energyReserveIncrement: Double,
                         val coverageThresholdSlack: Double) extends Logs {

  var energyReserve: Double = 0.0

  def updatePathPlannerCoverageThreshold(failureData: FailureData): Unit = {
    // calculate new coverage threshold based on result
    val newCoverageThreshold: Double = failureData.metricValue + coverageThresholdSlack

    // update coverage threshold by setting state in PP component
    // TODO: make sure threshold name is consistent with intent definition
    log.debug(s"Setting new Path Planner coverage threshold = $newCoverageThreshold")
    setThreshold(ComponentIds.PPComponentId, "coverage", newCoverageThreshold)
  }

  def updatePathPlannerDistanceBudget(): Unit = {
    // get energy level from state estimator
    getEnergyLevel() match {
      case Some(energyLevel) =>
        // recalculate distance budget based on energy level
        val newDistanceBudget: Double = {
          val d = energyToDistanceConversion * (energyLevel - energyReserve)
          if(d >= 0.0) {
            d
          } else {
            0.0
          }
        }

        // update distance budget by setting state in PP component
        // TODO: make sure threshold name is consistent with intent definition
        log.debug(s"Setting new Path Planner distance budget = $newDistanceBudget")
        setThreshold(ComponentIds.PPComponentId, "distance", newDistanceBudget)
      case None =>
        log.warn("Power value not found in State Estimator")
    }
  }

  def updateEnergyReserve(result: VerificationResult): Unit = {
    // TODO: update energy reserve based on additional information provided by Verifier
    //  Without Verifier info, just add a constant amount defined by energyReserveIncrement
    energyReserve += energyReserveIncrement
    log.debug(s"Updated energy reserve = $energyReserve")
    updatePathPlannerDistanceBudget()
  }

  private def setThreshold(componentId: Int, thresholdName: String, newVal: Double): Unit = {
    for (cam <- CAMs) {
      val intent: Intent = cam.component.intent()
      if(intent.componentId == componentId) {
        cam.component.intent.updateThreshold(thresholdName, newVal)
      }
    }
  }

  private def getEnergyLevel(): Option[Double] = {
    val values = stateEstimator.valuesForKeys(Set("energylevel"))
    val energyLevel = values("energylevel")
    log.debug(s"Retrieving energy level = $energyLevel")
    energyLevel
  }
}
