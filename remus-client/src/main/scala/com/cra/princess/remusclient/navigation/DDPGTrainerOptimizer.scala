package com.cra.princess.remusclient.navigation

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.metron.remus.state.{RemusDvlData, RemusVehicleState}
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput
import com.cra.princess.optimizer.ComponentOptimizer
import com.cra.princess.training.ddpg.DDPGTrainer
import com.cra.princess.training.ddpg.structures.{Actor, Critic}
import com.cra.princess.training.training.TrainingState
import org.apache.commons.math3.linear.{ArrayRealVector, RealVector}

class DDPGTrainerOptimizer(actor: Actor, critic: Critic,
                           batchSize: Int, discountFactor: Double, delta: Double, saveFile: String, windowSize: Int)
  extends DDPGTrainer(actor, critic, batchSize, discountFactor, delta, saveFile)
    with ComponentOptimizer[PathFollowerEnvironment, PathFollowerInput]{

  private var stateWindow: Array[TrainingState] = Array.empty[TrainingState]
  private var totalSteps = 0
  private var episodeNum = 0
  private var destination: RealVector = _
  private var startLoc: RealVector = _
  private var estLoc: (Double, Double) = _
  private var prevGtState: RemusVehicleState = _
  private var currGtState: RemusVehicleState = _
  private var currentDVLState: RemusDvlData = _
  private var kfOutput: KalmanFilterOutput = _
  private var hasTerminated: Boolean = false

  override def apply(v1: PathFollowerEnvironment, v2: PathFollowerInput): ComponentControls = {

    val estVE = kfOutput.getState.getDeltaComponents.getEntry(0)
    val estVN = kfOutput.getState.getDeltaComponents.getEntry(1)
    val nextState = Array(destination.getEntry(0) - estLoc._1, destination.getEntry(1) - estLoc._2, estVE, estVN)

    val headingDeviation =
      if(stateWindow.nonEmpty && totalSteps < windowSize) {
        val currGtLoc = new ArrayRealVector(Array(currGtState.getTrueLatitude, currGtState.getTrueLongitude))
        val prevGtLoc = new ArrayRealVector(Array(prevGtState.getTrueLatitude, prevGtState.getTrueLongitude))
        trainStep(stateWindow.flatten, nextState, calculateReward(currGtLoc, prevGtLoc, startLoc, destination), hasTerminated)
        stateWindow = stateWindow.drop(0) ++ Array(nextState)
        calculateExploreExploitCtrls(stateWindow.flatten, totalSteps, episodeNum).head
      } else {
        stateWindow = stateWindow ++ Array(nextState)
        0.0
      }
    prevGtState = currGtState
    totalSteps += 1
    Map("headingDeviation" -> new BoundedScalarPrincessFeature(headingDeviation, 0, 0))
  }

  def setRemusVehicleState(rvs: RemusVehicleState): Unit =
    currGtState = rvs

  def setRemusDVLData(rdd: RemusDvlData): Unit =
    currentDVLState = rdd

  def setKfOutput(kfo: KalmanFilterOutput): Unit =
    kfOutput = kfo

  def setEstLoc(loc: LatLon): Unit =
    estLoc = (loc.Lon, loc.Lat)

  def setTerminated(): Unit =
    hasTerminated = true

  def reset(start: LatLon, dest: LatLon): Unit = {
    stateWindow = Array.empty[TrainingState]
    episodeNum += 1
    startLoc =  new ArrayRealVector(Array(start.Lon, start.Lat))
    destination = new ArrayRealVector(Array(dest.Lon, dest.Lat))
    hasTerminated = false
  }

  private def calculateReward(currentLoc: RealVector, prevLoc: RealVector,
                              start: RealVector, dest: RealVector): Double = {
    val baseVec = dest.subtract(start)
    val currVec = currentLoc.subtract(start)
    val prevVec = prevLoc.subtract(start)
    val currProj = currVec.projection(baseVec)
    val prevProj = prevVec.projection(baseVec)
    val prevNorm = prevProj.subtract(dest).getNorm
    val currNorm = currProj.subtract(dest).getNorm
    currNorm - prevNorm
  }
}

case class DDPGTrainerInput(rvs: RemusVehicleState, rdd: RemusDvlData, destination: LatLon, terminal: Boolean)