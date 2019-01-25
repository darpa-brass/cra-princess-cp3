package com.cra.princess.componentmodel

import com.cra.figaro.library.atomic.continuous.AtomicNormal
import com.cra.figaro.util.random
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess._
import com.cra.princess.core._
import org.scalatest.{FlatSpec, Matchers}

/**
  * Verifies that the linear component model yields accurate estimates
  */
class LinearComponentModelTest extends FlatSpec with Matchers {

  "A LinearComponentModel" should "produce accurate conditional distributions" in {
    val lmParameters =
      List(
        new LinearRegressionParameters(1.0, Array[Double](2.0, 30.0, 400.0, 60000.0), 3.0),
        new LinearRegressionParameters(1.1, Array[Double](2.1, 30.1, 400.1, 60000.1), 5.0)
      )
    val lm = LinearComponentModel[VectorPrincessFeature, ScalarPrincessFeature](lmParameters)
    val estimate = lm(new ComponentModelInput(new VectorPrincessFeature(Array(2.0, 3.0)), new ScalarPrincessFeature(4.0), Map("A" -> new BoundedScalarPrincessFeature(5.0, 4.0, 6.0))))
    var condEst = estimate(0).asInstanceOf[AtomicNormal]
    condEst.mean should be(301694.0 + 1.0)
    condEst.variance should be(3.0)

    condEst = estimate(1).asInstanceOf[AtomicNormal]
    condEst.mean should be(301695.4 + 1.1)
    condEst.variance should be(5.0)
  }

  it should "ignore features when requested" in {
    val lmParameters =
      List(
        new LinearRegressionParameters(1.0, Array(2.0), 3.0, Array(0)),
        new LinearRegressionParameters(1.1, Array(2.1), 5.0, Array(0))
      )
    val lm = LinearComponentModel[VectorPrincessFeature, ScalarPrincessFeature](lmParameters)
    val estimate = lm(new ComponentModelInput(new VectorPrincessFeature(Array(2.0, 3.0)), new ScalarPrincessFeature(4.0), Map("A" -> new BoundedScalarPrincessFeature(5.0, 4.0, 6.0))))
    var condEst = estimate(0).asInstanceOf[AtomicNormal]
    condEst.mean should be(2.0 * 2.0 + 1.0)
    condEst.variance should be(3.0)

    condEst = estimate(1).asInstanceOf[AtomicNormal]
    condEst.mean should be(2.0 * 2.1 + 1.1)
    condEst.variance should be(5.0)
  }


  "A LinearComponentModelBuilder" should "estimate accurate model parameters" in {
    val vfg = (a:Any) => new VectorPrincessFeature(Array(random.nextGaussian(), random.nextGaussian()))
    val sfg = (a:Any) => new ScalarPrincessFeature(random.nextGaussian())
    val envFeatures = (0 until 1000).map(vfg).toList
    val inputFeatures = (0 until 1000).map(sfg).toList
    val inputs = (0 until envFeatures.length).map(i =>
      new ComponentModelData(
        new ComponentModelInput(envFeatures(i), inputFeatures(i), Map("A" -> new BoundedScalarPrincessFeature(i, i-1, i+1))),
        List(envFeatures(i).value.getEntry(0) * 1.1 + envFeatures(i).value.getEntry(1) * 1.2 + inputFeatures(i).value * 1.3 + i * 2.75 + 2 * 2.5))).toList;

    val mockComponent = new OptimizableComponent[VectorPrincessFeature, ScalarPrincessFeature, Double] {
      override def intent():Intent = null
      override def component(e: VectorPrincessFeature, i: ScalarPrincessFeature, c: ComponentControls): Double = Double.NaN
      override def metricCalculator(e: VectorPrincessFeature, i: ScalarPrincessFeature, o: Threshold): ComponentMetrics = List(Double.NaN)
      override def runComponent(e: VectorPrincessFeature, i: ScalarPrincessFeature) : Double = ???
      override def updateControls(c: ComponentControls): Unit = ???
    }

    val lmBuilder = new LinearComponentModelBuilder(mockComponent)
    val componentModel = lmBuilder.componentLearner(inputs).asInstanceOf[LinearComponentModel[VectorPrincessFeature, ScalarPrincessFeature]]

    val params = componentModel.regressionModels(0)
    // program features should be ignored, they have no variance
    params.featureBetas.length should equal(4)
    params.columnsWithVariance should be(Array(0, 1, 2, 3))

    params.intercept should be(5.0 +- 1e-5)
    params.featureBetas(0) should be(1.1 +- 1e-5)
    params.featureBetas(1) should be(1.2 +- 1e-5)
    params.featureBetas(2) should be(1.3 +- 1e-5)
    params.featureBetas(3) should be(2.75 +- 1e-5)
    params.errorVariance should be(0.0 +- 1e-5)

    val metricEst = componentModel.apply(new ComponentModelInput(
      new VectorPrincessFeature(Array(10.0, 100.0)), 1000.0, Map("A" -> new BoundedScalarPrincessFeature(10.0, 9.0, 11.0))))
    val normalEst = metricEst(0).asInstanceOf[AtomicNormal]
    normalEst.mean should be(10.0 * 1.1 + 100.0 * 1.2 + 1000.0 * 1.3 + 2.75 * 10.0 + 2.5 * 2 +- 1e-5)
    normalEst.variance should be(0.0 +- 1e-5)
  }
}
