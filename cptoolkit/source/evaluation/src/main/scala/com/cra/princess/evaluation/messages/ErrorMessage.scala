package com.cra.princess.evaluation.messages

case class ErrorMessage(Timestamp: String, Error: String, Message: String) extends ToJson
object ErrorMessage extends FromJson[ErrorMessage]