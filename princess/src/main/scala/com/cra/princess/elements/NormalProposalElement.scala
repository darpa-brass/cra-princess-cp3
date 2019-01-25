package com.cra.princess.elements

import com.cra.figaro.language.Atomic
import com.cra.figaro.util.random

/**
  * When we make instances of Figaro elements, we can use this trait to specify
  * an appropriate step size in annealing. Elements with this trait
  * will choose a normal deviation from the current value.
  */
trait NormalProposalElement extends Atomic[Double] {
  override type Randomness = Double

  val stdDev: Double

  override def nextRandomness(rand: Randomness) = {
    val u1 = random.nextDouble()
    val u2 = random.nextDouble()
    val w = math.sqrt(-2.0 * math.log(u1))
    val x = 2.0 * math.Pi * u2
    val next = rand + stdDev * w * math.sin(x)
    (next, density(next)/density(rand), 1.0)
  }
}


