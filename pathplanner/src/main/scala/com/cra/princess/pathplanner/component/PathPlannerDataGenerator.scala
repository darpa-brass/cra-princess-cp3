package com.cra.princess.pathplanner.component

import java.io.{File, FileWriter, PrintWriter}

import com.cra.figaro.algorithm.sampling._
import com.cra.figaro.language._
import com.cra.figaro.library.atomic.continuous.Uniform
import com.cra.princess.pathplanner.{PathCoverageSimulator, SingleFunctionPathPlanner}
import neuroflow.core.Network

import scala.util.control.Exception._

class PathPlannerInput (val startLocation: (Double, Double), val returnLocation: (Double, Double),
    val searchArea: List[(Double, Double)], val altitude: Double, val fovRadians: Double)    
    
/**
 * Produces a data set to use for training the Path Planner Component Model
 * Writes data to a csv file
 * 
 * @param ctrlBounds A map with each entry specifying the a control variable index as the key, and a Tuple with minimum,
 *                   maximum, and increment values for that control
 * @param altitudeBounds A Tuple3 containing minimum, maximum, and increment values for the altitude
 * @param searchAreaBounds A Tuple3 containing minimum, maximum, and increment values for the search
 *                         coordinates, respectively
 * @param fovRadiansBounds A Tuple3 containing minimum, maximum, and increment values for the
 *                         fovRadians (sensor field of view)
 * @param prDetectionFunction Function that calculates probability of detection factor given altitude, minimum altitude,
 *                            and maximum altitude
 */
