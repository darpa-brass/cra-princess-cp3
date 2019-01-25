package com.cra.princess.util

trait FeatureScaler {
  def scale(input:Seq[Double]):Seq[Double]
  def scaleAll(inputs:Seq[Seq[Double]]):Seq[Seq[Double]] = inputs.map(scale(_))
}

/**
  * Scales numeric vectors to [0,1] bounds
  * @param data A table of data used to obtain data bounds
  */
class UnitFeatureScaler(data:Seq[Seq[Double]]) extends FeatureScaler {
  val ndim = data(0).size
  val minVals = (0 until ndim).map(i => data.map(_ (i)).min)
  val maxVals = (0 until ndim).map(i => data.map(_ (i)).max)

  override def scale(input: Seq[Double]) = (0 until ndim).map(d =>
    if (maxVals(d) == minVals(d)) 0 else (input(d) - minVals(d)) / (maxVals(d) - minVals(d)))
}
