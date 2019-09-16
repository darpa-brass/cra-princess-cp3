package com.cra.princess.scenario

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

trait Simulator {
  protected var state: TrainingState = _
  protected var steps = 0
  protected val maxSteps: Int
  var stepsBeyondDone: Option[Int] = None
  val resultsFileName: String
  val rand = new scala.util.Random(4321) // seed

  /**
    * @param exploreExploitAction - list of training controls, each training control handles a separate component
    * @return
    */
  def step(exploreExploitAction: List[TrainingControls]): (TrainingControls, TrainingState, TrainingMetric, Boolean)
  def reset(): TrainingState = {
    stepsBeyondDone = None
    state = Array.fill[Double](4)(rand.nextDouble() - 0.5) // start with random state (-0.5, 0.5)
    //    state = Array(0.0, 0.0, -0.1, 0.0) // start with slight angle at x = 0.0, xDot = 0.0
    state
  }
  def render(): Unit = {
    println(state.toList)
  }
  def getCurrentState: TrainingState = state
}
