package com.cra.princess.elements

import com.cra.figaro.algorithm.sampling.{Importance, MetropolisHastings, ProposalScheme}
import com.cra.figaro.language.Universe
import com.cra.figaro.util._
import com.cra.princess.{_}
import org.scalatest.{FlatSpec, Matchers}

/**
 * Verifies that the KDE accurately computes densities
  *
  * @author Dan Garant
 */
class KernelDensityTest extends FlatSpec with Matchers {

  val kernel = (v1:Double) => (v2:Double) => if((v1 - v2) / 3.0 <= 1.0) (3.0 / 4.0) * (1 - math.pow(v1 / 3.0 - v2 / 3.0, 2)) else 0.0

  it should "compute accurate univariate densities when all instances are within the Epanechnikov radius" in {
    Universe.createNew()
    val kde = KernelDensity(Array(1.0, 2.0, 3.0), 3.0, Array(1.0, 0.5, 1.0))
    val k1 = kernel(1.0)
    val k2 = kernel(2.0)
    val k3 = kernel(3.0)

    val combinedDensity = (k1(2.5) + 0.5 * k2(2.5) + k3(2.5)) / 2.5
    kde.density(2.5) should be(combinedDensity +- 1e-5)
  }

  it should "compute accurate univariate densities when some instances are not within the Epanechnikov radius" in {
    Universe.createNew()
    val kde = KernelDensity(Array(1.0, 2.0, 3.0, 4.0, 5.0), 3.0, Array(1.0, 0.5, 1.0, 0.5, 1.0))
    val k1 = kernel(1.0)
    val k2 = kernel(2.0)
    val k3 = kernel(3.0)
    val k4 = kernel(4.0)
    val k5 = kernel(5.0)

    val combinedDensity = (k1(1.5) + 0.5 * k2(1.5) + k3(1.5) + 0.5 * k4(1.5) + k5(1.5)) / 4.0
    kde.density(1.5) should be(combinedDensity +- 1e-5)
  }

  it should "yield accurate marginal expectations" in {
    Universe.createNew()
    val samples = Array.fill(5000)(if(com.cra.figaro.util.random.nextDouble() < 0.7)
      com.cra.figaro.util.random.nextGaussian() else com.cra.figaro.util.random.nextGaussian() + 1.0)
    val kde = KernelDensity(samples)
    val alg = MetropolisHastings(5000, ProposalScheme.default, 100, kde)
    alg.start()
    alg.computeExpectation(kde, (v:Double) => v) should be (0.3 +- 0.1)
  }

  it should "characterize distribution quantiles accurately" in {
    Universe.createNew()
    val samples = Array.fill(5000)(com.cra.figaro.util.random.nextGaussian())
    val kde = KernelDensity(samples)
    val alg = MetropolisHastings(5000, ProposalScheme.default, 100, kde)
    alg.start()
    alg.computeProbability(kde, (v:Double) => v < -1) should be (0.158 +- 0.08)
    alg.computeProbability(kde, (v:Double) => v < 0) should be (0.5 +- 0.05)
    alg.computeProbability(kde, (v:Double) => v > 1) should be (0.158 +- 0.08)
  }
}
