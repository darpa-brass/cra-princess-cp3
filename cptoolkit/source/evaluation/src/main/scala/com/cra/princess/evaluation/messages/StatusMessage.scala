package com.cra.princess.evaluation.messages

case class StatusMessage(Timestamp: String, Status: String, Message: String) extends ToJson
object StatusMessage extends FromJson[StatusMessage]
