package com.cra.princess.componentmodel

import com.cra.figaro.language._
import com.cra.figaro.library.atomic.continuous.Normal
import com.cra.princess._
import com.cra.princess.core.PrincessFeature
import com.cra.princess.util.PrincessTypeUtility

case class LinearRegressionParameters(intercept:Double, featureBetas:Array[Double], errorVariance: Double, var columnsWithVariance: Array[Int] = null) {
  if(columnsWithVariance == null)
    columnsWithVariance = (0 until featureBetas.length).toArray
}

/** A linear model relating environments, inputs, and program features to metrics */
class LinearComponentModel[Env <: PrincessFeature, Input <: PrincessFeature](
    val regressionModels: List[LinearRegressionParameters],
    elementCollection: ElementCollection) extends ComponentModel[Env, Input] {

  val numMetrics = regressionModels.length

  override def apply(v1: ComponentModelInput[Env, Input]): ComponentModelMetrics = {
    val featureVector = PrincessTypeUtility.flatten(v1)

    regressionModels.zipWithIndex.map(modeli => {
      val (model, i) = modeli
        val keepFeatures = model.columnsWithVariance.map(c => featureVector(c))
        val condMean:Double = model.intercept + model.featureBetas.zip(keepFeatures).map(a => a._1 * a._2).sum
        Normal(condMean, model.errorVariance)
    })
  }
}

object LinearComponentModel {
  def apply[Env <: PrincessFeature, Input <: PrincessFeature](regressionModels: List[LinearRegressionParameters])
       (implicit elementCollection: ElementCollection) = new LinearComponentModel[Env, Input](regressionModels, elementCollection)
}
