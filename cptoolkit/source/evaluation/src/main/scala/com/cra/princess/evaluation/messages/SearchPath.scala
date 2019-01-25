package com.cra.princess.evaluation.messages

case class SearchPath(Timestamp: String, MaxSpeed: String, Waypoints: List[LatLon]) extends ToJson
object SearchPath extends FromJson[SearchPath]
