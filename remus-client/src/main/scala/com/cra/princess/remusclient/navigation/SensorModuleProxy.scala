package com.cra.princess.remusclient.navigation

import com.cra.princess.kalmanfilter.KalmanFilterInputWrapper
import com.cra.princess.localizationalgorithm.components.ComponentState
import com.cra.princess.metron.remus.state.RemusDvlData
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector
import com.metsci.dynamic.simple.AffineTransform
import org.apache.commons.math3.linear.{ArrayRealVector, MatrixUtils, RealMatrix}

class SensorModuleProxy {

  def generateKalmanFilterInput(state: RemusDvlData, previousState: ComponentState, previousCovariance: RealMatrix, actuatorValues: KalmanFilterActuatorVector): KalmanFilterInputWrapper = {
    val worldVel = surgeSwayHeave2EastNorthUp(state)
    val observations = new ArrayRealVector(Array[Double](worldVel.east, worldVel.north))
    val ps = if (null == previousState)
                new ComponentState(new ArrayRealVector(Array(0.0, 0.0)), observations)
             else previousState
    val pc = if (null == previousCovariance)
                MatrixUtils.createRealIdentityMatrix(2)
             else
                previousCovariance
    val av = if (null == actuatorValues) new KalmanFilterActuatorVector(19200.0, 100.0, 0.0, 0.0, 0.0) else actuatorValues
    new KalmanFilterInputWrapper(ps, av, Seq(observations), 1.0, 0.0, pc)
  }

  private def surgeSwayHeave2EastNorthUp(state: RemusDvlData): ENU = {
    val (roll, pitch, yaw) = (Math.toRadians(state.getRoll), Math.toRadians(state.getPitch), Math.toRadians(state.getHeading))
    val bodyToWorld: AffineTransform = new AffineTransform(0, 0, 0, roll, pitch, yaw)
    val bodyVelocity = Array(state.getSurge, state.getSway, state.getHeave)
    val worldVelocity = bodyToWorld.transform(bodyVelocity)
    val (vE, vN, vU) = (worldVelocity(1), worldVelocity(0), -worldVelocity(2))
    ENU(vE, vN, vU)
  }
  
}

private case class ENU(east: Double, north: Double, up: Double)