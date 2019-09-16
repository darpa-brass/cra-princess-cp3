package com.cra.princess.training

import com.cra.princess.training.training.TrainingControls

object ControlGenerator {
  // TODO: possibly center around non-transformed/synthesized controls
  def generateRandomControls(params: Map[String, Double], numControls: Int = 1000): List[TrainingControls] = {
    val dimension = params("dimension").toInt
    val min = params("min")
    val max = params("max")
    val range = Math.abs(min - max)
    val randomlySampledControls = (1 to numControls).map{ _ =>
      Array.fill(dimension)(Math.random() * range + min)
    }.toList
    randomlySampledControls
  }
}
