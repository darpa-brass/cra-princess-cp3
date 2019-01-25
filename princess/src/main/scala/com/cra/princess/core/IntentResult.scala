package com.cra.princess.core

import com.cra.princess.{Metric, Threshold}

case class IntentResult(componentId: Int, pass: Boolean, failureData: Option[FailureData] = None) {}
case class FailureData(metricName: String, metricValue: Metric, threshold: Threshold, relation: ThresholdRelation)
