package com.cra.princess.training

import java.io.File

import com.cra.princess.training.training.{TrainingControls, _}
import com.cra.princess.util.Logs
import org.deeplearning4j.nn.modelimport.keras.KerasModelImport
import org.deeplearning4j.nn.multilayer.MultiLayerNetwork
import org.deeplearning4j.util.ModelSerializer
import org.nd4j.linalg.api.ndarray.INDArray
import org.nd4j.linalg.factory.Nd4j

/**
  * Optimizer that uses the D4J library for constructing and training neural nets
  * @param criticParamsFile - pass None if the model has yet to be trained, otherwise, pass a file with Trained Data
  */
class D4JOptimizer(actorParamsFile: String, criticParamsFile: String) extends ActorCriticNetwork with Logs {

  private var actorNetwork: MultiLayerNetwork = loadD4JModel(actorParamsFile)
  private var criticNetwork: MultiLayerNetwork = loadD4JModel(criticParamsFile)
  val actorInputDim: Int = actorNetwork.layerSize(0)
  val actorOutputDim: Int = actorNetwork.layerSize(numLayers(actorNetwork) - 1)
  val criticInputDim: Int = criticNetwork.layerSize(0)
  val criticOutputDim: Int = criticNetwork.layerSize(numLayers(criticNetwork) - 1)
  private def numLayers(net: MultiLayerNetwork): Int = net.getLayers.indices.count(i => net.layerSize(i) > 0)

  override def actorForwardPass(s: Array[TrainingState], c: Array[TrainingControls]): Unit = {
    val model: MultiLayerNetwork = loadD4JModel(actorParamsFile)
    model.fit(Nd4j.create(s),Nd4j.create(c))
    actorNetwork = model
  }

  override def criticForwardPass(s: Array[TrainingState], m: Array[TrainingMetric]): Unit = {
    val model: MultiLayerNetwork = loadD4JModel(criticParamsFile)
    model.fit(Nd4j.create(s),Nd4j.create(m))
    criticNetwork = model
  }

  def saveNetworks(): Unit ={
    actorNetwork.save(new File(actorParamsFile))
    criticNetwork.save(new File(criticParamsFile))
  }

  /**
    * @param inputs - current state
    * @return control values
    */
  override def optimize(inputs: List[Double]): TrainingControls = {
    val (resMin, resMax) = (-10.0, 10.0)
    val normalizedTestX = normalizeInput(inputs.toArray, resMin, resMax)
    val indArray = Nd4j.create(Array(normalizedTestX))
    actorNetwork.output(indArray).toDoubleVector
  }

  /**
    * @param inputs - current state and current controls
    * @return metric value
    */
  override def getReward(inputs: List[Double]): TrainingMetric = {
    val (resMin, resMax) = (-10.0, 10.0)
    val normalizedTestX = normalizeInput(inputs.toArray, resMin, resMax)
    val indArray = Nd4j.create(Array(normalizedTestX))
    criticNetwork.output(indArray).toDoubleVector.head
  }

  private def loadD4JModel(d4jParamsFilePath: String, seed: Int = 12345): MultiLayerNetwork = {
    Nd4j.getRandom.setSeed(seed)
    ModelSerializer.restoreMultiLayerNetwork(new File(d4jParamsFilePath))
  }


}

object D4JOptimizer{

  def apply(actorParamsFile: String, criticParamsFile: String): D4JOptimizer =
    new D4JOptimizer(actorParamsFile, criticParamsFile)

  def train(paramsFile: String, trainingFile: String, inputDim: Int, outputDim: Int,
            normalizationRange: (Double, Double) = (-10.0, 10.0)): Unit = {
    Nd4j.getRandom.setSeed(12345)
    val model: MultiLayerNetwork = ModelSerializer.restoreMultiLayerNetwork(new File(paramsFile))
    val (xs, ys) = readTrainingData(trainingFile, inputDim, outputDim)
    val xsNormalized = Nd4j.create(normalizeInputs(xs.toDoubleMatrix))
    model.fit(xsNormalized, ys)
    model.save(new File(paramsFile))
  }

  def trainFromKeras(kerasParamsFilePath: String, d4jParamsFilePath: String, trainingFile: String,
                     inputDim: Int, outputDim: Int, normalizationRange: (Double, Double) = (-10.0, 10.0)): Unit = {
    convertKerasModel(kerasParamsFilePath, d4jParamsFilePath)
    train(d4jParamsFilePath, trainingFile, inputDim, outputDim)
  }

  def convertKerasModel(kerasParamsFilePath: String, d4jParamsFilePath: String): Unit = {
    val model: MultiLayerNetwork = KerasModelImport.importKerasSequentialModelAndWeights(kerasParamsFilePath)
    model.save(new File(d4jParamsFilePath))
  }

  private def readTrainingData(filename: String, inputDim: Int, outputDim: Int): (INDArray, INDArray) = {
    val (xs, ys) = {
      val bufferedSource = scala.io.Source.fromFile(filename)
      val lines = bufferedSource.getLines.toList.tail
      for (line <- lines.toIterator) yield {
        val cols = line.split(",").map(_.trim) // init because metric is last column
        val inputsSeq = cols.take(inputDim).map(x => x.toDouble)
        val controlsSeq = cols.slice(inputDim, inputDim + outputDim).map(x => x.toDouble) // take columns on right for ctrls
        (inputsSeq, controlsSeq)
      }
    }.toList.unzip
    (Nd4j.create(xs.toArray), Nd4j.create(ys.toArray))
  }
}