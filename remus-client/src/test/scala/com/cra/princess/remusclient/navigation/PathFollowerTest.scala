package com.cra.princess.remusclient.navigation

import com.cra.princess.evaluation.messages.LatLon
import com.cra.princess.pathplanner.Waypoint
import com.cra.princess.remusclient.navigation.PathFollower.{DESTINATION_REACHED, WAYPOINT_REACHED}
import org.scalatest.{FlatSpec, Matchers}

class PathFollowerTest extends FlatSpec with Matchers {

  var waypointsReached: Int = 0
  var destinationsReached: Int = 0

  "A PathFollower" should "generate actuator values to direct the client to follow a given path" in {
    var wps = List[Waypoint](new Waypoint(-1.0, -1.0),
      new Waypoint(-1.0, 1.0),
      new Waypoint(1.0, 1.0),
      new Waypoint(1.0, -1.0))

    var pf: PathFollower = new PathFollower(new Waypoint(0.0, 0.0), wps)
    pf.addListener(handleEvent)

    waypointsReached = 0
    destinationsReached = 0
    var av = pf.generateActuatorVector(LatLon(0.0, 0.0))
    av.getEntry(4) should be(225.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(-0.5, -0.5))
    av.getEntry(4) should be(225.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(-1.0, -1.0))
    waypointsReached should be(1)
    destinationsReached should be(0)
    av.getEntry(4) should be(90.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(0.0, 0.0))
    av.getEntry(4) should be(135.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(-1.1, 1.0))
    av.getEntry(4) should be(0.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(-1.000005, 1.0))
    waypointsReached should be(2)
    destinationsReached should be(0)
    av.getEntry(4) should be(0.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(0.0, 0.0))
    av.getEntry(4) should be(45.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(1.0, 1.01))
    av.getEntry(4) should be(270.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(1.01, 1.0))
    av.getEntry(4) should be(180.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(1.0, 0.999991))
    waypointsReached should be(3)
    destinationsReached should be(0)
    av.getEntry(4) should be(270.0 +- 0.01)
    av.getEntry(0) should be(19200.0)
    av = pf.generateActuatorVector(LatLon(1.0, -1.0))
    waypointsReached should be(4)
    destinationsReached should be(1)
    av.getEntry(4) should be(0.0)
    av.getEntry(0) should be(0.0)

    av = pf.generateActuatorVector(LatLon(1.0, 1.0))
    waypointsReached should be (4)
    destinationsReached should be (1)
    av.getEntry(4) should be (0.0)
    av.getEntry(0) should be (0.0)
  }

  it should "generate a bounding box containing all remaining points in the queue" in {
    var wps = List[Waypoint](new Waypoint(0.0, 0.0),
      new Waypoint(9.0, 0.0),
      new Waypoint(9.0, 2.0),
      new Waypoint(0.0, 2.0),
      new Waypoint(0.0, 4.0),
      new Waypoint(9.0, 4.0),
      new Waypoint(9.0, 6.0),
      new Waypoint(0.0, 6.0),
      new Waypoint(0.0, 8.0),
      new Waypoint(9.0, 8.0),
      new Waypoint(9.0, 10.0),
      new Waypoint(0.0, 10.0),
      new Waypoint(0.0, 0.0))

    var pf: PathFollower = new PathFollower(new Waypoint(0.0, 0.0), wps)
    pf.generateActuatorVector(LatLon(0.0, 0.0))
    pf.generateActuatorVector(LatLon(9.0, 0.0))
    pf.generateActuatorVector(LatLon(9.0, 2.0))
    pf.generateActuatorVector(LatLon(0.0, 2.0))

    val bb = pf.generateRemainingPathBoundingBox()
    bb match {
      case Some(bbox) =>
        bbox.minLat should equal (0.0)
        bbox.minLon should equal (4.0)
        bbox.maxLat should equal (9.0)
        bbox.maxLon should equal (10.0)
      case None => fail
    }
  }

  def handleEvent(e: PathEvent): Unit = {
    e.eventType match {
      case WAYPOINT_REACHED => waypointsReached += 1
      case DESTINATION_REACHED => destinationsReached += 1
      case _ => throw new IllegalStateException("This should not have happened")
    }
    println(s"path event occurred: ${e.eventType}")
  }

}
