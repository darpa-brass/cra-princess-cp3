package com.cra.princess.training

import java.io.File

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.optimizer.ComponentOptimizer
import org.deeplearning4j.nn.multilayer.MultiLayerNetwork
import org.deeplearning4j.util.ModelSerializer
import org.nd4j.linalg.factory.Nd4j

class TrainedNetwork(d4jParamsFilePath: String) extends ComponentOptimizer[Array[Double], Array[Double]]{

  val dl4jNet: MultiLayerNetwork =  ModelSerializer.restoreMultiLayerNetwork(new File(d4jParamsFilePath))

  def query(inputs: Array[Double]): Array[Double] = {
    val indArray = Nd4j.create(inputs)
    dl4jNet.output(indArray, false).toDoubleVector
  }

  override def apply(v1: Array[Double], v2: Array[Double]): ComponentControls = {
    val controlValues = query(v1 ++ v2)
    controlValues.indices.map{ i =>
      s"control$i" -> new BoundedScalarPrincessFeature(controlValues(i), 0, 0)
    }.toMap
  }
}
