package com.cra.princess.componentmodel

import com.cra.princess._
import com.cra.princess.elements.GaussianProcess
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.figaro.language.{Chain, Element, ElementCollection}
import com.cra.princess.core.PrincessFeature

/**
 * Performs density estimation of metrics conditioned on environment, input, and controls using Gaussian process regression
 * @author Dan Garant
 */
class GaussianProcessComponentModel[Env <: PrincessFeature, Input <: PrincessFeature]
  (val metricModels: List[GaussianProcess[(Env, Input, ComponentControls)]],
   elementCollection: ElementCollection) extends ComponentModel[Env, Input] {

  val numMetrics = metricModels.length

  def apply(input:ComponentModelInput[Env, Input]): ComponentModelMetrics = {
    metricModels.zipWithIndex.map(modeli => {
      val (model, i) = modeli
      model.model((input.env, input.input, input.controls))
    })
  }
}

object GaussianProcessComponentModel {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](
    metricModels: List[GaussianProcess[(Env, Input, ComponentControls)]])(implicit elementCollection: ElementCollection) =
    new GaussianProcessComponentModel(metricModels, elementCollection)
}
