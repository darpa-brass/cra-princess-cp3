package com.cra.princess.elements

import org.apache.commons.math3.random.RandomGenerator

/**
 * Wraps the Figaro RNG around the apache math RNG so we can use the apache math multivariate normal .
 * Copied from Figaro MultivariateNormal. 
 */
class ApacheRandomGeneratorWrapper(val rng: scala.util.Random) extends RandomGenerator  {
    def nextBoolean(): Boolean = rng.nextBoolean
    def nextBytes(bytes: Array[Byte]) = rng.nextBytes(bytes)
    def nextDouble() = rng.nextDouble
    def nextFloat() = rng.nextFloat
    def nextGaussian() = rng.nextGaussian
    def nextInt() = rng.nextInt
    def nextInt(n: Int) = rng.nextInt(n)
    def nextLong() = rng.nextLong
    def setSeed(seed: Int) = {}
    def setSeed(seed: Array[Int]) = {}
    def setSeed(seed: Long) = {}
} 