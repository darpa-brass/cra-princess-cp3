package com.cra.princess.training.ddpg

import java.io.FileWriter

import com.cra.princess.scenario.Simulator
import com.cra.princess.training.ddpg.structures.{Actor, Critic}
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

object PreTrainer {

  def preTrain(actor: Actor, critic: Critic, preTrainFileName: String, rewardThreshold: Double): Unit ={
    val bufferedSource = scala.io.Source.fromFile(preTrainFileName)
//    var actorTrainingNum = 0
    var lineNum = 0
    for (line <- bufferedSource.getLines) {
      if(lineNum % 10000 == 0) println(lineNum)
      val data = line.split(",").map(_.toDouble)
      val state: TrainingState = data.take(actor.inputDim)
      val ctrls: TrainingControls = data.slice(actor.inputDim, actor.inputDim + actor.outputDim)
      val reward: TrainingMetric = data.last
//      critic.train(Array(state), Array(ctrls), Array(reward))
      if(reward > rewardThreshold) {
//        actorTrainingNum += 1
        actor.train(Array(state), Array(ctrls))
      }
      lineNum += 1
    }
//    println(s"number of actor training samples: $actorTrainingNum")
    critic.matchTargetToBehavior()
    actor.matchTargetToBehavior()
  }

  def generateData(numEpisodes: Int, simulator: Simulator, preTrainFileName: String,
                   ctrlDim: Int, defaultCtrls: Array[Double]): Unit ={
    // generate data (state, control, reward)
    val fw = new FileWriter(preTrainFileName, true)
    for(i <- 0 until numEpisodes){
      println(s"generating data for episode $i")
      var savedData = List.empty[(TrainingState, TrainingControls)]
      simulator.reset()
      var terminal = false
      var lastReward = 0.0
      var steps = 0
      val randomCtrls: List[TrainingControls] = List(defaultCtrls.map(c => c + 2*(Math.random() - 0.5)))
      while(! terminal){
        val (_: TrainingControls,  nextState: TrainingState, reward: TrainingMetric, isTerminal: Boolean) =
          simulator.step(randomCtrls)
        savedData = savedData :+ (nextState, randomCtrls.head)
        lastReward = reward
        terminal = isTerminal
        steps += 1
      }
      println(steps)
      savedData.foreach{ case(state, ctrls) =>
        fw.append(s"${state.mkString(",")}, ${ctrls.mkString(",")}, $lastReward\n")
      }
    }
    fw.close()
  }
}
