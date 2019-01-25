package com.cra.princess.remusclient.navigation

import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicReference

import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.metron.remus.state.{ObjectDetectionListener, RemusObjectDetectionState}
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterActuatorVector
import com.cra.princess.pathplanner.Waypoint
import com.cra.princess.remusclient.util.RemusUtils
import com.cra.princess.util.Logs

import scala.collection.JavaConverters._

class PathFollower(home: Waypoint, path: List[Waypoint]) extends ObjectDetectionListener with Logs {

  if (path.length < 1) log.warn("PathFollower given an empty path")

  private var listeners: List[PathEvent => Unit] = Nil
  private val pointQueue: ConcurrentLinkedQueue[Waypoint] = new ConcurrentLinkedQueue[Waypoint](path.asJava)
  private val epsilon = 0.00007
  private val initialActuatorValues = new KalmanFilterActuatorVector(19200, 100.0, 0.0, 0.0, 0.0)
  private val isHolding: AtomicReference[Boolean] = new AtomicReference(false)
  private var holdLocation: Option[Waypoint] = None

  def generateActuatorVector(latLon: LatLon): KalmanFilterActuatorVector = {
    val (lat, lon) = (latLon.Lat, latLon.Lon)

    pointQueue.synchronized {
      if (!pointQueue.isEmpty) {
        val nextWp = holdLocation match {
          case Some(loc) => loc
          case None => pointQueue.peek()
        }
        log.debug(s"Current location: ($lat, $lon)")
        log.debug(s"Current waypoint: (${nextWp.getNorth}, ${nextWp.getEast})")
        val distance = RemusUtils.distance(lat, lon, nextWp.getNorth, nextWp.getEast)
        log.debug("Distance to waypoint: " + distance)
        if (distance < epsilon && !this.isHolding.get) {
          fireWaypointReached(nextWp)
          // Dequeue waypoint from list - if the list is empty, fire DESTINATION_REACHED
          val wp = pointQueue.poll()
          if (pointQueue.isEmpty) fireDestinationReached(wp)
        }
      }

      if (!pointQueue.isEmpty || this.holdLocation.isDefined) {
        // Calculate heading based on the front of the queue
        val wp = this.holdLocation match {
          case Some(loc) => loc
          case None => pointQueue.peek()
        }
        val heading = calcHeading(lat, lon, wp.getNorth, wp.getEast)
        new KalmanFilterActuatorVector(initialActuatorValues.getEntry(0),
          initialActuatorValues.getEntry(1),
          initialActuatorValues.getEntry(2),
          initialActuatorValues.getEntry(3),
          heading)
      } else {
        new KalmanFilterActuatorVector(0,
          initialActuatorValues.getEntry(1),
          initialActuatorValues.getEntry(2),
          initialActuatorValues.getEntry(3),
          0)
      }
    }
  }

  private[remusclient] def generateRemainingPathBoundingBox(): Option[BoundingBox] = {
    def helper(bbox: Option[BoundingBox], points: List[Waypoint]): Option[BoundingBox] = {
      points match {
        case p :: ps =>
          bbox match {
            case None => helper(Some(BoundingBox(p.getNorth, p.getEast, p.getNorth, p.getEast)), ps)
            case Some(bb) =>
              val minLat = if (p.getNorth < bb.minLat) p.getNorth else bb.minLat
              val minLon = if (p.getEast < bb.minLon) p.getEast else bb.minLon
              val maxLat = if (p.getNorth > bb.maxLat) p.getNorth else bb.maxLat
              val maxLon = if (p.getEast > bb.maxLon) p.getEast else bb.maxLon
              helper(Some(BoundingBox(minLat, minLon, maxLat, maxLon)), ps)
          }
        case _ => bbox
      }
    }
    // We need to ignore the last point because the last point in the path is the return location
    if (!this.pointQueue.isEmpty) helper(None, this.pointQueue.asScala.toList.init)
    else None
  }

  private[remusclient] def updatePath(newPath: java.util.List[Waypoint]) = {
    // put a lock here so that generateActuatorVector has to wait until this call is finished
    pointQueue.synchronized {
      this.pointQueue.clear()
      this.pointQueue.addAll(newPath)
    }
  }

  def holdAtLocation(location: Waypoint): Unit = {
    if (!this.isHolding.get) {
      this.setHolding(true)
      this.holdLocation = Some(location)
    }
  }

  def resumePath(): Unit = {
    if (this.isHolding.get) {
      this.setHolding(false)
      this.holdLocation = None
    }
  }

  private def setHolding(isHolding: Boolean): Unit = {
    if (this.isHolding.get != isHolding) this.isHolding.set(isHolding)
  }

  private[remusclient] def currentWaypoint: Option[Waypoint] =
    if (pointQueue.size >= 1) Some(pointQueue.peek()) else None

  private[remusclient] def numRemainingWaypoints: Int = pointQueue.size

  private def deg2rad(lat1: Double, lon1: Double, lat2: Double, lon2: Double): (Double, Double, Double, Double) =
    (lat1.toRadians, lon1.toRadians, lat2.toRadians, lon2.toRadians)

  private def makePositive(heading: Double): Double = {
    if (heading >= 0) heading else makePositive(heading + 360.0)
  }

  /**
    * Takes two lat/lon values in degrees and returns the heading from (lat1, lon1) to (lat2, lon2) in degrees
    */
  private[remusclient] def calcHeading(lat1: Double, lon1: Double, lat2: Double, lon2: Double): Double = {
    val radians = Math.atan2(lat2 - lat1, lon2 - lon1)
    makePositive(-Math.toDegrees(radians)+90)
  }

  def addListener(l: PathEvent => Unit): Unit = listeners ::= l

  private def fireWaypointReached(wp: Waypoint): Unit = listeners.foreach(_.apply(PathEvent(PathFollower.WAYPOINT_REACHED, wp)))
  private def fireDestinationReached(wp: Waypoint): Unit = listeners.foreach(_.apply(PathEvent(PathFollower.DESTINATION_REACHED, wp)))

  override def objectDetected(objectDetectionMessage: RemusObjectDetectionState): Unit = {
    this.pointQueue.clear()
    this.pointQueue.add(home)
  }
}

object PathFollower {
  sealed trait EventType
  case object WAYPOINT_REACHED extends EventType
  case object DESTINATION_REACHED extends EventType
}

case class PathEvent(eventType: PathFollower.EventType, waypoint: Waypoint)
case class BoundingBox(minLat: Double, minLon: Double, maxLat: Double, maxLon: Double)