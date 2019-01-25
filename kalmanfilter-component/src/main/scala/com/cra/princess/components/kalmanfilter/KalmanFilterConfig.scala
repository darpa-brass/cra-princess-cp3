package com.cra.princess.components.kalmanfilter

import com.cra.princess.core.BoundedScalarPrincessFeature

import scala.beans.BeanProperty

class KalmanFilterConfig {
  @BeanProperty var samplingPeriod: BoundedScalarPrincessFeature = null
  @BeanProperty var processNoiseXPos: BoundedScalarPrincessFeature = null
  @BeanProperty var processNoiseYPos: BoundedScalarPrincessFeature = null
  @BeanProperty var processNoiseXVel: BoundedScalarPrincessFeature = null
  @BeanProperty var processNoiseYVel: BoundedScalarPrincessFeature = null
  @BeanProperty var xmeasurementNoise: BoundedScalarPrincessFeature = null
  @BeanProperty var ymeasurementNoise: BoundedScalarPrincessFeature = null
  @BeanProperty var actuator1: BoundedScalarPrincessFeature = null
  @BeanProperty var actuator2: BoundedScalarPrincessFeature = null
  @BeanProperty var actuator3: BoundedScalarPrincessFeature = null
  @BeanProperty var actuator4: BoundedScalarPrincessFeature = null
}