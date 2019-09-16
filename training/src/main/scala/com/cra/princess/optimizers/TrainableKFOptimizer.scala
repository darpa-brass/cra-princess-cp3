package com.cra.princess.optimizers

import com.cra.princess.kalmanfilter.KalmanFilterInputWrapper
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterOutput
import com.cra.princess.training._
import com.cra.princess.training.actorcritic.{ActorCriticTrainer, D4JNetwork}
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}
import com.cra.princess.util.Logs

class TrainableKFOptimizer(val trainer: ActorCriticTrainer, val params: Map[String, Double],
                           val discountFactor: Double = 0.5, val batchSize: Int = 10, val maxBufferSize: Int = 100,
                           val initialState: TrainingState, val initialControls: TrainingControls, val policy: ExploreExploitPolicy)
  extends KFOptimizer(trainer.getActorCriticNetwork) with TrainableNNOptimizer[KalmanFilterInputWrapper, KalmanFilterOutput] with Logs {

  override protected def computeStateAndMetric(input: KalmanFilterInputWrapper, output: KalmanFilterOutput): (TrainingState, TrainingMetric) = {
    trainingTime = input.time
    val newState: TrainingState = input.state.getCombinedState.toArray
    val metric: TrainingMetric = -output.getDistance
    (newState, metric)
  }
}

object TrainableKFOptimizer {
  def apply(actorFile: String, criticFile: String, dimension: Int = 6,
            discountFactor: Double = 0.5, batchSize: Int = 10, initialState: TrainingState = Array(0.0, 0.0),
            initialControls: TrainingControls = Array(1, 1, 0.3, 0.3, 0.1, 0.2)): TrainableKFOptimizer = {
    val params = Map(
      "dimension" -> dimension.toDouble,
      "min" -> 0.0,
      "max" -> 1.0,
    )
    val model = new D4JNetwork(actorFile, criticFile)
    val trainer = new ActorCriticTrainer(model, discountFactor)
    val policy = new ExploreExploitPolicy(params("min"), params("max"))
    new TrainableKFOptimizer(trainer, params, discountFactor, batchSize, 100, initialState, initialControls, policy)
  }
}
