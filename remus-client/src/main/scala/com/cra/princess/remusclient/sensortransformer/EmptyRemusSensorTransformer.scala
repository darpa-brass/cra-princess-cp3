package com.cra.princess.remusclient.sensortransformer

import com.cra.princess.metron.remus.state.{RemusDvlData, RemusRpmData, RemusWaterSpeedData, TransformedRemusDvlData}
import com.cra.princess.util.Logs

class EmptyRemusSensorTransformer extends RemusSensorTransformer with Logs {
  override def processSensorReadings(dvlData: RemusDvlData): TransformedRemusDvlData = {
    new TransformedRemusDvlData(dvlData.getTimestamp, dvlData.getDepth, dvlData.getvE(), dvlData.getvN(), dvlData.getvU(), dvlData.getPitch,
      dvlData.getRoll, dvlData.getHeading, 1, 1, 1, 0, 0, 0,
      dvlData.getSurge, dvlData.getSway, dvlData.getHeave, 1, 1, 1, 0, 0, 0)
  }

  override def rpmSensorUpdate(rpmDataUpdateMessage: RemusRpmData): Unit = {}

  override def waterSpeedSensorUpdate(waterSpeedDataUpdateMessage: RemusWaterSpeedData): Unit = {}

  override def doTransform(dimension: String): Unit = {}
}
