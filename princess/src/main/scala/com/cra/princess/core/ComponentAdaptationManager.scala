package com.cra.princess.core

import java.util.UUID

import com.cra.princess.ComponentControls
import com.cra.princess.monitor.{IntentResultListener, VerificationResultListener}
import com.cra.princess.optimizer.{ComponentOptimizer, Trainable}
import com.cra.princess.util.Logs
import com.cra.princess.verifier.Verifier

import scala.collection.mutable
import scala.collection.mutable.ListBuffer

class ComponentAdaptationManager[Env <: PrincessFeature, Input <: PrincessFeature, Output](val component: OptimizableComponent[Env, Input, Output],
                                                                                           val optimizer: ComponentOptimizer[Env, Input],
                                                                                           val inputProvider: Option[() => Option[Input]] = None) extends Logs {

  val uuid = UUID.randomUUID()
  private var verifier: Option[Verifier] = None

  private val intentListeners: mutable.ListBuffer[IntentResultListener] = ListBuffer.empty
  private val verificationListeners: mutable.ListBuffer[VerificationEventListener] = ListBuffer.empty
  private val optimizationEventListeners: mutable.ListBuffer[OptimizationEventListener] = ListBuffer.empty
  def addIntentListener(listener: IntentResultListener): Unit = intentListeners += listener
  def addVerificationListener(listener: VerificationEventListener): Unit = verificationListeners += listener
  def addOptimizationEventListener(listener: OptimizationEventListener): Unit = optimizationEventListeners += listener
  private def notifyIntentListeners(result: IntentResult): Unit = intentListeners.foreach(_(result))
  private def fireVerificationEvent(event: VerificationEvent): Unit = verificationListeners.foreach(_.handleVerificationEvent(event))
  private def fireOptimizationEvent(event: OptimizationEvent): Unit = optimizationEventListeners.foreach(_.handleOptimization(event))
  private def fireAdaptationStatusEvent(event: AdaptationStatusEvent): Unit = optimizationEventListeners.foreach(_.handleAdaptationStatus(event))
  private var currentInput: Input = _
  private var currentEnvironment: Env = _
  private var currentOutput: Output = _

  def setVerifier(verifier: Verifier): Unit = {
    this.verifier = Some(verifier)
  }

  val MAX_VERIFICATION_FAILURES = 100
  var verificationFailures = 0
  def handleComponentIO(env: Env, in: Input, out: Output): Unit = {
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ANALYSIS_STARTED))

    // Store env and input for later use by optimizer
    this.currentEnvironment = env
    this.currentInput = in
    this.currentOutput = out

    val metrics = component.metricCalculator(env, in, out)
    val result = component.satisfiesIntent(metrics)
    if (!result.pass) {
      fireAdaptationStatusEvent(AdaptationStatusEvent(component, INTENT_VIOLATION_DETECTED))
      notifyIntentListeners(result)
    } else log.debug("IntentResult = true")
    // If this component has a Verifier, pass output to the Verifier for verification
    this.verifier match {
      case Some(v) =>
        var verification = new VerificationResult(true)
        if(verificationFailures < MAX_VERIFICATION_FAILURES) {
          verification = v.verify(out)
        }
        if(verification.pass) {
          verificationFailures = 0
        } else {
          verificationFailures += 1
        }
        log.debug(s"Verification result = ${verification.pass}")
        fireVerificationEvent(VerificationEvent(this.component, verification))
      case None =>
    }

    log.debug("handleComponentIO complete")
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ANALYSIS_COMPLETE))
  }

  def handleExceptionResult(): Unit = {
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ANALYSIS_STARTED))
    log.error(s"Component $component threw exception. No analysis performed.")
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ANALYSIS_COMPLETE))
  }

  def optimize(): Unit = {
    log.debug(s"Component optimizing - $component")
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ADAPTATION_STARTED))
    // update optimizer with new intent (for thresholds)
    optimizer.intent = this.component.intent()
    // run optimizer and set new controls (if there are any)
    val newInput: Option[Input] = inputProvider match {
      case Some(ip) => ip() match {
        case Some(in) => Some(in)
        case None => None
      }
      case None => Some(this.currentInput)
    }
    val newControls: ComponentControls = newInput match {
      case Some(in) =>
        optimizer match {
          case trainableOpt: Trainable[Input, Output] =>
            try {
              trainableOpt.train(in, currentOutput)
            } catch {
              case e: IllegalArgumentException =>
                log.error(s"Trainer encountered an exception: ${e.getMessage}")
            }
          case _ => {}
        }
        try {
          optimizer(currentEnvironment, in)
        } catch {
          case e: Exception =>
            log.error(s"Exception caught during component optimization: ${e.getMessage}")
            null
        }
      case None => {
        log.warn("Component unable to generate new inputs")
        null
      }
    }
    log.debug(s"New control variables = $newControls")
    if (newControls != null) {
      if(newControls.nonEmpty) {
        this.component.updateControls(newControls)
        fireOptimizationEvent(OptimizationEvent(this.component, newControls))
      }
    }
    fireAdaptationStatusEvent(AdaptationStatusEvent(component, ADAPTATION_COMPLETE))
  }

  def setValid(pass: Boolean): Unit = ???

}
