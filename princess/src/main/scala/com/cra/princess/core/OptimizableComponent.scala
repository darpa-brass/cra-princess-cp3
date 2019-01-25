package com.cra.princess.core

import com.cra.princess.{ComponentControls, ComponentMetrics}

/**
  * @author Gerald Fry
  * Required interface for optimizable components. To be "optimizable," a component (written in Java), must be wrapped
  * 	inside of a Scala class that extends this trait
  * @tparam Env - Environment type
  * @tparam Input - Input type
  * @tparam Output - Output type
  */
trait OptimizableComponent [Env <: PrincessFeature, Input <: PrincessFeature, Output] {

  def intent():Intent

  /**
    * Run the component and update control variables.
    * If synchronous, call runComponent and updateControls (in some order)
    * If asynchronous, a custom implementation is needed
    * @param e - Env
    * @param i - Input
    * @param c - ComponentControls
    * @return Output
    */
  def component(e: Env, i: Input, c: ComponentControls): Output

  /**
    * Run the component
    * @param e - Env
    * @param i - Input
    * @return Output
    */
  def runComponent(e: Env, i: Input) : Output

  /**
    * Update control variables for component
    * @param c
    */
  def updateControls(c: ComponentControls): Unit

  /**
    * @param e - Env
    * @param i - Input
    * @param o - Output
    * @return ComponentMetrics - Current state of component
    */
  def metricCalculator(e: Env, i: Input, o: Output): ComponentMetrics

  def satisfiesIntent(metrics:ComponentMetrics): IntentResult = intent.evaluateIntentState(metrics)

  def satisfiesIntent(e: Env, i: Input, c:ComponentControls): IntentResult = {
    val output = component(e, i, c)
    val metrics = metricCalculator(e, i, output)
    intent().evaluateIntentState(metrics)
  }
}
