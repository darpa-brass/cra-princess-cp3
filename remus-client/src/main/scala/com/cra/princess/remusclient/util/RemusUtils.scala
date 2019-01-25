package com.cra.princess.remusclient.util

import com.cra.princess.core.{ADAPTATION_COMPLETE, ADAPTATION_STARTED, AdaptationState, INTENT_VIOLATION_DETECTED}
import com.cra.princess.evaluation.EvaluationMessenger

object RemusUtils {

  private val em = EvaluationMessenger.getInstance()

  def distance(x1: Double, y1: Double, x2: Double, y2: Double): Double = {
    val xDiff = x2 - x1
    val yDiff = y2 - y1
    Math.sqrt(xDiff * xDiff + yDiff * yDiff)
  }

  def generateAdaptationEventHandler(componentName: String): AdaptationState => Unit = {
    (s: AdaptationState) => {
      s match {
        case INTENT_VIOLATION_DETECTED => em.sendIntentViolationDetectedMessage(componentName)
        case ADAPTATION_STARTED => em.sendAdaptationStartedMessage(componentName)
        case ADAPTATION_COMPLETE => em.sendAdaptationCompletedMessage(componentName)
        case _ => throw new IllegalArgumentException("Unknown adaptation state")
      }
    }
  }
}
