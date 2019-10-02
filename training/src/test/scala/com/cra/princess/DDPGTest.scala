package com.cra.princess
import com.cra.princess.training.ddpg.structures.{Actor, NetworkWrapper}
import org.deeplearning4j.nn.gradient.Gradient
import org.deeplearning4j.nn.weights.WeightInit
import org.nd4j.linalg.activations.Activation
import org.nd4j.linalg.api.ndarray.INDArray
import org.nd4j.linalg.factory.Nd4j
import org.nd4j.linalg.primitives
import org.scalatest.{FlatSpec, Matchers}

class DDPGTest extends FlatSpec with Matchers {

  val reluUniformOpt = Some(WeightInit.RELU_UNIFORM)

  "DDPG" should "update target network with behavior network" in {
    val actor1 = new Actor(0.0, 5, 10, false, 0.1, Activation.TANH, weightInit = reluUniformOpt, nodesPerHiddenLayer = 128)
    val input = Array.fill(5)(100.0)
    val out1 = actor1.predictWithBehavior(input).toList
    val out2 = actor1.predictWithTarget(input).toList
    actor1.updateTarget()
    val out3 = actor1.predictWithTarget(input).toList
    assert(out1 != out2 && out1 == out3)

    val actor2 = new Actor(1.0, 5, 10, false, 0.1, Activation.TANH, weightInit = reluUniformOpt, nodesPerHiddenLayer = 128)
    val out4 = actor2.predictWithBehavior(input).toList
    val out5 = actor2.predictWithTarget(input).toList
    actor2.updateTarget()
    val out6 = actor2.predictWithTarget(input).toList
    assert(out4 != out5 && out5 == out6)

    val actor3 = new Actor(Math.random(), 5, 10, true, 0.1, Activation.TANH, weightInit = reluUniformOpt, nodesPerHiddenLayer = 128)
    val out7 = actor3.predictWithBehavior(input).toList
    val out8 = actor3.predictWithTarget(input).toList
    actor3.updateTarget()
    val out9 = actor3.predictWithTarget(input).toList
    val diff = Math.sqrt((out8 zip out9).map { case (x, y) => Math.pow(Math.abs(x - y), 2) }.sum)
    assert(out7 == out8, diff < 0.0001)
  }
  "Multilayer network" should "maintain shape" in {

    val featureArr1 = Array(
      Array(1.0, 1.0, 1.0, 1.0, 1.0)
    )
    val labelArr1 = Array(
      Array(1.0, 1.0, 1.0)
    )

    val featureArr2 = Array(
      Array(2.0, 1.0, 1.0, 1.0, 1.0)
    )
    val labelArr2 = Array(
      Array(2.0, 2.0, 2.0)
    )

    val featureArr3 = Array(
      Array(1.0, 1.0, 1.0, 1.0, 1.0),
      Array(2.0, 1.0, 1.0, 1.0, 1.0)
    )

    val labelArr3 = Array(
      Array(1.0, 1.0, 1.0),
      Array(2.0, 2.0, 2.0)
    )

    val actorFunc: (Int, Int) => Actor = new Actor(0.5, _, _, learningRate = 0.1,
      outputActivation = Activation.TANH,
      weightInit = reluUniformOpt,
      nodesPerHiddenLayer = 128)
    val actor = actorFunc(5, 3)
    val net = actor.behaviorNetwork.dl4jNet

    val (grad1, indArr1) = testHelper(featureArr1, labelArr1, actorFunc(5, 3))
    val (grad2, indArr2) = testHelper(featureArr2, labelArr2, actorFunc(5, 3))
    val (grad3, indArr3) = testHelper(featureArr3, labelArr3, actorFunc(5, 3))

    assert(grad1.gradient.add(grad2.gradient()).equals(grad3.gradient()))

    assert(net.numParams() == 33792)
    assert(grad3.gradient().shape().toList == List(1, net.numParams()))

    assert(indArr1.shape().toList == List(1, 5))
    assert(indArr2.shape().toList == List(1, 5))
    assert(indArr3.shape().toList == List(2, 5))
  }

  "N4DJ" should "perform matrix operations in" in {
    val f1 = Array(
      Array(1.0, 2.0, 3.0),
      Array(4.0, 5.0, 6.0),
      Array(7.0, 8.0, 9.0),
      Array(1.1, 2.1, 3.1)
    )
    val f2 = Array(1.0, 2.0, 3.0)
    val f3 = Array(
      Array(1.0),
      Array(2.0),
      Array(3.0)
    )
    val fa1 = Nd4j.create(f1)
    val fa2 = Nd4j.create(f2)
    val fa3 = Nd4j.create(f3)
    assert(fa1.mmul(fa2.transpose()) == fa1.mmul(fa3))
  }

  private def testHelper(features: Array[Array[Double]],
                         labels: Array[Array[Double]], net: NetworkWrapper): (Gradient, INDArray) = {
    val featureArr = Nd4j.create(features)
    val labelArr = Nd4j.create(labels)
    val pair: primitives.Pair[Gradient, INDArray] =
      net.behaviorNetwork.dl4jNet.calculateGradients(featureArr, labelArr, null, null)
    val (grad, indArr) = (pair.getLeft, pair.getRight)
    (grad, indArr)
  }
}
