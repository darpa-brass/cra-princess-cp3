package com.cra.princess.evaluation.messages

case class PerturbingCurrentType(LowerLeftLocation: LatLon, UpperRightLocation: LatLon, vE: Double, vN: Double) extends ToJson
object PerturbingCurrentType extends FromJson[PerturbingCurrentType]