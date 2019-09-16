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


class ActorNetwork(val inputDim: Int, val outputDim: Int, val learningRate: Double,
                   val outputActivation: Activation,
                   val hiddenActivation: Activation = Activation.RELU,
                   val randomSeed: Int = 1234, val loss: LossFunctions.LossFunction,
                   val distribution: Option[Distribution] = None,
                   val weightInit: Option[WeightInit] = None,
                   val savedWeightsFile: Option[String] = None,
                   val nodesPerHiddenLayer: Int,
                   val numLayers: Int = 3) extends TrainingNetwork {

  /**
    * @param stateArr - state vector
    * @param actionArr - control vector
    * @param criticGrads - gradients of action w.r.t to output and weight
    * @return actor gradient
    */
  def calculateGradient(stateArr: Array[TrainingState],
                        actionArr: Array[TrainingControls],
                        criticGrads: INDArray, delta: Double): INDArray = {
    require(stateArr.length == actionArr.length)
    require(stateArr.length == criticGrads.rows)
    val policyGrads: Seq[INDArray] = stateArr.indices.map{ i =>
      val actorGradient = computeGradientsForAllWeightsAndOutputs(stateArr(i), actionArr(i), delta)
      actorGradient.mmul(criticGrads.getRow(i).dup().transpose())
    }
    val zeroMatrix = Nd4j.zeros(policyGrads.head.rows().toLong, policyGrads.head.columns().toLong)
    val sum: INDArray = policyGrads.foldLeft(zeroMatrix)((a: INDArray, b: INDArray) => a.add(b))
    sum.div(stateArr.length.toDouble).transpose()
  }

  private def computeGradientsForAllWeightsAndOutputs(stateArr: TrainingState,
                                                      actionArr: TrainingControls, delta: Double): INDArray = {
    val jacobian: Array[Array[Double]] = actionArr.indices.map{ i =>
      actionArr.updated(i, actionArr(i) + delta)
    }.map{ error =>
      val pair: primitives.Pair[Gradient, INDArray] =
        dl4jNet.calculateGradients(Nd4j.create(stateArr), Nd4j.create(error), null, null)
      pair.getLeft.gradient().toDoubleVector
    }.toArray
    Nd4j.create(jacobian).transpose()
  }

  def applyGradient(pg: INDArray): Unit = dl4jNet.setParams(dl4jNet.params().add(pg.mul(learningRate)))
}