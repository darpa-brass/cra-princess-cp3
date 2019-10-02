package com.cra.princess

import com.cra.princess.scenario.{CartpoleSimulator, KalmanFilterDDPGSimulator}
import com.cra.princess.training.TrainedNetwork
import com.cra.princess.training.ddpg.structures.{Actor, Critic}
import com.cra.princess.training.ddpg.{DDPGController, DDPGTrainer, PreTrainer}
import com.cra.princess.training.training.TrainingMetric
import org.deeplearning4j.nn.conf.distribution.UniformDistribution
import org.deeplearning4j.nn.weights.WeightInit
import org.nd4j.linalg.activations.Activation

object DDPGExperiment{

  def main(args: Array[String]): Unit = {
    kfExperiment1()
    kfExperiment2()
    kfExperiment3()
  }

  def kfExperiment1(): Unit = {
    val numFrames = 16
    val frameSize = 4
    val actorSaveFile = "pre_trained_KF_actor.h5"
    val criticSaveFile = "pre_trained_KF_critic.h5"
    val stateDim = frameSize * numFrames
    val actionDim = 1
    val rewardDim = 1
    val numEpisodes = 10000
    val maxStepsPerEpisode = 5000

    for{
      mixingFactor <- List(0.8)
      actorLR = 0.0001
      criticLR = 0.01
      actorWeightMin = -0.000001
      actorWeightMax = 0.000001
      criticWeightMin = -0.000001
      criticWeightMax = 0.000001
    } {
      val actorWeightDist = new UniformDistribution(actorWeightMin, actorWeightMax)
      val criticWeightDist = new UniformDistribution(criticWeightMin, criticWeightMax)
      val actor = new Actor(mixingFactor, stateDim, actionDim,
        learningRate = actorLR,
        outputActivation = Activation.IDENTITY,
        distribution = Some(actorWeightDist),
        nodesPerHiddenLayer = 128)
      val critic = new Critic(mixingFactor, stateDim + actionDim, rewardDim,
        learningRate = criticLR,
        outputActivation = Activation.IDENTITY,
        distribution = Some(criticWeightDist),
        nodesPerHiddenLayer = 128)
      val resultsFileName = s"kf_results.csv"
      val sim = new KalmanFilterDDPGSimulator(resultsFileName, maxStepsPerEpisode)
      val preTrainFileName = "preTrain.csv"
      val defaultCtrls = Array(
        1.0, 0.0, 0.0, 1.0,
        0.3, 0.0, 0.0, 0.3,
        0.1, 0.0, 0.0, 0.2,
        0.0, 0.0, 0.0, 0.0)
      PreTrainer.generateData(numEpisodes, sim, preTrainFileName, actor.outputDim, defaultCtrls)
      println("Started pre-training actor/critic")

      PreTrainer.preTrain(actor, critic, preTrainFileName, -100)
      println("successfully trained with one set of hyper-params....")
      actor.behaviorNetwork.saveParams(actorSaveFile)
//      critic.behaviorNetwork.saveParams(criticSaveFile)
    }
  }

