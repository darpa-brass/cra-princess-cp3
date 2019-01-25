package com.cra.princess.training

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

import scala.collection.mutable.ArrayBuffer
import scala.util.Random

class ActorCriticTrainer(actorParamsFile: String, criticParamsFile: String, discountFactor: Double) {

  private val actorCriticNetwork: ActorCriticNetwork = D4JOptimizer(actorParamsFile, criticParamsFile)
  private var optimalControls: TrainingControls = Array.fill(actorCriticNetwork.actorOutputDim)(0.0)
  private var exploreExploitControls: TrainingControls = Array.fill(actorCriticNetwork.actorOutputDim)(0.0)
  private var currentState: TrainingState = Array.fill(actorCriticNetwork.actorInputDim)(0.0)
  private var nextState: TrainingState = Array.fill(actorCriticNetwork.actorInputDim)(0.0)
  private var metric: TrainingMetric = 0.0
  private val replayBuffer = ArrayBuffer.empty[(TrainingState, TrainingControls, TrainingControls, TrainingMetric)]

  def trainActorCriticNetwork(batchSize: Int): Unit = {
    val batch = getMiniBatch(batchSize).indices.flatMap{ i =>
      if(i < replayBuffer.length - 1) {
        val (currState: TrainingState, optCtrls: TrainingControls, expCtrls, m) = replayBuffer(i)
        val (nxtState, _, _ ,_) = replayBuffer(i + 1)
        val nextControls = actorCriticNetwork.optimize(nxtState.toList)
        val m0 = m + discountFactor * actorCriticNetwork.getReward((nxtState ++ nextControls).toList)
        Some(((nxtState, optCtrls), (currState ++ expCtrls, m0)))
      }
      else None
    }
    val (actorData,  criticData) = batch.unzip
    val (actorI, actorO) = actorData.unzip
    val (criticI, criticO) = criticData.unzip
    actorCriticNetwork.actorForwardPass(actorI.toArray, actorO.toArray)
    actorCriticNetwork.criticForwardPass(criticI.toArray, criticO.toArray)
  }

  def getMiniBatch(batchSize: Int): List[(TrainingState, TrainingControls, TrainingControls, TrainingMetric)] =
    Random.shuffle(replayBuffer.toList).take(batchSize)


  def storeTrainingInstance(newState: TrainingState, newOptCtrls: TrainingControls,
                            newExploreExploitCtrls: TrainingControls, newMetric: TrainingMetric): Unit = {
    currentState = nextState
    nextState = newState
    optimalControls = newOptCtrls
    exploreExploitControls = newExploreExploitCtrls
    metric = newMetric

    val nextControls = actorCriticNetwork.optimize(nextState.toList)
    val discountedReward = metric + discountFactor * actorCriticNetwork.getReward((nextState ++ nextControls).toList)
    val instance = (currentState, optimalControls, exploreExploitControls, discountedReward)
    replayBuffer += instance
  }

  def resumeSimulator(): Unit = {}
}