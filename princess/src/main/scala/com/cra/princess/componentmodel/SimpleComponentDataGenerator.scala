package com.cra.princess.componentmodel

import com.cra.princess._
import com.cra.princess.exceptions.UnsupportedTypeException
import com.cra.figaro.algorithm.sampling.ElementSampler
import com.cra.figaro.library.atomic._
import com.cra.figaro.language.Element
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess.core.{OptimizableComponent, PrincessFeature}


// TODO: Triage all data generation classes, whether to move them to separate project, or delete them

/**
  * @deprecated Data generation should come from external environment
  * Generates random component data from an input model and a control generator
 */
class SimpleComponentDataGenerator[Env <: PrincessFeature, Input <: PrincessFeature, ComponentOutput](nsamples:Int = 1000) 
    extends ComponentDataGenerator[Env, Input, ComponentOutput] {

  /** Creates a set of random input data by sampling independently from the control generator and the input model*/
  override def generate(inputModel:InputModel[Env, Input], controlGenerator: ControlGenerator,
      component: OptimizableComponent[Env, Input, ComponentOutput]): List[ComponentModelData[Env, Input]] = {
      val inputSampler = ElementSampler(inputModel)

    // sample jointly from environments and inputs, independently from controls
    (0 until nsamples).map(i => {
      val (env, input) = inputSampler.sample()._2(inputModel).asInstanceOf[(Env, Input)]
      val controls = controlGenerator()
      val output = component.component(env, input, controls)
      val metrics = component.metricCalculator(env, input, output)
      new ComponentModelData(new ComponentModelInput(env, input, controls), metrics)
    }).toList 
  }
}