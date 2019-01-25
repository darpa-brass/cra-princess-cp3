package com.cra.princess.inputmodel

import com.cra.princess.componentmodel._
import com.cra.figaro.language._
import com.cra.princess.core.{InstanceBuilder, PrincessFeature}
import com.cra.princess.util.PrincessTypeUtility
import org.apache.commons.math3.linear.RealMatrix

/**
  * Deprecated - Not used anywhere in core PRINCESS library
  * A Kernel density input model which can be updated with new inputs.
  * This updating is performed by applying a decaying exponential weight terms to the input stream.
  * The input model is seeded with some initial inputs, which are used to estimate the kernel bandwidth and serve as a prior.
  * Each of the initial inputs has weight priorStrength / (# prior samples)
  *
  * @param priorSamples Samples which constitute the prior. These samples will always have weight priorStrength/(# prior samples).
  * @param decayRate Exponential rate (lambda) at which the weight of new points decays.
  *                  Setting decayRate=0.01, for instance, gives a point which was just observed weight 1 and a point observed 100 time units ago weight 0.368.
  * @param priorStrength Total strength of the prior. The newest observation point has input 1.
  * @param threshold Only points with weight greater than this threshold will be maintained so that
  *                  the size of the input pool is upper-bounded by a constant.
  */
@Deprecated
class UpdateableKernelDensityInputModel[Env <: PrincessFeature, Input <: PrincessFeature]
(priorSamples: Seq[(Env, Input)], envBuilder: InstanceBuilder[Env],
 inputBuilder: InstanceBuilder[Input], decayRate: Double, priorStrength:Int, threshold:Double,
 baseName:String,
 name: Name[(Env, Input)], collection: ElementCollection,
 observations:Seq[(Env, Input)] = Seq.empty, observationTimes:Seq[Double] = Seq.empty,
 val bandwidth:RealMatrix = null, val skipDimensions:Set[Int] = Set.empty)
  extends ConditionalInputModel[Env, Input](name, collection) with Atomic[(Env, Input)] {

  // a random point drawn from one of the MVNs centered at a sample
  type Randomness = Array[Double]

  val numEnvFeatures = PrincessTypeUtility.flatten(priorSamples(0)._1).length
  val flattenedSamples = (priorSamples ++ observations).map(s => PrincessTypeUtility.flatten(s._1) ++ PrincessTypeUtility.flatten(s._2) toArray)

  val kde = new MultivariateKernelDensityEstimator(flattenedSamples, bandwidth=bandwidth, skipDimensions=skipDimensions)

  val numPriorSamples = priorSamples.length
  val priorWeights = Array.fill[Double](numPriorSamples)(priorStrength * 1.0 / numPriorSamples)
  val lastObsTime = observationTimes.lastOption
  val obsWeights = observationTimes.map(t => Math.exp(-decayRate * (lastObsTime.get - t)))
  kde.setWeights(priorWeights ++ obsWeights)

  def generateRandomness(): Randomness = {
    kde.sample()
  }

  override def update(time:Double, obs:(Env, Input)):UpdateableKernelDensityInputModel[Env, Input] = {
    new UpdateableKernelDensityInputModel(priorSamples, envBuilder, inputBuilder,
      decayRate, priorStrength, threshold, baseName,
      baseName + "_" + time, collection,
      observations ++ Seq(obs), observationTimes ++ Seq(time),
      kde.bandwidth, skipDimensions ++ kde.zeroVarDimensions.toSet)
  }

  def generateValue(rand: Randomness): (Env, Input) = {
    PrincessTypeUtility.unflatten(priorSamples(0), rand, envBuilder, inputBuilder)
  }

  def density(t: (Env, Input)): Double = {
    val flattened = PrincessTypeUtility.flatten(t._1).toArray ++ PrincessTypeUtility.flatten(t._2)
    kde.density(flattened)
  }
}

object UpdateableKernelDensityInputModel {

  def apply[Env <: PrincessFeature, Input <: PrincessFeature]
  (envValues: List[Env], inputValues: List[Input],
   decayRate: Double, priorStrength:Int,
   envBuilder: InstanceBuilder[Env], inputBuilder: InstanceBuilder[Input],
  threshold:Double=1e-4)
  (implicit name: Name[(Env, Input)], collection: ElementCollection) = {
    if (envValues.length != inputValues.length)
      throw new IllegalArgumentException("The number of environments (" + envValues.length +
        ") does not match the number of inputs (" + inputValues.length + ")")
    new UpdateableKernelDensityInputModel(envValues zip inputValues, envBuilder,
      inputBuilder, decayRate, priorStrength, threshold, name.string, name, collection)
  }
}
