package com.cra.princess.remusclient.navigation

import com.cra.princess.components.kalmanfilter.{KalmanFilterComponent, KalmanFilterComponentImpl}
import com.cra.princess.core.ScenarioController
import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper, KalmanFilterOptimizer}
import com.cra.princess.localizationalgorithm.components.ComponentState
import com.cra.princess.messaging.types.Location
import com.cra.princess.metron.MetronRemusManager
import com.cra.princess.metron.remus.state.RemusDvlData
import com.cra.princess.models.kalmanfiltercomponents.{KalmanFilterActuatorVector, KalmanFilterEnvironment, KalmanFilterOutput}
import com.cra.princess.remusclient.util.RemusUtils
import com.cra.princess.util.{Logs, PrincessProperties}
import com.cra.princess.utility.math.LatLonConverter
import org.apache.commons.math3.linear.{ArrayRealVector, RealMatrix}

class Localization(controller: ScenarioController, startingLat: Double = 0.0, startingLon: Double = 0.0) extends Logs {

  private var previousState: ComponentState = _
  private var previousCovariance: RealMatrix = _
  private val sensor = new SensorModuleProxy
  private var (total_dN, total_dE) = (0.0, 0.0)
  private var count = 0
  private var timestamp = -1L
  private val llConv = new LatLonConverter(startingLat, startingLon)
  private val kalmanFilter = this.buildKalmanFilterComponent
  controller.registerAdaptationEventHandler(kalmanFilter, RemusUtils.generateAdaptationEventHandler("Kalman Filter"))

  private var estVE = 0.0
  private var estVN = 0.0

  private[remusclient] def getEstVE = estVE
  private[remusclient] def getEstVN = estVN

  def updateLocation(dvlData: RemusDvlData, actuatorValues: KalmanFilterActuatorVector): LatLon = {
    val kfi = sensor.generateKalmanFilterInput(dvlData, previousState, previousCovariance, actuatorValues)
    val output = {
      val rawOut = if (count < 2)
        initOutput(kfi.state.getStateComponents.getEntry(0), kfi.state.getStateComponents.getEntry(1))
      else kalmanFilter.component(new KalmanFilterEnvironmentWrapper(new KalmanFilterEnvironment(0.0, 0.0)), kfi, null)
      val (dN, dE) = {
        val dT = if (timestamp == -1L) 1000 else dvlData.getTimestamp - timestamp
        log.debug(s"dT = $dT")
        val (vE, vN) = (rawOut.getState.getDeltaComponents.getEntry(0), rawOut.getState.getDeltaComponents.getEntry(1))
        estVE = vE
        estVN = vN
        val seconds = dT / 1000.0
        (vN * seconds, vE * seconds)
      } // this is the distance we've traveled since the last dvlSensorUpdate

      // Add current delta to total deltas
      this.total_dE += dE
      this.total_dN += dN

      // Calculate lat/lon from total distance traveled in each direction
      val (newLat, newLon) = {
        llConv.getLatLon(this.total_dN, this.total_dE) match {
          case a: Array[Double] =>
            if (a.length == 2) (a(0), a(1))
            else throw new IllegalStateException("LatLonConverter returned array of incorrect size")
          case _ => throw new IllegalStateException("Did not get an array from LatLonConverter")
        }
      }

      // Update last known timestamp from the sim
      this.timestamp = dvlData.getTimestamp
      val newState = new ComponentState(new ArrayRealVector(Array[Double](newLat, newLon)), rawOut.getState.getDeltaComponents)
      new KalmanFilterOutput(newState, rawOut.getCovariance, rawOut.getMeasurementResidual)
    }
    this.previousState = output.getState
    this.previousCovariance = output.getCovariance
    count += 1

    // Send estimated position via ActiveMQ
    val mrm = MetronRemusManager.getInstance
    val loc = new Location(output.getState.getStateComponents.getEntry(0), output.getState.getStateComponents.getEntry(1), dvlData.getTimestamp)
    mrm.sendEstimatedLocation(loc)

    val (lat, lon) = output.getState.getStateComponents match {
      case vec: ArrayRealVector => (vec.getEntry(0), vec.getEntry(1))
    }

    new LatLon(lat, lon)
  }

  private def buildKalmanFilterComponent: KalmanFilterComponent = {
    val (optimizer, threshold) = (new KalmanFilterOptimizer(netFile = Some(PrincessProperties.kfOptimizerFile)), 0.0)
    controller.buildWrappedComponent[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper, KalmanFilterOutput, KalmanFilterComponent](
      new KalmanFilterComponentImpl(threshold), optimizer)
  }

  private def initOutput(vE: Double, vN: Double) = new KalmanFilterOutput(new ComponentState(new ArrayRealVector(Array[Double](0.0, 0.0)),
    new ArrayRealVector(Array[Double](vE, vN))),
    null,
    new ArrayRealVector(Array[Double](0.0, 0.0)))

}
