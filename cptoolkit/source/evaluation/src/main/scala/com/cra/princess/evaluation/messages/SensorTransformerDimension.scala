package com.cra.princess.evaluation.messages

case class SensorTransformerDimension(timestamp: Long, dimension: String, failuretype: Int, confidence: Double) extends ToJson
object SensorTransformerDimension extends FromJson[SensorTransformerDimension]
