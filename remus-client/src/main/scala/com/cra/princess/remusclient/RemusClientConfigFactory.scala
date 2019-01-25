package com.cra.princess.remusclient

import java.io.IOException

import com.cra.princess.evaluation.{EvaluationMessenger, EvaluationScenarioManager}
import com.cra.princess.evaluation.messages.{CpInitialParams, LatLon}
import com.cra.princess.pathplanner.component.PPInput
import com.cra.princess.utility.math.LatLonConverter

class RemusClientConfigFactory {

  def createRemusClientConfig(json: String): RemusClientConfig = {
    val em = EvaluationMessenger.getInstance()
    val params = CpInitialParams.fromJson(json)

        val origin = LatLon(0.0, 0.0)

        val altitude = 90
        val fov = Math.toRadians(20.0)

        val ppInput = buildPPInput(origin, origin, origin, params.SearchRegion.LowerLeftLocation, params.SearchRegion.UpperRightLocation, altitude, fov)

        try {
          em.sendScenarioGenerationStartedMessage()
          EvaluationScenarioManager.generateCPScenario(params)
          em.sendScenarioGenerationCompletedMessage()
        } catch {
          case e: IOException =>
            em.sendScenarioGenerationFailureError(e.getMessage)
        }

        RemusClientConfig(ppInput, origin, origin, params.DVLSensorPerturbations, params.Adaptation)
  }

  def buildPPInput(origin: LatLon, startLocation: LatLon, destination: LatLon, lowerLeft: LatLon, upperRight: LatLon, altitude: Double, fov: Double): PPInput = {
    val llConv = new LatLonConverter(origin.Lat, origin.Lon)
    val startLocationXY = llConv.getXY(startLocation.Lat, startLocation.Lon)
    val destinationXY = llConv.getXY(destination.Lat, destination.Lon)

    val (lowerLeftX, lowerLeftY) = {
      val lowerLeftLat = lowerLeft.Lat
      val lowerLeftLon = lowerLeft.Lon
      val lowerLeftXY = llConv.getXY(lowerLeftLat, lowerLeftLon)
      (lowerLeftXY(0), lowerLeftXY(1))
    }
    val (upperRightX, upperRightY) = {
      val upperRightLat = upperRight.Lat
      val upperRightLon = upperRight.Lon
      val upperRightXY = llConv.getXY(upperRightLat, upperRightLon)
      (upperRightXY(0), upperRightXY(1))
    }

    PPInput(startLocationXY(0), startLocationXY(1), destinationXY(0), destinationXY(1), List(List(lowerLeftX, lowerLeftY),
      List(lowerLeftX, upperRightY), List(upperRightX, upperRightY),
      List(upperRightX, lowerLeftY)), altitude, fov, None, None)
  }

}
