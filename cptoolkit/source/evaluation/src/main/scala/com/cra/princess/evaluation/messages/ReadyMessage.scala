package com.cra.princess.evaluation.messages

case class ReadyMessage(Timestamp: String) extends ToJson
object ReadyMessage extends FromJson[ReadyMessage]
