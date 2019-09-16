package com.cra.princess.training

package object training {

  type TrainingTime = Double
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

  def permutationsWithRepetitions[T](input : List[T], n : Int) : List[List[T]] = {
    require(input.nonEmpty && n > 0)
    n match {
      case 1 => for (el <- input) yield List(el)
      case _ => for (el <- input; perm <- permutationsWithRepetitions(input, n - 1)) yield el :: perm
    }
  }
}
