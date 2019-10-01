package com.cra.princess.remusclient.navigation
import com.cra.princess.util.PrincessProperties
import org.deeplearning4j.nn.conf.distribution.UniformDistribution
import com.cra.princess.training.ddpg.structures.{Actor, Critic}
import org.deeplearning4j.nn.weights.WeightInit
import org.nd4j.linalg.activations.Activation

object DDPGTrainerOptimizerFactory {


  def getDDPGTrainerOptimizer():DDPGTrainerOptimizer = {

    val actorWeightInit = WeightInit.RELU
    val criticWeightInit = WeightInit.RELU

    // There are multiple ways to create an actor and critic - Kenny 9/16/2019
    //val actorWeightDist = new UniformDistribution(PrincessProperties.actorWeightMin, PrincessProperties.actorWeightMax)
    //val criticWeightDist = new UniformDistribution(PrincessProperties.criticWeightMin, PrincessProperties.criticWeightMax)

    val actor = new Actor(PrincessProperties.mixingFactor, PrincessProperties.stateDim, PrincessProperties.actionDim,
      learningRate = PrincessProperties.actorLR,
      outputActivation = Activation.TANH,//Activation.IDENTITY,
      weightInit = Some(actorWeightInit),
      nodesPerHiddenLayer = PrincessProperties.nodesPerHiddenLayer)

    actor.matchTargetToBehavior()
    actor.updateTemp()


    val critic = new Critic(PrincessProperties.mixingFactor, PrincessProperties.stateDim + PrincessProperties.actionDim,
      PrincessProperties.rewardDim,
      learningRate = PrincessProperties.criticLR,
      outputActivation = Activation.TANH,//Activation.IDENTITY,
      weightInit = Some(criticWeightInit),
      nodesPerHiddenLayer = PrincessProperties.nodesPerHiddenLayer)
    critic.matchTargetToBehavior()
    critic.updateTemp()

    // Instantiate and return a new DDPGTrainerOptimizer
    return new DDPGTrainerOptimizer(actor, critic, PrincessProperties.batchSize, PrincessProperties.discountFactor,
      PrincessProperties.delta, PrincessProperties.saveFile, PrincessProperties.windowSize)
  }

}
