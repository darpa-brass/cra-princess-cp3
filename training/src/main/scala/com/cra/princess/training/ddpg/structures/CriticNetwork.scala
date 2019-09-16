package com.cra.princess.training.ddpg.structures

import com.cra.princess.training.training.{TrainingControls, TrainingState}
import org.deeplearning4j.nn.conf.distribution.Distribution
import org.deeplearning4j.nn.gradient.Gradient
import org.deeplearning4j.nn.weights.WeightInit
import org.nd4j.linalg.activations.Activation
import org.nd4j.linalg.api.ndarray.INDArray
import org.nd4j.linalg.factory.Nd4j
import org.nd4j.linalg.lossfunctions.LossFunctions
import org.nd4j.linalg.primitives

/**
  * Estimates the future discounted reward - type double
  *
  * @param inputDim - Int
  * @param outputDim - Int
  * @param randomSeed - Int
  */
class CriticNetwork(val inputDim: Int, val outputDim: Int, val learningRate: Double,
                    val outputActivation: Activation = Activation.IDENTITY,
                    val hiddenActivation: Activation = Activation.RELU,
                    val randomSeed: Int = 1234, val loss: LossFunctions.LossFunction,
                    val distribution: Option[Distribution] = None,
                    val weightInit: Option[WeightInit] = None,
                    val savedWeightsFile: Option[String] = None,
                    val nodesPerHiddenLayer: Int,
                    val numLayers: Int = 1) extends TrainingNetwork {

  /**
    * @param stateArr - batch of states
    * @param actionArr - batch of controls
    * @param labelArr - batch of discounted future rewards
    * @return
    */
  def calculateGradient(stateArr: Array[TrainingState],
                        actionArr: Array[TrainingControls],
                        labelArr: Array[Double],
                        delta: Double): INDArray = {
    val features = Nd4j.create((stateArr zip actionArr).map{case (s,a) => s ++ a})
    val deltaLabelArr = labelArr.map(l => l+delta)
    val labels = Nd4j.create(deltaLabelArr.map(Array(_)))
    val pair: primitives.Pair[Gradient, INDArray] = dl4jNet.calculateGradients(features, labels, null, null)
    val indArr = pair.getRight
    val stateDim = stateArr.head.length
    val actionDim = actionArr.head.length
    val featureDim = stateDim + actionDim
    val gradients = indArr.getColumns(stateDim until featureDim:_*)
    gradients
  }
}