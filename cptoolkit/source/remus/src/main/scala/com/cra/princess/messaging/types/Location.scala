package com.cra.princess.messaging.types

import com.cra.princess.messaging.{FromJson, ToJson}

/**
  * Created by smarotta on 5/3/2017.
  */
case class Location(lat: Double, lon: Double, timestamp: Long) extends ToJson
object Location extends FromJson[Location]
