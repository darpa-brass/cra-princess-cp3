package com.cra.princess.kalmanfilter

import com.cra.princess.core.{PrincessFeature, PrincessFeatureCollection}
import com.cra.princess.models.kalmanfiltercomponents.{KalmanFilterEnvironment, KalmanFilterOutput}

/**
  * Created by smarotta on 4/24/2017.
  */
class KalmanFilterEnvironmentWrapper(val env: KalmanFilterEnvironment, val kfo: KalmanFilterOutput = null)
  extends PrincessFeatureCollection(Seq[PrincessFeature]()) with Serializable