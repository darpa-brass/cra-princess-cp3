package com.cra.princess.training.ddpg

import java.util.Random

import com.cra.princess.training.ReplayBuffer
import com.cra.princess.training.ddpg.structures.{Actor, Critic}
import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}
import org.nd4j.linalg.api.ndarray.INDArray
import org.nd4j.linalg.factory.Nd4j

/**
  * Generic Trainer that can support Kalman Filter, Path Planner, Cartpole, and other examples
  */
class DDPGTrainer(val actor: Actor, val critic: Critic, batchSize: Int,
                  discountFactor: Double, delta: Double, saveFile: String){

  val func = OrnsteinUhlenbeckNoise(actor.inputDim, Nd4j.create(Array.fill(actor.inputDim)(0.0)), 0.3, 0.15, 0.01)
  val seed = 4321
  val rand = new Random(seed)
  val MAX_BUFFER_SIZE = 1000000
  private val replayBuffer =
    new ReplayBuffer[(TrainingState, TrainingControls, TrainingMetric, TrainingState, Boolean)](MAX_BUFFER_SIZE)

  private var exploreExploitAction: TrainingControls = _

  def saveActorParams(): Unit = actor.behaviorNetwork.saveParams(saveFile)

  def calculateExploreExploitCtrls(currentState: TrainingState, numTotalSteps: Int, numEpisodes: Int): TrainingControls = {
    exploreExploitAction = (actor.predictWithBehavior(currentState) zip explorationNoise(actor.outputDim, numTotalSteps, numEpisodes))
      .map { case (ctrl, noise) => ctrl + noise }
    exploreExploitAction
  }

  def trainStep(currentState: TrainingState, nextState: TrainingState,
                reward: TrainingMetric, terminal: Boolean): Unit = {
    replayBuffer.storeInstance((currentState, exploreExploitAction, reward, nextState, terminal))

    // If we have a batch, update networks
    if (replayBuffer.length() >= batchSize && terminal) {

      // sample batch from replay buffer
      val miniBatch = replayBuffer.getMiniBatch(batchSize)
      val sBatch: Array[TrainingState] = miniBatch.map(_._1)
      val aBatch: Array[TrainingControls] = miniBatch.map(_._2)
      val rBatch: Array[TrainingMetric] = miniBatch.map(_._3)
      val s2Batch: Array[TrainingState] = miniBatch.map(_._4)
      val tBatch: Array[Boolean] = miniBatch.map(_._5)

      // Calculate targets for critic update - note: uses actor's and critic's target network
      val targetQBatch: Array[Double] = s2Batch.map { state =>
        val actorPrediction = actor.predictWithTarget(state)
        critic.predictWithTarget(state, actorPrediction).head
      }

      val criticTargets: Array[TrainingMetric] = (0 until batchSize).map { k =>
        if (tBatch(k)) rBatch(k) // This is a terminal state
        else rBatch(k) + targetQBatch(k) * discountFactor // Usual case (not terminal)
      }.toArray

      // Update critic with targets
      // Note: predictedQValue is just for reporting
      critic.train(sBatch, aBatch, criticTargets)
      //println(s"critic weights: ${critic.behaviorNetwork.dl4jNet.params}")
      /////////////////////////////////////////////////
      // Update target networks with policy gradient.//
      /////////////////////////////////////////////////

      // update L1 networks
      actor.updateTemp()
      critic.updateTemp()

      // Calculate policy gradient
      val aOuts = sBatch.map(actor.predictWithTemp)
      val rOuts = (sBatch zip aOuts).map { case (s, a) => s ++ a }.map(critic.predictWithTemp)
      val criticGrads: INDArray = critic.tempNetwork.calculateGradient(sBatch, aOuts, rOuts.map(_.head), delta)
      val policyGrad: INDArray = actor.tempNetwork.calculateGradient(sBatch, aOuts, criticGrads, delta)

      println(s"policyGrad: $policyGrad")
      actor.behaviorNetwork.applyGradient(policyGrad)

      // apply policy gradient
      actor.updateTarget()
      critic.updateTarget()
    }
  }

  def explorationNoise(actionDim: Int, numTotalSteps: Int, numEpisodes: Int): TrainingControls = {
    Array.fill(actionDim)(((rand.nextDouble() * 2.0) - 1.0)/1000.0)
    //Array.fill(actionDim)(0.0)
    //func().toDoubleVector
  }

  case class OrnsteinUhlenbeckNoise(actionDim: Int , mu: INDArray, sigma: Double, theta: Double,
                                    delta: Double, x0: Option[INDArray] = None) extends (() => INDArray){
    private var xPrev = x0 match {
      case Some(initialX) => initialX
      case _ => Nd4j.create(Array.fill(actionDim)(0.0))
    }

    override def apply(): INDArray = {
      val vectorDiff = mu.sub(xPrev).mul(theta).mul(delta)
      val randVec = Nd4j.create(Array.fill(actionDim)(rand.nextGaussian()))
      val vectorProd = randVec.mul(sigma).mul(Math.sqrt(delta))
      val x = xPrev.add(vectorDiff).add(vectorProd)
      xPrev = x
      x
    }
  }
}

