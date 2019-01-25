package com.cra.princess

import com.cra.princess.training.ActorCriticTrainer
import org.scalatest.{FlatSpec, Matchers}

class RLTest extends FlatSpec with Matchers{

  val d4jActorFile = "d4j_actor_weight.h5"
  val d4jCriticFile = "d4j_critic_weight.h5"

  "Actor Critic Trainer" should "Train the Optimizer" in {
    val trainer = new ActorCriticTrainer(d4jActorFile, d4jCriticFile, 0.5)
  }
}
