package com.cra.princess.elements

import com.cra.figaro.algorithm.sampling.Importance
import com.cra.figaro.language.{Chain, Constant, Inject}
import com.cra.figaro.library.atomic.continuous.{AtomicNormal, Uniform}
import com.cra.figaro.util._
import com.cra.princess.componentmodel._
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess.core.{PrincessFeature, ScalarPrincessFeature}
import org.apache.commons.math3.linear._
import org.apache.commons.math3.stat.StatUtils
import org.scalatest.{FlatSpec, Matchers}

/**
 * Tests the GaussianProcessElement to ensure it returns accurate posterior predictive estimates
 */
class GaussianProcessTest extends FlatSpec with Matchers {
   
  // just a simple linear combination
  val testInputs = List[PrincessFeature](Array(1.0, 2.0), Array(3.0, 4.0), Array(5.0, 6.0), Array(7.0, 8.0), Array(9.0, 10.0))
  val testOutputs = Array(3.0, 7, 11, 15, 19)
  val trainingData = testInputs.zip(testOutputs).map(z => (z._1, z._2))

  random.setSeed(1)
  val estCovarFunc = GaussianCovarianceFunction[PrincessFeature](testInputs)

  it should "produce zero-variance posterior estimates at design points when noise is 0" in {
    val gp = new GaussianProcess[PrincessFeature](estCovarFunc, noiseVariance=0)
    gp.train(trainingData)
    var respDist = gp.model(List(1.0, 2)).asInstanceOf[AtomicNormal]
    respDist.mean should be(3.0 +- 1e-4)
    respDist.variance should be(0.0 +- 1e-4)
    
    respDist = gp.model(Array(3.0, 4.0)).asInstanceOf[AtomicNormal]
    respDist.mean should be(7.0 +- 1e-4)
    respDist.variance should be(0.0 +- 1e-4)
  }
  
  it should "produce non-zero variance posterior estimates at novel points" in {
    // "estimate" RBF parameter from data
    val gp = new GaussianProcess[PrincessFeature](estCovarFunc, noiseVariance=0)
    gp.train(trainingData)
    var respDist = gp.model(Array(1.1, 2.1)).asInstanceOf[AtomicNormal]
    respDist.mean should be(3.0 +- 1.5)
    respDist.variance should be > 1e-5
  }

  it should "rely heavily on the user-specified mean function at points well outside the support" in {
    val gp = new GaussianProcess[ScalarPrincessFeature](GaussianCovarianceFunction[ScalarPrincessFeature](1), noiseVariance=0)
    val testInputs = Seq[ScalarPrincessFeature](1.0, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    val trainingData = testInputs.zip(testInputs.map(t => t.value + 1.0)).toList
    val responseVariance = StatUtils.variance(testInputs.map(i => i.value +1.0).toArray)

    gp.train(trainingData)

    val meanFun = (x:ScalarPrincessFeature) => Math.PI
    gp.updateMeanFunction(meanFun)
    var respDist = gp.model(200).asInstanceOf[AtomicNormal]
    respDist.mean should be (Math.PI +- 1e-3)
    respDist.variance should be (responseVariance +- 1e-2)

    // we should be able to update the mean function post-training
    val newMeanFun = (x:ScalarPrincessFeature) => Math.E
    gp.updateMeanFunction(newMeanFun)
    var newRespDist = gp.model(200).asInstanceOf[AtomicNormal]
    newRespDist.mean should be (Math.E +- 1e-3)
    newRespDist.variance should be (responseVariance +- 1e-2)

    // the mean function should not matter much, however wild, if we have support in the training data
    val hugeMeanFun = (x:ScalarPrincessFeature) => 200.0
    gp.updateMeanFunction(newMeanFun)
    var new2RespDist = gp.model(5.1).asInstanceOf[AtomicNormal]
    new2RespDist.mean should be (6.2 +- 0.1)
    new2RespDist.variance should be < responseVariance / 2.0
  }

  it should "compute accurate log-likelihood" in {
    val covFun = new GaussianCovarianceFunction[ScalarPrincessFeature](1)
    val gp = new GaussianProcess[ScalarPrincessFeature](covFun, noiseVariance=0)
    gp.train(List[(ScalarPrincessFeature, Double)]((0.0, 1.0), (1.0, 2.0), (-1.0, 0.0)))

    val covariance = new Array2DRowRealMatrix(Array(
      Array(1.0, 0.367879, 0.367879),
      Array(0.367879, 1.0, 0.0183156),
      Array(0.367879, 0.183156, 1)
    ))
    val logCovarianceDeterminant = math.log(0.7339515)
    val residualTerm = 2.037315
    val expectedVal = -1/2.0 * logCovarianceDeterminant - 1/2.0 * residualTerm - 3.0/2 * math.log(2 * math.Pi)

    gp.covarianceLikelihood() should be(expectedVal +- 1e-4)
  }
  
  // integration test of sorts
  it should "not fail when used with Figaro's inference algorithms" in {
    val testFeatures = Inject(Uniform(0, 11), Uniform(0, 11))
    
    // GP is the target
    val gp = new GaussianProcess[PrincessFeature](estCovarFunc, noiseVariance=0)
    gp.train(trainingData)
    val gpElt = Chain(testFeatures, (f:List[Double]) => gp.model(f)) 
    val gpSampler = Importance(1000, gpElt)
    gpSampler.start()
    gpSampler.computeExpectation(gpElt, (v:Double) => v)
    gpSampler.kill()
    
    // GP is the parent
    val gpeffect = Chain(gpElt, (v:Double) => if(v > 5) Constant(true) else Constant(false))
    val effectSampler = Importance(1000, gpeffect)
    effectSampler.start()
    effectSampler.computeExpectation(gpeffect, (v:Boolean) => if(v) 1 else 0)
    effectSampler.kill()
  }
}