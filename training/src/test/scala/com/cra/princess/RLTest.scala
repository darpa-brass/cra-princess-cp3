package com.cra.princess

import com.cra.princess.training.actorcritic.{ActorCriticTrainer, D4JNetwork}
import com.cra.princess.training.ControlGenerator
import org.scalatest.{FlatSpec, Matchers}

class RLTest extends FlatSpec with Matchers{

  val d4jActorFile = "training/src/test/resources/d4j_actor_weights_unit_test.h5"
  val d4jCriticFile = "training/src/test/resources/d4j_critic_weights_unit_test.h5"

  "Actor Critic Trainer" should "Train the Optimizer" in {
    val optimizer = D4JNetwork(d4jActorFile, d4jCriticFile)
    val discountFactor = 0.5
    val trainer = new ActorCriticTrainer(optimizer, discountFactor)
  }

  "Control Generator" should "generate potential control variables" in {
    val params = Map(
      "dimension" -> 3.0,
      "min" -> -5.0,
      "max" -> 5.0,
      "granularity" -> 0.5
    )
    assert(ControlGenerator.generateRandomControls(params).size == 1000)
  }
}
