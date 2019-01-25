package com.cra.princess.evaluation.messages

case class LatLon(Lat: Double, Lon: Double) extends ToJson
object LatLon extends FromJson[LatLon]
