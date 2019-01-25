package com.cra.princess.pathplanner.component

import java.io.{File, FileWriter, PrintWriter}

import com.cra.princess.core.{NormalPriorPrincessFeature, PrincessFeature}
import com.cra.princess.optimizer.ComponentOptimizer
import com.cra.princess.pathplanner.{PathCoverageSimulator, SingleFunctionPathPlanner}
import com.cra.princess.{ComponentControls, Metric, Threshold}
import neuroflow.application.plugin.Notation._
import neuroflow.core.Activator._
import neuroflow.core._
import neuroflow.nets.cpu.DenseNetwork.double
import shapeless.HNil

import scala.io
import scala.util.control.Exception.allCatch

/**
  * Path planner optimizer utilizing neural network
  * @param inputDim - number of inputs
  * @param outputDim - number of outputs
  * @param hiddenDim - number of nodes in hidden layer
  */
class PathPlannerNNOptimizer(netFile: String = "PPNet", inputDim: Int = 15,
                             outputDim: Int = 8, hiddenDim: Int = 20, budget: Double = 5000.0)
  extends ComponentOptimizer[PathPlannerEnvironment,PPInput] {

  private val EXCEPTION_NUM = -2.0

  // Original controls
  // TODO: should these be acquired from some other object?
  val origControls = Seq(0.0, 0.0, 0.0, 2.0, 1.0, 1.0, 2.0, 0.0)

  // NN settings
  val settings = Settings[Double](
    learningRate = { case (iter, rate) => 0.0000005},//0.0000007},//0.000001 /*0.000001*/},
    iterations = 1000,
    precision = 0.01
  )

  //TODO: check this way of constructing network
  // Construct NN architecture
  val net: FFN[Double] = {
    // Initialize NN weights using normal distribution
    implicit val wp = neuroflow.core.WeightProvider.Double.FFN.normal {
      Map ( // normal config per weight layer
        0 -> (0.0, 1.0), /* was 10.0 */
        1 -> (0.0, 1.0)
      )
    }
    Network(Input(inputDim) :: Dense(hiddenDim, ReLU) :: Output(outputDim, Linear) :: HNil, settings)
  }

//  val trainedNet = {
//    implicit val wp = neuroflow.application.plugin.IO.File.readDouble(netFile)
//    Network(Input(inputDim) :: Dense(hiddenDim, ReLU) :: Output(outputDim, Linear) :: HNil, settings)
//  }

  override def apply(env: PathPlannerEnvironment, input: PPInput): ComponentControls = {
    val budgetThreshold: Threshold = {
      if(this.intent != null) {
        this.intent.thresholds.head
      } else {
        budget
      }
    }
    val xs = ->(input.startLocationX, input.startLocationY, input.returnLocationX, input.returnLocationY,
                input.searchArea(0)(0), input.searchArea(0)(1), input.searchArea(1)(0), input.searchArea(1)(1),
                input.searchArea(2)(0), input.searchArea(2)(1), input.searchArea(3)(0), input.searchArea(3)(1),
                input.altitude, input.fovRadians, budgetThreshold)
    val nonNormalXs = xs.toArray.clone()
    normalizeInputs(List(xs))
    val inferredControls = net.evaluate(xs).toArray
    val (_, _, coverage) = generateDataPoint(nonNormalXs, inferredControls)
    if(coverage == -1) {
      // use original controls if exception generated
      ctrlSeqToComponentControls(origControls)
    } else {
      // return inferred controls
      ctrlSeqToComponentControls(inferredControls.toSeq)
    }
  }

  private def ctrlSeqToComponentControls(ctrlSeq: Seq[Double]): ComponentControls = {
    var i: Int = 0
    ctrlSeq.map { d => i=i+1
      ("ctrl"+(i-1), new NormalPriorPrincessFeature(d, 0.0, 0.0))
    }.toMap
  }

  def normalizeInputs(xs: List[Network.Vector[Double]]): Unit = {
    // calc max/min
    val maxArray: Array[Double] = Array(556.0, 556.0, 0.0, 0.0, 0.0, 556.0, 0.0, 556.0, 556.0, 556.0, 556.0, 556.0, 90.0, 0.349066, 8000.0)
    val minArray: Array[Double] = Array(  0.0,   0.0, 0.0, 0.0, 0.0, 0.0,   0.0, 111.0, 111.0, 111.0, 111.0, 0.0,   90.0, 0.349066, 0.0)

    for(x <- xs) {
      for(i <- 0 until inputDim) {
        if(minArray(i) == maxArray(i)) {
          x(i) = 0.0
        } else {
          x(i) = (x(i) - minArray(i)) / (maxArray(i) - minArray(i)) - 0.5
        }
      }
    }
  }

  def train(trainingFile: String): Unit = {
    // This should return ((inputs, controls), (distance, coverage))
    val trainingData = readFile(trainingFile).toList
    val (trainingSeq, _) = trainingData.unzip[(Array[Double], Array[Double]), (Double, Double)]
    val (inputsSeq, controlsSeq) = trainingSeq.unzip[Array[Double], Array[Double]]
    val xs = inputsSeq.map(input => ->(input:_*))
    normalizeInputs(xs)
    val ys = controlsSeq.map(controls => ->(controls:_*))
    net.train(xs, ys)
//    neuroflow.application.plugin.IO.File.write(net.weights, "trainingFile.json")
  }

  private def readFile(filename: String): Iterator[((Array[Double], Array[Double]), (Double, Double))] = {
    val bufferedSource = scala.io.Source.fromFile(filename)
    val lines = bufferedSource.getLines.toList // skip first line because of header
    for (line <- lines.toIterator) yield {
      val cols = line.split(",").map(_.trim).take(inputDim+outputDim)
      val inputsSeq = cols.take(inputDim).map(x => x.toDouble)
      val controlsSeq = cols.takeRight(outputDim).map(x => x.toDouble)
      val (distance, coverage) = (line.split(",")(23).trim.toDouble, line.split(",")(24).trim.toDouble)
      ((inputsSeq, controlsSeq), (distance, coverage))
    }
  }

  // returns (output, distance, coverage)
  private def generateDataPoint(inputs: Array[Double], controls: Array[Double]): (Array[Array[Double]], Double, Double) = {
    // inputs
    val (startLocationX, startLocationY) = (inputs(0), inputs(1))
    val (returnLocationX, returnLocationY) = (inputs(2), inputs(3))
    val searchArea = Array(Array(inputs(4), inputs(5)), Array(inputs(6), inputs(7)), Array(inputs(8), inputs(9)), Array(inputs(10), inputs(11)))
    val altitude = inputs(12)
    val fovRadians = inputs(13)
    val distanceBudget = inputs(14)

    // controls
    val (ctrl0, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6, ctrl7) = (controls(0), controls(1), controls(2), controls(3),
                                                                    controls(4), controls(5), controls(6), controls(7))
    // Execute path planner to get output
    val pp = new SingleFunctionPathPlanner()
    val output: Array[Array[Double]] = allCatch.opt(pp.TransformedPlan(ctrl0, ctrl1, ctrl2, ctrl3, ctrl4,
      ctrl5, ctrl6, ctrl7, startLocationX,
      startLocationY, returnLocationX, returnLocationY,
      searchArea,
      searchArea.length, altitude, fovRadians)).orNull

    if(output != null) {
      // Calculate metrics
      val distance = SingleFunctionPathPlanner.distance(output)
      val pc = new PathCoverageSimulator(output, searchArea(0),
        searchArea(2), altitude, fovRadians)
      val coverage = pc.coverage()
      if(distance > distanceBudget)
        return (output, distance, -1.0)
      (output, distance, coverage)
    } else  // "unsuccessful values" - generated exception
      (Array(Array(-1.0, -1.0), Array(-1.0, -1.0)), -1.0, EXCEPTION_NUM)
  }

  def testOnData(testDataFile: String, outputFile: String): Unit = {
    // Read test data for inputs
    val testData = readFile(testDataFile).toList

    // Write headers for test output
    val writer = new FileWriter(new File(outputFile), false)
    val pWriter = new PrintWriter(writer, false)
//    writer.write("startLocationX,startLocationY,returnLocationX,returnLocationY,searchAreaX0,searchAreaY0,searchAreaX1," +
//      "searchAreaY1,searchAreaX2,searchAreaY2,searchAreaX3,searchAreaY3,altitude,fovRadians,distanceBudget," +
//      "ctrlLoop0,ctrlLoop1,ctrlCmp0,ctrlConst0,ctrlConst1,ctrlConst2,ctrlConst3,ctrlConst4,inferredCoverage,baselineCoverage")
    writer.close()
    for (((inputs, _), (_, _)) <- testData) {
      // evaluate on inputs and compare to controls
      val testX = ->(inputs.clone():_*)
      normalizeInputs(List(testX))

      val inferredControls = net.evaluate(testX)
//      println(s"inputs = ${testX.toString()}")
//      println(s"inferred controls = ${inferredControls.toString()}")
      // Run PP to get metric with constant (initial) controls - this is the baseline
      val baselineControls = Array(0.0, 0.0, 0.0, 2.0, 1.0, 1.0, 2.0, 0.0)
      val (baselinePath, baselineDistance, baselineCoverage) = generateDataPoint(inputs, baselineControls)

      // Get metric using inferred controls
      val (inferredPath, inferredDistance, inferredCoverage) = generateDataPoint(inputs, inferredControls.toArray)

      // Write test output
      writeTestOutput(outputFile, inputs, inferredControls.toArray, inferredCoverage, baselineCoverage, inferredDistance, baselineDistance, baselinePath,inferredPath)
    }
  }

  private def writeTestOutput(outputFile: String, inputs: Array[Double], inferredControls: Array[Double],
                              inferredMetric: Double, baselineMetric: Double,
                              inferredDistance: Double, baselineDistance: Double,
                              baselinePath: Array[Array[Double]],
                              inferredPath: Array[Array[Double]]) = {
    val writer = new FileWriter(new File(outputFile), true)
    val pWriter = new PrintWriter(writer, true)

    //println("Writing output...")
    for(i <- inputs)
      writer.write(s"$i,")
    for(ic <- inferredControls)
      writer.write(s"$ic,")
    writer.write(s"$inferredMetric,$baselineMetric,$inferredDistance,$baselineDistance,")
    for(basePoint <- baselinePath.toList)
      writer.write(s"(${basePoint(0)} : ${basePoint(1)}),")
    writer.write(",")
    for(inferPoint <- inferredPath.toList)
      writer.write(s"(${inferPoint(0)} : ${inferPoint(1)}),")
    pWriter.println()
    writer.close()
  }
}

