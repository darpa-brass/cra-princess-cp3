package com.cra.princess.evaluation.messages

import org.scalatest.{FlatSpec, Matchers}

class ReadyMessageTest extends FlatSpec with Matchers {

  "A ReadyMessage" should "serialize and deserialize" in {

    val rm = new ReadyMessage("1000")
    val json = """{"Timestamp":"1000"}"""
    rm.toJson should equal (json)
    ReadyMessage.fromJson(json) should equal (rm)

  }

}
