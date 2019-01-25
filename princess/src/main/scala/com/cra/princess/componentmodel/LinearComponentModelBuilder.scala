package com.cra.princess.componentmodel

import com.cra.princess._
import com.cra.princess.core.{OptimizableComponent, PrincessFeature}
import com.cra.princess.util.PrincessTypeUtility
import org.apache.commons.math3.stat.regression.OLSMultipleLinearRegression

/**
  * Constructs a linear model relating environment and input features to metrics
  */
class LinearComponentModelBuilder[Env <: PrincessFeature, Input <: PrincessFeature](
       val optimizableComponent: OptimizableComponent[Env, Input, _])
    extends ComponentModelBuilder[Env, Input] {

  /**
    * Learns a linear regression model of metrics conditioned on inputs
    */
  override def componentLearner(
           componentData: List[ComponentModelData[Env, Input]]): ComponentModel[Env, Input] = {
    // split the component data up by metric
    val nmetrics = componentData(0).metrics.length
    val envFeatures = componentData.map(_.componentInput.env)
    val inputFeatures = componentData.map(_.componentInput.input)
    val controlFeatures = componentData.map(_.componentInput.controls)

    val augmentedInput = (0 until componentData.length).map(i =>
      PrincessTypeUtility.flatten(envFeatures(i), inputFeatures(i), controlFeatures(i)).toArray).toArray
    val ncols = augmentedInput(0).length

    def isConstant(table:Array[Array[Double]], col:Integer) = {
      table.map(row => row(col)).toSet.size > 1
    }

    // hide features with no variability from the linear model
    val variableColumns = (0 until ncols).filter(isConstant(augmentedInput, _)).toArray
    val keepInputs = augmentedInput.map(row => variableColumns.map(c => row(c)))

    val lmParams = (0 until nmetrics).map(i => {
      val metricRegression = new OLSMultipleLinearRegression()
      val metricData = componentData.map(c => c.metrics(i)).toArray

      metricRegression.newSampleData(metricData, keepInputs)
      val parameters = metricRegression.estimateRegressionParameters()
      LinearRegressionParameters(parameters(0), parameters.drop(1), metricRegression.estimateErrorVariance(), variableColumns)
    }).toList

    // at modeling time, query each linear model
    LinearComponentModel(lmParams)
  }
}
