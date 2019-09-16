package com.cra.princess.training.ddpg.structures

import com.cra.princess.training.training.{TrainingControls, TrainingState}
import org.deeplearning4j.nn.conf.distribution.Distribution
import org.deeplearning4j.nn.weights.WeightInit
import org.nd4j.linalg.activations.Activation
import org.nd4j.linalg.lossfunctions.LossFunctions

trait NetworkWrapper{
  val mixingFactor: Double
  val inputDim: Int
  val outputDim: Int
  val sameSeed: Boolean
  val savedWeightsFile: Option[String]
  protected val (seed1, seed2) = if (sameSeed) (1234, 1234) else (1234, 12345)
  val behaviorNetwork: TrainingNetwork
  val targetNetwork: TrainingNetwork
  val tempNetwork: TrainingNetwork

  def updateTemp(): Unit = tempNetwork.dl4jNet.setParams(behaviorNetwork.params())

  def updateTarget(): Unit = {
    val newParams = targetNetwork.params().mul(mixingFactor).add(behaviorNetwork.params().mul(1 - mixingFactor))
    targetNetwork.setParams(newParams)
  }
  def predictWithTemp(inputs: Array[Double]): Array[Double] = tempNetwork.query(inputs)
  def predictWithBehavior(inputs: Array[Double]): Array[Double] = behaviorNetwork.query(inputs)
  def predictWithTarget(inputs: Array[Double]): Array[Double] = targetNetwork.query(inputs)
  def matchTargetToBehavior(): Unit =
    targetNetwork.setParams(behaviorNetwork.params())
}

class Actor(val mixingFactor: Double, val inputDim: Int, val outputDim: Int,
            val sameSeed: Boolean = true, learningRate: Double,
            val outputActivation: Activation,
            val savedWeightsFile: Option[String] = None,
            val distribution: Option[Distribution] = None,
            val weightInit: Option[WeightInit] = None,
            val nodesPerHiddenLayer: Int) extends NetworkWrapper {
  val behaviorNetwork = new ActorNetwork(inputDim, outputDim, learningRate, outputActivation, Activation.RELU,
    seed1, LossFunctions.LossFunction.MSE, distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)
  val targetNetwork = new ActorNetwork(inputDim, outputDim, learningRate, outputActivation,  Activation.RELU,
    seed2, LossFunctions.LossFunction.MSE, distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)
  val tempNetwork = new ActorNetwork(inputDim, outputDim, learningRate, outputActivation, Activation.RELU,
    seed1, LossFunctions.LossFunction.L1, distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)

  /**
    * @param sBatch - Array of TrainingState
    * @param aBatch - Array of TrainingControl
    */
  def train(sBatch: Array[Array[Double]], aBatch: Array[Array[Double]]): Unit =
    behaviorNetwork.train(sBatch, aBatch)
}

class Critic(val mixingFactor: Double, val inputDim: Int, val outputDim: Int,
             val sameSeed: Boolean = true, learningRate: Double,
             val outputActivation: Activation,
             val savedWeightsFile: Option[String] = None,
             val distribution: Option[Distribution] = None,
             val weightInit: Option[WeightInit] = None,
             val nodesPerHiddenLayer: Int) extends NetworkWrapper {
  val behaviorNetwork = new CriticNetwork(inputDim, outputDim, learningRate, outputActivation, Activation.RELU,
    seed1, LossFunctions.LossFunction.MSE,  distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)
  val targetNetwork = new CriticNetwork(inputDim, outputDim, learningRate, outputActivation, Activation.RELU,
    seed2, LossFunctions.LossFunction.MSE,  distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)
  val tempNetwork = new CriticNetwork(inputDim, outputDim, learningRate, outputActivation, Activation.RELU,
    seed1, LossFunctions.LossFunction.L1, distribution, weightInit, savedWeightsFile, nodesPerHiddenLayer)

  def predictWithTarget(state: TrainingState, action: TrainingControls): Array[Double] =
    targetNetwork.query(state ++ action)

  /**
    * @param sBatch - Array of TrainingState
    * @param aBatch - Array of TrainingControl
    * @param rewards - Array of Discounted Future Reward
    */
  def train(sBatch: Array[Array[Double]], aBatch: Array[Array[Double]], rewards: Array[Double]): Unit = {
    val inputs = (sBatch zip aBatch).map{case (state, action) => state ++ action}
    behaviorNetwork.train(inputs, rewards.map(Array(_)))
  }
}