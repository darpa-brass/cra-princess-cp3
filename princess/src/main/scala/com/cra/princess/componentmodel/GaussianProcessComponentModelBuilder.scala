package com.cra.princess.componentmodel

import com.cra.princess.elements.GaussianProcess
import com.cra.princess._
import com.cra.princess.core.{OptimizableComponent, PrincessFeature}
import com.cra.princess.util.Logs
import org.apache.commons.math3.analysis.{MultivariateFunction, MultivariateVectorFunction}
import org.apache.commons.math3.optim.{InitialGuess, MaxEval, MaxIter, SimplePointChecker}
import org.apache.commons.math3.optim.nonlinear.scalar.{GoalType, ObjectiveFunction, ObjectiveFunctionGradient}
import org.apache.commons.math3.optim.nonlinear.scalar.gradient.NonLinearConjugateGradientOptimizer


/** Mean functions supported by the GP Model Builder */
object MeanFunctionType extends Enumeration {
  val Polynomial, Fixed, Clustering, NearestNeighbor = Value
}

/**
 * Constructs a component model using Gaussian processes for conditional density estimation
 *
 * @author Dan Garant
 * @param sigmaEstQuantile The quantile of the empirical distribution of distances between points that will be used as the bandwidth.
  *                         When None, the maximum-likelihood estimate of a finite pool of values is selected (this can be slow).
 * @param noiseVariance Conditional variance of output variable (permitting uncertainty in training data)
 * @param regressorSubsetFraction A fraction of the total points to use, approximating the full GP covariance.
  *                                    Null values indicate that no approximation will be employed
  *                                    See http://www.gaussianprocess.org/gpml/chapters/RW.pdf, sec 8.3
  * @param meanFunctionType Specifies the form of the prior mean
 */
