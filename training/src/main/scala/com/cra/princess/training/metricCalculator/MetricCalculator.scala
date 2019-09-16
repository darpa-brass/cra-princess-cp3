package com.cra.princess.training.metricCalculator

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

trait MetricCalculator[Output <: TrainingComponentOutput] extends ((Output, TrainingControls, TrainingState) => TrainingMetric) {
}
