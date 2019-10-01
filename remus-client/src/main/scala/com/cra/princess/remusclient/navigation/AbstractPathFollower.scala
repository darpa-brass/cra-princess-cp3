package com.cra.princess.remusclient.navigation
import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.metron.remus.state.RemusObjectDetectionState
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector
import com.cra.princess.pathplanner.Waypoint

trait AbstractPathFollower {

  def generateActuatorVector(latLon: LatLon): KalmanFilterActuatorVector

  def holdAtLocation(location: Waypoint): Unit

  def resumePath(): Unit

  def addListener(l: PathEvent => Unit): Unit

  def objectDetected(objectDetectionMessage: RemusObjectDetectionState): Unit

  private[remusclient] def numRemainingWaypoints: Int

  private[remusclient] def currentWaypoint: Option[Waypoint]

  private[remusclient] def updatePath(newPath: java.util.List[Waypoint]): Boolean
}