class GaussianProcessComponentModelBuilder[Env <: PrincessFeature, Input <: PrincessFeature]
    (sigmaEstQuantile:Option[Double]=None, noiseVariance:Double=0.1, regressorSubsetFraction:Option[Double] = None,
     meanFunctionType:MeanFunctionType.Value = MeanFunctionType.Fixed)
      extends ComponentModelBuilder[Env, Input] with Logs {

  type MeanFunction = Function1[(Env, Input, ComponentControls), Double]

  // not needed by GP model:
  val optimizableComponent:OptimizableComponent[Env, Input, _] = null

  /**
    * Learns a conditional model of metrics
    * @param componentData Samples of (Env, Input, Control, Metrics) which will be used to train the model
    * @return The trained component model, which uses one Gaussian process regression model per metric
    */
  override def componentLearner(componentData: List[ComponentModelData[Env, Input]]): ComponentModel[Env, Input] = {
    // split the component data up by metric
    val nmetrics = componentData(0).metrics.length
    val ncontrols = componentData(2).componentInput.controls.size
    val envFeatures = componentData.map(_.componentInput.env)
    val inputFeatures = componentData.map(_.componentInput.input)
    val controlFeatures = componentData.map(_.componentInput.controls)

    val augmentedInput = (0 until componentData.length).map(i => (envFeatures(i), inputFeatures(i), controlFeatures(i))).toList

    val metrics = (0 until nmetrics).map(i => componentData.map(c => c.metrics(i)))

    val covarianceFunctions = buildCovarianceFunctions(augmentedInput, metrics)
    var trainedGp:GaussianProcess[(Env, Input, ComponentControls)] = null
    // estimate one GP per metric
    val metricModels = (0 until nmetrics).map(i => {
      val gp = new GaussianProcess(covarianceFunctions(i), noiseVariance=noiseVariance,
          regressorSubsetFraction=regressorSubsetFraction)

      // if this GP uses the same covariance as the previous GP, no need to retrain
      if (trainedGp == null || !(covarianceFunctions(i) eq trainedGp.covarianceFunction)) {
        gp.train(augmentedInput.zip(metrics(i)))
        trainedGp = gp
      } else {
        gp.trainWithSameCovariance(augmentedInput.zip(metrics(i)), trainedGp)
      }

      // optimize the parameters of the requested mean function
      log.trace("Establishing mean function ...")
      val meanFunction:MeanFunction = meanFunctionType match {
        case MeanFunctionType.Fixed => new FixedMeanFunction(metrics(i)).value
        case MeanFunctionType.Polynomial => {
          val function = new OptimizableParabolicMeanFunction[Env, Input](controlFeatures, gp, metrics(i))
          optimizeMeanFunction(function)
        }
        case MeanFunctionType.Clustering => {
          val function = new ClusteringMeanFunction[Env, Input](augmentedInput, gp, metrics(i))
          optimizeMeanFunction(function)
        }
        case MeanFunctionType.NearestNeighbor => {
          val function = new NearestNeighborMeanFunction[Env, Input](augmentedInput, gp, metrics(i))
          optimizeMeanFunction(function)
        }
      }
      gp.updateMeanFunction(meanFunction)
      gp
    }) toList
    
    // at modeling time, query each GP model
    GaussianProcessComponentModel[Env, Input](metricModels)
  }

  /**
    * Builds one covariance function for each metric
    *
    * @param data the data used to evaluate covariance function choices
    * @param metrics the metrics corresponding to the input data
    * @return A sequence of metric-specific covariance functions, in the same order as the supplied metrics
    */
  def buildCovarianceFunctions(data:List[(Env,Input,ComponentControls)], metrics:Seq[Seq[Metric]]):
          Seq[CovarianceFunction[(Env,Input,ComponentControls)]] = {

    val nmetrics = metrics.length
    val envFeatures = data.map(_._1)
    val inputFeatures = data.map(_._2)
    val controlFeatures = data.map(_._3)

    if(sigmaEstQuantile.isDefined) {
      // use same covariance function for each metric
      val covFun = FlatteningGaussianCovarianceFunction3(envFeatures, inputFeatures, controlFeatures, sigmaEstQuantile.get)
      Array.fill(nmetrics)(covFun)
    } else {
      val considerQuantiles = List(0.005, 0.01, 0.05, 0.1, 0.25, 0.5)
      log.trace("Setting sigma quantiles by optimizing likelihood")

      (0 until nmetrics).map(metricIndex => {
        val bestCov = considerQuantiles.map(curquantile => {
          // create the GP with this covariance function
          val curCovar = FlatteningGaussianCovarianceFunction3(envFeatures, inputFeatures, controlFeatures, sigmaEstQuantile = curquantile)
          val gp = new GaussianProcess(curCovar, noiseVariance = noiseVariance, regressorSubsetFraction = regressorSubsetFraction)
          gp.train(data.zip(metrics.head))
          val ll = gp.covarianceLikelihood()

          log.trace("Sigma quantile: " + curquantile + ", likelihood: " + ll)

          (curCovar, curquantile, ll)
        }).sortBy(t => t._3).last

        log.trace("Best covariance for metric " + metricIndex + " has sigma quantile " + bestCov._2)
        bestCov._1
      })
    }
  }

  /**
    * Optimizes the parameters of a mean function with a finite set of parameters
    * @param meanFunction The function to optimize parameters for
    * @return A deterministic function mapping inputs to responses
    */
  def optimizeMeanFunction(meanFunction:FiniteOptimizableMeanFunction[Env, Input]): MeanFunction = {
    log.debug("Optimizing hyperparameters of mean function " + meanFunction + "...")
    val bestParams = meanFunction.parameterSpace.map(params => {
      // it is the responsibility of meanFunction to penalize the likelihood if desired
      val ll = meanFunction.likelihood(params)
      log.debug("\tParameters: " + params.mkString(", ") + ", likelihood: " + ll)
      (params, ll)
    }).max(Ordering.by[(Array[Double], Double), Double](p => p._2))._1

    meanFunction.responseMeanFun(bestParams)
  }

  /**
    * Optimize a mean function with a continuous parameter space, for which we can compute gradients.
    * The GP likelihood is not necessarily convex wrt the mean function parameters, so this identifies a local maximum.
    * @param meanFunction The differentiable mean function we wish to optimize
    * @return A deterministic function mapping inputs to responses
    */
  def optimizeMeanFunction(meanFunction:GradientOptimizableMeanFunction[Env, Input]): MeanFunction = {
    log.debug("Optimizing hyperparameters of mean function " + meanFunction + "...")
    val optimizable = meanFunction
    log.debug("\tOriginal log-likelihood: " + optimizable.likelihood(optimizable.initialParameters))
    log.debug("\tOriginal parameters: " + optimizable.initialParameters.mkString(", "))

    val optimizer = new NonLinearConjugateGradientOptimizer(
      NonLinearConjugateGradientOptimizer.Formula.POLAK_RIBIERE, new SimplePointChecker(Double.PositiveInfinity, 1e-3))
    val objective = new MultivariateFunction() {
      override def value(point: Array[Double]): Double = optimizable.likelihood(point)
    }
    val objectiveGradient = new MultivariateVectorFunction {
      override def value(point: Array[Double]): Array[Double] = optimizable.likelihoodGradient(point)
    }

    val result = optimizer.optimize(new ObjectiveFunction(objective),
      new ObjectiveFunctionGradient(objectiveGradient),
      new InitialGuess(optimizable.initialParameters),
      new MaxEval(10000),
      new MaxIter(500),
      GoalType.MAXIMIZE)
    log.debug("\tFinal log-likelihood: " + result.getValue)
    log.debug("\tFinal parameters: " + result.getPoint.mkString(", "))
    optimizable.responseMeanFun(result.getPoint)
  }

}