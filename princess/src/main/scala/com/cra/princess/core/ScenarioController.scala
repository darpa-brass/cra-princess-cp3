package com.cra.princess.core

import com.cra.princess.ComponentControls
import com.cra.princess.monitor.{ComponentMonitor, MonitorProxy, SystemMonitor}
import com.cra.princess.optimizer.{ComponentOptimizer, OptimizationManager, SensorTransformerPolicy, StateEstimator}
import com.cra.princess.util.Logs
import com.cra.princess.verifier.Verifier

import scala.concurrent.ExecutionContext.Implicits.global
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.concurrent.Future
import scala.reflect.{ClassTag, classTag}

class ScenarioController(stateEstimator: StateEstimator, sensorTransformerPolicy: SensorTransformerPolicy, adaptation: Boolean) extends OptimizationEventListener with VerificationEventListener with Logs {
  type OptimizationHandler = ComponentControls => Unit
  type AdaptationHandler = AdaptationState => Unit
  type VerificationEventHandler = VerificationResult => Unit

  private val componentAdaptationManagers = ListBuffer.empty[ComponentAdaptationManager[_ <: PrincessFeature, _ <: PrincessFeature, _]]
  private val sensorTransformers = ListBuffer.empty[SensorTransformer]
  private val optimizationManager = new OptimizationManager(CAMs = componentAdaptationManagers, stateEstimator, sensorTransformerPolicy)
  private val optimizationHandlers: mutable.Map[OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], List[OptimizationHandler]] = mutable.Map.empty
  private val adaptationEventHandlers: mutable.Map[OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], List[AdaptationHandler]] = mutable.Map.empty
  private val verificationEventHandlers: mutable.Map[OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], List[VerificationEventHandler]] = mutable.Map.empty

  def initScenario(): Unit = {
    this.optimizationManager.init()
  }

  private def addComponent(cam: ComponentAdaptationManager[_ <: PrincessFeature, _ <: PrincessFeature, _]) = {
    if (adaptation) {
      cam.addIntentListener(optimizationManager.observeIntentResult)
      cam.addVerificationListener(optimizationManager.observeVerificationResult)
      cam.addVerificationListener(this)
    }
    cam.addOptimizationEventListener(this)
    componentAdaptationManagers += cam
  }

  def addSensorTransformer(transformer: SensorTransformer): Unit = {
    transformer.addListener(optimizationManager)
    sensorTransformers += transformer
  }

  def attachSystemMonitor(monitor: SystemMonitor): Unit = {
    monitor.addListener(optimizationManager.observeIntentResult)
  }

  def registerOptimizationHandler(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _],
                                  handler: ComponentControls => Unit): Unit = {
    addToMap(optimizationHandlers, component, handler)
  }

  def registerAdaptationEventHandler(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _],
                                     handler: AdaptationState => Unit): Unit = {
    addToMap(adaptationEventHandlers, component, handler)
  }

  def registerVerificationEventHandler(component: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _],
                                       handler: VerificationResult => Unit): Unit = {
    addToMap(verificationEventHandlers, component, handler)
  }

  private def addToMap[T](m: mutable.Map[OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], List[T]],
                          c: OptimizableComponent[_ <: PrincessFeature, _ <: PrincessFeature, _], item: T): Unit = {
    val list = m.getOrElse(c, List.empty)
    m(c) = list :+ item
  }

  override def handleOptimization(e: OptimizationEvent): Unit = {
    log.debug(s"Scenario Controller received OptimizationEvent: $e")
    if (optimizationHandlers.contains(e.component)) {
      Future[Unit] {
        optimizationHandlers(e.component).foreach(_(e.controlVariables))
      }
      log.debug("Launched optimization handler for event")
    }
    else log.debug("No action taken")
  }

  override def handleAdaptationStatus(e: AdaptationStatusEvent): Unit = {
    log.debug(s"Scenario Controller received AdaptationStatusEvent: $e")
    if (adaptationEventHandlers.contains(e.component)) {
      Future[Unit] {
        adaptationEventHandlers(e.component).foreach(_(e.state))
      }
      log.debug("Launched adaptation status event handler")
    } else log.debug("No action taken")
  }

  override def handleVerificationEvent(e: VerificationEvent): Unit = {
    log.debug(s"Scenario controller received VerificationEvent: $e")
    if (verificationEventHandlers.contains(e.component)) {
      Future[Unit] {
        verificationEventHandlers(e.component).foreach(_(e.result))
      }
      log.debug("Launched verification status event handler")
    } else log.debug("No action taken")
  }

  def buildWrappedComponent[Env <: PrincessFeature: ClassTag, Input <: PrincessFeature: ClassTag, Output, Comp <: OptimizableComponent[Env, Input, Output]: ClassTag]
  (component: Comp, optimizer: ComponentOptimizer[Env, Input], verifier: Option[Verifier] = None, inputProvider: Option[() => Option[Input]] = None): Comp = {
    val cam = new ComponentAdaptationManager(component, optimizer, inputProvider)
    val monitor = new ComponentMonitor(cam)
    val wrapped = java.lang.reflect.Proxy.newProxyInstance(
      this.getClass.getClassLoader,
      Array[Class[_]](classTag[Comp].runtimeClass),
      new MonitorProxy[Env, Input, Output](component, monitor)) match {
      case good: Comp => good
      case _ => throw new IllegalStateException(s"MonitorProxy returned wrong type for ${classTag[Comp].runtimeClass.toString}")
    }
    verifier match {
      case Some(v) => cam.setVerifier(v)
      case None =>
    }
    this.addComponent(cam)
    wrapped
  }
}
