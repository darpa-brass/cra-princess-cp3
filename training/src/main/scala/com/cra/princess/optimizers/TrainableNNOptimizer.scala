package com.cra.princess.optimizers

import com.cra.princess.optimizer.Trainable
import com.cra.princess.training.actorcritic.ActorCriticTrainer
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}
import com.cra.princess.training.{ExploreExploitPolicy, MOptimizer}

trait TrainableNNOptimizer[I, O] extends Trainable[I, O]{

  val initialState: TrainingState
  val initialControls: TrainingControls
  val policy: ExploreExploitPolicy
  val trainer: ActorCriticTrainer
  val params: Map[String, Double]
  val discountFactor: Double
  val maxBufferSize: Int
  val batchSize: Int

  protected var state: TrainingState = initialState
  protected var prevOptControls: TrainingControls = initialControls
  protected var prevExploreExploitCtrls: TrainingControls = initialControls
  protected var trainCounter = 0
  protected var trainingTime = 0.0

  def train(input: I, output: O): TrainingControls = {
    val (newState, metric) = computeStateAndMetric(input, output)
    trainer.storeTrainingInstance(newState, prevOptControls, prevExploreExploitCtrls, metric)
    if(trainer.bufferSize >= batchSize) {
      trainer.trainActorCriticNetwork(batchSize)
      trainCounter += 1
    }

//    controls.map(c => trainer.getActorCriticNetwork.getReward(c.toList ++ newState.toList)).foreach(println)
    val controls = List(
      Array(-1.0, -1.0),
      Array(1.0, 1.0),
      Array(-1.0, 1.0),
      Array(1.0, -1.0)
    )
//    val controls = ControlGenerator.generateRandomControls(params)
    val mOpt = new MOptimizer(trainer.getActorCriticNetwork)
    val newOptCtrls: TrainingControls = mOpt.getOptimizedControls(controls, newState)
    val newExploreExploitCtrls = policy(newOptCtrls, newState, trainingTime)

    state = newState
    prevOptControls = newOptCtrls
    prevExploreExploitCtrls = newExploreExploitCtrls
    newOptCtrls
  }

  def getTrainCounter: Int = trainCounter
  def resetTrainCounter(): Unit = trainCounter = 0
  def saveParams(actorFile: String = "actorParams.h5", criticFile: String = "criticParams.h5"): Unit =
    trainer.getActorCriticNetwork.saveParams(actorFile, criticFile)

  protected def computeStateAndMetric(input: I, output: O): (TrainingState, TrainingMetric)
}
