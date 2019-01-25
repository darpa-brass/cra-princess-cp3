package com.cra.princess.elements

import com.cra.figaro.language._
import com.cra.figaro.util.random

/**
  * An element that resamples from the supplied inputs
  * @param values The values to resample from
  */
class BootstrapElement[T](val values:Seq[T], name:Name[T], elementCollection:ElementCollection)
  extends Element[T](name, elementCollection) with Atomic[T] {

  override type Randomness = Int
  override def generateRandomness() = random.nextInt(values.size)
  override def generateValue(rand: Int) = values(rand)
  val constantDensity = 1.0 / values.size
  override def density(t: T): Double = if(values.contains(t)) constantDensity else 0.0
}

object BootstrapElement {
  def apply[T](values:Seq[T])(implicit name:Name[T], ec:ElementCollection) =
    new BootstrapElement(values, name, ec)
}