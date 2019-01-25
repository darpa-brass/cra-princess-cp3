package com.cra.princess.evaluation.messages

case class DvlSensorPerturbationType(TimeIntoScenario: Int, SensorName: String, SensorBias: Double, SensorNoise: Double, SensorAnchor: Double, SensorAnchorProbability: Double) extends ToJson
object DvlSensorPerturbationType extends FromJson[DvlSensorPerturbationType]