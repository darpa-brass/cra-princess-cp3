package com.cra.princess.componentmodel

import com.cra.figaro.language._
import com.cra.princess.core.{OptimizableComponent, PrincessFeature}
import com.cra.princess.{ComponentControls, ComponentMetrics, ComponentModelMetrics, Control, InputModel}

/**
 * @author Gerald Fry
 * API for Component Model Building
 * @tparam Env Environment type
 * @tparam Input Input type
  */
trait ComponentModelBuilder [Env <: PrincessFeature, Input <: PrincessFeature] {
  
  val optimizableComponent: OptimizableComponent[Env, Input, _]
  def componentLearner(componentData: List[ComponentModelData[Env, Input]]): ComponentModel[Env, Input]
}

/** Represents an input to the component model, which consists of an environment, input, and control variable assignment */
case class ComponentModelInput[Env <: PrincessFeature, Input <: PrincessFeature]
(env:Env, input:Input, controls:ComponentControls)

/** Represents the result of running the component at a specified input, resulting in a metric value */
case class ComponentModelData[Env <: PrincessFeature, Input <: PrincessFeature]
(componentInput:ComponentModelInput[Env, Input], metrics:ComponentMetrics)

/** Generates component data consistent with a control generation procedure and an input model */
trait ComponentDataGenerator[Env <: PrincessFeature, Input <: PrincessFeature, ComponentOutput] {
  def generate(inputModel:InputModel[Env, Input], controlGenerator: ControlGenerator, 
      component: OptimizableComponent[Env, Input, ComponentOutput]): List[ComponentModelData[Env, Input]]
}

/** PRINCESS core representation of component to optimize
  * Captures environmental conditions as well as Input, Output is obtained by running the component*/
trait ComponentModel[Env <: PrincessFeature, Input <: PrincessFeature]
  extends (ComponentModelInput[Env, Input] => ComponentModelMetrics) {
  /** The number of metrics that this ComponentModel accounts for */
  def numMetrics:Int
}

/**Responsible for generating control variables*/
trait ControlGenerator extends (() => ComponentControls) {
  def elements: Map[String, Element[Control]]
}

/**
  * An input model which can be updated with observed environments and inputs at runtime
  */
abstract class ConditionalInputModel[Env, Input](name:Name[(Env, Input)], elementCollection: ElementCollection)
    extends InputModel[Env, Input](name, elementCollection) {

  /**
    * Incorporate a new environment and input into a new model, leaving this instance unmodified.
    * @param time The time at which this observation was made
    * @param obs The observed environment and input
    * @return A new input model
    */
  def update(time:Double, obs:(Env, Input)):ConditionalInputModel[Env, Input]
}

/**
  * An input model which can be updated with observed inputs at runtime
  */
abstract class LatentEnvironmentInputModel[Env, Input](name:Name[(Env, Input)], elementCollection: ElementCollection)
    extends InputModel[Env, Input](name:Name[(Env, Input)], elementCollection:ElementCollection) {

  /**
    * Incorporate a new environment and input into a new model, leaving this instance unmodified.
    * @param time The time at which this observation was made
    * @param obs The observed input
    * @return A new input model
    */
  def update(time:Double, obs:Input):LatentEnvironmentInputModel[Env, Input]
}

/**
 * Performs dynamic code analysis on a component, implemented as a Java class
 */
trait ComponentCodeAnalyzer[Env <: PrincessFeature, Input <: PrincessFeature] {

  /**
    * Creates a PrincessFeature containing the analysis of program execution at a specified set of inputs
    */
  def analyze(componentData:List[(Env, Input, ComponentControls)]):List[PrincessFeature]
}