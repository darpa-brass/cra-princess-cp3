package com.cra.princess.remusclient.verifier

import java.util

import com.cra.princess.core.VerificationResult
import com.cra.princess.optimizer.StateEstimator
import com.cra.princess.pathplanner.Waypoint
import com.cra.princess.remusclient.RemusStateEstimator
import com.cra.princess.util.{Logs, Recognizer}
import com.cra.princess.verifier.{BatteryModel, Verifier}
import prism.{Prism, PrismDevNullLog}

import scala.collection.JavaConverters._


class PrismVerifier(model: String, properties: String, stateEstimator: StateEstimator) extends Verifier with Logs {

  private val prism = new Prism(new PrismDevNullLog())
  prism.initialise()
  prism.setEngine(Prism.EXPLICIT)


  override def verify(output: Any): VerificationResult = {

    val stateVariables = stateEstimator.valuesForKeys(stateEstimator.keys) // TODO do something with these values

    // we require a RemusStateEstimator object, for this verification instance
    val initialBatteryWattHrs = stateVariables.get(RemusStateEstimator.ENERGY_LEVEL) match {
      case None | Some(None) => return VerificationResult(false)
      case Some(Some(num)) => num.toInt
    }

    //cast output to waypoints
    val waypoints = output match{
      case b :scala.runtime.BoxedUnit  => return VerificationResult(false)
      case l: java.util.ArrayList[_] => {
        if (Recognizer.recognizeSeq[Waypoint](l.asScala)) {
          l.asInstanceOf[java.util.ArrayList[Waypoint]].asScala
        } else {
          log.error("Waypoints must be a Java list of Waypoint")
          throw new IllegalArgumentException("Waypoints must be a Java list of Waypoint")
        }
      }
    }

    val geodeticWaypoints: util.ArrayList[Array[Double]] = new util.ArrayList[Array[Double]]
    for (waypoint <- waypoints) geodeticWaypoints.add(Array[Double](waypoint.getNorth, waypoint.getEast, 0))

    val property: String = "P=?[F \"home\"]"

    val bm : BatteryModel = new BatteryModel(initialBatteryWattHrs,geodeticWaypoints)
    prism.loadModelGenerator(bm)

    val result = prism.modelCheck(property)

    log.debug(s"Probability of returning home :  ${result.getResult}")

    val success = result.getResult.asInstanceOf[Double] >= 0.9

    log.debug(s"Property satisfied? : $success")

    VerificationResult(success.booleanValue())
  }
}


