package com.cra.princess.inputmodel

import com.cra.figaro.util._
import com.cra.princess.componentmodel.MultivariateKernelDensityEstimator
import com.cra.princess.core._
import com.cra.princess.core.PrincessTypeImplicits._
import org.apache.commons.math3.distribution.{MultivariateNormalDistribution, NormalDistribution}
import org.apache.commons.math3.linear.MatrixUtils
import org.scalatest.{FlatSpec, Matchers}

/**
 * Verifies that the KDE accurately computes densities
 * @author Dan Garant
 */
class KernelDensityInputModelTest extends FlatSpec with Matchers {
  
  it should "compute accurate univariate densities" in {
    val kde = new MultivariateKernelDensityEstimator(Array(Array(1.0), Array(2.0), Array(3.0)))
    val stdDev = Math.sqrt(kde.bandwidth.getEntry(0, 0))
    val distr1 = new NormalDistribution(1.0, stdDev)
    val distr2 = new NormalDistribution(2.0, stdDev)
    val distr3 = new NormalDistribution(3.0, stdDev)
    
    val combinedDensity = (distr1.density(2.5) + distr2.density(2.5) + distr3.density(2.5)) / 3.0
    kde.density(Array(2.5)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(100.0)) should be(0.0 +- 1e-5)
  }
  
