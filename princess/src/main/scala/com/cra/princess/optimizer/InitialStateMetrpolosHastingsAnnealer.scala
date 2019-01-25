package com.cra.princess.optimizer

import com.cra.figaro.algorithm.sampling._
import com.cra.figaro.language.{Element, NamedEvidence, Universe}

/**
  * A MH annealer that begins at a specified initial state and energy. The final solution will not be worse than the initial state.
  */
class InitialStateMetropolosHastingsAnnealer(universe: Universe, myNumSamples: Int, scheme: ProposalScheme, annealSchedule: Schedule, initialStateElements: List[Element[_]])
  extends OneTimeMetropolisHastingsAnnealer(universe, myNumSamples, scheme, annealSchedule, 0, 1) with OneTimeMPESampler {

  override def doInitialize(): Unit = {
    Forward(universe, chainCache)
    initConstrainedValues()
    dissatisfied = universe.conditionedElements.toSet filter (!_.conditionSatisfied)
    currentEnergy = universe.constrainedElements.map(_.constraintValue).sum

    initUpdates()
    if (dissatisfied.nonEmpty) bestEnergy = Double.MinValue else bestEnergy = currentEnergy

    initialStateElements.foreach(elt => {
      elt.activate()
      elt.unset()
    })
  }
}

object InitialStateMetropolosHastingsAnnealer {
  /**
    * Create a one-time Metropolis-Hastings annealer using the given number of samples, proposal
    * scheme and annealing schedule.
    */
  def apply(numSamples: Int, scheme: ProposalScheme, annealSchedule: Schedule, initialStateElements: List[Element[_]])(implicit universe: Universe) =
    new InitialStateMetropolosHastingsAnnealer(universe, numSamples, scheme, annealSchedule, initialStateElements)
}
