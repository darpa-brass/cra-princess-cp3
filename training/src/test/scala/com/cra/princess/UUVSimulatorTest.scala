package com.cra.princess

import com.cra.princess.scenario.KalmanFilterDDPGSimulator
import com.cra.princess.training.training.TrainingState
import org.scalatest.{FlatSpec, Matchers}

class UUVSimulatorTest extends FlatSpec with Matchers{
  "UUV Simulator" should "create same scenarios" in {
    var states = List.empty[TrainingState]
    for(_ <- 1 to 10) {
      var newStates = List.empty[TrainingState]
      val kfsim = new KalmanFilterDDPGSimulator("", 10)
      for(_ <- 1 to 20) {
        kfsim.reset()
        newStates = newStates ++ List(kfsim.getCurrentState)
      }
      if(states.nonEmpty){
        (states zip newStates).foreach{ case (state1, state2) =>
          assert(state1 sameElements state2)
        }
      }
      states = newStates
    }
  }
}
