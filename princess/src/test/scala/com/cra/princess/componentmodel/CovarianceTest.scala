package com.cra.princess.componentmodel

import org.scalatest.Matchers
import org.scalatest.FlatSpec
import com.cra.princess._
import com.cra.princess.core.PrincessTypeImplicits._
import org.apache.commons.math3.linear.ArrayRealVector
import com.cra.figaro.util._
import com.cra.princess.core._

/**
 * Ensures that covariance functions can be constructed without error, and produce accurate values
 */
class CovarianceTest extends FlatSpec with Matchers {

  def BSPS(v:Double) = new BoundedScalarPrincessFeature(v, v-1, v+1)

  "Automatic sigma estimation" should "yield median of squared deviations" in {
    // just a simple linear combination
    val testInputs = List[PrincessFeature](Array(1.0, 2.0), Array(3.0, 4.0), 
        Array(5.0, 6.0), Array(7.0, 8.0), Array(9.0, 10.0))
    
    // fixing seed to reproduce row sampling
    com.cra.figaro.util.random.setSeed(1)
    GaussianCovarianceFunction(testInputs, 0.5, 0.5).bandwidth should be (20.0 +- 1e-4)
    com.cra.figaro.util.random.setSeed(1)
    GaussianCovarianceFunction(testInputs, 1, 0.5).bandwidth should be (32.0 +- 1e-4)
  }
    
  "A GaussianCovarianceFunction" should "accurately measure similarity between vectors" in {
    val covFun = GaussianCovarianceFunction[PrincessFeature](0.1)
    covFun.apply(new ArrayRealVector(Array(1.0, 2)), new ArrayRealVector(Array(1.0, 2))) should be(1)
    covFun.apply(new ArrayRealVector(Array(-20.0, -20)), new ArrayRealVector(Array(1.0, 2))) should be(0.0 +- 1e-3)
    covFun.apply(new ArrayRealVector(Array(1.0, 1.5)), new ArrayRealVector(Array(1.0, 2))) should be(0.08209 +- 1e-3)
  }  
  
  it should "accurately measure similarity between scalars" in {
    val covFun = GaussianCovarianceFunction[ScalarPrincessFeature](2.0)
    covFun(1.0, 1.0) should be(1.0 +- 1e-5)
    covFun(1.0, 100.0) should be(0.0 +- 1e-5)
    covFun(1.0, 2.0) should be(Math.exp( - 1 / 2.0) +- 1e-5)
    covFun(1.0, 3.0) should be(Math.exp( - 4 / 2.0) +- 1e-5)
  }
  
  "A LinearlyNestedCovarianceFunction3" should "accurately compute uniform sum-combinations of covariances" in {
    // this data is used to estimate kernel bandwidths
    com.cra.figaro.util.random.setSeed(1)
    val inputs1 = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0)
    val inputs2 = List[PrincessFeature](1.5, 2.5, 3.5, 4.5, 5.5)
    val inputs3 = List[PrincessFeature](3.5, 4.5, 5.5, 6.5, 7.5)
    val inputs4:List[ComponentControls] = List(Map("A" -> BSPS(5), "B" -> BSPS(6)), Map("A" -> BSPS(7), "B" -> BSPS(8)), 
                              Map("A" -> BSPS(9), "B" -> BSPS(10)), Map("A" -> BSPS(11), "B" -> BSPS(12)), Map("A" -> BSPS(13), "B" -> BSPS(14)))
    com.cra.figaro.util.random.setSeed(1)
    val covFun = LinearlyNestedCovarianceFunction4(inputs1, inputs2, inputs3, inputs4)(KernelCombinationType.Additive)
    val boundedControls1 = Map("A" -> BSPS(1.0), "B" -> BSPS(1.0))
    val boundedControls100 = Map("A" -> BSPS(100.0), "B" -> BSPS(100.0))
    
    covFun((1.0, 1.0, 1.0, boundedControls1), (1.0, 1.0, 1.0, boundedControls1)) should be(1.0 +- 1e-5)
    covFun((1.0, 1.0, 1.0, boundedControls1), (100.0, 100.0, 100.0, boundedControls100)) should be(0.0 +- 1e-5)
    
