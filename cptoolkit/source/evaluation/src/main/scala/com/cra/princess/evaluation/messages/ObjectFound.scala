package com.cra.princess.evaluation.messages

case class ObjectFound(Timestamp: String, Status: String, Message: LatLon) extends ToJson
object ObjectFound extends FromJson[ObjectFound]