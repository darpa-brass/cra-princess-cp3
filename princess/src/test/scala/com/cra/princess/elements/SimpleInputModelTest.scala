package com.cra.princess.elements

import org.scalatest.FlatSpec
import org.scalatest.Matchers
import com.cra.princess.inputmodel.SimpleInputModel

class SimpleInputModelTest extends FlatSpec with Matchers {
  
  val environment = List(1, 2, 3, 1, 2)
  val input = List("a", "b", "c", "b", "c")
  
  "SimpleInputModel" should "return a sample that is in the input" in {
    val model = SimpleInputModel(environment, input)
    val rand = model.generateRandomness()
    val eltVal = model.generateValue(rand)
    assert(environment.contains(eltVal._1))
    assert(input.contains(eltVal._2))
  }
  
  it should "return zero density for values outside the input" in {
    val model = SimpleInputModel(environment, input)
    model.density((4, "a")) should equal(0)
    model.density((1, "d")) should equal(0)
    model.density((4, "d")) should equal(0)
  }
  
  it should "return non-zero density for values within the input" in {
    val model = SimpleInputModel(environment, input)
    var totalMass:Double = 0
    for { x:Int <- environment.toSet; y:String <- input.toSet } {
      val curDensity = model.density((1, "a"))
      totalMass += curDensity
      curDensity should be(1.0 / 9 +- 1e-4)
    }
    totalMass should be(1.0 +- 1e-5)
  }
  
}