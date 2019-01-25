package com.cra.princess.componentmodel

import com.cra.figaro.language.Chain
import com.cra.figaro.library.atomic.continuous.AtomicNormal
import com.cra.princess._
import com.cra.princess.core.PrincessTypeImplicits._
import org.scalatest.{FlatSpec, Matchers}
import com.cra.figaro.util.random
import com.cra.princess.core.{BoundedScalarPrincessFeature, PrincessFeatureCollection, ScalarPrincessFeature}

/**
  * Verifies that mean functions can be
  * optimized and return reasonable results
  */
class OptimizableMeanFunctionTest extends FlatSpec with Matchers {

  "A ClusteringMeanFunction" should "return prior means from within appropriate clusters" in {
    val mode1 = List.fill[ScalarPrincessFeature](100)(random.nextGaussian())
    val mode2 = List.fill[ScalarPrincessFeature](100)(random.nextGaussian() + 100)
    val inputs = mode1 ++ mode2
    val environment = List.fill(inputs.length)(PrincessFeatureCollection())
    val control1 = Map("A" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0.0, 1.0))
    val controls = List.fill(inputs.length)(control1)
    val metrics = inputs.map(i => i.value + 1)

    val modelBuilder = new GaussianProcessComponentModelBuilder[PrincessFeatureCollection, ScalarPrincessFeature](
      meanFunctionType = MeanFunctionType.Clustering, sigmaEstQuantile = Some(0.2))

    val componentData = (0 until inputs.length).map(i => new ComponentModelData(new ComponentModelInput(environment(i), inputs(i), controls(i)), List(metrics(i)))).toList
    val componentModel = modelBuilder.componentLearner(componentData)
    val estMean1 = componentModel.apply(
      new ComponentModelInput(PrincessFeatureCollection(), 200.0, control1))(0).asInstanceOf[AtomicNormal].mean
    estMean1 should be (100.0 +- 5.0)

    val estMean2 = componentModel.apply(
      new ComponentModelInput(PrincessFeatureCollection(), -100.0, control1))(0).asInstanceOf[AtomicNormal].mean
    estMean2 should be (0.0 +- 5.0)
  }

  "A NearestNeighborMeanFunction" should "return the closest point for a distant novel point" in {
    val mode1 = List.fill[ScalarPrincessFeature](100)(random.nextGaussian())
    val mode2 = List.fill[ScalarPrincessFeature](100)(random.nextGaussian() + 100)
    val inputs = mode1 ++ mode2
    val environment = List.fill(inputs.length)(PrincessFeatureCollection())
    val control1 = Map("A" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0.0, 1.0))
    val controls = List.fill(inputs.length)(control1)
    val metrics = inputs.map(i => i.value + 1)

    val modelBuilder = new GaussianProcessComponentModelBuilder[PrincessFeatureCollection, ScalarPrincessFeature](
      meanFunctionType = MeanFunctionType.NearestNeighbor, sigmaEstQuantile = Some(0.2))

    val componentData = (0 until inputs.length).map(i => new ComponentModelData(new ComponentModelInput(environment(i), inputs(i), controls(i)), List(metrics(i)))).toList
    val componentModel = modelBuilder.componentLearner(componentData)
    val estMean1 = componentModel.apply(new ComponentModelInput(PrincessFeatureCollection(), 200.0, control1))(0).asInstanceOf[AtomicNormal].mean

    // depending on the selected parameters, the largest 10 values should bound the estimate
    val maxVals = mode2.map(m => m.value + 1.0).sorted.takeRight(10)
    maxVals.min should be <= estMean1
    maxVals.max should be >= estMean1

    val estMean2 = componentModel.apply(
      new ComponentModelInput(PrincessFeatureCollection(), -100.0, control1))(0).asInstanceOf[AtomicNormal].mean

    // depending on the selected parameters, the smallest 10 values should bound the estimate
    val minVals = mode1.map(m => m.value + 1.0).sorted.take(10)
    minVals.min should be <= estMean2
    minVals.max should be >= estMean2
  }

}
