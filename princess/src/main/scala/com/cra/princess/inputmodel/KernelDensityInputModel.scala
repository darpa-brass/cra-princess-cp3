package com.cra.princess.inputmodel

import com.cra.princess._
import com.cra.princess.componentmodel._
import com.cra.figaro.language._
import com.cra.princess.core.{InstanceBuilder, PrincessFeature}
import com.cra.princess.util.PrincessTypeUtility

/**
  * Wrapper around KernelDensityEstimator to meet InputModel contract
  */
class KernelDensityInputModel[Env <: PrincessFeature, Input <: PrincessFeature]
(samples: Seq[(Env, Input)], envBuilder: InstanceBuilder[Env], inputBuilder: InstanceBuilder[Input], name: Name[(Env, Input)], collection: ElementCollection)
  extends InputModel[Env, Input](name, collection) with Atomic[(Env, Input)] {

  // a random point drawn from one of the MVNs centered at a sample
  type Randomness = Array[Double]

  val numEnvFeatures = PrincessTypeUtility.flatten(samples(0)._1).length
  val flattenedSamples = samples.map(s => PrincessTypeUtility.flatten(s._1) ++ PrincessTypeUtility.flatten(s._2) toArray)

  val kde = new MultivariateKernelDensityEstimator(flattenedSamples)

  def generateRandomness(): Randomness = {
    kde.sample()
  }

  def generateValue(rand: Randomness): (Env, Input) = {
    PrincessTypeUtility.unflatten(samples(0), rand, envBuilder, inputBuilder)
  }

  def density(t: (Env, Input)): Double = {
    val flattened = PrincessTypeUtility.flatten(t._1).toArray ++ PrincessTypeUtility.flatten(t._2)
    kde.density(flattened.toArray)
  }
}

object KernelDensityInputModel {

  def apply[Env <: PrincessFeature, Input <: PrincessFeature]
  (envValues: List[Env], inputValues: List[Input], envBuilder: InstanceBuilder[Env], inputBuilder: InstanceBuilder[Input])
  (implicit name: Name[(Env, Input)], collection: ElementCollection) = {
    if (envValues.length != inputValues.length)
      throw new IllegalArgumentException("The number of environments (" + envValues.length + ") does not match the number of inputs (" + inputValues.length + ")")
    new KernelDensityInputModel(envValues zip inputValues, envBuilder, inputBuilder, name, collection)
  }
}