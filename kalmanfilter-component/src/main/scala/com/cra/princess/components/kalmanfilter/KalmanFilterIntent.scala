package com.cra.princess.components.kalmanfilter

import com.cra.princess.Metric
import com.cra.princess.core.{Intent, LessThan, ThresholdData}
import com.cra.princess.optimizer.ComponentIds

/**
 * An intent specialization for the Kalman filter component. 
 * Additionally constrains the number of steps over which the error volume will be evaluated.
 */
// TODO: this could be abstracted into a more general intent type (e.g. TimeWindowIntent) - DG
class KalmanFilterIntent(opReqs : List[Intent], threshold : Metric, val numKfSteps:Int)
  extends Intent(ComponentIds.KFComponentId, "keep error volume delta and measurement residual below threshold", opReqs, List(ThresholdData("residual", threshold, LessThan()))) with Serializable {
  
}
