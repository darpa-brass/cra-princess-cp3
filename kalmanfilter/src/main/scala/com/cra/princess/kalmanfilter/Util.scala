package com.cra.princess.kalmanfilter

/**
  * Created by klu on 7/17/2018.
  */
object Util {
  def generateRandomSample(range: (Double, Double) = (0.0, 1.0)): Double ={
    val (min, max) = range
    Math.random() * (max - min) + min
  }
}
