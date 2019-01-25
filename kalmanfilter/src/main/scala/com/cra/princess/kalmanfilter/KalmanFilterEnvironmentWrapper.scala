package com.cra.princess.kalmanfilter

import com.cra.princess.core.{InstanceBuilder, PrincessFeature, PrincessFeatureCollection}
import com.cra.princess.models.kalmanfiltercomponents.KalmanFilterEnvironment

/**
  * Created by smarotta on 4/24/2017.
  */
class KalmanFilterEnvironmentWrapper(val env: KalmanFilterEnvironment)
  extends PrincessFeatureCollection(Seq[PrincessFeature]()) with Serializable

// TODO: Unnecessary logic? See comments on InstanceBuilder -klu
class KalmanFilterEnvironmentBuilder extends InstanceBuilder[KalmanFilterEnvironmentWrapper] {
  def build(c:PrincessFeature) = {
    new KalmanFilterEnvironmentWrapper(new KalmanFilterEnvironment())
  }
}
