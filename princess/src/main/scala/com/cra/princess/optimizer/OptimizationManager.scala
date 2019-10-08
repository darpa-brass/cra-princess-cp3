package com.cra.princess.optimizer

import com.cra.princess.core._
import com.cra.princess.util.Logs

import scala.collection.mutable.ListBuffer
import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

// Params:
//  stateEstimator: StateEstimator - needed by MP to update energy reserve
//  CAMs: reference to component adaptation managers maintained by ScenarioController
//  energyToDistanceConversion: Double - needed by MP to calc distance budget
//  energyReserveIncrement: Double - needed by MP to adjust energy reserve, oonverts watt-hours to meters
//  coverageThresholdSlack: Double - needed by MP to adjust coverage threshold
//  sensorTransformer: ? - needed by OM to trigger optimization

class OptimizationManager (CAMs: ListBuffer[ComponentAdaptationManager[_ <: PrincessFeature, _ <: PrincessFeature, _]] = null,
                           val stateEstimator: StateEstimator = null, sensorTransformerPolicy: SensorTransformerPolicy = new DefaultSensorTransformerPolicy,
                           val energyToDistanceConversion: Double = 0.00016837354104938271604938271604938, // Phase 3: m/joule, Phase: 1.125 m/Wh
                           val energyReserveIncrement: Double = 360000.0, // Phase3: joules, Phase2: 100.0 Wh,
                           val coverageThresholdSlack: Double = 0.0) extends SensorEventListener with Logs {

  private var ready: Boolean = true
  private var kfReady: Boolean = true
  private val missionPrioritizer: MissionPrioritizer =
    new MissionPrioritizer(stateEstimator,
                           CAMs,
                           energyToDistanceConversion,
                           energyReserveIncrement,
                           coverageThresholdSlack)

  def init(): Unit  = {
    this.lockKfForTimeDuration()
  }

  def observeStatusUpdateReady(): Unit = {
    ready = true
  }

  def observeIntentResult(result: IntentResult): Unit = {
    log.debug(s"Calling observeIntentResult with IntentResult = $result")
    result match {
      case IntentResult(componentId, false, Some(failureData)) => {
        componentId match {
          case ComponentIds.KFComponentId => {
            if (ready && kfReady) {
              ready = false
              triggerOptimizer(componentId)
              ready = true
              lockKfForTimeDuration()
            }
          }
          case ComponentIds.PPComponentId => {
            failureData.metricName.toLowerCase() match {
              case "coverage" => {
                missionPrioritizer.updatePathPlannerCoverageThreshold(failureData) // updates threshold in optimizer
              }
              case _ => {
                log.error(s"Unrecognized failure metric: ${failureData.metricName}")
              }// die with error
            }
          }
          case ComponentIds.SystemComponentId => {
            missionPrioritizer.updatePathPlannerDistanceBudget() //updates threshold in optimizer
            ready = false
            triggerOptimizer(ComponentIds.PPComponentId)
            ready = true
          }
          case _ =>
            log.error(s"Unrecognized component ID: $componentId")
        }
      }
      case _ =>
        log.debug("Ignoring intent result")
    }
  }

  def observeVerificationResult(event: VerificationEvent): Unit = {
    // observe the VerificationResult
    val result = event.result
    if(!result.pass) {
      // Assume for now that this will always be associated with path planner
      missionPrioritizer.updateEnergyReserve(result) // also updates distance budget in optimizer
      triggerOptimizer(ComponentIds.PPComponentId)
    }
  }

  private def triggerOptimizer(componentId: Int): Unit = {
    log.debug(s"Optimizer triggered")
    for(cam <- CAMs) {
      if (cam.component.intent().componentId == componentId) {
        cam.optimize()
      }
    }
  }

  private def triggerSensorTransformerLearner(st: SensorTransformer, dim: String): Unit = {
    if (sensorTransformerPolicy.shouldTransform(st, dim)) {
      log.debug("Sensor transformer learner triggered")
      st.doTransform(dim)
    }
  }

  override def faultDetected(data: FaultData, transformer: SensorTransformer): Unit = {
    Future[Unit] {
      if (ready) {
        ready = false
        triggerSensorTransformerLearner(transformer, data.dimension)
        ready = true
      }
    }
  }

  private def lockKfForTimeDuration(durationMs: Long = 10000): Unit = {
    kfReady = false
    Future[Unit] {
      Thread.sleep(durationMs)
      kfReady = true
    }
  }

  override def transformationStarted(data: TransformationData): Unit = {} // TODO anything?
  override def transformationComplete(data: TransformationData): Unit = {} // TODO anything?
}

object ComponentIds {
  val KFComponentId: Int = 0
  val PPComponentId: Int = 1
  val SensorComponentId: Int = 2
  val SystemComponentId: Int = 3
}
