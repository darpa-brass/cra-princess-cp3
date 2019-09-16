package com.cra.princess.scenario

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

class CartpoleSimulator(val resultsFileName: String, val maxSteps: Int) extends Simulator{
  val gravity = 9.8
  val massCart = 1.0
  val massPole = 0.1
  val totalMass = massPole + massCart
  val halfLength = 0.5 // half the pole's length
  val poleMassLength = massPole * halfLength
  val forceMag = 30.0
  val secondsBetweenStateUpdates = 0.02 // seconds between state updates
  val minAction = -1.0
  val maxAction = 1.0

  val thetaThresholdRadians = 12.0 * 2.0 * Math.PI / 360.0 // failure angle in radians
  val xThreshold = 2.4 // failure distance
  val high: Array[Double] = Array(xThreshold*2.0, Double.MaxValue, thetaThresholdRadians*2.0, Double.MaxValue)

  def stepPhysics(force: Double): TrainingState = {
    val (x, xDot, theta, thetaDot) = (state(0), state(1), state(2), state(3))
    val cosTheta = Math.cos(theta)
    val sinTheta = Math.sin(theta)
    val temp = (force + poleMassLength * thetaDot * thetaDot * sinTheta) / totalMass
    val thetaAcc = (gravity * sinTheta - cosTheta * temp) /
                   (halfLength * (4.0/3.0 - massPole * cosTheta * cosTheta / totalMass))
    val xAcc = temp - poleMassLength * thetaAcc * cosTheta / totalMass

    val nextX = x + secondsBetweenStateUpdates * xDot
    val nextXDot = xDot + secondsBetweenStateUpdates * xAcc
    val nextTheta = theta + secondsBetweenStateUpdates * thetaDot
    val nextThetaDot = thetaDot + secondsBetweenStateUpdates * thetaAcc
    Array(nextX, nextXDot, nextTheta, nextThetaDot)
  }

  def step(explorationAction: List[TrainingControls]): (TrainingControls, TrainingState, TrainingMetric, Boolean) = {
    val action = explorationAction.head(0) //if(explorationAction(0) > 1.0) 1.0 else if (explorationAction(0) < -1.0) -1.0

    val force = forceMag * action
    state = stepPhysics(force)
    val x = state(0)
    val theta = state(2)
    val done = (x < -xThreshold) ||
               (x > xThreshold) ||
               (theta < -thetaThresholdRadians) ||
               (theta > thetaThresholdRadians)
    val reward = if(!done) {
      1.0//1.0/(1.0 + Math.abs(theta))
    } else if (stepsBeyondDone.isEmpty) {
      stepsBeyondDone = Some(0)
      1.0//1.0/(1.0 + Math.abs(theta))
    } else {
      stepsBeyondDone = Some(stepsBeyondDone.get + 1)
      0.0
    }
    (Array(action), state, reward, done)
  }
}