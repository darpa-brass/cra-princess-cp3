package com.cra.princess.training

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

trait ActorCriticNetwork {
  def actorForwardPass(s: Array[TrainingState], m: Array[TrainingControls])
  def criticForwardPass(s: Array[TrainingState], c: Array[TrainingMetric])
  def optimize(inputs: List[Double]): TrainingControls
  def getReward(inputs: List[Double]): TrainingMetric

  val actorInputDim: Int
  val actorOutputDim: Int
  val criticInputDim: Int
  val criticOutputDim: Int
}
