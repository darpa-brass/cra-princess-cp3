package com.cra.princess.training.actorcritic

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

import scala.collection.mutable.ArrayBuffer
import scala.util.Random

class ActorCriticTrainer(actorCriticNetwork: ActorCriticNetwork , discountFactor: Double){

  private var optimalControls: TrainingControls = Array.fill(actorCriticNetwork.actorOutputDim)(0.0)
  private var exploreExploitControls: TrainingControls = Array.fill(actorCriticNetwork.actorOutputDim)(0.0)
  private var currentState: TrainingState = Array.fill(actorCriticNetwork.actorInputDim)(0.0)
  private var nextState: TrainingState = Array.fill(actorCriticNetwork.actorInputDim)(0.0)
  private var metric: TrainingMetric = 0.0
  private val replayBuffer = ArrayBuffer.empty[(TrainingState, TrainingControls, TrainingControls, TrainingMetric)]

  def trainActorCriticNetwork(batchSize: Int): Unit = {
    val batch: Seq[((TrainingState, TrainingControls), (TrainingState, TrainingMetric))] = getMiniBatch().indices.flatMap{ i =>
      if(i < replayBuffer.length - 1) {
        val (currState: TrainingState, optCtrls: TrainingControls, expCtrls, m) = replayBuffer(i)
        val (nxtState, _, _ ,_) = replayBuffer(i + 1)
//        val nextControls = actorCriticNetwork.optimize(nxtState.toList)
//        val r = actorCriticNetwork.getReward((nxtState ++ nextControls).toList)
//        val m0 = m + discountFactor * r
        Some(((nxtState, optCtrls), (currState ++ expCtrls, m)))
      }
      else None
    }
    val (actorData,  criticData) = batch.unzip
    val (actorI, actorO) = actorData.unzip // (nextState, optimizedControls)
    val (criticI, criticO) = criticData.unzip // (currentState ++ exploreExploitControls, discountedReward)
    actorCriticNetwork.actorForwardPass(actorI.toArray, actorO.toArray)
    actorCriticNetwork.criticForwardPass(criticI.toArray, criticO.toArray)
    replayBuffer.clear()
  }

  private def getMiniBatch(batchSize: Int = 64): List[(TrainingState, TrainingControls, TrainingControls, TrainingMetric)] =
    if(batchSize == replayBuffer.length) replayBuffer.toList
    else Random.shuffle(replayBuffer.toList).take(batchSize)

  def storeTrainingInstance(newState: TrainingState, newOptCtrls: TrainingControls,
                            newExploreExploitCtrls: TrainingControls, newMetric: TrainingMetric): Unit = {
    currentState = nextState
    nextState = newState
    optimalControls = newOptCtrls
    exploreExploitControls = newExploreExploitCtrls
    metric = newMetric

    //val nextControls = actorCriticNetwork.optimize(nextState.toList)
    val discountedReward = metric //+ discountFactor * actorCriticNetwork.getReward((nextState ++ nextControls).toList)
    val instance = (currentState, optimalControls, exploreExploitControls, discountedReward)
    replayBuffer += instance
  }

  def getActorCriticNetwork: ActorCriticNetwork = actorCriticNetwork
  def bufferSize: Int = replayBuffer.length
  def clearBuffer(): Unit = replayBuffer.clear()
}