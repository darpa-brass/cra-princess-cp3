package com.cra.princess.optimizer

import scala.collection.mutable

abstract class StateEstimator {

  protected val map: mutable.Map[String, Option[Double]] = mutable.Map.empty

  def keys: Set[String]

  def valuesForKeys(keys: Set[String]): Map[String, Option[Double]]

}
