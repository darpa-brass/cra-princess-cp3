package com.cra.princess.core

import com.cra.princess.ComponentControls

case class OptimizationEvent(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], controlVariables: ComponentControls) {}
case class AdaptationStatusEvent(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], state: AdaptationState)

trait OptimizationEventListener {
  def handleOptimization(e: OptimizationEvent)
  def handleAdaptationStatus(a: AdaptationStatusEvent)
}
