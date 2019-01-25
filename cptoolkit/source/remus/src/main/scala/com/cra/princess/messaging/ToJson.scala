package com.cra.princess.messaging

import net.liftweb.json.{DefaultFormats, Serialization}

/**
  * Created by smarotta on 3/24/2017.
  */
trait ToJson {
  private implicit val formats = DefaultFormats
  def toJson = Serialization.write(this)
}
