package com.cra.princess.remusclient.sensortransformer

import com.cra.princess.core.SensorTransformer
import com.cra.princess.metron.remus.state.{RemusDvlData, RemusRpmData, RemusWaterSpeedData, TransformedRemusDvlData}

trait RemusSensorTransformer extends SensorTransformer {

  def processSensorReadings(readings: RemusDvlData): TransformedRemusDvlData

  def rpmSensorUpdate(rpmDataUpdateMessage: RemusRpmData): Unit

  def waterSpeedSensorUpdate(waterSpeedDataUpdateMessage: RemusWaterSpeedData): Unit
}
