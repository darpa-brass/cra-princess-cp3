package com.cra.princess.remusclient.sensortransformer

//import com.cra.princess.core.{FaultData, SensorTransformer}
//import com.cra.princess.evaluation.EvaluationMessenger
//import com.cra.princess.metron.MetronRemusManager
//import com.cra.princess.metron.remus.state.{SensorFailureData, SensorFailureUpdateListener}
//
//class ProxiedSensorTransformer extends SensorTransformer with SensorFailureUpdateListener {
//
//  private val em = EvaluationMessenger.getInstance()
//  private val mrm = MetronRemusManager.getInstance()
//
//  private val componentName = "Sensor Transformer"
//
//  override def doTransform(dimension: String): Unit = {
//    em.sendAdaptationStartedMessage(componentName)
//    log.info(s"Invoking transformation on sensor dimension: $dimension")
//    mrm.sendSensorTransformerLearnCommand(dimension)
//    em.sendAdaptationCompletedMessage(componentName)
//  }
//
//  override def sensorFailureUpdate(msg: SensorFailureData): Unit = {
//    log.info(s"Sensor failure detected: ${msg.toString}")
//    em.sendPerturbationDetectedMessage(msg.getDimension, msg.getConfidence)
//    val fault = new FaultData(msg.getDimension, msg.getTimestamp)
//    this.fireFaultDetected(fault)
//  }
//}
