//package com.cra.princess.remusclient.sensortransformer
//
//import com.cra.princess.core.{FaultData, SensorEventListener, SensorTransformer, TransformationData}
//import com.cra.princess.metron.remus.state.{RemusDvlData, RemusRpmData, RemusWaterSpeedData}
//import org.scalatest.{FlatSpec, Matchers}
//
//class NativeSensorTransformerTest extends FlatSpec with Matchers {
//
//  "A NativeSensorTransformer" should "detect a sensor fault" in {
//    val data = new RemusDvlData(System.currentTimeMillis(), 10.0, 0.01, 3.2, 0.01, 0.01, 0.01, 0.01, 3.2, 0.01, 0.01)
//    val waterSpeed = new RemusWaterSpeedData(System.currentTimeMillis(), 3.2)
//    val rpm = new RemusRpmData(System.currentTimeMillis(), 700.0)
//    var fault = false
//
//    val nst = new NativeSensorTransformer("CP3")
//
//    nst.addListener(new SensorEventListener {
//      override def faultDetected(data: FaultData, st: SensorTransformer): Unit = {
//        fault = true
//        nst.setAdaptationEnabled(true)
//      }
//
//      override def transformationStarted(data: TransformationData): Unit = {}
//
//      override def transformationComplete(data: TransformationData): Unit = {}
//    })
//
//    nst.rpmSensorUpdate(rpm)
//    nst.waterSpeedSensorUpdate(waterSpeed)
//
//    //val transformed = nst.processSensorReadings(data)
//    for (i <- 1 to 5) {
//      val transformed = nst.processSensorReadings(generateGoodData)
//      println(s"transformed surge = ${transformed.getSurge}")
//    }
//
//    fault should equal (false)
//
//    nst.processSensorReadings(generateBadData)
//    nst.processSensorReadings(generateBadData)
//
//    val transformed = nst.processSensorReadings(generateBadData)
//    transformed.getSurge should equal (2.84)
//
//  }
//
//  private def generateGoodData: RemusDvlData = new RemusDvlData(System.currentTimeMillis(), 10.0, 0.01, 3.2,
//    0.01, 0.01, 0.01, 0.01, 3.2, 0.01, 0.01)
//
//  private def generateBadData: RemusDvlData = new RemusDvlData(System.currentTimeMillis(), 10.0, 0.01, -3.2,
//    0.01, 0.01, 0.01, 0.01, -3.2, 0.01, 0.01)
//}
