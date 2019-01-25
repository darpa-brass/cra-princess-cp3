package com.cra.princess.kalmanfilter

import com.cra.princess.ComponentControls
import com.cra.princess.core.BoundedScalarPrincessFeature
import com.cra.princess.kalmanfilter.scenario.KalmanFilterScenarioGenerator
import com.cra.princess.localizationalgorithm.KinematicsModel
import com.cra.princess.optimizer.ComponentOptimizer
import com.cra.princess.util.Logs
import neuroflow.application.plugin.Notation._
import neuroflow.core.Activator._
import neuroflow.core._
import neuroflow.nets.cpu.DenseNetwork.double
import org.apache.commons.math3.linear._
import shapeless._


object Params{
  val learningRate = 0.00000000005
  val precision = 0.01
}

class KalmanFilterOptimizer(inputDim: Int = 8, outputDim: Int = 6, hiddenDim: Int = 20, numLayers: Int = 3,
                            numIterations: Int = 1000, batchSize: Int = 0, netFile: Option[String] = None)

  extends ComponentOptimizer[KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper] with Logs {

  val settings: Settings[Double] = Settings[Double](
    learningRate = { case (_, _) => Params.learningRate },
    iterations = numIterations,
    precision = Params.precision,
  )

  val net: FFN[Double] = {
    implicit val wp: WeightProvider[Double] = netFile match {
      case None => neuroflow.core.WeightProvider.Double.FFN.normal {List.range(0, numLayers).map{i => i -> (1.1, 0.1) }.toMap} // (0.0, 0.5)
      case Some(file) =>
        println(s"Loading model from file...$file")
        neuroflow.application.plugin.IO.File.readDouble(file)
    }
    Network(Input(inputDim) :: Dense(hiddenDim, ReLU) :: Dense(hiddenDim, Tanh) :: Output(outputDim, Linear) :: HNil, settings)
  }


  def train(data: Seq[(Seq[Double], Seq[Double])]): Unit = {
    val (inputsSeq, controlsSeq) = data.unzip
    val xs = inputsSeq.map(input => ->(input:_*))
    val ys = controlsSeq.map(controls => ->(controls:_*))
    net.train(xs, ys)
    neuroflow.application.plugin.IO.File.write(net.weights, "savedModel.json")
  }

  def train(trainingFile: String): Unit = {
    val trainingData = readFile(trainingFile).toList
    // TODO: use more history of error in training
    val (trainingSeq, _) = trainingData.unzip[(Array[Double], Array[Double]), Double]
    val (inputsSeq, controlsSeq) = trainingSeq.unzip[Array[Double], Array[Double]]
    val xs = inputsSeq.map(input => ->(input:_*))
    val ys = controlsSeq.map(controls => ->(controls:_*))
    val normalizedXs = normalizeInputs(xs)
//    val normalizedYs = normalizeOutputs(ys)
    net.train(normalizedXs, ys)
    neuroflow.application.plugin.IO.File.write(net.weights, "savedModel.json")

  }

  // TODO: eventually output ComponentControls and input KFInput (or something)
  override def optimize(testInputs: List[Double]): List[Double] = {
    val testX = ->(testInputs:_*)
    val normalizedTestX = normalizeInput(testX)
    net.evaluate(normalizedTestX).toArray.toList
  }

  // TODO: fix these normalization functions to use parametrized ranges for scaling
  private def normalizeInputs(xs: List[Network.Vector[Double]]): List[Network.Vector[Double]] = {
    // TODO: use values exported by data generator
    xs.map{ x => normalizeInput(x)}
  }

  private def normalizeInput(x: Network.Vector[Double]): Network.Vector[Double] = {
    val (resMin, resMax) = (-10.0, 10.0)
    ->(x.toArray.toList.map{ v =>(v - resMin)/(resMax - resMin) - 0.5}:_*)
  }


  // TODO: update based on new KF component and optimization approach
  override def apply(env: KalmanFilterEnvironmentWrapper, input: KalmanFilterInputWrapper): ComponentControls = {
    val state = input.state.getCombinedState
    val prevVelocity = input.state.getDeltaComponents
    val p00 = input.covariance.getEntry(0,0)
    val p11 = input.covariance.getEntry(1,1)
    val (x1, x2) = (state.getEntry(2), state.getEntry(3))
    val (z1, z2) = (input.observations.head.getEntry(0), input.observations.head.getEntry(1))
    val baselineControls = Map("bDiag0" -> new BoundedScalarPrincessFeature(1, 1, 1),
      "bDiag1" -> new BoundedScalarPrincessFeature(1, 1, 1),
      "qDiag0" -> new BoundedScalarPrincessFeature(0.3, 1e-5, 1),
      "qDiag1" -> new BoundedScalarPrincessFeature(0.3, 1e-5, 1),
      "rDiag0" -> new BoundedScalarPrincessFeature(0.1, 1e-5, 1),
      "rDiag1" -> new BoundedScalarPrincessFeature(0.2, 1e-5, 1))

    val u = MatrixUtils.createRealVector(KinematicsModel.getAcceleration(input.actuatorValues.toArray, prevVelocity.toArray))

    val controls = optimize(List(p00,p11,x1,x2,z1,z2,u.getEntry(0),u.getEntry(1)))
    log.debug(s"KalmanFilterOptimizer inputs: ${List(p00,p11,x1,x2,z1,z2,u.getEntry(0),u.getEntry(1)).toString}")
    log.debug(s"KalmanFilterOptimizer controls: ${controls.toString()}")
    val (_, res) = KalmanFilterScenarioGenerator.generateDataPoint(Array(p00,p11,x1,x2,z1,z2,u.getEntry(0),u.getEntry(1)), controls.toArray)
    if(controls.sum == 0.0) {
      return baselineControls
    }
    res match {
      case Some(_) =>
        Map("bDiag0" -> new BoundedScalarPrincessFeature(controls.head, 0, 0),
            "bDiag1" -> new BoundedScalarPrincessFeature(controls(1), 0, 0),
            "qDiag0" -> new BoundedScalarPrincessFeature(controls(2), 0, 0),
            "qDiag1" -> new BoundedScalarPrincessFeature(controls(3), 0, 0),
            "rDiag0" -> new BoundedScalarPrincessFeature(controls(4), 0, 0),
            "rDiag1" -> new BoundedScalarPrincessFeature(controls(5), 0, 0))
      case _ => baselineControls
    }
  }

  private def readFile(filename: String): Iterator[((Array[Double], Array[Double]), Double)] = {
    val bufferedSource = scala.io.Source.fromFile(filename)
    val lines = bufferedSource.getLines.toList.tail
    for (line <- lines.toIterator) yield {
      val cols = line.split(",").map(_.trim).init // init because metric is last column
      val inputsSeq = cols.take(inputDim).map(x => x.toDouble)
      val controlsSeq = cols.slice(inputDim, inputDim + outputDim).map(x => x.toDouble) // take columns on right for ctrls
      val metric = line.split(",").map(_.trim).last.toDouble
      ((inputsSeq, controlsSeq), metric)
    }
  }
}