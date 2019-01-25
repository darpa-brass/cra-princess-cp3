package com.cra.princess.core

import com.cra.princess.Threshold

case class ThresholdData(name: String, threshold: Threshold, relation: ThresholdRelation) {

  def withValue(newValue: Threshold): ThresholdData = ThresholdData(name, newValue, relation)

}