    com.cra.figaro.util.random.setSeed(1)
    val cov1 = GaussianCovarianceFunction(inputs1)
    val cov2 = GaussianCovarianceFunction(inputs2)
    val cov3 = GaussianCovarianceFunction(inputs3)
    val cov4 = GaussianCovarianceFunction(inputs4.map(c => c("A")))
    val cov5 = GaussianCovarianceFunction(inputs4.map(c => c("B")))
    val combinationVal = covFun((1.0, 1.0, 1.0, Map("A" -> BSPS(1.0), "B" -> BSPS(2.0))), (2.0, 3.0, 4.0, Map("A" -> BSPS(2.0), "B" -> BSPS(3.0))))
    val independentVal = (cov1(1.0, 2.0) + cov2(1.0, 3.0) + cov3(1.0, 4.0) +
      cov4(BSPS(1.0), BSPS(2.0)) + cov5(BSPS(2.0), BSPS(3.0))) / 5.0
    combinationVal should be(independentVal +- 1e-5)
  }

  it should "accurately compute uniform product-combinations of covariances" in {
    // this data is used to estimate kernel bandwidths
    com.cra.figaro.util.random.setSeed(1)
    val inputs1 = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0)
    val inputs2 = List[PrincessFeature](1.5, 2.5, 3.5, 4.5, 5.5)
    val inputs3 = List[PrincessFeature](3.5, 4.5, 5.5, 6.5, 7.5)
    val inputs4:List[ComponentControls] = List(Map("A" -> BSPS(5), "B" -> BSPS(6)), Map("A" -> BSPS(7), "B" -> BSPS(8)),
      Map("A" -> BSPS(9), "B" -> BSPS(10)), Map("A" -> BSPS(11), "B" -> BSPS(12)), Map("A" -> BSPS(13), "B" -> BSPS(14)))
    com.cra.figaro.util.random.setSeed(1)
    val covFun = LinearlyNestedCovarianceFunction4(inputs1, inputs2, inputs3, inputs4)(KernelCombinationType.Multiplicative)
    val boundedControls1 = Map("A" -> BSPS(1.0), "B" -> BSPS(1.0))
    val boundedControls100 = Map("A" -> BSPS(100.0), "B" -> BSPS(100.0))

    covFun((1.0, 1.0, 1.0, boundedControls1), (1.0, 1.0, 1.0, boundedControls1)) should be(1.0 +- 1e-5)
    covFun((1.0, 1.0, 1.0, boundedControls1), (100.0, 100.0, 100.0, boundedControls100)) should be(0.0 +- 1e-5)

    com.cra.figaro.util.random.setSeed(1)
    val cov1 = GaussianCovarianceFunction(inputs1)
    val cov2 = GaussianCovarianceFunction(inputs2)
    val cov3 = GaussianCovarianceFunction(inputs3)
    val cov4 = GaussianCovarianceFunction(inputs4.map(c => c("A")))
    val cov5 = GaussianCovarianceFunction(inputs4.map(c => c("B")))
    val combinationVal = covFun((1.0, 1.0, 1.0, Map("A" -> BSPS(1.0), "B" -> BSPS(2.0))), (2.0, 3.0, 4.0, Map("A" -> BSPS(2.0), "B" -> BSPS(3.0))))
    val independentVal = (cov1(1.0, 2.0) * cov2(1.0, 3.0) * cov3(1.0, 4.0) *
      cov4(BSPS(1.0), BSPS(2.0)) * cov5(BSPS(2.0), BSPS(3.0)))
    combinationVal should be(independentVal +- 1e-5)
  }

  "A LinearlyNestedCovarianceFunction" should "unwrap PrincessFeatureCollections" in {
    val a = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
    val b = List[PrincessFeature](2.0, 3.0, 4.0, 5.0, 6.0, 7.0)
    val collection1 = a zip b map { s => PrincessFeatureCollection(s._1, s._2) }
    
    val c = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
    val d = List[PrincessFeature](2.0, 3.0, 4.0, 5.0, 6.0, 7.0)
    val collection2 = c zip d map { s => PrincessFeatureCollection(s._1, s._2) }
    com.cra.figaro.util.random.setSeed(1)
    val covFun = LinearlyNestedCovarianceFunction(collection1, collection2)(KernelCombinationType.Additive)
    
    com.cra.figaro.util.random.setSeed(1)
    val indepCovariances = List(a, b, c, d).map(vals => GaussianCovarianceFunction(vals))
    val combinationVal = covFun(List(PrincessFeatureCollection(8.1, 9.1), PrincessFeatureCollection(7.1, 8.1)),
                                List(PrincessFeatureCollection(8.5, 9.5), PrincessFeatureCollection(7.5, 8.5)))
    val independentVal = (indepCovariances(0)(8.1, 8.5) + indepCovariances(1)(9.1, 9.5) + 
                          indepCovariances(2)(7.1, 7.5) + indepCovariances(3)(8.1, 8.5)) / 4.0
    combinationVal should be (independentVal +- 1e-5)
  }

  "A FlatteningGaussianCovarianceFunction3" should "unwrap and scale PrincessFeatures" in {
    val inputs1 = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0)
    val inputs2 = List[PrincessFeature](1.5, 2.5, 3.5, 4.5, 5.5)
    val inputs3:List[ComponentControls] = List(Map("A" -> BSPS(5), "B" -> BSPS(6)), Map("A" -> BSPS(7), "B" -> BSPS(8)),
      Map("A" -> BSPS(9), "B" -> BSPS(10)), Map("A" -> BSPS(11), "B" -> BSPS(12)), Map("A" -> BSPS(13), "B" -> BSPS(14)))

    random.setSeed(1)
    val flatteningCovar = FlatteningGaussianCovarianceFunction3(inputs1, inputs2, inputs3)
    random.setSeed(1)

    def scaleSample = (s:Seq[Double]) => Array((s(0) - 1.0) / 4.0, (s(1) - 1.5) / 4.0, (s(2) - 5.0) / 8.0, (s(3) - 6.0) / 8.0)
    val flatCovar = GaussianCovarianceFunction(List[VectorPrincessFeature](
      scaleSample(Array(1.0, 1.5, 5.0, 6.0)),
      scaleSample(Array(2.0, 2.5, 7.0, 8.0)),
      scaleSample(Array(3.0, 3.5, 9.0, 10.0)),
      scaleSample(Array(4.0, 4.5, 11.0, 12.0)),
      scaleSample(Array(5.0, 5.5, 13.0, 14.0))))

    val flatteningVal = flatteningCovar((4.0, 5.6, Map("A" -> BSPS(13.1), "B" -> BSPS(14.1))),
      (4.5, 5.5, Map("A" -> BSPS(13.0), "B" -> BSPS(14.0))))
    val flatVal = flatCovar(scaleSample(Array(4.0, 5.6, 13.1, 14.1)), scaleSample(Array(4.5, 5.5, 13.0, 14.0)))
    flatteningVal should be (flatVal +- 1e-7)
  }

  "A FlatteningGaussianProductCovarianceFunction3" should "compute a product of covariances" in {
    val inputs1 = List[PrincessFeature](1.0, 2.0, 3.0, 4.0, 5.0)
    val inputs2 = List[PrincessFeature](1.5, 2.5, 3.5, 4.5, 5.5)
    val inputs3:List[ComponentControls] = List(Map("A" -> BSPS(5), "B" -> BSPS(6)), Map("A" -> BSPS(7), "B" -> BSPS(8)),
      Map("A" -> BSPS(9), "B" -> BSPS(10)), Map("A" -> BSPS(11), "B" -> BSPS(12)), Map("A" -> BSPS(13), "B" -> BSPS(14)))

    random.setSeed(1)
    val flatteningCovar = FlatteningGaussianProductCovarianceFunction3(inputs1, inputs2, inputs3)
    random.setSeed(1)

    def scaleInputSample(s:Seq[Double]) = Array((s(0) - 1.0) / 4.0, (s(1) - 1.5) / 4.0)
    def scaleControl(s:Double*) = Array((s(0) - 5.0) / 8.0, (s(1) - 6.0) / 8.0)
    val flatInputCovar = GaussianCovarianceFunction(List[VectorPrincessFeature](
      scaleInputSample(Array(1.0, 1.5, 5.0, 6.0)),
      scaleInputSample(Array(2.0, 2.5, 7.0, 8.0)),
      scaleInputSample(Array(3.0, 3.5, 9.0, 10.0)),
      scaleInputSample(Array(4.0, 4.5, 11.0, 12.0)),
      scaleInputSample(Array(5.0, 5.5, 13.0, 14.0))))
    val flatControlCovar = GaussianCovarianceFunction(List[VectorPrincessFeature](
      scaleControl(5.0, 6.0),
      scaleControl(7.0, 8.0),
      scaleControl(9.0, 10.0),
      scaleControl(11.0, 12.0),
      scaleControl(13.0, 14.0)))

    val flatteningVal = flatteningCovar((4.0, 5.6, Map("A" -> BSPS(13.1), "B" -> BSPS(14.1))),
                                        (4.5, 5.5, Map("A" -> BSPS(13.0), "B" -> BSPS(14.0))))
    val flatVal = flatInputCovar(scaleInputSample(Array(4.0, 5.6)), scaleInputSample(Array(4.5, 5.5, 7.0))) *
      flatControlCovar(scaleControl(13.1, 14.1), scaleControl(13.0, 14.0))
    flatteningVal should be (flatVal +- 0.1) // allow some slack due to bandwidth estimation
  }

  "An EmptyCovarianceFunction" should "have no weight in additive combinations" in {
    val gaussCovar = new GaussianCovarianceFunction[PrincessFeature](1.0)
    val combinationType = KernelCombinationType.Additive
    val covarComb = new LinearlyNestedCovarianceFunction(Seq(new EmptyCovarianceFunction[PrincessFeature](combinationType), gaussCovar), combinationType)
    covarComb(Seq[ScalarPrincessFeature](1.0, 2.0), Seq[ScalarPrincessFeature](1.0, 2.1)) should be(gaussCovar(2.0, 2.1) +- 1e-5)  
  }

  it should "have weight 1 in multiplicative combinations" in {
    val gaussCovar = new GaussianCovarianceFunction[PrincessFeature](1.0)
    val combinationType = KernelCombinationType.Multiplicative
    val covarComb = new LinearlyNestedCovarianceFunction(Seq(new EmptyCovarianceFunction[PrincessFeature](combinationType), gaussCovar), combinationType)
    covarComb(Seq[ScalarPrincessFeature](1.0, 2.0), Seq[ScalarPrincessFeature](1.0, 2.1)) should be(gaussCovar(2.0, 2.1) +- 1e-5)
  }

  it should "assign covariance 1 to all pairs" in {
   val emptyCovar = new EmptyCovarianceFunction[ScalarPrincessFeature](KernelCombinationType.Additive)
   emptyCovar(1.0, 2.0) should equal(1.0)
   emptyCovar(1.0, 1.0) should equal(1.0)
  }
  
}