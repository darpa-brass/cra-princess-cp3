package com.cra.princess.componentmodel

import org.scalatest.Matchers
import org.scalatest.FlatSpec
import org.apache.commons.math3.linear.ArrayRealVector
import com.cra.princess._
import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.figaro.library.atomic.continuous.AtomicNormal
import com.cra.figaro.language.Chain
import com.cra.figaro.language.Element
import org.apache.commons.math3.stat.StatUtils
import com.cra.figaro.util.random
import com.cra.princess.core.{BoundedScalarPrincessFeature, ScalarPrincessFeature, VectorPrincessFeature}

/**
 * Tests the feature construction performed in the component model
 */
class GaussianProcessComponentModelTest extends FlatSpec with Matchers  {

  type Env = ScalarPrincessFeature
  type Input = VectorPrincessFeature
  type GPType = GaussianProcessComponentModel[Env, Input]
  def V(a:Double*) = new Input(new ArrayRealVector(a.toArray))

  com.cra.figaro.util.random.setSeed(1)
  val nsamples = 100
  val testEnvironment = (0 until nsamples).map(i => new ScalarPrincessFeature(random.nextDouble()))
  val testInputs:List[VectorPrincessFeature] = (0 until nsamples).map(i => V(random.nextDouble() * 2 + 1, random.nextDouble() * 4 + 2)).toList
  val testControl = (0 until nsamples).map(i => Map("A" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0, 1)))
  // linear combination of inputs
  val testMetric1 = (0 until nsamples).map(i => testInputs(i).value.toArray.sum)
  // linear combination of inputs and environment
  val testMetric2 = (0 until nsamples).map(i => testInputs(i).value.toArray.sum + testEnvironment(i).value)
  // linear combination of inputs, environment, and control
  val testMetric3 = (0 until nsamples).map(i =>
    testInputs(i).value.toArray.sum + testEnvironment(i).value + testControl(i)("A").value)

  val metric1Data = (0 until testEnvironment.length).map(i => 
      new ComponentModelData(
          new ComponentModelInput(testEnvironment(i), testInputs(i), testControl(i)), 
            List(testMetric1(i)))) toList
  val metric12Data = (0 until testEnvironment.length).map(i => 
      new ComponentModelData(
          new ComponentModelInput(testEnvironment(i), testInputs(i), testControl(i)), 
            List(testMetric1(i), testMetric2(i)))) toList      
  val metric123Data = (0 until testEnvironment.length).map(i => 
      new ComponentModelData(
          new ComponentModelInput(testEnvironment(i), testInputs(i), testControl(i)), 
            List(testMetric1(i), testMetric2(i), testMetric3(i)))) toList      

  val covarianceFunction = LinearlyNestedCovarianceFunction3(testEnvironment, testInputs, testControl)
  
  "GaussianProcessComponentModelBuilder" should "return as many GP models as metrics" in {
    
    val builder = new GaussianProcessComponentModelBuilder[Env, Input]()
    var gpModel = builder.componentLearner(metric1Data).asInstanceOf[GaussianProcessComponentModel[Env, Input]]
    gpModel.metricModels.length should equal(1)
    
    gpModel = builder.componentLearner(metric12Data).asInstanceOf[GaussianProcessComponentModel[Env, Input]]
    gpModel.metricModels.length should equal(2)    
    
    gpModel = builder.componentLearner(metric123Data).asInstanceOf[GaussianProcessComponentModel[Env, Input]]
    gpModel.metricModels.length should equal(3)    
  }

  def getGPEst(c:Element[Double]) = c.asInstanceOf[AtomicNormal]
  val priorMetric1Variance = StatUtils.variance(testMetric1.toArray)
  val priorMetric2Variance = StatUtils.variance(testMetric2.toArray)
  val priorMetric3Variance = StatUtils.variance(testMetric3.toArray)

  it should "yield reasonably accurate metrics" in {
    
    com.cra.figaro.util.random.setSeed(1)
    val kernelCombinationType = KernelCombinationType.Additive

    // no code or component integration for this test
    val builder = new GaussianProcessComponentModelBuilder[Env, Input](sigmaEstQuantile = Some(0.5), meanFunctionType = MeanFunctionType.Polynomial)
    var gpModel = builder.componentLearner(metric1Data).asInstanceOf[GPType]
    val controls5 = Map("A" -> new BoundedScalarPrincessFeature(0.5, 0, 1))
    val testInput = new ComponentModelInput[Env, Input](0.12, V(1.2, 3.5), controls5)

    var metric1Est = getGPEst(gpModel.apply(testInput)(0))
    metric1Est.mean should be (4.7 +- 0.15)
    metric1Est.variance should be < priorMetric1Variance

    gpModel = builder.componentLearner(metric12Data).asInstanceOf[GPType]
    gpModel.metricModels.length should equal(2)

    var metrics = gpModel.apply(testInput)
    metric1Est = getGPEst(metrics(0))
    metric1Est.mean should be (4.7 +- 0.15)
    metric1Est.variance should be < priorMetric1Variance
    
    var metric2Est = getGPEst(metrics(1))
    metric2Est.mean should be (4.82 +- 0.2)
    metric2Est.variance should be < priorMetric2Variance

    gpModel = builder.componentLearner(metric123Data).asInstanceOf[GPType]
    gpModel.metricModels.length should equal(3)  
    
    metrics = gpModel.apply(new ComponentModelInput[Env, Input](0.61, V(2.1, 2.3), controls5))
    metric1Est = getGPEst(metrics(0))
    metric1Est.mean should be (4.4 +- 1e-1)
    metric1Est.variance should be < priorMetric1Variance
    
    metric2Est = getGPEst(metrics(1))
    metric2Est.mean should be (5.01 +- 1e-1)
    metric2Est.variance should be < priorMetric2Variance
    
    val metric3Est = getGPEst(metrics(2))
    metric3Est.mean should be (5.51 +- 1e-1)
    metric3Est.variance should be < priorMetric3Variance
  }

  it should "perform subset of regressor approximation with limited loss of fidelity" in {
    val kernelCombinationType = KernelCombinationType.Additive

    // no code or component integration for this test
    val builder = new GaussianProcessComponentModelBuilder[Env, Input](sigmaEstQuantile = Some(0.5),
          meanFunctionType = MeanFunctionType.Fixed, regressorSubsetFraction = Option(0.3))
    var gpModel = builder.componentLearner(metric1Data).asInstanceOf[GPType]
    val controls5 = Map("A" -> new BoundedScalarPrincessFeature(0.5, 0, 1))
    val testInput = new ComponentModelInput[Env, Input](0.12, V(1.2, 3.5), controls5)

    var metric1Est = getGPEst(gpModel.apply(testInput)(0))
    metric1Est.mean should be (4.7 +- 3e-1)
    metric1Est.variance should be < priorMetric1Variance
  }

  it should "optimize for multiple control variables" in {
    val multiControls = (0 until nsamples).map(i => Map(
      "A" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0, 1),
      "B" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0, 1)
    ))

    val newMetric = (0 until nsamples).map(i => testInputs(i).value.toArray.sum + testEnvironment(i).value + multiControls(i).values.map(v => v.value).sum)
    val multiControlData = (0 until testEnvironment.length).map(i =>
      new ComponentModelData(
        new ComponentModelInput(testEnvironment(i), testInputs(i), multiControls(i)),
        List(newMetric(i)))).toList

    val builder = new GaussianProcessComponentModelBuilder[Env, Input](sigmaEstQuantile = Some(0.5), meanFunctionType = MeanFunctionType.Polynomial)
    var gpModel = builder.componentLearner(multiControlData).asInstanceOf[GPType]

    val testControls = Map("A" -> new BoundedScalarPrincessFeature(0.5, 0, 1), "B" -> new BoundedScalarPrincessFeature(0.9, 0, 1))
    val testInput = new ComponentModelInput[Env, Input](0.12, V(1.2, 3.5), testControls)
    var metricEst = getGPEst(gpModel.apply(testInput)(0))
    metricEst.mean should be (0.12 + 1.2 + 3.5 + 0.5 + 0.9 +- 1)
    metricEst.variance should be < priorMetric1Variance
  }

  it should "optimize sigmaEstQuantile when not supplied" in {
    val multiControls = (0 until nsamples).map(i => Map(
      "A" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0, 1),
      "B" -> new BoundedScalarPrincessFeature(random.nextDouble(), 0, 1)
    ))

    val newMetric = (0 until nsamples).map(i => testInputs(i).value.toArray.sum + testEnvironment(i).value + multiControls(i).values.map(v => v.value).sum)
    val multiControlData = (0 until testEnvironment.length).map(i =>
      new ComponentModelData(
        new ComponentModelInput(testEnvironment(i), testInputs(i), multiControls(i)),
        List(newMetric(i)))).toList

    val builder = new GaussianProcessComponentModelBuilder[Env, Input](meanFunctionType = MeanFunctionType.Polynomial)
    var gpModel = builder.componentLearner(multiControlData).asInstanceOf[GPType]

    val testControls = Map("A" -> new BoundedScalarPrincessFeature(0.5, 0, 1), "B" -> new BoundedScalarPrincessFeature(0.9, 0, 1))
    val testInput = new ComponentModelInput[Env, Input](0.12, V(1.2, 3.5), testControls)
    var metricEst = getGPEst(gpModel.apply(testInput)(0))
    metricEst.mean should be (0.12 + 1.2 + 3.5 + 0.5 + 0.9 +- 5e-1)
    metricEst.variance should be < priorMetric1Variance

  }
}