/**
  * @param fileName - file path of training data consisting of controls, inputs, and a single metric for the path planner
  */
class PathPlannerOptimizer(fileName: String, budget: Double = 5000.0) extends ComponentOptimizer[PathPlannerEnvironment,PPInput] {
  private val searchAreaBin = Some(Seq.tabulate(4)(_ => Seq.tabulate(2)(_ => 0.001)))
  private val binSizes = Some(Seq(Double.MaxValue, Double.MaxValue, Double.MaxValue, Double.MaxValue, Double.MaxValue, Double.MaxValue))

  override def apply(env: PathPlannerEnvironment, input: PPInput): ComponentControls = {
    val budgetThreshold: Threshold = {
      if(this.intent != null) {
        this.intent.thresholds.head
      } else {
        budget
      }
    }
    val bufferedSource = io.Source.fromFile(fileName)
    var data: Seq[(PPControls, PPInput, Metric)] = Seq()
    for (line <- bufferedSource.getLines.drop(1)) {
      val cols = line.split(",").map(_.trim.toDouble)
      val controls = PPControls(cols(0), cols(1), cols(2), cols(3), cols(4), cols(5), cols(6), cols(7))
      val searchArea =
        Seq(
          Seq(cols(12), cols(13)),
          Seq(cols(14), cols(15)),
          Seq(cols(16), cols(17)),
          Seq(cols(18), cols(19)))
      val ppInput = PPInput(cols(8), cols(9), cols(10), cols(11), searchArea, cols(20), cols(21), binSizes, searchAreaBin)
      val distance = cols(22) // needs to be under the budget
      if(ppInput.equals(input) && distance < budgetThreshold) {
        val prDet: Metric = cols(23) // the metric
        data = data :+ (controls, ppInput, prDet)
      }
    }
    bufferedSource.close
    if(data.isEmpty) ctrlSeqToComponentControls(Seq.empty[Double])
    else {
      val sortedData = data.sortWith(_._3 > _._3)
      val ctrlTuple = PPControls.unapply(sortedData.head._1).get
      val ctrlSeq: Seq[Double] = Seq(ctrlTuple._1, ctrlTuple._2, ctrlTuple._3, ctrlTuple._4, ctrlTuple._5, ctrlTuple._6,
        ctrlTuple._7, ctrlTuple._8)
      ctrlSeqToComponentControls(ctrlSeq)
    }
  }

