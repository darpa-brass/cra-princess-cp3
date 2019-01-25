package com.cra
import com.cra.figaro.language._
import com.cra.princess.componentmodel.KernelCombinationType
import com.cra.princess.core.{PrincessFeature, PriorPrincessFeature}

/**
  * Project level type aliases to clarify usages of specific types
  */

package object princess {
  type Metric = Double // How to paramaterize this type? -GFry
  type ComponentMetrics = List[Metric]
  type ComponentModelMetrics = List[Element[Metric]] // For use in ComponentModel definition

   // Make Threshold same type as Metric, but is there a way to specify that they just need to be comparable 
  // (e.g., <=:  (Int, Double) => Bool)? -GFry
  type Threshold = Metric
  type ComponentThresholds = List[Threshold]

  /** Type aliasing PriorPrincessFeature as control variables */
  type Control = PriorPrincessFeature
  type ComponentControls = Map[String, Control]

  type InputModel[Env, Input] = Element[(Env, Input)]
  type ProgramFeatures = PrincessFeature
  type ProgramFeatureModel = Element[PrincessFeature]

  implicit def kernelCombinationType = KernelCombinationType.Multiplicative
}
