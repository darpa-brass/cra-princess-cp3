package com.cra.princess.training.ddpg.structures

import java.io.File

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.optimizer.{ComponentOptimizer, Trainable}
import com.cra.princess.util.Logs
import org.deeplearning4j.nn.api.OptimizationAlgorithm
import org.deeplearning4j.nn.conf.{MultiLayerConfiguration, NeuralNetConfiguration}
import org.deeplearning4j.nn.conf.distribution.Distribution
import org.deeplearning4j.nn.conf.layers.{DenseLayer, OutputLayer}
import org.deeplearning4j.nn.multilayer.MultiLayerNetwork
import org.deeplearning4j.nn.weights.WeightInit
import org.deeplearning4j.util.ModelSerializer
import org.nd4j.linalg.activations.Activation
import org.nd4j.linalg.api.ndarray.INDArray
import org.nd4j.linalg.factory.Nd4j
import org.nd4j.linalg.learning.config.Adam
import org.nd4j.linalg.lossfunctions.LossFunctions

/**
  * Trait for constructing an untrained network
  * Underlying computation uses DL4J
  */
trait TrainingNetwork extends Logs
  with ComponentOptimizer[Array[Double], Array[Double]]
  with Trainable[Array[Double], Array[Double]]{

  val learningRate: Double
  val numLayers: Int
  val inputDim: Int
  val outputDim: Int
  val randomSeed: Int
  val savedWeightsFile: Option[String]
  val weightInit: Option[WeightInit]
  val distribution: Option[Distribution]
  val outputActivation: Activation
  val hiddenActivation: Activation
  val loss: LossFunctions.LossFunction
  val nodesPerHiddenLayer: Int

  val dl4jNet: MultiLayerNetwork = savedWeightsFile match {
    case Some(fileName) => loadD4JModel(fileName)
    case None => initializeNetwork()
  }
  dl4jNet.init()

  // XOR operator, only one of the following can be true!
  //require((weightInit.nonEmpty ^ distribution.nonEmpty) ^ savedWeightsFile.nonEmpty)

  val behaviorInputDim: Int = dl4jNet.layerInputSize(0)
  val behaviorOutputDim: Int = dl4jNet.layerSize(numLayers(dl4jNet) - 1)

  private def numLayers(net: MultiLayerNetwork): Int = net.getLayers.indices.count(i => net.layerSize(i) > 0)

  /**
    * Saves learned parameters to a file
    * Saved parameters can be reloaded into a TrainedDDPGNetwork
    * @param actorFile - the filepath to save to
    */
  def saveParams(actorFile: String): Unit = dl4jNet.save(new File(actorFile))

  override def apply(v1: Array[Double], v2: Array[Double]): ComponentControls = {
    val controlValues = query(v1 ++ v2)
    controlValues.indices.map{ i =>
      s"control$i" -> new BoundedScalarPrincessFeature(controlValues(i), 0, 0)
    }.toMap
  }

  def query(inputs: Array[Double]): Array[Double] = {
    val indArray = Nd4j.create(Array(inputs))
    dl4jNet.output(indArray).toDoubleVector
  }

  def params(): INDArray = dl4jNet.params()
  def setParams(params: INDArray): Unit = dl4jNet.setParams(params)

  protected def initializeNetwork(): MultiLayerNetwork = {
    var builder: NeuralNetConfiguration.ListBuilder = createBuilder(lr = learningRate)
    for( i <- 0 until numLayers) {
      val numNodes = if(i == 0) inputDim else nodesPerHiddenLayer
      builder = builder.layer(i, createHiddenLayer(hiddenActivation, numNodes, nodesPerHiddenLayer))
    }
    val conf: MultiLayerConfiguration =
      builder.layer(numLayers, createOutputLayer(outputActivation, nodesPerHiddenLayer, outputDim, loss)).build()
    new MultiLayerNetwork(conf)
  }

  protected def createBuilder(lr: Double): NeuralNetConfiguration.ListBuilder = new NeuralNetConfiguration.Builder()
    .seed(randomSeed) //High Level Configuration
    .optimizationAlgo(OptimizationAlgorithm.STOCHASTIC_GRADIENT_DESCENT)
    .updater(new Adam(lr))
    .list()

  protected def createHiddenLayer(func: Activation, inDim: Int, outDim: Int,
                                  hasBias: Boolean = false): DenseLayer = {
    val builder = new DenseLayer.Builder().nIn(inDim).nOut(outDim).hasBias(hasBias)
    val builderWithWeights =
      if(weightInit.nonEmpty) builder.weightInit(weightInit.get)
      else builder.weightInit(distribution.get)
    builderWithWeights.activation(func).build()
  }

  protected def createOutputLayer(func: Activation,inDim: Int, outDim: Int,
                                  loss: LossFunctions.LossFunction,
                                  hasBias: Boolean = false): OutputLayer = {
    val builder = new OutputLayer.Builder().nIn(inDim).nOut(outDim).hasBias(hasBias)
    val builderWithWeights =
      if(weightInit.nonEmpty) builder.weightInit(weightInit.get)
      else builder.weightInit(distribution.get)
    builderWithWeights.lossFunction(loss).activation(func).build()
  }

  def train(input: Array[Array[Double]], target: Array[Array[Double]]): Unit = {
    require(input.head.length == behaviorInputDim && target.head.length ==  behaviorOutputDim)
    dl4jNet.fit(Nd4j.create(input),Nd4j.create(target))
  }

  def train(input: Array[Double], target: Array[Double]): Array[Double] = {
    require(input.length == behaviorInputDim && target.length ==  behaviorOutputDim)
    dl4jNet.fit(Nd4j.create(input),Nd4j.create(target))
    Array.empty[Double]
  }


  def loadD4JModel(d4jParamsFilePath: String, seed: Int = 12345): MultiLayerNetwork = {
    Nd4j.getRandom.setSeed(seed)
    ModelSerializer.restoreMultiLayerNetwork(new File(d4jParamsFilePath))
  }

}
