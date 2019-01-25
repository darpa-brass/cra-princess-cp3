package com.cra.princess.componentmodel

import com.cra.figaro.language.Constant
import com.cra.princess._
import com.cra.princess.core.{OptimizableComponent, PrincessFeature}

/**
  * A component model which just runs the component and returns the metric calculated on the output.
  * This is useful for diagnostic/testing purposes.
  * Presumably PRINCESS would not want to execute (or could not execute) components at runtime.
  */
class DelegatingComponentModel[Env <: PrincessFeature, Input <: PrincessFeature, Output](
                          component: OptimizableComponent[Env, Input, Output]) extends ComponentModel[Env, Input] {

  /** The number of metrics that this componentmodel accounts for */
  override def numMetrics: Int = component.intent().thresholds.length

  override def apply(v1: ComponentModelInput[Env, Input]): ComponentModelMetrics = {
    val output = component.component(v1.env, v1.input, v1.controls)
    component.metricCalculator(v1.env, v1.input, output).map(c => Constant(c))
  }
}

class DelegatingComponentModelBuilder[Env <: PrincessFeature, Input <: PrincessFeature, Output](
                 val optimizableComponent: OptimizableComponent[Env, Input, Output]) extends ComponentModelBuilder[Env, Input] {

  override def componentLearner(componentData: List[ComponentModelData[Env, Input]]): ComponentModel[Env, Input] = {
    new DelegatingComponentModel(optimizableComponent)
  }
}