  it should "compute accurate multivariate densities" in {
    val kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 1.0), Array(2.0, 4.0), Array(3.0, 6.0)))
    val covar = kde.bandwidth.getData
    val distr1 = new MultivariateNormalDistribution(Array(1.0, 1.0), covar)
    val distr2 = new MultivariateNormalDistribution(Array(2.0, 4.0), covar)
    val distr3 = new MultivariateNormalDistribution(Array(3.0, 6.0), covar)
    
    val combinedDensity = (distr1.density(Array(3.0, 3.0)) + distr2.density(Array(3.0, 3.0)) + distr3.density(Array(3.0, 3.0))) / 3.0
    kde.density(Array(3.0, 3.0)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(100.0, 100.0)) should be(0.0 +- 1e-5)    
  }
  
  it should "handle dimensions with zero variance" in {
    var kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 1.0), Array(1.0, 4.0), Array(1.0, 6.0)))
    val covar = kde.bandwidth.getData()(0)(0)
    val distr1 = new NormalDistribution(1.0, Math.sqrt(covar))
    val distr2 = new NormalDistribution(4.0, Math.sqrt(covar))
    val distr3 = new NormalDistribution(6.0, Math.sqrt(covar))
    
    val combinedDensity = (distr1.density(3.0) + distr2.density(3.0) + distr3.density(3.0)) / 3.0
    kde.density(Array(1.0, 3.0)) should be(combinedDensity +- 1e-5)
    
    kde.density(Array(1.0001, 3.0)) should be(0.0 +- 1e-5)

    kde = new MultivariateKernelDensityEstimator(Array(Array(1.0, 495.0), Array(1.0, 500.0), Array(1.0, 505.0)))
    val sVal = kde.sample()
    sVal(0) should be (1.0)
    sVal(1) should be > (50.0)
  }
  
  "A KernelDensityInputModel" should "appropriately wrap environment and input types" in {
    val environments = List[PrincessFeatureCollection](
        PrincessFeatureCollection(Array(1.1, 2.1), Array(3.0, 4.0)),
        PrincessFeatureCollection(Array(5.2, 6.1), Array(7.0, 8.0)),
        PrincessFeatureCollection(Array(9.3, 10.1), Array(11.0, 12.0)))
    val inputs = List[ScalarPrincessFeature](1.4, 4.1, 6.0)
    random.setSeed(1)
    val inputModel = KernelDensityInputModel(environments, inputs, 
        IdentityBuilder[PrincessFeatureCollection](), IdentityBuilder[ScalarPrincessFeature]())
    
    random.setSeed(1)
    val kde = new MultivariateKernelDensityEstimator(List(Array(1.1, 2.1, 3.0, 4.0, 1.4),
        Array(5.2, 6.1, 7.0, 8.0, 4.1),
        Array(9.3, 10.1, 11.0, 12.0, 6.0)))
    inputModel.density(PrincessFeatureCollection(Array(3.0, 4.0), Array(5.0, 6.0)), 3.0) should be(kde.density(Array(3.0, 4.0, 5.0, 6.0, 3.0)) +- 1e-5)
    inputModel.density(PrincessFeatureCollection(Array(30.0, 40.0), Array(50.0, 60.0)), 30.0) should be(0.0 +- 1e-5)
    
    random.setSeed(1)
    val samplePointKde = kde.sample()
    
    random.setSeed(1)
    val samplePointIm = inputModel.generateRandomness()
    samplePointKde should equal(samplePointIm)
    
    val unwrapped = inputModel.generateValue(samplePointIm)
    
    val subfeat1 = unwrapped._1.subfeatures(0).asInstanceOf[VectorPrincessFeature]
    val subfeat2 = unwrapped._1.subfeatures(1).asInstanceOf[VectorPrincessFeature]
    subfeat1.value.getEntry(0) should equal(samplePointKde(0))
    subfeat1.value.getEntry(1) should equal(samplePointKde(1))
    subfeat2.value.getEntry(0) should equal(samplePointKde(2))
    subfeat2.value.getEntry(1) should equal(samplePointKde(3))    
    unwrapped._2.value should equal(samplePointKde(4))
    
    // now try with matrices
    val matrixInputs = List[PrincessFeatureCollection](
        PrincessFeatureCollection(MatrixUtils.createRealDiagonalMatrix(Array(1.0, 2.0)), MatrixUtils.createRealDiagonalMatrix(Array(1.1, 2.1))), 
        PrincessFeatureCollection(MatrixUtils.createRealDiagonalMatrix(Array(3.0, 4.0)), MatrixUtils.createRealDiagonalMatrix(Array(3.1, 4.1))), 
        PrincessFeatureCollection(MatrixUtils.createRealDiagonalMatrix(Array(5.0, 6.0)), MatrixUtils.createRealDiagonalMatrix(Array(5.1, 6.1))))
    val inputModel2 = KernelDensityInputModel(environments, matrixInputs, 
        IdentityBuilder[PrincessFeatureCollection](), IdentityBuilder[PrincessFeatureCollection]())
     val kde2 = new MultivariateKernelDensityEstimator(List(Array(1.0, 2.0, 3.0, 4.0, 1.0, 0.0, 0.0, 2.0),
        Array(5.0, 6.0, 7.0, 8.0, 3.0, 0.0, 0.0, 4.0),
        Array(9.0, 10.0, 11.0, 12.0, 6.0, 5.0, 0.0, 0.0, 6.0)))
    
      val density1 = inputModel2.density(
          (PrincessFeatureCollection(Array(3.1, 4.1), Array(5.1, 6.1)), 
          PrincessFeatureCollection(MatrixUtils.createRealDiagonalMatrix(Array(1.2, 2.2)), MatrixUtils.createRealDiagonalMatrix(Array(1.3, 2.3)))))
          
      density1 should be(kde.density(Array(3.1, 4.1, 5.1, 6.1, 1.2, 0.0, 0.0, 2.2, 1.3, 0.0, 0.0, 2.3)) +- 1e-5)
    
      val density2 = inputModel2.density(
          (PrincessFeatureCollection(Array(30.0, 40.0), Array(50.0, 60.0)), 
          PrincessFeatureCollection(MatrixUtils.createRealDiagonalMatrix(Array(100.0, 200.0)), MatrixUtils.createRealDiagonalMatrix(Array(150.0, 250.0))))) 
          
      density2 should be(0.0 +- 1e-5)  
    
    val rand = inputModel2.generateRandomness()
    val genVal = inputModel2.generateValue(rand)
    genVal._1.asInstanceOf[PrincessFeatureCollection].subfeatures.length should be(2)
    genVal._1.asInstanceOf[PrincessFeatureCollection].subfeatures(0).asInstanceOf[VectorPrincessFeature].value.getDimension should be(2)
    
    genVal._2.asInstanceOf[PrincessFeatureCollection].subfeatures.length should be(2)
    genVal._2.asInstanceOf[PrincessFeatureCollection].subfeatures(0).asInstanceOf[MatrixPrincessFeature].value.getRowDimension should be(2)
    genVal._2.asInstanceOf[PrincessFeatureCollection].subfeatures(0).asInstanceOf[MatrixPrincessFeature].value.getColumnDimension should be(2)
  }  
}