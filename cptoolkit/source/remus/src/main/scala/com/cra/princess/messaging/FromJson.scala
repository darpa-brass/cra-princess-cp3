package com.cra.princess.messaging

import net.liftweb.json.JsonParser.ParseException
import net.liftweb.json.{DefaultFormats, parse}

/**
  * Created by smarotta on 3/24/2017.
  */
class FromJson[T](implicit m: Manifest[T]) {
  private implicit val formats = DefaultFormats
  def fromJson(json: String): T =
    try
      parse(json).extract[T]
    catch {
      case e: ParseException => throw new SerializationException(s"JSON parse error: ${e.getMessage}", e)
    }
}
