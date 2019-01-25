package com.cra.princess.components.kalmanfilter

import com.cra.princess._
import com.cra.princess.models.TransformedSingleFunctionKalmanFilter
import com.cra.princess.models.kalmanfiltercomponents._
import org.apache.commons.math3.linear._

import com.cra.princess.localizationalgorithm.components.ComponentState
import org.yaml.snakeyaml.Yaml
import org.yaml.snakeyaml.constructor.CustomClassLoaderConstructor
import java.io.FileInputStream

import com.cra.princess.util.Logs
import java.io.FileNotFoundException

import com.cra.princess.core.{BoundedScalarPrincessFeature, Intent, ScalarPrincessFeature}
import com.cra.princess.kalmanfilter.{KalmanFilterEnvironmentWrapper, KalmanFilterInputWrapper}
import com.cra.princess.localizationalgorithm.KinematicsModel

case class ControlParams(dt: Long, pNoise: RealVector, mNoise: RealVector, controlInput: java.util.List[java.lang.Double])

class KalmanFilterComponentImpl(intentThreshold: Double = 0.0) extends KalmanFilterComponent with Logs {

  // TODO: are we using this config?
  private val config = {
    try {
      val yaml: Yaml = new Yaml(new CustomClassLoaderConstructor(classOf[KalmanFilterConfig], classOf[KalmanFilterConfig].getClassLoader()))
      val input = new FileInputStream("kalmanfilter.yaml")
      Some(yaml.load(input).asInstanceOf[KalmanFilterConfig])
    } catch {
      case me: scala.MatchError => {
        log.error("Error reading Kalman Filter configuration file: " + me.getLocalizedMessage)
        None
      }
      case fnf: FileNotFoundException => {
        log.error("Kalman Filter configuration file not found")
        None
      }
    }
  }

  private val defaultControls = Map("bDiag0" -> new BoundedScalarPrincessFeature(1, 1, 1),
                                    "bDiag1" -> new BoundedScalarPrincessFeature(1, 1, 1),
                                    "qDiag0" -> new BoundedScalarPrincessFeature(0.3, 1e-5, 1),
                                    "qDiag1" -> new BoundedScalarPrincessFeature(0.3, 1e-5, 1),
                                    "rDiag0" -> new BoundedScalarPrincessFeature(0.1, 1e-5, 1),
                                    "rDiag1" -> new BoundedScalarPrincessFeature(0.2, 1e-5, 1))

  private val initialControls = config match {
    case Some(c) =>
      log.debug("Using Kalman Filter configuration from config file")
      Map("bDiag0" -> c.actuator3,
        "bDiag1" -> c.actuator4,
        "qDiag0" -> c.processNoiseXVel,
        "qDiag1" -> c.processNoiseYVel,
        "rDiag0" -> c.xmeasurementNoise,
        "rDiag1" -> c.ymeasurementNoise
      )
    case None => {
      log.debug("Using built-in default Kalman Filter configuration")
      defaultControls
    }
  }

  private var currentControls: ComponentControls = initialControls

  val intent_ = new KalmanFilterIntent(List[Intent](), intentThreshold, 10)
  def intent = intent_

  var kf = new TransformedSingleFunctionKalmanFilter()

  def getInitialControls(): ComponentControls = initialControls

  override def updateControls(c: ComponentControls): Unit = {
    if (null != c) {
      currentControls = c
    } else {
      currentControls = defaultControls
    }
  }
  
  override def runComponent(env: KalmanFilterEnvironmentWrapper, input: KalmanFilterInputWrapper): KalmanFilterOutput = {
    // INPUTS
    val prevVelocity = input.state.getDeltaComponents()
    val actuatorDeltas = MatrixUtils.createRealVector(KinematicsModel.getAcceleration(input.actuatorValues.toArray, prevVelocity.toArray))
    val sensor = input.observations(0)

    // FIXED CONTROLS
    val A: RealMatrix = MatrixUtils.createRealIdentityMatrix(2) // state transition is always identity
    val H: RealMatrix = MatrixUtils.createRealIdentityMatrix(2) // observation matrix (no controls)

    // CONTROLS
    def getCVal(c:Control) = c.asInstanceOf[ScalarPrincessFeature].value
    val bDiag0 = getCVal(currentControls("bDiag0"))
    val bDiag1 = getCVal(currentControls("bDiag1"))
    val B: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(bDiag0, bDiag1)) // control (has controls)
    val qDiag0 = getCVal(currentControls("qDiag0"))
    val qDiag1 = getCVal(currentControls("qDiag1"))
    val Q: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(qDiag0, qDiag1)) // process noise covariance (has controls)
    val rDiag0 = getCVal(currentControls("rDiag0"))
    val rDiag1 = getCVal(currentControls("rDiag1"))
    val R: RealMatrix = MatrixUtils.createRealDiagonalMatrix(Array(rDiag0, rDiag1))

    val outArray = kf.autoTransformedrunAlgorithm(prevVelocity, sensor, actuatorDeltas, input.covariance,
      A.getEntry(0,0), 0, 0, A.getEntry(1,1),
      B.getEntry(0,0), 0, 0, B.getEntry(1,1),
      H.getEntry(0,0), 0, 0, H.getEntry(1,1),
      Q.getEntry(0,0), 0, 0, Q.getEntry(1,1),
      R.getEntry(0,0), 0, 0, R.getEntry(1,1))
    val outCovariance = outArray match { case Array(_, pNext: RealMatrix, _) => pNext}
    val (stateEstimate, residualVector) = outArray match { case Array(xNext: RealVector, _, y_hat: RealVector) => (xNext, y_hat)}

    log.debug(s"state estimate = ${stateEstimate.toString}")
    val componentState = new ComponentState(MatrixUtils.createRealVector(Array(0.0, 0.0)), stateEstimate)
    val output = new KalmanFilterOutput(componentState, outCovariance, residualVector)
    log.debug(s"residual vector norm = ${output.getMeasurementResidual.getNorm}")
    output
  }
  
  def component(env: KalmanFilterEnvironmentWrapper, input: KalmanFilterInputWrapper, controls: ComponentControls): KalmanFilterOutput = {
    //getOutputTrajectory(env, input, controls).last
    // Apply controls to Kalman Filter
    if((controls != null) && controls.nonEmpty) {
      updateControls(controls)
    }
    this.runComponent(env, input)
  }

  def metricCalculator(e: KalmanFilterEnvironmentWrapper, i: KalmanFilterInputWrapper, o: KalmanFilterOutput): ComponentMetrics = {
    val cm = List(o.getMeasurementResidual.getNorm)
    cm
  }

}