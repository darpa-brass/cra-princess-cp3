package com.cra.princess.util

import com.cra.princess.{ComponentControls, Control}
import org.scalatest.{FlatSpec, Matchers}
import scala.collection.JavaConverters._

class RecognizerTest extends FlatSpec with Matchers {

  "A Recognizer" should "match aliased types" in {
    val cc: ComponentControls = Map.empty
    val m: Map[String, Control] = Map.empty
    val o: Any = m
    Recognizer.recognize[ComponentControls](cc) should equal (true)
    Recognizer.recognize[ComponentControls](m) should equal (true)
    Recognizer.recognize[ComponentControls](o) should equal (true)

    Recognizer.recognize[String](cc) should equal (false)
    Recognizer.recognize[String](m) should equal (false)
    Recognizer.recognize[String](o) should equal (false)

    Recognizer.recognize[Any](cc) should equal (true)
    Recognizer.recognize[Any](m) should equal (true)
    Recognizer.recognize[Any](o) should equal (true)

    val list = new java.util.ArrayList[String]
    list.add("foo")
    Recognizer.recognize[java.util.ArrayList[_]](list) should equal (true)
    Recognizer.recognizeSeq[String](list.asScala) should equal (true)
    Recognizer.recognizeSeq[Boolean](list.asScala) should equal (false)
  }

}
