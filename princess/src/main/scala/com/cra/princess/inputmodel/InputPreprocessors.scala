package com.cra.princess.inputmodel

/**
  * Applies pre-processing to PRINCESS inputs
  */
trait InputPreprocessor {
  def wrap(sample:Array[Double]):Array[Double]
  def unwrap(flat:Array[Double]):Array[Double]
}

/** Eliminates features with zero variance */
class ZeroVarianceEliminatingPreprocessor(constantIndices:Seq[Int], nonConstantIndices:Seq[Int], constantValues:Seq[Double]) extends InputPreprocessor {

  val indices = (0 until (constantIndices.length + nonConstantIndices.length)).toArray
  val termPermutation = (constantIndices ++ nonConstantIndices).zip(indices).toMap

  override def wrap(sample: Array[Double]): Array[Double] = {
    nonConstantIndices.map(sample(_)).toArray
  }

  override def unwrap(flat: Array[Double]): Array[Double] = {
    val withConstants = (constantValues ++ flat)
    indices.map(i => withConstants(termPermutation(i)))
  }
}

object ZeroVarianceEliminatingPreprocessor {
  def apply(samples:Seq[Array[Double]]) = {
    val firstSample = samples(0)
    val ndim = samples(0).length
    val isConstant = (0 until ndim).map(i => samples.map(_(i)).toSet.size == 1)

    val zeroVarDimensions = (0 until isConstant.length).filter(isConstant)
    val nonzeroVarDimensions = (0 until isConstant.length).filter(!isConstant(_))
    val constantValues = zeroVarDimensions.map(firstSample)
    new ZeroVarianceEliminatingPreprocessor(zeroVarDimensions, nonzeroVarDimensions, constantValues)
  }
}
