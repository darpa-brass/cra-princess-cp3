package com.cra.princess.core

case class VerificationEvent(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], result: VerificationResult)

trait VerificationEventListener {
  def handleVerificationEvent(e: VerificationEvent)
}