  def kfExperiment2(): Unit ={

    //    val resultsFilesIndices = new FileWriter(new File("kf_results_files_indices.csv"), true)
    //    resultsFilesIndices.append("mixingFactor, actorLR, criticLR, " +
    //      "actorWeightMin, actorWeightMax, criticWeightMin, " +
    //      "criticWeightMax, batchSize, discountFactor, delta, resultsFileName\n")

    /////////////// constant params /////////////////////
    val saveFile = "ddpgKFActor.h5"
    val numFrames = 16
    val frameSize = 4
    val stateDim = frameSize * numFrames
    val actionDim = 1
    val rewardDim = 1
    val numEpisodes = 20000

    val maxStepsPerEpisode = 5000
    var idx = 0

    /////////////// set params for experiments /////////////////////
    for{
      mixingFactor <- List(0.8)
      actorLR = 0.00001
      criticLR = 0.0001
      actorWeightMin = -0.000001
      actorWeightMax = 0.000001
      criticWeightMin = -0.000001
      criticWeightMax = 0.000001
      batchSize = 256
      discountFactor = 0.9
      delta = 0.001
    } {
      val actorWeightInit = WeightInit.RELU
      val criticWeightInit = WeightInit.RELU
      val actorWeightDist = new UniformDistribution(actorWeightMin, actorWeightMax)
      val criticWeightDist = new UniformDistribution(criticWeightMin, criticWeightMax)
      val actor = new Actor(mixingFactor, stateDim, actionDim,
        learningRate = actorLR,
        outputActivation = Activation.TANH,//Activation.IDENTITY,
        weightInit = Some(actorWeightInit),
//        distribution = Some(actorWeightDist),
//        savedWeightsFile = Some("pre_trained_KF_actor.h5"),
        nodesPerHiddenLayer = 128)
      //      println(actor.behaviorNetwork.params())
      actor.matchTargetToBehavior()
      actor.updateTemp()
      val critic = new Critic(mixingFactor, stateDim + actionDim, rewardDim,
        learningRate = criticLR,
        outputActivation = Activation.TANH,//Activation.IDENTITY,
        weightInit = Some(criticWeightInit),
//        distribution = Some(criticWeightDist),
//        savedWeightsFile = Some("pre_trained_KF_critic.h5"),
        nodesPerHiddenLayer = 128)
      critic.matchTargetToBehavior()
      critic.updateTemp()

      val resultsFileName = s"kf_results_$idx.csv"
      val trainer = new DDPGTrainer(actor, critic, batchSize, discountFactor, delta, saveFile)
      val sim = new KalmanFilterDDPGSimulator(resultsFileName, maxStepsPerEpisode)
      DDPGController.train(numEpisodes, List(trainer), simulator = sim)
      //      val params = List(mixingFactor, actorLR, criticLR,
      //        actorWeightMin, actorWeightMax, criticWeightMin, criticWeightMax, batchSize, discountFactor, delta)
      //      resultsFilesIndices.append(s"${params.mkString(",")},$resultsFileName\n")
      idx += 1
    }
  }

  def kfExperiment3(): Unit = {
    val saveFile = "ddpgKFactor.h5"
//    val saveFile = "pre_trained_KF_actor.h5"
    val tn = new TrainedNetwork(saveFile)
    println(s"Params: ${tn.dl4jNet.params()}")
    val simulator = new KalmanFilterDDPGSimulator(resultsFileName = s"kf_results_baseline.csv", maxSteps = 5000)
    for(_ <- 0 until 200) {
      var isTerminal = false
      simulator.reset()
      var totalReward = 0.0
      while (!isTerminal) {
//        val ctrls = tn.query(simulator.getCurrentState)
        val ctrls = Array(0.0)
        println(ctrls.toList)
        val (_, _, reward: TrainingMetric, terminal: Boolean) = simulator.step(List(ctrls))
        isTerminal = terminal
        totalReward += reward
      }
      //println(totalReward)
    }
  }

  def cartpoleExperiment(): Unit = {
    val reluUniformOpt = Some(WeightInit.RELU_UNIFORM)
    val saveFile = "ddpgCartpoleActor.h5"
    val mixingFactor = 0.9
    val stateDim = 4
    val actionDim = 1
    val maxStepsPerEpisode = 10000
    val actor = new Actor(mixingFactor, stateDim, actionDim, learningRate = 0.1,
      outputActivation = Activation.TANH,
      weightInit = reluUniformOpt,
      nodesPerHiddenLayer = 128)
    val critic = new Critic(mixingFactor, stateDim + actionDim, 1, learningRate = 0.1,
      outputActivation = Activation.IDENTITY,
      weightInit = reluUniformOpt,
      nodesPerHiddenLayer = 128)

    val trainer = new DDPGTrainer(actor, critic, batchSize = 64, discountFactor = 0.9, delta = 0.1, saveFile)
    DDPGController.train(
      numEpisodes = 200,
      List(trainer),
      simulator = new CartpoleSimulator("cartpole_results.csv", maxStepsPerEpisode)
    )
    val tn = new TrainedNetwork(saveFile)
    val simulator = new CartpoleSimulator("cartpole_results.csv", maxStepsPerEpisode)
    for (_ <- 0 to 100) {
      var isTerminal = false
      simulator.reset()
      var totalReward = 0.0
      while (!isTerminal) {
        val ctrls = tn.query(simulator.getCurrentState)
        val (_, _, reward: TrainingMetric, terminal: Boolean) = simulator.step(List(ctrls))
        isTerminal = terminal
        totalReward += reward
      }
      println(totalReward)
    }
  }
}

