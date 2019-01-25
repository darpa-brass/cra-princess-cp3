package com.cra.princess.componentmodel

import com.cra.figaro.algorithm.sampling.ElementSampler
import com.cra.figaro.language.{Atomic, Element, ElementCollection}
import com.cra.princess._



/**
 * Basic generator of control values.
 * @param controls One instance of the control variables to generate data for.
 *                 The metadata contained in this instance is used to create a sampler.
 */
class BasicControlGenerator(controls:ComponentControls, elementCollection: ElementCollection) extends ControlGenerator {

  // create elements that represent the controls
  private val controlElements = controls.transform((k, v) => v.prior(k, elementCollection))
  private val controlSamplers = controlElements.mapValues(ElementSampler(_))

  override def elements(): Map[String, Element[Control]] = {
    controlElements
  }

  /** Independently samples from the prior of each control variable, then merges the results into a ComponentControls type. */
  override def apply(): ComponentControls = {
    controlSamplers.transform((name, sampler) => sampler.sample()._2(controlElements(name)).asInstanceOf[Control])
  }
}

object BasicControlGenerator {
  def apply(controls:ComponentControls)(implicit elementCollection: ElementCollection) =
    new BasicControlGenerator(controls, elementCollection)
}