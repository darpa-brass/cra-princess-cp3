package com.cra.princess.training

package object training {
  type TrainingMetric = Double
  type TrainingState = Array[Double]
  type TrainingControls = Array[Double]

  def normalizeInputs(xs: Array[Array[Double]], resMin: Double = -10.0, resMax: Double = 10.0): Array[Array[Double]] =
    xs.map{ x => normalizeInput(x, resMin, resMax)}

  def normalizeInput(x: Array[Double], resMin: Double, resMax: Double): Array[Double] =
    x.map{ v =>(v - resMin)/(resMax - resMin) - 0.5}

  def generateRandomSample(range: (Double, Double) = (0.0, 1.0)): Double ={
    val (min, max) = range
    Math.random() * (max - min) + min
  }
}
