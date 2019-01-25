package com.cra.princess.pathplanner.component

import java.io.{File, FileWriter, PrintWriter}

object PathPlannerNNExperiment {
  // Function to calculate probability of detection from a given altitude and altitude bounds
  private def linearPrDetectionFunction(altitude: Double, altMin: Double, altMax: Double): Double = {
    if (altMax != altMin) {
      1.0 - (altitude - altMin) / (altMax - altMin)
    } else {
      1.0 // if altitude is fixed, use a constant (1.0 implies coverage = probability)
    }
  }
  // Experimental parameters
  val ctrlBounds: Map[Int, (Double, Double, Double)] = Map(1 -> (-1.0, 1.0, 0.0), 2 -> (-1.0, 1.0, 0.5), 3 -> (-1.0, 1.0, 1.0),
    4-> (1.0, 3.0, 0.5), 5 -> (0.0, 2.0, 0.5), 6 -> (0.0, 2.0, 0.5),
    7 -> (1.0, 3.0, 0.5), 8-> (-1.0, 1.0, 0.5))
  val altitudeBounds: (Double, Double, Double) = (90.0, 90.0, 0.0)
  val fovRadiansBounds: (Double, Double, Double) = (0.174533, 0.174533, 0.0)
  val searchAreaBounds: (Double, Double, Double) = (100.0, 500.0, 100.0)
  val distanceBudget: Double = 2000.0

  def main(args: Array[String]): Unit = {
    val trainingFile = args(0)
    val testFile = args(1)

    val numInputsList = List(100000, 200000, 300000)
    val numControlsList = List(500)
    val minDistBudgets = List(1000, 2000, 2500)
    for{
      numInputs <- numInputsList
      numControls <- numControlsList
      minDistBudget <- minDistBudgets
    }{
      // generate training data
      val beforeTimeDG = System.currentTimeMillis()
      val ppdg = new PathPlannerDataGenerator(ctrlBounds, altitudeBounds, searchAreaBounds, fovRadiansBounds, linearPrDetectionFunction, distanceBudget)
      ppdg.generateTrainingData(trainingFile, append = false, numInputs = numInputs, numControls = numControls, budgetRange = (minDistBudget, 3000))
      val afterTimeDG = System.currentTimeMillis()
      println(s"Data Generation Time time: ${(afterTimeDG-beforeTimeDG)/1000.0}")

      // instantiate optimizer and train
      val beforeTimeTrain = System.currentTimeMillis()
      val ppOpt = new PathPlannerNNOptimizer()
      ppOpt.train(trainingFile)
      val afterTimeTrain = System.currentTimeMillis()
      val outFile = s"output_${numInputs}_${numControls}_$minDistBudget.csv"

      // generate test data
      ppdg.generateTrainingData(testFile, append = false, numInputs = 1000, testData = true)

      //   test on test data and output results
      val beforeTimeTest = System.currentTimeMillis()
      ppOpt.testOnData(testFile, outFile)
      val afterTimeTest = System.currentTimeMillis()
      val trainingTime = (afterTimeTrain-beforeTimeTrain)/1000.0
      println(s"Training time: $trainingTime")
      println(s"Testing time: ${(afterTimeTest-beforeTimeTest)/1000.0}")
      summarizeOutput(outFile, Seq(numInputs, numControls, trainingTime, minDistBudget))
    }
  }

  private def summarizeOutput(file: String, params: Seq[Double]): Unit ={
    val bufferedSource = scala.io.Source.fromFile(file)
    val lines = bufferedSource.getLines.toList

    var timesDistGreater = 0
    var timesDistLess = 0
    var timesDistEqual = 0
    var diffDist = 0.0
    var percentDistDiff = 0.0

    var timesGreater = 0
    var timesLess = 0
    var timesEqual = 0
    var diff = 0.0
    var percentDiff = 0.0
    val results = lines.map{ line =>
      val cols = line.split(",").map(_.trim)
      val inferredMetric = cols(23).toDouble
      val baselineMetric = cols(24).toDouble
      val inferredDistance = cols(25).toDouble
      val baselineDistance = cols(26).split("\\(")(0).toDouble
      val processedInferred = Math.max(0.0, inferredMetric)
      val processedBaseline = Math.max(0.0, baselineMetric)
      diff += inferredMetric - baselineMetric
      percentDiff += 100*(inferredMetric - baselineMetric)/baselineMetric

      if (inferredDistance > baselineDistance)
        timesDistGreater += 1
      else if (inferredDistance < baselineDistance)
        timesDistLess += 1
      else
        timesDistEqual += 1
      diffDist += inferredDistance - baselineDistance
      percentDistDiff += 100*(inferredDistance - baselineDistance)/baselineDistance


      if (processedInferred > processedBaseline)
      timesGreater += 1
      else if (processedInferred < processedBaseline)
        timesLess += 1
      else
        timesEqual += 1
      ((inferredMetric, baselineMetric), (inferredDistance, baselineDistance))
    }
    val inferredSuccessBaseSuccess = results.count{case ((inferred, baseline), _) => inferred >= 0.0 && baseline >= 0.0}
    val inferredSuccessBaseFail = results.count{case ((inferred, baseline), _) => inferred >= 0.0 && baseline == -1.0}
    val inferredFailBaseSuccess = results.count{case ((inferred, baseline), _) => inferred == -1.0 && baseline >= 0.0}
    val inferredFailBaseFail = results.count{case ((inferred, baseline), _) => inferred == -1.0 && baseline == -1.0}
    val inferredExceptionBaseSuccess = results.count{case ((inferred, baseline), _) => inferred == -2.0 && baseline >= 0.0}
    val inferredExceptionBaseFail = results.count{case ((inferred, baseline), _) => inferred == -2.0 && baseline == -1.0}

    val bothSuccessDist = results.filter{case ((inferred, baseline), _) => inferred == -2.0 && baseline == -1.0}.map(_._2)
    val timesGreaterBothSuccess = bothSuccessDist.count{case (inferred, baseline) => inferred > baseline}
    val timesEqualBothSuccess = bothSuccessDist.count{case (inferred, baseline) => inferred == baseline}
    val timesLessBothSuccess = bothSuccessDist.count{case (inferred, baseline) => inferred < baseline}
    val avgDiffDistBothSuccess = bothSuccessDist.map{case (inferred, baseline) => inferred - baseline}.sum/bothSuccessDist.size

    println(timesGreater, timesEqual, timesLess)
    println(diff/(timesGreater + timesEqual + timesLess))

    val avgDiff = diff/(timesGreater + timesEqual + timesLess)
    val avgDistDiff = diffDist/(timesDistGreater + timesDistEqual + timesDistLess)
    val avgPercentDistDiff = percentDiff/(timesDistGreater + timesDistEqual + timesDistLess)
    val writer = new FileWriter(new File("path_planner_optimization_results.csv"), true)
    val pWriter = new PrintWriter(writer, true)
    pWriter.println((params++Seq(timesGreater,timesEqual, timesLess, avgDiff, inferredSuccessBaseSuccess,
      inferredSuccessBaseFail, inferredFailBaseSuccess, inferredFailBaseFail, inferredExceptionBaseSuccess,
      inferredExceptionBaseFail, timesDistGreater, timesDistEqual, timesDistLess, avgDistDiff, avgPercentDistDiff,
      timesGreaterBothSuccess, timesEqualBothSuccess, timesLessBothSuccess, avgDiffDistBothSuccess)).mkString(","))
  }
}