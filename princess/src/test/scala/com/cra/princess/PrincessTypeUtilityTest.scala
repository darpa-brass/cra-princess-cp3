package com.cra.princess

import com.cra.princess.core.{MatrixPrincessFeature, ScalarPrincessFeature, VectorPrincessFeature}
import com.cra.princess.util.PrincessTypeUtility
import org.scalatest.FlatSpec
import org.scalatest.Matchers
import org.apache.commons.math3.linear._

class PrincessTypeUtilityTest extends FlatSpec with Matchers {
  
  "PrincessTypeUtility" should "properly flatten and unflatten scalars" in {
    val scalarElt = new ScalarPrincessFeature(1)
    PrincessTypeUtility.flatten(scalarElt) should equal(Seq(1))
    PrincessTypeUtility.unflatten(scalarElt, PrincessTypeUtility.flatten(scalarElt)).asInstanceOf[ScalarPrincessFeature].value should equal(1)
  }
  
  it should "properly flatten and unflatten vectors" in {
    val vectorElt = new VectorPrincessFeature(new ArrayRealVector(Array(1.0, 2, 3, 4)))
    PrincessTypeUtility.flatten(vectorElt) should equal(Seq(1, 2, 3, 4))
    val roundTrip = PrincessTypeUtility.unflatten(vectorElt, PrincessTypeUtility.flatten(vectorElt)).asInstanceOf[VectorPrincessFeature].value
    roundTrip.getEntry(0) should equal(1.0)
    roundTrip.getEntry(1) should equal(2.0)
    roundTrip.getEntry(2) should equal(3.0)
    roundTrip.getEntry(3) should equal(4.0)
  }
  
  it should "flatten and unflatten matrices in row-major order" in {
    val matrixElt = new MatrixPrincessFeature(new Array2DRowRealMatrix(Array(Array(1.0, 2), Array(3.0, 4))))
    PrincessTypeUtility.flatten(matrixElt) should equal(Seq(1.0, 2, 3, 4))
    val roundTrip = PrincessTypeUtility.unflatten(matrixElt, PrincessTypeUtility.flatten(matrixElt)).asInstanceOf[MatrixPrincessFeature].value
    roundTrip.getEntry(0, 0) should equal(1.0)
    roundTrip.getEntry(0, 1) should equal(2.0)
    roundTrip.getEntry(1, 0) should equal(3.0)
    roundTrip.getEntry(1, 1) should equal(4.0)    
  }  
}