package com.cra.princess.evaluation.messages

case class CP3SutFinishedStatus(Timestamp: String, Status: String, Results: CP3ResultsType) extends ToJson
object CP3SutFinishedStatus extends FromJson[CP3SutFinishedStatus]

case class CP3ResultsType(SufficientPower: Boolean, ObjectDetected: Boolean, Lat: Double, Lon: Double, DistanceFromDestination: Double) extends ToJson
object CP3ResultsType extends FromJson[CP3ResultsType]