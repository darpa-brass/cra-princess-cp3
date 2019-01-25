package com.cra.princess.training

import com.cra.princess.training.training.{TrainingControls, TrainingMetric, TrainingState}

trait TrainingComponentOutput

trait MetricCalculator extends ((TrainingComponentOutput, TrainingControls, TrainingState) => TrainingMetric) {
}
