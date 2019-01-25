package com.cra.princess.kalmanfilter

import com.cra.princess.core.PrincessTypeImplicits._
import com.cra.princess.core._
import com.cra.princess.localizationalgorithm.components.ComponentState
import org.apache.commons.math3.linear.{ArrayRealVector, RealMatrix, RealVector}

/**
 * Represents the input that will be reasoned over with the component modeling API.
  *
  * @param state Position and velocity at time t
 * @param actuatorValues Motion plan all for times t' > t
 * @param observations Sensed x and y velocities for times t' >= t
 * @param initialCovarianceDiagonal Values of diagonal elements of coviarance matrix
 * @param initialCovarianceOffDiagonal Values of off-diagonal elements of covariance matrix
 */
class KalmanFilterInputWrapper(val state: ComponentState, val actuatorValues: RealVector, val observations: Seq[RealVector],
    val initialCovarianceDiagonal:Double, val initialCovarianceOffDiagonal:Double, val covariance: RealMatrix)
        extends PrincessFeatureCollection(
              List[PrincessFeature](
                initialCovarianceDiagonal, initialCovarianceOffDiagonal,
                new VectorPrincessFeature(actuatorValues),
                new VectorPrincessFeature(state.getDeltaComponents))
                 ++ observations.map(o => new VectorPrincessFeature(o)).toList)
                with Serializable

/**
  * 'Deserializes' a LocalizationInput from a PrincessFeatureCollection
  */
class KalmanFilterInputBuilder extends InstanceBuilder[KalmanFilterInputWrapper] {
  override def build(c:PrincessFeature) = {
    val coll = c.asInstanceOf[PrincessFeatureCollection]
    val covarianceDiagonal = coll.subfeatures(0).asInstanceOf[ScalarPrincessFeature].value
    val covarianceOffDiagonal = coll.subfeatures(1).asInstanceOf[ScalarPrincessFeature].value
    val actuators = coll.subfeatures(2).asInstanceOf[VectorPrincessFeature].value
    val state = coll.subfeatures(3).asInstanceOf[VectorPrincessFeature].value
    val observations = coll.subfeatures.drop(4)

    new KalmanFilterInputWrapper(
      new ComponentState(new ArrayRealVector(Array(0.0, 0.0)), state),
      actuators,
      observations.map(o => o.asInstanceOf[VectorPrincessFeature].value),
      covarianceDiagonal,
      covarianceOffDiagonal, null)
  }
}
