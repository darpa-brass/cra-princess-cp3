package com.cra.princess

import com.cra.princess.optimizers.TrainableNNOptimizer
import com.cra.princess.training._
import com.cra.princess.training.actorcritic.{ActorCriticTrainer, D4JNetwork}
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

class TestOptimizer(val trainer: ActorCriticTrainer, val params: Map[String, Double],
                    val discountFactor: Double = 0.5, val batchSize: Int = 10, val maxBufferSize: Int,
                    val initialState: TrainingState, val initialControls: TrainingControls,
                    val policy: ExploreExploitPolicy)
  extends TrainableNNOptimizer[GameState, GameState]{

  def selectMove(input: GameState): Move = {
    val (x1, y1) = input.currentLoc
    val (x2, y2) = input.dest
    val ctrls: TrainingControls = trainer.getActorCriticNetwork.optimize(List(x1, y1, x2, y2))
    println(ctrls.toList, input)
    Move(ctrls(0).round.toInt, ctrls(1).round.toInt)
  }

  override protected def computeStateAndMetric(input: GameState, output: GameState): (TrainingState, TrainingMetric) = {
    val (x1, y1) = input.prevLoc
    val (x2, y2) = input.currentLoc
    val (x3, y3) = input.dest
    val dist1 = Math.hypot(x1 - x3, y1 - y3)
    val dist2 = Math.hypot(x2 - x3, y2 - y3)
    val diff = dist1 - dist2
    val metric: TrainingMetric = -dist2
    println(input.prevLoc, input.currentLoc, metric)
    (Array(x1, y1, x3, y3), metric)
  }
}

object TestOptimizer {
  def apply(actorFile: String, criticFile: String, dimension: Int = 4,
            discountFactor: Double = 0.5, batchSize: Int = 32, maxBufferSize: Int = 100, initialState: TrainingState = Array(1, 1, 5, -5),
            initialControls: TrainingControls = Array(1, -1)): TestOptimizer = {
    val params = Map(
      "dimension" -> dimension.toDouble,
      "min" -> -2.0,
      "max" -> 2.0,
    )
    val model = new D4JNetwork(actorFile, criticFile)
    val trainer = new ActorCriticTrainer(model, discountFactor)
    val policy = new ExploreExploitPolicy(params("min"), params("max"))
    new TestOptimizer(trainer, params, discountFactor, batchSize, maxBufferSize, initialState, initialControls, policy)
  }
}