class PathPlannerDataGenerator (val ctrlBounds: Map[Int, (Double, Double, Double)],
                                val altitudeBounds: (Double, Double, Double),
                                val searchAreaBounds: (Double, Double, Double),
                                val fovRadiansBounds: (Double, Double, Double),
                                val prDetectionFunction: (Double, Double, Double) => Double,
                                val distanceBudget: Double) {
  
  val EndMarker: Double = SingleFunctionPathPlanner.END_MARKER // Specifies end of list points in plan
  var ptsGenerated: Int = 0
  var ptsWritten: Int = 0
  var ptsTotal: Int = 0
  /*
   * Generate a single set of control values
   */
  private def generateControls(): List[Double] = {
    (for{i <- 1 to ctrlBounds.size} yield generateUniform(i)).toList
  }
  
  /*
   * Generate a single input instance - TODO: update for CP3 perturbation scenario
   */
  private def generateInput(): PathPlannerInput = {
    val startLocation: (Double, Double) = (0.0, 0.0)
    val returnLocation: (Double, Double) = (0.0, 0.0)
    
    val (searchAreaMin, searchAreaMax) = (searchAreaBounds._1, searchAreaBounds._2)
    val (altitudeMin, altitudeMax) = (altitudeBounds._1, altitudeBounds._2)                                              
    val (fovRadiansMin, fovRadiansMax) = (fovRadiansBounds._1, fovRadiansBounds._2)
    
    // Assumes we restrict search area to 4 points, rectangular
    val searchAreaValX = generateUniform(searchAreaMin, searchAreaMax)
    val searchAreaValY = generateUniform(searchAreaMin, searchAreaMax)
    val searchArea: List[(Double, Double)] = List((0.0, 0.0), (0.0, searchAreaValY), (searchAreaValX, searchAreaValY),
                                                  (searchAreaValX, 0.0))
         
    val altitude: Double = generateUniform(altitudeMin, altitudeMax)
    val fovRadians: Double = generateUniform(fovRadiansMin, fovRadiansMax)
    new PathPlannerInput(startLocation, returnLocation, searchArea, altitude, fovRadians)
  }

  /*
   * Utility functions for random number generation
   */
  private def generateUniform(min: Double, max: Double): Double = {
    //val uelt: Element[Double] = Uniform(min, max)
    //val sampler = ElementSampler(uelt)
    //sampler.sample()._2(uelt).asInstanceOf[Double]
    Math.random() * (max - min) + min
  }
  
  private def generateUniform(ctrlIndex: Int): Double = {
    val (ctrlMin, ctrlMax) = (ctrlBounds(ctrlIndex)._1, ctrlBounds(ctrlIndex)._2)
    generateUniform(ctrlMin, ctrlMax)
  }
  
  /*
   * Generate output by calling path planner function
   */
  private def calculateOutput(controls: List[Double], input: PathPlannerInput): Array[Array[Double]] = {
    val pp = new SingleFunctionPathPlanner()
    
    
    // TODO: load transformed code from file and compile into an object
    val (startLocationX, startLocationY) = (input.startLocation._1, input.startLocation._2)
    val (returnLocationX, returnLocationY) = (input.returnLocation._1, input.returnLocation._2)

    // TODO: make controls a list to generalize for different sets of control values (e.g., for different transformations)
    val output: Option[Array[Array[Double]]] = allCatch.opt(pp.TransformedPlan(controls(0), controls(1), controls(2), controls(3), controls(4),
                                    controls(5), controls(6), controls(7), startLocationX, 
                                    startLocationY, returnLocationX, returnLocationY, 
                                    input.searchArea.map{case (x, y) => Array(x, y)}.toArray, 
                                    input.searchArea.length, input.altitude, input.fovRadians))
    output.orNull
  }
  
  /*
   * Calculate distance, coverage, and probability of detection
   */
  private def calculateMetrics(input: PathPlannerInput, output: Array[Array[Double]], budget: Double = distanceBudget): (Double, Double, Double) = {
    val truncatedOutput = output//SingleFunctionPathPlanner.truncatePath(output, budget)
    val distance = SingleFunctionPathPlanner.distance(truncatedOutput)
    val pc = new PathCoverageSimulator(truncatedOutput, Array(input.searchArea(0)._1, input.searchArea(0)._2),
                                       Array(input.searchArea(2)._1, input.searchArea(2)._2), input.altitude, input.fovRadians)
    var coverage = pc.coverage()
    if (distance > budget) {
      coverage = 0.0
    }
    val prDet = prDetectionFunction(input.altitude, altitudeBounds._1, altitudeBounds._2) * coverage
    (distance, coverage, prDet)
  }

  /*
   * Open output file and prepare for writing
   */
  private def openOutputFile(filename: String, append: Boolean): FileWriter = {
    val writer = new FileWriter(new File(filename), append)
    if(!append) {
      writeHeaders(writer)
    }
    writer
  }

  private def elementData(min: Double, max: Double, inc: Double) = {
    if((inc > 0.0) && (max > min)) {
      List.tabulate(((max - min) / inc).toInt + 1)(min + _ * inc)
    } else {
      List(min)
    }
  }

  /*
   * Write training data column headers
   */
  private def writeTrainingHeaders(writer: FileWriter): Unit = {
    writer.write("startLocationX,startLocationY,returnLocationX,returnLocationY,searchAreaX0,searchAreaY0,searchAreaX1,searchAreaY1,searchAreaX2,searchAreaY2,searchAreaX3,searchAreaY3,altitude,fovRadians,distanceBudget,ctrlLoop0,ctrlLoop1,ctrlCmp0,ctrlConst0,ctrlConst1,ctrlConst2,ctrlConst3,ctrlConst4,distance,coverage,prDet,outputBegin")
    val pWriter = new PrintWriter(writer, true)
    pWriter.println()
  }

  /*
   * Write controls, inputs, outputs, distance for each generated instance to csv file
   */
  private def writeTrainingData(writer: FileWriter, controls: List[Double], input: PathPlannerInput, distanceBudget: Double,
                                output: List[(Double, Double)], distance: Double, coverage: Double, prDet: Double): Unit = {
    // inputs
    writer.write(s"${input.startLocation._1},${input.startLocation._2},")
    writer.write(s"${input.returnLocation._1},${input.returnLocation._2},")
    for(s <- input.searchArea) { // always 4 points
      writer.write(s"${s._1},${s._2},")
    }
    writer.write(s"${input.altitude.toString},")
    writer.write(s"${input.fovRadians.toString},")
    writer.write(s"${distanceBudget.toString},")
    // controls
    for (c <- controls) {
      writer.write(s"${c.toString},")
    }

    //distance, coverage, prDet
    writer.write(s"${distance.toString},${coverage.toString},${prDet.toString}")

    // outputs (variable length list of coordinates)
    //var i = 0
    //while((i < output.length) && (output(i)._1 != EndMarker))
    //{
    //  val o = output(i)
    //  writer.write(",")
    //  writer.write(o._1.toString)
    //  writer.write(",")
    //  writer.write(o._2.toString)
    //  i = i + 1
    //}

    val pwriter = new PrintWriter(writer, true)
    pwriter.println()
  }

  /*
   * Generate a single input instance for training data - TODO: update for CP3 perturbation scenario
   */
  private def generateTrainingInput(): PathPlannerInput = {

    val (searchAreaMin, searchAreaMax) = (searchAreaBounds._1, searchAreaBounds._2)
    val (altitudeMin, altitudeMax) = (altitudeBounds._1, altitudeBounds._2)
    val (fovRadiansMin, fovRadiansMax) = (fovRadiansBounds._1, fovRadiansBounds._2)

    // To faithfully represent a CP3 scenario, we need to generate an initial search area, and a subset of that search
    // area (i.e., the new search area after the perturbation). This is because we need a reference point for the
    // return point, which will differ from the start point in the after-perturbation search area.

    // Assumes we restrict search area to 4 points, rectangular
    val searchAreaValX = generateUniform(searchAreaMin, searchAreaMax)
    val searchAreaValY = generateUniform(searchAreaMin, searchAreaMax)
    val newSearchAreaMinY = generateUniform(0.0, searchAreaValY)
    val searchArea: List[(Double, Double)] = List((0.0, newSearchAreaMinY), (0.0, searchAreaValY), (searchAreaValX, searchAreaValY),
      (searchAreaValX, newSearchAreaMinY))

    val altitude: Double = generateUniform(altitudeMin, altitudeMax)
    val fovRadians: Double = generateUniform(fovRadiansMin, fovRadiansMax)

    // Generate random X position where perturbation occurred
    val startLocationX: Double = generateUniform(0.0, searchAreaValX)
    // Start location Y position where perturbation occurred
    val startLocationY: Double = newSearchAreaMinY

    new PathPlannerInput((startLocationX, startLocationY), (0.0, 0.0), searchArea, altitude, fovRadians)
  }

  /**
    * Generate control, input, output, distance instance (Neural Net training set version)
    *
    * @param filename Output file
    * @param append true to append to an existing file, false to overwrite existing file
    */
  def generateTrainingData(filename: String, append: Boolean, numInputs: Int = 10000, numControls: Int = 100,
                           testData: Boolean = false, budgetRange: (Double, Double) = (100.0, 3000.0)): Unit = {
    val writer = new FileWriter(new File(filename), append)
    if(!append) {
      writeTrainingHeaders(writer)
    }

    //for (inputIdx <- 1 to numInputs) {
    var inputIdx = 0
    while(inputIdx < numInputs) {
      val input = generateTrainingInput()
      val distanceBudgetLocal = generateUniform(budgetRange._1, budgetRange._2)
      var optimalCoverage = 0.0
      var optimalCoverageDist = 0.0
      var optimalPrDet = 0.0
      var optimalDistance = Double.MaxValue
      var optimalDistanceDist = Double.MaxValue
      var optimalControls: List[Double] = List.empty
      var optimalControlsDist: List[Double] = List.empty
      var optimalOutput: Array[Array[Double]] = Array()
      var optimalOutputDist: Array[Array[Double]] = Array()
      val ctrlIterations = if(testData) 1 else numControls // don't iterate through more than 1 control for test data
      for(_ <- 1 to ctrlIterations) {
        val controls: List[Double] = generateControls()
        val output = calculateOutput(controls, input)
        if(output != null) {
          val (distance, coverage, prDet) = calculateMetrics(input, output, budget=distanceBudgetLocal)
          //println(s"trying coverage: $coverage")

          // first try to maximize coverage while staying under distance budget
          if((optimalControls.isEmpty || coverage > optimalCoverage) && (distance < distanceBudgetLocal)) {
            optimalCoverage = coverage
            optimalControls = controls
            optimalOutput = output
            optimalPrDet = prDet
            optimalDistance = distance
          }
          // find minimal distance in case we can't get under budget
          if(distance < optimalDistance) {
            optimalCoverageDist = coverage
            optimalControlsDist = controls
            optimalOutputDist = output
            optimalDistanceDist = distance
          }

        }
      }

      def origControl(i: Int) = {(ctrlBounds(i)._1 + ctrlBounds(i)._2)/2.0}

      // In case we never got a valid output (under distance budget)
      // Instead use controls that give minimum distance
      if(optimalControls.isEmpty /*&& testData*/) {
        optimalControls = optimalControlsDist //(1 to 8).toList.map(i => origControl(i))
        optimalCoverage = optimalCoverageDist
        optimalDistance = optimalDistanceDist
        optimalOutput = optimalOutputDist
      }

      /* Compare against baseline to make sure we don't do worse */
      val baseLineControls = (1 to 8).toList.map(i => origControl(i))
      val baseLineOutput = calculateOutput(baseLineControls, input)
      val (baseLineDistance, baseLineCoverage, _) =
        if(baseLineOutput == null) {
          (0.0, 0.0, 0.0)
        } else {
          calculateMetrics(input, baseLineOutput, budget=distanceBudgetLocal)
        }
      if((baseLineCoverage > optimalCoverage) && (baseLineDistance < optimalDistance)) {
        optimalControls = baseLineControls
      }

      // Write data line
      //if(!optimalControls.isEmpty || testData) {
        inputIdx += 1
        println(s"optimalDistance = $optimalDistance, optimalCoverage = $optimalCoverage, numInputSamples = $inputIdx")
        writeTrainingData(writer, optimalControls, input, distanceBudgetLocal, optimalOutput.map(x => (x(0), x(1))).toList, optimalDistance, optimalCoverage, optimalPrDet)
      //}
      //if(inputIdx % 10 == 0) System.gc()
    }
  }

    /**
    * Generate control, input, output, distance instance (deterministic version)
    *
    * @param filename Output file
    * @param append true to append to an existing file, false to overwrite existing file
    */
  def generate(filename: String, append: Boolean): Unit = {
    val writer = openOutputFile(filename, append)

    val ctrlLoop0Data = List(0.0)
    val ctrlLoop1Data = elementData(ctrlBounds(2)._1, ctrlBounds(2)._2, ctrlBounds(2)._3)
    val ctrlCmp0Data = elementData(ctrlBounds(3)._1, ctrlBounds(3)._2, ctrlBounds(3)._3)
    val ctrlConst0Data = elementData(ctrlBounds(4)._1, ctrlBounds(4)._2, ctrlBounds(4)._3)
    val ctrlConst1Data = elementData(ctrlBounds(5)._1, ctrlBounds(5)._2, ctrlBounds(5)._3)
    val ctrlConst2Data = elementData(ctrlBounds(6)._1, ctrlBounds(6)._2, ctrlBounds(6)._3)
    val ctrlConst3Data = elementData(ctrlBounds(7)._1, ctrlBounds(7)._2, ctrlBounds(7)._3)
    val ctrlConst4Data = elementData(ctrlBounds(8)._1, ctrlBounds(8)._2, ctrlBounds(8)._3)
    val searchAreaData = elementData(searchAreaBounds._1, searchAreaBounds._2, searchAreaBounds._3)
    val altitudeData = elementData(altitudeBounds._1, altitudeBounds._2, altitudeBounds._3)
    val fovRadiansData = elementData(fovRadiansBounds._1, fovRadiansBounds._2, fovRadiansBounds._3)

    for(ctrlLoop0 <- ctrlLoop0Data;
        ctrlLoop1 <- ctrlLoop1Data;
        ctrlCmp0 <- ctrlCmp0Data;
        ctrlConst0 <- ctrlConst0Data;
        ctrlConst1 <- ctrlConst1Data;
        ctrlConst2 <- ctrlConst2Data;
        ctrlConst3 <- ctrlConst3Data;
        ctrlConst4 <- ctrlConst4Data;
        searchAreaX0 <- List(0.0);
        searchAreaY0 <- List(0.0);
        searchAreaX1 <- List(0.0);
        searchAreaY1 <- searchAreaData;
        searchAreaX2 <- searchAreaData;
        searchAreaY2 <- List(searchAreaY1);
        searchAreaX3 <- List(searchAreaX2);
        searchAreaY3 <- List(searchAreaY0);
        altitude <- altitudeData;
        fovRadians <- fovRadiansData) {
          val controls = List(ctrlLoop0, ctrlLoop1, ctrlCmp0, ctrlConst0, ctrlConst1, ctrlConst2, ctrlConst3, ctrlConst4)
          val searchArea = List((searchAreaX0, searchAreaY0), (searchAreaX1, searchAreaY1),
                                (searchAreaX2, searchAreaY2), (searchAreaX3, searchAreaY3))
          val inputs = new PathPlannerInput((0.0, 0.0), (0.0, 0.0), searchArea, altitude, fovRadians)

          val output = calculateOutput(controls, inputs)

          if(output != null) {
            val (distance, coverage, prDet) = calculateMetrics(inputs, output)
            if (prDet > 0.0) {
              writeData(writer, controls, inputs, output.map(x => (x(0), x(1))).toList, distance, coverage, prDet)
              ptsWritten = ptsWritten + 1
            }
          }

          ptsGenerated = ptsGenerated + 1
          if (ptsGenerated % 10 == 0) {
            println(s"Points tried: $ptsGenerated / $ptsTotal, Points written: $ptsWritten")
          }
    }
  }

  /**
   * Generate control, input, output, distance instances
   *
   * @param filename Output file
   * @param numDataPoints Number of data records to generate
   * @param append true to append to an existing file, false to overwrite existing file 
   */
  def generateRandom(filename: String, numDataPoints: Int, append: Boolean): Unit = {
    val writer = openOutputFile(filename, append)
    
    for (i <- 1 to numDataPoints) {
      val controls = generateControls()
      val input: PathPlannerInput = generateInput()
      val output: Array[Array[Double]] = calculateOutput(controls, input)
      val (distance, coverage, prDet) = calculateMetrics(input, output)
      writeData(writer, controls, input, output.map(x => (x(0), x(1))).toList, distance, coverage, prDet)
    }
  }
  
  /*
   * Write column headers
   */
  private def writeHeaders(writer: FileWriter): Unit = {
    writer.write("ctrlLoop0,ctrlLoop1,ctrlCmp0,ctrlConst0,ctrlConst1,ctrlConst2,ctrlConst3,ctrlConst4,startLocationX,startLocationY,returnLocationX,returnLocationY,searchAreaX0,searchAreaY0,searchAreaX1,searchAreaY1,searchAreaX2,searchAreaY2,searchAreaX3,searchAreaY3,altitude,fovRadians,distance,coverage,prDet,outputBegin")
    val pWriter = new PrintWriter(writer, true)
    pWriter.println()
  }
  
  /*
   * Write controls, inputs, outputs, distance for each generated instance to csv file
   */
  private def writeData(writer: FileWriter, controls: List[Double], input: PathPlannerInput,
                        output: List[(Double, Double)], distance: Double, coverage: Double, prDet: Double): Unit = {
    // controls
    for (c <- controls) {
      writer.write(s"${c.toString},")
    }
    
    // inputs
    writer.write(s"${input.startLocation._1},${input.startLocation._2},")
    writer.write(s"${input.returnLocation._1},${input.returnLocation._2},")
    for(s <- input.searchArea) { // always 4 points
      writer.write(s"${s._1},${s._2},")
    }
    writer.write(s"${input.altitude.toString},")
    writer.write(s"${input.fovRadians.toString}")
    
    //distance
    writer.write(",")
    writer.write(s"${distance.toString},${coverage.toString},${prDet.toString}")
    
    // outputs (variable length list of coordinates)
    var i = 0
    while((i < output.length) && (output(i)._1 != EndMarker))
    {
      val o = output(i)
      writer.write(",")
      writer.write(o._1.toString)
      writer.write(",")
      writer.write(o._2.toString)
      i = i + 1
    }
    
    val pwriter = new PrintWriter(writer, true)
    pwriter.println()
  }

  // TODO: need to uncomment some lines and check for div by 0
  def numPointsDeterministic(): Int = {
    ptsTotal = //(/*(ctrlBounds(1)._2 - ctrlBounds(1)._1 / ctrlBounds(1)._3).floor +*/
      (((ctrlBounds(2)._2 - ctrlBounds(2)._1) / ctrlBounds(2)._3).toInt + 1) *
      (((ctrlBounds(3)._2 - ctrlBounds(3)._1) / ctrlBounds(3)._3).toInt + 1) *
      (((ctrlBounds(4)._2 - ctrlBounds(4)._1) / ctrlBounds(4)._3).toInt + 1) *
      (((ctrlBounds(5)._2 - ctrlBounds(5)._1) / ctrlBounds(5)._3).toInt + 1) *
      (((ctrlBounds(6)._2 - ctrlBounds(6)._1) / ctrlBounds(6)._3).toInt + 1) *
      (((ctrlBounds(7)._2 - ctrlBounds(7)._1) / ctrlBounds(7)._3).toInt + 1) *
      (((ctrlBounds(8)._2 - ctrlBounds(8)._1) / ctrlBounds(8)._3).toInt + 1) *
      Math.pow(((searchAreaBounds._2 - searchAreaBounds._1) / searchAreaBounds._3).toInt + 1, 2.0).toInt * //*
      (((altitudeBounds._2 - altitudeBounds._1) / altitudeBounds._3).toInt + 1) //+
      //(fovRadiansBounds._2 - fovRadiansBounds._1 / fovRadiansBounds._3).floor*/).toInt
    ptsTotal
  }
}

