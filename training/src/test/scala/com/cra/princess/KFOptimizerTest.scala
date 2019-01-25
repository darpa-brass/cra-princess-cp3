package com.cra.princess

import java.io.{File, FileOutputStream, PrintWriter}

import com.cra.princess.scenario.KalmanFilterScenarioGenerator
import org.scalatest.{FlatSpec, Matchers}
import com.cra.princess.training.D4JOptimizer
import com.cra.princess.training.training.generateRandomSample

class KFOptimizerTest extends FlatSpec with Matchers{

  val kerasActorFile = "model.h5"
  val d4jActorFile = "d4j_actor_weight.h5"


  val kerasCriticFile = "q_model.h5"
  val d4jCriticFile = "d4j_critic_weight.h5"

  "KF D4J Optimizer" should "successfully convert from keras" in {
    //val trainingFile = "kf_training_data_1.csv"
    List((kerasActorFile, d4jActorFile), (kerasCriticFile, d4jCriticFile)).foreach{ case (kerasFile, d4jFile) =>
      D4JOptimizer.convertKerasModel(kerasFile, d4jFile)
    }
  }

  "KF D4J Optimizer" should "find optimized controls in" in {
    val resultsFile = "kf_results.csv"
    val optimizer = D4JOptimizer(d4jActorFile, d4jCriticFile)
    optimizer.actorForwardPass(
      Array(Array(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
      Array(Array(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)))
    assert(optimizer.actorInputDim == 20)
    assert(optimizer.actorOutputDim == 20)
    assert(optimizer.criticInputDim == 40)
    assert(optimizer.criticOutputDim == 1)
    println(optimizer.optimize(List(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)).toList)
    runExperiment(optimizer, resultsFile)
  }

  private def runExperiment(optimizer: D4JOptimizer, resultsFile: String): Unit ={
    val pw = new PrintWriter(new FileOutputStream(new File(resultsFile), true))
    pw.println(s"wcX, wcY, wcRegionLower, wcRegionUpper, sensorNoiseStdev, baselineDist, inferredDist")
    // generate testing scenarios
    val wcXRange: (Double, Double) = (-2, 2)
    val wcYRange: (Double, Double) = (-1, 1)
    val wcRegionRange: (Double, Double) = (166.79262, 555.9754 - 100)
    val sensorNoiseStdevRange: (Double, Double) = (0, 8)

    for(_ <- 0 until 1000){
      val wcX = generateRandomSample(wcXRange)
      val wcY = generateRandomSample(wcYRange)
      val wcRegionLower = generateRandomSample(wcRegionRange)
      val wcRegionUpper = generateRandomSample((wcRegionLower + 100, wcRegionRange._2 + 100))
      val sensorNoiseStdev = generateRandomSample(sensorNoiseStdevRange)
      val numResiduals = 10
      val (_, baselineDist, baseControls, _) = KalmanFilterScenarioGenerator.runScenario(
        waterCurrentVector = (wcX, wcY),
        waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
        sensorNoiseStdev = sensorNoiseStdev,
        numResiduals = numResiduals,
        optimizerOpt = None)
      val (_, inferredDist, inferredControls, _) = KalmanFilterScenarioGenerator.runScenario(
        waterCurrentVector = (wcX, wcY),
        waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
        sensorNoiseStdev = sensorNoiseStdev,
        numResiduals = numResiduals,
        optimizerOpt = Some(optimizer))
      pw.println(s"$wcX, $wcY, $wcRegionLower, $wcRegionUpper, $sensorNoiseStdev, $baselineDist, " +
        s"$inferredDist, ${baseControls.mkString(",")}, ${inferredControls.mkString(",")}")
    }
  }
}
