package com.cra.princess.testharness.example

import com.cra.figaro.language.Universe
import org.apache.commons.math3.linear.Array2DRowRealMatrix
import org.apache.commons.math3.linear.DiagonalMatrix
import com.cra.figaro.library.atomic.continuous.MultivariateNormal

class TestDataGenerator(range: Double, scale: Double, seed: Int = 13) {

  val random = new scala.util.Random(seed)
  com.cra.figaro.util.setSeed(seed)

  def generateCovariance(dim: Int, diagonalOnly: Boolean = true): List[List[Double]] = {
    val cov = if (diagonalOnly) {
    	val covs = Array.fill(dim)(random.nextDouble*scale)
    	new DiagonalMatrix(covs)
    } else {
      val rm = new Array2DRowRealMatrix(dim, dim)
      for (i <- 0 until dim) {
        for (j <- 0 until dim) {
          rm.setEntry(i, j, random.nextDouble)
        }
      }
      val symm = rm.multiply(rm.transpose())
      symm.scalarMultiply(scale * range)
    }
    val covAsList = (for (i <- 0 until dim) yield {
      List(cov.getRowVector(i).toArray(): _*)
    }).toList
    covAsList
  }

  def generateMeans(dim: Int) = {
    List.fill(dim)(random.nextDouble * range)
  }

  def generate(numClusters: Int, dim: Int, numDataPoints: Int, diagonalOnly: Boolean): (List[Array[Double]], List[Int]) = {
    val u = new Universe
    val normals = List.fill(numClusters) {
      val mean = generateMeans(dim)
      val cov = generateCovariance(dim, diagonalOnly)
      MultivariateNormal(mean, cov)
    }

    val data = List.fill(numDataPoints) {
      val c = random.nextInt(numClusters)
      val normal = normals(random.nextInt(numClusters))
      normal.generate
      (normal.value.toArray, c)
    }
    data.unzip
  }

}