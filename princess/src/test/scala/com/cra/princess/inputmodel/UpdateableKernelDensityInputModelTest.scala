package com.cra.princess.inputmodel

import com.cra.figaro.util._
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess._
import com.cra.princess.componentmodel.MultivariateKernelDensityEstimator
import com.cra.princess.core.{IdentityBuilder, PrincessFeatureCollection, ScalarPrincessFeature}
import org.apache.commons.math3.distribution.{MultivariateNormalDistribution, NormalDistribution}
import org.scalatest.{FlatSpec, Matchers}

/**
 * Verifies that the updateable KDE accurately computes weighted densities
  *
  * @author Dan Garant
 */
class UpdateableKernelDensityInputModelTest extends FlatSpec with Matchers {

  "A MultivariateKernelDensityEstimate" should "compute accurate weighted univariate densities" in {
    val kde = new MultivariateKernelDensityEstimator(Array(Array(1.0), Array(2.0), Array(3.0)))
    kde.setWeights(Array(1, 0.5, 0.1))
    val stdDev = Math.sqrt(kde.bandwidth.getEntry(0, 0))
    val distr1 = new NormalDistribution(1.0, stdDev)
    val distr2 = new NormalDistribution(2.0, stdDev)
    val distr3 = new NormalDistribution(3.0, stdDev)
    
    val combinedDensity = (1 * distr1.density(2.5) + 0.5 * distr2.density(2.5) + 0.1 * distr3.density(2.5)) / 1.6
    kde.density(Array(2.5)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(100.0)) should be(0.0 +- 1e-5)
  }
  
  it should "compute accurate weighted multivariate densities" in {
    val kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 1.0), Array(2.0, 4.0), Array(3.0, 6.0)))
    kde.setWeights(Array(1, 0.5, 0.1))
    val covar = kde.bandwidth.getData
    val distr1 = new MultivariateNormalDistribution(Array(1.0, 1.0), covar)
    val distr2 = new MultivariateNormalDistribution(Array(2.0, 4.0), covar)
    val distr3 = new MultivariateNormalDistribution(Array(3.0, 6.0), covar)
    
    val combinedDensity = (1 * distr1.density(Array(3.0, 3.0)) + 0.5 * distr2.density(Array(3.0, 3.0)) + 0.1 * distr3.density(Array(3.0, 3.0))) / 1.6
    kde.density(Array(3.0, 3.0)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(100.0, 100.0)) should be(0.0 +- 1e-5)    
  }
  
  it should "handle dimensions with zero variance" in {
    var kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 1.0), Array(1.0, 4.0), Array(1.0, 6.0)))
    kde.setWeights(Array(1, 0.5, 0.1))
    val covar = kde.bandwidth.getData()(0)(0)
    val distr1 = new NormalDistribution(1.0, Math.sqrt(covar))
    val distr2 = new NormalDistribution(4.0, Math.sqrt(covar))
    val distr3 = new NormalDistribution(6.0, Math.sqrt(covar))
    
    val combinedDensity = (1 * distr1.density(3.0) + 0.5 * distr2.density(3.0) + 0.1 * distr3.density(3.0)) / 1.6
    kde.density(Array(1.0, 3.0)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(1.0001, 3.0)) should be(0.0 +- 1e-5)

    // sampling should respect weights
    val secondDim = (0 until 10).map(i => {
      kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 495.0), Array(1.0, 500.0), Array(1.0, 505.0)))
      kde.setWeights(Array(1000.0, 0.1, 0.1))
      val sVal = kde.sample()
      sVal(0) should be(1.0)
      sVal(1)
    })
    (secondDim.sum / secondDim.length) should be (495.0 +- 2.0)
  }

  "An UpdateableKernelDensityInputModel" should "assign appropriate weights to points" in {
    val environments = List.fill(3)(PrincessFeatureCollection())
    val inputs = List[ScalarPrincessFeature](1.4, 4.1, 6.0)
    random.setSeed(1)
    val inputModel = UpdateableKernelDensityInputModel(environments, inputs, 0.1, 5,
      IdentityBuilder[PrincessFeatureCollection](), IdentityBuilder[ScalarPrincessFeature]())

    var updatedInputModel = inputModel.update(2, (PrincessFeatureCollection(), 2.0))
    updatedInputModel = updatedInputModel.update(4, (PrincessFeatureCollection(), 1.0))

    val bw = Math.sqrt(updatedInputModel.kde.bandwidth.getEntry(0, 0))
    val distr1 = new NormalDistribution(1.4, bw)
    val distr2 = new NormalDistribution(4.1, bw)
    val distr3 = new NormalDistribution(6.0, bw)
    val distr4 = new NormalDistribution(2.0, bw)
    val distr5 = new NormalDistribution(1.0, bw)
    updatedInputModel.density((PrincessFeatureCollection(), 3.3)) should be(
      (5 / 3.0 * distr1.density(3.3) + 5 / 3.0 * distr2.density(3.3) + 5/ 3.0 * distr3.density(3.3) +
        0.81873 * distr4.density(3.3) + 1 * distr5.density(3.3)) / (5 + 1.819) +- 1e-5)

    // make sure the original didn't change
    val origDensity = ((distr1.density(3.3) + distr2.density(3.3) + distr3.density(3.3)) / 3)
    inputModel.density((PrincessFeatureCollection(), 3.3)) should be(origDensity +- 1e-5)
  }

  it should "remove points with weight below the threshold" in {
    val environments = List.fill(3)(PrincessFeatureCollection())
    val inputs = List[ScalarPrincessFeature](1.4, 4.1, 6.0)
    random.setSeed(1)
    val inputModel = UpdateableKernelDensityInputModel(environments, inputs, 0.1, 5,
      IdentityBuilder[PrincessFeatureCollection](), IdentityBuilder[ScalarPrincessFeature]())

    var updatedInputModel = inputModel.update(2, (PrincessFeatureCollection(), 2.0))

    val bw = Math.sqrt(updatedInputModel.kde.bandwidth.getEntry(0, 0))
    val distr1 = new NormalDistribution(1.4, bw)
    val distr2 = new NormalDistribution(4.1, bw)
    val distr3 = new NormalDistribution(6.0, bw)
    val distr4 = new NormalDistribution(2.0, bw)
    updatedInputModel.density((PrincessFeatureCollection(), 3.3)) should be(
      (5 / 3.0 * distr1.density(3.3) + 5 / 3.0 * distr2.density(3.3) + 5/ 3.0 * distr3.density(3.3) +
        1 * distr4.density(3.3)) / (5 + 1) +- 1e-5
    )

    val distr5 = new NormalDistribution(1.0, bw)
    updatedInputModel = updatedInputModel.update(400, (PrincessFeatureCollection(), 1.0)) // drop off previous observation
    updatedInputModel.density((PrincessFeatureCollection(), 3.3)) should be(
      (5 / 3.0 * distr1.density(3.3) + 5 / 3.0 * distr2.density(3.3) + 5/ 3.0 * distr3.density(3.3) +
        1 * distr5.density(3.3)) / (5 + 1) +- 1e-5
    )
  }
}