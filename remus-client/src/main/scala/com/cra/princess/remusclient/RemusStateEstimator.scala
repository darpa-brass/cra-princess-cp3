package com.cra.princess.remusclient

import com.cra.princess.metron.remus.state._
import com.cra.princess.optimizer.StateEstimator
import com.cra.princess.util.Logs

import scala.collection.mutable

class RemusStateEstimator extends StateEstimator with TransformedDvlSensorUpdateListener with VehiclePowerUpdateListener with WaterSpeedSensorUpdateListener with RpmSensorUpdateListener with Logs {

  private val ALL_KEYS = RemusStateEstimator.DVL_VARS ++ RemusStateEstimator.POWER_VARS ++ RemusStateEstimator.WATERSPEED_VARS ++ RemusStateEstimator.RPM_VARS
  ALL_KEYS.foreach(map(_) = None)

  override def transformedDvlSensorUpdate(msg: TransformedRemusDvlData): Unit = {
    map(RemusStateEstimator.DVL_E) = Some(msg.getvE)
    map(RemusStateEstimator.DVL_N) = Some(msg.getvN)
    map(RemusStateEstimator.DVL_U) = Some(msg.getvU)
    map(RemusStateEstimator.DVL_DEPTH) = Some(msg.getDepth)
    map(RemusStateEstimator.DVL_PITCH) = Some(msg.getPitch)
    map(RemusStateEstimator.DVL_ROLL) = Some(msg.getRoll)
    map(RemusStateEstimator.DVL_HEADING) = Some(msg.getHeading)
  }


  override def waterSpeedSensorUpdate(msg: RemusWaterSpeedData): Unit = {
    map(RemusStateEstimator.WATER_SPEED) = Some(msg.getSpeed)
  }

  override def rpmSensorUpdate(msg: RemusRpmData): Unit = {
    map(RemusStateEstimator.RPM) = Some(msg.getRpm)
  }

  override def vehiclePowerUpdate(msg: RemusPowerState): Unit = {
    log.debug(s"State Estimator received energy remaining value of ${msg.getEnergyRemaining}")
    map(RemusStateEstimator.ENERGY_LEVEL) = Some(msg.getEnergyRemaining)
  }

  override def keys: Set[String] = ALL_KEYS

  override def valuesForKeys(keys: Set[String]): Map[String, Option[Double]] = map.retain((k, _) => keys.contains(k)).toMap
}

object RemusStateEstimator {
  val DVL_E = "dvl.e"
  val DVL_N = "dvl.n"
  val DVL_U = "dvl.u"
  val DVL_DEPTH = "dvl.depth"
  val DVL_PITCH = "dvl.pitch"
  val DVL_ROLL = "dvl.roll"
  val DVL_HEADING = "dvl.heading"

  val WATER_SPEED = "waterspeed"

  val RPM = "rpm"

  val ENERGY_LEVEL = "energylevel"

  val DVL_VARS = Set(DVL_E, DVL_N, DVL_U, DVL_DEPTH, DVL_PITCH, DVL_ROLL, DVL_HEADING)
  val WATERSPEED_VARS = Set(WATER_SPEED)
  val RPM_VARS = Set(RPM)
  val POWER_VARS = Set(ENERGY_LEVEL)
}