  private def ctrlSeqToComponentControls(ctrlSeq: Seq[Double]): ComponentControls = {
    var i: Int = 0
    ctrlSeq.map { d => i=i+1
                  ("ctrl"+(i-1), new NormalPriorPrincessFeature(d, 0.0, 0.0))
    }.toMap
  }
}

object PathPlannerOptimizer{
  def apply(fileName: String, budget: Int = 5000): PathPlannerOptimizer = new PathPlannerOptimizer(fileName, budget)
}

object testOPt {
  def main(args: Array[String]): Unit = {
    val t0 = System.currentTimeMillis()
    val optimizeFunc = PathPlannerOptimizer("binned_path_planner_data.csv")
    val searchArea: Seq[Seq[Double]] = Seq(Seq(0,0), Seq(0,111), Seq(111,111), Seq(111,0))
    val binSizesOpt = Some(Seq(0.1, 0.1, 0.1, 0.1, 10.1, 0.1))
    val searchAreaBinOpt = Some(Seq(Seq(0.1, 0.1), Seq(0.1, 0.1), Seq(0.1, 0.1), Seq(0.1, 0.1)))
    val input = PPInput(0, 0, 0, 0, searchArea, 50, Math.PI/4, binSizesOpt, searchAreaBinOpt)
    println(optimizeFunc(null, input))
    val t1 = System.currentTimeMillis()
    println((t1 - t0)/1000.0)
  }
}

