package com.cra.princess.inputmodel

import com.cra.princess._
import com.cra.figaro.language.Name
import com.cra.figaro.language.ElementCollection
import com.cra.figaro.language.Atomic
import com.cra.figaro.util.random

/**
 * Very simple input model which samples independently from observed environments and inputs, giving novel settings zero probability density.
 */
class SimpleInputModel[Env, Input](envValues: List[Env], inputValues: List[Input], name: Name[(Env, Input)], collection: ElementCollection)
    extends InputModel[Env, Input](name, collection) with Atomic[(Env, Input)] {
  type Randomness = (Int, Int)

  def generateRandomness() = {
    (random.nextInt(envValues.length), random.nextInt(inputValues.length))
  }

  def generateValue(rand: Randomness) = {
    (envValues(rand._1), inputValues(rand._1))
  }

  // keep only distinct values for density
  val distinctEnvVals = envValues.toSet
  val distinctInputVals = inputValues.toSet
  val constantDensity = 1.0 / (distinctEnvVals.size * distinctInputVals.size)

  def density(v: (Env, Input)) = {
    if (!distinctEnvVals.contains(v._1) || !distinctInputVals.contains(v._2))
      0
    else
      constantDensity
  }

  override def toString = "SimpleInputModel"
}

object SimpleInputModel {

  def apply[Env, Input](envValues: List[Env], inputValues: List[Input])(implicit name: Name[(Env, Input)], collection: ElementCollection) =
    new SimpleInputModel(envValues, inputValues, name, collection)

}