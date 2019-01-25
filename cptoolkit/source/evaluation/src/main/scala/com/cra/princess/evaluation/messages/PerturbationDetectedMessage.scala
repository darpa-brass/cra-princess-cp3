package com.cra.princess.evaluation.messages

case class PerturbationDetectedMessage(Timestamp: String, Status: String, Message: PerturbationDetectedMessageBody) extends ToJson
object PerturbationDetectedMessage extends FromJson[PerturbationDetectedMessage]

case class PerturbationDetectedMessageBody(failedsensors: FailedSensorType) extends ToJson
object PerturbationDetectedMessageBody extends FromJson[PerturbationDetectedMessageBody]

case class FailedSensorType(id: String, ConfidenceOfFailure: Double)