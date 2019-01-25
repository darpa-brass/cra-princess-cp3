/*
 * KernelDensity.scala
 * Element representing a kernel density estimate
 *
 * Created By:      Dan Garant (dgarant@cra.com)
 * Creation Date:   May 27, 2016
 *
 * Copyright 2016 Avrom J. Pfeffer and Charles River Analytics, Inc.
 * See http://www.cra.com or email figaro@cra.com for information.
 *
 * See http://www.github.com/p2t2/figaro for a copy of the software license.
 */

package com.cra.princess.elements

import com.cra.figaro.language._
import com.cra.princess.util.KdTree
import org.apache.commons.math3.stat.StatUtils

import scala.collection.JavaConverters._

/**
  * Performs density estimation using an Epanechnikov kernel to smooth density estimates around observed inputs.
  *
  * @param samples Observed points
  * @param bandwidth Parameter of kernel
  */
class KernelDensity(name: Name[Double], val samples: Seq[Double],
                    val bandwidth: Double, val weights:Seq[Double],
                    collection: ElementCollection)
  extends Element[Double](name, collection) with Atomic[Double] {

  // randomness is a random index along with a noise value
  type Randomness = (Int, Double)
  val totalWeight = weights.sum

  private val kdTree = new KdTree.Manhattan[Int](1, samples.length * 2)
  (0 until samples.length).foreach(i => kdTree.addPoint(Array(samples(i) / bandwidth), i))

  private def randomIndex():Int = {
    val exprates = weights.map(w => -math.log(com.cra.figaro.util.random.nextDouble()) / w)
    (0 until exprates.length).min(Ordering.by[Int, Double](i => exprates(i)))
  }

  /** Generates a random sample index and offset */
  def generateRandomness:Randomness = {
    val idx = randomIndex()
    val rand = com.cra.figaro.util.random.nextGaussian() * bandwidth
    (idx, rand)
  }

  override def nextRandomness(rand: Randomness) = {
    val idx = randomIndex()
    val noise = com.cra.figaro.util.random.nextGaussian() * bandwidth

    val modelProbRatio = density(samples(idx) + noise) / density(samples(rand._1) + rand._2)
    ((idx, noise), 1.0, modelProbRatio)
  }

  /** Generates a random value from the KD distribution */
  def generateValue(rand:Randomness):Double = {
    return samples(rand._1) + rand._2
  }

  /** Computes the density of a new point */
  def density(point:Double):Double = {
    val scaledPoint = point/bandwidth
    val pointsToConsider = kdTree.pointsWithinDist(Array(scaledPoint), 1, false)
    pointsToConsider.asScala.map(i =>
      weights(i.value) * 3.0 / 4.0 * (1 - math.pow(scaledPoint - samples(i.value) / bandwidth, 2))).sum / totalWeight
  }

  override def toString = "KernelDensity(bandwidth=" + this.bandwidth + ")"
}

object KernelDensity {
  /**
    * Create a kernel density estimator with specified bandwidth
    */
  def apply(samples: Seq[Double], bandwidth: Double, weights:Seq[Double])(implicit name: Name[Double], collection: ElementCollection):KernelDensity = {
    new KernelDensity(name, samples, bandwidth, weights, collection)
  }

  /** Creates a kernel density estimator using rule-of-thumb bandwidth for the Epanechnikov kernel */
  def apply(samples: Seq[Double])(implicit name: Name[Double], collection: ElementCollection):KernelDensity = {
    val bandwidth = 2.34 * math.sqrt(StatUtils.variance(samples.toArray)) * math.pow(samples.length, -1.0 / (5.6))
    KernelDensity(samples, bandwidth, Array.fill(samples.length)(1.0))(name, collection)
  }
}
