package com.cra.princess.elements

import com.cra.figaro.language._
import org.apache.commons.math3.stat.StatUtils

/**
  * Calculates a bivariate kernel density as a product of two univariate kernels.
  * Note that this is not the same as taking a product of two univariate densities---
  * the product-of-kernels approach can model bivariate dependence.
  */
class BaseBivariateKernelDensity(val samples: Seq[(Double, Double)],
                                 val bandwidth1: Double, val bandwidth2:Double) {

  /** Computes the density of a new point */
  def density(point:(Double, Double)):Double = {
    val densities1 = samples.map(s => {
      1.0 / (math.sqrt(2 * math.Pi)) * math.exp(- 0.5 * math.pow((s._1 - point._1) / bandwidth1, 2)) / bandwidth1
    })
    val densities2 = samples.map(s => {
      1.0 / (math.sqrt(2 * math.Pi)) * math.exp(- 0.5 * math.pow((s._2 - point._2) / bandwidth2, 2)) / bandwidth2
    })

    // multiply contributions term-wise rather than multiplying the resulting univariate densities
    densities1.zip(densities2).map(d => d._1 * d._2).sum / samples.length
  }
}

/**
  * A kernel density estimator for bivariate data which uses a product of kernels
  */
class BivariateKernelDensity(kde:BaseBivariateKernelDensity, name: Name[(Double, Double)], collection: ElementCollection)
  extends Element[(Double, Double)](name, collection) with Atomic[(Double, Double)] {

  // randomness is a random index along with a noise value
  type Randomness = (Int, Double, Double)

  /** Generates a random sample index and offset in both dimensions */
  def generateRandomness:Randomness = {
    val idx = com.cra.figaro.util.random.nextInt(kde.samples.length)
    val rand1 = com.cra.figaro.util.random.nextGaussian() * kde.bandwidth1
    val rand2 = com.cra.figaro.util.random.nextGaussian() * kde.bandwidth2
    (idx, rand1, rand2)
  }

  /** Generates a random value from the KD distribution */
  def generateValue(rand:Randomness):(Double, Double) = {
    return (kde.samples(rand._1)._1 + rand._2, kde.samples(rand._1)._2 + rand._3)
  }

  override def toString = "BivariateKernelDensity(bandwidth1=" + kde.bandwidth1 + ", bandwidth2=" + kde.bandwidth2 + ")"

  override def density(t: (Double, Double)): Double = kde.density(t)
}

object BivariateKernelDensity {
  /**
    * Create a kernel density estimator with specified bandwidth
    */
  def apply(samples: Seq[(Double, Double)], bandwidth1: Double, bandwidth2:Double)(implicit name: Name[(Double, Double)], collection: ElementCollection) = {
    val backingDensity = new BaseBivariateKernelDensity(samples, bandwidth1, bandwidth2)
    new BivariateKernelDensity(backingDensity, name, collection)
  }

  /** Creates a kernel density estimator using rule-of-thumb bandwidth*/
  def apply(samples: Seq[(Double, Double)])(implicit name: Name[(Double, Double)], collection: ElementCollection) = {
    val backingDensity = BaseBivariateKernelDensity(samples)
    new BivariateKernelDensity(backingDensity, name, collection)
  }
}

object BaseBivariateKernelDensity {
   /** Creates a kernel density estimator using rule-of-thumb bandwidth*/
  def apply(samples: Seq[(Double, Double)])(implicit name: Name[(Double, Double)], collection: ElementCollection) = {
    val bandwidth1 = 1.06 * math.sqrt(StatUtils.variance(samples.map(_._1).toArray)) * math.pow(samples.length, -1.0 / 5.0)
    val bandwidth2 = 1.06 * math.sqrt(StatUtils.variance(samples.map(_._2).toArray)) * math.pow(samples.length, -1.0 / 5.0)
    new BaseBivariateKernelDensity(samples, bandwidth1, bandwidth2)
  }
}
