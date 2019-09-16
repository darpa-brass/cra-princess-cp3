package com.cra.princess.training.metricCalculator

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

object KalmanFilterMetricCalculator extends MetricCalculator[KFTrainingComponentOutput] {
  override def apply(v1: KFTrainingComponentOutput, v2: TrainingControls, v3: TrainingState): TrainingMetric = {
    v1.residuals.map{ case (x,y) => Math.hypot(x,y)}.sum
  }
}