case class PPInput(startLocationX: Double,
                   startLocationY: Double,
                   returnLocationX: Double,
                   returnLocationY: Double,
                   searchArea: Seq[Seq[Double]],
                   altitude: Double,
                   fovRadians: Double,
                   binsSizesOpt : Option[Seq[Double]],
                   searchAreaBinOpt: Option[Seq[Seq[Double]]]) extends PrincessFeature{
  // check if two inputs are the same based on binning
  // the larger the bin size the more relaxed the similarity requirements
  override def equals(obj: scala.Any): Boolean = obj match {
    case input: PPInput => (binsSizesOpt, searchAreaBinOpt) match {
      case (Some(binSizes), Some(searchAreaBin)) =>
        sameArea(input.searchArea, searchArea, searchAreaBin) &&
        Math.abs(input.startLocationX - startLocationX) <= binSizes.head &&
        Math.abs(input.startLocationY - startLocationY) <= binSizes(1) &&
        Math.abs(input.returnLocationX - returnLocationX) <= binSizes(2) &&
        Math.abs(input.returnLocationY - returnLocationY) <= binSizes(3) &&
        Math.abs(input.altitude - altitude) <= binSizes(4) &&
        Math.abs(input.fovRadians - fovRadians) <= binSizes(5)
      case _ => false
    }
    case _ => false
  }
  private def sameArea(area1: Seq[Seq[Double]], area2: Seq[Seq[Double]], bins: Seq[Seq[Double]]): Boolean = {
    if(area1.length == area2.length){
      for(i <- area1.indices){
        if(area1(i).length != area2(i).length)
          return false
        for(j <- area1(i).indices){
          if(Math.abs(area1(i)(j) - area2(i)(j)) > bins(i)(j))
            return false
        }
      }
      true
    }else
      false
  }

  /**
    * Returns the lower left coordinate of this PPInput's search area
    * @return The lower left coordinate as (x, y)
   */
  def searchAreaLowerLeft: (Double, Double) = {
    val ll = searchArea.head
    (ll.head, ll.tail.head)
  }

  /**
    * Returns the upper right coordinate of this PPInput's search area
    * @return The upper right coordinate as (x, y)
    */
  def searchAreaUpperRight: (Double, Double) = {
    val ur = searchArea(2)
    (ur.head, ur.tail.head)
  }
}

case class PPControls(ctrlLoop0: Double, ctrlLoop1: Double, ctrlCmp0: Double,
                      ctrlConst0: Double, ctrlConst1: Double, ctrlConst2: Double,
                      ctrlConst3: Double, ctrlConst4: Double)