package com.cra.princess.training.ddpg

import java.io.{File, FileWriter}

import com.cra.princess.scenario.{CartpoleSimulator, KalmanFilterDDPGSimulator, Simulator}
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

object DDPGController {

  def train(numEpisodes: Int, trainers: List[DDPGTrainer], simulator: Simulator): Unit = {
    ///////// DDPG train ////////////////
    var totalSteps = 0
    // Main loop
    for (i <- 0 until numEpisodes) {
      println(s"\t$i")
      simulator.reset()
      // get initial state (component inputs/environment)
      var currentState: TrainingState = simulator.getCurrentState

      // bookkeeping for evaluation
      var episodeReward: Double = 0.0
      // vars for while condition
      var j = 0
      var scenarioFinished = false
      while (!scenarioFinished) {
        val exploreExploitCtrls = trainers.map { trainer =>
          trainer.calculateExploreExploitCtrls(currentState, totalSteps, i)
        }
        val (controls: TrainingControls,  nextState: TrainingState, reward: TrainingMetric, terminal: Boolean) =
          simulator.step(exploreExploitCtrls)

        trainers.foreach { trainer =>
          trainer.trainStep(currentState, nextState, reward, terminal)
        }

        totalSteps += 1
        // Advance current state var
        currentState = nextState
        episodeReward += reward
        scenarioFinished = terminal
        j += 1
      }

//      println(s"episodes ran: $i")
      //println(s"numSteps: $j")
      val file = new FileWriter(new File(simulator.resultsFileName), true)
      file.append(s"$episodeReward\n")
      file.close()

      if(episodeReward > 100)
        println(s"large reward: $episodeReward, $i")
      else if(episodeReward > 1)
        println(s"episode reward: $episodeReward, $i")
    }
    trainers.foreach{ trainer =>
      trainer.saveActorParams()
    }
  }
}
