package com.cra.princess

import java.io.{File, FileOutputStream, PrintWriter}

import com.cra.princess.optimizers.TrainableKFOptimizer
import com.cra.princess.scenario.KalmanFilterScenarioGenerator
import com.cra.princess.training.actorcritic.D4JNetwork
import org.scalatest.{FlatSpec, Matchers}

class KFOptimizerTest extends FlatSpec with Matchers{

  val path = ""//"training/src/test/resources/"
  val kerasActorFile: String = path + "keras_actor_model.h5"
  val d4jActorFile: String = path + "gameActor.h5"

  val kerasCriticFile: String = path + "keras_critic_model.h5"
  val d4jCriticFile: String = path + "gameCritic.h5"

  "KF D4J Optimizer" should "successfully convert from keras" in {
    List((kerasActorFile, d4jActorFile), (kerasCriticFile, d4jCriticFile)).foreach{ case (kerasFile, d4jFile) =>
      D4JNetwork.convertKerasModel(kerasFile, d4jFile)
    }
  }

  "KF D4J Optimizer" should "find optimized controls in" in {
    val resultsFile = "kf_results.csv"
    val network = D4JNetwork(d4jActorFile, d4jCriticFile)
    val optimizer = TrainableKFOptimizer("actorParams.h5", "criticParams.h5")
//    val optimizer = TrainableKFOptimizer(d4jActorFile, d4jCriticFile)
    network.actorForwardPass(
      Array(Array(1, 1, 1, 1)),
      Array(Array(1, 1, 1, 1, 1, 1)))
    assert(network.actorInputDim == 4)
    assert(network.actorOutputDim == 6)
    assert(network.criticInputDim == 10)
    assert(network.criticOutputDim == 1)
    assert(network.optimize(List(1, 1, 1, 1)).toList ==
      List(2.563066244125366, 1.11273193359375, 1.8094964027404785,
        2.051718235015869, 2.542667865753174, 0.9035800695419312))
    runExperiment(optimizer, resultsFile)
  }

  private def runExperiment(optimizer: TrainableKFOptimizer, resultsFile: String): Unit ={
    // generate testing scenarios
//    val wcXRange: (Double, Double) = (-2, 2)
//    val wcYRange: (Double, Double) = (-1, 1)
//    val wcRegionRange: (Double, Double) = (166.79262, 555.9754 - 100)
//    val sensorNoiseStdevRange: (Double, Double) = (0, 8)
    for(i <- 0 until 10000){
      val pw = new PrintWriter(new FileOutputStream(new File(resultsFile), true))
      val wcX = 1//generateRandomSample(wcXRange)
      val wcY = 0//generateRandomSample(wcYRange)
      val wcRegionLower = 150//generateRandomSample(wcRegionRange)
      val wcRegionUpper = 400//generateRandomSample((wcRegionLower + 100, wcRegionRange._2 + 100))
      val sensorNoiseStdev = 1//generateRandomSample(sensorNoiseStdevRange)
      val numResiduals = 10
      val (_, realPositionBase, dest) = KalmanFilterScenarioGenerator.runScenario(
        uuvSpeed = Math.sqrt(2),
        end = (0,400),
        waterCurrentVector = (wcX, wcY),
        waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
        sensorNoiseStdev = sensorNoiseStdev,
        numResiduals = numResiduals,
        optimizerOpt = None)
      println("running adapted case....")
      val (estPos, realPositionAdapt, _) = KalmanFilterScenarioGenerator.runScenario(
        uuvSpeed = Math.sqrt(2),
        end = (0,400),
        waterCurrentVector = (wcX, wcY),
        waterCurrentRegion = ((Double.NegativeInfinity, wcRegionLower), (Double.PositiveInfinity, wcRegionUpper)),
        sensorNoiseStdev = sensorNoiseStdev,
        numResiduals = numResiduals,
        optimizerOpt = Some(optimizer))
      val baselineDist: Double =  Math.hypot(realPositionBase._1 - dest._1, realPositionBase._2 - dest._2)
      val adaptDist: Double =  Math.hypot(realPositionAdapt._1 - dest._1, realPositionAdapt._2 - dest._2)

      val verdict = if(baselineDist < adaptDist) 0 else 1

      pw.println(s"$wcX, $wcY, $wcRegionLower, $wcRegionUpper, $sensorNoiseStdev, ${estPos._1}, ${estPos._2}, $baselineDist, $adaptDist, $verdict")
      println(i, optimizer.policy.getIterations, optimizer.getTrainCounter)
      optimizer.resetTrainCounter()
      optimizer.policy.setIterations(i)
      optimizer.trainer.clearBuffer()
      optimizer.saveParams()
      pw.close()
    }
  }
}