object PathPlannerDataGeneratorTest {
  
  // Function to calculate probability of detection from a given altitude and altitude bounds
  def linearPrDetectionFunction(altitude: Double, altMin: Double, altMax: Double): Double = {
    if (altMax != altMin) {
      1.0 - (altitude - altMin) / (altMax - altMin)
    } else {
      1.0 // if altitude is fixed, use a constant (1.0 implies coverage = probability)
    }
  }
  
  val ppdg = new PathPlannerDataGenerator(Map(1 -> (0.0, 0.0, 0.0), 2 -> (-1.0, 1.0, 1.0), 3 -> (-1.0, 1.0, 1.0),
                                              4-> (1.0, 3.0, 0.5), 5 -> (0.0, 2.0, 0.5), 6 -> (0.0, 2.0, 0.5),
                                              7 -> (1.0, 3.0, 0.5), 8-> (-1.0, 1.0, 0.5)),
                                          (90.0, 90.0, 0.0),
                                          //(0.001, 0.005, 0.001), (0.174533, 0.174533, 0.0),
                                          (100, 500, 100), (0.174533, 0.174533, 0.0),
                                          linearPrDetectionFunction, 2000)
  
  def main(args: Array[String]): Unit = {  
    //val numPts = ppdg.numPointsDeterministic()
    //println(s"Deterministically generating ${numPts} points...")
    //ppdg.generate(args(0), append=false) // false to overwrite file, true to append
    println(s"Generating Path Planner training data...")
    ppdg.generateTrainingData(args(0), append=false)
  }
}