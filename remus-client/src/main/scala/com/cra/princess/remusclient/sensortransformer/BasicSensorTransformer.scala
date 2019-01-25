package com.cra.princess.remusclient.sensortransformer

import com.cra.princess.core.{FaultData, SensorTransformer}
import com.cra.princess.evaluation.EvaluationMessenger
import com.cra.princess.evaluation.messages.DvlSensorPerturbationType
import com.cra.princess.util.Logs

import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.Future

//class BasicSensorTransformer(perturbations: List[DvlSensorPerturbationType]) extends SensorTransformer with SensorFailureUpdateListener with Logs {
//
//  private val em = EvaluationMessenger.getInstance()
//
//  // start a thread that will call sensorFailureUpdate at the prescribed time
//  perturbations.foreach (p => {
//    Future[Unit] {
//      Thread.sleep(p.TimeIntoScenario * 1000)
//      log.info("Generating sensor failure...")
//      sensorFailureUpdate(new SensorFailureData(System.currentTimeMillis(), "DVL", 0, 1.0))
//    }
//  })
//
//  override def doTransform(dimension: String): Unit = {
//    // send adaptation started / completed events
//    val componentName = "Sensor Transformer"
//    em.sendAdaptationStartedMessage(componentName)
//    log.info(s"Invoking transformation on sensor dimension: $dimension")
//    em.sendAdaptationCompletedMessage(componentName)
//  }
//
//  override def sensorFailureUpdate(msg: SensorFailureData): Unit = {
//    // send intent violation detected message
//    log.info(s"Sensor failure detected on dimension: ${msg.getDimension}")
//    em.sendIntentViolationDetectedMessage("Sensor Transformer")
//
//    // fire faultDetected
//    fireFaultDetected(FaultData(msg.getDimension, msg.getTimestamp))
//  }
//
//}
